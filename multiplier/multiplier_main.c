//컴퓨터구조 211p 참고
#include<stdio.h>

unsigned int algorythm_1(unsigned int a, unsigned int b);
unsigned int algorythm_2(unsigned int a, unsigned int b);
unsigned int divide_algorythm_1(unsigned int a, unsigned int b, unsigned int* remain);

int main(void) {
	unsigned int a, b;

	scanf_s("%d %d", &a, &b);
	printf("algorythm_1 : %u\n", algorythm_1(a, b));
	printf("algorythm_2 : %u\n", algorythm_2(a, b));

	unsigned int c, d;

	scanf_s("%d %d", &a, &b);
	c = divide_algorythm_1(a, b, &d);
	printf("divide algorythm_1 : %u...%u\n", c, d);
	

	return 0;
}

unsigned int algorythm_1(unsigned int a, unsigned int b) { //부호없는 정수 곱셈 1번
	unsigned long long int multiplicand = a; //64비트 피승수
	unsigned long long int product = 0; //결과
	unsigned long long int mask = 1; //마스크

	for (int i = 0; i < 32; i++) {
		multiplicand <<= 1;
		b >>= 1;
		if (b & mask)
			product += multiplicand;
	}

	return product;
}

unsigned int algorythm_2(unsigned int a, unsigned int b) { //부호없는 정수 곱셈 2번
	//unsigned long long int multiplicand = a; //64비트 피승수 (필요없음)
	unsigned long long int product = b; //결과 (곱 레지스터 오른쪽에 승수)
	unsigned long long int mask = 1; //마스크

	for (int i = 0; i < 32; i++) {
		product >>= 1;
		if (product & mask)
			product += ((unsigned long long int)a << 32); //곱 레지스터 왼쪽에 결과값 저장
	}

	return product;
}

unsigned int divide_algorythm_1(unsigned int a, unsigned int b, unsigned int* remain) {
	unsigned long long int divisor = b; //제수
	divisor <<= 32;
	unsigned long long int remainder = a; //나머지
	unsigned int quotient = (unsigned)0;
	//printf("dbg : divisor = %llu / remainder = %llu / qu = %lu\n", divisor, remainder, quotient);

	for (int i = 0; i < 32; i++) {
		divisor >>= 1;
		quotient <<= 1;
		if (remainder >= divisor) {
			remainder -= divisor;
			quotient++;
		}
		//printf("dbg %d : re = %llu / qu = %lu\n", i, remainder, quotient);
		//printf("dbg : divisor = %llu / remainder = %llu\n", divisor, remainder);
	}

	*remain = remainder;
	return quotient;
}

unsigned int divide_algorythm_2(unsigned int a, unsigned int b, unsigned int* remain) {
	unsigned int divisor = b; //제수
	unsigned long long int remainder = a; //나머지
	unsigned int quotient = (unsigned)0;
	//printf("dbg : divisor = %llu / remainder = %llu / qu = %lu\n", divisor, remainder, quotient);

	for (int i = 0; i < 32; i++) {
		divisor >>= 1;
		quotient <<= 1;
		if (remainder >= divisor) {
			remainder -= divisor;
			quotient++;
		}
		//printf("dbg %d : re = %llu / qu = %lu\n", i, remainder, quotient);
		//printf("dbg : divisor = %llu / remainder = %llu\n", divisor, remainder);
	}

	*remain = remainder;
	return quotient;
}