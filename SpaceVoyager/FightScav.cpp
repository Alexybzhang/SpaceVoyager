

#include "FightScav.h"
#include "MasterHeader.h"
#include "Render.h"





GLfloat fogColor_fs[] = {0.8,0.8,0.8,0.1};
GLfloat fogDensity_fs = 0.000001f;


void fightScav::initScene()
{
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);


  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (GLfloat)w*1 / (GLfloat)h, 1.0,FAR_SIGHT);
  glMatrixMode(GL_MODELVIEW);
  



   
  GLfloat black[] =     { 0.0, 0.0, 0.0, 1.0};
  GLfloat dark[] =      { 0.2, 0.15, 0.2, 1.0};
  GLfloat white[] =     { 0.7 , 0.7, 0.7, 1.0};
  GLfloat direction[] = { 0.2, 0.0, 10.5,0.0};

  glMaterialfv(GL_FRONT, GL_SPECULAR, white);
  glMaterialf(GL_FRONT, GL_SHININESS, 30);
  glLightfv(GL_LIGHT0, GL_AMBIENT , white);
  glLightfv(GL_LIGHT0, GL_DIFFUSE , white);
  glLightfv(GL_LIGHT0, GL_SPECULAR , white);
  glLightfv(GL_LIGHT0, GL_POSITION , direction);


  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);

  //fog
  glEnable(GL_FOG);
  glFogi(GL_FOG_MODE,GL_EXP2);
  glFogfv(GL_FOG_COLOR,fogColor_fs);
  glFogf(GL_FOG_DENSITY,fogDensity_fs);
  glFogf(GL_FOG_START,900000.0f);
  glHint(GL_FOG_HINT,GL_NICEST);


  _ship->init_ship();

  ifInit = true;
  
 }

fightScav::fightScav()
{
	           _ship = new Ship(Point(0,0,2000000));
	           
			   collisionManager = new CollisionManager();
		
			   ifInit = false;
}

fightScav::~fightScav()
{
	
}


void fightScav::display_fn_game()
{

    if(!ifInit)
    {
        initScene();
    }
     

	_ship->shipDraw();

}

void fightScav::idle_fn_game()
{
	timer_fn_game(0);
}

void fightScav::keyboard_fn_game(unsigned char& key,int& x, int& y)
{
    const double deltaSpeed = 10 ;
    const double angle      = 0.01;
    char  speed_str[5];
    switch(key)
    {
          case 'w': _ship->setSpeed(_ship->getSpeed() + deltaSpeed);  break;
          case 's': _ship->setSpeed(_ship->getSpeed() - deltaSpeed);  break;
          case 'a': _ship->roll(angle);                              break;
          case 'd': _ship->roll(-angle);                             break;
          case 'm': _ship->slide(1);                                 break;
          case 'n': _ship->slide(-1);                                break;
          case 'r': _ship->teleport(Point(0,0,50000));               break;
		  case 27:  exit(0);  delete[] IEntityManager::getInstance();                                     break;      
		  case 'f': _ship->msys->createMissileAt(_ship->getPositon(),_ship->getForward() ,_ship->getSpeed());break;
		  case 'u':  break;
         default:                                                   break;


    }

     glutPostRedisplay();
}


void fightScav::special_fn_game(int& key , int& x, int& y)
{ 
    float fraction = 0.01f;
    double angle   = 0.01;
     switch(key){

    case GLUT_KEY_LEFT :
    {
      _ship->yaw(angle);
      break;
    }
    case GLUT_KEY_RIGHT :
    {
      _ship->yaw(-angle);
      break;
    }
    case GLUT_KEY_UP :
    {
      _ship->pitch(angle);
      break;
    }
    case GLUT_KEY_DOWN :
    {
      _ship->pitch(-angle);
      break;
    }
    default: break;
    
    }


    glutPostRedisplay();
}

void fightScav::timer_fn_game(int t)
{
      

	   _ship->shipUpdate();

	   collisionManager->runCollisionEngine();

       Point eye(_ship->getPositon());
       Point at(_ship->getPositon() + _ship->getDirection());
       Vector up(_ship->getVertical());

	
	 




      glLoadIdentity();
      gluLookAt(eye.x,eye.y,eye.z,
                at.x,at.y,at.z,
                up.i,up.j,up.k);
    
      glutPostRedisplay();
}



