void ip_swap_to_dec(unsigned int *p,char x[])
{
	int i, m;
	*p = x[32] - '0';
	for (i = 1, m = 30; i <= 32; i++, m--)
		*p += (x[i] - '0') * (2 << m);//利用位运算将二进制IP地址转换为十进制
}