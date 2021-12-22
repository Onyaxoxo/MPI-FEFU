#include <iostream>
#include <mpi.h>
using namespace std;
int main(int argc, char **argv)
{
	int n = 8;
	
	double time_start, time_finish;
	int rank, size, message;
	int nk;
	
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	nk = size / 2;
	time_start = MPI_Wtime();
	int a[1] = {1};
	
	while (nk >= 1)
	{
		if ( (rank >= nk) && (rank < nk * 2) )		//Вторая половина
		{
			MPI_Send(&a,1,MPI_INT,rank - nk,0,MPI_COMM_WORLD);
		}
		else if ( rank < nk )											//Первая половина
		{
			MPI_Recv(&message,1,MPI_INT,rank + nk,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
			a[0] += message;
			if (rank == 0)
				cout << "Крайний левый: " <<  a[0] << endl;
		}
		nk /= 2;
	}
	
	if (rank == 0)
	{
		cout << a[0] << endl;
	}
	MPI_Finalize();
}