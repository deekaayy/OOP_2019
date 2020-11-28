#include "pch.h"
#include <iostream>
using namespace std;
int main()
{
	/*char a[100], b[100];
	int br=0;
	cout << "First array: ";
	cin >> a;

	cout << "Second array: ";
		cin >> b;
	for (int i = 0; a[i]!='\0'; i++)
	{
		bool flag = true;
		for (int j = 0; b[j]!='\0'; j++)
		{
			if (a[i+j]==b[j])
			{
				flag = true;
			}
			else
			{
				flag = false; break;
			}
			
		}
		if (flag == true)
		{
			br++;
		}

	}
	cout << "Number of times: " << br << endl;
	*/


	///////////////////////////////////////task 2
	
	char a[100][100];
	int columns, rows, br1 = 0, br2=0, br3=0;
	cout << "Input nxm matrix: ";
	cin >> columns >> rows;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cin >> a[i][j];
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	int x = 0, y = 0, temp1=0, temp2=0;
	do
	{
		if (columns - x >= 0 && rows - y >= 0)
		{
			switch (a[temp1 + y][temp2 + x])
			{
			case '@':
				br1++; break;
			case '&':
				br2++; break;
			case 'x':
				br3++; break;
			}
		}
		else
			cout << "Outside of bonds!" << endl;
		cout << "Input the command: ";
		cin >> x >> y;
		cout << "Position: " << temp1 + x << "," << temp2 + y << endl;
		temp1 += x;
		temp2 += x;
	} while ((temp1 != -1 ||temp1 != -1));
	cout << "@: " << br1 << " times." << endl << "&: " << br2 << " times." << endl << "x: " << br3 << " times." << endl;

}

