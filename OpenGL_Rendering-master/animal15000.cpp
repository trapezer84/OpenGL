#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#define MAX 100000
FILE * file;

int vertcount;	//total number of vertices
int tricount;
int i, j, v; 
char str[10];

struct Vertex			// Vertex Structure
{
	float x,y,z;
};
struct Triangle			// Triangle Structure
{
	int vert1, vert2, vert3;
};
struct Vector
{
	float x, y, z;
};
struct Normal 
{
	float x, y, z;		//Normal Vector 
};

struct Vertex myVertex[MAX];			// Instantiation of Vertex defined as struct with 3 floats to store coordinates
struct Triangle myTriangle[MAX];		// Instantiation of the Triangle STRUCT
struct Vector myVector[5];
struct Normal myNormal[MAX];

void init(void)
{
   GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
   GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat position[] = {0.0, 3.0, 3.0, 0.0};

   GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
   GLfloat local_view[] = {0.0};

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   glLightfv(GL_LIGHT0, GL_POSITION, position);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

   glFrontFace(GL_CW);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_AUTO_NORMAL);
   glEnable(GL_NORMALIZE);
   glEnable(GL_DEPTH_TEST); 
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(8,0,0);
	glRotatef(100,170,0,0);
	glScalef(7,7,7);

	glBegin(GL_TRIANGLES);
	for(v=0; v<tricount; v++){
		glNormal3f(myNormal[myTriangle[v].vert1].x, myNormal[myTriangle[v].vert1].y, myNormal[myTriangle[v].vert1].z );
		glVertex3f(myVertex[myTriangle[v].vert1].x, myVertex[myTriangle[v].vert1].y, myVertex[myTriangle[v].vert1].z );
		
		glNormal3f(myNormal[myTriangle[v].vert2].x, myNormal[myTriangle[v].vert2].y, myNormal[myTriangle[v].vert2].z );
		glVertex3f(myVertex[myTriangle[v].vert2].x, myVertex[myTriangle[v].vert2].y, myVertex[myTriangle[v].vert2].z );
	
		glNormal3d(myNormal[myTriangle[v].vert3].x, myNormal[myTriangle[v].vert3].y, myNormal[myTriangle[v].vert3].z );
		glVertex3f(myVertex[myTriangle[v].vert3].x, myVertex[myTriangle[v].vert3].y, myVertex[myTriangle[v].vert3].z );
	}
	glEnd();

	glPopMatrix();
	glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(0.0, 16.0, 0.0, 16.0*(GLfloat)h/(GLfloat)w,
              -10.0, 10.0);
   else
      glOrtho(0.0, 16.0*(GLfloat)w/(GLfloat)h, 0.0, 16.0,
              -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
}


/*
 * Main Loop 
 */
int main(int argc, char **argv)
{
	file = fopen ("animal15000.tri","r");				// Tries to access the file specified. TO BE CHANGED ----> Dialaog window with browse for file function
	fscanf(file, "%s", str);		//TRI 읽어 들임
	fscanf(file, "%d", &vertcount);		//vertext 총 갯수 
	fscanf(file, "%d", &tricount);		//triangle 총 갯수 
	
	for (v=0; v<vertcount; v++)
	{
		fscanf(file, "%f %f %f",&myVertex[v].x, &myVertex[v].y, &myVertex[v].z);
	}
	for (v=0; v<tricount; v++)
	{
		fscanf(file, "%d %d %d",&myTriangle[v].vert1, &myTriangle[v].vert2, &myTriangle[v].vert3);
	}
	
	//normal vector 계산
	for(v=0; v<tricount; v++){
		//두 벡터를 만든다. 
		myVector[0].x = myVertex[myTriangle[v].vert2].x - myVertex[myTriangle[v].vert1].x;
		myVector[0].y = myVertex[myTriangle[v].vert2].y - myVertex[myTriangle[v].vert1].y;
		myVector[0].z = myVertex[myTriangle[v].vert2].z - myVertex[myTriangle[v].vert1].z;
		
		myVector[1].x = myVertex[myTriangle[v].vert3].x - myVertex[myTriangle[v].vert1].x;
		myVector[1].y = myVertex[myTriangle[v].vert3].y - myVertex[myTriangle[v].vert1].y;
		myVector[1].z = myVertex[myTriangle[v].vert3].z - myVertex[myTriangle[v].vert1].z;

		//두 벡터의 외적을 구해 Normal Vector을 만든다. 
		myNormal[myTriangle[v].vert1].x += (myVector[0].y * myVector[1].z - myVector[0].z * myVector[1].y) ;
		myNormal[myTriangle[v].vert1].y += (myVector[0].z * myVector[1].x - myVector[0].x * myVector[1].z) ;
		myNormal[myTriangle[v].vert1].z += (myVector[0].x * myVector[1].y - myVector[0].y * myVector[1].x) ;

		myNormal[myTriangle[v].vert2].x += (myVector[0].y * myVector[1].z - myVector[0].z * myVector[1].y) ;
		myNormal[myTriangle[v].vert2].y += (myVector[0].z * myVector[1].x - myVector[0].x * myVector[1].z) ;
		myNormal[myTriangle[v].vert2].z += (myVector[0].x * myVector[1].y - myVector[0].y * myVector[1].x) ;

		myNormal[myTriangle[v].vert3].x += (myVector[0].y * myVector[1].z - myVector[0].z * myVector[1].y) ;
		myNormal[myTriangle[v].vert3].y += (myVector[0].z * myVector[1].x - myVector[0].x * myVector[1].z) ;
		myNormal[myTriangle[v].vert3].z += (myVector[0].x * myVector[1].y - myVector[0].y * myVector[1].x) ;
	}

	//최종 적으로 저장된 Normal Vector 중에서 구한다. 
	for(i=0; i<vertcount; i++){
		myNormal[i].x = myNormal[i].x / ( sqrt(myNormal[i].x*myNormal[i].x + myNormal[i].y*myNormal[i].y + myNormal[i].z*myNormal[i].z) );
		myNormal[i].y = myNormal[i].y / ( sqrt(myNormal[i].x*myNormal[i].x + myNormal[i].y*myNormal[i].y + myNormal[i].z*myNormal[i].z) );
		myNormal[i].z = myNormal[i].z / ( sqrt(myNormal[i].x*myNormal[i].x + myNormal[i].y*myNormal[i].y + myNormal[i].z*myNormal[i].z) );

//		printf("%f %f %f \n", myNormal[i].x, myNormal[i].y, myNormal[i].z);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 600);
	glutInitWindowPosition(50,50);
	glutCreateWindow(argv[0]);
	init();
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	
	glutMainLoop();
	fclose(file);
   
	return 0;
}
