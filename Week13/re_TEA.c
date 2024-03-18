#include<stdio.h>
int main()
{
	unsigned int enc[] = { 0xC11EE75A, 0xA4AD0973, 0xF61C9018, 0x32E37BCD, 0x2DCC1F26, 0x344380CC };
	unsigned int key[] = { 0x00010203, 0x04050607, 0x08090A0B, 0x0C0D0E0F };
	int i,j;
	long sum,delta=0x61C88647;//0x9e3779b9
	for (i = 0; i < 6; i+=2)
	{
		sum = -(delta * 32);
		for (j = 0; j < 32; j++)
		{
			enc[i+1] -= (((enc[i] >> 5) ^ (16 * enc[i])) + enc[i]) ^ (key[(sum >> 11) & 3] + sum);
			sum += delta;
			enc[i] -= (((enc[i+1] >> 5) ^ (16 * enc[i+1])) + enc[i+1]) ^ (key[sum & 3] + sum);
		}
	}
	printf("%s", enc);
	return 0;
}