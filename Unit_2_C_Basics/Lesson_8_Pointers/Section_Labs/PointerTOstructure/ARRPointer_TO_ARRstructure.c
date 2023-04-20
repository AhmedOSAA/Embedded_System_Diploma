//AOS  //Lab_Pointers_To_Fun  //ARRPointer_TO_ARRstructure
#include "stdio.h"
#include "string.h"
#define M 3
#define N 3
struct myss {
	int age ;
	char n[20];
};

int main(){
	struct myss smy[2] = {{25 , "Ahmed"},{26 , "Eman"}};
	struct myss *psmy[2];
	int i;
	for (i=0;i<2;i++){
		psmy[i] = &smy[i];
	}

	for (i=0;i<2;i++){
			printf("%d %s\n",psmy[i]->age , psmy[i]->n);
		}

	return 0;
}

/*
int main(){
	struct myss smy[2] = {{25 , "Ahmed"},{26 , "Eman"}};
	struct myss *psmy = smy ;
	int i,j;
	//printf("%s",(psmy+1)->n);

	for (i=0;i<2;i++){
			printf("%d %s\n",(psmy+i)->age , (psmy+i)->n);
		}

	return 0;
}*/
