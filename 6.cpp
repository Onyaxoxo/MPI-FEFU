#include <iostream>
#include "mpi.h"
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	int rank, n, i, j;
	int x = 100;
	int A[x], B[x];
	int sum = 0;
	int sumloc = 0;
	
	for (i = 0; i < x; i++)
	{
		A[i] = 1;
		B[i] = 1;
	}
	
	int part;		//Длина кусков, которые считают процессы
	int last;			//Последние оставшиеся элементы массива
	
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	
	if (rank == 0)
	{
		part  = x / (n - 1);
		last = x % (n -1 );
		cout << endl;
		cout << "Элементов: " << x << endl;
		cout << "Процессов для рассчёта: " << n - 1 << endl;
		cout << "Элементов на один процесс: " << part << endl;
		cout << "Остаток: " << last << endl;
		
		for ( i = 1 ;	i < n;	 i++)
		{
			MPI_Recv(&sumloc, 1, MPI_INT, MPI_ANY_SOURCE,MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			sum += sumloc;
		}
		
		for (i = x - last; i < x;  i++)	
		{
			sum += A[i] * B[i];
		}
		
		sleep(2);
		cout << endl;
		cout << "Сумма = " << sum << endl;
		cout << endl;
	}
		
	else 
	{
		sleep(1);
		part  = x / (n - 1);
		last = x % (n -1 );
		for (i = 0; i < part; i++)
		{
			sumloc += A[part * (rank -1) + i] * B[part * (rank -1) + i];
	//		cout << rank << ": " << A[part * (rank -1) + i] << " * " << B[part * (rank -1) + i] << " = " << C[i] << endl;
		}
		MPI_Send(&sumloc,  1,  MPI_INT,  0,  0,  MPI_COMM_WORLD);

	}
		

	
	MPI_Finalize();
	return 0;
}