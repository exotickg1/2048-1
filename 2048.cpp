/*************************************************************************
	> File Name: 2048.cpp
	> Author: wilson_91
	> Mail: wilson_91@qq.com 
	> Created Time: Thu 20 Mar 2014 08:53:41 PM CST
 ************************************************************************/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <conio.h>

using namespace std;

enum movDirection{LEFT = 4,UP = 8,RIGHT = 6,DOWN = 2};

int main()
{
	//棋盘表格，用来存储显示的数字
	int grid[5][5] = {0};
	bool flag = true;
	
	//初始化棋盘2,4位置
	srand(time(0));
	int x0 = rand()%4 + 1;
	int y0 = rand()%4 + 1;
	int x1 = rand()%4 + 1;
	int y1 = rand()%4 + 1;

	grid[x0][y0] = rand()%2 ?2:4;
	grid[x1][y1] = rand()%2 ?4:2;
	//当棋盘还能移动的时候，循环执行
	//否则，退出循环
	int motion;
	bool skipMotion;
	while(flag)
	{
		//打印之前应该先清空控制台
		system("cls");
		skipMotion = false;
		//system("clear");//for linux version
		for (int i = 1;i < 5;i++)
		{
			//cout << "---";
			cout.fill('-');
			for (int j = 1;j < 5;j++)
			{
				cout << setw(10) << grid[i][j];// << "---";
			}
			cout << endl;
		}
		//用getchar或input替换
		//cin >> motion;
		motion = getch() - 48;
		switch (motion)
		{
		case LEFT:
			for (int i = 1;i < 5;i++)
			{
				bool posAva[5] = {true,true,true,true,true};
				for (int j = 2;j < 5;j++)
				{
					int temp = j;
					while(--temp > 0 && grid[i][temp] == 0);
					if (temp == 0)
					{
						grid[i][1] = grid[i][j];
						grid[i][j] = 0;
						continue;
					}
					if (grid[i][temp] != 0)
					{
						if (grid[i][j] == grid[i][temp] && posAva[temp])
						{
							grid[i][temp] *=2;
							grid[i][j] = 0;
							posAva[temp] = false;
						}

						if (temp + 1 != j)
						{
							grid[i][temp+1] = grid[i][j];
							grid[i][j] = 0;
						}
						
						continue;
					}
				}
			}
			break;
		case UP:
			for (int j = 1;j < 5;j++)
			{
				bool posAva[5] = {true,true,true,true,true};
				for (int i = 2;i < 5;i++)
				{
					int temp = i;
					while(--temp > 0 && grid[temp][j] == 0);
					if (temp == 0)
					{
						grid[1][j] = grid[i][j];
						grid[i][j] = 0;
						continue;
					}
					if (grid[temp][j] != 0)
					{
						if (grid[i][j] == grid[temp][j] && posAva[temp])
						{
							grid[temp][j] *=2;
							grid[i][j] = 0;
							posAva[temp] = false;
							continue;
						}

						if (temp + 1 != i)
						{
							grid[temp+1][j] = grid[i][j];
							grid[i][j] = 0;
						}
						
						continue;
					}
				}
			}
			break;
		case RIGHT:
			for (int i = 1;i < 5;i++)
			{
				bool posAva[5] = {true,true,true,true,true};
				for (int j = 3;j > 0;j--)
				{
					int temp = j;
					while(++temp < 5 && grid[i][temp] == 0);
					if (temp == 5)
					{
						grid[i][4] = grid[i][j];
						grid[i][j] = 0;
						continue;
					}
					if (grid[i][temp] != 0)
					{
						if (grid[i][j] == grid[i][temp] && posAva[temp])
						{
							grid[i][temp] *=2;
							grid[i][j] = 0;
							posAva[temp] = false;
						}

						if (temp - 1 != j)
						{
							grid[i][temp-1] = grid[i][j];
							grid[i][j] = 0;
						}
						
						continue;
					}
				}
			}
			break;
		case DOWN:
			for (int j = 1;j < 5;j++)
			{
				bool posAva[5] = {true,true,true,true,true};
				for (int i = 3;i > 0;i--)
				{
					int temp = i;
					while(++temp < 5 && grid[temp][j] == 0);
					if (temp == 5)
					{
						grid[4][j] = grid[i][j];
						grid[i][j] = 0;
						continue;
					}
					if (grid[temp][j] != 0)
					{
						if (grid[i][j] == grid[temp][j] && posAva[temp])
						{
							grid[temp][j] *=2;
							grid[i][j] = 0;
							posAva[temp] = false;
							continue;
						}
						
						if (temp - 1 != i)
						{
							grid[temp-1][j] = grid[i][j];
							grid[i][j] = 0;
						}
						
						continue;
					}
				}
			}
			break;
		default:
			skipMotion = true;
			break;
		}
		if(skipMotion) continue;
		//添加一个新值到数组中
		//method one：
		int newValue = rand()%2?4:2;
		int zeroNums = 0;
		for (int i = 1;i < 5;i++)
		{
			for (int j = 1;j < 5;j++)
			{
				if (!grid[i][j])
				{
					zeroNums++;
				}
			}
		}
		//无0值情况还未考虑
		if (zeroNums)
		{
			int inserPos = rand()%zeroNums;
			bool breakflag = false;
			for (int i = 1;i < 5;i++)
			{
				for (int j = 1;j < 5;j++)
				{
					if (!grid[i][j] && !inserPos--)
					{
						grid[i][j] = newValue;
						breakflag = true;
						break;
					}
				}
				if (breakflag)
					break;
			}
		}
		
		//method two:
		////////
		//////////////////////////////////////////////////////////////////////////

		//判断棋盘是否还有可移动空间，并进行相应处理
		flag = false;
		for (int i = 1;i < 5;i++)
		{
			for (int j = 1;j < 5; j++)
			{
				//如果数组值为零的话，则说明还有空格，必定可以移动
				if(grid[i][j] == 0)
				{
					flag = true;
					break;
				}
				//只要当前数字和其有邻居或和其下邻居相等则必定存在可可移动空间
				if (((i + 1 < 5) && (grid[i][j] == grid[i+1][j]))||(j + 1 < 5) && (grid[i][j] == grid[i][j+1]))
				{
					flag = true;
					break;
				}
			}
			if(flag == true)
				break;
		}
	}
	for (int i = 1;i < 5;i++)
	{
		cout << "---";
		for (int j = 1;j < 5;j++)
		{
			cout << grid[i][j] << "---";
		}
		cout << endl;
	}
	cout << "oops....try more hard next time!" << endl;
	system("pause");
	return 0;
}
