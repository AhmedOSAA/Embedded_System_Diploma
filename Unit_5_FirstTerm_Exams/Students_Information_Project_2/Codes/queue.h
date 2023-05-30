/* Queue.h
 * Created on: May 25, 2023
 * Author: ENG. Ahmed Osamaa
 */
#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// printf issue
#define print(...) fflush(stdin);fflush(stdout);\
	printf(__VA_ARGS__);\
	fflush(stdin);fflush(stdout);

// Element data type
typedef struct {
	char Fname[10];
	char Lname[10];
	unsigned int roll ;
	float gpa ;
	int courses_id[5];
}Selement_t;

// Queue controller data type

typedef struct {
	unsigned int length ;  // Size of Queue
	unsigned int count ;   // Number of existed element
	Selement_t * base ;
	Selement_t * head ;
	Selement_t * tail ;
}FIFO_t;

// fifo state
typedef enum {
	no_error,
	error,
	null,
	full,
	not_empty,
	empty
}STATE;

//API

/**************External APIs for Project***************/
STATE fifo_init ( FIFO_t* fifo , Selement_t* buffer , unsigned int length );
STATE isfull(FIFO_t* fifo);
STATE Roll_check(FIFO_t* fifo, unsigned int temp);
void view_roll_info(Selement_t* ptr);

/**************APIs Of Project***************/
STATE ADD_students_manually(FIFO_t* fifo);
STATE ADD_students_FromFile(FIFO_t* fifo);
STATE Find_by_Roll(FIFO_t* fifo);
STATE Find_by_Fname(FIFO_t* fifo);
STATE Find_REG_Courses(FIFO_t* fifo);
STATE Total_studentNUM(FIFO_t* fifo);
STATE Delete_student(FIFO_t* fifo);
STATE update_student(FIFO_t* fifo);
STATE Show_ALL_INFO(FIFO_t* fifo);

#endif /* QUEUE_H_ */
