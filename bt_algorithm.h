#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

//When the number of typical testors becomes to large, iterating over every testor becomes inefficient
//This function verifies the typicality of a testor directly inside the matrix, borrowing logic from the YYC algorithm

bool isCompatibleSet(const vector<vector<bool>>& BM, vector<int>& subset) {
    int one_rows = 0; // Counter for number of rows who's sum of elements add up to 1
    vector<vector<int>> refSM; // Matrix used later to verify condition 2.
    int rowNum = BM.size();

    for(int row = 0; row < rowNum; row++) {
        vector<int> refSM_row;
        int sum = 0;

        // Adds up the values in the testor columns and the column that is being checked for compatibility
        for(auto column: subset) {
            if(BM[row][column]) sum++;
            refSM_row.push_back(BM[row][column]);
        }

        if(sum == 1) {
            one_rows++;
            refSM.push_back(refSM_row); // refSM contains all rows which add up to 1
        }
    }

    if(one_rows < subset.size()) return false;

    // Verify Condition 2

    // Iterates through every column of refSM
    for(int column = 0; column < refSM[0].size(); column++) {
        int sum = 0;

        // Sums all the values of each columns
        for(int row = 0; row < refSM.size(); row++) 
            if(refSM[row][column]) sum++;

        if(sum < 1) return false;
    }

    return true;  
}

// Function to check if a subset is a testor. Handles alpha updates
bool isTestor(const vector<vector<bool>>& BM, const vector<int>& subset, unsigned long long &alpha) {
    
    vector<int> zero_rows; // Stores index of all-zero rows
    unsigned int columnNum = BM[0].size();

    // Iterates over every row in BM. Checks if selected columns have an all-zero row
    for(int row = 0; row < BM.size(); row++) {
        bool allZeros = true;

        for(auto column: subset){
            if(BM[row][column]){
                allZeros =  false;
                break;
            }
        }
        if(allZeros) zero_rows.push_back(row);
    }
    
    if(zero_rows.empty()) {

        // If there are no all-zero rows, applies proposition 1.4

        // Calculates k (the position of the rightmost 1 in alpha)
        int k = columnNum;
        for(int i  = columnNum - 1; i >= 0; i--) {
            if(alpha & (1ull << i)) k = columnNum - i;
        }

        //Skips 2^(n-k) positions
        alpha += pow(2, columnNum - k);

        // bitset<64> new_alpha(alpha);
        // cout << "final alpha: " << endl;
        // for(int i = columnNum - 1; i >= 0; i--) cout << new_alpha.test(i);
        //     cout << endl << endl;
        return true;
    }

    else {

        // If there are all-zero rows, applies proposition 1.5

        // Calculates k (the position of the last 1 in the all-zero row)
        // If there are multiple all-zero rows, takes the leftmost 1
        int k = columnNum - 1;
        for(auto row: zero_rows){
            int tempK = columnNum - 1;
            for(int column = 0; column < columnNum; column++) {
                if(BM[row][column]) tempK = column; 
            }

            if(tempK < k) k = tempK;
        }
        
        // All positions before k are kept the same
        bitset<64> new_alpha(alpha);
        
        // Position k is set to 1
        new_alpha.set( (columnNum - 1) - k, true);


        // All positions after k are set to zero
        for(int i = 0; i < (columnNum - 1) - k; i++) {
            new_alpha.set(i, false);
        }

        // cout << "final alpha: " << endl;
        // for(int i = columnNum - 1; i >= 0; i--) cout << new_alpha.test(i);
        //     cout << endl << endl;

        alpha = new_alpha.to_ullong();
        return false;
    }
}

// Main BT algorithm function
set<vector<int>> btAlgorithm(const vector<vector<bool>>& BM) {
    set<vector<int>> typicalTestors; // Output set of typical testors
    int columnNum = BM[0].size();

    unsigned long long alpha = 1; // Start from (0...01)

    while (alpha < (1ull << columnNum)) { 
        vector<int> subset;

        // cout << "Subset: " << endl;
        // for (auto i: subset)
        //     cout << i << " " << endl;
        
        // Translates bits into column index
        for (int j = 0; j < columnNum; j++) {
            if (alpha & (1ull << j)) subset.push_back(columnNum - 1 - j);
        }

        // Check if the subset is a testor
        if (isTestor(BM, subset, alpha)) {

            if(typicalTestors.size() < columnNum) {

                // Check if the new testor is a superset of any testor already stored
                bool isTypical = true;
 
                // Iterates over every testor stored
                for (const auto& testor : typicalTestors) {
                    bool isSuperSet = true;
                    for (int column : testor) {

                        // If any element in the typical testor is different to the new testor, the new testor is not a superset
                        if (find(subset.begin(), subset.end(), column) == subset.end()) {
                            isSuperSet = false;
                            break;
                        }
                    }
                    if (isSuperSet) {
                        isTypical = false;
                        break;
                    }
                }
                if (isTypical) 
                    typicalTestors.insert(subset); // Store typical testor
            }

            else {
                bool isTypical = isCompatibleSet(BM, subset);
                if(isTypical)
                    typicalTestors.insert(subset);

            }
        }
    }

    return typicalTestors;
}
