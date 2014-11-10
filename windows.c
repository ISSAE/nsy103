/* window.c --This program opens a window on the display
* Use "gcc -o window window.c -L/usr/X11R6/lib -lX11
* to compile this code.
*/


#include <X11/X.h>
#include <X11/Xlib.h>


int main(void)
{
Display *display;
Window window, rootwindow;
int screen;


display = XOpenDisplay(NULL);
screen = DefaultScreen(display);
rootwindow = RootWindow(display,screen);
window = XCreateSimpleWindow(display, rootwindow,
                0, 0, 100, 100, 1, 0, 0);
XMapWindow(display, window);
XFlush(display);


sleep(10);
XCloseDisplay(display);
return (0);
}
