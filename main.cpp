#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IP地址转换【点分十进制→二进制】.cpp"
#include "IP地址转换【二进制→十进制】.cpp"
using namespace std;

struct rule
{
	char z0[9854] = {};
	char z1[9855] = {};
	char ip0bin[37];
	char ip1bin[37];
	int ip01,ip02,ip03,ip04,ip0wei;
	int ip11,ip12,ip13,ip14,ip1wei;
	int d01, d02, d11, d12;
	struct rule* next;
};

int main()
{
	FILE* fp_rule, * fp_out;
	struct rule* head, * p, * prev, * current;
	char input[2022] = {};//存储数据来源文件的完整路径
	char output[2022] = {};//存储数据输出文件的完整路径
	char* pt;
	int i, count = 0;

	

	/*===为了方便调试，暂时将文件路径直接写进代码
	cout << "请输入数据来源文件的完整路径：" << endl;
	gets_s(input);
	cout << "请输入数据输出文件的完整路径：" << endl;
	gets_s(output);
	fp_rule = fopen(input, "r");//“r”表示以只读模式打开文件
	fp_out = fopen(output, "w+");//“w+”表示打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
	*/
	
	fp_rule = fopen("F:\\Visual Studio\\C++ Source\\2022面向对象程序设计（福州大学）寒假作业2\\dataset1\\rule1.txt", "r");
	fp_out = fopen("F:\\Visual Studio\\C++ Source\\2022面向对象程序设计（福州大学）寒假作业2\\test_out.txt", "w+");

	head = (struct rule*)malloc(sizeof(struct rule));//建立链表头结点
	head->next = NULL;
	prev = head;
	p = (struct rule*)malloc(sizeof(struct rule));
	while ((fscanf(fp_rule, "@%d%*c%d%*c%d%*c%d%*c%d", &p->ip01, &p->ip02, &p->ip03, &p->ip04, &p->ip0wei)) != EOF)//从文件中按行读取相应类型数据，EOF表示读取到文件末尾后结束循环
	{
		fscanf(fp_rule, "%d%*c%d%*c%d%*c%d%*c%d", &p->ip11, &p->ip12, &p->ip13, &p->ip14, &p->ip1wei);
		fscanf(fp_rule, "%d%*c%*c%*c%d", &p->d01, &p->d02);
		fscanf(fp_rule, "%d%*c%*c%*c%d", &p->d11, &p->d12);
		fscanf(fp_rule, "%*c%*c%*c%c%c%*c%*c%*c%c%c%*c", &p->z0[0], &p->z0[1], &p->z1[0], &p->z1[1]);
		for (i = 0; i < 37; i++)//初始化链表字符数组
			p->ip0bin[i] = p->ip1bin[i] = '\0';
		ip_swap_to_bin(p->ip01, p->ip02, p->ip03, p->ip04, p->ip0bin);//将源ip地址转换为二进制形式储存到链表相应的字符数组中
		ip_swap_to_bin(p->ip11, p->ip12, p->ip13, p->ip14, p->ip1bin);//将目的ip地址转换为二进制形式储存到链表相应的字符数组中
		
		/*以下4行代码为建立新链表的过程*/
		prev->next = p;
		p->next = NULL;
		prev = p;
		p = (struct rule*)malloc(sizeof(struct rule));
	}
	for (p = head->next; p; p = p->next)//按建立顺序访问链表
	{
		count++;//计数器，表示当前为第几条规则
		printf("%s\t%s\n", p->ip0bin + 1, p->ip1bin + 1);//输出转换后的二进制ip地址，测试存储数据的准确性
		//system("pause");
	}
	for (p = head; p; head = p->next, free(p))//完成任务，释放访问和连接链表的指针所占用的内存
	{
		p = head;
		if (!p)
		{
			free(p);
			free(head);
			break;
		}
	}
	fclose(fp_rule);//关闭文件指针对应文件
	fclose(fp_out);
	system("pause");
	return 0;
}