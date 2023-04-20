#include "stdio.h"

#define debug

#define DPRINTF(debug_level,...) if(debug_level > 1)\
		printf("@ Func: %s, File: %s, Line: %d ",__func__,__FILE__,__LINE__);\
		printf(">> \t");\
		printf(__VA_ARGS__);\

void CAN_Send ()
{
#ifdef debug
	DPRINTF(2,"\n");
#endif
}

void CAN_init ()
{
#ifdef debug
	DPRINTF(2,"\n");
#endif
}

int main(){
#ifdef debug
	DPRINTF(2,"Start main\n");
#endif

	CAN_init();
	CAN_Send();

#ifdef debug
	DPRINTF(2,"End main\n");
#endif

	return 0;
}
