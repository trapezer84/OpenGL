#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h> 

inline int round (const float a) { return int (a + 0.5); }
int a, b, c, d;

void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0); 

	glMatrixMode (GL_PROJECTION); 
	gluOrtho2D (0.0, 400.0, 0.0, 400.0);
}

void setPixel(int x, int y)
{
	glBegin (GL_POINTS);
		glVertex2i (x, y); 
		std::cout << x << " " << y << std::endl;
	glEnd ( );
	glFlush();
}


/* Bresenham line-drawing procedure for |m| < 1.0. */
void lineBres (int x0, int y0, int xEnd, int yEnd)
{
	int dx = fabs ((float)(xEnd - x0) ), dy = fabs( (float)(yEnd - y0));

	int p = 2 * dy - dx;
	int p2 = 2 * dx - dy;

	int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
	int twoDy2 = 2 * dx , twoDyMinusDx2 = 2 * (dx - dy);

	float m = (y0 - yEnd) / (x0 - xEnd);
	int x, y;

	/* Determine which endpoint to use as start position. */
	if (x0 > xEnd) {
		x = xEnd;
		y = yEnd;
		xEnd = x0;
		yEnd = y0;
	}
	else {
		x = x0;
		y = y0;
	}
	setPixel (x, y);

	if( -1 < m && m < 1) {
		while (x < xEnd) {
			x++;
			if (p < 0)
				p += twoDy;
			else {
				y++;
				p += twoDyMinusDx;
			}
			setPixel (x, y);
		}
	}
	else {
		while (y < yEnd) {
			y++;
			if (p2 < 0)
				p#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h> 

inline int round (const float a) { return int (a + 0.5); }

void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0); 

	glMatrixMode (GL_PROJECTION); 
	gluOrtho2D (0.0, 400.0, 0.0, 400.0);
}

void setPixel(int x, int y)
{
	glBegin (GL_POINTS);
		glVertex2i (x, y); 
		std::cout << x << " " << y << std::endl;
	glEnd ( );
	glFlush();
}


/* Bresenham line-drawing procedure for |m| < 1.0. */
void lineBres (int x0, int y0, int xEnd, int yEnd)
{
	int dx = fabs ((float)(xEnd - x0) ), dy = fabs( (float)(yEnd - y0));
	int p = 2 * dy - dx;
	int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
	int x, y;

	/* Determine which endpoint to use as start position. */
	if (x0 > xEnd) {
		x = xEnd;
		y = yEnd;
		xEnd = x0;
	}
	else {
		x = x0;
		y = y0;
	}
	setPixel (x, y);

	while (x < xEnd) {
		x++;
		if (p < 0)
			p += twoDy;
		else {
			y++;
			p += twoDyMinusDx;
		}
		setPixel (x, y);
	}
}


void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT); 
	glColor3f (1.0, 0.0, 0.0);

	
	lineBres(0, 0, 399, 299);

	glutSwapBuffers();
}

void main (int argc, char** argv)
{
	glutInit (&argc, argv); 
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize (400, 400); 
	glutCreateWindow ("Line Rasterizer"); 

	init ( ); 
	glutDisplayFunc (display); 
	glutMainLoop ( ); 
}
2 += twoDy2;
			else {
				x++;
				p2 += twoDyMinusDx2;
			}
			setPixel (x, y);
		}
	}
}


void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT); 
	glColor3f (1.0, 0.0, 0.0);

	
	//lineBres(0, 0, 399, 299);
	lineBres(a, b, c, d);

	glutSwapBuffers();
}

void main (int argc, char** argv)
{
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	c = atoi(argv[3]);
	d = atoi(argv[4]);

	glutInit (&argc, argv); 


	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize (400, 400); 
	glutCreateWindow ("Line Rasterizer"); 

	init ( ); 
	glutDisplayFunc (display); 
	glutMainLoop ( ); 
}
