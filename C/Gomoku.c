/*
게임 : 오목
개발자 : 이동건 gnyontu39@gmail.com

게임 대강 구조
판:
┌┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┐
├┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┤
├┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┤
├┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┤
├┼┼┼┼┼┼┼┼●┼┼┼●┼┼┼┼┼┤
├┼┼┼┼※┼┼┼●┼┼●┼┼┼┼┼┼┤
├┼┼┼┼┼┼┼┼●┼●┼┼┼┼┼┼┼┤
├┼┼┼┼┼┼┼┼●●┼┼┼┼┼┼┼┼┤
├┼┼┼┼┼┼┼○●●●●●┼┼┼┼┼┤
├┼┼┼┼┼┼┼┼┼●┼┼┼┼┼┼┼┼┤
├┼┼┼┼┼┼┼┼┼┼●┼┼┼┼┼┼┼┤
├┼┼┼┼┼┼┼┼┼┼┼●┼┼┼┼┼┼┤
├┼┼┼┼┼┼┼┼┼┼┼┼●┼┼┼┼┼┤
├┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┤
├┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┤
├┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┤
└┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┘
모양 : ○●
*/

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

/*
	함수
*/

void frame(int, int, int **map);	//오목판 위에 있는 값의 원래의 모양으로 변경해주는 함수
void gotoxy(int, int);				//화면을 좌표로 표시하는 함수
void frame_reset(int **map);		//게임을 초기화하는 함수
void move(char key, int **map);		//사용자가 움직임을 인식하는 함수.
void gameSystem(int **map);			//오목 시스템의 핵심 함수

/*
	인터페이스의 색깔을 선언하는 부분
*/

#define col GetStdHandle(STD_OUTPUT_HANDLE)
#define RED SetConsoleTextAttribute(col,0x000f)
#define YELLOW SetConsoleTextAttribute(col,0x0006)
#define WHITE  SetConsoleTextAttribute(col,0x0005)

/*
	게임 시스템에 필요한 것들
*/

int npx, npy,mapx,mapy; //오목판의 크기를 정하거나, 포인터의 위치를 나타내는 변수
int HP;					//지금 움직이는 플레이어를 결정함
int GameState;			//게임의 상태를 알려줌.

int main()
{
	do
	{
		int **map;
		system("cls");
		YELLOW; printf("Do you want play games?(Yes - 1 │ No - 0)\n");		//게임을 시작하겠습니까?
		scanf("%d", &GameState);
		if (GameState !=0)
		{
			printf("Can you setting about Size?(ex - 40 23)\n");			//오목판의 크기를 정해주세요
			scanf("%d" "%d", &mapx, &mapy);
			map = (int**)malloc(sizeof(int*)*(mapx+1));						//행을 동적할당한다.
			for (int i = 0; i < mapx+1; i++)								//행에 대한 열을 동적할당한다.
			{
				map[i] = (int*)malloc(sizeof(int*)* (mapy+1));
			}
			frame_reset(map);												//오목판을 초기화한다.
			while (GameState!=2)
			{
				move(getch(), map);
			}
			free(map);
		}
	} while (GameState != 0);
	
}

void move(char key,int **map)
{
	frame(npx, npy, map);									//이동하기 전에 해당 지점의 원래 부분으로 복구한다.
	switch (key)
	{
	case'w':
		npy--;
		break;
	case's':
		npy++;
		break;
	case'a':
		npx--;
		break;
	case'd':
		npx++;
		break;
	case' ':
		if (map[npx][npy] != 7 && map[npx][npy] != 8)		//스페이스바의 값을 얻게 되면 그 부분에 바둑알을 입력
		{
			if (HP == 0)
			{
				map[npx][npy] = 8;
				HP++;
			}
			else
			{
				map[npx][npy] = 7;
				HP--;
			}
			gameSystem(map);
		}
		break;
	case'p':												//게임을 중지하고 초기화면으로 넘어간다.
		gotoxy(0, mapy / 2);
		GameState = 2;
		break;
	}
	if (GameState != 2)
	{
		if (npx >= mapx)
		{
			npx--;
		}
		if (npx < 0)
		{
			npx++;
		}
		if (npy < 0)
		{
			npy++;
		}
		if (npy >= mapy)
		{
			npy--;
		}
		gotoxy(npx * 2, npy);
		if (HP == 0)
		{
			YELLOW; printf("※");
		}
		else
		{
			RED; printf("※");
		}
	}
}

