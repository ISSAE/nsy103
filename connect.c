/*n Linux compile with gcc connect.c -L/usr/X11R6/lib -lX11
*/


#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<stdio.h>


int main(){
        Display *display_name;
        int depth,screen,connection;


        /*Opening display and setting defaults*/
        display_name = XOpenDisplay(NULL);
        screen = DefaultScreen(display_name);
        depth = DefaultDepth(display_name,screen);
        connection = ConnectionNumber(display_name);


        /*Displaying the info gathered*/
        printf("The display is::%s\n",XDisplayName((char*)display_name));
        printf("Width::%d\tHeight::%d\n",
                                DisplayWidth(display_name,screen),
                                DisplayHeight(display_name,screen));
        printf("Connection number is %d\n",connection);


        if(depth == 1)
                printf("You live in prehistoric times\n");
        else
                printf("You've got a coloured monitor with depth of %d\n",
                        depth);


        /*Closing the display*/
        XCloseDisplay(display_name);
}

