#include <iostream>
#include "mpi.h"

using namespace std;

const int N = 6;
const int P = 6;
const int H = N / P;

void inputMatrix(int matrix[N][N]);
void outputMatrix(int matrix[N][N]);
void inputVector(int vector[N]);
void outputVector(int vector[N]);

void ckeckSize(int r, int s);

bool isNull(int V[N], int M1[N][N], int M2[N][N], int M3[N][N], int M4[N][N]);

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	int rank, size;
	int Z[N];
	int MA[N][N], MB[N][N], MC[N][N], MO[N][N], MK[N][N];
	int a;

	MPI_Status status;
	int msgTag = 0;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	ckeckSize(rank, size);

	//input data
	if (rank == 0)
	{
		inputMatrix(MB);
		inputMatrix(MO);

		MPI_Send(MB, N*N, MPI_INT, 1, msgTag, MPI_COMM_WORLD);
		MPI_Send(MO, N*N, MPI_INT, 1, msgTag, MPI_COMM_WORLD);

		MPI_Send(MB, N*N, MPI_INT, P / 3, msgTag, MPI_COMM_WORLD);
		MPI_Send(MO, N*N, MPI_INT, P / 3, msgTag, MPI_COMM_WORLD);

		//////////////////////////////////////////////////////////

		MPI_Recv(MC, N*N, MPI_INT, 1, msgTag, MPI_COMM_WORLD, &status);
		MPI_Recv(MK, N*N, MPI_INT, 1, msgTag, MPI_COMM_WORLD, &status);
		MPI_Recv(Z, N, MPI_INT, 1, msgTag, MPI_COMM_WORLD, &status);

		MPI_Send(MC, N*N, MPI_INT, P / 3, msgTag, MPI_COMM_WORLD);
		MPI_Send(MK, N*N, MPI_INT, P / 3, msgTag, MPI_COMM_WORLD);
		MPI_Send(Z, N, MPI_INT, P / 3, msgTag, MPI_COMM_WORLD);

	}
	else if (rank == P / 3 - 1)
	{
		inputVector(Z);
		inputMatrix(MC);
		inputMatrix(MK);

		MPI_Recv(MB, N*N, MPI_INT, P / 3 - 2, msgTag, MPI_COMM_WORLD, &status);
		MPI_Recv(MO, N*N, MPI_INT, P / 3 - 2, msgTag, MPI_COMM_WORLD, &status);

		MPI_Send(MB, N*N, MPI_INT, 2 * P / 3 - 1, msgTag, MPI_COMM_WORLD);
		MPI_Send(MO, N*N, MPI_INT, 2 * P / 3 - 1, msgTag, MPI_COMM_WORLD);

		///////////////////////////////////////////////////////

		MPI_Send(MC, N*N, MPI_INT, P / 3 - 2, msgTag, MPI_COMM_WORLD);
		MPI_Send(MK, N*N, MPI_INT, P / 3 - 2, msgTag, MPI_COMM_WORLD);
		MPI_Send(Z, N, MPI_INT, P / 3 - 2, msgTag, MPI_COMM_WORLD);

		MPI_Send(MC, N*N, MPI_INT, 2 * P / 3 - 1, msgTag, MPI_COMM_WORLD);
		MPI_Send(MK, N*N, MPI_INT, 2 * P / 3 - 1, msgTag, MPI_COMM_WORLD);
		MPI_Send(Z, N, MPI_INT, 2 * P / 3 - 1, msgTag, MPI_COMM_WORLD);
	}

	if (rank > 0 && rank < P / 3 - 1)
	{
		MPI_Recv(MB, N*N, MPI_INT, rank - 1, msgTag, MPI_COMM_WORLD, &status);
		MPI_Recv(MO, N*N, MPI_INT, rank - 1, msgTag, MPI_COMM_WORLD, &status);

		MPI_Send(MB, N*N, MPI_INT, rank + 1, msgTag, MPI_COMM_WORLD);
		MPI_Send(MO, N*N, MPI_INT, rank + 1, msgTag, MPI_COMM_WORLD);

		MPI_Send(MB, N*N, MPI_INT, rank + P / 3, msgTag, MPI_COMM_WORLD);
		MPI_Send(MO, N*N, MPI_INT, rank + P / 3, msgTag, MPI_COMM_WORLD);

		////////////////////////////////////////////////////////////

		MPI_Recv(MC, N*N, MPI_INT, rank + 1, msgTag, MPI_COMM_WORLD, &status);
		MPI_Recv(MK, N*N, MPI_INT, rank + 1, msgTag, MPI_COMM_WORLD, &status);
		MPI_Recv(Z, N, MPI_INT, rank + 1, msgTag, MPI_COMM_WORLD, &status);

		MPI_Send(MC, N*N, MPI_INT, rank - 1, msgTag, MPI_COMM_WORLD);
		MPI_Send(MK, N*N, MPI_INT, rank - 1, msgTag, MPI_COMM_WORLD);
		MPI_Send(Z, N, MPI_INT, rank - 1, msgTag, MPI_COMM_WORLD);

		MPI_Send(MC, N*N, MPI_INT, rank + P / 3, msgTag, MPI_COMM_WORLD);
		MPI_Send(MK, N*N, MPI_INT, rank + P / 3, msgTag, MPI_COMM_WORLD);
		MPI_Send(Z, N, MPI_INT, rank + P / 3, msgTag, MPI_COMM_WORLD);
	}

	if (rank > P / 3 - 1 && rank < 2 * P / 3)
	{
		MPI_Recv(MB, N*N, MPI_INT, rank - P / 3, msgTag, MPI_COMM_WORLD, &status);
		MPI_Recv(MO, N*N, MPI_INT, rank - P / 3, msgTag, MPI_COMM_WORLD, &status);

		MPI_Send(MB, N*N, MPI_INT, rank + P / 3, msgTag, MPI_COMM_WORLD);
		MPI_Send(MO, N*N, MPI_INT, rank + P / 3, msgTag, MPI_COMM_WORLD);

		/////////////////////////////////////////////////////////////

		MPI_Recv(MC, N*N, MPI_INT, rank - P / 3, msgTag, MPI_COMM_WORLD, &status);
		MPI_Recv(MK, N*N, MPI_INT, rank - P / 3, msgTag, MPI_COMM_WORLD, &status);
		MPI_Recv(Z, N, MPI_INT, rank - P / 3, msgTag, MPI_COMM_WORLD, &status);

		MPI_Send(MC, N*N, MPI_INT, rank + P / 3, msgTag, MPI_COMM_WORLD);
		MPI_Send(MK, N*N, MPI_INT, rank + P / 3, msgTag, MPI_COMM_WORLD);
		MPI_Send(Z, N, MPI_INT, rank + P / 3, msgTag, MPI_COMM_WORLD);
	}

	if (rank > 2 * P / 3 - 1 && rank < P)
	{
		MPI_Recv(MB, N*N, MPI_INT, rank - P / 3, msgTag, MPI_COMM_WORLD, &status);
		MPI_Recv(MO, N*N, MPI_INT, rank - P / 3, msgTag, MPI_COMM_WORLD, &status);

		/////////////////////////////////////////////////////////////////////

		MPI_Recv(MC, N*N, MPI_INT, rank - P / 3, msgTag, MPI_COMM_WORLD, &status);
		MPI_Recv(MK, N*N, MPI_INT, rank - P / 3, msgTag, MPI_COMM_WORLD, &status);
		MPI_Recv(Z, N, MPI_INT, rank - P / 3, msgTag, MPI_COMM_WORLD, &status);
	}

	cout << "Tread N_" << rank << " - " << isNull(Z, MB, MO, MC, MK) << endl;

	/*if (rank == 0)
	{
	cout << "Thread N_" << rank << endl;
	cout << "Vector Z:" << endl;
	outputVector(Z);
	cout << "Matrix MB:" << endl;
	outputMatrix(MB);
	cout << "Matrix MO:" << endl;
	outputMatrix(MO);
	cout << "Matrix MC:" << endl;
	outputMatrix(MC);
	cout << "Matrix MK:" << endl;
	outputMatrix(MK);
	}*/

	MPI_Finalize();
	return 0;
}

void inputMatrix(int matrix[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			matrix[i][j] = 1;
		}
	}
}
void outputMatrix(int matrix[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void inputVector(int vector[N])
{
	for (int i = 0; i < N; i++)
	{
		vector[i] = 1;
	}
}
void outputVector(int vector[N])
{
	for (int i = 0; i < N; i++)
	{
		cout << vector[i] << " ";
	}
	cout << endl;
}
void ckeckSize(int r, int s)
{
	if (s < 6 || s % 3 != 0)
	{
		if (r == 0)
			cout << "For correct program work the count of threads must be more than 6" <<
			"and multiple of three. Please make sure that you input correct data"
			<< endl << "Your threads' size is " << s << endl;
		MPI_Finalize();
		exit(-1);
	}
}

bool isNull(int V[N], int M1[N][N], int M2[N][N], int M3[N][N], int M4[N][N]) {

	for (int i = 0; i < N; i++)
	{
		if (V[i] != 1) return true;
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (M1[i][j] != 1) return true;
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (M2[i][j] != 1) return true;
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (M3[i][j] != 1) return true;
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (M4[i][j] != 1) return true;
		}
	}
	return false;
}