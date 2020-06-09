#include "data.h"

void Sort(int* arr,int n){
	int counter=0;
  int tmp;
	for(int i=1;i<n;i++){
		for(int j=i; j>0 && arr[j-1]>arr[j];j--){
			counter++;
			tmp=arr[j-1];
			arr[j-1]=arr[j];
			arr[j]=tmp;
		}
	}
}