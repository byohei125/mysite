#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <ostream>
#include<sstream>
#include <Windows.h>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include "Difinition.h"
#include "Bitmap.h"


using namespace std;
#define NN 400
//int width, height;//�E�B���h�E�傫���E���W
const int PointSize = 1;
double dx[NN][NN];
double dy[NN][NN];
double dw[NN][NN];
int x, y;
double ax = 1.0, bx = 1.0, cx = 0.1;
double ay = 1.5, by = 1.5, cy = 0.1;
double aw = 0.1, bw = 0.1, cw = 1.0;
int i, tajudo;
double n, e = 1;
double fx1, fx2, fy1, fy2, fw1, fw2;
double dxmax, dxmin, dymax, dymin, dwmax, dwmin;

//---------------------------------------------------------------------------------------------------
//�@�@Yuragi
//�@�@Desc : ��炬�֐�
//---------------------------------------------------------------------------------------------------
void Yuragi(void) {

	/*cout << "fx1 = " << fx1 << endl;
	cout << "fx2 = " << fx2 << endl;*/
	dxmax = 0, dxmin = NN, dymax = 0, dymin = NN, dwmax = 0, dwmin = NN;
	for (x = 1; x < NN; x++) {
		for (y = 1; y < NN; y++) {
			for (i = 1; i <= tajudo; i++) {
				fx1 = sin(x + ax*sin(bx*y) + (i - 1)*cx); /*cout << "fx1 = " << fx1 << endl;*/
				fx2 = sin(y + ax*sin(bx*x) + (i - 1)*cx); /*cout << "fx2 = " << fx2 << endl;*/
				dx[x][y] += (sin(pow(n, (i - 1)) * fx1) + sin(pow(n, (i - 1)) * fx2)) / pow(n, e * (i - 1));
				fy1 = sin(x + ay*sin(by*y) + (i - 1)*cy);
				fy2 = sin(y + ay*sin(by*x) + (i - 1)*cy);
				dy[x][y] += (sin(pow(n, (i - 1)) * fy1) + sin(pow(n, (i - 1)) * fy2)) / pow(n, e * (i - 1));
				fw1 = sin(x + aw*sin(bw*y) + (i - 1)*cw);
				fw2 = sin(y + aw*sin(bw*x) + (i - 1)*cw);
				dw[x][y] += (sin(pow(n, (i - 1)) * fw1) + sin(pow(n, (i - 1)) * fw2)) / pow(n, e * (i - 1));
				dw[x][y] = dw[x][y] / 6.17 + 1;//i = 1, n = 1�̂Ƃ��p
				//dw[x][y] = dw[x][y] / 10 + 0.9;//i = 2, n = 1�̂Ƃ��p
				//dw[x][y] = dw[x][y] / 6 + 1;//i = 2, n = 3�̂Ƃ��p

				dxmax = (dx[x][y] >= dxmax) ? dx[x][y] : dxmax;
				dxmin = (dx[x][y] <= dxmin) ? dx[x][y] : dxmin;
				dymax = (dy[x][y] >= dymax) ? dy[x][y] : dymax;
				dymin = (dy[x][y] <= dymin) ? dy[x][y] : dymin;
				dwmax = (dw[x][y] >= dwmax) ? dw[x][y] : dwmax;
				dwmin = (dw[x][y] <= dwmin) ? dw[x][y] : dwmin;
			}
			//cout << "(x, y) = (" << x << ", " << y << ")�Fdx = " << dx[x][y] << endl;
		}
	}
	cout << "ax = " << ax << ", bx = " << bx << ", cx = " << cx << endl;
	cout << "dxmax = " << dxmax << ",	dxmin = " << dxmin << endl;
	cout << endl;
	cout << "ay = " << ay << ", by = " << by << ", cy = " << cy << endl;
	cout << "dymax = " << dymax << ",	dymin = " << dymin << endl;
	cout << endl;
	cout << "aw = " << aw << ", bw = " << bw << ", cw = " << cw << endl;
	cout << "dwmax = " << dwmax << ",	dwmin = " << dwmin << endl;

}

