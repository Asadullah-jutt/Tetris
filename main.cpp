#include <iostream>
#include "help.h"
#include <ctime>
using namespace std;

void myRect(int x1, int y1, int x2, int y2, int R, int G, int B, int w);
void lettersnNumbers(int chr, int x1, int x2, int y1, int y2, int size, int R, int G, int B);
void letters(char chr, int x1, int x2, int y1, int y2, int size, int R, int G, int B);
void Capitalizer(char* text);
void drawText(int size, int start_x, int start_y, int R, int G, int B, char* text, bool isNum, int num);

class Board 
{
	int rows;
	int cols;
	friend class TetrisGame;
public:
	Board()
	{
		rows = 17;
		cols = 10;
	}
	Board(int _x , int _y)
	{
		rows = _x;
		cols = _y;
	}
	void Boardprint()
	{
		int xx = 0, yy = 0;
		xx = 900;
		yy = 800;
		//else 
		for (int i = 0; i <= rows; i++)
		{
			myLine(300, 50 + i * 50, yy, 50 + i * 50, 255);
		}
		for (int j = 0; j <= cols; j++)
		{
			myLine(300 + j * 50, 50, 300 + j * 50, xx, 255);
		}

	}
};

class xy_cordinates {

protected:
	int x1, x2;
	int y1, y2;
	friend class Shape;
	friend class TetrisGame;

public:

	xy_cordinates()
	{
		x1 = 0;
		x2 = 0;
		y1 = 0;
		y2 = 0;
	}
	xy_cordinates(int a1, int a2, int b1, int b2)
	{
		x1 = a1;
		x2 = a2;
		y1 = b1;
		y2 = b2;
	}
	void set_x1(int a)
	{
		x1 = a;
	}
	void set_x2(int a)
	{
		x2 = a;
	}
	void set_y1(int a)
	{
		y1 = a;
	}
	void set_y2(int a)
	{
		y2 = a;
	}
};

class Cell : public xy_cordinates{
	bool on;
	int colour;
	friend class Shape;
	friend class TetrisGame;
	
	void moveleft()
	{
		cellprint(1);
		x1 = x1 - 50;
		x2 = x2 - 50;
		cellprint();
	}
	void moveright()
	{
		cellprint(1);
		x1 = x1 + 50;
		x2 = x2 + 50;
		cellprint();
	}

public:
	Cell():xy_cordinates()
	{
		on = 0;
		colour = 0;
	}
	Cell(bool a , int b , int a1, int a2, int b1, int b2 ):xy_cordinates(a1,a2,b1,b2)
	{
		on = a;
		colour = b;
	}
	void cellset(bool a, int b, int a1, int a2, int b1, int b2)
	{
		on = a;
		colour = b;
		set_x1(a1);
		set_x2(a2);
		set_y1(b1);
		set_y2(b2);


	}
	void movement(int t)
	{
		if (t == 1)
			moveleft();
		else if (t == 2)
			moveright();
		
	}
	void cellprint(int dd = 0)
	{
		int R, G, B;

		if (colour == 1)
		{
			R = 255;
			G = 100;
			B = 110;
		}
		else if (colour == 2)
		{
			R = 255;
			G = 0;
			B = 0; // Red
		}
		else if (colour == 3)
		{
			R = 0;
			G = 255;
			B = 0; // Green
		}
		else if (colour == 4)
		{
			R = 0;
			G = 0;
			B = 255; // Blue
		}
		else if (colour == 5)
		{
			R = 255;
			G = 255;
			B = 0; // Yellow
		}
		else if (colour == 6)
		{
			R = 255;
			G = 0;
			B = 255; // Magenta
		}
		else if (colour == 7)
		{
			R = 0;
			G = 255;
			B = 255; // Cyan
		}
		else if (colour == 8)
		{
			R = 255;
			G = 165;
			B = 0; // Orange
		}
		if(dd == 1)
		{
			R = 0;
			G = 0;
			B = 0; // Black (default color)
			myRect(x1 + 5, y1 - 5, x2 - 5, y2 + 5, R, B, G, 3);
			myRect(x1 + 10, y1 - 10, x2 - 10, y2 + 10, R, B, G, 3);
			myRect(x1 + 20, y1 - 20, x2 - 20, y2 + 20, R, B, G , 25);
			return;
		}

		myRect(x1 + 5, y1 - 5, x2 - 5, y2 + 5,R, G, B, 3);
		myRect(x1 + 10, y1 - 10, x2 - 10, y2 + 10, R, G,B- 100, 3);
		myRect(x1 + 20, y1 - 20, x2 - 20, y2 + 20, R, G, B-0, 25);

	}
	void movedown()
	{
		cellprint(1);
		y1 = y1 + 50;
		y2 = y2 + 50;
		cellprint();
	}

};

