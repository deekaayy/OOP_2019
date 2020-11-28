#include "pch.h"
#include <iostream>
using namespace std;
int check(char a[][100], int x, int y)
{
	int br = 0;
	if (x - 1 >= 0 && y-1>=0 )
	{
		for (int i = x - 1; i <= x + 1; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				if ((int)a[i][j] == 52)
				{
					br++;
				}
			}
		}
	}
	else if (x == 0 && y == 0)
	{
		for (int i = x; i <= x + 1; i++)
		{
			for (int j = y; j <= y + 1; j++)
			{
				if ((int)a[i][j] == 52)
				{
					br++;
				}
			}
		}
	}
	if (br >= 3)
	{
		return 51;
	}
	else
	{
		return 52;
	}
}
int main()
{
	int m, n, years;
	char a[100][100], b[100][100];
	cout << "Enter the range of the forest mxn: ";
	cin >> n >> m;
	cout << "Input the forest: "<<endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> a[i][j];
		}
	}
	cout << "Input the years: ";
	cin >> years;
	if (years >= 10)
	{
		for (int k = 1; k <= (years / 10); k++)
		{
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < n; j++)
				{
					int temp = a[i][j];
					if (temp >= 48 && temp <= 57)
					{
						switch (temp)
						{
						case 49:
							b[i][j] = 50; break;
						case 50:
							b[i][j] = 51; break;
						case 51:
							b[i][j] = 52; break;
						case 52:
						{
							b[i][j]=check(a,i,j); break;
						}
						}
					}
					else if (temp == 82 || temp == 114 || temp == 83 || 115)
					{
						b[i][j] = (char)temp;
					}
					a[i][j] = (char)b[i][j];
				}
			}
		}
		cout << "forest: " << endl;
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << (char)b[i][j] << " ";
			}
			cout << endl;
		}
	}
	else
	{
		cout << "forest: " << endl;
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << (char)a[i][j] << " ";
			}
			cout << endl;
		}
	}
}
