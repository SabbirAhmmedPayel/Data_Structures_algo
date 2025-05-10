#include <bits/stdc++.h>
using namespace std;

void dfs(vector<vector<char>> &grid, int r, int c)
{
    int row = grid.size();
    int col = grid[0].size();

    // Base condition
    // if r or c is out of bounds or grid[r][c] is not 'L' (land)
    if (r < 0 || c < 0 || r >= row || c >= col || grid[r][c] != 'L')
    {
        return;
    }

    // Mark the cell as visited by setting it to 'W' (water)
    grid[r][c] = 'W';

    // Traverse all 8 possible directions
    vector<int> rNbr = {1, -1, 0, 0, 1, -1, 1, -1};
    vector<int> cNbr = {0, 0, 1, -1, 1, -1, -1, 1};

    for (int i = 0; i < 8; ++i)
    {
        int newR = r + rNbr[i];
        int newC = c + cNbr[i];
        dfs(grid, newR, newC);
    }
}

// Function to count the number of islands
int countIslands(vector<vector<char>> &grid)
{
    int row = grid.size();
    int col = grid[0].size();
    int count = 0;

    // Traverse the entire matrix
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {

            // If a cell with value 'L' (land) is found
            if (grid[r][c] == 'L')
            {
                // Increment the island count
                count++;

                // Start DFS from the current cell
                dfs(grid, r, c);
            }
        }
    }
    return count;
}

int main()
{
    vector<vector<char>> grid =
    {
        {'L', 'L', 'W', 'W', 'W'},
        {'W', 'L', 'W', 'W', 'L'},
        {'L', 'W', 'W', 'L', 'L'},
        {'W', 'W', 'W', 'W', 'W'},
        {'L', 'W', 'L', 'L', 'W'}
    };

    cout << countIslands(grid) << endl; 
    return 0;
}
