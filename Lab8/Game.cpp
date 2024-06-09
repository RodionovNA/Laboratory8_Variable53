#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "glut.h"

// ���� �������� ������
float angle = 0.0;
// ���������� ������� ����������� �������� ������
float lx = 0.0f, lz = -1.0f;

// XZ ������� ������
float x = 0.0f, z = 5.0f, y = 0.0f;
//����� ������� ������. ���������� ���������������� �������� ����������
//����� ������� �� ������
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

// �������� �������
bool is_open = false;
bool is_lift_cube = false;
double x_cube = -5, y_cube = 0, z_cube = -5;
double x_button = -2, y_button = 0, z_button = -3;
double x_portal = 5, y_portal = 0, z_portal = 5;

bool game_over = false;

int Game_space_radius = 5;

void changeSize(int w, int h) {
	// �������������� ������� �� ����
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	// ���������� ������� ��������
	glMatrixMode(GL_PROJECTION);
	// �������� �������
	glLoadIdentity();
	// ���������� ��������� ��������
	glViewport(0, 0, w, h);
	// ���������� ���������� �����������
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// ��������� � ������� ��������
	glMatrixMode(GL_MODELVIEW);
}

void drawButton() {
	glPushMatrix();

	glBegin(GL_QUADS);
	// ����� 1
	glColor3f(0.8f, 0.7f, 0.6f); // ������ ����

	glVertex3f(-0.5f, 0.2f, -0.5f);
	glVertex3f(-0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, 0.2f, -0.5f);

	// ����� 2
	glVertex3f(-0.5f, 0.2f, 0.5f);
	glVertex3f(-0.5f, -0.2f, 0.5f);
	glVertex3f(0.5f, -0.2f, 0.5f);
	glVertex3f(0.5f, 0.2f, 0.5f);

	// ����� 3
	glVertex3f(-0.5f, 0.2f, -0.5f);
	glVertex3f(-0.5f, -0.2f, -0.5f);
	glVertex3f(-0.5f, -0.2f, 0.5f);
	glVertex3f(-0.5f, 0.2f, 0.5f);

	// ����� 4
	glVertex3f(0.5f, 0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, 0.5f);
	glVertex3f(0.5f, 0.2f, 0.5f);

	// ����� 5
	glVertex3f(-0.5f, 0.2f, 0.5f);
	glVertex3f(-0.5f, 0.2f, -0.5f);
	glVertex3f(0.5f, 0.2f, -0.5f);
	glVertex3f(0.5f, 0.2f, 0.5f);

	// ����� 6
	glVertex3f(-0.5f, -0.2f, 0.5f);
	glVertex3f(-0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, 0.5f);
	glEnd();


	glColor3f(0.0f, 0.0f, 0.0f); // ������ ����
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5f, 0.2f, -0.5f);
	glVertex3f(-0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, 0.2f, -0.5f);

	// ����� 2
	glVertex3f(-0.5f, 0.2f, 0.5f);
	glVertex3f(-0.5f, -0.2f, 0.5f);
	glVertex3f(0.5f, -0.2f, 0.5f);
	glVertex3f(0.5f, 0.2f, 0.5f);

	// ����� 3
	glVertex3f(-0.5f, 0.2f, -0.5f);
	glVertex3f(-0.5f, -0.2f, -0.5f);
	glVertex3f(-0.5f, -0.2f, 0.5f);
	glVertex3f(-0.5f, 0.2f, 0.5f);

	// ����� 4
	glVertex3f(0.5f, 0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, 0.5f);
	glVertex3f(0.5f, 0.2f, 0.5f);

	// ����� 5
	glVertex3f(-0.5f, 0.2f, 0.5f);
	glVertex3f(-0.5f, 0.2f, -0.5f);
	glVertex3f(0.5f, 0.2f, -0.5f);
	glVertex3f(0.5f, 0.2f, 0.5f);

	// ����� 6
	glVertex3f(-0.5f, -0.2f, 0.5f);
	glVertex3f(-0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, 0.5f);

	glEnd();

	glPopMatrix();
}

