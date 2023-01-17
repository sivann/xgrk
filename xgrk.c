/*
 * xgrk - Greek keyboard support for X
 *
 * (c) Spiros Ioannou 1999-2000 under GPL
 *
 * sivann@softlab.ece.ntua.gr
 * http://www.softlab.ece.ntua.gr/~sivann/xgrk
 *
 * okok, the whole thing needs to be rewritten -someday
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/xpm.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#include "xgrk_uk.xpm"
#include "xgrk_el.xpm"

#ifndef alth
#include "xgrk.h"
#else
#include "xgrk2.h"
#endif

long poll_interval=25000;  	/* microseconds */ 
long reset_delay=100000;	/* microseconds */
int tt=10;			/* count */

/*poll_interval: If set too high, it will miss keystrokes. 
 *		 If set too low, it will eat up cpu.
 */

/*reset_delay:    If set too high, you'll get many accented greek characters.
 * 		  If set too low, characters won't be accented 
 *		  RACE CONDITION
 */


char version[]="version 1.6 , Mar 2000";

char *KeyEventToString (XEvent * ev);
int map_init (Display *);
void setmap (Display *, int);
void descend_tree (Window, unsigned long);
int parseopts (int argc, char **argv);
void setXFlag (Window * , Pixmap * );


char cur_keymap[32], prev_keymap[32];

Display *d;
char *display = NULL;
KeySym *original_ks;
int min_keycode, max_keycode, numof_keycodes, syms_per_keycode;
unsigned char alt_l, meta_l,meta_r, alt_r, shift_l, shift_r, semicolon ;
unsigned char control_l,control_r;
int poll_mode = 1;
int flag = 1;
int verbose=0;
long int gx=0,gy=0;

KeySym *greek_plain_ks, *greek_accent_ks;
KeySym *greek_diaeresis_ks, *greek_diaeresis_accent_ks;

int savestate=0,restorestate=0;


/*A Signal handler -- try to reset to Latin*/
void
signal_hdl(int koko)
{
  fprintf(stderr,"\nxgrk:Reseting to Latin...");
  setmap (d, -1);
  fprintf(stderr,"Done\n");
  exit (koko);
}

/*Caused when the WM closes the program*/
void
pipe_hdl(int koko)
{
  /* This sucks but works somehow*/
  d = XOpenDisplay (display);
  fprintf(stderr,"xgrk:Reseting to Latin...\n");
  setmap (d, -1);
  XCloseDisplay(d);
  fprintf(stderr,"Done\n");
  exit(koko);
}

quit() {
  fprintf(stderr,"xgrk:Reseting to Latin...\n");
  setmap (d, -1);
  XCloseDisplay(d);
  fprintf(stderr,"Done\n");
  exit(0);
}

/*Descend the tree periodically*/
void
alarm_hdl (int koko)
{
  descend_tree (DefaultRootWindow (d), KeyPressMask);
  signal (SIGALRM, alarm_hdl);
  alarm (2);
}

/*Descend the client tree and set an event handler everywhere*/
void
descend_tree (Window w, unsigned long type)
{
  int ret, i;
  static long int level = 0;
  unsigned int nchildren;
  Window root, parent, *children;

  alarm (0);
  /* printf("Descending tree level:%ld\n",level); */

  ret = XQueryTree (d, w, &root, &parent, &children, &nchildren);

  if (ret == False) {
    fprintf (stdout, "xgrk:Query error level:%ld\n", level);
    return;
  }
  if (!nchildren)
    return;

  if (w == root) {
    level = 0;
    XSelectInput (d, root, type);
  }
  level++;

  for (i = 0; i < nchildren; i++) {
    XSelectInput (d, children[i], type);
    descend_tree (children[i], type);
  }

  if (children)
    XFree (children);
}

#define IS_DOWN(keymap,keycode)  (int)((keymap[keycode/8]>>(keycode%8))&1)

