/* student database project (linked list)
 * Linked list.c
 * ENG : Ahmed Osamaa
 */

#include "linked_list.h"
// make a head pointer to point at first element and init by NULL
sElement_t* gpfirst_element = NULL ;

void AddStudent (){
	char temp[40] ;
	sElement_t* temp_element = gpfirst_element ;
	// make a pointer point to a dynamic location
	sElement_t* pNew_element = (sElement_t*)malloc(sizeof(sElement_t));
	// 3 condition
	//1) if new element is first element
	if(gpfirst_element == NULL)
	{
		gpfirst_element = pNew_element ;
	}else{
		//2) if new element isn't first element
		while (1){
			if (temp_element->pNext_element == NULL) break ;
			temp_element = temp_element->pNext_element;
		}
		temp_element->pNext_element = pNew_element ;
	}

	// get data from user
	print("Enter Student ID :");
	gets(temp);
	pNew_element->data.ID = atoi(temp);


	print("Enter Student Name :");
	gets(pNew_element->data.Name);

	print("Enter Student height :");
	gets(temp);
	pNew_element->data.height = atof(temp);

	pNew_element->pNext_element = NULL ;
}
int Delete_Student ()
{
	// make prev_element point to pNext_element of selected element
	sElement_t* prev_element = NULL;
	sElement_t* selected_element = gpfirst_element;
	unsigned int temp_id ;
	if(gpfirst_element){
		print("Enter student ID to delete : ");  // take ID from user
		scanf("%d",&temp_id);
		while(selected_element){
			if(selected_element->data.ID == temp_id){
				if(prev_element){
					prev_element->pNext_element = selected_element->pNext_element ;
				}else{
					gpfirst_element = selected_element->pNext_element;
				}
				free(selected_element);
				print("\n- Deleted >>>>>> done\n\n");
				return 1 ;
			}else{
				prev_element = selected_element ;
				selected_element = selected_element->pNext_element ;
			}
		}
		print(" ID is not found \n\n");
	}else{
		printf("\n\t ==== List is Empty ====\n\n");
	}
	return 0 ;

}
void View_Student ()
{
	int count = 1 ;
	sElement_t* view_element = gpfirst_element;
	if(view_element){
		while(view_element){
			print(">Record Number :%d\nID : %d\nName: %s\nHeight: %.2f\n-------\n"
					,count,view_element->data.ID,view_element->data.Name,view_element->data.height);
			view_element = view_element->pNext_element;
			count++;
		}
	}else {
		print("\t ==== List is Empty ====\n\n");
	}
}
void DeleteALL (){
	// make gpfirst_element point to NULL
	sElement_t* temp_element = gpfirst_element;
	sElement_t* free_element = gpfirst_element;
	gpfirst_element = NULL ;
	// loop & free elements
	if(temp_element){
		while(temp_element){
			free_element = temp_element ;
			temp_element = temp_element->pNext_element;
			free(free_element);
		}
		printf("\n\t ==== Delete All >>> Done ====\n\n");
	}else{
		printf("\n\t ==== List is Empty ====\n\n");
	}
}

void GetNth ()
{
	// takes a linked list and an integer index
	sElement_t* temp_element = gpfirst_element;
	unsigned int node_number , count = 1 ;
	print("Enter Node number : ");  // take index from user
	scanf("%d",&node_number);
	if(temp_element){
		while(temp_element)
		{
			if(count == node_number){
				print(">Record Number :%d\nID : %d\nName: %s\nHeight: %.2f\n-------\n"
						,count,temp_element->data.ID,temp_element->data.Name,temp_element->data.height);
				break;
			}else{
				temp_element = temp_element->pNext_element ;
				count++ ;
				if(temp_element == NULL)
					printf("\n\t ==== Out OF Range ====\n\n");
			}
		}
	}else{
		printf("\n\t ==== List is Empty ====\n\n");
	}

}
void length_List ()
{
	// a pointer point at first element & loop to NULL
	sElement_t* pointer_element = gpfirst_element;
	unsigned int count = 0 ;
	while(pointer_element)
	{
		count++;
		pointer_element = pointer_element->pNext_element ;
	}
	printf("\nLength of list is : %d\n", count);
}

