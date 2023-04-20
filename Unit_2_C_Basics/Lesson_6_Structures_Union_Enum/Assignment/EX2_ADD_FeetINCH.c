//AOS  //Structure's Assignment  //EX2_ADD_FeetINCH
#include <stdio.h>
#include <string.h>

struct Sdistance{
	float m_inch;
	float m_feet;
};
int main(){
	int count=0;
	struct Sdistance dis[2],sum;
	do{
		printf("Enter Information for distance(%d)\n",count+1);
		printf("Enter feet: ");
		fflush(stdout);  fflush(stdin);
		scanf("%f",&dis[count].m_feet);

		printf("Enter inch: ");
		fflush(stdout);  fflush(stdin);
		scanf("%f",&dis[count].m_inch);

		++count;
	}while(count<2);
	sum.m_feet = dis[0].m_feet + dis[1].m_feet;
	sum.m_inch = dis[0].m_inch + dis[1].m_inch;
	if(sum.m_inch > 12){
		sum.m_inch-=12;
		++sum.m_feet;}
	printf("\nSum of distance = %.2f\' -%.2f\"",sum.m_feet,sum.m_inch);
	return 0;
}