int
main (int argc, char *argv[])
{
  char *string;
  int state = -1,i;
  int keycode = 0, kc;
  int pre2state=-1,prevstate=-1,prevkeycode = 0;
  int status;
  int screen, black;
  int width, height;
  unsigned long int root_height,root_width,counter=0;
  int sfd,r;
  char buff[256];
  char hostname[64];
  KeySym KS[256];

  XEvent xev;
  Window root, win, win2;
  Pixmap pixmap_uk, pixmap_el;
  XpmAttributes attributes;
  XSizeHints wmhints;
  Atom closedownAtom;

  /*command line options*/
  parseopts (argc, argv); 

#ifdef NOXPM
  flag=0;
#endif
  
  if (verbose) {
    printf("poll interval : %ld us\n",poll_interval);
    printf("reset delay:    %ld us\n",reset_delay);
    printf("tt count:    %d us\n",tt);
  }

  d = XOpenDisplay (display);
  if (d == NULL) {
    perror ("xgrk:XOpenDisplay");
    exit (10);
  }

  XDisplayKeycodes (d, &min_keycode, &max_keycode);
  numof_keycodes = max_keycode - min_keycode + 1;
  original_ks = XGetKeyboardMapping (d, min_keycode,
				     numof_keycodes, &syms_per_keycode);

  if (savestate) {
    if (gethostname(hostname,64)){
      perror("gethostname");
      exit(errno);
    }
    sprintf(buff,"%s/.xgrk-%s",getenv("HOME"),hostname);
    sfd=open(buff,O_WRONLY|O_CREAT, 0644);
    if (!sfd) {
      perror(buff);
      exit(errno);
    }
    r=write(sfd,original_ks,numof_keycodes*sizeof(KeySym));
    printf("written %d bytes (%d keycodes) to %s\n",r,numof_keycodes,buff);

    exit(0);
  }
  if (restorestate) {
    if (gethostname(hostname,64)){
      perror("gethostname");
      exit(errno);
    }
    sprintf(buff,"%s/.xgrk-%s",getenv("HOME"),hostname);
    sfd=open(buff,O_RDONLY);
    if (!sfd) {
      perror(buff);
      exit(errno);
    }

    r=read(sfd,original_ks,numof_keycodes*sizeof(KeySym));
    numof_keycodes=r/sizeof(KeySym);

    XChangeKeyboardMapping (d, min_keycode, syms_per_keycode,
			    original_ks, numof_keycodes);
    XSync (d, False);
    printf("restored %d keycodes\n",numof_keycodes);
    exit(0);
  }


  map_init (d);

  root = DefaultRootWindow (d);
  screen = DefaultScreen (d);
  black = BlackPixel (d, screen);
  root_height=DisplayHeight(d,screen);
  root_width=DisplayWidth(d,screen);

  /*Establish the signal handlers*/
  signal(SIGHUP,signal_hdl);	
  signal(SIGINT,signal_hdl);	
  signal(SIGTERM,signal_hdl);	

#ifndef NOXPM
  /* if we show the little country flag xpm */
  if (flag) {
    signal(SIGPIPE,pipe_hdl);	


    attributes.valuemask = 0;
    status = XpmCreatePixmapFromData (d, root, gb, &pixmap_uk,
				  NULL, &attributes);

    if (status != XpmSuccess) {
      fprintf (stderr, "%s\n",XpmGetErrorString (status));
      exit (-1);
    }

    status = XpmCreatePixmapFromData (d, root, greece, &pixmap_el,
				  NULL, NULL);

    if (status != XpmSuccess) {
      fprintf (stderr, "%s\n",XpmGetErrorString (status));
      exit (-2);
    }

    width = attributes.width;
    height = attributes.height;
    if (gx<0) gx+=root_width+gx-width;
    if (gy<0) gy=root_height+gy-height;

    win = XCreateSimpleWindow (d, root, gx,gy, width, height, 0,
			       black, black);
    
    win2 = XCreateSimpleWindow (d, win, 0, 0, width, height, 0,
				black, black);
				
    XStoreName (d, win, "xgrk");
   
    wmhints.flags=PSize|PMinSize|PMaxSize|USPosition;
    wmhints.width=wmhints.min_width=wmhints.max_width=width;
    wmhints.height=wmhints.min_height=wmhints.max_height=height;
    XSetWMNormalHints(d,win,&wmhints);

    XSelectInput (d, win2, ButtonPressMask);

    /* Get Window manager's close event*/
    if (closedownAtom = XInternAtom(d, "WM_DELETE_WINDOW", False)) 
      XSetWMProtocols(d, win, &closedownAtom, 1);

    XMapWindow (d, win);
    XMapWindow (d, win2);
    XSync(d,False);
  }

  if (flag) 			/*we want a flag to be displayed*/
    setXFlag (&win2,&pixmap_uk);
  
#endif

  if (!poll_mode) { 		/*event mode*/
    signal (SIGALRM, alarm_hdl);
    descend_tree (root, KeyPressMask);
    XSelectInput (d, root, SubstructureNotifyMask);
  }
  else if (poll_mode)
    XQueryKeymap (d, prev_keymap);

  while (1) {
    if (!poll_mode) {
      XSync (d, True);	/* Alt key repeats forever in XFree without this */
      XNextEvent (d, &xev);
      if (verbose)
	printf ("\n00-Event:%d\n", xev.type);
      keycode = xev.xkey.keycode;
      usleep (10000);
    }
    else {
      if (XPending(d)){
	XNextEvent (d, &xev);
	XSync(d,False);
	if (verbose)
	  printf ("\n01-Event:%d\n", xev.type);
      }
      /*Got quit from window manager*/
      if (xev.xany.type == ClientMessage && 
	  ((XClientMessageEvent *) & xev)->data.l[0] == closedownAtom) {
	quit();
      }
      usleep (poll_interval);	/* Poll interval */
      XQueryKeymap (d, cur_keymap);
      if (memcmp (cur_keymap, prev_keymap, 32) == 0)
	if (!flag && xev.type!=ButtonPress) 
	  continue;		/*if keyboard state is the same*/

      keycode = -1;
      /*get the keycodes of the pressed keys*/ 
      /*keycode>0: pressed, keycode<0: released*/
      for (kc = min_keycode; kc <= max_keycode; kc++)
	if (IS_DOWN (cur_keymap, kc) - IS_DOWN (prev_keymap, kc) == 1) {
	  keycode = kc;
	}
	else if (IS_DOWN (cur_keymap, kc) - IS_DOWN (prev_keymap, kc) == -1) {
	  keycode = -kc;
	}

      memcpy (prev_keymap, cur_keymap, 32);
    }
    if (keycode==control_l) {	/*switch to Latin to get Ctrl characters*/
      if (state>=0) { 
	state=-1;
	setmap (d, -1);
	if (flag) {
	  setXFlag (&win2,&pixmap_uk);
	  XStoreName (d, win, "xgrk-Latin");
	}
      }
    }
  
    if (tt>0) {
      counter++;
      if (counter >1000000) counter=0;
    }

    //printf("%ld ",counter);fflush(stdout);

    if (poll_mode && keycode<0)
      if (!flag || (flag && xev.type != ButtonPress))
	continue;

    if (!poll_mode && (xev.type == MapNotify)) {
      usleep (10000);
      descend_tree (root, KeyPressMask);
      alarm (1);		/* Re - descent the tree after a while */
    }
    else if (poll_mode || xev.type == KeyPress || xev.type==ButtonPress) {
      if (!poll_mode) {
	string = KeyEventToString (&xev);
	if (string == NULL)
	  continue;
	if (verbose && strlen (string) == 1)
	  printf ("%c", *string);
      }

      if (verbose && !poll_mode)
	printf ("<%s>", string);
      if (verbose)
        printf ("03-keycode:%d\n", keycode);

      /* alt-shift timer*/
      if (tt>0 && (keycode == alt_l || keycode == meta_l ||
	  keycode == alt_r || keycode == meta_r))
	counter=0;

      /*Handle Alt+Shift/Meta+Shift. Keyboard toggle*/
      if (( (flag && xev.type == ButtonPress) || 
	    (keycode == shift_l &&
	  (prevkeycode == alt_l || prevkeycode == meta_l))  ||
	    (keycode == shift_r && 
	  (prevkeycode == alt_r || prevkeycode == meta_r)) )) {

	if (!(flag && xev.type == ButtonPress) && tt>0 && counter>tt) {
	  if (verbose)
	    printf("\n%ld>tt=%d, toggle timed out (tt option) \n",counter,tt);
	  continue;
	}


	if (state<0){
	  state = 0;
	  setmap (d, 0);	/*greek*/
	  if (flag) {
	    setXFlag (&win2,&pixmap_el);
	    XStoreName (d, win, "xgrk-Greek");
	  }
	}
	else
	{
	  state = -1;
	  setmap (d, -1);	/*latin*/
	  if (flag){  
	    setXFlag (&win2,&pixmap_uk);
	    XStoreName (d, win, "xgrk-Latin");
	  }
	}
      }

      /*Handle accents*/

      if (keycode == semicolon && 
	  (state == 0 && 
	   ((prevkeycode!= shift_r) && (prevkeycode != shift_l) 
	|| (pre2state==-1 && prevstate==0)))) {

	setmap (d, 1);		/*greek accented*/
	state = 1;
      }
      else if (keycode == semicolon && state == 0 && pre2state !=-1 &&
	  ((prevkeycode == shift_r) || (prevkeycode == shift_l)) ) {
	setmap (d, 2);		/*greek diaeresis*/
	state = 2;
      }
      else if (keycode == semicolon && state == 1 && 
	  ((prevkeycode == shift_r) || (prevkeycode == shift_l)) ) {
	setmap (d, 3);		/*greek accented dieresis*/
	state = 3;
      }
      else if (state>0 && keycode && keycode != shift_r && keycode != shift_l) {
	/* Race condition. Will the Xclient get the accented letter before 
	 * we do and the map gets reset again? yes if we are slow enough... 
	 */
	usleep (reset_delay);
	XSync (d, False);
	setmap (d, 0);
	state = 0;
      }

      fflush (stdout);
      prevkeycode = keycode;
    }
      pre2state = prevstate;
      prevstate = state;
  }
}


