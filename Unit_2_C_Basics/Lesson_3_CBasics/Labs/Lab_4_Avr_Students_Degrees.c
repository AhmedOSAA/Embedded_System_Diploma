//Calculate the Average Students Degrees
#include <stdio.h>
#include <stdlib.h>

int main() {
	int num_student , i;
	float sum = 0 , degree ;
	printf("Enter number of students :");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num_student);  // don't forget (&) address of variable you want scan

	for(i=1;i<=num_student;i++){
		printf("Enter student (%d) degree :",i);
		fflush(stdin); fflush(stdout);
		scanf("%f", &degree); // don't forget (&) address of variable you want scan
		sum += degree ;
	}
	printf("the Average Students Degrees is : %0.2f\n",sum/num_student);
}
