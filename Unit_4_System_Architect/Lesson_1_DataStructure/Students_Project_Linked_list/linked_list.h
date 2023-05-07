/* student database project (linked list)
 * Linked list.h
 * ENG : Ahmed Osamaa
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define print(...) fflush(stdin);fflush(stdout);\
	printf(__VA_ARGS__);\
	fflush(stdin);fflush(stdout);

// configuration Information of each student
struct sInfo {
    unsigned int ID;
    char Name[40] ;
    float height ;
};
// configuration structure for element in linked list
typedef struct sStudent {
    struct sInfo data ;
    struct sStudent* pNext_element ;
}sElement_t;
// Status

// APIs
void AddStudent ();
int Delete_Student ();
void View_Student ();
void DeleteALL ();
void GetNth ();  //Assignment
void length_List (); //Assignment
int ELement_From_End (); //Assignment
void Find_Mid (); //Assignment
int Detect_loop (); //Assignment
void Reverse_List (); //Assignment

#endif /* LINKED_LIST_H_ */