//---------------------------------------------------------------------------------------------------
//�@�@Display
//�@�@Desc : �E�B���h�E1�ւ̕`��
//---------------------------------------------------------------------------------------------------
void Display(void) {

	//��ʃN���A
	glClear(GL_COLOR_BUFFER_BIT);	

	////////////////////////////////////////�F�̏d�Ȃ�̊m�F/////////////////////////////////
	/*glPushMatrix();
	glColor3d(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2d(NN / 2 -100, NN / 2 - 100);
	glVertex2d(NN / 2 + 100, NN / 2 - 100);
	glVertex2d(NN / 2 + 100, NN / 2 + 100);
	glVertex2d(NN / 2 - 100, NN / 2 + 100);
	glEnd();
	glPushMatrix();

	glPushMatrix();
	glColor3d(0.7, 0.7, 1.0);
	glBegin(GL_QUADS);
	glVertex2d(NN / 2, NN / 2);
	glVertex2d(NN / 2 + 200, NN / 2);
	glVertex2d(NN / 2 + 200, NN / 2 + 200);
	glVertex2d(NN / 2, NN / 2 + 200);
	glEnd();
	glPushMatrix();*/

	///////////////////////////////////////��炬////////////////////////////////////////////
	//���S�_
	/*glPushMatrix();
	glColor3d(1.0, 0.0, 0.0);
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2d(NN / 2, NN / 2);
	glEnd();
	glPushMatrix();*/

	Yuragi();
	glPointSize(PointSize);
	//for (int x = 1; x < NN; x++) {
	//	for (int y = 1; y < NN; y++) {
	//		glBegin(GL_POINTS);
	//		//glVertex2d(NN / 2 - dx[x][y], y);
	//		glVertex2d(x + dx[x][y], y + dy[x][y]);
	//		glEnd();
	//	}
	//}
	for (int y = 1; y < NN; y++) {
		x = NN / 2 + 1;
		//��Ƃ��钼���i�_�̂Ȃ���j
		glPointSize(PointSize);
		glBegin(GL_POINTS);
		glColor3d(1.0, 0.0, 0.0);
		glVertex2d(x, y);
		glEnd();

		//�����i�_�̑傫���j�݂̂ɂ�炬��^�����Ƃ�
		glPointSize(PointSize * abs(dw[x][y]));
		glBegin(GL_POINTS);
		glColor3d(0.0, 1.0, 0.0);
		glVertex2d(x, y);
		glEnd();

		//��炬��^�����Ƃ�
		//glPointSize(PointSize /** abs(dw[x][y])*/);
		//glBegin(GL_POINTS);
		//glColor3d(0.0, 0.0, 1.0);
		//glVertex2d(x + dx[x][y], y);
		////glVertex2d(x + dx[x][y], y + dy[x][y]);
		//glEnd();
	}
	//for (int y = 1; y < NN; y++) {
	//	x = NN / 2;
	//	//��Ƃ��钼���i�_�̂Ȃ���j
	//	glPointSize(PointSize);
	//	glBegin(GL_POINTS);
	//	glColor3d(1.0, 0.5, 0.5);
	//	glVertex2d(x, y);
	//	glEnd();

	//	//�����i�_�̑傫���j�݂̂ɂ�炬��^�����Ƃ�
	//	/*glPointSize(PointSize * abs(dw[x][y]));
	//	glBegin(GL_POINTS);
	//	glColor3d(0.0, 1.0, 0.0);
	//	glVertex2d(x, y);
	//	glEnd();*/

	//	//��炬��^�����Ƃ�
	//	glPointSize(PointSize /** abs(dw[x][y])*/);
	//	glBegin(GL_POINTS);
	//	glColor3d(0.5, 0.5, 1.0);
	//	glVertex2d(x + dx[x][y], y);
	//	//glVertex2d(x + dx[x][y], y + dy[x][y]);
	//	glEnd();
	//}
	
	
	/////////////////////////////////////////GL_POINT_SMOOTH�̊m�F///////////////////////
	//const int PointSize = 3;	
	////glPushMatrix();
	//glColor4d(0.5, 0.5, 1.0, 0.8);
	//glScaled(1, 1.5, 1);
	//glPointSize(13);	
	//glBegin(GL_POINTS);
	//glVertex2f(200, 200);
	///*glColor4d(0.0, 1.0, 0.0, 0.0);
	//glVertex2f(0.4,0);*/
	//glEnd();
	////glPopMatrix();

	////glPushMatrix();
	//glColor4d(0.3, 0.3, 1.0, 0.8);
	//glEnable(GL_POINT_SMOOTH);
	//glPointSize(11);
	//glBegin(GL_POINTS);
	//glVertex2f(200, 200);
	//glEnd();
	////glPopMatrix();

	////glPushMatrix();
	//glColor4d(0.2, 0.2, 1.0, 0.8);
	//glEnable(GL_POINT_SMOOTH);
	//glPointSize(7);
	//glBegin(GL_POINTS);
	//glVertex2f(200, 200);
	//glEnd();
	////glPopMatrix();

	////glPushMatrix();
	//glColor4d(0.0, 0.0, 1.0, 0.8);
	//glEnable(GL_POINT_SMOOTH);
	//glPointSize(3);
	//glBegin(GL_POINTS);
	//glVertex2f(200, 200);
	//glEnd();
	////glPopMatrix();


	//////////////////////////////////////�z�ڂ�QUADS�ŕ`��//////////////////////////////
	//glPushMatrix();
	//glBegin(GL_QUADS);
	//glColor3d(0.0, 0.0, 1.0);
	//glVertex2d(NN / 2, NN / 2 - 1); glVertex2d(NN / 2 + 3, NN / 2 - 1);
	//glVertex2d(NN / 2 + 3, NN / 2 + 4); glVertex2d(NN / 2, NN / 2 + 4);
	//
	//glColor3d(1.0, 0.0, 0.0);
	///*glVertex2d(NN / 2 + 3, NN / 2); glVertex2d(NN / 2 + 3 + 1, NN / 2);
	//glVertex2d(NN / 2 + 3 + 1, NN / 2 + 3); glVertex2d(NN / 2 + 3, NN / 2 + 3);
	//glVertex2d(NN / 2, NN / 2); glVertex2d(NN / 2 - 1, NN / 2);
	//glVertex2d(NN / 2 - 1, NN / 2 + 3); glVertex2d(NN / 2, NN / 2 + 3);*/
	//glVertex2d(NN / 2 - 0.8, NN / 2 + 3 + 0.8); glVertex2d(NN / 2 + 3 + 0.8, NN / 2 + 3 + 0.8);
	//glVertex2d(NN / 2 + 4, NN / 2 + 3 + 3 + 0.8); glVertex2d(NN / 2 - 1, NN / 2 + 3 + 3 + 0.8);
	//
	//glVertex2d(NN / 2 - 1, NN / 2); glVertex2d(NN / 2 + 4, NN / 2);
	//glVertex2d(NN / 2 + 4, NN / 2 + 3); glVertex2d(NN / 2 - 1, NN / 2 + 3);

	//glColor3d(0.0, 0.0, 1.0);
	//glVertex2d(NN / 2, NN / 2 - 1 + 4); glVertex2d(NN / 2 + 3, NN / 2 - 1 + 4);
	//glVertex2d(NN / 2 + 3, NN / 2 + 4 + 4); glVertex2d(NN / 2, NN / 2 + 4 + 4);

	//glEnd();
	//glPopMatrix();


//	glColor4d(0.5, 0.5, 1.0, 1.0);	
////glEnable(GL_POINT_SMOOTH);
//	glPointSize(30);
//	glBegin(GL_POINTS);
//	for (int i = 100; i <= 300; i += 30) {
//		for (int j = 100; j <= 300; j += 30) {
//			glVertex2f(i, j);
//			//glVertex2f((i + (PointSize - 1) * (i - 1)), (j + (PointSize - 1) * (j - 1)));
//		}
//	}

	glFlush();

}

