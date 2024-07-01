#include <DxLib.h>
#include <stdbool.h>
#include <math.h>
#define size 5
#define pai 3.14159266535
short int d_x = 180, d_y = 180, scale = 600, PX = 300, PY = 260, PZ = size * 5, N, m_x=100, m_y=100,m_z=100, m_dx, m_dy,m_dz,mmap;
int Mouse_x, Mouse_y;
double X, Y, Z, n_x, n_y, n_z;



void Projection(double x, double y, double z)
{
	double temp,lunacab=0.8;
	if (mmap == 0)lunacab = 0.55;
	X = x*lunacab+n_x;  Y = y*lunacab+n_y;  Z = z*lunacab+n_z;
	temp = X;
	X = X * cos(d_y * pai / 180) - Z * sin(d_y * pai / 180);
	Z = temp * sin(d_y * pai / 180) + Z * cos(d_y * pai / 180);
	temp = Y;
	Y = Y * cos(d_x * pai / 180) + Z * sin(d_x * pai / 180);
	Z = Z * cos(d_x * pai / 180) - temp * sin(d_x * pai / 180);
	Z += PZ;
	X = (X * scale / Z);
	Y = (Y * scale / Z);
}

void Drow_number2(double x1, double y1, double z1, double x2, double y2, double z2, short int L,unsigned int Color)
{
	double tri_x, tri_y,tri_x2, tri_y2;
	if (L == 2) {
		Projection(x1, y1, z1);	tri_x = X;	tri_y = Y;
		Projection(x2, y2, z2);	tri_x2 = X;	tri_y2 = Y;
	}
	if (L == 0) {
		Projection(z1, x1, y1);	tri_x = X;	tri_y = Y;
		Projection(z2, x2, y2);	tri_x2 = X;	tri_y2 = Y;
	}
	if (L == 1) {
		Projection(y1, z1, x1);	tri_x = X;	tri_y = Y;
		Projection(y2, z2, x2);	tri_x2 = X;	tri_y2 = Y;
	}
	DrawLineAA(tri_x + PX, tri_y + PY, tri_x2 + PX, tri_y2 + PY, Color, 3);
}

void Drow_number(short int p[],short int L,double x,short int n)
{
	
	bool d[4];
	int c1=0, c2=0, c3=0;
	unsigned int Cr ;
	if (n % 3 == 0) {
		c1 = 250; if (n % 2 == 0)c2 = 80 * n; else c3 = 80 * n;
	}
	else {
		if (n % 3 == 1) {
			c2 = 250; if (n % 2 == 0)c3 = 60 * n; else c1 = 10 * n;
		}
		else {
			c3 = 250; if (n % 2 == 0)c1 = 80 * n; else c2 = 80 * n;
		}
	}
	Cr = GetColor(c1, c2, c3);
	d[0] = (n & 0b0001) >> 0;
	d[1] = (n & 0b0010) >> 1;
	d[2] = (n & 0b0100) >> 2;
	d[3] = (n & 0b1000) >> 3;
	
	if ((d[0] ^ !d[2]) | d[1] | d[3]) {
		Drow_number2(0.6 - x, p[L] * -0.6, p[L], (0.1 - x), p[L] * -0.6,p[L], L,Cr);		// s0
		
	}
	if (!(d[2]&(d[1]^d[0]))){
		Drow_number2((0.1 - x), p[L] * -0.6, p[L] , (0.1 - x), 0, p[L] ,  L,Cr);				//  s2
		
	}
	if (d[3] | d[2] | !d[1] | d[0]) {
		Drow_number2((0.1 - x),  0, p[L], (0.1 - x), p[L] * 0.6, p[L], L,Cr);					//  S5
	}
	if (                d[1]^(d[3]|d[2])|(d[1]&!d[0])   ) {
		Drow_number2((0.1 - x),  0, p[L], (0.6 - x),  0, p[L], L,Cr);							//  S3
		
	}
	if ((!d[2] ^ (!d[1] & d[0]) | (d[1] & !d[0]))) {
		Drow_number2((0.1 - x), p[L] * 0.6, p[L], (0.6 - x), p[L] * 0.6, p[L], L,Cr);				//  S6

	}
	if ((!d[2] & !d[0]) | (d[1] & !d[0])) {
		Drow_number2((0.6 - x), p[L] * 0.6, p[L], (0.6 - x),  0, p[L], L,Cr);				//  S4

	}
	if (d[3] | d[2] | !(d[1]|d[0])) {
		Drow_number2((0.6 - x),  0, p[L], (0.6 - x), p[L] * -0.6, p[L] , L,Cr);					//S1
	
	}


}

