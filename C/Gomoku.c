/*
���� : ����
������ : �̵��� gnyontu39@gmail.com

���� �밭 ����
��:
����������������������������������������
����������������������������������������
����������������������������������������
����������������������������������������
�������������������ܦ������ܦ�����������
�����������ئ������ܦ����ܦ�������������
�������������������ܦ��ܦ���������������
�������������������ܡܦ�����������������
�����������������ۡܡܡܡܡܦ�����������
���������������������ܦ�����������������
�����������������������ܦ���������������
�������������������������ܦ�������������
���������������������������ܦ�����������
����������������������������������������
����������������������������������������
����������������������������������������
����������������������������������������
��� : �ۡ�
*/

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

/*
	�Լ�
*/

void frame(int, int, int **map);	//������ ���� �ִ� ���� ������ ������� �������ִ� �Լ�
void gotoxy(int, int);				//ȭ���� ��ǥ�� ǥ���ϴ� �Լ�
void frame_reset(int **map);		//������ �ʱ�ȭ�ϴ� �Լ�
void move(char key, int **map);		//����ڰ� �������� �ν��ϴ� �Լ�.
void gameSystem(int **map);			//���� �ý����� �ٽ� �Լ�

/*
	�������̽��� ������ �����ϴ� �κ�
*/

#define col GetStdHandle(STD_OUTPUT_HANDLE)
#define RED SetConsoleTextAttribute(col,0x000f)
#define YELLOW SetConsoleTextAttribute(col,0x0006)
#define WHITE  SetConsoleTextAttribute(col,0x0005)

/*
	���� �ý��ۿ� �ʿ��� �͵�
*/

int npx, npy,mapx,mapy; //�������� ũ�⸦ ���ϰų�, �������� ��ġ�� ��Ÿ���� ����
int HP;					//���� �����̴� �÷��̾ ������
int GameState;			//������ ���¸� �˷���.

int main()
{
	do
	{
		int **map;
		system("cls");
		YELLOW; printf("Do you want play games?(Yes - 1 �� No - 0)\n");		//������ �����ϰڽ��ϱ�?
		scanf("%d", &GameState);
		if (GameState !=0)
		{
			printf("Can you setting about Size?(ex - 40 23)\n");			//�������� ũ�⸦ �����ּ���
			scanf("%d" "%d", &mapx, &mapy);
			map = (int**)malloc(sizeof(int*)*(mapx+1));						//���� �����Ҵ��Ѵ�.
			for (int i = 0; i < mapx+1; i++)								//�࿡ ���� ���� �����Ҵ��Ѵ�.
			{
				map[i] = (int*)malloc(sizeof(int*)* (mapy+1));
			}
			frame_reset(map);												//�������� �ʱ�ȭ�Ѵ�.
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
	frame(npx, npy, map);									//�̵��ϱ� ���� �ش� ������ ���� �κ����� �����Ѵ�.
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
		if (map[npx][npy] != 7 && map[npx][npy] != 8)		//�����̽����� ���� ��� �Ǹ� �� �κп� �ٵϾ��� �Է�
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
	case'p':												//������ �����ϰ� �ʱ�ȭ������ �Ѿ��.
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
			YELLOW; printf("��");
		}
		else
		{
			RED; printf("��");
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
				printf("��");
				break;
			case 1:
				printf("��");
				break;
			case 2:
				printf("��");
				break;
			case 3:
				printf("��");
				break;
			case 4:
				printf("��");
				break;
			case 5:
				printf("��");
				break;
			case 6:
				printf("��");
				break;
			case 9:
				printf("��");
				break;
			case 10:
				printf("��");
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
		printf("��");
		break;
	case 1:
		printf("��");
		break;
	case 2:
		printf("��");
		break;
	case 3:
		printf("��");
		break;
	case 4:
		printf("��");
		break;
	case 5:
		printf("��");
		break;
	case 6:
		printf("��");
		break;
	case 7:
		RED; printf("��");
		break;
	case 8:
		YELLOW; printf("��");
		break;
	case 9:
		printf("��");
		break;
	case 10:
		printf("��");
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