//second parallel version of Simpson's Method

#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define n 10000
#define LIMIT_PROC 4
#define MSG_DATA 100
#define MSG_RESULT 101

double f(double x);
int GetIters(int size);
void master(void);
void slave(void);

int main(int argc,char **argv){
  int myrank;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
  if(!myrank)
    master();
  else
    slave();
  MPI_Finalize();
  return 0;
}

int GetIters(int size){
  int iters;
  if(size>1){
    if(size>LIMIT_PROC)
      iters = (n/2 -1)/(size-1);
    else
      iters = (n/2 -1)/size;
  }
  return iters;
}

void master(void){

  double integration,a,b,sum;
  int i,size,iters;
  double mydomain[2];
  MPI_Status status;
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  iters=GetIters(size);
  printf("enter the domain of integration: ");
  scanf("%lf %lf", &a,&b);
  mydomain[1] = (b-a)/n;
  //divide work and send
  mydomain[0]=a+mydomain[1];
  for(i=0;i<size-1;i++){
    mydomain[0] = a+(2*i*iters+1)*mydomain[1];
    MPI_Send(mydomain,2,MPI_DOUBLE,i+1,MSG_DATA,MPI_COMM_WORLD);
  }
  //master completes work
  for(i=(size-1)*iters+1,integration=0;i<n/2;i++){
    integration += 2*f(a +(2*i-1)*mydomain[1])+f(a+2*i*mydomain[1]);
  }

  //master receives results
  for(i=1;i<size;i++){
    MPI_Recv(&sum,1,MPI_DOUBLE,MPI_ANY_SOURCE,MSG_RESULT,MPI_COMM_WORLD,&status);
    integration += sum;
  }

  integration *= 2;
  integration += f(a) + f(b) +4*f(b-mydomain[1]);
  integration *= mydomain[1]/3;
  printf("the result is %lf\n",integration);
}

void slave(void){

  double sum;
  int i,size,iters;
  double mydomain[2];
  MPI_Status status;
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  iters=GetIters(size);
  MPI_Recv(mydomain,2,MPI_DOUBLE,0,MSG_DATA,MPI_COMM_WORLD,&status);
  
  for(i=0,sum=0;i<iters;i++){
    sum+=2*f(mydomain[0]+(2*i)*mydomain[1])+f(mydomain[0]+(2*i+1)*mydomain[1]);
   }
    MPI_Send(&sum,1,MPI_DOUBLE,0,MSG_RESULT,MPI_COMM_WORLD);
  
}

double f(double x){return 1/x;}