int ELement_From_End (){
	/* create two pointer and make n element between them
	 * move them together until the last one  reach NULL
	 */
	unsigned int node_number , count = 1 ;
	print("Enter Node number from the end : ");  // take index from user
	scanf("%d",&node_number);
	sElement_t* selected_element = gpfirst_element;
	sElement_t* mover_element = gpfirst_element;
	// make mover_element at n element from selected_element
	if(gpfirst_element){
		for (int i = 0 ; i < node_number ; i++)
		{
			mover_element = mover_element->pNext_element ;
			if(mover_element == NULL && i != node_number-1){
				printf("\n\t ==== Out OF Range ====\n\n");
				return 0;
			}
		}
		while(mover_element)
		{
			mover_element = mover_element->pNext_element ;
			selected_element = selected_element->pNext_element ;
			count++;
		}
		print(">Record Number :%d\nID : %d\nName: %s\nHeight: %.2f\n-------\n"
				,count,selected_element->data.ID,selected_element->data.Name,selected_element->data.height);
	}else{
		printf("\n\t ==== List is Empty ====\n\n");
	}
	return 1 ;
}

void Find_Mid ()
{
	//make two pointer one move double step and other move one step
	// when a fast_p || fast_p.pNext == NULL then the slow_p is at Middle
	sElement_t* fast_pointer = gpfirst_element;
	sElement_t* slow_pointer = gpfirst_element;
	unsigned int count = 1 ;

	if(gpfirst_element){
		while(fast_pointer && fast_pointer->pNext_element){
			fast_pointer = fast_pointer->pNext_element->pNext_element;
			slow_pointer = slow_pointer->pNext_element ;
			count++;
		}
		print("Student at the middles:\n>Record Number :%d\nID : %d\nName: %s\nHeight: %.2f\n-------\n"
				,count,slow_pointer->data.ID,slow_pointer->data.Name,slow_pointer->data.height);
	}else{
		printf("\n\t ==== List is Empty ====\n\n");
	}
}

int Detect_loop ()
{
	//make two pointer one move double step and other move one step
	//when two pointer == then the list is looped
	sElement_t* fast_pointer = gpfirst_element;
	sElement_t* slow_pointer = gpfirst_element;
	if(gpfirst_element){
		while(slow_pointer && fast_pointer && fast_pointer->pNext_element){
			fast_pointer = fast_pointer->pNext_element->pNext_element;
			slow_pointer = slow_pointer->pNext_element ;
			if(fast_pointer == slow_pointer){
				printf("\n\t Found Loop \n\n");
				return 1 ;
			}
		}
		printf("\n\t List isn't Loop \n\n");
	}else{
		printf("\n\t ==== List is Empty ====\n\n");
	}
	return 0 ;
}

void Reverse_List()
{
	/* 1) create two pointer (temp_p & rev_ ) with a head pointer of list & point to first element
	 * 2) Move head_P and make first element point to NULL by rev_p
	 * 3) make rev_ == head then move head then reverse this element to temp_p
	 * 4) and so on until the head.Npointer point to NULL
	 */
	sElement_t* temp_pointer = gpfirst_element;
	sElement_t* reverse_pointer = gpfirst_element;
	if(gpfirst_element) // Check list is empty
	{
		// Check the next element is NULL or element
		// if(1) element
		if(gpfirst_element->pNext_element){
			gpfirst_element = gpfirst_element->pNext_element; // move head
			reverse_pointer->pNext_element = NULL ; // point first element to NULL
			// then Go loop check the next element is element > go loop until be NULL
			while(gpfirst_element->pNext_element){
				reverse_pointer = gpfirst_element ;
				gpfirst_element = gpfirst_element->pNext_element;
				reverse_pointer->pNext_element = temp_pointer ;
				temp_pointer = reverse_pointer ;
			}
			//when be NULL then this element become first element
			//make it point to reverse_P "become second element"
			gpfirst_element->pNext_element = reverse_pointer ;
			printf("\n\t ==== Reverse is Done ====\n\n");
		}
		else // if(1) NULL
		{
			printf("\n\t ==== List have one element ====\n\n");
		}
	}else{
		printf("\n\t ==== List is Empty ====\n\n");
	}
}
