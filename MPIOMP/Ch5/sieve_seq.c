#include <assert.h>
/* sequential version of the sieve of eratosthenes */
#include <stdio.h>

int isPrime(int *arr,int Num);
void sieve(int *arr,int N);

void printArr(int* arr,int lim);
//print all primes less 100;
int main(){
  int N=100;
  int primes[N];
  sieve(primes,N);
  printArr(primes,N);
  assert(isPrime(primes,99)==0);
  assert(isPrime(primes,98)==0);
  assert(isPrime(primes,97)==1);
  puts("success!");
  return 0;
}

void printArr(int *arr,int lim){
  puts("here's the array:\n");
  for(int i=0;i<lim;i++){
    printf("%d ",arr[i]);
  }
  printf("\n");
}


void sieve(int *arr,int N){
//by default set to true
//in C:  0 := False and 1:= True
  for( int i=0; i<N;i++)
    arr[i]=1;

  for( int k=2;k<N;k++){
    for(int j=k;k*j<N;j++){
    //mark multiples as false
      arr[k*j]=0;
    }
  }
}

int isPrime(int *sieve,int Num){
  return sieve[Num];
}
