/* this program computes pi using the rectangle rule */

#include <stdio.h>

#define INTERVALS 1000000

int main(int argc,char *argv[]){
  double area,ysum,xi;
  int i;

  ysum=0.0;
  for(i=0;i<INTERVALS;i++){
    xi=(1.0/INTERVALS)*(i+0.5);
    ysum += 4.0/(1.0+xi*xi);
  }
  area=ysum *(1.0/INTERVALS);
  printf("Area is %13.11f\n",area);
  return 0;
}
