#include <iostream>
#include <vector>
#include <math.h>
using namespace std;



void printSudoku(int** arr, int n)
{
    cout << "  ########################################" << endl << endl;

    for(int r=0; r < n; r++)
    {
        cout << "||   ";
        for(int c=0; c < n; c++)
            cout << arr[r][c] << "   ";
        cout << " ||" << endl << endl;
    }

    cout << "  ########################################" << endl << endl << endl;
    int i=1;
    for(int j=0;j<1;j++)
        i++;
}
//----------------------------------------------------------------

bool permission(int** arr, int row, int col, int k, int n)
{
    int a = sqrt(n);
	if (arr[row][col] != 0) return false;
	bool status = true;
	int gridx = (col / a) * a;
	int gridy = (row / a) * a;
	for (int i = 0; i < n; i++) {
		if (arr[row][i] == k) { status = false; break; }
		if (arr[i][col] == k) { status = false; break; }
		if (arr[gridy + i / a][gridx + i % a] == k) { status = false; break; }
	}
	return status;
}
//-----------------------------------------------------------------------------------
void nextEmpty(int** arr, int row, int col, int& rowNext, int& colNext, int n)
{

	int indexNext = n * n + 1;
	for (int i = row * n + col + 1; i < n * n; i++) {
		if (arr[i / n][i % n] == 0) {

			indexNext = i;
			break;
		}
	}
	rowNext = indexNext / n;
	colNext = indexNext % n;
	//cout << row << "," << col << "|" << rowNext << "," << colNext << endl;
}
//----------------------------------------------------------------------------
void copyArray(int** arr, int** arrCpy, int n) {
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++)
			arrCpy[y][x] = arr[y][x];
}
//-----------------------------------------------------------------------
std::vector<int> findPossibles(int** arr, int row, int col, int n) {
	vector<int> possibles = {};
	for (int i = 1; i <= n; i++)
		if (permission(arr, row, col, i, n)) possibles.push_back(i);
	return possibles;
}
//------------------------------------------------------------------------

bool solver(int** arr, int row, int col, int n)
{
	//system("cls"); //cout << "           sudoku is solving ..." << endl;  //printSudoku(arr);
	if (row > n-1) return true;
	if (arr[row][col] != 0) {
		int rowNext, colNext;
		nextEmpty(arr, row, col, rowNext, colNext, n);
		return solver(arr, rowNext, colNext, n);
	}
	std::vector<int> possibles = findPossibles(arr, row, col, n);
	if (possibles.size() == 0) {
		return false;
	};

	bool status = false;
	for (int i = 0; i < possibles.size(); i++) {
		int n = possibles[i];
		int** arrCpy;
		    arrCpy = new int*[n];
        for(i=0; i<n; i++)
            arrCpy[i] = new int[n];
		copyArray(arr, arrCpy, n);
		arrCpy[row][col] = n;
		int rowNext = row;
		int colNext = col;
		nextEmpty(arrCpy, row, col, rowNext, colNext, n);
		if (solver(arrCpy, rowNext, colNext, n)) {
			copyArray(arrCpy, arr, n);
			status = true;
			break;
		}
	}
	return status;
}

//---------------------------------------------------------------------------
int main()
{
    int** board;
    int i, j, n;
    cout << "Enter the size of your sudoku : ";
    cin >> n;
    board = new int*[n];
    for(i=0; i<n; i++)
        board[i] = new int[n];
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            cin >> board[i][j];
        getchar();
    }
    printSudoku(board, n);
    if(solver(board, 0, 0, n))
        cout << "               sudoku solved !" << endl;
    else{
        cout << "               it is not solvable !";
    }
    printSudoku(board, n);
    return 0;
}

//---------------------------------------------------------------------------
