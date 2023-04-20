//AOS  //Structure  //Lab1_Adding_Complex
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
	x = ReadComplex("X");
	y = ReadComplex("Y");
	z = AddComplex(x,y);
	PrintComplex("Z",z);
}

struct SComplex ReadComplex (char a[]){
	struct SComplex c;
	printf("Enter %s Complex value (Ex: 5 , -3): ", a);
	fflush(stdout);
	scanf("%lf , %lf",&c.m_R,&c.m_I);
	return c;
}
struct SComplex AddComplex(struct SComplex A, struct SComplex B){
	struct SComplex c;
	c.m_R = A.m_R + B.m_R;
	c.m_I = A.m_I + B.m_I;
	return c;
}
void PrintComplex(char a[],struct SComplex c){
	printf("%s = (%.2lf) + j (%.2lf) \n",a,c.m_R,c.m_I);
}
