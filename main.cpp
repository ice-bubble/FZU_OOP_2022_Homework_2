#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IP��ַת�������ʮ���ơ������ơ�.cpp"
#include "IP��ַת����CIDR��ʾ����IP��ַ�������ޡ�.cpp"
using namespace std;

struct rule
{
	char z0[9854], z1[9855];
	char ip0bin[37], ip1bin[37];
	unsigned int ip0min, ip0max, ip1min, ip1max;
	int ip01,ip02,ip03,ip04,ip0wei;
	int ip11,ip12,ip13,ip14,ip1wei;
	int d01, d02, d11, d12;
	struct rule* next;
};

int main()
{
	FILE* fp_rule, * fp_out;
	struct rule* head, * p, * prev, * current;
	char input[2022] = {};//�洢������Դ�ļ�������·��
	char output[2022] = {};//�洢��������ļ�������·��
	int i, count = 0;

	

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

	head = (struct rule*)malloc(sizeof(struct rule));//��������ͷ���
	head->next = NULL;
	prev = head;
	p = (struct rule*)malloc(sizeof(struct rule));
	while ((fscanf(fp_rule, "@%d%*c%d%*c%d%*c%d%*c%d", &p->ip01, &p->ip02, &p->ip03, &p->ip04, &p->ip0wei)) != EOF)//���ļ��а��ж�ȡ��Ӧ�������ݣ�EOF��ʾ��ȡ���ļ�ĩβ�����ѭ��
	{
		fscanf(fp_rule, "%d%*c%d%*c%d%*c%d%*c%d", &p->ip11, &p->ip12, &p->ip13, &p->ip14, &p->ip1wei);
		fscanf(fp_rule, "%d%*c%*c%*c%d", &p->d01, &p->d02);
		fscanf(fp_rule, "%d%*c%*c%*c%d", &p->d11, &p->d12);
		fscanf(fp_rule, "%*c%*c%*c%c%c%*c%*c%*c%c%c%*c", &p->z0[0], &p->z0[1], &p->z1[0], &p->z1[1]);
		for (i = 0; i < 37; i++)//��ʼ�������ַ�����
			p->ip0bin[i] = p->ip1bin[i] = '\0';
		ip_swap_to_bin(p->ip01, p->ip02, p->ip03, p->ip04, p->ip0bin);//��Դip��ַת��Ϊ��������ʽ���浽������Ӧ���ַ�������
		ip_swap_to_bin(p->ip11, p->ip12, p->ip13, p->ip14, p->ip1bin);//��Ŀ��ip��ַת��Ϊ��������ʽ���浽������Ӧ���ַ�������
		CIDR_ip_swap_to_max_and_min(p->ip0bin, p->ip0wei, &p->ip0max, &p->ip0min);
		CIDR_ip_swap_to_max_and_min(p->ip1bin, p->ip1wei, &p->ip1max, &p->ip1min);
		
		
		/*����4�д���Ϊ����������Ĺ���*/
		prev->next = p;
		p->next = NULL;
		prev = p;
		p = (struct rule*)malloc(sizeof(struct rule));
	}
	for (p = head->next; p; p = p->next)//������˳���������
	{
		count++;//����������ʾ��ǰΪ�ڼ�������
		cout << p->ip0bin + 1 << endl << p->ip0min << "\t" << p->ip0max << endl;
	}
	for (p = head; p; head = p->next, free(p))//��������ͷŷ��ʺ����������ָ����ռ�õ��ڴ�
	{
		p = head;
		if (!p)
		{
			free(p);
			free(head);
			break;
		}
	}
	fclose(fp_rule);//�ر��ļ�ָ���Ӧ�ļ�
	fclose(fp_out);
	system("pause");
	return 0;
}