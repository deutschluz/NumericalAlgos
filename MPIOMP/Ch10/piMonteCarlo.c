//monte carlo method to compute pi
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
  int count;//points inside circle
  int i;
  int n;  //number of samples
  double pi; //estimate of pi
  unsigned short xi[3]; //random number seed
  double x,y; //point coordinates

  if(argc != 5){
    printf("Correct command line: ");
    printf("%s <#samples> <seed0> <seed1> <seed2>\n",argv[0]);
    return -1;
  }
  n=atoi(argv[1]);
  for(i=0;i<3;i++)
    xi[i]=atoi(argv[i+2]);

  count =0;
  for(i=0;i<n;i++){
    x=random();
    y=random();
    if(x*x + y*y <= 1.0) count++;
  }
  pi=4.0 *(double)count/(double)n;
  printf("Samples: %d Estimate of pi: %7.5f\n",n,pi);
}
