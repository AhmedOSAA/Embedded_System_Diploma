//AOS  //Structure's Assignment  //EX6_def_struct_union
#include <stdio.h>
#include <string.h>

union job{
	char name[32];
	float salary;
	int worker_no;
}u;

struct job1{
	char name[32];
	float salary;
	int worker_no;
}s;

int main(){
	printf("Size of Union: %d\n\n",sizeof(u));
	printf("Size of Structure: %d",sizeof(s));
	return 0;
}
