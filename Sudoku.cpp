#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;
int a[9][9];//�����洢����
int n; //�����������
int m;//�����Ľ���
int sign = 0;//�ɹ����
FILE* fp1;
FILE* fp2;
bool judge_palace(int x, int row, int col, int key)/*4��6��8��9������Ҫ�Թ������ж� */
{
	int i, j;

	/* bΪx���ڵ�С�Ź����󶥵������� */
	int  b = x / m / row * row;

	/* cΪx���ڵ�С�Ź����󶥵������ */
	int  c = x % m / col * col;
	for (i = b; i < b + row; i++)
	{
		for (j = c; j < c + col; j++)
		{
			if (a[i][j] == key)
			{
				return false;
			}
		}
	}
	return true;
}
bool judge_row_col(int x, int key)/*�ж�������ÿһ��ÿһ���Ƿ��ظ�*/
{
	int row = x / m;
	int col = x % m;
	for (int i = 0; i < m; i++)/*�ж��� */
	{
		if (a[row][i] == key)
		{
			return false;
		}
	}
	for (int i = 0; i < m; i++)/*�ж���*/
	{
		if (a[i][col] == key)
		{
			return false;
		}
	}
	if (m == 4)/*4����*/
	{
		if (judge_palace(x, 2, 2, key))/* ���Ĵ�С2*2 */
		{
			return true;
		}
		return false;

	}
	else if (m == 6)/*6����*/
	{
		if (judge_palace(x, 2, 3, key))/* ���Ĵ�С2*3 */
		{
			return true;
		}
		return false;
	}
	else if (m == 8)/*8����*/
	{
		if (judge_palace(x, 4, 2, key))/* ���Ĵ�С4*2 */
		{
			return true;
		}
		return false;
	}
	else if (m == 9)/*9����*/
	{
		if (judge_palace(x, 3, 3, key))/* ���Ĵ�С3*3 */
		{
			return true;
		}
		return false;
	}
	return true;
}
void print()/*������������д��txt*/
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fprintf(fp2, "%d", a[i][j]);/*д��txt*/
			if (j < m - 1)
			{
				fprintf(fp2, " ");
			}
		}
		fprintf(fp2, "\n");
	}
}

void DFS(int x)/* ���ѹ������� */
{
	if (sign)/*����Ѿ���� ֱ�ӷ���*/
	{
		return;
	}
	if (x == m * m)/* ˵�����еĶ����ϣ����������ϣ��˳��ݹ� */
	{
		print();
		sign = 1;
		return;
	}
	int row = x / m;
	int col = x % m;
	if (a[row][col] != 0)/*��ǰλ�ò�Ϊ�����ж���һ��*/
	{
		DFS(x + 1);
	}
	else
	{
		for (int i = 1; i <= m; i++)
		{
			if (judge_row_col(x, i))
			{
				a[row][col] = i;
				DFS(x + 1);
				/* ������첻�ɹ�����ԭ��ǰλ */
				a[row][col] = 0;
			}
		}
	}
}
int main(int argc, char* argv[])
{

	m = atoi(argv[2]);/*��������*/
	n = atoi(argv[4]);/*��������������*/
	char* inputfile = argv[6];/*������ļ���������m3n5.txt*/
	char* outputfile = argv[8];/*������ļ���������out35.txt*/
	fp1 = fopen(inputfile, "r");/*�������ļ�*/
	if (fp1 == NULL)/*����ļ������ڣ����ش���*/
	{
		return -1;
	}
	fp2 = fopen(outputfile, "w");/*������ļ�*/
	if (fp2 == NULL) /*����ļ������ڣ����ش���*/
	{
		return -1;
	}
	fclose(fp2);
	while (n--)/*���ζ�ȡ�����ļ��е�����*/
	{
		int i, j;
		memset(a, 0, sizeof(a));
		sign = 0;
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < m; j++)
			{
				fscanf(fp1, "%d", &a[i][j]);/*��ȡ����*/
			}
		}
		fp2 = fopen(outputfile, "a");/*������ļ�*/
		DFS(0);
		if (n > 0)
		{
			fprintf(fp2, "\n");/*д��������ļ�*/

		}
		fclose(fp2);/*�ر�����ļ�*/
	}
	fclose(fp1);/*�ر������ļ�*/
	return 0;
}
