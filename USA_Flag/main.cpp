#include <windows.h>
#ifdef __APPLE__
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <cmath>

void DrawStar(float fX, float fY) {
	const float kfPi = 3.1415926535897932384626433832795;
	const float kfRadius = 0.0616/2.0;
	const float kfInnerRadius = kfRadius*(1.0/(sin((2.0*kfPi)/5.0)*2.0*cos(kfPi/10.0) + sin((3.0*kfPi)/10.0)));
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(fX, fY, 0.0);
		for (int iVertIndex = 0; iVertIndex < 10; ++iVertIndex) {
			float fAngleStart	= kfPi/2.0 + (iVertIndex*2.0*kfPi)/10.0;
			float fAngleEnd		= fAngleStart + kfPi/5.0;
			if (iVertIndex % 2 == 0) {
				glVertex3f(fX + kfRadius*cos(fAngleStart)/1.9, fY + kfRadius*sin(fAngleStart), 0.0);
				glVertex3f(fX + kfInnerRadius*cos(fAngleEnd)/1.9, fY + kfInnerRadius*sin(fAngleEnd), 0.0);
			} else {
				glVertex3f(fX + kfInnerRadius*cos(fAngleStart)/1.9, fY + kfInnerRadius*sin(fAngleStart), 0.0);
				glVertex3f(fX + kfRadius*cos(fAngleEnd)/1.9, fY + kfRadius*sin(fAngleEnd), 0.0);
			}
		}
	glEnd();
}

void DrawStars() {
	for (int iStarRow = 0; iStarRow < 9; ++iStarRow) {
		float fY = 6.0/13.0 + (iStarRow + 1)*((7.0/13.0)/10);
		// Alternate between rows of five or six stars
		if (iStarRow % 2 == 0) {
			for (int iStarCol = 0; iStarCol < 6; ++iStarCol) {
				DrawStar(iStarCol*((0.76/1.9)/6.0) + (0.76/1.9)/12.0, fY);
			}
		} else {
			for (int iStarCol = 0; iStarCol < 5; ++iStarCol) {
				DrawStar((iStarCol + 1)*((0.76/1.9)/6.0), fY);
			}
		}
	}
}

void DrawStripes() {
	for (int iStripeIndex = 0; iStripeIndex < 13; ++iStripeIndex) {
		// Alternate stripe colors
		if (iStripeIndex % 2 == 0) {
			glColor3f(204.0/255.0, 0.0, 0.0);
		} else {
			glColor3f(1.0, 1.0, 1.0);
		}
		float fStartX	= 0.0;
		float fEndX		= 1.0;
		float fStartY	= iStripeIndex*(1.0/13.0);
		float fEndY		= (iStripeIndex + 1)*(1.0/13.0);
		// The last seven stripes are shorter
		if (iStripeIndex > 5) {
			fStartX = 0.76/1.9;
		}
		glBegin(GL_QUADS);
			glVertex3f(fStartX, fStartY, 0.0);
			glVertex3f(fEndX, fStartY, 0.0);
			glVertex3f(fEndX, fEndY, 0.0);
			glVertex3f(fStartX, fEndY, 0.0);
		glEnd();
	}
}

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	DrawStripes();
	DrawStars();
	glFlush();
}

void Initialize() {
	glClearColor(0.0, 0.0, 102.0/255.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(950, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("American Flag Made By Aqib Mehedi");
	Initialize();
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}
