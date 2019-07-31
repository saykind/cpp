#define standard 0
#define cross_line 1
#define coord_line 2
#define border_line 3
#define surface    4
#define surface_int 5

static float bevel_mat_ambient[] = {0.0, 0.0, 0.0, 1.0};
static float bevel_mat_emission[] = {0.0,0.0,0.0,0.0};
static float bevel_mat_shininess[] = {30.0};
static float bevel_mat_specular[] = {0.1, 0.1, 0.1, 0.0};
static float bevel_mat_diffuse[] = {1.0, 0.0, 0.0, 0.0};

static float cross_line_mat_ambient[] = {0.0, 0.0, 0.0, 1.0};
static float cross_line_mat_emission[] = {1.0,1.0,1.0,1.0};
static float cross_line_mat_shininess[] = {10.0};
static float cross_line_mat_specular[] = {0.0, 0.0, 0.0, 1.0};
static float cross_line_mat_diffuse[] = {0.0, 0.0, 0.0, 1.0};

static float coord_line_mat_ambient[] = {0.0, 0.0, 0.0, 1.0};
static float coord_line_mat_emission[] = {0.7, 0.3, 0.1, 1.0};
static float coord_line_mat_shininess[] = {10.0};
static float coord_line_mat_specular[] = {0.0,0.0,0.0,1.0};
static float coord_line_mat_diffuse[] = {0.0, 0.0, 0.0, 1.0};

static float border_line_mat_ambient[] = {0.0, 0.0, 0.0, 1.0};
static float border_line_mat_emission[] = {0.2, 0.6, 0.8, 1.0};
static float border_line_mat_shininess[] = {10.0};
static float border_line_mat_specular[] = {0.0,0.0,0.0,1.0};
static float border_line_mat_diffuse[] = {0.0, 0.0, 0.0, 1.0};

static float surface_mat_ambient[] = {0.0, 0.0, 0.0, 0.0};
static float surface_mat_emission[] = {0.0,0.1,0.0,1.0};
static float surface_mat_shininess[] = {10.0};
static float surface_mat_specular[] = {0.0, 0.0, 0.0, 0.0};
static float surface_mat_diffuse[] = {0.7, 0.6, 0.4, 1.0};

static float surface_int_mat_ambient[] = {0.0, 0.0, 0.0, 0.0};
static float surface_int_mat_emission[] = {0.2,0.05,0.0,1.0};
static float surface_int_mat_shininess[] = {10.0};
static float surface_int_mat_specular[] = {0.0, 0.0, 0.0, 0.0};
static float surface_int_mat_diffuse[] = {0.7, 0.3, 0.1, 1.0};




void MatColorSet( int object)
{

  switch (object) {
  case standard:
    glMaterialfv(GL_FRONT, GL_AMBIENT, bevel_mat_ambient);
    glMaterialfv(GL_FRONT, GL_EMISSION, bevel_mat_emission);
    glMaterialfv(GL_FRONT, GL_SHININESS, bevel_mat_shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, bevel_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bevel_mat_diffuse);
    break;
  case cross_line:
    glMaterialfv(GL_FRONT, GL_AMBIENT, cross_line_mat_ambient);
    glMaterialfv(GL_FRONT, GL_EMISSION, cross_line_mat_emission);
    glMaterialfv(GL_FRONT, GL_SHININESS, cross_line_mat_shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cross_line_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cross_line_mat_diffuse);
    break;
  case coord_line:
    glMaterialfv(GL_FRONT, GL_AMBIENT, coord_line_mat_ambient);
    glMaterialfv(GL_FRONT, GL_EMISSION, coord_line_mat_emission);
    glMaterialfv(GL_FRONT, GL_SHININESS, coord_line_mat_shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, coord_line_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, coord_line_mat_diffuse);
    break;

  case border_line:
    glMaterialfv(GL_FRONT, GL_AMBIENT, border_line_mat_ambient);
    glMaterialfv(GL_FRONT, GL_EMISSION, border_line_mat_emission);
    glMaterialfv(GL_FRONT, GL_SHININESS, border_line_mat_shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, border_line_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, border_line_mat_diffuse);
    break;

  case surface:
    glMaterialfv(GL_FRONT, GL_AMBIENT, surface_mat_ambient);
    glMaterialfv(GL_FRONT, GL_EMISSION, surface_mat_emission);
    glMaterialfv(GL_FRONT, GL_SHININESS, surface_mat_shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, surface_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, surface_mat_diffuse);
    break;

 case surface_int:
    glMaterialfv(GL_FRONT, GL_AMBIENT, surface_int_mat_ambient);
    glMaterialfv(GL_FRONT, GL_EMISSION, surface_int_mat_emission);
    glMaterialfv(GL_FRONT, GL_SHININESS, surface_int_mat_shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, surface_int_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, surface_int_mat_diffuse);
    break;


  default:
    glMaterialfv(GL_FRONT, GL_AMBIENT, bevel_mat_ambient);
    glMaterialfv(GL_FRONT, GL_EMISSION, bevel_mat_emission);
    glMaterialfv(GL_FRONT, GL_SHININESS, bevel_mat_shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, bevel_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bevel_mat_diffuse);
    return;
  }

}