#include <iostream>
#include "mpi.h"

#define ASIZE 3

int main(int argc, char *argv[])
{
  int rank, numtasks, namelen, rc;
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int i;
  double seed = 1;
  double init_val[ASIZE], val[ASIZE], sum, tsum;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(processor_name, &namelen);

  if (rank == 0) {   /* Only the first process in the group */
    for (i = 0; i < ASIZE; i++){
      init_val[i] = (double)i * seed;
    }
  }
  rc = MPI_Bcast(init_val, ASIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD); 
  /* Broadcast computed initial values to all other processes */

  if (rc != MPI_SUCCESS) {
    fprintf(stderr, "Oops! An error occurred in MPI_Bcast()\n");
    MPI_Abort(MPI_COMM_WORLD, rc);
  }

  for (i = 0, sum = 0.0; i < ASIZE; i++) {
    val[i] = init_val[i] * rank;
    sum += val[i];
  }
  printf("%d: My sum is %lf\n", rank, sum);

  /* Send sum back to the first process */
  if (rank != 0){/* All processes except the one of rank 0 */
    MPI_Send(&sum, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
  }
  else {
    tsum = sum;
    for (i = 1; i < numtasks; i++) {
      MPI_Recv(&sum, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 1, 
	       MPI_COMM_WORLD, &status);
      tsum += sum;
    }
    printf("%d: Total sum is %lf\n", rank, tsum);
  }

  MPI_Finalize();
}
