#include <stdio.h>
#include <math.h>

int slen(char* s)
{
	int len = 0;
	while (*s != '\0') {
		len++;
		s++;
	}
	return len;
}

int ctoi(char* c)
{
	if (*c  < '0') { // left bound
		return 0;
	} else if (*c > 'F') { // right bound
		return 0;
	} else if (*c <= '9') { // between left bound and end of digits
		return *c - '0';
	} else if (*c >= 'A')  { // between start of letters and right bound
		return 10 + (*c - 'A');
	}

	return 0;
}

int main()
{
	char* s = "1111";
	int sLen = slen(s);
	int val = 0;
	while (*s != '\0') {
		int wmod = pow(16, --sLen);
		val += ctoi(s) * wmod;
		s++;
	}
	printf("%d\n", val);

	return 0;
}