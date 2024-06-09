#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "glut.h"

// угол поворота камеры
float angle = 0.0;
// координаты вектора направления движения камеры
float lx = 0.0f, lz = -1.0f;

// XZ позиция камеры
float x = 0.0f, z = 5.0f, y = 0.0f;
//Ключи статуса камеры. Переменные инициализируются нулевыми значениями
//когда клавиши не нажаты
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

// игровыве объекты
bool is_open = false;
bool is_lift_cube = false;
double x_cube = -5, y_cube = 0, z_cube = -5;
double x_button = -2, y_button = 0, z_button = -3;
double x_portal = 5, y_portal = 0, z_portal = 5;

int game_status = 0; // 0 - игра продолжается, 1 - победа, -1 - после 2х минут проигрышь

int Game_space_radius = 5;

void timer(int value) {
	game_status = -1;
}

void changeSize(int w, int h) {
	// предотвращение деления на ноль
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);
	// обнуляем матрицу
	glLoadIdentity();
	// установить параметры вьюпорта
	glViewport(0, 0, w, h);
	// установить корректную перспективу
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// вернуться к матрице проекции
	glMatrixMode(GL_MODELVIEW);
}

void drawButton() {
	glPushMatrix();

	glBegin(GL_QUADS);
	// Грань 1
	glColor3f(0.8f, 0.7f, 0.6f); // Черный цвет

	glVertex3f(-0.5f, 0.2f, -0.5f);
	glVertex3f(-0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, 0.2f, -0.5f);

	// Грань 2
	glVertex3f(-0.5f, 0.2f, 0.5f);
	glVertex3f(-0.5f, -0.2f, 0.5f);
	glVertex3f(0.5f, -0.2f, 0.5f);
	glVertex3f(0.5f, 0.2f, 0.5f);

	// Грань 3
	glVertex3f(-0.5f, 0.2f, -0.5f);
	glVertex3f(-0.5f, -0.2f, -0.5f);
	glVertex3f(-0.5f, -0.2f, 0.5f);
	glVertex3f(-0.5f, 0.2f, 0.5f);

	// Грань 4
	glVertex3f(0.5f, 0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, 0.5f);
	glVertex3f(0.5f, 0.2f, 0.5f);

	// Грань 5
	glVertex3f(-0.5f, 0.2f, 0.5f);
	glVertex3f(-0.5f, 0.2f, -0.5f);
	glVertex3f(0.5f, 0.2f, -0.5f);
	glVertex3f(0.5f, 0.2f, 0.5f);

	// Грань 6
	glVertex3f(-0.5f, -0.2f, 0.5f);
	glVertex3f(-0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, 0.5f);
	glEnd();


	glColor3f(0.0f, 0.0f, 0.0f); // Черный цвет
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5f, 0.2f, -0.5f);
	glVertex3f(-0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, 0.2f, -0.5f);

	// Грань 2
	glVertex3f(-0.5f, 0.2f, 0.5f);
	glVertex3f(-0.5f, -0.2f, 0.5f);
	glVertex3f(0.5f, -0.2f, 0.5f);
	glVertex3f(0.5f, 0.2f, 0.5f);

	// Грань 3
	glVertex3f(-0.5f, 0.2f, -0.5f);
	glVertex3f(-0.5f, -0.2f, -0.5f);
	glVertex3f(-0.5f, -0.2f, 0.5f);
	glVertex3f(-0.5f, 0.2f, 0.5f);

	// Грань 4
	glVertex3f(0.5f, 0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, -0.5f);
	glVertex3f(0.5f, -0.2f, 0.5f);
	glVertex3f(0.5f, 0.2f, 0.5f);

	// Грань 5
	glVertex3f(-0.5f, 0.2f, 0.5f);
	glVertex3f(-0.5f, 0.2f, -0.5f);
	glVertex3f(0.5f, 0.2f, -0.5f);
	glVertex3f(0.5f, 0.2f, 0.5f);

	// Грань 6
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

	// грань 1
	glColor3f(1.0f, 0.0f, 0.0f); // красный
	glVertex3f(-0.25f, 0.0f, -0.25f);
	glVertex3f(0.25f, 0.0f, -0.25f);
	glVertex3f(0.25f, 0.5f, -0.25f);
	glVertex3f(-0.25f, 0.5f, -0.25f);

	// грань 2
	glColor3f(1.0f, 1.0f, 0.0f); // желтый
	glVertex3f(-0.25f, 0.0f, 0.25f);
	glVertex3f(0.25f, 0.0f, 0.25f);
	glVertex3f(0.25f, 0.5f, 0.25f);
	glVertex3f(-0.25f, 0.5f, 0.25f);

	// грань 3
	glColor3f(0.0f, 1.0f, 0.0f); // зеленый
	glVertex3f(-0.25f, 0.0f, -0.25f);
	glVertex3f(0.25f, 0.0f, -0.25f);
	glVertex3f(0.25f, 0.0f, 0.25f);
	glVertex3f(-0.25f, 0.0f, 0.25f);

	// грань 4
	glColor3f(0.0f, 1.0f, 1.0f); // голубой
	glVertex3f(-0.25f, 0.5f, -0.25f);
	glVertex3f(0.25f, 0.5f, -0.25f);
	glVertex3f(0.25f, 0.5f, 0.25f);
	glVertex3f(-0.25f, 0.5f, 0.25f);

	// грань 5
	glColor3f(0.0f, 0.0f, 1.0f); // синий
	glVertex3f(0.25f, 0.0f, -0.25f);
	glVertex3f(0.25f, 0.5f, -0.25f);
	glVertex3f(0.25f, 0.5f, 0.25f);
	glVertex3f(0.25f, 0.0f, 0.25f);

	// грань 6
	glColor3f(1.0f, 0.0f, 1.0f); // фиолетовый
	glVertex3f(-0.25f, 0.0f, -0.25f);
	glVertex3f(-0.25f, 0.5f, -0.25f);
	glVertex3f(-0.25f, 0.5f, 0.25f);
	glVertex3f(-0.25f, 0.0f, 0.25f);

	glEnd();
	glPopMatrix();
}

