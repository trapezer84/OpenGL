#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

// ROBOT ARM CONTROLS
float BaseTransX=-0.5f;  // 0
float BaseTransZ=0;      
float BaseSpin=0;        // 1
float ShoulderAng=-10;   // 2
float ElbowAng=-120;     
float WristAng=90;       // 3
float WristTwistAng=10;
float FingerAng1=45;     // 4
float FingerAng2=-90;

// ROBOT COLORS
GLubyte Arms[] = { 128,128,128 };
GLubyte Joints[] = { 0,68,119 };
GLubyte Fingers[] = { 150,0,24 };
GLubyte FingerJoints[] = { 128,128,128 };

// USER INTERFACE GLOBALS
int LeftButtonDown=0;    // MOUSE STUFF
int OldX,OldY,NewX,NewY;
int RobotControl=1;

void DrawUnitCylinder(int NumSegs)  // x,y,z in [0,1], Y-axis is up
{
  int i;
  float *Px = new float[NumSegs];
  float *Py = new float[NumSegs];
  float AngIncr = (2.0f*3.1415927f) / (float)NumSegs;
  float Ang = AngIncr;
  Px[0]=1;
  Py[0]=0;
  for (i=1; i<NumSegs; i++, Ang+=AngIncr)
  {
    Px[i]=(float)cos(Ang);
    Py[i]=(float)sin(Ang);
  }

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
    glTranslatef(0.5f,0.5f,0.5f);
    glScalef(0.5f,0.5f,0.5f);

    // TOP
    glNormal3f(0,1,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,1,0);
    for (i=0; i<NumSegs; i++)
      glVertex3f(Px[i],1,-Py[i]);
    glVertex3f(Px[0],1,-Py[0]);
    glEnd();

    // BOTTOM
    glNormal3f(0,-1,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,-1,0);
    for (i=0; i<NumSegs; i++)
      glVertex3f(Px[i],-1,Py[i]);
    glVertex3f(Px[0],-1,Py[0]);
    glEnd();

    // SIDES
    glBegin(GL_QUAD_STRIP);
    for (i=0; i<NumSegs; i++)
    {
      glNormal3f(Px[i],0,-Py[i]);
      glVertex3f(Px[i],1,-Py[i]);
      glVertex3f(Px[i],-1,-Py[i]);
    }
    glNormal3f(Px[0],0,-Py[0]);
    glVertex3f(Px[0],1,-Py[0]);
    glVertex3f(Px[0],-1,-Py[0]);
    glEnd();

  glPopMatrix();

  delete[] Px;
  delete[] Py;
}

void DrawUnitSphere(int NumSegs)  // x,y,z in [0,1]
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
    glTranslatef(0.5f,0.5f,0.5f);
    glutSolidSphere(0.5f,NumSegs,NumSegs);
  glPopMatrix();
}

void DrawUnitCone(int NumSegs)  // x,y,z in [0,1], apex is in +Y direction
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
    glTranslatef(0.5f,0,0.5f);
    glRotatef(-90, 1,0,0);
    glutSolidCone(0.5f,1,NumSegs,NumSegs);
  glPopMatrix();
}

void DrawGroundPlane(int NumSegs)
{
  glColor3f(0.7f,0.7f,0.7f);
  glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glVertex3f(-1,0,1);
    glVertex3f(1,0,1);
    glVertex3f(1,0,-1);
    glVertex3f(-1,0,-1);
  glEnd();
}

void DrawJoint(int NumSegs)
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
    glScalef(0.15f,0.15f,0.12f);
    glRotatef(90,1,0,0);
    glTranslatef(-0.5f,-0.5f,-0.5f);
      glColor3ubv(Joints);
      DrawUnitCylinder(NumSegs);
  glPopMatrix();
}

void DrawBase(int NumSegs)
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
    glScalef(0.2f,0.025f,0.2f);
    glTranslatef(-0.5f,0,-0.5f);
      glColor3ubv(Joints);
      DrawUnitCylinder(NumSegs);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-0.05f,0,-0.05f);
    glScalef(0.1f,0.4f,0.1f);
      glColor3ubv(Arms);
      DrawUnitCylinder(NumSegs);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0,0.4f,0);
    DrawJoint(NumSegs);
  glPopMatrix();
}

void DrawArmSegment(int NumSegs)
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
    glTranslatef(-0.05f,0,-0.05f);
    glScalef(0.1f,0.5f,0.1f);
      glColor3ubv(Arms);
      DrawUnitCylinder(NumSegs);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0,0.5f,0);
    DrawJoint(NumSegs);
  glPopMatrix();
}

void DrawWrist(int NumSegs)
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
    glTranslatef(-0.04f,0,-0.04f);
    glScalef(0.08f,0.2f,0.08f);
      glColor3ubv(Fingers);
      DrawUnitCylinder(NumSegs);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0,0.2f,0);
    glScalef(0.12f,0.12f,0.12f);
    glTranslatef(-0.5f,-0.5f,-0.5f);
      glColor3ubv(FingerJoints);
      DrawUnitSphere(NumSegs);
  glPopMatrix();
}

