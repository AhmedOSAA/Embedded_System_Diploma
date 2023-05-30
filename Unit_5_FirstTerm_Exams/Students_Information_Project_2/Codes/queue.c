/* Queue.c
 * Created on: May 25, 2023
 * Author: ENG. Ahmed Osamaa
 */
#include "queue.h"

// Define APIs

/**************External APIs for Project***************/
STATE fifo_init ( FIFO_t* fifo , Selement_t* buffer , unsigned int length ){
	if(buffer == NULL) return null;

	fifo->base = buffer ;
	fifo->head = buffer ;
	fifo->tail = buffer ;
	fifo->length = length;
	fifo->count = 0;

	return no_error;
}

STATE isfull(FIFO_t* fifo){
	if(fifo->count == 0)return empty ;
	else if(fifo->count == 50)return full;
	else return not_empty;

}

STATE Roll_check(FIFO_t* fifo,unsigned int temp){
	Selement_t* ptr = fifo->base;
	for(int i = 0 ; i < fifo->count ; i++){
		if(temp == ptr->roll)return error ;
		ptr++;
	}
	return no_error;
}

void view_roll_info(Selement_t* ptr){
	printf("The Student Details :\n\n"
			"The Student Roll Number: %d\n"
			"The First name is %s\n"
			"The Last name is %s\n"
			"The GPA is %0.2f\n"
			"His Courses ID :\n",ptr->roll,ptr->Fname,ptr->Lname,ptr->gpa);
	for(int i=0 ; i < 5 ; i++){
		printf("\tThe Course %d id: %d\n",i+1,ptr->courses_id[i]);
	}
}

/**************APIs Of Project***************/
STATE ADD_students_manually(FIFO_t* fifo){
	if( isfull(fifo) == full ){
		print("\t <<You can't add new one; The Queue is completed >>\n")
				return full;
	}
	print("Enter The Roll Number = ")
	scanf("%u",(unsigned int*)&fifo->head->roll);
	// Checking roll number is not repeated ...
	if(Roll_check(fifo ,fifo->head->roll) == error){
		print("\t\t\t\t << The Roll Number is existed >> \n")
				return error ;
	}
	print("Enter The First Name of student: ")
	gets(fifo->head->Fname);
	print("Enter The Last Name of student:")
	gets(fifo->head->Lname);
	print("Enter The GPA of student = ")
	scanf("%f",(float*)&fifo->head->gpa);
	print("Enter The courses ID : \n")
	for(int i=0 ; i < 5 ; i++){
		print("Course %d id: ",i+1)
		scanf("%d",&fifo->head->courses_id[i]);
	}
	fifo->head++;
	fifo->count++;
	printf("\t << ADD Student Successfully>> \n");
	return no_error;
}

STATE ADD_students_FromFile(FIFO_t* fifo){
	 /* n : controller variable for student's information (9 info for each student).
	  * i : track each char in the line & reset to zero every new line.
	  * j : track each info to store in a temp array & reset to zero every new info in the line.  */
	int n=0 , i=0 , j=0 ;
	FILE *Pfile = fopen("INFO_file.txt", "r"); // Access file with pointer of FILE Data_type
	char info[255] , temp[10];
	if(Pfile == NULL){
			printf("Couldn't find the file , try name the file by 'INFO_file.txt'\n");
	}else{
		// fgets(array , size_array , pointer to file); it take line by line from file.
		while(fgets(info , 255 , Pfile) != NULL){
			i=0;
			for(n=0 ; n<=8 ;n++){
				j=0;
				while(1){
					if(info[i] == ' '){
						i++;
						temp[j] = '\0';
						break;
					}else if(info[i] == '\0'){
						temp[j]= '\0';
						break;
					}else{
						temp[j] = info[i];
						i++; j++;
						continue;
					}
				}
				switch(n){
				case 0 :
					fifo->head->roll = atoi(temp);
					// Checking roll number is not repeated ...
					if(Roll_check(fifo ,fifo->head->roll) == error){
						printf("[ERROR] Roll Number %d is already taken. \n",fifo->head->roll);
						n=9;    // n=9 because for loop will increment n then check the condition
					}
					break;
				case 1 :
					strcpy(fifo->head->Fname , temp);
					break;
				case 2 :
					strcpy(fifo->head->Lname , temp);
					break;
				case 3 :
					fifo->head->gpa = atof(temp);
					break;
				case 4 :
					fifo->head->courses_id[0] = atoi(temp);
					break;
				case 5 :
					fifo->head->courses_id[1] = atoi(temp);
					break;
				case 6 :
					fifo->head->courses_id[2] = atoi(temp);
					break;
				case 7 :
					fifo->head->courses_id[3] = atoi(temp);
					break;
				case 8 :
					fifo->head->courses_id[4] = atoi(temp);
					break;
				default:
					printf("Couldn't find the file , try name the file by 'INFO_file.txt'\n");
					return error;
				}
			}
			if(n==10){  // n = 10 after incrementing of for loop if the roll number is already taken.
				continue;
			}else{
				printf("[INFO] The Roll Number %d saved successfully.\n", fifo->head->roll);
				fifo->head++;
				fifo->count++;
			}
		}
		fclose(Pfile); // to close the file.
	}
	printf("[INFO] Student Details is added Successfully.\n");
	return no_error;
}