class Shape {

	Cell C[4][4];
	friend class TetrisGame;
	int type;
public:
	Shape(int aa)
	{
		if (aa == 1)
		{
			type = 1;
			C[0][1].cellset(1, 7, 550, 600, -150, -200);
			C[1][1].cellset(1, 7, 550, 600, -100, -150);
			C[2][1].cellset(1, 7, 550, 600, -50,-100 );
			C[3][1].cellset(1, 7, 550, 600, 0, -50);
		}
		else if (aa == 2)
		{
			type = 2;
			C[1][1].cellset(1, 4, 550, 600, -100, -150);
			C[2][1].cellset(1, 4, 550, 600, -50, -100);
			C[3][1].cellset(1, 4, 550, 600, 0, -50);
			C[3][0].cellset(1, 4, 500, 550, 0, -50);
		}
		else if (aa == 3)
		{
			type = 3;
			C[1][1].cellset(1, 8, 550, 600, -100, -150);
			C[2][1].cellset(1, 8, 550, 600, -50, -100);
			C[3][1].cellset(1, 8, 550, 600, 0, -50);
			C[3][2].cellset(1, 8, 600, 650, 0, -50);
		}
		else if (aa == 4)
		{
			type = 4;
			C[2][1].cellset(1, 5, 550, 600, -50, -100);
			C[2][2].cellset(1, 5, 600, 650, -50, -100);
			C[3][1].cellset(1, 5, 550, 600, 0, -50);
			C[3][2].cellset(1, 5, 600, 650, 0, -50);
		}
		else if (aa == 5)
		{
			type = 5;
			C[2][3].cellset(1, 3, 650, 700, -50, -100);
			C[2][2].cellset(1, 3, 600, 650, -50, -100);
			C[3][1].cellset(1, 3, 550, 600, 0, -50);
			C[3][2].cellset(1, 3, 600, 650, 0, -50);
		}
		else if (aa == 6)
		{
			type = 6;
			C[2][1].cellset(1, 6, 550, 600, -50, -100);
			C[3][0].cellset(1, 6, 500, 550, 0, -50);
			C[3][1].cellset(1, 6, 550, 600, 0, -50);
			C[3][2].cellset(1, 6, 600, 650, 0, -50);
		}
		else if (aa == 7)
		{
			type = 7;
			C[2][0].cellset(1, 2, 500, 600, -50, -100);
			C[2][1].cellset(1, 2, 550, 600, -50, -100);
			C[3][2].cellset(1, 2, 600, 650, 0, -50);
			C[3][1].cellset(1, 2, 550, 600, 0, -50);
		}

	}
	void sprint()
	{
		for(int i = 0 ; i < 4 ; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (C[i][j].on == 1)
					C[i][j].cellprint();
			}
		}
	}
	void movement(int &dd)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (C[i][j].on == 1)
					C[i][j].movement(dd);
			}
		}
		dd = 0;
	}
	void movedown()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (C[i][j].on == 1)
					C[i][j].movedown();
			}
		}
		sprint();
	}


};
class GridBlock {
public:
	bool used;
	int color;
	GridBlock()
	{
		used = 0 ;
		color = 0;
	}
};

class TetrisGame {
	Board Grid;
	char name[30];
	Shape* C;
	GridBlock** backarr;
	int lvl;
public:


