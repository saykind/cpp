/* GL definitons */
#define BACKGROUND 8
#define pi      3.14159265358979323L
#define twopi 6.28318530717958646L

//#define WIN32
//#define NOGDI

/* End of the GL definitions */

/* The standard libraries used in our program */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <X11/Xlib.h>
//#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glxext.h>
#include <GL/glu.h>

using namespace std;

/* End of standard libraries list */


#ifndef GLX_MESA_swap_control
#define GLX_MESA_swap_control 1
typedef int (*PFNGLXGETSWAPINTERVALMESAPROC)(void);
#endif

static GLboolean fullscreen = GL_FALSE;	/* Create a single fullscreen window */
static GLboolean stereo = GL_FALSE;	/* Enable stereo.  */
static GLboolean animate = GL_TRUE;	/* Animation */
static GLfloat eyesep = 0.2;		/* Eye separation. */
static GLfloat fix_point = 40.0;	/* Fixation point distance.  */
static GLfloat left1, right1, asp;	/* Stereo frustum params.  */ 

static Display *dpy;
static Window win1,win2;
static GLXContext ctx1;

/** Event handler results: */
#define NOP 0
#define EXIT 1
#define DRAW 2

unsigned int w1width=800,w1height=600;
int win1x0=100,win1y0=100;

float angsx=0.,angsy=0.,angsz=-120.,win1_dx=0,win1_dy=0,win1_dz=10;
float win1_mx,win1_my,win1_ox,win1_oy;

#include "colors.h"

GLenum rgb, doubleBuffer;

int button1,draw_yes,show1,show2,show3,show11,show4;



#include "user.h"
#include "open.h"

static void
usage(void)
{
   printf("Usage:\n");
   printf("  -display <displayname>  set the display to run on\n");
   printf("  -stereo                 run in stereo mode\n");
   printf("  -fullscreen             run in fullscreen mode\n");
   printf("  -info                   display OpenGL renderer info\n");
   printf("  -geometry WxH+X+Y       window geometry\n");
}
 
int main(int argc, char* argv[])
{

GLenum type;  
int i11;
char *dpyName = NULL;
GLboolean printInfo = GL_FALSE;

   for (i11 = 1; i11 < argc; i11++) {
      if (strcmp(argv[i11], "-display") == 0) {
         dpyName = argv[i11+1];
         i11++;
      }
      else if (strcmp(argv[i11], "-info") == 0) {
         printInfo = GL_TRUE;
      }
      else if (strcmp(argv[i11], "-stereo") == 0) {
         stereo = GL_TRUE;
      }
      else if (strcmp(argv[i11], "-fullscreen") == 0) {
         fullscreen = GL_TRUE;
      }
      else if (i11 < argc-1 && strcmp(argv[i11], "-geometry") == 0) {
         XParseGeometry(argv[i11+1], &win1x0, &win1y0, &w1width, &w1height);
         i11++;
      }
      else {
         usage();
         return -1;
      }
   }

 
 dpy = XOpenDisplay(dpyName);
 if (!dpy) {
   printf("Error: couldn't open display %s\n",
	  dpyName ? dpyName : getenv("DISPLAY"));
   return -1;
 }

 make_window(dpy, "Cross Cap", win1x0, win1y0, w1width, w1height, &win1, &ctx1);
 XMapWindow(dpy, win1);
 glXMakeCurrent(dpy, win1, ctx1);
 query_vsync(dpy, win1);
 
 if (printInfo) {
   printf("GL_RENDERER   = %s\n", (char *) glGetString(GL_RENDERER));
   printf("GL_VERSION    = %s\n", (char *) glGetString(GL_VERSION));
   printf("GL_VENDOR     = %s\n", (char *) glGetString(GL_VENDOR));
   printf("GL_EXTENSIONS = %s\n", (char *) glGetString(GL_EXTENSIONS));
 }

SetInitialParams();
Init();
Reshape(w1width, w1height);
 
DrawScene3D();

while (1) 
   {
     int op;
     while (XPending(dpy) > 0) 
       {
	 XEvent event;
	 XNextEvent(dpy, &event);
	 if(event.xany.window==win1)  op = Handle_event_win1(dpy, win1, &event);
	 if (op == EXIT)
	   return 0;
       }
     if (op == DRAW)
       {
	 DrawScene3D();
	 op = NOP;
       }
   }
    
 glDeleteLists(theObject, 1);
 glXMakeCurrent(dpy, None, NULL);
 glXDestroyContext(dpy, ctx1);
 XDestroyWindow(dpy, win1);
 XCloseDisplay(dpy);  
    
  }