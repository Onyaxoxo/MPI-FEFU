#include <iostream>
#include <mpi.h>
using namespace std;
int main(int argc, char **argv)
{
	int n = 100000;
	
	int mess[n];
	double time_start, time_finish;
	double Time = 0; 
	double R = 0, S = 0;
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	
	if (rank == 0)
	{
		int message[n];
		time_start = MPI_Wtime();
		for (int i = 0; i < 10; i++)
		{
			MPI_Send(&message,n,MPI_INT,1,0,MPI_COMM_WORLD);
			MPI_Recv(&mess, n, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		}
		time_finish = MPI_Wtime();
		Time = time_finish - time_start;
		R = (2 * 10 * ( n * sizeof(int) ) ) / Time;
		R /= 1024;
		R /= 1024;		
		cout <<endl << "Пропускная способность: " << R <<endl;
		Time = 0;
		
		int messageLat[1];
		time_start = MPI_Wtime();
		for (int i = 0; i < 10; i++)
		{
			MPI_Send(&messageLat, 1,MPI_INT,1,0,MPI_COMM_WORLD);
			MPI_Recv(&mess, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		}
		time_finish = MPI_Wtime();
		Time = time_finish - time_start;
		S = Time / (2 * 10);
		cout << "Латентнось: " << S <<endl<< endl ;
	}
	
	
	if (rank == 1)
	{
		for (int i = 0; i < 10; i++)
		{
			MPI_Recv(&mess, n, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			MPI_Send(&mess,n,MPI_INT,0,0,MPI_COMM_WORLD);
		}
		for (int i = 0; i < 10; i++)
		{
			MPI_Recv(&mess, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			MPI_Send(&mess,1,MPI_INT,0,0,MPI_COMM_WORLD);
		}
	}
	MPI_Finalize();
}