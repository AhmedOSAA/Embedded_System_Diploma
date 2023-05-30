/* main.c
 * Created on: May 25, 2023
 * Author: ENG. Ahmed Osamaa
 */
#include "queue.h"

// Queue buffer
Selement_t buffer[50];
// Queue pointer controller
FIFO_t students;

int main (){
	// run & Exit variable
	int run = 1 , selector;
	// Queue pointer controller
	FIFO_t students;
	//init fifo
	if ( fifo_init(&students , buffer , 50) == no_error ){
		print("\t\t\t\t == Program start by ENG.Ahmed Osamaa == \n")
		printf("\t\t << Welcome to the Student Management System >>\n\n");
	}else{
		print("\t\t\t\t == Program Error == \n")
		run = 0;
	}

	while(run){
		printf("Choose The Task that you want to perform\n\n");
		printf("1. Add the Student Details Manually\n");
		printf("2. Add the Student Details From Text File\n");
		printf("3. Find the Student Details by Roll Number\n");
		printf("4. Find the Student Details by First Name\n");
		printf("5. Find the Students Details of Course ID\n");
		printf("6. Find the Total Number of Students\n");
		printf("7. Delete the Student Details by Roll Number\n");
		printf("8. Update the Student Details by Roll Number\n");
		printf("9. Show all Informations\n");
		printf("10. TO EXIT\n");
		print("Enter your choice to perform The Task: ")
		scanf("%d",&selector);

		switch(selector){
		case 1 :
			printf("-----------------------------\n");
			ADD_students_manually(&students);
			printf("-----------------------------\n");
			break;
		case 2 :
			printf("-----------------------------\n");
			ADD_students_FromFile(&students);
			printf("-----------------------------\n");
			break;
		case 3 :
			printf("-----------------------------\n");
			Find_by_Roll(&students);
			printf("-----------------------------\n");
			break;
		case 4 :
			printf("-----------------------------\n");
			Find_by_Fname(&students);
			printf("-----------------------------\n");
			break;
		case 5 :
			printf("-----------------------------\n");
			Find_REG_Courses(&students);
			printf("-----------------------------\n");
			break;
		case 6 :
			printf("-----------------------------\n");
			Total_studentNUM(&students);
			printf("-----------------------------\n");
			break;
		case 7 :
			printf("-----------------------------\n");
			Delete_student(&students);
			printf("-----------------------------\n");
			break;
		case 8 :
			printf("-----------------------------\n");
			update_student(&students);
			printf("-----------------------------\n");
			break;
		case 9 :
			printf("-----------------------------\n");
			Show_ALL_INFO(&students);
			printf("-----------------------------\n");
			break;
		case 10 :
			run = 0 ;
			break;
		default:
			printf("-----------------------------\n");
			printf("\t\t\t << Wrong Choice >> \n\n");
			printf("-----------------------------\n");
			break;
		}
	}
	return 0 ;
}

