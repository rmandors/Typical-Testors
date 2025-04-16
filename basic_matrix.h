#include <vector>

using namespace std;

// Function to check if row 'p' is a subrow of row 't'
bool isSubrow(const vector<bool>& p, const vector<bool>& t) {
    bool strictlyLess = false;
    for (size_t col = 0; col < p.size(); ++col) {
        if (p[col] > t[col]) return false; // 'p' cannot be greater than 't' in any column
        if (p[col] < t[col]) strictlyLess = true; // 'p' must be strictly less in at least one column
    }
    return strictlyLess;
}

// Function to reduce DM to BM
vector<vector<bool>> reduceMatrix(const vector<vector<bool>>& DM) {
    vector<vector<bool>> BM; // Output reduced matrix
    vector<bool> isBasic(DM.size(), true); // Flag to track if a row is basic

    // Iterates through every row in DM
    for (int i = 0; i < DM.size(); ++i) {
        
        // Iterates through every row except the current row 'i' to compare all rows with eachother
        for (int j = 0; j < DM.size(); ++j) {
            if (!isBasic[j]) continue; // Skip if row 'j' is already marked as non-basic
            
            if (i != j && isSubrow(DM[j], DM[i])) {
                isBasic[i] = false; // Mark row 'i' as non-basic if it's a superrow
                break;
            }
        }
    }

    // Collect all rows marked as basic
    for (int i = 0; i < isBasic.size(); ++i) {
        if (isBasic[i]) BM.push_back(DM[i]);
    }

    return BM;
}