#define KEY_BUFF_SIZE 256
static char key_buff[KEY_BUFF_SIZE];

char *
KeyEventToString (XEvent * ev)
{
  int count;
  char *tmp;
  KeySym ks;

  ks = 0;

  if (ev->type == KeyPress) {
    count = XLookupString ((XKeyEvent *) ev, key_buff, KEY_BUFF_SIZE, &ks, NULL);
    key_buff[count] = '\0';

    if (count == 0) {
      tmp = XKeysymToString (ks);
      if (tmp)
	strcpy (key_buff, tmp);
      else
	key_buff[0] = 0;
    }

    return key_buff;
  }
  else
    return NULL;
}



/*fill in the variables with the appropriate keycodes*/
int
map_init (Display * d)
{

  int i;
  int keycode_size;
  unsigned char keycode;

  char letters[] =
  {'a', 'b', 'g', 'd', 'e', 'z', 'h', 'u', 'i', 'k', 'l', 'm', 'n', 'j',
   'o', 'p', 'r', 'w', 's', 't', 'y', 'f', 'x', 'c', 'v', 'q', ';' };

  /* Find the keycodes from the letters */

  for (i = 0; i < sizeof (letters); i++) {
    keycode = XKeysymToKeycode (d, letters[i]);
    greek_plain[i][0] = keycode;
    greek_accent[i][0] = keycode;
    greek_diaeresis[i][0] = keycode;
    greek_diaeresis_accent[i][0] = keycode;
  }

  alt_l = XKeysymToKeycode (d, XStringToKeysym ("Alt_L"));
  alt_r = XKeysymToKeycode (d, XStringToKeysym ("Alt_R"));
  meta_l = XKeysymToKeycode (d, XStringToKeysym ("Meta_L"));
  meta_r = XKeysymToKeycode (d, XStringToKeysym ("Meta_R"));
  shift_l = XKeysymToKeycode (d, XStringToKeysym ("Shift_L"));
  shift_r = XKeysymToKeycode (d, XStringToKeysym ("Shift_R"));
  semicolon = XKeysymToKeycode (d, XStringToKeysym ("semicolon"));
  control_l = XKeysymToKeycode (d, XStringToKeysym ("Control_L"));
  control_r = XKeysymToKeycode (d, XStringToKeysym ("Control_R"));
  
  if (verbose)
    printf("semicolon:%d\n",semicolon);

  /* Now, make the keysym tables */
  keycode_size = numof_keycodes * syms_per_keycode * sizeof (KeySym);
  greek_plain_ks = (KeySym *) malloc (keycode_size);
  greek_accent_ks = (KeySym *) malloc (keycode_size);
  greek_diaeresis_ks = (KeySym *) malloc (keycode_size);
  greek_diaeresis_accent_ks = (KeySym *) malloc (keycode_size);

  if (!(greek_plain_ks && greek_accent_ks && greek_diaeresis_ks &&
	greek_diaeresis_accent_ks)) {
    perror ("xgrk:malloc of keysym tables failed");
    exit (errno);
  }

  memcpy (greek_plain_ks, original_ks, keycode_size);
  memcpy (greek_accent_ks, original_ks, keycode_size);
  memcpy (greek_diaeresis_ks, original_ks, keycode_size);
  memcpy (greek_diaeresis_accent_ks, original_ks, keycode_size);

  for (i = 0; i < sizeof(letters); i++) {
    keycode = greek_plain[i][0];	/* keycodes are the same in all tables*/

    greek_plain_ks[(keycode - min_keycode) * syms_per_keycode] =
	greek_plain[i][1];
    greek_plain_ks[(keycode - min_keycode) * syms_per_keycode + 1] =
	greek_plain[i][2];

    greek_accent_ks[(keycode - min_keycode) * syms_per_keycode] =
	greek_accent[i][1];
    greek_accent_ks[(keycode - min_keycode) * syms_per_keycode + 1] =
	greek_accent[i][2];

    greek_diaeresis_ks[(keycode - min_keycode) * syms_per_keycode] =
	greek_diaeresis[i][1];
    greek_diaeresis_ks[(keycode - min_keycode) * syms_per_keycode + 1] =
	greek_diaeresis[i][2];

    greek_diaeresis_accent_ks[(keycode - min_keycode) * syms_per_keycode] =
	greek_diaeresis_accent[i][1];
    greek_diaeresis_accent_ks[(keycode - min_keycode) * syms_per_keycode + 1] =
	greek_diaeresis_accent[i][2];

  }
  return 1;
}

