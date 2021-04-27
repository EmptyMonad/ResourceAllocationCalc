/*
Banker's Algorithm
Calculation Reference Doc: https://www.geeksforgeeks.org/program-bankers-algorithm-set-1-safety-algorithm/
*/


#include <iostream>
#include <fstream>

using namespace std;

/*Variable Declarations*/

const int N = 5; //number of processes, needs to be const for these void functions to hold, couldn't process it via text, PAL Lab is weak!!!!
const int M = 4; //number of resources, needs to be const for these void functions to hold, couldn't process it via text, PAL Lab is weak!!!!

/* End of Variable Decalrations */

/* Function Declarations */

void calc(int need[N][M], int max[N][M], int allocated[N][M]) //this counts through both processes and resources in order to acquire the values of need/max/allocated.
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			need[i][j] = max[i][j] - allocated[i][j];
}

bool execute(int processes[], int available[], int max[][M], int allocated[][M]) //this executes calculations based on N processes, A available resources, the 2-d array of Max, and the 2-d array of allocated resources
	{
		int need[N][M];
		calc(need, max, allocated); //calculates the values to process through the system
		bool done[N] = {0};
		int required[M];
		int sequence[N];
		for (int v = 0; v < M; v++)
            required[v] = available[v];
		int count = 0;
		while (count < N)
		{
			bool found = false;
			for (int w = 0; w < N; w++)
			{
				if (done[w] == 0) //these checks are arcane, they check at each level for each part of the 2d arrays and compare it to the need. If they pass without error, it is listed as true. Otherwise, false and unsafe.
				{
					for (int x = 0; x < M; x++)
					{	if (need[w][x] > required[x])
						{
							break;
						}
						if (x == M)
						{
							for (int y = 0; y < M; y++)
								required[y] += allocated[w][y];
							sequence[count++] = w;
							done[w] = 1;
							found = true;
						}
					}
				}
			}
        if (found == false)
        {
            cout << "This is not a safe allotment.";
            return false;
        }
	}
    cout << "The Safe Sequence is: ";
    for (int z = 0; z < N ; z++)
        cout << sequence[z] << " ";
    return true;
}

/* End of Function Declarations */

int main() //herein lies a bunch of syntax utilized to print the correct results
{
	int processes[N];
	int available[N];
	int max[N][M];
	int allocated[N][M];
	int need[N][M];
	int request[M];
	ifstream input ("input.txt");
	/*here is where we extract the values from the text file. Notably, the 1:0420 was changed to 0420 due to parsing errors. Likewise, the 5,4 for process number and resource amount have been omitted due to these being easier used as predefined constants.*/
	for (int count = 0; count < N; count ++)
		processes[count] = count;
	for (int row = 0; row < N; row++)
	{
		for(int col = 0; col < M; col++)
			input >> allocated[row][col];
	}
	
	for (int row = 0; row < N; row++)
	{
		for(int col = 0; col < M; col++)
			input >> max[row][col];
	}
	
	for (int row = 0; row < M; row++)
			input >> available[row];
		
	for (int row = 0; row < M; row++)
			input >> request[row];
/*conclusion of file reading. */
	calc(need, max, allocated);
	cout << "There are " << N << " " << "processes in the system.\n";
	cout << "There are " << M << " " << "resource types.\n";
	cout << "\nThe Allocation Matrix is... \n";
	for (int row = 0; row < N; row++)
	{
		cout << row << ": ";
		for(int col = 0; col < M; col++)
			cout << allocated[row][col] << " ";
		cout << endl;
	}
	cout << "\nThe Max Matrix is... \n";
	for (int row = 0; row < N; row++)
	{
		cout << row << ": ";
		for(int col = 0; col < M; col++)
			cout << max[row][col] << " ";
		cout << endl;
	}
	cout << "\nThe Need Matrix is... \n";
	for (int row = 0; row < N; row++)
	{
		cout << row << ": ";
		for(int col = 0; col < M; col++)
			cout << need[row][col] << " ";
		cout << endl;
	}
	
	cout << "\nThe Request Vector is... \n";
	cout << "   A B C D \n1: ";
	for (int row = 0; row < M; row++)
	{	
		cout << request[row] << " ";
	}
	cout << "\n";
	cout << "\nThe Available Vector is... \n";
	cout << "A B C D \n";
	for (int row = 0; row < M; row++)
	{		
		cout << available[row]<< " ";
	}
	cout << "\n";
	execute(processes, available, max, allocated);
    return 0;
}





















