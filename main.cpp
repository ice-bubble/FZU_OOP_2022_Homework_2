#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "IP��ַƥ��.cpp"
using namespace std;

int main()
{
	FILE* fp_rule, * fp_out;
	char z[9854] = {};
	char input[2022] = {};//�洢������Դ�ļ�������·��
	char output[2022] = {};//�洢��������ļ�������·��
	int ip01,ip02,ip03,ip04,ip0wei;
	int ip11,ip12,ip13,ip14,ip1wei;
	int d01, d02, d11, d12;
	int count = 0;

	/*===Ϊ�˷�����ԣ���ʱ���ļ�·��ֱ��д������
	cout << "������������Դ�ļ�������·����" << endl;
	gets_s(input);
	cout << "��������������ļ�������·����" << endl;
	gets_s(output);
	fp_rule = fopen(input, "r");//��r����ʾ��ֻ��ģʽ���ļ�
	fp_out = fopen(output, "w+");//��w+����ʾ�򿪿ɶ�д�ļ������ļ��������ļ�������Ϊ�㣬�����ļ����ݻ���ʧ�����ļ��������������ļ���
	*/

	fp_rule = fopen("F:\\Visual Studio\\C++ Source\\2022������������ƣ����ݴ�ѧ��������ҵ2\\dataset1\\rule1.txt", "r");
	fp_out = fopen("F:\\Visual Studio\\C++ Source\\2022������������ƣ����ݴ�ѧ��������ҵ2\\test_out.txt", "w+");
	while ((fscanf(fp_rule, "@%d%*c%d%*c%d%*c%d%*c%d", &ip01, &ip02, &ip03, &ip04, &ip0wei)) != EOF)//���ļ��а��ж�ȡ��Ӧ�������ݣ�EOF��ʾ��ȡ���ļ�ĩβ�����ѭ��
	{
		fscanf(fp_rule, "%d%*c%d%*c%d%*c%d%*c%d", &ip11, &ip12, &ip13, &ip14, &ip1wei);
		fscanf(fp_rule, "%d%*c%*c%*c%d", &d01, &d02);
		fscanf(fp_rule, "%d%*c%*c%*c%d", &d11, &d12);
		fscanf(fp_rule, "%*c%*c%*c%c%c%*c%*c%*c%c%c%*c", &z[0], &z[1], &z[2], &z[3]);
		count++;

		fprintf(fp_out, "%d %d %d %d %d\t", ip01, ip02, ip03, ip04, ip0wei);//����Ӧ��������������ļ�
		fprintf(fp_out, "%d %d %d %d %d\t", ip11, ip12, ip13, ip14, ip1wei);
		fprintf(fp_out, "%d : %d\t%d : %d\t", d01, d02, d11, d12);
		fprintf(fp_out, "0x%c%c/0x%c%c\n", z[0], z[1], z[2], z[3]);
	}
	fclose(fp_rule);//�ر��ļ�ָ���Ӧ�ļ�
	fclose(fp_out);
	system("pause");
	return 0;
}