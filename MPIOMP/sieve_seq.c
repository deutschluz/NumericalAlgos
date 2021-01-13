
/* sequential version of the sieve of eratosthenes */
#include <stdio.h>


int* sieve(int N);

void printArr(int* arr,int lim);
//print all primes less 100;
int main(){
  int N=100;
  int primes[N];
  primes=sieve(N);
  printArr(primes,N);
  return 0;
}

void printArr(arr,lim){
  puts("here's the array:\n");
  for(int i=0;i<lim;i++){
    printf("%d ",arr[i]);
  }
  printf("\n");
}


int* sieve(int N){
//dynamically allocate array of N booleans
  int arr[N];
//by default set to true
//in C:  0 := False and 1:= True
  for( int i=0; i<N;i++)
    arr[i]=1;

  for( int k=2;k<N;k++){
    for(int j=k;j<N;j++){
    //mark multiples as false
      arr[k*j]=0;
  }
 }
 return arr;
}
