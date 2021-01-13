


int maxSubseqSum(int a[], unsigned int n);




int maxSubseqSum(int a[],unsigned int n){
  int this_sum,max_sum, best_i,best_j,i,j,k;

  max_sum=0;best_i=best_j=-1;

  for(i=0;i<n;i++)
    for(j=i;j<n;j++){
      this_sum=0;
      for(k=i;k<=j;k++)
	this_sum+=a[k];

      if(this_sum> max_sum){
	max_sum=this_sum;
        best_i=i;
	best_j=j;
      }
    }
  return(max_sum);
}