/*change keyboard mapping*/
void
setmap (Display * d, int map_id)
{
  verbose && printf ("Switching to map %d\n", map_id);
  switch (map_id) {
  case 0:
    XChangeKeyboardMapping (d, min_keycode, syms_per_keycode,
			    greek_plain_ks, numof_keycodes);
    break;
  case 1:
    XChangeKeyboardMapping (d, min_keycode, syms_per_keycode,
			    greek_accent_ks, numof_keycodes);
    break;
  case 2:
    XChangeKeyboardMapping (d, min_keycode, syms_per_keycode,
			    greek_diaeresis_ks, numof_keycodes);
    break;
  case 3:
    XChangeKeyboardMapping (d, min_keycode, syms_per_keycode,
			    greek_diaeresis_accent_ks, numof_keycodes);
    break;
  default:
    XChangeKeyboardMapping (d, min_keycode, syms_per_keycode,
			    original_ks, numof_keycodes);
  }

  XSync (d, False);
}

int
parseopts (int argc, char **argv)
{
  int i;


  for (i = 1; i < argc; i++) {
    if (strcmp (argv[i], "-poll") == 0) {
      poll_mode = 1;
    }
    else if (strcmp (argv[i], "-save") == 0) {
      savestate=1;
    }
    else if (strcmp (argv[i], "-restore") == 0) {
      restorestate=1;
    }
    else if (strcmp (argv[i], "-event") == 0) {
      poll_mode = 0;
    }
    else if (strcmp (argv[i], "-v") == 0) {
      verbose = 1;
    }
    else if (strcmp (argv[i], "-noflag") == 0) {
      flag = 0;
    }
    else if (strcmp (argv[i], "-geometry") == 0) {
      if (argc<i+2) {
	fprintf (stderr, "xgrk: -geometry: parse error\n");
	exit (0);
      }
      i++;
      if (sscanf(argv[i],"%ld%ld",&gx,&gy) < 2) {
	printf("xgrk: -geometry: not enough parameters\n");
	exit(0);
      }
      printf("gx:%ld,gy:%ld",gx,gy);
    }
    else if (strcmp (argv[i], "-rd") == 0) {
      if (argc<=i+1) {
	fprintf (stderr, "xgrk: -rd: parse error\n");
	exit (0);
      }
      i++;
      reset_delay = atol(argv[i]);
    }
    else if (strcmp (argv[i], "-tt") == 0) {
      if (argc<=i+1) {
	fprintf (stderr, "xgrk: -tt: parse error\n");
	exit (0);
      }
      i++;
      tt = atoi(argv[i]);
      if (tt<0){
	fprintf (stderr, "");
	exit (0);
      }
    }
    else if (strcmp (argv[i], "-pi") == 0) {
      if (argc<=i+1) {
	fprintf (stderr, "xgrk: -pi: parse error\n");
	exit (0);
      }
      i++;
      poll_interval = atol(argv[i]);
      if (poll_interval<50){
	fprintf (stderr, "xgrk: -pi: poll interval must be >50\n");
	exit (0);
      }
    }
    else if (strcmp (argv[i], "-display") == 0) {
      if (argc<=i+1) {
	fprintf (stderr, "xgrk: -display: parse error\n");
	exit (0);
      }
      i++;
      display = argv[i];
    }
    else {
      fprintf(stderr, "xgrk: invalid argument %s\n\n", argv[i]);
      fprintf(stderr, "xgrk %s,(c) Spiros Ioannou 1999-2000\n",version);
      fprintf(stderr, 
	  "Usage: xgrk [-poll] [-event] [-v] [-noflag] [-display display]\n"
	  "\t    [-geometry x y] [-pi poll_interval] [-rd reset_delay]\n"
	  "\t    [-save] [-restore]\n");
      fprintf(stderr,
      "\n-poll\t\tpoll the xserver for keyboard stat every %ld us (default)\n",
	  poll_interval);
      fprintf(stderr,"-event\t\tevent based keyboard monitoring\n");
      fprintf(stderr,"-noflag\t\tdon't display a window\n");
      fprintf(stderr,"-display\tdisplay to connect to\n");
      fprintf(stderr,"-geometry\twhere to popup\n");
      fprintf(stderr,"-pi <interval>\tdefault value is 25000 microseconds.\n\t\t"
	  "If set too high, it will miss keystrokes,\n\t\t"
	  "if set too low, it will eat up cpu.\n");
      fprintf(stderr,"-rd <interval>\tdefault value is 100000 microseconds.\n\t\t"
	  "If set too high, you'll get many accented greek characters.\n\t\t"
	  "If set too low, characters won't be accented.\n");
      fprintf(stderr,"-tt\t\ttoggle timeout: counted in \"poll_interval\"s\n\t"
	  "\thow quick alt and shift must be pressed. Default=10\n");
      fprintf(stderr,"-save\t\tsave current keycodes to file\n");
      fprintf(stderr,"-restore\trestore previously saved keycodes\n");
      fprintf(stderr,"-v\t\tbe verbose \n\n");
      exit (0);
    }
  }
  return i;
}

/*display the country flag*/
void setXFlag (Window * win, Pixmap * pixmap)
{
#ifndef NOXPM
  XSetWindowBackgroundPixmap (d, *win, *pixmap);
  XUnmapWindow (d,* win);
  XMapWindow (d,* win);
#endif
}
