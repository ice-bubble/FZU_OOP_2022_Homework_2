/*���ļ���ȡ���ݺͽ�����������ļ�*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main()
{
	FILE* fp, * out;
	char z[9854] = {};
	char input[2022] = {};//�洢������Դ�ļ�������·��
	char output[2022] = {};//�洢��������ļ�������·��
	int i;
	cout << "������������Դ�ļ�������·����" << endl;
	gets_s(input);
	cout << "��������������ļ�������·����" << endl;
	gets_s(output);
	fp = fopen(input, "r");//��r����ʾ��ֻ��ģʽ���ļ�
	out = fopen(output, "w+");//��w+����ʾ�򿪿ɶ�д�ļ������ļ��������ļ�������Ϊ�㣬�����ļ����ݻ���ʧ�����ļ��������������ļ���
	while ((fscanf(fp, "%s", z)) != EOF)//���ļ��а��ж�ȡ��Ӧ�������ݣ�EOF��ʾ��ȡ���ļ�ĩβ�����ѭ��
	{
		fprintf(out, "%s\n", z);//����Ӧ��������������ļ�
	}
	fclose(fp);//�ر��ļ�ָ���Ӧ�ļ�
	fclose(out);
	system("pause");
	return 0;
}