void drawCube() {
	glPushMatrix();
	glBegin(GL_QUADS);

	// ����� 1
	glColor3f(1.0f, 0.0f, 0.0f); // �������
	glVertex3f(-0.25f, 0.0f, -0.25f);
	glVertex3f(0.25f, 0.0f, -0.25f);
	glVertex3f(0.25f, 0.5f, -0.25f);
	glVertex3f(-0.25f, 0.5f, -0.25f);

	// ����� 2
	glColor3f(1.0f, 1.0f, 0.0f); // ������
	glVertex3f(-0.25f, 0.0f, 0.25f);
	glVertex3f(0.25f, 0.0f, 0.25f);
	glVertex3f(0.25f, 0.5f, 0.25f);
	glVertex3f(-0.25f, 0.5f, 0.25f);

	// ����� 3
	glColor3f(0.0f, 1.0f, 0.0f); // �������
	glVertex3f(-0.25f, 0.0f, -0.25f);
	glVertex3f(0.25f, 0.0f, -0.25f);
	glVertex3f(0.25f, 0.0f, 0.25f);
	glVertex3f(-0.25f, 0.0f, 0.25f);

	// ����� 4
	glColor3f(0.0f, 1.0f, 1.0f); // �������
	glVertex3f(-0.25f, 0.5f, -0.25f);
	glVertex3f(0.25f, 0.5f, -0.25f);
	glVertex3f(0.25f, 0.5f, 0.25f);
	glVertex3f(-0.25f, 0.5f, 0.25f);

	// ����� 5
	glColor3f(0.0f, 0.0f, 1.0f); // �����
	glVertex3f(0.25f, 0.0f, -0.25f);
	glVertex3f(0.25f, 0.5f, -0.25f);
	glVertex3f(0.25f, 0.5f, 0.25f);
	glVertex3f(0.25f, 0.0f, 0.25f);

	// ����� 6
	glColor3f(1.0f, 0.0f, 1.0f); // ����������
	glVertex3f(-0.25f, 0.0f, -0.25f);
	glVertex3f(-0.25f, 0.5f, -0.25f);
	glVertex3f(-0.25f, 0.5f, 0.25f);
	glVertex3f(-0.25f, 0.0f, 0.25f);

	glEnd();
	glPopMatrix();
}

void drawPortal() {
	// ������ ��������� ����� �������
	glPushMatrix();

	// ������ ����� ������ �����
	glLineWidth(5); // ������ ������ �����

	if (is_open) {
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 1.0f); 
		glVertex3f(-0.25f, 1.5f, 0.26f);
		glColor3f(0.0f, 0.0f, 1.0f); 
		glVertex3f(0.25f, 1.5f, 0.26f);
		glColor3f(0.0f, 1.0f, 1.0f); 
		glVertex3f(0.25f, -1.5f, 0.26f);
		glColor3f(1.0f, 1.0f, 0.0f); 
		glVertex3f(-0.25f, -1.5f, 0.26f);
		glEnd();
	}
	else {
		glBegin(GL_POLYGON);
		// ������� ����� ����
		glColor3f(1.0f, 0.0f, 1.0f); // ����� ������� ���� - ���� #FF00FF
		// ������� ������ ����
		glColor3f(0.0f, 0.0f, 1.0f); // ������ ������� ���� - ���� #0000FF
		// ������ ������ ����
		glColor3f(0.0f, 1.0f, 1.0f); // ������ ������ ���� - ���� #00FFFF
		// ������ ����� ����
		glColor3f(1.0f, 1.0f, 0.0f); // ����� ������ ���� - ���� #FFFF00
		glEnd();
	}
	// ������ ����� ������ ����� �������
	glColor3f(1.0f, 0.0f, 0.0f); // ������ ����
	glBegin(GL_LINES);
	// ������������ �����
	glVertex3f(-0.25f, 1.5f, 0.26f); // ������� ����� ����
	glVertex3f(-0.25f, -1.5f, 0.26f); // ������ ����� ����
	glVertex3f(0.25f, 1.5f, 0.26f); // ������� ������ ����
	glVertex3f(0.25f, -1.5f, 0.26f); // ������ ������ ����
	// �������������� �����
	glVertex3f(-0.25f, 1.5f, 0.26f); // ������� ����� ����
	glVertex3f(0.25f, 1.5f, 0.26f); // ������� ������ ����
	glVertex3f(-0.25f, -1.5f, 0.26f); // ������ ����� ����
	glVertex3f(0.25f, -1.5f, 0.26f); // ������ ������ ����
	glEnd();

	glPopMatrix(); // ��������� ��������� ����� �������
}

void computePos(float deltaMove)
{
	float x_new = x + deltaMove * lx * 0.1f;
	float z_new = z + deltaMove * lz * 0.1f;

	// �������� �� ������������ �� �������
	if (x_new < -Game_space_radius || x_new > Game_space_radius || z_new < -Game_space_radius || z_new > Game_space_radius) {
		return; // �� ��������� ���� ����������� 
	}
	
	if (x_cube + 1 > x_new && x_new > x_cube -1 && z_cube + 1 > z_new && z_new > z_cube - 1 && y == y_cube) {
		is_lift_cube = true;
	}

	if (x_button + 1 > x_new && x_new > x_button - 1 && z_button + 1 > z_new && z_new > z_button - 1 && y == y_button && is_lift_cube) {
		is_lift_cube = false;
		is_open = true;
		x_cube = x_button;
		y_cube = y_button;
		z_cube = z_button;
	}

	if (x_portal + 1 > x_new && x_new > x_portal - 1 && z_portal + 1 > z_new && z_new > z_portal - 1 && y == y_portal && is_open) {
		game_over = true;
	}

	x = x_new;
	z = z_new;
}