void DrawFingerBase(int NumSegs)
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
    glTranslatef(-0.025f,0,-0.025f);
    glScalef(0.05f,0.3f,0.05f);
      glColor3ubv(Fingers);
      DrawUnitCylinder(NumSegs);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0,0.3f,0);
    glScalef(0.08f,0.08f,0.08f);
    glTranslatef(-0.5f,-0.5f,-0.5f);
      glColor3ubv(FingerJoints);
      DrawUnitSphere(NumSegs);
  glPopMatrix();
}

void DrawFingerTip(int NumSegs)
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
    glScalef(0.05f,0.25f,0.05f);
    glTranslatef(-0.5f,0,-0.5f);
      glColor3ubv(Fingers);
      DrawUnitCone(NumSegs);
  glPopMatrix();
}

void DrawRobotArm(int NumSegs)
{
  glMatrixMode(GL_MODELVIEW);
  // ADD YOUR DISPLAY ROUTINE HERE
  /*1번: 전체 움직이기*/
  glTranslatef(BaseTransX, 0 , BaseTransZ); //초기 위치 정해주기 여기서 이제 올라감 
  glRotatef(BaseSpin, 0, 0.4f , 0); //제일 처음것만 움직여 주면 다 바뀌니까 ^^ 그냥 rotate시켜줌 
  DrawBase(50); //밑에 기본적인 것 그려주기 
  /*2번: 전체 돌아가기*/
  glTranslatef(0,0.4f,0); //위치만 정해주고   
  glRotatef(ShoulderAng,0,0,1.0f);
  DrawArmSegment(50); 
  /*3번 구부려지기*/
  glTranslatef(0,0.5f,0);
  glRotatef(ElbowAng,0,0,1.0f);
  DrawArmSegment(50);
  /*4번 빨간색 돌아가기*/
  //팔기둥
  glTranslatef(0,0.5f,0);
  glRotatef(WristAng,0,0,1.0f);
  DrawWrist(300); //빨간색 기본바탕 

  glRotatef(WristTwistAng,0,1.0f,0);
  //첫번째 빨간 팔
  glPushMatrix();
  glTranslatef(0,0.2f,0);
  glRotatef(FingerAng1,1.0f,0,0);
  DrawFingerBase(300);
  //
  glTranslatef(0,0.3f,0);
  glRotatef(FingerAng2,1.0f,0,0);
  DrawFingerTip(300);//여기서 빨간 집게 만들기
  glPopMatrix();

  //두번째 빨간 팔 
  glPushMatrix();
  glTranslatef(0,0.2f,0);
  glRotatef(-FingerAng1,1.0f,0,0);
  DrawFingerBase(300);

  glTranslatef(0,0.3f,0);
  glRotatef(-FingerAng2,1.0f,0,0);
  DrawFingerTip(300);//여기서 빨간 집게 만들기
  glPopMatrix();



  //glutPostRedisplay();
}

void myDisplay()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,2,4, 0,0.5f,0, 0,1,0);

  DrawGroundPlane(16);
  DrawRobotArm(16);

  glutSwapBuffers();
}

void myReshape(int w, int h)
{
  glViewport(0,0,w,h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30,(float)w/h,0.1,10);
}

void myIdle()
{
  glutPostRedisplay();
}

void KeyboardFunc(unsigned char Key, int x, int y)
{
	//여기서 if로 Robotcontrol 받기때문에 괜찮음
  if (Key>='1' && Key<='5') RobotControl=Key-'1';
  if (Key==27) exit(0);         // ESC
  
}

void MouseFunc(int button, int state, int x, int y)
{
  NewX=x; NewY=y;
  if (button==GLUT_LEFT_BUTTON)
    LeftButtonDown=!LeftButtonDown;
}

void MotionFunc(int x, int y)
{
  OldX=NewX; OldY=NewY;
  NewX=x;    NewY=y;
  float RelX = (NewX-OldX) / (float)glutGet((GLenum)GLUT_WINDOW_WIDTH);
  float RelY = (NewY-OldY) / (float)glutGet((GLenum)GLUT_WINDOW_HEIGHT);
  if (LeftButtonDown) 
    switch(RobotControl)
    {
      case 0: BaseTransX+=RelX; BaseTransZ+=RelY; break;
      case 1: BaseSpin+=RelX*180; break;
      case 2: ShoulderAng+=RelY*-90; ElbowAng+=RelX*90; break;
      case 3: WristAng+=RelY*-180; WristTwistAng+=RelX*180; break;
      case 4: FingerAng1+=RelY*90; FingerAng2+=RelX*180; break;
    };
  glutPostRedisplay();
}


void main(void)
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(512,512);
  glutInitWindowPosition(180,100);
  glutCreateWindow("The Robot Arm");

  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_CULL_FACE);

  glutDisplayFunc(myDisplay);
  glutReshapeFunc(myReshape);
  glutIdleFunc(myIdle);

  glutKeyboardFunc(KeyboardFunc);
  glutMouseFunc(MouseFunc);
  glutMotionFunc(MotionFunc);

  glutMainLoop();
}
