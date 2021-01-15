#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define n 10000
#define LIMIT_PROC 4

#define MSG_DATA 100
#define MSG_RESULT 101

struct domain_of_sum{
  double begin;
  double step;
  int iters; //number of iterations
};

double f(double x);

MPI_Datatype Init_Type_Domain(void);

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

MPI_Datatype Init_Type_Domain(void){
  MPI_Datatype Domain;
  MPI_Datatype type[3]={MPI_DOUBLE,MPI_DOUBLE,MPI_INT};
  int blocklen[3]={1,1,1};
  MPI_Aint ext;
  MPI_Type_extent (MPI_DOUBLE,&ext);
  MPI_Aint disp[3]={0,ext,2*ext};
  MPI_Type_struct(3,blocklen,disp,type,&Domain);
  return Domain;
}

void master(void){
  double integration,a,b,sum;
  int i,size;
  struct domain_of_sum mydomain;
  MPI_Status status;
  MPI_Datatype Domain = Init_Type_Domain();
  MPI_Type_commit(&Domain);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  printf("enter the domain of integration: ");
  scanf("%lf %lf",&a,&b);
  mydomain.step = (b-a)/n;
  if(size>1){
    if(size > LIMIT_PROC)
      mydomain.iters=(n/2 -1)/(size -1);
    else
      mydomain.iters=(n/2-1)/size;
  }
  mydomain.begin=a+mydomain.step;
  for(i=0;i<size-1;i++){
    mydomain.begin =a +(2*i*mydomain.iters+1)*mydomain.step;
    MPI_Send(&mydomain,1,Domain,i+1,MSG_DATA,MPI_COMM_WORLD);
  }
  for(i= (size -1)*mydomain.iters+1,integration =0;i<n/2;i++)
    integration += 2*f(a+(2*i-1)*mydomain.step)+f(a+2*i*mydomain.step);

  for(i=1;i<size;i++){
    MPI_Recv(&sum,1,MPI_DOUBLE,MPI_ANY_SOURCE,MSG_RESULT,
	     MPI_COMM_WORLD,&status);
    integration += sum;
  }
  integration *= 2;
  integration += f(a) + f(b) + 4*f(b-mydomain.step);
  integration *= mydomain.step/3;
  printf("%15lf\n",integration);
}

void slave(void){
  double sum;
  int i;
  struct domain_of_sum mydomain;
  MPI_Status status;
  MPI_Datatype Domain=Init_Type_Domain();
  MPI_Type_commit(&Domain);
  MPI_Recv(&mydomain,1,Domain,0,MSG_DATA,MPI_COMM_WORLD,&status);

  for(i=0,sum=0;i<mydomain.iters;i++)
    sum+= 2*f(mydomain.begin+(2*i)*mydomain.step)+
      f(mydomain.begin+(2*i+1)*mydomain.step);
  MPI_Send(&sum,1,MPI_LONG_LONG_INT,0,MSG_RESULT,MPI_COMM_WORLD);
}

double f(double x) {return 1/x;}