void frame_reset(int **map)
{
	HP = 0;
	for (int i = 0; i < mapx;i++)
	{
		for (int j = 0; j < mapy; j++)
		{
			map[i][j] = 0;
		}
	}
	npx = mapx / 2;
	npy = mapy / 2;
	map[0][0] = 3;
	map[mapx - 1][0] = 4;
	map[0][mapy - 1] = 5;
	map[mapx - 1][mapy - 1] = 6;
	for (int i = 1; i < mapx-1; i++)
	{
		map[i][0] = 1;
		map[i][mapy - 1] = 10;
	}
	for (int i = 1; i < mapy - 1; i++)
	{
		map[0][i] = 2;
		map[mapx - 1][i] = 9;
	}
	for (int i = 0; i < mapx; i++)
	{
		for (int j = 0; j < mapy; j++)
		{
			gotoxy(i * 2, j);
			WHITE;
			switch (map[i][j])
			{
			case 0:
				printf("┼");
				break;
			case 1:
				printf("┬");
				break;
			case 2:
				printf("├");
				break;
			case 3:
				printf("┌");
				break;
			case 4:
				printf("┐");
				break;
			case 5:
				printf("└");
				break;
			case 6:
				printf("┘");
				break;
			case 9:
				printf("┤");
				break;
			case 10:
				printf("┴");
				break;
			}
		}
		printf("\n");
	}
}
void frame(int i, int j, int **map)
{
	gotoxy(i*2, j);
	WHITE;
	switch (map[i][j])
	{
	case 0:
		printf("┼");
		break;
	case 1:
		printf("┬");
		break;
	case 2:
		printf("├");
		break;
	case 3:
		printf("┌");
		break;
	case 4:
		printf("┐");
		break;
	case 5:
		printf("└");
		break;
	case 6:
		printf("┘");
		break;
	case 7:
		RED; printf("●");
		break;
	case 8:
		YELLOW; printf("●");
		break;
	case 9:
		printf("┤");
		break;
	case 10:
		printf("┴");
		break;
	}
}

void gotoxy(int x, int y)
{
	COORD XY = { x, y };
	HANDLE hHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hHandle, XY);
}

void gameSystem(int **map)
{
	int Count=0;
	for (int i=0; i < mapx; i++)
	{
		for (int j=0; j < mapy; j++)
		{
			int k;
			if (map[i][j] == 7 || map[i][j] == 8)
			{
				if (map[i][j] == 7)
				{
					k = 7;
				}
				else if (map[i][j] == 8)
				{
					k = 8;
				}
				if ((map[i + 1][j] == k && map[i + 2][j] == k && map[i + 3][j] == k && map[i + 4][j] == k) || (map[i][j + 1] == k && map[i][j + 2] == k && map[i][j + 3] == k && map[i][j + 4] == k) || (map[i + 1][j + 1] == k && map[i + 2][j + 2] == k && map[i + 3][j + 3] == k && map[i + 4][j + 4] == k) || (map[i + 1][j - 1] == k && map[i + 2][j - 2] == k && map[i + 3][j - 3] == k && map[i + 4][j - 4] == k))
				{
					GameState = 2;
					gotoxy(mapx-5,mapy/2);
					RED; printf("%d Player Win!!!", k - 6);
					Sleep(3000);
				}
			}
			else
			{
				Count++;
			}
		}
	}
	if (Count ==0)
	{
		GameState = 2;
		gotoxy(mapx - 5, mapy / 2);
		RED; printf("All Player draw !!!");
		Sleep(3000);
	}
}