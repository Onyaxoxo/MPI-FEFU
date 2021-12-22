#include <iostream>
#include <cstdlib>	//rand
#include "mpi.h"

using namespace std;

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	srand(time(0)); 
	int rank, n, i, a, message;
	int x = 10;
	int mass[x];
	int nech;		//произведение нечётных
	int max;		//наибольшее отрицательное
	
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0)
	{
		cout << "Root Process: " << rank << "\n";
		for (i=1; i<n; i++)
		{
			MPI_Recv(&mass[0], x, MPI_INT, MPI_ANY_SOURCE,MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			cout << "Process " << i <<endl;
			cout <<"Случайные числа: \t";
			
			max = -10000;
			for  (a = 0; a < x; a++)
			{
				cout  << mass[a] << "\t";
				if (mass[a] < 0  && mass[a] > max)
				{
					max = mass[a];
				}
			}
			cout << endl;
	
			cout <<"Из них нечётные:\t";
			nech = 1;
			for  (a = 0; a < x; a++)
			{
				if (mass[a]  %  2 == 1 || mass[a]  %  2 == -1)
				{
					cout  << mass[a] << "\t";
					nech *= mass[a];
				}
				else cout <<"\t";

			}
			cout << endl;		
			
			cout << "Произведение всех нечётных чисел: " << nech << endl;
			
			cout << "Наибольшее из отрицательных: " << max << endl;
			
			cout << "Их разность: " << nech - max;
			
			cout << endl << endl;	
		}
	}
	else 
	{
		for ( a= 0 ;	a < x; 	a++) 
		{
			mass[a] = rand()%(20*rank) - (10*rank);
		}
		MPI_Send(&mass[0],x,MPI_INT,0,0,MPI_COMM_WORLD);
	}
		
	
	MPI_Finalize();
	return 0;
}