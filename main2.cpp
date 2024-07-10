#include <iostream>
#include <vector>
using namespace std;

void GetSudoku(int a[9][9])
{
    cout << "Enter your Sudoku : " << endl;
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            cin >> a[i][j];
        }
        getchar();
    }
}

void printSudoku(int arr[9][9])
{
    cout << "  ########################################" << endl << endl;

    for(int r=0; r < 9; r++)
    {
        cout << "||   ";
        for(int c=0; c < 9; c++)
            cout << arr[r][c] << "   ";
        cout << " ||" << endl << endl;
    }

    cout << "  ########################################" << endl << endl << endl;
    int i=1;
    for(int j=0;j<1;j++)
        i++;
}
//----------------------------------------------------------------

bool permission(int arr[9][9], int row, int col, int n)
{
	if (arr[row][col] != 0) return false;
	bool status = true;
	int gridx = (col / 3) * 3;
	int gridy = (row / 3) * 3;
	for (int i = 0; i < 9; i++) {
		if (arr[row][i] == n) { status = false; break; }
		if (arr[i][col] == n) { status = false; break; }
		if (arr[gridy + i / 3][gridx + i % 3] == n) { status = false; break; }
	}
	return status;
}
//-----------------------------------------------------------------------------------
void nextEmpty(int arr[9][9], int row, int col, int& rowNext, int& colNext)
{

	int indexNext = 9 * 9 + 1;
	for (int i = row * 9 + col + 1; i < 9 * 9; i++) {
		if (arr[i / 9][i % 9] == 0) {

			indexNext = i;
			break;
		}
	}
	rowNext = indexNext / 9;
	colNext = indexNext % 9;
	//cout << row << "," << col << "|" << rowNext << "," << colNext << endl;
}
//----------------------------------------------------------------------------
void copyArray(int arr[9][9], int arrCpy[9][9]) {
	for (int y = 0; y < 9; y++)
		for (int x = 0; x < 9; x++)
			arrCpy[y][x] = arr[y][x];
}
//-----------------------------------------------------------------------
std::vector<int> findPossibles(int arr[9][9], int row, int col) {
	vector<int> possibles = {};
	for (int i = 1; i <= 9; i++)
		if (permission(arr, row, col, i)) possibles.push_back(i);
	return possibles;
}
//------------------------------------------------------------------------

bool solver(int arr[9][9], int row, int col)
{
	//system("cls");
	//cout << "           sudoku is solving ..." << endl;
	//printSudoku(arr);
	if (row > 8) return true;
	if (arr[row][col] != 0) {
		int rowNext, colNext;
		nextEmpty(arr, row, col, rowNext, colNext);
		return solver(arr, rowNext, colNext);
	}

	std::vector<int> possibles = findPossibles(arr, row, col);

	if (possibles.size() == 0) {

		return false;

	};

	bool status = false;
	for (int i = 0; i < possibles.size(); i++) {
		int n = possibles[i];
		int arrCpy[9][9];
		copyArray(arr, arrCpy);
		//cout << "(" << row << "," << col << ") =>" << n << endl;
		arrCpy[row][col] = n;
		int rowNext = row;
		int colNext = col;
		nextEmpty(arrCpy, row, col, rowNext, colNext);
		if (solver(arrCpy, rowNext, colNext)) {
			copyArray(arrCpy, arr);
			status = true;
			break;
		}
	}
	return status;
}

//---------------------------------------------------------------------------
int main()
{
	int board[9][9];/* = {
		{5,3,0,0,7,0,0,0,0},
		{6,0,0,1,9,5,0,0,0},
		{0,9,8,0,0,0,0,6,0},
		{8,0,0,0,6,0,0,0,3},
		{4,0,0,8,0,3,0,0,1},
		{7,0,0,0,2,0,0,0,6},
		{0,6,0,0,0,0,2,8,0},
		{0,0,0,4,1,9,0,0,5},
		{0,0,0,0,8,0,0,7,9}
	};*/

	GetSudoku(board);
    printSudoku(board);
    if(solver(board, 0, 0))
        cout << "               sudoku solved !" << endl;
    else{
        cout << "               it is not solvable !";
    }
    printSudoku(board);
    return 0;
}

//---------------------------------------------------------------------------
