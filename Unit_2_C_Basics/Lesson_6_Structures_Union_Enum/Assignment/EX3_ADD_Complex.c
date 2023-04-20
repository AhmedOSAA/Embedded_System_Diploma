//AOS  //Structure  //EX3_ADD_Complex
#include <stdio.h>
#include <string.h>
struct SComplex {
	double m_R;  //Real part
	double m_I;  //Imaginary part
};

struct SComplex ReadComplex (char a[]);
struct SComplex AddComplex(struct SComplex A, struct SComplex B);
void PrintComplex(char a[],struct SComplex c);

int main(){
	struct SComplex x,y,z;
	printf("For 1st complex number:\n");
	x = ReadComplex("X");
	printf("For 2nd complex number:\n");
	y = ReadComplex("Y");
	z = AddComplex(x,y);
	PrintComplex("Z",z);
}
struct SComplex ReadComplex (char a[]){
	struct SComplex c;
	printf("Enter %s Complex value (Ex: 5 , -3): ", a);
	fflush(stdout);  fflush(stdin);
	scanf("%lf ,%lf",&c.m_R,&c.m_I);
	return c;
}

struct SComplex AddComplex(struct SComplex A, struct SComplex B){
	struct SComplex c;
	c.m_R = A.m_R + B.m_R;
	c.m_I = A.m_I + B.m_I;
	return c;
}

void PrintComplex(char a[],struct SComplex c){
	printf("SUM : %s = (%.2lf) + (%.2lf)i \n",a,c.m_R,c.m_I);
}