STATE Find_by_Roll(FIFO_t* fifo){
	if( isfull(fifo) == empty ){
		print("\t << The Queue is Empty >>\n")
				return empty;
	}
	Selement_t* ptr = fifo->base;
	unsigned int temp ;
	print("Enter The Roll Number of the student: ")
	scanf("%u",&temp);
	for(int i=0 ; i <= fifo->count ; i++){
		if(temp == ptr->roll){
			view_roll_info(ptr);
			return no_error;
		}
		ptr++;
	}
	print("\t\t\t\t << This Roll Number is not Existed >> \n")

	return error;
}

STATE Find_by_Fname(FIFO_t* fifo){
	if( isfull(fifo) == empty ){
		print("\t << The Queue is Empty >>\n")
				return empty;
	}
	Selement_t* ptr = fifo->base;
	int same = 0;
	char temp[10] ;
	print("Enter The First Name of the student: ")
	gets(temp);
	for(int i =0 ; i <= fifo->count ; i++){
		if(stricmp(temp,ptr->Fname) == 0){
			view_roll_info(ptr);
			same++;
			printf("\t----------------\n");
		}
		ptr++;
	}
	if(same)return no_error;
	print("\t\t\t\t << This Name is not Existed >> \n")
	return error;
}

STATE Find_REG_Courses(FIFO_t* fifo){
	if( isfull(fifo) == empty ){
		print("\t << The Queue is Empty >>\n")
				return empty;
	}
	Selement_t* ptr = fifo->base;
	int C_id , num = 0;
	print("Enter The Course ID: ")
	scanf("%u",&C_id);
	for(int i=0 ; i <= fifo->count ;i++){
		for(int j=0 ; j < 5 ; j++){
			if(C_id == ptr->courses_id[j]){
				num++;
				printf("The Student Details :\n\n"
						"The Student Roll Number: %d\n"
						"The First name is %s\n"
						"The Last name is %s\n"
						"The GPA is %0.2f\n"
						"His Courses ID :\n"
						"----------------------\n",ptr->roll,ptr->Fname,ptr->Lname,ptr->gpa);
			}
		}
		ptr++;
	}
	if(num){
		printf("[INFO] Total Number of Student Enrolled: %d\n",num);
		return no_error;
	}
	printf("[ERROR] Course ID %d not found\n",C_id);
	return error;
}

STATE Total_studentNUM(FIFO_t* fifo){
	printf("-----------------------------\n");
	printf("[INFO] The Total number of Student is %d\n",fifo->count);
	printf("[INFO] You can add up to %d students.\n",fifo->length);
	printf("[INFO] You can add %d more students.\n",(fifo->length-fifo->count));
	printf("-----------------------------\n");
	return no_error;
}

