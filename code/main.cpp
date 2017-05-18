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
//int width, height;//ウィンドウ大きさ・座標
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
//　　Yuragi
//　　Desc : ゆらぎ関数
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
				dw[x][y] = dw[x][y] / 6.17 + 1;//i = 1, n = 1のとき用
				//dw[x][y] = dw[x][y] / 10 + 0.9;//i = 2, n = 1のとき用
				//dw[x][y] = dw[x][y] / 6 + 1;//i = 2, n = 3のとき用

				dxmax = (dx[x][y] >= dxmax) ? dx[x][y] : dxmax;
				dxmin = (dx[x][y] <= dxmin) ? dx[x][y] : dxmin;
				dymax = (dy[x][y] >= dymax) ? dy[x][y] : dymax;
				dymin = (dy[x][y] <= dymin) ? dy[x][y] : dymin;
				dwmax = (dw[x][y] >= dwmax) ? dw[x][y] : dwmax;
				dwmin = (dw[x][y] <= dwmin) ? dw[x][y] : dwmin;
			}
			//cout << "(x, y) = (" << x << ", " << y << ")：dx = " << dx[x][y] << endl;
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
//　　Display
//　　Desc : ウィンドウ1への描画
//---------------------------------------------------------------------------------------------------
void Display(void) {

	//画面クリア
	glClear(GL_COLOR_BUFFER_BIT);	

	////////////////////////////////////////色の重なりの確認/////////////////////////////////
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

	///////////////////////////////////////ゆらぎ////////////////////////////////////////////
	//中心点
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
		//基準とする直線（点のつながり）
		glPointSize(PointSize);
		glBegin(GL_POINTS);
		glColor3d(1.0, 0.0, 0.0);
		glVertex2d(x, y);
		glEnd();

		//太さ（点の大きさ）のみにゆらぎを与えたとき
		glPointSize(PointSize * abs(dw[x][y]));
		glBegin(GL_POINTS);
		glColor3d(0.0, 1.0, 0.0);
		glVertex2d(x, y);
		glEnd();

		//ゆらぎを与えたとき
		//glPointSize(PointSize /** abs(dw[x][y])*/);
		//glBegin(GL_POINTS);
		//glColor3d(0.0, 0.0, 1.0);
		//glVertex2d(x + dx[x][y], y);
		////glVertex2d(x + dx[x][y], y + dy[x][y]);
		//glEnd();
	}
	//for (int y = 1; y < NN; y++) {
	//	x = NN / 2;
	//	//基準とする直線（点のつながり）
	//	glPointSize(PointSize);
	//	glBegin(GL_POINTS);
	//	glColor3d(1.0, 0.5, 0.5);
	//	glVertex2d(x, y);
	//	glEnd();

	//	//太さ（点の大きさ）のみにゆらぎを与えたとき
	//	/*glPointSize(PointSize * abs(dw[x][y]));
	//	glBegin(GL_POINTS);
	//	glColor3d(0.0, 1.0, 0.0);
	//	glVertex2d(x, y);
	//	glEnd();*/

	//	//ゆらぎを与えたとき
	//	glPointSize(PointSize /** abs(dw[x][y])*/);
	//	glBegin(GL_POINTS);
	//	glColor3d(0.5, 0.5, 1.0);
	//	glVertex2d(x + dx[x][y], y);
	//	//glVertex2d(x + dx[x][y], y + dy[x][y]);
	//	glEnd();
	//}
	
	
	/////////////////////////////////////////GL_POINT_SMOOTHの確認///////////////////////
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


	//////////////////////////////////////布目をQUADSで描画//////////////////////////////
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
//　　resize
//　　Desc : 
//---------------------------------------------------------------------------------------------------
void resize(int w, int h) {
	/* ウィンドウ全体をビューポートにする */
	glViewport(0, 0, w, h);
	/* 変換行列の初期化 */
	glLoadIdentity();
	//表示する座標範囲を(0, 0, -1)~(400, 400, 1)とする
	glOrtho(0, w, 0, h, -1.0, 1.0);
}

//----------------------------------------------------------------------------------------------------
//　　Initialize
//　　Desc : 初期化処理，背景色
//----------------------------------------------------------------------------------------------------
void Initialize(void) {
	//glClearColor(R, G, B, α値：不透明度（0 で透明, 1 で不透明）);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

//----------------------------------------------------------------------------------------------------
//　　main
//　　Desc : メインエントリーポイント
//----------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {

	if (isinf(0 / (0.000184 * 0.0135)) == 1) cout << "inf" << endl;


	//cout << "x = "; cin >> x; /*cout << "x = " << x << endl;*/
	//cout << "y = "; cin >> y; /*cout << "y = " << y << endl;*/
	cout << "多重度(tajudo)は："; cin >> tajudo; /*cout << "多重度は：" << tajudo << endl;*/
	cout << "周波数係数(n)は："; cin >> n; /*cout << "n = " << n << endl;*/

	//width = NN * PointSize, height = NN * PointSize;//ウィンドウ大きさ・座標
	width = NN, height = NN;//ウィンドウ大きさ・座標

	glutInit(&argc, argv);//glutの初期化
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);//値はピクセル
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