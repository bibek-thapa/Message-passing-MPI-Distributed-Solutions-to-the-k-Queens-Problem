#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <mpi.h>

#define MASTER 0
#define TAG 0
#define ARRAY_SIZE 15

int chess_board[ARRAY_SIZE];
int diagnoal_lhs[ARRAY_SIZE];
int diagnoal_rhs[ARRAY_SIZE];
int temp[ARRAY_SIZE];
int placed_queen = 0;
int total_solution =0;



void print_result(int temp[ARRAY_SIZE])
{
for(int row =0;row<=ARRAY_SIZE-1;row++)
	{
		 printf("%d\t",temp[row]);

	}
printf("\n");


}

bool isNotSafe(int temp[ARRAY_SIZE],int row,int col,int sum_lhs,int diff_rhs)
{
bool result=true;
for(int j=0;j<col-1;j++){
		if(chess_board[j]==row || row+col==diagnoal_lhs[j]||row-col==diagnoal_rhs[j])
			{
				result=false;
			}

}
 return result;



}

void place_queen (int col)
{

	if (placed_queen==ARRAY_SIZE) {
		total_solution++;
			}
	else {
		// try all rows
		for (int row=1; row <= ARRAY_SIZE; row++) {

		bool res=isNotSafe(chess_board,row,col,row+col,row-col);

			if(res==true)
				{
					chess_board[col-1]=row;
					placed_queen++;
					diagnoal_lhs[col-1]=row+col;
					diagnoal_rhs[col-1]=row-col;
					place_queen(col+1);
					chess_board[col-1]=0;
					placed_queen--;
					 diagnoal_lhs[col-1]=0;
					diagnoal_rhs[col-1]=0;

				}
		}

		}
}


int main(int argc,char** argv)
{


int sum;
int my_rank, source, num_nodes;
double start, end;

MPI_Request req;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
MPI_Comm_size(MPI_COMM_WORLD, &num_nodes);
start = MPI_Wtime();


   placed_queen=0;
	for (int i = 0; i < ARRAY_SIZE; i++){
		chess_board[i] = 0;
		diagnoal_lhs[i]=0;
		diagnoal_rhs[i]=0;
	}
	chess_board[0] = my_rank + 1;
	diagnoal_lhs[0]=my_rank+1+1;
	diagnoal_rhs[0]=my_rank+1-1;
   placed_queen++;
	place_queen(2);


printf("total_solution from process %d : %d",my_rank,total_solution);
printf("\n");

if (my_rank != MASTER) {
	MPI_Send(&total_solution, 1, MPI_INT, MASTER, TAG, MPI_COMM_WORLD);
}
else {
	sum = total_solution;
	for (source = 1; source < num_nodes; source++) {
		MPI_Recv(&total_solution, 1, MPI_INT, source, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		sum = sum + total_solution;
	}

	printf("Value of k is %d",ARRAY_SIZE);
	printf("\n");

   printf("Total solutions is %d",sum);
   printf("\n");
   end = MPI_Wtime();
	printf("Execution time for %d nodes: %f\n", num_nodes ,end - start);
printf("\n");
}

MPI_Finalize();
return 0;
}