	TetrisGame(int l , char *arr)
	{
		lvl = l;
		for (int i = 0;i <  strlen(arr); i++)
			name[i] = arr[i];
		C = nullptr;
		backarr = new GridBlock * [Grid.rows];
		for (int i = 0; i < Grid.rows; i++) {
			backarr[i] = new GridBlock[Grid.cols]; // create an array of integers
		}
	}
	bool canmovedown(GridBlock** &carr ,int i , int j , Shape& S)
	{
		if (i >= Grid.rows -1 )
			return false;
		
		if (S.type == 1)
		{
			if (carr[i][j].used == 1)
				return false;
			else
				return true;
		}
		else if(S.type == 2)  	
		{
			if (carr[i][j].used == 1 || carr[i][j-1].used == 1)
				return false;
			else
				return true;
		}
		else if (S.type == 3)
		{
			if (carr[i][j].used == 1 || carr[i][j + 1].used == 1)
				return false;
			else
				return true;
		}
		else if (S.type == 4)
		{
			if (carr[i][j].used == 1 || carr[i][j + 1].used == 1)
				return false;
			else
				return true;
		}
		else if (S.type == 5)
		{
			if (carr[i][j].used == 1 || carr[i][j - 1].used == 1)
				return false;
			else
				return true;
		}
		else if (S.type == 6)
		{
			if (carr[i][j].used == 1 || carr[i][j + 1].used == 1 || carr[i][j - 1].used == 1)
				return false;
			else
				return true;
		}
		else if (S.type == 7)
		{
			if (carr[i][j].used == 1 || carr[i][j + 1].used == 1)
				return false;
			else
				return true;
		}
		
	}
	bool fillbarr(GridBlock** &carr, int i, int j, Shape& S)
	{
		if (S.type == 1)
		{
			for (int ii = i - 1; ii > i - 5; ii--)
			{
				if (ii == 0)
					return false;
				carr[ii][j].used = 1;
			}
		}
		if (S.type == 2)
		{
			for (int ii = i - 1; ii > i - 4; ii--)
			{
				if (ii == 0)
					return false;
				carr[ii][j].used = 1;
			}
			if (i - 1 <= 0)
				return false;
			carr[i-1][j-1].used = 1;
		}
		if (S.type == 3)
		{
			for (int ii = i - 1; ii > i - 4; ii--)
			{
				if (ii == 0)
					return false;
				carr[ii][j].used = 1;
			}
			if (i - 1 <= 0)
				return false;
			carr[i - 1][j + 1].used = 1;
		}
		if (S.type == 4)
		{
			if (i - 1 <= 0)
				return false;
			carr[i-1][j].used = 1;
			carr[i-1][j+1].used = 1;
			if (i - 2 <= 0)
				return false;
			carr[i-2][j].used = 1;
			carr[i - 2][j + 1].used = 1;
		}
		if (S.type == 5)
		{
			if (i - 1 <= 0)
				return false;
			carr[i -1][j+1].used = 1;
			carr[i -1][j ].used = 1;
			if (i - 2 <= 0)
				return false;
			carr[i - 2][j+1].used = 1;
			carr[i - 2][j + 2].used = 1;
		}
		if (S.type == 6)
		{
			if (i - 1 <= 0)
				return false;
			carr[i - 1][j + 1].used = 1;
			carr[i - 1][j].used = 1;
			if (i - 2 <= 0)
				return false;
			carr[i - 1][j - 1].used = 1;
			carr[i - 2][j].used = 1;
		}
		if (S.type == 7)
		{
			if (i - 1 <= 0)
				return false;
			carr[i - 1][j + 1].used = 1;
			carr[i - 1][j].used = 1;
			if (i - 2 <= 0)
				return false;
			carr[i - 2][j].used = 1;
			carr[i - 2][j - 1].used = 1;
		}
		return true;
	}
	bool movecheck(GridBlock**& carr, int i, int j,int a, Shape& S)
	{
		int l = 1;
		if (a == 1)
			l == -1;

		if (j + l < 0)
			return false;
		if (j + l > Grid.cols)
			return false;
		return true;
	}