void drawWall(double center = 0) {
	glColor3f(0.0, 0.0, 0.0); // ��������� ����� ����� �� ������

	glBegin(GL_LINE_LOOP); // ������ ������ �������
	glVertex3f(-(Game_space_radius + 1) + center, 0, -(Game_space_radius + 1));
	glVertex3f(-(Game_space_radius + 1) + center, 1.5f, -(Game_space_radius + 1));
	glVertex3f((Game_space_radius + 1) + center, 1.5f, -(Game_space_radius + 1));
	glVertex3f((Game_space_radius + 1) + center, 0, -(Game_space_radius + 1));
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f((Game_space_radius + 1) + center, 0, -(Game_space_radius + 1));
	glVertex3f((Game_space_radius + 1) + center, 1.5f, -(Game_space_radius + 1));
	glVertex3f((Game_space_radius + 1) + center, 1.5f, (Game_space_radius + 1));
	glVertex3f((Game_space_radius + 1) + center, 0, (Game_space_radius + 1));
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f((Game_space_radius + 1) + center, 0, (Game_space_radius + 1));
	glVertex3f((Game_space_radius + 1) + center, 1.5f, (Game_space_radius + 1));
	glVertex3f(-(Game_space_radius + 1) + center, 1.5f, (Game_space_radius + 1));
	glVertex3f(-(Game_space_radius + 1) + center, 0, (Game_space_radius + 1));
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-(Game_space_radius + 1) + center, 0, (Game_space_radius + 1));
	glVertex3f(-(Game_space_radius + 1) + center, 1.5f, (Game_space_radius + 1));
	glVertex3f(-(Game_space_radius + 1) + center, 1.5f, -(Game_space_radius + 1));
	glVertex3f(-(Game_space_radius + 1) + center, 0, -(Game_space_radius + 1));
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(-(Game_space_radius + 1) + center, 0, -(Game_space_radius + 1));
	glVertex3f(-(Game_space_radius + 1) + center, 1.5f, -(Game_space_radius + 1));
	glVertex3f((Game_space_radius + 1) + center, 1.5f, -(Game_space_radius + 1));
	glVertex3f((Game_space_radius + 1) + center, 0, -(Game_space_radius + 1));

	glVertex3f((Game_space_radius + 1) + center, 0, -(Game_space_radius + 1));
	glVertex3f((Game_space_radius + 1) + center, 1.5f, -(Game_space_radius + 1));
	glVertex3f((Game_space_radius + 1) + center, 1.5f, (Game_space_radius + 1));
	glVertex3f((Game_space_radius + 1) + center, 0, (Game_space_radius + 1));

	glVertex3f((Game_space_radius + 1) + center, 0, (Game_space_radius + 1));
	glVertex3f((Game_space_radius + 1) + center, 1.5f, (Game_space_radius + 1));
	glVertex3f(-(Game_space_radius + 1) + center, 1.5f, (Game_space_radius + 1));
	glVertex3f(-(Game_space_radius + 1) + center, 0, (Game_space_radius + 1));

	glVertex3f(-(Game_space_radius + 1) + center, 0, (Game_space_radius + 1));
	glVertex3f(-(Game_space_radius + 1) + center, 1.5f, (Game_space_radius + 1));
	glVertex3f(-(Game_space_radius + 1) + center, 1.5f, -(Game_space_radius + 1));
	glVertex3f(-(Game_space_radius + 1) + center, 0, -(Game_space_radius + 1));
	glEnd();

}

void renderScene(void) {
	if (!game_over) {
		if (deltaMove)
			computePos(deltaMove);
		//�������� ����� ����� � �������
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// �������� �������������
		glLoadIdentity();
		// ���������� ������
		gluLookAt(x, 1.0f, z,
			x + lx, 1.0f, z + lz,
			0.0f, 1.0f, 0.0f);
		// �������� "�����"
		glColor3f(0.9, 1, 0.9);
		// ������� (plaine)
		glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, -100.0f);
		glEnd();

		// �������� �����
		drawWall();

		glPushMatrix();
		glTranslatef(x_portal, y_portal, z_portal);
		drawPortal();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(x_button, y_button, z_button);
		drawButton();
		glPopMatrix();

		if (!is_lift_cube) {
			glPushMatrix();
			glTranslatef(x_cube, y_cube, z_cube);
			drawCube();
			glPopMatrix();
		}

		glutSwapBuffers();
	}

	else {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(0, 1.0f, 5,
			0, 1.0f, 4,
			0.0f, 1.0f, 0.0f);
		// ���������� ������
		glColor3f(1.0, 1.0, 1.0); // ������������� ���� ������ �������
		std::string str = "You W I N!";
		int i = 0;
		while (str[i] != '\0') {
			glRasterPos2f((double)i * 0.2 - 3 + 2, 1.0); // ������������� ������� ������
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);

			++i;
		}

		// ������� ����� "GAME OVER"
		glutSwapBuffers();
	}

}

void processNormalKeys(unsigned char key, int xx, int yy) {
	if (key == 27)
		exit(0);
}

void pressKey(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_UP: deltaMove = 0.5f; break; // �������� �� ��, ����� ������ ������� �� �� 0.5 ������� ������ �� �����
	case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;
	}
}

void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.01f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else {	// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}

int main(int argc, char** argv) {

	// ������������� GLUT � �������� ����
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Portal 3");
	
	// �����������
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	
	// ������������ ��� ����� �������
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	// OpenGL - ������������� ������� �����
	glEnable(GL_DEPTH_TEST);
	
	glutMainLoop();
	
	return 0;
}