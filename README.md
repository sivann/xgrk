    XGRK - write greek in the X Window System

_XGRK - Write GREEK in the X Window System_

_xgrk **1.6.3** , (C) Spiros Ioannou 1998-2001_  

![english](uk.png)  ![greek](greek.png)

### Introduction

This program is a contribution to the community of greek UNIX users. It provides the possibility to change keyboard mapping with alt-shift or meta-shift combinations or by clicking on the displayed flag image. You will be able to write greek in X programs like netscape, xedit or xterm without the need for a special keyboard or driver. You must have the greek fonts, which are not provided with this package, but you can find some in the link section at the end of this page.  
  

### Compatibility

![APPLE](images/silverapple.gif "APPLE") ![UNIX](images/os-digital.gif "DGUX") ![HPUX](images/hplogo.gif "HPUX") ![IRIX](images/sgilogo.gif "IRIX") ![GNU/Linux](images/linuxlogo.gif "GNU/Linux") ![SunOS](images/sunlogo.gif "SunOS")

_This program may not work with recent XFree86 distributions with KDE/GNOME combinations. These systems usually have their own layout switching utilities which usually rely on libraries (e.g. [libxklavier](https://freedesktop.org/Software/LibXklavier)) which take advantage of the recent XKB Xserver extensions._  

Keycodes are auto-detected on startup so it should work with all unices and keyboard layouts.  
This program has been **succesfully** tested with:

*   i386Linux (Redhat 5.2, Redhat 6, Redhat 6.1, debian 2.1) and the following window managers: fvwm, fvwm2, twm, KDE, GNOME
*   KDE 2.1.1, RedHat 7.1, kernel 2.4.2-2 (RedHat's default), Intel P4 box.
*   FreeBSD 3.4 with WindowMaker, Enlightenment & GNOME (i386)
*   Debian Linux sparc64 with kernel 2.2.14 on a Sun ULTRA 1 and the following window managers: fvwm, twm
*   SparcLinux (Redhat 6) on a Sparc Station 5 and the following window managers: fvwm, twm
*   Sun Ultra 10 with SunOs 5.7 and Openwin , 24bit display and type-4 keyboard, non-greek ready (dip switches under the keyboard) and the following window managers: fvwm, twm, CDE, KDE
*   Sparc Station 10 with Solaris 2.6 , 8bit display and type 3 keyboard and the following window managers: fvwm, CDE
*   Silicon Graphics Indy R5500 with IRIX 6.2, the default X server, 8bit display and the following window managers: twm,mwm,4Dwm
*   Hewllet Packard apollo 9000/730 running HP-UX A.09.05 C (Alt key = key named 'Extended char') and the following window manager: HP-VUE
*   MacOSX 10.3.2/Apple X11 1.0 (XFree 4.3.0 based) (you must first disable "Follow system keyboard layout" from X11/Preferences/Input)
*   MacOSX 10.4 Tiger/Apple X11
*   opteron 242/Solaris 10

### Requirements

I tried to make it as simple as possible, so it depends only on Xlib for the main functionality and libXpm for the .xpm flag.

The greek/uk flag images are in xpm format so that you can change them as you please.  
The XPM library (libXpm) can be found here: [ftp://koala.inria.fr/pub/xpm/](ftp://koala.inria.fr/pub/xpm/) or here [http://koala.ilog.fr/ftp/pub/xpm/](http://koala.ilog.fr/ftp/pub/xpm/)  
The X keyboard extensions (XKB) are **not** needed.

  

Installation
------------

1\. run make  
2\. copy the **"xgrk"** and **"xgrk2"** binaries somewhere in your path like /usr/local/X11/bin  

The xgrk2 binary is created with an alternative xgrk.h from [E. Lefty Kreouzis](/cdn-cgi/l/email-protection#a0cccbd2c5cfd5dae0c9ced4c5d2cec5d48ec7d2)  
This one seems to work with different aplications, probably unicode-enabled like the new mozilla builds, gterm etc.  
For non-unicode apps like xterm, xedit, netscape communicator 4.7x use xgrk.  
_xgrk and xgrk2 cannot run at the same time._  

*   For xgrk2 you may need \_XKB\_CHARSET=iso8859-7 in your environment.
*   xgrk2 does not support the middle dot

Hint by Athanasios Douitsis: to run in MacOS's X11 server: edit xgrk.h and xgrk2.h and  

_replace:_
#define DUMMY1 XK\_F30
#define DUMMY2 XK\_F31
_with:_
#define DUMMY1 XK\_Shift\_L
#define DUMMY2 XK\_Shift\_L

You can alternatively download the compiled universal binary below.

Usage
-----

You don't have to be root to run this software. For the following information, left or right keys are the same. Note that the keys don't have to be pressed at the same time, only the right order matters.

Action

Key sequence

Keyboard mapping switching:

Alt + Shift or Meta + Shift

Accent:

';' and then the letter

diaeresis (dialitika):

Shift + ';' and then the letter

accented diaeresis:

';' then Shift+';' and then the letter

Middle Dot (��� ������ �):

Shift + 'w'

Note: _characters ';' and ':' are mapped to the 'q' key in greek mode. If there is no Alt key, the Meta key is used.  
You may also switch language by clicking onto the flag._

### Command line options

\-h		Display help for command line options

-poll           poll the xserver for keyboard stat every 25000 us (default)
                This is the default, it works very well, it doesn't take cpu 
                and works under xterm's 'Secure Keyboard'

-event          event based keyboard monitoring
                This is event-based operation, but windows mapped after the 
                xgrk starts aren't always captured by xgrk

-noflag         don't display a window. 
-display        display to connect to
-geometry       where to popup (ex.: -geometry +0+100 or -geometry -1-1)
-v              be verbose
-pi <interval>  default poll interval value is 25000 microseconds.
                If set too high, it will miss keystrokes,
                if set too low, it will eat up cpu.
-rd <interval>  default reset delay value is 100000 microseconds.
                If set too high, you'll get many accented greek characters.
                If set too low, characters won't be accented.
-tt             toggle timeout: counted in "poll\_interval"s
                how quick alt and shift must be pressed. Default=10
-save           save current keycodes to file ($HOME/.xgrk-hostname)
-restore        restore previously saved keycodes

It is a good idea to put the following in your .xinitrc:  
`xgrk -save`  
  
This will create the file $HOME/.xgrk-hostname with the original keycodes.  
If you don't use an .xinitrc file, just run the above command once from an xterm.  
  
Then, add to your window manager a mouse menu which executes the following:  
`xgrk -restore`  
  
This way, if xgrk gets killed and you're stuck in greek mode, you'll be able to restore the original keyboard status with the mouse menu.

### Notes for greek support in Netscape 4.x

Trick for netscape to display greek fonts in forms and buttons correctly:

1.  Start netscape with : netscape -xrm "\*documentFonts.charset\*iso8859-7:iso-8859-1"
2.  Go to Edit->Preferences-Fonts, choose 8859-1 (or western) (netscape thinks that greek fonts are 8859-1 now), and choose a greek font like Lucidasansgreek for the Variable Width Font field. Do the same for the Fixed Width font.

You're set. You can now use pages like http://www.hellasyellow.gr/onom.html and write greek inside the forms.  
_Note: The UNIX version of [Mozilla](https://www.mozilla.org) seems to handle greek [almost](https://bugzilla.mozilla.org/show_bug.cgi?id=28019) perfectly :-)_

### Notes for fvwm2

Add theese to the appropriate fields in your .fvwm2rc:  
**fvwm2 style:** Style "xgrk" RandomPlacement, NoTitle, StaysOnTop, NoHandles, BorderWidth 0  
  
**fvwm2 swallow option:**  
Very cool, it gets swallowed as a button in the bar:  
\*FvwmButtons( Center Size 60 40 Swallow(UseOld) xgrk \`Exec exec xgrk &\`)

### Unknown BUGS

Well there should be many bugs. Please mail bug corrections and reports to <!-- var username = "sivann"; var hostname = "cs.ntua.gr"; var linktext = username + "@" + hostname; document.write("<a href=" + "mail" + "to:" + username + "@" + hostname + ">" + linktext + "</a>"); //-->

sivann at cs dot ntua dot gr

### TODO

I've been asked to implement the following stuff. I'll try to implement them when I find the time.  

*   Configurable accent key (for Norwegian keyboards which produce ';' with Shift+',').
*   Support for unicode polytonic greek (ancient greek)
*   Better support for Control sequences. (Switch back to greek after Ctrl+c ?)
*   Unify xgrk and xgrk2

### MORE HELP

You can mail me for help.  
Other useful info can be found at: [http://www.hri.org/fonts](http://www.hri.org/fonts)  
and many fonts and links here:[http://www.ccss.de/slovo/unifonts.htm](http://www.ccss.de/slovo/unifonts.htm)

#### Did it work for your OS succesfully?

Please mail me to add your OS in the compatibility list.  
For bug-reports/questions (please,only xgrk-related!) : <!-- var username = "sivann"; var hostname = "cs.ntua.gr"; var linktext = username + "@" + hostname; document.write("<a href=" + "mail" + "to:" + username + "@" + hostname + ">" + linktext + "</a>"); //-->

sivann at cs dot ntua dot gr

  

![](../images/bluedot.gif)

  

Download Sources/Binaries

[xgrk-1.6.3.tar.gz](xgrk-1.6.3.tar.gz)

Latest source release. Produces 2 binaries: xgrk,xgrk2. Read the CHANGES

[xgrk-1.6.3.patch](xgrk-1.6.3.patch)

Security patch by Vacheh D Sardarian

[xgrk\_1.6-1\_i386.deb](xgrk_1.6-1_i386.deb)

Intel Linux debian package (by [taver](/~taver/))

[wm-xgrk-1.6.tar.gz](wm-xgrk-1.6.tar.gz)

A WindowMaker applet written by Nicholas Christopoulos ([\[email protected\]](/cdn-cgi/l/email-protection))

[Binaries](static/)

Click for intel and sparc binaries with libXpm static compiled. Download them, make them executable (chmod +x file) and run them. These binaries are not often updated.

[xgrk on freshmeat](http://freshmeat.net/projects/xgrk/)

The freshmeat entry

  

*   [CHANGES](current/CHANGES)
*   [xgrk-1.4.tar.gz](xgrk-1.4.tar.gz) A previous release
*   [xpm-3.4k.tar.gz](xpm-3.4k.tar.gz) A locally stored and probably outdated version of LibXPM. Get the original from  
    [ftp://koala.inria.fr/pub/xpm/](ftp://koala.inria.fr/pub/xpm/) or [http://koala.ilog.fr/ftp/pub/xpm/](http://koala.ilog.fr/ftp/pub/xpm/)  
    

  

### OTHER INFO

*   [Screenshots](screenshots.html)

*   [greekfonts.tar.gz](greekfonts.tar.gz) including some iso-8859-7 fonts and a 437gr (737) greek vga font (made by me), the latter for accessing greek DOS BBSs
*   [ArialUnicodeMS.ttf.gz](ArialUnicodeMS.ttf.gz) a HUGE unicode font (25MB), includes even ancient greek, works perfectly with Solaris + mozilla
*   [iso8859-7 map](iso8859-7.html)
*   [Dealing with Greek Characters in Computers](greek-zvr.html) by Alexios Zavras
*   [grkbd, a similar software, pc-oriented](http://grkbd.pathfinder.gr)
*   [grvi.c](grvi.c) , runs vim through a pipe and translates keystrokes.
*   [U0370.pdf](U0370.pdf) Greek Unicode fonts
