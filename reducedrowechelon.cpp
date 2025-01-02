#include <iostream>
#include <vector>
#include <iomanip>  // for setting precision

using namespace std;

// Function to convert matrix to Reduced Row Echelon Form (RREF)
void rref(vector<vector<double>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    int lead = 0;

    for (int r = 0; r < rows; ++r) {
        if (lead >= cols)
            return;
        int i = r;
        while (matrix[i][lead] == 0) {
            i++;
            if (i == rows) {
                i = r;
                lead++;
                if (lead == cols)
                    return;
            }
        }

        // Swap rows i and r
        swap(matrix[i], matrix[r]);

        // Normalize row r (make the leading value 1)
        double leadVal = matrix[r][lead];
        for (int j = 0; j < cols; ++j) {
            matrix[r][j] /= leadVal;
        }

        // Eliminate all other entries in the column
        for (int i = 0; i < rows; ++i) {
            if (i != r) {
                double scale = matrix[i][lead];
                for (int j = 0; j < cols; ++j) {
                    matrix[i][j] -= scale * matrix[r][j];
                }
            }
        }

        lead++;
    }
}

int main() {
    // Example matrix (3x4 matrix)
    vector<vector<double>> matrix = {
        {.5,-.1,-.1,7900},
        {-.2,.5,-.3,3950},
        {-.1,-.3,.6,1975}
    };

    cout << "Original matrix:\n";
    for (const auto& row : matrix) {
        for (double val : row)
            cout << setw(8) << val << " ";
        cout << endl;
    }

    rref(matrix);  // Convert to RREF

    cout << "\nMatrix in Reduced Row Echelon Form (RREF):\n";
    for (const auto& row : matrix) {
        for (double val : row)
            cout << setw(8) << fixed << setprecision(0) << val << " ";
        cout << endl;
    }

    return 0;
}
