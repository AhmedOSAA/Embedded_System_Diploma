
#include <stdio.h>
#include <stdlib.h>
/*Calculate circle area or circumference
  used if statement & goto statement & line Condition */
int main()
{
	char choice;
	float r , area = 0 , circum = 0 , sum ;
	printf ("Enter circle Radius :");
	fflush(stdout); 	fflush(stdin);
	scanf ("%f",&r);
	try_again: // label goto
	printf ("Enter your choice (a to print the area , c to print the circumference):");
	fflush(stdout); 	fflush(stdin);
	scanf ("%c",&choice);
	if(choice=='a')
		area = 3.14*r*r;
	else if(choice=='c')
		circum = 2*3.14*r;
	else
		{printf("\nWrong Choice , pls try again\n");
		goto try_again;} // goto statement
	sum = (area>circum)? area : circum ; // line condition
	printf ("sum = %f ", sum);
}