	void PlayGame()
	{
		char p[30] = "PLAYER:";
		drawText(30, 900, 200, 0, 255, 255,p , 1, 0);
		drawText(30, 1140, 200, 0, 255, 255, name, 1, 0);
		char l[30] = "Level:";
		char t[20] = "Time:";
		
		drawText(30, 900, 400, 0, 255, 255, l, 1, lvl);
		int s = 100;
		if (lvl == 2)
		{
			s = 50;
		}
		else if (lvl == 3)
			s = 30;
		int i = 0 , j = 0; 
		int a;
		clock_t start = clock();
		char o = '0';
		srand(time(0));
		bool end = 0;
		while (1)
		{
			C = new Shape(rand()%7+1);
			i = 0, j = 5;
			C->movedown();
			C->movedown();
			while (1)
			{
				
				
				Grid.Boardprint();
				isCursorKeyPressed(a);
				//cout << j << "  ";
			
					if (a == 1)
						j--;
					else if (a == 2)
						j++;
					if (j < 0)
					{
						j ==0;
						a == 0;
					}
					else if (j > Grid.cols)
					{
						j == Grid.cols - 1;
						a == 0;
					}
					C->movement(a);
				if (canmovedown(backarr, i, j,*C) == false)
				{
					if (fillbarr(backarr, i, j, *C) == 0)
						end = 1;
					break;
				}
				C->movedown();
				i++;
				Sleep(s);
				clock_t end = clock();
				double duration = (double)(end - start) / CLOCKS_PER_SEC;
				myRect(980, 600, 1100, 700, 10, 10, 10, 60);
				drawText(30, 900, 600, 0, 255, 255, t, 1, duration);


			}
			if (end == 1)
				break;
		}


	}



};



int main()
{ 
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	HANDLE	color = GetStdHandle(STD_OUTPUT_HANDLE); // to color the text

	char s[30] = "Enter Your name : ";
	char name[30];
	drawText(30, 80, 50, 255, 100, 100, s, 1,0);
	cin >> name;
	system("cls");
	 char ss[20] = "TETRIS";
		 drawText(30, 600, 400, 0, 255, 255, ss, 1, 0);
		 drawText(30, 595, 390, 255, 0, 255, ss, 1, 0);
		 Sleep(100);
		
		 drawText(30, 600, 400, 255, 0, 255, ss, 1, 0);
		 drawText(30, 595, 390, 0, 255, 255, ss, 1, 0);
		 Sleep(5000);
		 system("cls");
	//SetConsoleTextAttribute(color,6);
	TetrisGame Game(1,name);
	Game.PlayGame();

	
	return 0;
}

