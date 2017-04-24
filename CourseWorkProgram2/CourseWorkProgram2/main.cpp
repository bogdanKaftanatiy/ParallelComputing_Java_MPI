#include <iostream>
#include <limits.h>
#include "mpi.h"

using namespace std;

const int N = 9;

void inputMatrix(int matrix[N][N]);
void outputMatrix(int matrix[N][N]);
void inputVector(int vector[N]);
void outputVector(int vector[N]);

void ckeckSize(int r, int s);

int maxNumber(int vector[N], int start, int end);

void sendMatrixPart(int matrix[N][N], int start, int end, int dest, int tag);
void recvMatrixPart(int matrix[N][N], int start, int end, int source, int tag, MPI_Status status);

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

	int P = size;
	int H = N / P;

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

	int startIndex = rank*H;
	int endIndex = (rank + 1)*H;

	//Find max element
	int a_i = maxNumber(Z, startIndex, endIndex);

	MPI_Allreduce(&a_i, &a, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);

	//Calc MA_H
	for (int i = startIndex; i < endIndex; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int M1 = 0, M2 = 0;

			for (int k = 0; k < N; k++)
			{
				M1 += MB[i][k] * MC[k][j];
				M2 += MO[i][k] * MK[k][j];
			}

			int resultValue = M1 + a * M2;
			MA[i][j] = resultValue;
		}
	}


	if (rank > 2 * P / 3 - 1 && rank < P)
	{
		sendMatrixPart(MA, startIndex, endIndex, rank - P / 3, msgTag);
	}
	if (rank > P / 3 - 1 && rank < 2 * P / 3)
	{
		int tempStart = (rank + P / 3) * H;
		int tempEnd = (rank + 1 + P / 3) * H;

		recvMatrixPart(MA, tempStart, tempEnd, rank + P / 3, msgTag, status);

		sendMatrixPart(MA, startIndex, endIndex, rank - P / 3, msgTag);
		sendMatrixPart(MA, tempStart, tempEnd, rank - P / 3, msgTag);
	}
	if (rank == 0)
	{
		int tempStart = (P / 3) * H;
		int tempEnd = (P / 3 + 1) * H;

		int secondTempStart = (2 * P / 3) * H;
		int secondTempEnd = (2 * P / 3 + 1) * H;

		recvMatrixPart(MA, tempStart, tempEnd, rank + P / 3, msgTag, status);
		recvMatrixPart(MA, secondTempStart, secondTempEnd, rank + P / 3, msgTag, status);

		sendMatrixPart(MA, startIndex, endIndex, rank + 1, msgTag);
		sendMatrixPart(MA, tempStart, tempEnd, rank + 1, msgTag);
		sendMatrixPart(MA, secondTempStart, secondTempEnd, rank + 1, msgTag);
	}
	if (rank > 0 && rank < P / 3 - 1)
	{
		int start1 = 0;
		int end1 = rank * H;

		int start2 = (P / 3) * H;
		int end2 = (P / 3 + rank) * H;

		int start3 = (2 * P / 3) * H;
		int end3 = (2 * P / 3 + rank) * H;

		recvMatrixPart(MA, start1, end1, rank - 1, msgTag, status);
		recvMatrixPart(MA, start2, end2, rank - 1, msgTag, status);
		recvMatrixPart(MA, start3, end3, rank - 1, msgTag, status);

		int tempStart = (P / 3 + rank) * H;
		int tempEnd = (P / 3 + rank + 1) * H;

		int secondTempStart = (2 * P / 3 + rank) * H;
		int secondTempEnd = (2 * P / 3 + rank + 1) * H;

		recvMatrixPart(MA, tempStart, tempEnd, rank + P / 3, msgTag, status);
		recvMatrixPart(MA, secondTempStart, secondTempEnd, rank + P / 3, msgTag, status);


		sendMatrixPart(MA, start1, endIndex, rank + 1, msgTag);
		sendMatrixPart(MA, start2, tempEnd, rank + 1, msgTag);
		sendMatrixPart(MA, start3, secondTempEnd, rank + 1, msgTag);
	}
	if (rank == P / 3 - 1)
	{
		int start1 = 0;
		int end1 = rank * H;

		int start2 = (P / 3) * H;
		int end2 = (P / 3 + rank) * H;

		int start3 = (2 * P / 3) * H;
		int end3 = (2 * P / 3 + rank) * H;

		recvMatrixPart(MA, start1, end1, rank - 1, msgTag, status);
		recvMatrixPart(MA, start2, end2, rank - 1, msgTag, status);
		recvMatrixPart(MA, start3, end3, rank - 1, msgTag, status);

		int tempStart = (P / 3 + rank) * H;
		int tempEnd = (P / 3 + rank + 1) * H;

		int secondTempStart = (2 * P / 3 + rank) * H;
		int secondTempEnd = (2 * P / 3 + rank + 1) * H;

		recvMatrixPart(MA, tempStart, tempEnd, rank + P / 3, msgTag, status);
		recvMatrixPart(MA, secondTempStart, secondTempEnd, rank + P / 3, msgTag, status);
	}


	if (rank == P / 3 - 1)
	{
		cout << "Result MA:" << endl;
		if (N <= 10)
			outputMatrix(MA);
		else
			cout << "Matrix is too large." << endl;
	}


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
			"and multiple of three. Please make sure that you input correct data!" << endl <<
			"Your threads' size is " << s << endl;
		MPI_Finalize();
		exit(-1);
	}
	if (N % 3 != 0)
	{
		if (r == 0)
			cout << "The dimension of the arrays must be a multiple of three." <<
			"Please make sure that you input correct data!" << endl <<
			"Current dimension is " << N << endl;
		MPI_Finalize();
		exit(-1);
	}
}

int maxNumber(int vector[N], int start, int end)
{
	int result = INT_MIN;
	for (int i = start; i < end; i++)
	{
		if (vector[i] > result)
		{
			result = vector[i];
		}
	}

	return result;
}

void sendMatrixPart(int matrix[N][N], int start, int end, int dest, int tag)
{
	for (int i = start; i < end; i++)
	{
		MPI_Send(matrix[i], N, MPI_INT, dest, tag, MPI_COMM_WORLD);
	}
}

void recvMatrixPart(int matrix[N][N], int start, int end, int source, int tag, MPI_Status status)
{
	for (int i = start; i < end; i++)
	{
		MPI_Recv(matrix[i], N, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
	}
}