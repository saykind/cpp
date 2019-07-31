unsigned char rgb_colors[3];
GLuint theObject;

void DrawScene(void)
{
    glPushMatrix();
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    gluLookAt(0,0,win1_dz, 0,0,0, 0,1,0);

    if(draw_yes>0) glDeleteLists(theObject,1);
    theObject = glGenLists(1);
    glNewList(theObject, GL_COMPILE);
    DrawObject();
    glEndList();
    draw_yes=1;

    glColor3ubv(rgb_colors);

	glPushMatrix();
	glTranslatef(win1_dx,win1_dy,0.);

	glRotatef(angsx,0., 1., 0.);
	glRotatef(angsy,1.,0., 0.);
	glRotatef(angsz,0.,0., 1.);	
       	glCallList(theObject);
	glPopMatrix();

	glPopMatrix();

    glFlush();
    /*
    if (doubleBuffer) {
      glutSwapBuffers();
    }
    */
}

void DrawScene3D(void)
{

  if(draw_yes>0) glDeleteLists(theObject,1);
  theObject = glGenLists(1);
  glNewList(theObject, GL_COMPILE);
  DrawObject();
  glEndList();
  draw_yes=1;

   if (stereo) {

      /* First left eye.  */
      glDrawBuffer(GL_BACK_LEFT);
      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glFrustum(-right1/100.,-left1/100.,-asp/100., asp/100., 0.03, 600.0); 

      glMatrixMode(GL_MODELVIEW);

      glPushMatrix();
      glTranslated(-1.5 * eyesep, 0.0, 0.0);
      DrawScene();
      glPopMatrix();

      /* Then right eye.  */

      glDrawBuffer(GL_BACK_RIGHT);
      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
      
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glFrustum(left1/100., right1/100., -asp/100., asp/100., 0.03, 600.0);


      glMatrixMode(GL_MODELVIEW);

      glPushMatrix();
      glTranslated(+1.5 * eyesep, 0.0, 0.0);
      DrawScene();
      glPopMatrix();
      glXSwapBuffers(dpy, win1);
   }
   else 
     {
       glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
       DrawScene();  
       glXSwapBuffers(dpy, win1);
     }

}

void Reshape(int width, int height)
{
  glViewport(0, 0, (GLint) width, (GLint) height);
    if (stereo) 
      {
	GLfloat w;
	asp = (GLfloat) height / (GLfloat) width;
	w = fix_point * (1.0 / 5.0);
	
	left1 = -5.0 * ((w - 0.5 * eyesep) / fix_point);
	right1 = 5.0 * ((w + 0.5 * eyesep) / fix_point);
      }
    else 
      {
	GLfloat h = (GLfloat) height / (GLfloat) width;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.01, 0.01, -h/100., h/100., 0.03, 600.0);
      }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



// Determine whether or not a GLX extension is supported.
static int
is_glx_extension_supported(Display *dpy, const char *query)
{
   const int scrnum = DefaultScreen(dpy);
   const char *glx_extensions = NULL;
   const size_t len = strlen(query);
   const char *ptr;

   if (glx_extensions == NULL) {
      glx_extensions = glXQueryExtensionsString(dpy, scrnum);
   }

   ptr = strstr(glx_extensions, query);
   return ((ptr != NULL) && ((ptr[len] == ' ') || (ptr[len] == '\0')));
}


// Attempt to determine whether or not the display is synched to vblank.

static void
query_vsync(Display *dpy, GLXDrawable drawable)
{
   int interval = 0;

#if defined(GLX_EXT_swap_control)
   if (is_glx_extension_supported(dpy, "GLX_EXT_swap_control")) {
       unsigned int tmp = -1;
       glXQueryDrawable(dpy, drawable, GLX_SWAP_INTERVAL_EXT, &tmp);
       interval = tmp;
   } else
#endif
   if (is_glx_extension_supported(dpy, "GLX_MESA_swap_control")) {
      PFNGLXGETSWAPINTERVALMESAPROC pglXGetSwapIntervalMESA =
          (PFNGLXGETSWAPINTERVALMESAPROC)
          glXGetProcAddressARB((const GLubyte *) "glXGetSwapIntervalMESA");

      interval = (*pglXGetSwapIntervalMESA)();
   } else if (is_glx_extension_supported(dpy, "GLX_SGI_swap_control")) {
      /* The default swap interval with this extension is 1.  Assume that it
       * is set to the default.
       *
       * Many Mesa-based drivers default to 0, but all of these drivers also
       * export GLX_MESA_swap_control.  In that case, this branch will never
       * be taken, and the correct result should be reported.
       */
      interval = 1;
   }


   if (interval > 0) {
      printf("Running synchronized to the vertical refresh.  The framerate should be\n");
      if (interval == 1) {
         printf("approximately the same as the monitor refresh rate.\n");
      } else if (interval > 1) {
         printf("approximately 1/%d the monitor refresh rate.\n",
                interval);
      }
   }
}

// Remove window border/decorations.

