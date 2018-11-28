#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>

#define ARRAY_SIZE 17

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


int main()
{


int column=1;

clock_t begin = clock();
for(int row=1;row<=ARRAY_SIZE;row++){
		placed_queen=0;

		 for(int i=0;i<ARRAY_SIZE;i++)
		{
			chess_board[i]=0;
			diagnoal_lhs[i]=0;
			diagnoal_rhs[i]=0;

		}


		chess_board[0]=row;
		diagnoal_lhs[0]=row+column;
		diagnoal_rhs[0]=row-column;
		placed_queen++;
		place_queen(2);


}

clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("The total time taken is %f",time_spent);
printf("\n");
printf("The value of k is %d",ARRAY_SIZE);
printf("\n");
printf("The total solution is %d",total_solution);
printf("\n");
return 0;
}
