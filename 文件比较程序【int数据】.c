/*�ļ��Ƚϳ���int���ݡ�*/


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	FILE* fp1, * fp2;
	int x1, x2, line = 0, count = 0;
	char file1[9855], file2[9854];
	puts("��������Ҫ�Ƚϵ��ļ�1������·�����������ţ���");
	gets(file1);
	puts("��������Ҫ�Ƚϵ��ļ�2������·�����������ţ���");
	gets(file2);
	fp1 = fopen(file1, "r");
	fp2 = fopen(file2, "r");
	while ((fscanf(fp1, "%d", &x1)) != EOF)
	{
		fscanf(fp2, "%d", &x2);
		if (x1 != x2)
		{
			printf("Differences on Line %d\n", line);
			count++;
		}
		line++;
	}
	if (count == 1)printf("Total: %d different line.\n", count);
	else if (count > 1)printf("Total: %d different lines.\n", count);
	else if (!count)printf("Total: %d different line.\nThe two files are the same!\n", count);
	fclose(fp1);
	fclose(fp2);
	system("pause");
	return 0;
}