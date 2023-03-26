//AOS
//EX4_Array_addelement
#include <stdio.h>
#include <stdlib.h>

int main() {
	int n ,s,l , a[100];
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
	printf("\nEnter the elements to be inserted:");
	fflush(stdin);   fflush(stdout);
	scanf("%d",&s);
	printf("Enter the location:");
	fflush(stdin);   fflush(stdout);
	scanf("%d",&l);
	for(int i=n;i>l-1;i--){
		a[i]=a[i-1];
	}
	n++;
	a[l-1]=s;
	for(int i=0;i<n;i++){
		printf("%d ",a[i]);
	}
}
