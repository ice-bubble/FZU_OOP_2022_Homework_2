#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "IP地址匹配.cpp"
using namespace std;

int main()
{
	FILE* fp_rule, * fp_out;
	char z0[9854] = {};
	char z1[9855] = {};
	char input[2022] = {};//存储数据来源文件的完整路径
	char output[2022] = {};//存储数据输出文件的完整路径
	int ip01, ip02, ip03, ip04, ip0wei;
	int ip11, ip12, ip13, ip14, ip1wei;
	int d01, d02, d11, d12;
	int count = 0;

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
	while ((fscanf(fp_rule, "@%d%*c%d%*c%d%*c%d%*c%d", &ip01, &ip02, &ip03, &ip04, &ip0wei)) != EOF)//从文件中按行读取相应类型数据，EOF表示读取到文件末尾后结束循环
	{
		fscanf(fp_rule, "%d%*c%d%*c%d%*c%d%*c%d", &ip11, &ip12, &ip13, &ip14, &ip1wei);
		fscanf(fp_rule, "%d%*c%*c%*c%d", &d01, &d02);
		fscanf(fp_rule, "%d%*c%*c%*c%d", &d11, &d12);
		fscanf(fp_rule, "%*c%*c%*c%c%c%*c%*c%*c%c%c%*c", &z0[0], &z0[1], &z1[0], &z1[1]);
		count++;

		fprintf(fp_out, "%d.%d.%d.%d/%d\t", ip01, ip02, ip03, ip04, ip0wei);//将相应类型数据输出到文件
		fprintf(fp_out, "%d.%d.%d.%d/%d\t", ip11, ip12, ip13, ip14, ip1wei);
		fprintf(fp_out, "%d : %d\t%d : %d\t", d01, d02, d11, d12);
		fprintf(fp_out, "0x%c%c/0x%c%c\n", z0[0], z0[1], z1[0], z1[1]);
	}
	fclose(fp_rule);//关闭文件指针对应文件
	fclose(fp_out);
	system("pause");
	return 0;
}