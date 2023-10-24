#include <windows.h>

#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>

bool autoColorChange = false;
using namespace glm;
double timer=0;
glm::vec3 currentColor(1.0f, 0.0f, 0.0f);
const int coloursQun = 6;
int R = 0, G = 0, B = 0;
glm::vec3 colorsArray[coloursQun] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 0.0f)
};
int currentColour = 0;
void autoColorChangeFunc();
// используем пространство имен стандартной библиотеки
using namespace std;

// функция, вызываемая при изменении размеров окна
void reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void display(void)
{
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10, 15, 17.5, 0, 0, 0, 0, 1, 0);
	// Матрица модели правого чайника, в точке - (4,0,0)
	GLfloat modelMatrix0[16] = {
	-1.0, 0.0, 0.0, 0.0, // ось Ox
	0.0, 1.0, 0.0, 0.0, // ось Oy
	0.0, 0.0, 1.0, 0.0, // ось Oz
	4.0, 0.0, 0.0, 1.0 // позиция объекта (начало системы координат)
	};
	// Матрица модели левого чайника, в точке - (-4,0,0)
	GLfloat modelMatrix1[16] = {
	1.0, 0.0, 0.0, 0.0, // ось Ox
	0.0, 1.0, 0.0, 0.0, // ось Oy
	0.0, 0.0, 1.0, 0.0, // ось Oz
	-4.0, 0.0, 0.0, 1.0 // позиция объекта (начало системы координат)
	};
	GLfloat modelMatrix2[16] = {
		0, 0, 1, 0, // ось Ox
		0, 1, 0, 0,  // ось Oy
		-1, 0, 0, 0,  // ось Oz
		0, 0, -4, 1   // позиция объекта (начало системы координат)
	};

	GLfloat modelMatrix3[16] = {
		0, 0, -1, 0, // ось Ox
		0, 1, 0, 0,  // ось Oy
		1, 0, 0, 0,  // ось Oz
	0.0, 0.0, 4.0, 1.0 // позиция объекта (начало системы координат)
	};
	// вывод правого чайника
	glColor3f(1, 0, 0);
	glPushMatrix();
	glMultMatrixf(modelMatrix0);
	glutWireTeapot(1.0);
	glPopMatrix();
	// вывод левого чайника
	glColor3f(0, 0, 1);
	glPushMatrix();
	glMultMatrixf(modelMatrix1);
	glutWireTeapot(1.0);
	glPopMatrix();

	glColor3f(0, 1, 0);
	glPushMatrix();
	glMultMatrixf(modelMatrix2);
	glutWireTeapot(1.0);
	glPopMatrix();

	glColor3f(0, 1, 1);
	glPushMatrix();
	glMultMatrixf(modelMatrix3);
	glutWireTeapot(1.0);
	glPopMatrix();

	glutSwapBuffers();
};

// функция вызывается каждые 20 мс
void simulation(int value)
{


	//cout << timer << endl;
	if (autoColorChange == true) {
		timer = timer+1;
		if (timer == 50) {
			timer = 0;
			autoColorChangeFunc();
		}
	}
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	// эта же функция будет вызвана еще раз через 20 мс
	glutTimerFunc(20, simulation, 0);
};


// Функция обработки нажатия клавиш
void keyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", key);
	if (key == 100) {
		currentColour++;
		if (currentColour == coloursQun) {
			currentColour = 0;
		}
	}
	else if (key == 97) {
		currentColour--;
		if (currentColour <= 0) {
			currentColour = coloursQun;
		}
	}
	else if (key == 119) {
		autoColorChange = true; // Включаем автоматическую смену цветов
	}
	else if (key == 115) {
		autoColorChange = false; // Выключаем автоматическую смену цветов
	};
	
	R = colorsArray[currentColour].r;
	G = colorsArray[currentColour].g;
	B = colorsArray[currentColour].b;
	cout << R<<endl;

};
void autoColorChangeFunc()
{

		currentColour++;
		if (currentColour == coloursQun) {
			currentColour = 0;
		}

		R = colorsArray[currentColour].r;
		G = colorsArray[currentColour].g;
		B = colorsArray[currentColour].b;
		glutPostRedisplay();
		
	
		
}

void main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru");

	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// СОЗДАНИЕ ОКНА:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(800, 600);
	// 3. создаем окно
	glutCreateWindow("Laba_01");

	// УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(reshape);
	// устанавливаем функцию, которая будет вызвана через 20 мс
	//glutTimerFunc(20, simulation, 0);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	// В функции main
	
	glutKeyboardFunc(keyboardFunc);
	
	glutTimerFunc(20, simulation, 0);
	


	// основной цикл обработки сообщений ОС
	glutMainLoop();
};