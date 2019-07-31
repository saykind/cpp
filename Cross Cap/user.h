/* Variables for the numeric part */
int numr=64, numr2=64, numphi=64;   
double s1,s2,s3;
double psi1,psi3=0.;

/* The surface parameters */
double l1,l2,l3=2.;
double zmax=1.0,z_lim=10.;
double x_sec=-1.,z_sec=2.,sec_angle;

void SetInitialParams(void)
{
 show1 = 1; show2 = 1; show3 = 1; show4 = 0;
}

void DrawSphere(int numr, int numphi, double cx, double cy, double cz, double R)
{
  int i,j;
  double s1,s2,c1,c2,x1,y1,z1,x2,y2,z2,n1,n2,n3,nl,phi1;

	for (j = 0; j < numr; j++)
	  { 
	    s1 = twopi*(double)j/(double)numr/2.; 
	    s2 = twopi*((double)j+1.)/(double)numr/2.; 
	    c1 = cos (s1 ); s1 = sin (s1 );
	    c2 = cos (s2 ); s2 = sin (s2 );
	   
	    glBegin(GL_QUAD_STRIP);
	    for (i = 0; i <= numphi; i++)
	      {
		phi1 = ( twopi / numphi ) * i;
		x1 = R * sin(-phi1) * s1; y1 = R * cos(-phi1) * s1; 
		z1 = R * c1;
		x2 = R * sin(-phi1) * s2; y2 = R * cos(-phi1) * s2; 
		z2 = R * c2;

		n1 = x1; n2 = y1; n3 = z1;
		nl = sqrt ( n1*n1 + n2*n2 + n3*n3);
		n1 = n1/nl; n2 = n2/nl; n3 = n3/nl;
		glNormal3f(n1, n2, n3);
		x1 = x1 + cx;
		y1 = y1 + cy;
		z1 = z1 + cz;
		glVertex3f(x1, y1, z1);

		n1 = x2; n2 = y2; n3 = z2;
		nl = sqrt ( n1*n1 + n2*n2 + n3*n3);
		n1 = n1/nl; n2 = n2/nl; n3 = n3/nl;
		glNormal3f(n1, n2, n3);
		x2 = x2 + cx;
		y2 = y2 + cy;
		z2 = z2 + cz;
		glVertex3f(x2, y2, z2);	    
	      }
	    glEnd();
	  }
}

void DrawLine(int width, double x1, double y1, double z1, double x2, double y2, double z2)
{
	    glLineWidth(width);
	    glBegin( GL_LINE_STRIP ); 
	    glVertex3f(x1, y1, z1);
	    glVertex3f(x2, y2, z2);
	    glEnd();
}



