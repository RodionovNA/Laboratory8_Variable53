//#include <math.h>
//
//#include <stdlib.h>
//#include "glut.h"
//
//// угол поворота камеры
//float angle = 0.0;
//// координаты вектора направления движения камеры
//float lx = 0.0f, lz = -1.0f;
//// XZ позиция камеры
//float x = 0.0f, z = 5.0f, y = 1.0f;
////Ключи статуса камеры. Переменные инициализируются нулевыми значениями
////когда клавиши не нажаты
//float deltaAngle = 0.0f;
//float deltaMove = 0;
//int xOrigin = -1;
//bool is_open = true;
//
//void changeSize(int w, int h) {
//	// предотвращение деления на ноль
//	if (h == 0)
//		h = 1;
//	float ratio = w * 1.0 / h;
//	// используем матрицу проекции
//	glMatrixMode(GL_PROJECTION);
//	// обнуляем матрицу
//	glLoadIdentity();
//	// установить параметры вьюпорта
//	glViewport(0, 0, w, h);
//	// установить корректную перспективу
//	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
//	// вернуться к матрице проекции
//	glMatrixMode(GL_MODELVIEW);
//}
//
//void drawCube() {
//	glColor3f(0.0f, 0.0f, 1.0f); // Синий цвет
//	// Начало рисования двери портала
//	glPushMatrix();
//	glTranslatef(0.0f, 0.0f, -0.1f);
//	glutSolidCube(1.0f); // Рисуем прямоугольник для двери
//	glPopMatrix();
//}
//
//void drawPortal() {
//	glColor3f(0.0f, 0.0f, 1.0f); // Синий цвет
//	// Начало рисования двери портала
//	glPushMatrix();
//	glTranslatef(0.0f, 0.0f, -0.1f);
//	glutSolidCube(0.5f); // Рисуем прямоугольник для двери
//	// Рисуем рамку вокруг двери
//	glColor3f(0.0f, 0.0f, 0.0f); // Белый цвет
//	glLineWidth(5.0f); // Задаем ширину линии
//	
//	if (is_open) {
//		glBegin(GL_POLYGON);
//		glColor3f(1.0f, 0.0f, 1.0f); // Белый цвет
//		glVertex3f(-0.25f, 2, 0.26f); // Верхний левый угол
//		glVertex3f(-0.25f, -2, 0.26f); // Нижний левый угол
//		glVertex3f(0.25f, 2, 0.26f); // Верхний правый угол
//		glVertex3f(0.25f, -2, 0.26f); // Нижний правый угол
//		glVertex3f(-0.25f, 2, 0.26f); // Соединяем верхние углы
//		glVertex3f(0.25f, 2, 0.26f);
//		glVertex3f(-0.25f, -2, 0.26f); // Соединяем нижние углы
//		glVertex3f(0.25f, -2, 0.26f);
//	} 
//	
//	else {
//		glBegin(GL_LINES);
//		glVertex3f(-0.25f, 2, 0.26f); // Верхний левый угол
//		glVertex3f(-0.25f, -2, 0.26f); // Нижний левый угол
//		glVertex3f(0.25f, 2, 0.26f); // Верхний правый угол
//		glVertex3f(0.25f, -2, 0.26f); // Нижний правый угол
//		glVertex3f(-0.25f, 2, 0.26f); // Соединяем верхние углы
//		glVertex3f(0.25f, 2, 0.26f);
//		glVertex3f(-0.25f, -2, 0.26f); // Соединяем нижние углы
//		glVertex3f(0.25f, -2, 0.26f);
//	}
//
//	glEnd();
//	glPopMatrix(); // Завершаем рисование двери портала
//}
//
//void computePos(float deltaMove)
//{
//	x += deltaMove * lx * 0.1f;
//	z += deltaMove * lz * 0.1f;
//}
//
//void renderScene(void) {
//	if (deltaMove)
//		computePos(deltaMove);
//	//очистить буфер цвета и глубины
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	// обнулить трансформацию
//	glLoadIdentity();
//	// установить камеру
//	gluLookAt(x, 1.0f, z,
//		x + lx, 1.0f, z + lz,
//		0.0f, 1.0f, 0.0f);
//	// нарисуем "землю"
//	glColor3f(0.9f, 0.9f, 0.9f);
//	// полигон (plaine)
//	glBegin(GL_QUADS);
//	glVertex3f(-100.0f, 0.0f, -100.0f);
//	glVertex3f(-100.0f, 0.0f, 100.0f);
//	glVertex3f(100.0f, 0.0f, 100.0f);
//	glVertex3f(100.0f, 0.0f, -100.0f);
//	glEnd();
//	
//	glPushMatrix();
//
//	glTranslatef(5.0, 0, 5.0);
//	drawPortal();
//
//	glTranslatef(10.0, 0, 10.0);
//	drawPortal();
//
//	glPopMatrix();
//		
//	glutSwapBuffers();
//}
//
//void processNormalKeys(unsigned char key, int xx, int yy) {
//	if (key == 27)
//		exit(0);
//	if (key == 119) // w
//	{
//
//	}
//	if (key == 100) // d
//	{
//
//	}
//	if (key == 97) // a
//	{
//
//	}
//}
//
//void pressKey(int key, int xx, int yy) {
//
//	switch (key) {
//	case GLUT_KEY_UP: deltaMove = 0.5f; break;
//	case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
//	}
//}
//
//void releaseKey(int key, int x, int y) {
//
//	switch (key) {
//	case GLUT_KEY_UP:
//	case GLUT_KEY_DOWN: deltaMove = 0; break;
//	}
//}
//
//void mouseMove(int x, int y) {
//
//	// this will only be true when the left button is down
//	if (xOrigin >= 0) {
//
//		// update deltaAngle
//		deltaAngle = (x - xOrigin) * 0.001f;
//
//		// update camera's direction
//		lx = sin(angle + deltaAngle);
//		lz = -cos(angle + deltaAngle);
//	}
//
//}
//
//void mouseButton(int button, int state, int x, int y) {
//
//	// only start motion if the left button is pressed
//	if (button == GLUT_LEFT_BUTTON) {
//
//		// when the button is released
//		if (state == GLUT_UP) {
//			angle += deltaAngle;
//			xOrigin = -1;
//		}
//		else {	// state = GLUT_DOWN
//			xOrigin = x;
//		}
//	}
//}
//
//int main(int argc, char** argv) {
//
//	// инициализация GLUT и создание окна
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(400, 400);
//	glutCreateWindow("Portal 3");
//
//	// регистрация
//	glutDisplayFunc(renderScene);
//	glutReshapeFunc(changeSize);
//	glutIdleFunc(renderScene);
//
//	glutIgnoreKeyRepeat(1);
//	glutKeyboardFunc(processNormalKeys);
//	glutSpecialFunc(pressKey);
//	glutSpecialUpFunc(releaseKey);
//
//	// регистрируем две новые функции
//	glutMouseFunc(mouseButton);
//	glutMotionFunc(mouseMove);
//
//	// OpenGL - инициализация функции теста
//	glEnable(GL_DEPTH_TEST);
//
//	// главный цикл
//	glutMainLoop();
//
//	return 1;
//}