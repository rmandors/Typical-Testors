#include <iostream>
#include <vector>
#include <set>

using namespace std;


// Compatibility set check
bool findCompatibleSet(const vector<int>& testor, const vector<vector<bool>>& BM, int column_id, int current_row) {
    
    //Verify Condition 1

    int one_rows = 0; // Counter for number of rows who's sum of elements add up to 1
    vector<vector<int>> refSM; // Matrix used later to verify condition 2.


    // Iterates up until the current row being analyzed in the main YYC function
    for(int row = 0; row <= current_row; row++) {
        vector<int> refSM_row;
        int sum = 0;

        // Adds up the values in the testor columns and the column that is being checked for compatibility
        for(auto column: testor) {
            if(BM[row][column]) sum++;
            refSM_row.push_back(BM[row][column]);
        }
        if(BM[row][column_id]) sum++;
        refSM_row.push_back(BM[row][column_id]);

        if(sum == 1) {
            one_rows++;
            refSM.push_back(refSM_row); // refSM contains all rows which add up to 1
        }
    }   

    if(one_rows < testor.size() + 1) return false;

    // Verify Condition 2

    // Iterates through every column of refSM
    for(int column = 0; column < refSM[0].size(); column++) {
        int sum = 0;

        // Sums all the values of each columns
        for(int row = 0; row < refSM.size(); row++) 
            if(refSM[row][column])sum++;

        if(sum < 1) return false;
    }

    return true;

}

// Main YYC algorithm function
set<vector<int>> yycAlgorithm(const vector<vector<bool>>& BM) {
    set<vector<int>> typicalTestors; // Output set of typical testors

    // Initialize with the columns that have 1 in the first row
    for (int column = 0; column < BM[0].size(); column++) {
        if (BM[0][column] == 1) {
            typicalTestors.insert({column});
        }
    }

    // Analyze each subsequent row
    for (int row = 1; row < BM.size(); row++) {
        set<vector<int>> newTestors; //Temporary new set of testors

        // Iterates through each known testor
        for (const auto& testor : typicalTestors) {
            bool preserved = false;

            // If at least one column in the current row has a 1 in the testor columns, keep it
            for (int column : testor) {
                if (BM[row][column] == 1) {
                    newTestors.insert(testor);
                    preserved = true;
                    break;
                }
            }

            // Else, run a compatible set check with every column that has a 1 in the current row
            if (!preserved) {
                for (int column = 0; column < BM[row].size(); column++) {
                    if (BM[row][column] == 1 && findCompatibleSet(testor, BM, column, row)) {
                        
                        //If the columns is compatible, add it to the testor
                        vector<int> updatedTestor = testor;
                        updatedTestor.push_back(column);
                        newTestors.insert(updatedTestor);
                    }
                }
            }
        }
        typicalTestors = newTestors;
    }
    return typicalTestors;
}
