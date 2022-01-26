#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IP��ַת�������ʮ���ơ������ơ�.cpp"
#include "IP��ַת����CIDR��ʾ����IP��ַ�������ޡ�.cpp"
#include "Э���ת����ʮ�����ơ�ʮ���ơ�.cpp"
#include "��˳����й���ƥ��.cpp"
using namespace std;

struct rule
{
	char z0[3], z1[3];
	char ip0bin[37], ip1bin[37];
	unsigned int ip0min, ip0max, ip1min, ip1max;
	int ip01,ip02,ip03,ip04,ip0wei;
	int ip11,ip12,ip13,ip14,ip1wei;
	int d01, d02, d11, d12, x0, x1;
	struct rule* next;
};

int main()
{
	FILE* fp_rule, * fp_out, * fp_packet;
	struct rule* head, * p, * prev, * current;
	char input[9854] = {};//�洢������Դ�ļ�������·��
	char output[9855] = {};//�洢��������ļ�������·��
	int i, count;
	unsigned int ip0, ip1, d0, d1, x;

	/*===Ϊ�˷�����ԣ���ʱ���ļ�·��ֱ��д������
	cout << "������������Դ�ļ�������·����" << endl;
	gets_s(input);
	cout << "��������������ļ�������·����" << endl;
	gets_s(output);
	fp_rule = fopen(input, "r");//��r����ʾ��ֻ��ģʽ���ļ�
	fp_out = fopen(output, "w+");//��w+����ʾ�򿪿ɶ�д�ļ������ļ��������ļ�������Ϊ�㣬�����ļ����ݻ���ʧ�����ļ��������������ļ���
	*/
	
	fp_rule = fopen("F:\\Visual Studio\\C++ Source\\2022������������ƣ����ݴ�ѧ��������ҵ2\\dataset1\\rule1.txt", "r");//��r����ʾ��ֻ��ģʽ���ļ�
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
		ip_swap_to_bin(p->ip01, p->ip02, p->ip03, p->ip04, p->ip0bin);//��ԴIP��ַת��Ϊ��������ʽ���浽������Ӧ���ַ�������
		ip_swap_to_bin(p->ip11, p->ip12, p->ip13, p->ip14, p->ip1bin);//��Ŀ��IP��ַת��Ϊ��������ʽ���浽������Ӧ���ַ�������
		CIDR_ip_swap_to_max_and_min(p->ip0bin, p->ip0wei, &p->ip0max, &p->ip0min);//��ԴIP��ַ��CIDR��ַ������IP��ַ����СIP��ַ�ֱ���ʮ���Ʊ�ʾ��ʽ�洢���������Ӧ������
		CIDR_ip_swap_to_max_and_min(p->ip1bin, p->ip1wei, &p->ip1max, &p->ip1min);//��Ŀ��IP��ַ��CIDR��ַ������IP��ַ����СIP��ַ�ֱ���ʮ���Ʊ�ʾ��ʽ�洢���������Ӧ������
		xieyi_swap_to_dec(&p->x0, &p->x1, p->z0, p->z1);//��Э������·�Χ�ֱ�ת��Ϊʮ���Ʊ�ʾ��ʽ�洢��������Ӧ������
		/*����4�д���Ϊ����������Ĺ���*/
		prev->next = p;
		p->next = NULL;
		prev = p;
		p = (struct rule*)malloc(sizeof(struct rule));
	}
	fclose(fp_rule);//�ر��ļ�ָ���Ӧ�ļ���rule��
	fp_packet = fopen("F:\\Visual Studio\\C++ Source\\2022������������ƣ����ݴ�ѧ��������ҵ2\\dataset1\\packet1.txt", "r");
	fp_out = fopen("F:\\Visual Studio\\C++ Source\\2022������������ƣ����ݴ�ѧ��������ҵ2\\res.txt", "w+");//��w+����ʾ�򿪿ɶ�д�ļ������ļ��������ļ�������Ϊ�㣬�����ļ����ݻ���ʧ�����ļ��������������ļ���
	while ((fscanf(fp_packet,"%d%d%d%d%d", &ip0, &ip1, &d0, &d1, &x)) != EOF)
	{
		for (p = head->next, count = 0; p; p = p->next)//������˳���������
		{
			if (rule_match(ip0, ip1, d0, d1, x, p->ip0min, p->ip0max, p->ip1min, p->ip1max, p->d01, p->d02, p->d11, p->d12, p->x0, p->x1))
			{
				fprintf(fp_out, "%d\n", count);
				break;
			}
			count++;//����������ʾ��ǰΪ�ڼ������򡾹����0��ʼ��š�
		}
	}
	fclose(fp_out);//�ر��ļ�ָ���Ӧ�ļ���res��
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
	return 0;
}