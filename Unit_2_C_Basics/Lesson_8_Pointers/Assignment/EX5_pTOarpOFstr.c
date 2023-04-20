//AOS  //Assignment_Pointers //EX5_pTOarpOFstr
#include "stdio.h"
#include "string.h"

struct emp {
	char *name;
	int id;
};

int main(){
	struct emp emp1 ={"Ahmed",1} , emp2 = {"Alex",1002} , emp3 = {"Ran" , 2};
	struct emp* arr[] = {&emp1,&emp2,&emp3};
	struct emp** p = arr;
	printf("ExmployeeName : %s \n\nEmployee ID : %d", (**(p+1)).name ,(*(p+1))->id);
	return 0;
}
