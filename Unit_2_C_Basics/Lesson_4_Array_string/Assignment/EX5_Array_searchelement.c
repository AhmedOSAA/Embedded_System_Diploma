//AOS
//EX5_Array_searchelement
#include <stdio.h>
#include <stdlib.h>

int main() {
	int n ,s,a[100];
	printf("Enter num of elements :");
	fflush(stdin);   fflush(stdout);
	scanf("%d",&n);
	printf("Enter %d elements :\n",n);
	for(int i=0;i<n;i++){
		fflush(stdin);   fflush(stdout);
		scanf("%d",&a[i]);
	}
	for(int i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	printf("\nEnter the elements to be searched:");
	fflush(stdin);   fflush(stdout);
	scanf("%d",&s);
	for(int i=0;i<n;i++){
		if(a[i]==s){
			printf("Number found at location = %d",i+1);
			break;
		}
		else if(i==n-1){printf("Number not found");}
		else continue;
		}
	}