void Drow_Block(short int p[], short int x, short int y, short int z, short int map, short int num)
{
	double tri_x[7], tri_y[7], angle = 0;
	short int i;
	unsigned Cr, Cr2;

	Projection(p[0], p[1], p[2]);	tri_x[0] = X;	tri_y[0] = Y;
	Projection(p[0] * -1, p[1], p[2]);	tri_x[1] = X;	tri_y[1] = Y;			Projection(p[0] * -1, p[1] * -1, p[2]);	tri_x[2] = X;	tri_y[2] = Y;
	Projection(p[0], p[1] * -1, p[2]);	tri_x[3] = X;	tri_y[3] = Y;			Projection(p[0], p[1] * -1, p[2] * -1);	tri_x[4] = X;	tri_y[4] = Y;
	Projection(p[0], p[1], p[2] * -1);	tri_x[5] = X;	tri_y[5] = Y;			Projection(p[0] * -1, p[1], p[2] * -1);	tri_x[6] = X;	tri_y[6] = Y;




	if (m_dx == x && m_dy == y && m_dz == z) {
		Cr2 = GetColor(200, 0, 0);
	}
	else
	{
		Cr2 = GetColor(250, 250, 250);
	}
	DrawLineAA(tri_x[1] + PX, tri_y[1] + PY, tri_x[2] + PX, tri_y[2] + PY, Cr2, 3);
	DrawLineAA(tri_x[2] + PX, tri_y[2] + PY, tri_x[3] + PX, tri_y[3] + PY, Cr2, 3);
	DrawLineAA(tri_x[3] + PX, tri_y[3] + PY, tri_x[4] + PX, tri_y[4] + PY, Cr2, 3);
	DrawLineAA(tri_x[4] + PX, tri_y[4] + PY, tri_x[5] + PX, tri_y[5] + PY, Cr2, 3);
	DrawLineAA(tri_x[5] + PX, tri_y[5] + PY, tri_x[6] + PX, tri_y[6] + PY, Cr2, 3);
	DrawLineAA(tri_x[6] + PX, tri_y[6] + PY, tri_x[1] + PX, tri_y[1] + PY, Cr2, 3);

	if (mmap == 0) {
		Cr = GetColor(0, 200, 200);
	}
	else {
		Cr = GetColor(0, 10, 250);
		if (mmap == 3) {
			Cr = GetColor(250, 50, 0);
		}
	}
	DrawTriangle(tri_x[4] + PX, tri_y[4] + PY, tri_x[3] + PX, tri_y[3] + PY, tri_x[5] + PX, tri_y[5] + PY, Cr, TRUE);		
	DrawTriangle(tri_x[2] + PX, tri_y[2] + PY, tri_x[3] + PX, tri_y[3] + PY, tri_x[1] + PX, tri_y[1] + PY, Cr, TRUE);		
	DrawTriangle(tri_x[6] + PX, tri_y[6] + PY, tri_x[5] + PX, tri_y[5] + PY, tri_x[1] + PX, tri_y[1] + PY, Cr, TRUE);		

	

	DrawTriangle(tri_x[0] + PX, tri_y[0] + PY, tri_x[1] + PX, tri_y[1] + PY, tri_x[3] + PX, tri_y[3] + PY, Cr, TRUE);
	DrawTriangle(tri_x[0] + PX, tri_y[0] + PY, tri_x[3] + PX, tri_y[3] + PY, tri_x[5] + PX, tri_y[5] + PY, Cr, TRUE);
	DrawTriangle(tri_x[0] + PX, tri_y[0] + PY, tri_x[5] + PX, tri_y[5] + PY, tri_x[1] + PX, tri_y[1] + PY, Cr, TRUE);
	
	//for (i = 1; i < 6; i++) {
	//	angle += ((tri_x[i]+PX - Mouse_x) * (tri_y[i + 1]+PY - Mouse_y) > (tri_y[i]+PY - Mouse_y) * (tri_x[i + 1] +PX- Mouse_x));
	//}
	//angle += ((tri_x[6] - Mouse_x) * (tri_y[ 1] - Mouse_y) > (tri_y[6] - Mouse_y) * (tri_x[ 1] - Mouse_x));
	//if (angle==0||angle==6) {
	//	m_x = x;
	//	m_y = y;
	//	m_z = z;
	//}

	Projection(0,0,0);	tri_x[6] = X;	tri_y[6] = Y;
	if (((tri_x[6] > tri_x[1]) == (tri_x[0] > tri_x[1])) || ((tri_y[6] > tri_y[1]) == (tri_y[0] > tri_y[1])))
		DrawLineAA(tri_x[0] + PX, tri_y[0] + PY, tri_x[1] + PX, tri_y[1] + PY, Cr2, 3);
	if (((tri_x[6] > tri_x[3]) == (tri_x[0] > tri_x[3])) || ((tri_y[6] > tri_y[3]) == (tri_y[0] > tri_y[3])))
		DrawLineAA(tri_x[0] + PX, tri_y[0] + PY, tri_x[3] + PX, tri_y[3] + PY, Cr2, 3);
	if (((tri_x[6] > tri_x[5]) == (tri_x[0] > tri_x[5])) || ((tri_y[6] > tri_y[5]) == (tri_y[0] > tri_y[5])))
		DrawLineAA(tri_x[0] + PX, tri_y[0] + PY, tri_x[5] + PX, tri_y[5] + PY, Cr2, 3);

	if (((tri_x[6] + PX - Mouse_x) * (tri_x[6] + PX - Mouse_x) + (tri_y[6] + PY - Mouse_y) * (tri_y[6] + PY - Mouse_y)) < 7*(scale-450)&&map!=0) {
		m_x = x;
		m_y = y;
		m_z = z;
	}


	if (map == 0) {
		
		// number


		N = num;

		if (N > 9) {
			Drow_number(p, 2, -0.2, N / 10);
			Drow_number(p, 0, -0.2, N / 10);
			Drow_number(p, 1, -0.2, N / 10);
		}


		Drow_number(p, 2, 0.7, N % 10);
		Drow_number(p, 0, 0.7, N % 10);
		Drow_number(p, 1, 0.7, N % 10);

	}


}








// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	short int  numlist[13][13][13], i, j, k, n, m = 5, nx[50 * 50 * 1], ny[50 * 50 * 1], nz[50 * 50 * 1], does, x[3], y[3], z[3], p[3], p2[3], map[13][13][13];
	unsigned int Cr;
	double  distancelist[50 * 50 * 1], temp, max_z = -1, tri_x[4], tri_y[4], ddx = 0, ddy = 0;
	bool bomlist[13][13][13];


	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	do {

		//初期化
		d_x = 180;  d_y = 180; scale = 600; PX = 300; PY = 260;   m_x = 100; m_y = 100; m_z = 100; max_z = -1;
		for (i = 0; i < size + 2; i++)                  //  1ずらす
		{
			for (j = 0; j < size + 2; j++)
			{
				for (k = 0; k < size + 2; k++)
				{
					map[i][j][k] = 1;                   // map  1 無印     0 hyouji
					bomlist[i][j][k] = 0;
					numlist[i][j][k] = 0;
				}
			}
		}
		for (n = 0; n < 15;) {
			i = GetRand(size - 1) + 1;
			j = GetRand(size - 1) + 1;
			k = GetRand(size - 1) + 1;
			if (!bomlist[i][j][k]) {
				bomlist[i][j][k] = 1;
				for (x[0] = -1; x[0] < 2; x[0]++) {
					for (y[0] = -1; y[0] < 2; y[0]++) {
						for (z[0] = -1; z[0] < 2; z[0]++) {
							numlist[x[0] + i][y[0] + j][z[0] + k] += 1;
						}
					}
				}
				numlist[i][j][k] -= 1;
				n++;
			}
		}

		while (1) {

			i = GetRand(size - 1) + 1;
			j = GetRand(size - 1) + 1;
			k = GetRand(size - 1) + 1;
			//numlist[i][j][k] = 0;
			//bomlist[i][j][k] = 0;
			if (numlist[i][j][k] == 0 && bomlist[i][j][k] == 0 && (i == 1 || j == 1 || k == 1)) {
				for (x[0] = -1; x[0] < 2; x[0]++) {
					for (y[0] = -1; y[0] < 2; y[0]++) {
						for (z[0] = -1; z[0] < 2; z[0]++) {
							map[x[0] + i][y[0] + j][z[0] + k] = 0;
						}
					}
				}
				break;
			}

		}


		//WaitKey();				// キー入力待ち



		does = 1;
		while (does == 1)
		{
			ClearDrawScreen();
			SetDrawScreen(DX_SCREEN_BACK);


			do {
				n = 0;
				for (i = 1; i <= size; i++)
				{
					for (j = 1; j <= size; j++)
					{
						for (k = 1; k <= size; k++)
						{
							if (numlist[i][j][k] == 0 && map[i][j][k] == 0) {
								for (x[0] = -1; x[0] < 2; x[0]++) {
									for (y[0] = -1; y[0] < 2; y[0]++) {
										for (z[0] = -1; z[0] < 2; z[0]++) {
											if (map[i + x[0]][j + y[0]][k + z[0]] == 1) {
												map[i + x[0]][j + y[0]][k + z[0]] = 0;
												n = 1;
											}
										}
									}
								}

							}
						}
					}
				}
			} while (n == 1);


			//numlist[1][1][1] = 3;
			//map[1][1][1] = 0;


			GetMousePoint(&Mouse_x, &Mouse_y);          //   sousa
			m_dx = m_x;
			m_dy = m_y;
			m_dz = m_z;
			m_x = size + 1;
			m_y = size + 1;
			m_z = size + 1;

			n = 0;                //    kyori ranking
			for (i = 0; i < size; i++)
			{
				for (j = 0; j < size; j++)
				{
					for (k = 0; k < size; k++)
					{

						X = (i - size / 2) * 2;  Y = (j - size / 2) * 2;  Z = (k - size / 2) * 2;
						temp = X;
						X = X * cos(d_y * pai / 180) - Z * sin(d_y * pai / 180);
						Z = temp * sin(d_y * pai / 180) + Z * cos(d_y * pai / 180);
						temp = Y;
						Y = Y * cos(d_x * pai / 180) + Z * sin(d_x * pai / 180);
						Z = Z * cos(d_x * pai / 180) - temp * sin(d_x * pai / 180) + PZ;
						temp = X * X + Y * Y + Z * Z;


						nx[n] = i;
						ny[n] = j;
						nz[n] = k;
						distancelist[n] = temp;

						n++;

					}
				}
			}
			for (i = 0; i < n - 1; i++)              //kyori sort
			{
				for (j = i; j < n; j++)
				{
					if (distancelist[i] < distancelist[j])
					{
						temp = distancelist[j];
						distancelist[j] = distancelist[i];
						distancelist[i] = temp;
						x[0] = nx[j];    nx[j] = nx[i];    nx[i] = x[0];
						y[0] = ny[j];    ny[j] = ny[i];    ny[i] = y[0];
						z[0] = nz[j];    nz[j] = nz[i];    nz[i] = z[0];
					}
				}
			}


			//block drow start
			for (i = 0; i < n; i++) {

				n_x = (nx[i] - size / 2) * 2;	n_y = (ny[i] - size / 2) * 2;	n_z = (nz[i] - size / 2) * 2;
				//n_x = 0;	n_y = i;	n_z = 0;
				if (map[nx[i] + 1][ny[i] + 1][nz[i] + 1] != 0 || numlist[nx[i] + 1][ny[i] + 1][nz[i] + 1] != 0) {
					max_z = 1000;
					p2[0] = 1;                       //一番手前の頂点算出
					while (p2[0] > -2) {
						p2[1] = 1;
						while (p2[1] > -2) {
							p2[2] = 1;
							while (p2[2] > -2) {
								X = p2[0] + n_x;  Y = p2[1] + n_y;  Z = p2[2] + n_z;
								temp = X;
								X = X * cos(d_y * pai / 180) - Z * sin(d_y * pai / 180);
								Z = temp * sin(d_y * pai / 180) + Z * cos(d_y * pai / 180);
								temp = Y;
								Y = Y * cos(d_x * pai / 180) + Z * sin(d_x * pai / 180);
								Z = Z * cos(d_x * pai / 180) - temp * sin(d_x * pai / 180) + PZ;
								Z = X * X + Y * Y + Z * Z;
								if (max_z > Z) { max_z = Z; p[0] = p2[0]; p[1] = p2[1]; p[2] = p2[2]; }
								p2[2] -= 2;
							}
							p2[1] -= 2;
						}
						p2[0] -= 2;
					}
					mmap = map[nx[i] + 1][ny[i] + 1][nz[i] + 1];
					Drow_Block(p, nx[i], ny[i], nz[i], map[nx[i] + 1][ny[i] + 1][nz[i] + 1], numlist[nx[i] + 1][ny[i] + 1][nz[i] + 1]);
				}
			}
			DrawFormatString(10, 10, GetColor(0, 250, 0), "残り %d個\n0キーで終了", m);



			ScreenFlip();

			scale += 15 * (GetMouseWheelRotVol());
			//ddy -= ((CheckHitKey(KEY_INPUT_RIGHT) == 1)|| (CheckHitKey(KEY_INPUT_D) == 1)) - ((CheckHitKey(KEY_INPUT_LEFT) == 1)|| (CheckHitKey(KEY_INPUT_A) == 1));
			//ddx -= ((CheckHitKey(KEY_INPUT_UP) == 1)|| (CheckHitKey(KEY_INPUT_W) == 1)) - ((CheckHitKey(KEY_INPUT_DOWN) == 1)|| (CheckHitKey(KEY_INPUT_S) == 1));
			//ddx *= 0.85;
			//ddy *= 0.85;
			d_y += (((CheckHitKey(KEY_INPUT_RIGHT) == 1) || (CheckHitKey(KEY_INPUT_D) == 1)) - ((CheckHitKey(KEY_INPUT_LEFT) == 1) || (CheckHitKey(KEY_INPUT_A) == 1))) * 2;
			d_x += (((CheckHitKey(KEY_INPUT_UP) == 1) || (CheckHitKey(KEY_INPUT_W) == 1)) - ((CheckHitKey(KEY_INPUT_DOWN) == 1) || (CheckHitKey(KEY_INPUT_S) == 1))) * 2;
			d_x = d_x % 360;
			d_y = d_y % 360;

			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && m_x < size)
			{

				SetDrawScreen(DX_SCREEN_BACK);
				DrawBox(Mouse_x + 20, Mouse_y - 65, Mouse_x + 80, Mouse_y - 5, GetColor(255, 0, 0), TRUE);
				DrawBox(Mouse_x + 20, Mouse_y + 5, Mouse_x + 80, Mouse_y + 65, GetColor(0, 255, 0), TRUE);
				DrawString(Mouse_x + 30, Mouse_y - 43, "Dig", GetColor(0, 0, 0));
				DrawString(Mouse_x + 30, Mouse_y + 27, "Check", GetColor(0, 0, 0));
				ScreenFlip();
				while ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {}
				while ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {}

				while ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
					i = Mouse_x;
					j = Mouse_y;
					GetMousePoint(&Mouse_x, &Mouse_y);
					if (i + 20 < Mouse_x && Mouse_x < i + 80 && j - 60 < Mouse_y && Mouse_y < j)
					{
						map[m_x % 10 + 1][m_y % 10 + 1][m_z % 10 + 1] = 0;
						if (bomlist[m_x % 10 + 1][m_y % 10 + 1][m_z % 10 + 1] == 1)does = 0;
					}
					GetMousePoint(&Mouse_x, &Mouse_y);
					if (i + 20 < Mouse_x && Mouse_x < i + 80 && j + 5 < Mouse_y && Mouse_y < j + 65)
					{
						if (map[m_x % 10 + 1][m_y % 10 + 1][m_z % 10 + 1] == 3)
							map[m_x % 10 + 1][m_y % 10 + 1][m_z % 10 + 1] = 1;
						else map[m_x % 10 + 1][m_y % 10 + 1][m_z % 10 + 1] = 3;
					}
				}
			}
			m = 0;
			for (i = 1; i <= size; i++)                  //  1ずらす
			{
				for (j = 1; j <= size; j++)
				{
					for (k = 1; k <= size; k++)
					{
						if (map[i][j][k] != 0 && bomlist[i][j][k] == 0)
							m++;

					}
				}
			}
			if (m == 0)does = 3;

			if (CheckHitKey(KEY_INPUT_0) == 1) { break; }
		}

		if (does == 0) {
			for (i = 0; i < 30; i++) {
				SetDrawScreen(DX_SCREEN_BACK);
				DrawCircle(GetRand(320) + 150, GetRand(300) + 150, GetRand(70) + 70, GetColor(GetRand(100) + 150, GetRand(100) + 150, GetRand(100) + 150), TRUE);
				ScreenFlip();
				WaitTimer(10);
			}
			DrawString(250, 250, "GAME OVER!!", GetColor(250, 250, 250)); ScreenFlip();
		}

		if (does == 3) {
			DrawString(250, 250, "GAME CLEAR!!", GetColor(0, 250, 0)); ScreenFlip();
		}

		WaitKey();				// キー入力待ち
	} while (does != 1);

















	//WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