void drawPortal() {
	// Начало рисования двери портала
	glPushMatrix();

	// Рисуем рамку вокруг двери
	glLineWidth(5); // Задаем ширину линии

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
		// Верхний левый угол
		glColor3f(1.0f, 0.0f, 1.0f); // Левый верхний угол - цвет #FF00FF
		// Верхний правый угол
		glColor3f(0.0f, 0.0f, 1.0f); // Правый верхний угол - цвет #0000FF
		// Нижний правый угол
		glColor3f(0.0f, 1.0f, 1.0f); // Правый нижний угол - цвет #00FFFF
		// Нижний левый угол
		glColor3f(1.0f, 1.0f, 0.0f); // Левый нижний угол - цвет #FFFF00
		glEnd();
	}
	// Рисуем рамку вокруг двери портала
	glColor3f(1.0f, 0.0f, 0.0f); // Черный цвет
	glBegin(GL_LINES);
	// Вертикальные линии
	glVertex3f(-0.25f, 1.5f, 0.26f); // Верхний левый угол
	glVertex3f(-0.25f, -1.5f, 0.26f); // Нижний левый угол
	glVertex3f(0.25f, 1.5f, 0.26f); // Верхний правый угол
	glVertex3f(0.25f, -1.5f, 0.26f); // Нижний правый угол
	// Горизонтальные линии
	glVertex3f(-0.25f, 1.5f, 0.26f); // Верхний левый угол
	glVertex3f(0.25f, 1.5f, 0.26f); // Верхний правый угол
	glVertex3f(-0.25f, -1.5f, 0.26f); // Нижний левый угол
	glVertex3f(0.25f, -1.5f, 0.26f); // Нижний правый угол
	glEnd();

	glPopMatrix(); // Завершаем рисование двери портала
}

void computePos(float deltaMove)
{
	float x_new = x + deltaMove * lx * 0.1f;
	float z_new = z + deltaMove * lz * 0.1f;

	// Проверка на столкновение со стенами
	if (x_new < -Game_space_radius || x_new > Game_space_radius || z_new < -Game_space_radius || z_new > Game_space_radius) {
		return; // Не двигаемся если столкнулись 
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
		game_status = 1;
	}

	x = x_new;
	z = z_new;
}

void drawWall(double center = 0) {
	glColor3f(0.0, 0.0, 0.0); // установка цвета линий на черный

	glBegin(GL_LINE_LOOP); // рисуем только контуры
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
	if (game_status == 0) {
		if (deltaMove)
			computePos(deltaMove);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(x, 1.0f, z,
			x + lx, 1.0f, z + lz,
			0.0f, 1.0f, 0.0f);
		glColor3f(0.9, 1, 0.9);
		glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, -100.0f);
		glEnd();

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

	else if (game_status == 1){
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(0, 1.0f, 5,
			0, 1.0f, 4,
			0.0f, 1.0f, 0.0f);

		glColor3f(1.0, 1.0, 1.0); 
		std::string str = "You W I N!";
		int i = 0;
		while (str[i] != '\0') {
			glRasterPos2f((double)i * 0.2 - 3 + 2, 1.0); 
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);

			++i;
		}

		glutSwapBuffers();
	}

	else if (game_status == -1) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();
			gluLookAt(0, 1.0f, 5,
				0, 1.0f, 4,
				0.0f, 1.0f, 0.0f);

			glColor3f(1.0, 1.0, 1.0);
			std::string str = "You L O S E!";
			int i = 0;
			while (str[i] != '\0') {
				glRasterPos2f((double)i * 0.2 - 3 + 2, 1.0);
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);

				++i;
			}
			
			glutSwapBuffers();
		}
}

void processNormalKeys(unsigned char key, int xx, int yy) {
	if (key == 27)
		exit(0);
}

void pressKey(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_UP: deltaMove = 0.5f; break; // отвечает за то, когда нажата клавиша то по 0.5 двигает камеру по карте
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

	if (xOrigin >= 0) {

		deltaAngle = (x - xOrigin) * 0.01f;

		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else {	
			xOrigin = x;
		}
	}
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Portal 3");
	
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	glEnable(GL_DEPTH_TEST);
	glutTimerFunc(30000, timer, 0);
	std::cout << "You have 30 second...";
	glutMainLoop();
	
	return 0;
}