void DrawObject(void)
{
  int i11, i12;
  double r0,aoval,boval,phi1,phi2,psi1,psi2,s1,c1,s2,c2,s12,c12,s22,c22;
  double e11,e12,e13,e21,e22,e23;

  double f,f1,f14,sf,cf,sf4,cf4;
  double x1, y1, z1, x2, y2, z2, x3, y3, z3;
  double n1, n2, n3 ,nl, nn1,nn2,nn3;

    // We draw the coordinate lines
  
  MatColorSet( coord_line); 
  for (i11 =0; i11 < numphi; i11++)
    {
      phi1=twopi*double(i11)/double(numphi);
      aoval = (1.25 + 0.25 * cos (2. * phi1));
      boval = aoval * aoval;
      psi2 = 0.;
      x2 = aoval * cos(phi1) * sin(psi2);
      y2 = aoval * sin(phi1) * sin(psi2);
      z2 = boval * (cos(psi2) + 1.) - 2.;

      for (i12 = 0; i12 < numr2; i12++)
	{
	  psi1 = psi2;
	  psi2= pi*double(i12+1)/double(numr);
	  x1 = x2; y1 = y2; z1 = z2;
	  x2 = aoval * cos(phi1) * sin(psi2);
	  y2 = aoval * sin(phi1) * sin(psi2);
	  z2 = boval * (cos(psi2) + 1.) - 2.;
	  DrawLine( 2, x1, y1, z1, x2, y2, z2);
	}
    }

  /*

  MatColorSet( border_line);
  phi2 = 0.;
  for (i11 =0; i11 < numphi; i11++)
    {
      phi1=phi2;
      phi2=twopi*double(i11+1)/double(numphi);
      x1 = cos(phi1);
      y1 = sin(phi1);
      z1 = cos(2*phi1);
      x2 = cos(phi2);
      y2 = sin(phi2);
      z2 = cos(2*phi2);
      DrawLine( 3, x1, y1, z1, x2, y2, z2); 
    }

  if(show2)
    {
        phi2 = 0.;
	for (i11 =0; i11 < numphi; i11++)
	  {
	    phi1=phi2;
	    phi2=twopi*double(i11+1)/double(numphi);
	    x1 = 2. * cos(phi1);
	    y1 = 2. * sin(phi1);
	    z1 = -2.;
	    x2 = 2. * cos(phi2);
	    y2 = 2. * sin(phi2);
	    z2 = -2.;
	    DrawLine( 3, x1, y1, z1, x2, y2, z2); 
	  }
    }
  */
  
  phi2=0;
  c2 = 1.; s2 = 0.;
  c22 = 1.; s22 = 0.;
  for (i11 =0; i11 < numphi; i11++)
    {
      phi1=phi2;
      phi2=twopi*double(i11+1)/double(numphi);
      c1 = c2; s1 = s2; c12 = c22; s12 = s22;
      c2 = cos(phi2); s2 = sin(phi2);
      c22 = c2 * c2 - s2 * s2;
      s22 = 2. * s2 *c2;
      // We draw the central part of the cross-cap
      MatColorSet( surface );
      glBegin(GL_QUAD_STRIP);      
      for (i12 =0; i12 <= numr2; i12++)
	{
	  psi1 = pi*double(i12)/double(numr);
	  aoval = (1.25 + 0.25 * cos (2. * phi2));
	  boval = aoval * aoval;
	  x2 = aoval * cos(phi2) * sin(psi1);
	  y2 = aoval * sin(phi2) * sin(psi1);
	  z2 = boval * (cos(psi1) + 1.) - 2.;
	  e11 = aoval * cos(phi2) * cos(psi1);  ; 
	  e12 = aoval * sin(phi2) * cos(psi1);
	  e13 = -boval * sin(psi1);
	  e21 = (-0.5 * sin(2. * phi2) * cos(phi2)- aoval * sin(phi2)) * 
	    sin(psi1);
	  e22 = (-0.5 * sin(2. * phi2) * sin(phi2)+ aoval * cos(phi2)) * 
	    sin(psi1);
	  e23 = -aoval *  sin(2. * phi2) * (cos(psi1) + 1.);
	    n1 = e12 * e23 - e13 * e22;
	  n2 = e13 * e21 - e11 * e23;
	  n3 = e11 * e22 - e12 * e21;
	  nl = sqrt ( n1*n1 + n2*n2 + n3*n3);
	  n1 = n1/nl; n2 = n2/nl; n3 = n3/nl;
	  glNormal3f(n1, n2, n3);
	  glVertex3f(x2, y2, z2);	  

	  aoval = (1.25 + 0.25 * cos (2. * phi1));
	  boval = aoval * aoval;
	  x2 = aoval * cos(phi1) * sin(psi1);
	  y2 = aoval * sin(phi1) * sin(psi1);
	  z2 = boval * (cos(psi1) + 1.) - 2.;
	  e11 = aoval * cos(phi1) * cos(psi1);  ; 
	  e12 = aoval * sin(phi1) * cos(psi1);
	  e13 = -boval * sin(psi1);
	  e21 = (-0.5 * sin(2. * phi1) * cos(phi1)- aoval * sin(phi1)) * 
	    sin(psi1);
	  e22 = (-0.5 * sin(2. * phi1) * sin(phi1)+ aoval * cos(phi1)) * 
	    sin(psi1);
	  e23 = -aoval *  sin(2. * phi1) * (cos(psi1) + 1.);
	    n1 = e12 * e23 - e13 * e22;
	  n2 = e13 * e21 - e11 * e23;
	  n3 = e11 * e22 - e12 * e21;
	  nl = sqrt ( n1*n1 + n2*n2 + n3*n3);
	  n1 = n1/nl; n2 = n2/nl; n3 = n3/nl;
	  glNormal3f(n1, n2, n3);
	  glVertex3f(x2, y2, z2);	  
	 
	}
      glEnd();

      MatColorSet( surface_int );
      glBegin(GL_QUAD_STRIP);      
      for (i12 =0; i12 <= numr2; i12++)
	{
	  psi1 = pi*double(i12)/double(numr);
	  aoval = (1.25 + 0.25 * cos (2. * phi1));
	  boval = aoval * aoval;
	  x2 = aoval * cos(phi1) * sin(psi1);
	  y2 = aoval * sin(phi1) * sin(psi1);
	  z2 = boval * (cos(psi1) + 1.) - 2.;
	  e11 = aoval * cos(phi1) * cos(psi1);  ; 
	  e12 = aoval * sin(phi1) * cos(psi1);
	  e13 = -boval * sin(psi1);
	  e21 = (-0.5 * sin(2. * phi1) * cos(phi1)- aoval * sin(phi1)) * 
	    sin(psi1);
	  e22 = (-0.5 * sin(2. * phi1) * sin(phi1)+ aoval * cos(phi1)) * 
	    sin(psi1);
	  e23 = -aoval *  sin(2. * phi1) * (cos(psi1) + 1.);
	    n1 = e12 * e23 - e13 * e22;
	  n2 = e13 * e21 - e11 * e23;
	  n3 = e11 * e22 - e12 * e21;
	  nl = -sqrt ( n1*n1 + n2*n2 + n3*n3);
	  n1 = n1/nl; n2 = n2/nl; n3 = n3/nl;
	  glNormal3f(n1, n2, n3);
	  glVertex3f(x2, y2, z2);	  

	  aoval = (1.25 + 0.25 * cos (2. * phi2));
	  boval = aoval * aoval;
	  x2 = aoval * cos(phi2) * sin(psi1);
	  y2 = aoval * sin(phi2) * sin(psi1);
	  z2 = boval * (cos(psi1) + 1.) - 2.;
	  e11 = aoval * cos(phi2) * cos(psi1);  ; 
	  e12 = aoval * sin(phi2) * cos(psi1);
	  e13 = -boval * sin(psi1);
	  e21 = (-0.5 * sin(2. * phi2) * cos(phi2)- aoval * sin(phi2)) * 
	    sin(psi1);
	  e22 = (-0.5 * sin(2. * phi2) * sin(phi2)+ aoval * cos(phi2)) * 
	    sin(psi1);
	  e23 = -aoval *  sin(2. * phi2) * (cos(psi1) + 1.);
	    n1 = e12 * e23 - e13 * e22;
	  n2 = e13 * e21 - e11 * e23;
	  n3 = e11 * e22 - e12 * e21;
	  nl = -sqrt ( n1*n1 + n2*n2 + n3*n3);
	  n1 = n1/nl; n2 = n2/nl; n3 = n3/nl;
	  glNormal3f(n1, n2, n3);
	  glVertex3f(x2, y2, z2);	  

	  
	 
	}
      glEnd();

    }
     
  MatColorSet( cross_line);
  DrawLine( 4, 0.0025, 0, 0, 0.0025, 0, 2.5);
  DrawLine( 4, -0.0025, 0, 0, -0.0025, 0, 2.5);
  DrawLine( 4, 0., 0.0025,  0, 0., 0.0025, 2.5);
  DrawLine( 4, 0., -0.0025,  0, 0., -0.0025, 2.5);



}