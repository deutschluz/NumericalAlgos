// Integration by Simpson's method- sequential version

#include <stdio.h>
#include <math.h>

#define n 10000 //must be even

double f(double x);
void simpson(double a,double b);

int main(void){
  puts("the integral of 1/x from 1 to 2 is");
  double a=1.0;double b=2.0;
  simpson(a,b);
  return 0;
}

void simpson(double a,double b){
  double integration,step;
  int i;
  step=(b-a)/n;

  for(i=1,integration=0;i<n/2;i++)
    integration += 2*f(a+(2*i-1)*step)+f(a+2*i*step);
  
  integration *= 2;
  integration += f(a) +f(b) +4*f(b-step);
  integration *= step/3;
  printf("%.15lf\n",integration);
}

double f(double x){
  return 1/x;
}