static void
no_border( Display *dpy, Window w)
{
   static const unsigned MWM_HINTS_DECORATIONS = (1 << 1);
   static const int PROP_MOTIF_WM_HINTS_ELEMENTS = 5;

   typedef struct
   {
      unsigned long       flags;
      unsigned long       functions;
      unsigned long       decorations;
      long                inputMode;
      unsigned long       status;
   } PropMotifWmHints;

   PropMotifWmHints motif_hints;
   Atom prop, proptype;
   unsigned long flags = 0;

   /* setup the property */
   motif_hints.flags = MWM_HINTS_DECORATIONS;
   motif_hints.decorations = flags;

   /* get the atom for the property */
   prop = XInternAtom( dpy, "_MOTIF_WM_HINTS", True );
   if (!prop) {
      /* something went wrong! */
      return;
   }

   /* not sure this is correct, seems to work, XA_WM_HINTS didn't work */
   proptype = prop;

   XChangeProperty( dpy, w,                         /* display, window */
                    prop, proptype,                 /* property, type */
                    32,                             /* format: 32-bit datums */
                    PropModeReplace,                /* mode */
                    (unsigned char *) &motif_hints, /* data */
                    PROP_MOTIF_WM_HINTS_ELEMENTS    /* nelements */
                  );
}


// Create an RGB, double-buffered window.
// Return the window and context handles.

static void
make_window( Display *dpy, const char *name,
             int x, int y, int width, int height,
             Window *winRet, GLXContext *ctxRet)
{
   int attribs[] = { GLX_RGBA,
                     GLX_RED_SIZE, 1,
                     GLX_GREEN_SIZE, 1,
                     GLX_BLUE_SIZE, 1,
                     GLX_DOUBLEBUFFER,
                     GLX_DEPTH_SIZE, 1,
                     None };
   int stereoAttribs[] = { GLX_RGBA,
                           GLX_RED_SIZE, 1,
                           GLX_GREEN_SIZE, 1,
                           GLX_BLUE_SIZE, 1,
                           GLX_DOUBLEBUFFER,
                           GLX_DEPTH_SIZE, 1,
                           GLX_STEREO,
                           None };
   int scrnum;
   XSetWindowAttributes attr;
   unsigned long mask;
   Window root;
   Window win;
   GLXContext ctx;
   XVisualInfo *visinfo;

   scrnum = DefaultScreen( dpy );
   root = RootWindow( dpy, scrnum );

   if (fullscreen) 
     {
       x = 0; y = 0;
       width = DisplayWidth( dpy, scrnum );
       height = DisplayHeight( dpy, scrnum );
     }

   if (stereo)
     visinfo = glXChooseVisual( dpy, scrnum, stereoAttribs );
   else
     visinfo = glXChooseVisual( dpy, scrnum, attribs );
   if (!visinfo) 
     {
       if (stereo) 
	 {
	   printf("Error: couldn't get an RGB, "
		  "Double-buffered, Stereo visual\n");
	 } else
         printf("Error: couldn't get an RGB, Double-buffered visual\n");
       exit(1);
     }

   /* window attributes */
   attr.background_pixel = 0;
   attr.border_pixel = 0;
   attr.colormap = XCreateColormap( dpy, root, visinfo->visual, AllocNone);
   attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask | ButtonPressMask | ButtonMotionMask ;
   /* XXX this is a bad way to get a borderless window! */
   mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

   win = XCreateWindow( dpy, root, x, y, width, height,
		        0, visinfo->depth, InputOutput,
		        visinfo->visual, mask, &attr );

   if (fullscreen)
      no_border(dpy, win);

   /* set hints and properties */
   {
      XSizeHints sizehints;
      sizehints.x = x;
      sizehints.y = y;
      sizehints.width  = width;
      sizehints.height = height;
      sizehints.flags = USSize | USPosition;
      XSetNormalHints(dpy, win, &sizehints);
      XSetStandardProperties(dpy, win, name, name,
                              None, (char **)NULL, 0, &sizehints);
   }

   ctx = glXCreateContext( dpy, visinfo, NULL, True );
   if (!ctx) {
      printf("Error: glXCreateContext failed\n");
      exit(1);
   }

   XFree(visinfo);

   *winRet = win;
   *ctxRet = ctx;
}

void Init(void)
{
    static float lmodel_ambient[] = {0.0, 0.0, 0.0, 0.0};
    static float lmodel_twoside[] = {GL_FALSE};
    static float lmodel_local[] = {GL_FALSE};
    static float light0_ambient[] = {0.8, 0.8, 0.8, 1.0};
    static float light0_diffuse[] = {0.8, 0.8, 0.9, 0.0};
    static float light0_position[] = {-0.8660254, 0.5, 2, 0};
    static float light0_specular[] = {0.4, 0.4, 0.4, 0.4};
    static float light1_ambient[] = {0.1, 0.1, 0.1, 1.0};
    static float light1_diffuse[] = {0.4, 0.2, 0.0, 0.0};
    static float light1_position[] = {0.8660254, -0.5, 2, 0};
    static float light1_specular[] = {1.0, 1.0, 1.0, 0.0};

    draw_yes=0;

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);


    glClearColor(0.0, 0.05, 0.2, 0.0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glEnable(GL_LIGHT1);

    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, lmodel_local);
    glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glEnable(GL_LIGHTING);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, bevel_mat_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, bevel_mat_shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, bevel_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bevel_mat_diffuse);
    
    glColorMaterial(GL_FRONT_AND_BACK, GL_SHININESS);
      
    //      glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);


}

