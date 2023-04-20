//AOS  //Structure  //Lab2_Enum
#include <stdio.h>
#include <string.h>
enum Gender{Male ,Female};
struct SPerson{
	char m_Name[100];
	enum Gender m_Gender;
};
int main(){
	struct SPerson Persons[]={{"Ahmed Ali",Male},{"Mona Mohamed",Female}};
	for(int i=0;i<sizeof(Persons)/sizeof(struct SPerson);++i){
		printf("%s  -  %s\n",Persons[i].m_Name,
				Persons[i].m_Gender==Male?"Male":"Female");
	}
}
