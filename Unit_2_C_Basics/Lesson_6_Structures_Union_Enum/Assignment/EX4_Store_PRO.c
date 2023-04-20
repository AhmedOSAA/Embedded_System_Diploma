//AOS  //Structure's Assignment  //EX4_Store_PRO
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
		student[count].m_roll = count+1;
		printf("For roll number %d:\n",student[count].m_roll);
		printf("Enter name: ");
		fflush(stdout);  fflush(stdin);
		scanf("%s",&student[count].m_name);

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

	printf("\nDisplaying Information of students:\n");
	for(int i=0 ;i<count; ++i){
		printf("Information for roll number %d:\nName: %s\nMarks: %.2f\n\n"
				,student[i].m_roll,student[i].m_name,student[i].m_marks);
	}
	return 0;
}
