
#include "basic_matrix.h"
#include "functions.h"

using namespace std;

int main() {

    cout << "--------------------------------------------O------------------------------------------" << endl
         << "                                       BASIC TEST 1" << endl
         << "--------------------------------------------O------------------------------------------" << endl << endl;

    vector<vector<bool>> DM = {
                             {1, 0, 0, 1, 0},
                             {0, 1, 0, 1, 0},
                             {1, 1, 0, 0, 1},
                             {0, 0, 1, 1, 0},
                             {1, 0, 1, 0, 0},
                             {0, 1, 1, 0, 1},
                             {0, 0, 0, 1, 1},
                             {1, 0, 0, 0, 1},
                             {0, 1, 1, 1, 0},
                             {1, 0, 1, 0, 1},
                             };

    cout << "Difference Matrix: " << endl << endl;

    printMatrix(DM);

    vector<vector<bool>> A = reduceMatrix(DM);

    cout << "Reduced Basic Matrix 'A': " << endl << endl;

    printMatrix(A);

    cout << "Matrix 'A' Density: " << matrixDensity(A) << endl << endl;

    set<vector<int>> A_btTypicalTestors = btAlgorithm(A);

    cout << "'A' Typical Testors found using BT algorithm:" << endl;

    printTypicalTestors(A_btTypicalTestors);

    cout << endl;

    set<vector<int>> A_yycTypicalTestors = yycAlgorithm(A);
    
    cout << "'A' Typical Testors found using YYC algorithm:" << endl;

    printTypicalTestors(A_yycTypicalTestors);

    cout<< endl;
    cout << "--------------------------------------------O------------------------------------------" << endl
         << "                                       BASIC TEST 2" << endl
         << "--------------------------------------------O------------------------------------------" << endl << endl;

    vector<vector<bool>> B = typicalTestorsMatrix(A_btTypicalTestors); 
    
    cout << "Matrix 'B': " << endl << endl;

    printMatrix(B);

    vector<vector<bool>> B_basic = reduceMatrix(B);

    cout << "Reduced Basic Matrix 'B': " << endl << endl;

    printMatrix(B_basic);

    set<vector<int>> B_btTypicalTestors = btAlgorithm(B);

    cout << "'B' Typical Testors found using BT algorithm:" << endl;

    printTypicalTestors(B_btTypicalTestors);

    cout << endl;    
    cout << "--------------------------------------------O------------------------------------------" << endl
         << "                                       BASIC TEST 3" << endl
         << "--------------------------------------------O------------------------------------------" << endl << endl;
    
    cout << "For the next two tables, let be: " << endl 
         << "O = theta Operator"  << endl
         << "P = phi Operator"  << endl
         << "G = gamma Operator " << endl
         << "T = typical testors" << endl << endl;

    vector<vector<bool>> AB = thetaOperator(A,B);

    printTypicalTestors(yycAlgorithm(AB));
         
    cout << "Table 5" << endl
         << "Relative efficiency of the tested algorithms against the phi operator." << endl
         << "---------------------------------------------------------------------------------------" << endl
         << setw(2) << "N" << setw(11) << "Matrix" << setw(9) << "Rows" << setw(6) << "Cols" << setw(5) << "T" 
         << setw(9) << "YYC" << setw(19) << "YYC (ordered)" << setw(7) << "BT" << setw(19) << "BT (ordered)" << endl
         << "---------------------------------------------------------------------------------------" << endl;

    for (int N = 1; N <= 5 ; N++) {
        vector<vector<bool>> result = phiOperator(AB, N);
        vector<vector<bool>> sortedResult = sortMatrix(result);

        cout << setw(2) << N << setw(4) << "P^" << N << setw(8)<< "(O(A,B))" << setw(6) << result.size() << setw(6) << result[0].size();
        printExecutionTime(result, sortedResult); 
    }

    cout << "---------------------------------------------------------------------------------------" << endl << endl;

    cout << "Table 6" << endl
         << "Relative efficiency of the tested algorithms against the gamma operator." << endl
         << "---------------------------------------------------------------------------------------" << endl
         << setw(2) << "N" << setw(11) << "Matrix" << setw(9) << "Rows" << setw(6) << "Cols" << setw(5) << "T" 
         << setw(9) << "YYC" << setw(19) << "YYC (ordered)" << setw(7) << "BT" << setw(19) << "BT (ordered)" << endl
         << "---------------------------------------------------------------------------------------" << endl;

    for (int N = 1; N <= 4 ; N++) {
        vector<vector<bool>> result = gammaOperator(AB, N);
        vector<vector<bool>> sortedResult = sortMatrix(result);

        cout << setw(2) << N << setw(4) << "G^" << N << setw(8)<< "(O(A,B))" << setw(6) << result.size() << setw(6) << result[0].size();
        printExecutionTime(result, sortedResult); 
    }

    cout << "---------------------------------------------------------------------------------------" << endl << endl;

    return 0;
}