void myRect(int x1, int y1, int x2, int y2, int R, int G, int B, int w)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, w, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(0, 0, 0)); //Fill color can also be passed as parameter to the function!!!
	SelectObject(device_context, brush);
	Rectangle(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
void lettersnNumbers(int chr, int x1, int x2, int y1, int y2, int size, int R = 0, int G = 0, int B = 0) {
	x1 += 5;
	x2 -= 5;
	y1 += 5;
	y2 -= 5;
	int mid_x = (x1 + x2) / 2;
	int mid_y = (y1 + y2) / 2;


	if (chr == 0) {
		myLine3(x1, y1, x2, y2, R, G, B);
		myLine3(x2, y1, x1, y2, R, G, B);

	}
	else if (chr == 1) {
		//  myLine3(x1, mid_y - size / 2, mid_x, y1, R, G, B);
		myLine3(mid_x, y1, mid_x, y2, R, G, B);
		// myLine3(x1, y2, x2, y2, R, G, B);
	}
	else if (chr == 2) {
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x2, y1, x2, mid_y, R, G, B);
		myLine3(x2, mid_y, x1, mid_y, R, G, B);
		myLine3(x1, mid_y, x1, y2, R, G, B);
		myLine3(x1, y2, x2, y2, R, G, B);
	}
	else if (chr == 3) {
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x2, y1, x2, mid_y, R, G, B);
		myLine3(x2, mid_y, x1, mid_y, R, G, B);
		myLine3(x2, mid_y, x2, y2, R, G, B);
		myLine3(x2, y2, x1, y2, R, G, B);
	}
	else if (chr == 4) {
		myLine3(x1, y1, x1, mid_y, R, G, B);
		myLine3(x1, mid_y, x2, mid_y, R, G, B);
		myLine3(mid_x + size / 6, y1, mid_x + size / 6, y2, R, G, B);
	}
	else if (chr == 5) {
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x1, y1, x1, mid_y, R, G, B);
		myLine3(x1, mid_y, x2, mid_y, R, G, B);
		myLine3(x2, mid_y, x2, y2, R, G, B);
		myLine3(x2, y2, x1, y2, R, G, B);
	}
	else if (chr == 6) {
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, mid_y, x2, mid_y, R, G, B);
		myLine3(x2, mid_y, x2, y2, R, G, B);
		myLine3(x2, y2, x1, y2, R, G, B);
	}
	else if (chr == 7) {
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x2, y1, x2, y2, R, G, B);
	}
	else if (chr == 8) {
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, mid_y, x2, mid_y, R, G, B);
		myLine3(x2, y1, x2, y2, R, G, B);
		myLine3(x2, y2, x1, y2, R, G, B);
	}
	else if (chr == 9) {
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x1, y1, x1, mid_y, R, G, B);
		myLine3(x1, mid_y, x2, mid_y, R, G, B);
		myLine3(x2, y1, x2, y2, R, G, B);
		myLine3(x2, y2, x1, y2, R, G, B);
	}
	else if (chr == '-')
		myRect(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 0, 0, 0, 2);
}
void letters(char chr, int x1, int x2, int y1, int y2, int size, int R = 0, int G = 0, int B = 0) {
	x1 += 5;
	x2 -= 5;
	y1 += 5;
	y2 -= 5;
	int mid_x = (x1 + x2) / 2;
	int mid_y = (y1 + y2) / 2;

	if (chr == '0') {
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x1, y2, x2, y2, R, G, B);
		myLine3(x2, y1, x2, y2, R, G, B);
	}
	else if (chr == '1') {
		//  myLine3(x1, mid_y - size / 2, mid_x, y1, R, G, B);
		myLine3(mid_x, y1, mid_x, y2, R, G, B);
		// myLine3(x1, y2, x2, y2, R, G, B);
	}
	else if (chr == '2') {
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x2, y1, x2, mid_y, R, G, B);
		myLine3(x2, mid_y, x1, mid_y, R, G, B);
		myLine3(x1, mid_y, x1, y2, R, G, B);
		myLine3(x1, y2, x2, y2, R, G, B);
	}
	else if (chr == '3') {
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x2, y1, x2, mid_y, R, G, B);
		myLine3(x2, mid_y, x1, mid_y, R, G, B);
		myLine3(x2, mid_y, x2, y2, R, G, B);
		myLine3(x2, y2, x1, y2, R, G, B);
	}
	else if (chr == '4') {
		myLine3(x1, y1, x1, mid_y, R, G, B);
		myLine3(x1, mid_y, x2, mid_y, R, G, B);
		myLine3(mid_x + size / 6, y1, mid_x + size / 6, y2, R, G, B);
	}
	else if (chr == '5') {
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x1, y1, x1, mid_y, R, G, B);
		myLine3(x1, mid_y, x2, mid_y, R, G, B);
		myLine3(x2, mid_y, x2, y2, R, G, B);
		myLine3(x2, y2, x1, y2, R, G, B);
	}
	else if (chr == '6') {
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, mid_y, x2, mid_y, R, G, B);
		myLine3(x2, mid_y, x2, y2, R, G, B);
		myLine3(x2, y2, x1, y2, R, G, B);
	}
	else if (chr == '7') {
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x2, y1, x2, y2, R, G, B);
	}
	else if (chr == '8') {
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, mid_y, x2, mid_y, R, G, B);
		myLine3(x2, y1, x2, y2, R, G, B);
		myLine3(x2, y2, x1, y2, R, G, B);
	}
	else if (chr == '9') {
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x1, y1, x1, mid_y, R, G, B);
		myLine3(x1, mid_y, x2, mid_y, R, G, B);
		myLine3(x2, y1, x2, y2, R, G, B);
		myLine3(x2, y2, x1, y2, R, G, B);
	}
	else if (chr == '-')
		myRect(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 0, 0, 0, 2);
	if (chr == 'A') {
		myLine3(mid_x, y1, x1, y2, R, G, B);
		myLine3(mid_x, y1, x2, y2, R, G, B);
		myLine3(x1 + 2, mid_y + size / 2, x2 - 3, mid_y + size / 2, R, G, B);
	}
	else if (chr == 'B') {
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, y1, mid_x + size / 4, y1 + size / 8, R, G, B);
		myLine3(mid_x + size / 4, y1 + size / 8, mid_x, mid_y, R, G, B);
		myLine3(x1, mid_y, mid_x, mid_y, R, G, B);
		myLine3(mid_x, mid_y, x2, mid_y + size / 4, R, G, B);
		myLine3(x2, mid_y + size / 4, mid_x + size / 8, y2, R, G, B);
		myLine3(mid_x + size / 8, y2, x1, y2, R, G, B);
	}
	else if (chr == 'C') {
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x2, y1, x2, y1 + size / 4, R, G, B);
		myLine3(x2, y2, x2, y2 - size / 4, R, G, B);
		myLine3(x1, y2, x2, y2, R, G, B);
	}
	else if (chr == 'D') {
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, y1, mid_x + size / 4, y1 + size / 4, R, G, B);
		myLine3(mid_x + size / 4, y1 + size / 4, mid_x + size / 4, y2 - size / 4, R, G, B);
		myLine3(mid_x + size / 4, y2 - size / 4, x1, y2, R, G, B);
	}
	else if (chr == 'E') {
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x1, mid_y, x2, mid_y, R, G, B);
		myLine3(x1, y2, x2, y2, R, G, B);
	}
	else if (chr == 'F') {
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x1, mid_y, x2, mid_y, R, G, B);
	}
	else if (chr == 'G') {
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x2, y1, x2, y1 + size / 4, R, G, B);
		myLine3(x2, y2, x2, y2 - size / 2, R, G, B);
		myLine3(x2, y2 - size / 2, mid_x, y2 - size / 2, R, G, B);
		myLine3(x1, y2, x2, y2, R, G, B);
	}
	else if (chr == 'H') {
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x2, y1, x2, y2, R, G, B);
		myLine3(x1, mid_y, x2, mid_y, R, G, B);
	}
	else if (chr == 'I') {
		myLine3(mid_x, y1, mid_x, y2, R, G, B);
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x1, y2, x2, y2, R, G, B);
	}
	else if (chr == 'J') {
		myLine3(x2, y1, x2, y2, R, G, B);
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x2, y2, x1, y2, R, G, B);
		myLine3(x1, y2, x1, y2 - size / 2, R, G, B);
	}
	else if (chr == 'K') {
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, mid_y, x2, y1, R, G, B);
		myLine3(x1, mid_y, x2, y2, R, G, B);
	}
	else if (chr == 'L') {
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, y2, x2, y2, R, G, B);
	}
	else if (chr == 'M') {
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, y1, mid_x, mid_y, R, G, B);
		myLine3(mid_x, mid_y, x2, y1, R, G, B);
		myLine3(x2, y1, x2, y2, R, G, B);
	}
	else if (chr == 'N') {
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, y1, x2, y2, R, G, B);
		myLine3(x2, y1, x2, y2, R, G, B);
	}
	else if (chr == 'O') {
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x1, y2, x2, y2, R, G, B);
		myLine3(x2, y1, x2, y2, R, G, B);
	}
	else if (chr == 'P') {
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, y1, mid_x + size / 4, y1 + size / 8, R, G, B);
		myLine3(mid_x + size / 4, y1 + size / 8, mid_x, mid_y, R, G, B);
		myLine3(x1, mid_y, mid_x, mid_y, R, G, B);

	}
	else if (chr == 'Q') {
		myLine3(x1, y1, x1, y2 - 5, R, G, B);
		myLine3(x1, y1, mid_x + 3, y1, R, G, B);
		myLine3(mid_x + 3, y1, mid_x + 3, y2 - 5, R, G, B);
		myLine3(x1, y2 - 5, mid_x + 3, y2 - 5, R, G, B);
		myLine3(mid_x - 2, mid_y, mid_x + 3, y2 - 5, R, G, B);
		myLine3(mid_x + 3, y2 - 5, x2, y2, R, G, B);
	}
	else if (chr == 'R') {
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, y1, mid_x + size / 4, y1 + size / 8, R, G, B);
		myLine3(mid_x + size / 4, y1 + size / 8, mid_x, mid_y, R, G, B);
		myLine3(x1, mid_y, mid_x, mid_y, R, G, B);
		myLine3(mid_x, mid_y, x2, y2, R, G, B);
	}
	else if (chr == 'S') {
		myLine3(mid_x, y1, x2, y1 + size / 2, R, G, B);
		myLine3(mid_x, y1, x1, y1 + size / 2, R, G, B);
		myLine3(x1, y1 + size / 2, x2, y2 - size / 2, R, G, B);
		myLine3(x2, y2 - size / 2, mid_x, y2, R, G, B);
		myLine3(mid_x, y2, x1, y2 - size / 2, R, G, B);
	}
	else if (chr == 'T') {
		myLine3(mid_x, y1, mid_x, y2, R, G, B);
		myLine3(x1, y1, x2, y1, R, G, B);
	}
	else if (chr == 'U') {
		myLine3(x1, y1, x1, y2, R, G, B);
		myLine3(x1, y2, x2, y2, R, G, B);
		myLine3(x2, y1, x2, y2, R, G, B);

	}
	else if (chr == 'V') {
		myLine3(x1, y1, mid_x, y2, R, G, B);
		myLine3(mid_x, y2, x2, y1, R, G, B);
	}
	else if (chr == 'W') {
		myLine3(x1, y1, mid_x - size / 8, y2, R, G, B);
		myLine3(mid_x - size / 8, y2, mid_x, mid_y, R, G, B);
		myLine3(mid_x, mid_y, mid_x + size / 8, y2, R, G, B);
		myLine3(mid_x + size / 8, y2, x2, y1, R, G, B);
	}
	else if (chr == 'X') {
		myLine3(x1, y1, x2, y2, R, G, B);
		myLine3(x2, y1, x1, y2, R, G, B);

	}
	else if (chr == 'Y') {
		myLine3(x1, y1, mid_x, mid_y, R, G, B);
		myLine3(x2, y1, x1, y2, R, G, B);
	}
	else if (chr == 'Z') {
		myLine3(x1, y1, x2, y1, R, G, B);
		myLine3(x2, y1, x1, y2, R, G, B);
		myLine3(x1, y2, x2, y2, R, G, B);
	}
	else if (chr == '.') {
		myLine3(x1, mid_y - size / 5, mid_x, y1, R, G, B);
		//myLine3(x1+7,3+ mid_y - size/5, mid_x , y1 +2, R, G, B);
		myLine3(x1, mid_y - size / 5, mid_x, y1 + 8, R, G, B);
		myLine3(mid_x, y1, mid_x, y2, R, G, B);
		//myLine3(x1, y2, x2, y2, R, G, B);
	}
	else if (chr == ',') {
		myRect(x2, y2 - size / 3, mid_x + size / 4, y2 - size / 6, R, G, B, 4);
		myLine(x2, y2 - size / 3, x2, y2, R);
		myLine(x2, y2, mid_x + size / 4, y2, R);
	}
	else if (chr == '!') {
		myRect(mid_x - size / 8, y1, mid_x - 1, y2 - size / 3, R, G, B, 4);
		myRect(mid_x - size / 8, y2 - size / 8, mid_x, y2, R, G, B, 4);
	}
	else if (chr == ':') {
		myRect(x2, y2 - 20, mid_x + size / 4, y2 - 16, R, G, B, 4);
		myRect(x2, y2 - 4, mid_x + size / 4, y2, R, G, B, 4);
	}
}
//This Function Converts a Cstring to uppercase
void Capitalizer(char* text) {
	for (int i = 0; i < strlen(text); i++)
		if (text[i] >= 'a' && text[i] <= 'z')
			text[i] -= 32;
}
//This Function to print Text on Screen
void drawText(int size, int start_x, int start_y, int R, int G, int B, char* text, bool isNum = false, int num = 0) {
	int idx = 0;
	int idx_x = 0;
	int idx_y = 0;
	int x1, x2, y1, y2;
	int digit_count = 0;
	int len = strlen(text);
	char temp[100];

	strcpy_s(temp, text);
	//If this function takes a number to print then he converts the number into atring using following loop
	if (isNum == true) {
		int reverse_num = 0;
		int i;
		if (num < 0)
			num = -(num);
		for (; num > 0; num /= 10, digit_count++)
			reverse_num = (reverse_num * 10) + num % 10;

		for (i = len; i - len < digit_count; i++, reverse_num /= 10)
			temp[i] = (reverse_num % 10) + 48;

		temp[i] = '\0';
	}
	//Now the cstring is converted into upper case letters
	Capitalizer(temp);
	//This loop prints each individual letter on the screen
	for (idx = 0; idx < strlen(temp); idx++)
	{
		x1 = start_x + size * idx_x;
		x2 = start_x + size * (idx_x + 1);

		if (x2 > 1585 - size) {
			idx_y++;
			idx_x = 0;
			x1 = start_x + size * idx_x;
			x2 = start_x + size * (idx_x + 1);

		}

		y1 = start_y + 2 * size * idx_y;
		y2 = start_y + 2 * size * (idx_y + 1);
		letters(temp[idx], x1, x2, y1, y2, size, R, G, B);
		idx_x++;
	}

}