static int
Handle_event_win1(Display *dpy, Window win, XEvent *event)
{
  (void) dpy;
  (void) win;
  static int button;
  switch (event->type) {
    // Redraw the window if it was exposed
  case Expose:
    return DRAW;
    break;
    // The size or position of the window was changed
  case ConfigureNotify:
    {
      Reshape(event->xconfigure.width, event->xconfigure.height);
      return DRAW;
    }
    break;
    // Reaction on the keyboard keys
  case KeyPress:
    {
      char buffer[10];
      int r, code;
      code = XLookupKeysym(&event->xkey, 0);
      if (code == XK_Left & numr2 >0 ) {
	numr2--;
      }
      else if (code == XK_Right & numr2 < numr ) {
        numr2++;
      }
      else if (code == XK_Up) {
	angsz += 2.;
      }
      else if (code == XK_Down) {
	angsz -= 2.;
      }
      else 
	{
	  r = XLookupString(&event->xkey, buffer, sizeof(buffer),
			    NULL, NULL);
	  if (buffer[0] == 27) {
	    /* escape */
	    return EXIT;
	  }
	  else if (buffer[0] == '1') 
	    {
	      show1 = 1 - show1;
	    }
	  else if (buffer[0] == '2') 
	    {
	      show2 = 1 - show2;
	    }
	  else if (buffer[0] == '3') 
	    {
	      show3 = 1 - show3;
	    }
	  else if (buffer[0] == '4') 
	    {
	      show4 = 1 - show4;
	    }
	  else if (buffer[0] == '+') 
	    {
	      if (sec_angle <= pi/2.-0.01 )  sec_angle = sec_angle + 0.01;
	    }
	  else if (buffer[0] == '=') 
	    {
	      if (sec_angle <= pi/2.-0.01 )  sec_angle = sec_angle + 0.01;
	    }
	 else if (buffer[0] == '-') 
	    {
	      if(  sec_angle>=0.01 )  sec_angle = sec_angle - 0.01;
	    }
	  /*
	 else if (buffer[0] == 'f' || buffer[0] == 'F' ) 
	   {
	     if( fullscreen)
	       fullscreen = GL_FALSE;
	     else
	       {
		 fullscreen = GL_TRUE;
		 win1x0 = 0; win1y0 = 0;
		 w1width = DisplayWidth( dpy, scrnum );
		 w1height = DisplayHeight( dpy, scrnum );
		 XChangeProperty( dpy, win1,                         // display, window 
				  prop, proptype,                 // property, type 
				  32,                             // format: 32-bit datums
				  PropModeReplace,                // mode 
				  (unsigned char *) &motif_hints, // data 
				  PROP_MOTIF_WM_HINTS_ELEMENTS    // nelements 
				  );
	       }
	     no_border(dpy, win1);
	     Reshape(event->xconfigure.width, event->xconfigure.height);
	   }
	  */
	}
      return DRAW;	 
    }
     break;
     // Reaction on the mouse button pressed
  case ButtonPress:
    {	
      GLfloat w;
      button = event->xbutton.button;
      win1_mx = event->xbutton.x; win1_my = event->xbutton.y;
      if(button == 1 )
	{
	  win1_ox=angsx;win1_oy=angsy;
	};
      if(button == 2 )
	{
	  win1_ox=win1_dx;win1_oy=win1_dy;
	};     
      if(button == 3)
	{
	  win1_ox=win1_dz;
	};
      if( button == 4 ) 
	{    
	  eyesep +=0.05;
	  w = fix_point * (1.0 / 5.0);
	  left1 = -5.0 * ((w - 0.5 * eyesep) / fix_point);
	  right1 = 5.0 * ((w + 0.5 * eyesep) / fix_point);
	}   
      if( button == 5 ) 
	{    
	  eyesep -=0.05;
	  w = fix_point * (1.0 / 5.0);
	  left1 = -5.0 * ((w - 0.5 * eyesep) / fix_point);
	  right1 = 5.0 * ((w + 0.5 * eyesep) / fix_point);
	}   
      return DRAW;
    }
    break;
    // What to do if mouse was moved
  case MotionNotify: 
    {
      int x,y;
      x = event->xmotion.x; y = event->xmotion.y;
      if( button == 1 ) 
	{angsx=win1_ox+x-win1_mx;angsy=win1_oy-y+win1_my;};      
      if( button == 2 ) 
	{
	  win1_dx=win1_ox+(x-win1_mx)/100.;
	  win1_dy=win1_oy-(y-win1_my)/100.;
	};
      if( button == 3 ) 
	{    
	  win1_dz=win1_ox-(x-win1_mx)/100.;
	}   
      return DRAW;
    }
    break;
  }
  return NOP;
}