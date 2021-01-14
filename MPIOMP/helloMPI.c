#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  char buf[256];
  int my_rank,num_procs;

  //init the comm infrastructure
  MPI_Init(&argc,&argv);
  //id this proc
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  //find out how many total procs are active
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  //up to this point all progs have been doing the
  // same thing; here we check the rank to distinguish
  // the roles of the programs
  if (my_rank == 0){
    int other_rank;
    printf("We have %i processes.\n", num_procs);

    //send mesg to all other procs
    for(other_rank=1;other_rank <num_procs; other_rank++){
      sprintf(buf,"Hello %i!",other_rank);
      MPI_Send(buf,sizeof(buf),MPI_CHAR,other_rank,
	       0,MPI_COMM_WORLD);
    }

    //recv mesgs from other procs

    for(other_rank=1;other_rank<num_procs;other_rank++){
      MPI_Recv(buf,sizeof(buf),MPI_CHAR,other_rank,
	       0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      printf("%s\n",buf);
    }
  }else{
    //recv msg from proc 0
    MPI_Recv(buf,sizeof(buf),MPI_CHAR,0,0,MPI_COMM_WORLD,
	     MPI_STATUS_IGNORE);
    assert(memcmp(buf,"Hello ",6) == 0);

    //send msg to proc 0
    sprintf(buf,"Process %i reporting for duty.",my_rank);
    MPI_Send(buf,sizeof(buf),MPI_CHAR,0,0,MPI_COMM_WORLD);
  }
  //tear down comm infra
  MPI_Finalize();
  return 0;
}
