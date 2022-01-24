void ip_swap_to_bin(int ip1, int ip2, int ip3, int ip4, char ip_bin[])
{
	char* pt;
	for (pt = ip_bin + 32; ip4; ip4 /= 2, pt--)
		*pt = ip4 % 2 + '0';
	if (pt != ip_bin + 24)
		for (; pt > ip_bin + 24; pt--)
			*pt = '0';
	for (; ip3; ip3 /= 2, pt--)
		*pt = ip3 % 2 + '0';
	if (pt != ip_bin + 16)
		for (; pt > ip_bin + 16; pt--)
			*pt = '0';
	for (; ip2; ip2 /= 2, pt--)
		*pt = ip2 % 2 + '0';
	if (pt != ip_bin + 8)
		for (; pt > ip_bin + 8; pt--)
			*pt = '0';
	for (; ip1; ip1 /= 2, pt--)
		*pt = ip1 % 2 + '0';
	if (pt != ip_bin)
		for (; pt > ip_bin; pt--)
			*pt = '0';
}