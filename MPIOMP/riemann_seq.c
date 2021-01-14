#include <stdio.h>
#include <stdlib.h>
#include <string.h>
double  avg(double x,double y);
void riemann_MP(double a,double b);
double f(double x);

int main(void){
  double a=1;double b=2;
  puts("the integral of 1/x from 1 to 2 is: ");
  riemann_MP(1,2);
  return 0;
}

//midpoint version of riemann sum
void  riemann_MP(double a,double b){

  double numOfTerms,integration,step,midP,delta_x;
  numOfTerms=10000;
  step=(b-a)/numOfTerms;
  midP=avg(a,a+step);
  // delta_x=1;
  integration = 0;
  for (int i=1;i<numOfTerms;i++){
      integration = integration + f(midP)*step;
      // delta_x=((a+step*i) - (a+step*(i-1)));
      midP=avg(a+step*(i+1),a+step*i);
  }
  printf("%.15lf\n", integration);
}

double avg(double x,double y){
  return (x+y)/2;
}

double f(double x) {return 1/x;}
       
