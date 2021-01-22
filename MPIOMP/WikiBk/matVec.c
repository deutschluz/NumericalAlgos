#include <stdio.h>
#include <stdlib.h>

void writecolumn(float *A,int N);

int main(int argc,char **argv){
  int N = 100;
  float *A=(float *)malloc(N*N*sizeof(float));
  
  float B[N];
  float C[N];
  unsigned int i,j;
  //check that memory has been successfully allocated by malloc
  if (A == NULL) {
    printf("Memory not allocated.\n");
    exit(0);
  }
  //init
  for(i=0;i<N;i++)
    for(j=0;j<N;j++)
      A[i*N+j]=i+j;
  B[i]=1;
//product of mat and vec
  for(i=0;i<N;++i)
    for(j=0,C[i]=0;j<N;j++)
      C[i] += A[j*N+j]*B[j];

  writecolumn(C,N);
  free(A);
  return 0;
}

void writecolumn(float *A,int N){
  int i;
  for(i=0;i<N;i++)
    printf("%f\n",A[i]);
}
