//AOS  //Lab_Pointers_To_Fun  //PointerTOstructure
#include "stdio.h"
#include "string.h"
#define M 3
#define N 3
struct myss {
	int a[M][N];
};
struct myss retarr() {
	struct myss smy = {
		   {{1,2,3},
			{4,5,6},
			{7,8,9}}
	};
	return smy ;
}
int main(){
	struct myss smy = retarr();
	struct myss *psmy ;
	psmy = &smy;
	int i,j;
	for (i=0;i<M;i++){
		for(j=0;j<N;j++){
			printf("%d ",psmy->a[i][j]);
		}
	}
	return 0;
}
