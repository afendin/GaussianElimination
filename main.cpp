#include<iostream>
#include<math.h>
using namespace std;


int main()
{
    int n;
    cout << "Enter number of equations:\n";
    cin >> n;
    float mat[n][n + 1]; // we put constants in n + 1 column

    cout << "Fill the matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            cin >> mat[i][j];
        }
    }
    // Tested on the marticies below
    // 1 3 2 13 4 4 -3 3 5 1 2 13                                           [3 equations] simple one
    // 2 5 4 1 20 1 3 2 1 11 2 10 9 7 40 3 8 9 2 37                         [4 equations] causes round-off error
    // 0 7 -1 3 1 5 0 3 4 1 7 7 6 2 0 2 -1 2 2 1 2 0 2 3 3 4 1 -2 1 4       [5 equations] test divizion by zero


    for (int column = 0; column < n - 1; ++column) {
        // partial pivoting
        if (fabs(mat[column][column]) < 1.0e-12) {
            for (int i = column + 1; i < n; ++i) {
                if (fabs(mat[i][column]) > fabs(mat[column][column])) {
                    for (int term = 0; term < n+1; ++term) {
                        float temp = mat[column][term];
                        mat[column][term] = mat[i][term];
                        mat[i][term] = temp;
                    }
                    break;
                }
            }
        }
        //

	// Elimination
        int lRow = column; // pivot row
        for (int row = lRow + 1; row < n; ++row) {
            if (mat[row][column] == 0) // if leading value is zero, skip row
                continue;

            float factor = mat[lRow][column] / mat[row][column];
            for (int term = lRow; term < n + 1; ++term) { // modify current row
                mat[row][term] = mat[lRow][term] - factor * mat[row][term];
            }
        }
    }

    cout << "\nResult matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << mat[i][j] << "      ";
        }
        cout << endl;
    }

    // Backward substitution
    float res[n];
    for (int row = n - 1; row >= 0; --row) {
        float sum = 0;
        for (int term = row + 1; term < n;  ++term){
            sum += mat[row][term] * res[term];
        }
        res[row] =  (mat[row][n] - sum) / mat[row][row];
    }

    cout << "\nSolutins:\n";
    for (int i = 0; i < n; ++i)
        cout << "X" << i << "=" << res[i] << endl;

    return 0;
}
