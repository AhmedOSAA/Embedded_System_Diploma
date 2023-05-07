/* student database project (linked list)
 * main.c
 * ENG : Ahmed Osamaa
 */

#include "linked_list.h"


int main ()
{	int selector = 0 ;
while(1){
	printf("\t Choose on of the following options\n");
	printf("\t ----------------------------------\n\n");
	print("1) Add Student\n"
			"2) Delete Student\n"
			"3) View Students\n"
			"4) Delete All\n"
			"5) View Nth\n"
			"6) Length of list\n"
			"7) student from end\n"
			"8) Find mid student\n"
			"9) Detect loop\n"
			"10) Reverse List\n"
			"Enter option Number: ");

	scanf("%d",&selector);
	printf("\n\t<=====================================>\n");
	switch(selector)
	{
	case 1:
		AddStudent();
		printf("\n\t<=====================================>\n");
		break;
	case 2:
		Delete_Student();
		printf("\n\t<=====================================>\n");
		break;
	case 3:
		View_Student();
		printf("\n\t<=====================================>\n");
		break;
	case 4:
		DeleteALL();
		printf("\n\t<=====================================>\n");
		break;
	case 5:
		GetNth();
		printf("\n\t<=====================================>\n");
		break;
	case 6:
		length_List();
		printf("\n\t<=====================================>\n");
		break;
	case 7:
		ELement_From_End();
		printf("\n\t<=====================================>\n");
		break;
	case 8:
		Find_Mid();
		printf("\n\t<=====================================>\n");
		break;
	case 9:
		Detect_loop();
		printf("\n\t<=====================================>\n");
		break;
	case 10:
		Reverse_List();
		printf("\n\t<=====================================>\n");
		break;
	default :
		printf("\n\t<======== You Select wrong option number =========>\n\n");
		break;
	}
}

return 0 ;
}

