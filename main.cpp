#include "yyc_algorithm.h"
#include "bt_algorithm.h"
#include "basic_matrix.h"
#include <iomanip>

using namespace std;

// Function to 
vector<vector<bool>> gammaOperator(const vector<vector<bool>>& A, int N) {

    if (N < 1) return {};

    int rows = A.size();
    int cols = A[0].size();

    vector<vector<bool>> result(N * rows, vector<bool>(N * cols, 0));

    for (int n = 0; n < N; ++n) {
        int rowOffset = n * rows;  
        int colOffset = n * cols;  

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result[rowOffset + i][colOffset + j] = A[i][j];
            }
        }
    }

    return result;
}


//Function to create user-input Matrix
vector<vector<bool>> userMatrix() {

    int rowNum;
    int columnNum;
    
    cout << "Number of columns of the matrix: ";
    cin >> columnNum;

    cout << "Number of rows of the matrix: ";
    cin >> rowNum;

    vector<vector<bool>> DM(rowNum, vector<bool>(columnNum));
    
    cout << endl << "Please enter each row as a string of ONLY 1's and 0's (NO spaces): " << endl;

    string rowInput;
    for(int i = 0; i < rowNum; i++) {
        cout << "Row " << i+1 << ": ";
        cin >> rowInput;

        if(rowInput.size() != columnNum) {
            cout << "Invalid input length. Please enter exactly " << columnNum << " columns" << endl << endl;
            i--;
            continue;
        }

        for(int j = 0; j < columnNum; j++) {
            DM[i][j] = rowInput[j] == '1';
        }

    }

    cout << endl;

    return DM;

}

// Function to print a matrix in desired format
void printMatrix(const vector<vector<bool>>& matrix) {

    cout << setw(4);
    for(int i = 0; i < matrix[0].size(); i++) cout << "x_" << i + 1 << " ";
    cout << endl;

    for (const auto& row : matrix) {
        for (int val : row) cout << setw(4) << val;
        cout << endl;
    }
    cout << endl;
}

int main() {

    int menu;
    cout << "Welcome to the typical testor calculator! Please select an option: " << endl;
    
    vector<vector<bool>> DM;

    do{
    cout << "1.) Input a new matrix\n"
         << "2.) Use test matrix\n"
         << "3.) Exit\n";

    cin >> menu;
    cout << endl;

    if(menu == 1) {
        DM = userMatrix(); 
        break;
    }

    else if(menu == 2) {
        // Test Matrix
        DM = {
        {1, 1, 1, 0, 0},
        {1, 1, 0, 0, 1},
        {1, 0, 1, 1, 0},
        {1, 0, 1, 0, 1}
        };

        break;
    }

    else if(menu == 3) {
        cout << "Exiting...";
        return 0;
    }
    
    else cout << "Please enter a valid option" << endl << endl;


    } while(menu != 3);

    cout << "Chosen Difference Matrix: " << endl << endl;

    printMatrix(DM);

    vector<vector<bool>> BM = reduceMatrix(DM);

    cout << "Reduced Basic Matrix: " << endl << endl;

    printMatrix(BM);

    set<vector<int>> typicalTestors;

    do{
    cout << "Which algorithm would you like to use to find the typical testors?" << endl;

    cout << "1.) YYC Algorithm\n"
         << "2.) BT Algorithm\n";
    
    cin >> menu;
    cout << endl;

    if(menu == 1) {
        typicalTestors = yycAlgorithm(BM);
        break;
    }

    else if(menu == 2) {
        typicalTestors = btAlgorithm(BM);
        break;
    }

    else if(menu == 3){
        cout << "Exiting...";
        return 0;
    }

    else cout << "Please enter a valid option" << endl << endl;
        
    } while(menu != 3);

    cout << "Typical Testors found:" << endl;

    int i = 0;
    for (const auto& testor : typicalTestors) {
        cout << "Testor " << i+1 << ": ";
        for (int column : testor) cout << "x_" << column + 1 << " ";
        cout << endl;
        i++;
    }
    cout << endl;
    return 0;

}