STATE Delete_student(FIFO_t* fifo){
	if( isfull(fifo) == empty ){
		print("\t << The Queue is Empty >>\n")
				return empty;
	}
	Selement_t* ptr = fifo->base;
	int tracker = 1 ;
	unsigned int temp ;
	print("Enter The Roll Number of the student: ")
	scanf("%u",&temp);

	for(int i=0 ; i < fifo->count ; i++){
		if(ptr->roll == temp){
			for(int j = tracker ; j < fifo->count ; j++){  // shift all next student back step.
				*ptr = *(ptr+1);
				ptr++;
			}
			fifo->head--;
			fifo->count--;
			printf("[INFO] The Roll number is removed Successfully\n");
			return no_error;
		}
		tracker++;
		ptr++;
	}

	printf("[ERROR] This is Roll %d not Found\n",temp);
	return error;
}

STATE update_student(FIFO_t* fifo){
	if( isfull(fifo) == empty ){
		print("\t << The Queue is Empty >>\n")
				return empty;
	}
	Selement_t* ptr = fifo->base;
	int selector = 0 , check = 0;
	unsigned int temp ;
	print("Enter The Roll Number of the student: ")
	scanf("%u",&temp);
	// find the selection student and point on it.
	for(int i=0 ; i < fifo->count ; i++){
		if(ptr->roll == temp){
			check++;
			break;
		}
		ptr++;
	}
	if(check == 0){
		printf("[ERROR] This is Roll %d not Found\n",temp);
		return error;
	}
	// goto statement
	another_edit:
	print("1. first name\n"
			"2. last name\n"
			"3. Roll No.\n"
			"4. GPA\n"
			"5. Courses ID\n"
			"6. Exit\n\n"
			"Enter no. Option : ")
			scanf("%d",&selector);

	switch(selector){
	case 1 :
		print("Enter The First Name of student: ")
		gets(ptr->Fname);
		printf("[INFO] UPDATE SUCCESSFULLY. \n");
		break;
	case 2 :
		print("Enter The Last Name of student:")
		gets(ptr->Lname);
		printf("[INFO] UPDATE SUCCESSFULLY. \n");
		break;
	case 3 :
		print("Enter The Roll Number = ")
		scanf("%u",(unsigned int*)&temp);
		// checking the roll number exist or not
		if(Roll_check(fifo ,temp) == error){
			print("\t<< The Roll Number is existed ,, Try another roll number >> \n")
			break;
			}
		ptr->roll = temp ;
		printf("[INFO] UPDATE SUCCESSFULLY. \n");
		break;
	case 4 :
		print("Enter The GPA of student = ")
		scanf("%f",(float*)&ptr->gpa);
		printf("[INFO] UPDATE SUCCESSFULLY. \n");
		break;
	case 5 :
		print("Enter The courses ID : \n")
		for(int j=0 ; j < 5 ; j++){
			print("Course %d id: ",j+1)
						scanf("%d",&ptr->courses_id[j]);
		}
		printf("[INFO] UPDATE SUCCESSFULLY. \n");
		break;
	case 6 :
		return no_error;
	default:
		printf("\t\t\t << Wrong Choice >> \n\n");
		break;
	}
	print(">> 1. Another Edit \n"
			">> 2. Exit\n"
			"Enter Choice : \n")
	scanf("%d",&check);

	if(check == 1)goto another_edit; // goto statement
	else return error;
}

STATE Show_ALL_INFO(FIFO_t* fifo){
	if( isfull(fifo) == empty ){
		print("\t << The Queue is Empty >>\n")
				return empty;
	}
	Selement_t* ptr = fifo->base;
	for(int i=0 ; i < fifo->count ; i++){
		printf("The Student Details :\n\n"
				"The Student Roll Number: %d\n"
				"The First name is %s\n"
				"The Last name is %s\n"
				"The GPA is %0.2f\n"
				"His Courses ID :\n",ptr->roll,ptr->Fname,ptr->Lname,ptr->gpa);
		for(int i=0 ; i < 5 ; i++){
			printf("\tThe Course %d id: %d\n",i+1,ptr->courses_id[i]);

		}
		ptr++;
		printf("\t_______________\n");
	}
	return error;
}

