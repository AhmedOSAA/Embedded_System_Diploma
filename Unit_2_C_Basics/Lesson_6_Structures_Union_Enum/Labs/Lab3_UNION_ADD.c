//AOS  //Structure  //Lab3_UNION_ADD
#include <stdio.h>
#include <string.h>
enum NUMtype{INT ,FLOAT , DOUBLE};

union UNUMvalue{
	int u_intvalue;
	float u_floatvalue;
	double u_doublevalue;
};
union UNUMvalue ADD(union UNUMvalue v1 ,union UNUMvalue v2 ,enum NUMtype type);
int main(){
	union UNUMvalue V1 , V2 , R;
	printf("The size of UNUMvalue is: %d bytes\n\n",sizeof(union UNUMvalue));
	V1.u_intvalue = 9898;
	V2.u_intvalue = 8776;
	R = ADD(V1,V2, INT);
	printf("int: %d + %d = %d\n",V1.u_intvalue,V2.u_intvalue,R.u_intvalue);

	V1.u_floatvalue = 86.82;
	V2.u_floatvalue = 83.11;
	R = ADD(V1,V2 , FLOAT);
	printf("float: %f + %f = %f\n",V1.u_floatvalue,V2.u_floatvalue,R.u_floatvalue);

	V1.u_doublevalue = 821.8;
	V2.u_doublevalue = 988.2;
	R = ADD(V1,V2 , DOUBLE);
	printf("double: %lf + %lf = %lf\n",V1.u_doublevalue,V2.u_doublevalue,R.u_doublevalue);

	return 0;
}

union UNUMvalue ADD(union UNUMvalue v1 ,union UNUMvalue v2 ,enum NUMtype type){
	union UNUMvalue r;
	switch (type){
	case INT : r.u_intvalue = v1.u_intvalue + v2.u_intvalue; break;
	case FLOAT : r.u_floatvalue = v1.u_floatvalue + v2.u_floatvalue; break;
	case DOUBLE : r.u_doublevalue = v1.u_doublevalue + v2.u_doublevalue; break;}
	return r;
}
