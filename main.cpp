#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IP地址转换【点分十进制→二进制】.cpp"
#include "IP地址转换【CIDR表示法→IP地址块上下限】.cpp"
#include "协议号转换【十六进制→十进制】.cpp"
#include "按顺序进行规则匹配.cpp"
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
	char input[9854] = {};//存储数据来源文件的完整路径
	char output[9855] = {};//存储数据输出文件的完整路径
	int i, count;
	unsigned int ip0, ip1, d0, d1, x;

	/*===为了方便调试，暂时将文件路径直接写进代码
	cout << "请输入数据来源文件的完整路径：" << endl;
	gets_s(input);
	cout << "请输入数据输出文件的完整路径：" << endl;
	gets_s(output);
	fp_rule = fopen(input, "r");//“r”表示以只读模式打开文件
	fp_out = fopen(output, "w+");//“w+”表示打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
	*/
	
	fp_rule = fopen("F:\\Visual Studio\\C++ Source\\2022面向对象程序设计（福州大学）寒假作业2\\dataset1\\rule1.txt", "r");//“r”表示以只读模式打开文件
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
		ip_swap_to_bin(p->ip01, p->ip02, p->ip03, p->ip04, p->ip0bin);//将源IP地址转换为二进制形式储存到链表相应的字符数组中
		ip_swap_to_bin(p->ip11, p->ip12, p->ip13, p->ip14, p->ip1bin);//将目的IP地址转换为二进制形式储存到链表相应的字符数组中
		CIDR_ip_swap_to_max_and_min(p->ip0bin, p->ip0wei, &p->ip0max, &p->ip0min);//将源IP地址的CIDR地址块的最大IP地址和最小IP地址分别用十进制表示方式存储在链表的相应变量中
		CIDR_ip_swap_to_max_and_min(p->ip1bin, p->ip1wei, &p->ip1max, &p->ip1min);//将目的IP地址的CIDR地址块的最大IP地址和最小IP地址分别用十进制表示方式存储在链表的相应变量中
		xieyi_swap_to_dec(&p->x0, &p->x1, p->z0, p->z1);//将协议号上下范围分别转换为十进制表示方式存储到链表相应变量中
		/*以下4行代码为建立新链表的过程*/
		prev->next = p;
		p->next = NULL;
		prev = p;
		p = (struct rule*)malloc(sizeof(struct rule));
	}
	fclose(fp_rule);//关闭文件指针对应文件【rule】
	fp_packet = fopen("F:\\Visual Studio\\C++ Source\\2022面向对象程序设计（福州大学）寒假作业2\\dataset1\\packet1.txt", "r");
	fp_out = fopen("F:\\Visual Studio\\C++ Source\\2022面向对象程序设计（福州大学）寒假作业2\\res.txt", "w+");//“w+”表示打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
	while ((fscanf(fp_packet,"%d%d%d%d%d", &ip0, &ip1, &d0, &d1, &x)) != EOF)
	{
		for (p = head->next, count = 0; p; p = p->next)//按建立顺序访问链表
		{
			if (rule_match(ip0, ip1, d0, d1, x, p->ip0min, p->ip0max, p->ip1min, p->ip1max, p->d01, p->d02, p->d11, p->d12, p->x0, p->x1))
			{
				fprintf(fp_out, "%d\n", count);
				break;
			}
			count++;//计数器，表示当前为第几条规则【规则从0开始编号】
		}
	}
	fclose(fp_out);//关闭文件指针对应文件【res】
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
	return 0;
}