// sum array - sequential version
#include <stdio.h>
#define N 100000

int main(void){
  float array[N];
  double mysum =0;
  unsigned long long i;
  for(i=0;i<N;i++)
    array[i] = i+1;

  for(i=0;i<N;i++)
    mysum += array[i];

  printf("%lf\n",mysum);
  return 0;
}
