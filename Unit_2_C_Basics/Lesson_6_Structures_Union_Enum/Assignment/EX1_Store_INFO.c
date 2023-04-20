//AOS  //Structure's Assignment  //EX1_Store_INFO
#include <stdio.h>
#include <string.h>

struct Sstudent{
	char m_name[100];
	int m_roll;
	float m_marks;
};

int main(){
	char choice;
	int count=0;
	struct Sstudent student[10];
	printf("Enter Information of student\n");
	do{
		printf("Enter name: ");
		fflush(stdout);  fflush(stdin);
		scanf("%s",&student[count].m_name);

		printf("Enter roll number: ");
		fflush(stdout);  fflush(stdin);
		scanf("%d",&student[count].m_roll);

		printf("Enter marks: ");
		fflush(stdout);  fflush(stdin);
		scanf("%f",&student[count].m_marks);

		++count;

		if (count == 10){
					printf("Maximum number of student");
					break;
				}
		printf("Do you want add another student?(Y/N)");
		fflush(stdout); fflush(stdin);
		scanf("%c",&choice);

	}while(choice == 'Y' || choice == 'y');

	printf("\nDisplaying Information\n");
	for(int i=0 ;i<count; ++i){
	printf("Student NUM[%d]\n\nName: %s\nRoll: %d\nMarks: %.2f\n\n"
			,i+1,student[i].m_name,student[i].m_roll,student[i].m_marks);
	}
	return 0;
}