//---------------------------------------------------------------------------------------------------
//�@�@resize
//�@�@Desc : 
//---------------------------------------------------------------------------------------------------
void resize(int w, int h) {
	/* �E�B���h�E�S�̂��r���[�|�[�g�ɂ��� */
	glViewport(0, 0, w, h);
	/* �ϊ��s��̏����� */
	glLoadIdentity();
	//�\��������W�͈͂�(0, 0, -1)~(400, 400, 1)�Ƃ���
	glOrtho(0, w, 0, h, -1.0, 1.0);
}

//----------------------------------------------------------------------------------------------------
//�@�@Initialize
//�@�@Desc : �����������C�w�i�F
//----------------------------------------------------------------------------------------------------
void Initialize(void) {
	//glClearColor(R, G, B, ���l�F�s�����x�i0 �œ���, 1 �ŕs�����j);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

//----------------------------------------------------------------------------------------------------
//�@�@main
//�@�@Desc : ���C���G���g���[�|�C���g
//----------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {

	if (isinf(0 / (0.000184 * 0.0135)) == 1) cout << "inf" << endl;


	//cout << "x = "; cin >> x; /*cout << "x = " << x << endl;*/
	//cout << "y = "; cin >> y; /*cout << "y = " << y << endl;*/
	cout << "���d�x(tajudo)�́F"; cin >> tajudo; /*cout << "���d�x�́F" << tajudo << endl;*/
	cout << "���g���W��(n)�́F"; cin >> n; /*cout << "n = " << n << endl;*/

	//width = NN * PointSize, height = NN * PointSize;//�E�B���h�E�傫���E���W
	width = NN, height = NN;//�E�B���h�E�傫���E���W

	glutInit(&argc, argv);//glut�̏�����
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);//�l�̓s�N�Z��
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Physics model");
	/*glEnable(GL_POINT_SMOOTH);*/
	//glHint(GL_POINT_SMOOTH_HINT,   GL_NICEST); 
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);*/

	glutDisplayFunc(Display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	Initialize();	
	glutMainLoop();
	return 0;

}