//AOS  //Lab_Pointers_To_Fun //PassArray
#include "stdio.h"
#include "string.h"

float calcsum (float age[]);
int main(){
	float result , age[] = {23.4, 55, 22.6, 3, 40.5, 18};

	result = calcsum (age);
	printf("Result = %.2f", result);
}

float calcsum (float age[]){
	float sum =0.0;
	for (int i = 0 ; i<6 ; i++){
		sum += age[i];
	}
	return sum ;
}

