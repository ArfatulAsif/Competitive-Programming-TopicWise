# DP ON GRID  

[![DP on Grid](https://img.shields.io/badge/Grid-Dynamic%20Programming-yellow?style=for-the-badge&logo=appveyor&logoColor=white)](https://shields.io/)

Dynamic Programming on a grid is quite simple. Since DP states correspond to grid cells, for Grid[i][j], we define dp[i][j] accordingly. Below are the two main approaches used for solving grid-based DP problems.

<br>

## Bottom-Up Approach (Most common):  
The DP state represents:  

**`dp[i][j] =`  from cell (0,0) to (i,j) minimum/maximum/count of things.**

## Top-Down Approach :  
The DP state represents:  

**`dp[i][j] =` from cell (i,j) to (m,n) minimum/maximum/count of things.**  

---
<br>
<br>

# Bottom-Up Problems Example  

<br>

## 64. Minimum Path Sum  
**Link:** [Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/description/?envType=problem-list-v2&envId=50izszui)  

### Problem Statement  
Given an m x n grid filled with non-negative numbers, find a path from the top-left to the bottom-right that minimizes the sum of all numbers along its path.  

Note: You can only move either down or right at any point in time.  

### DP State  
**dp[i][j] = minimum path sum from (0,0) to (i,j).**  

### Code  
```cpp
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        const int n = (int)grid.size();
        const int m = (int)grid[0].size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(m, INT_MAX));
        
        dp[0][0] = grid[0][0];

        for(int i=1; i<m; i++) {
            dp[0][i] = dp[0][i-1] + grid[0][i];
        }

        for(int i=1; i<n; i++) {
            dp[i][0] = dp[i-1][0] + grid[i][0];
        }

        for(int i=1; i<n; i++) {
            for(int j=1; j<m; j++) {
                dp[i][j] = min(dp[i][j], dp[i-1][j] + grid[i][j]); // Coming from top
                dp[i][j] = min(dp[i][j], dp[i][j-1] + grid[i][j]); // Coming from left
            }
        }

        return dp[n-1][m-1];
    }
};
```

---

<br>

## 62. Unique Paths  
**Link:** [Unique Paths](https://leetcode.com/problems/unique-paths/description/?envType=problem-list-v2&envId=50izszui)  

### Problem Statement  
A robot is placed on an m x n grid at the top-left corner (grid[0][0]). It tries to move to the bottom-right corner (grid[m-1][n-1]). The robot can only move either down or right at any point in time.  

Given the integers m and n, return the number of unique paths the robot can take to reach the bottom-right corner.  

### DP State  
**dp[i][j] = number of unique paths from (0,0) to (i,j).**  

### Code  
```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        int dp[n][m];
        memset(dp, 0, sizeof(dp));

        dp[0][0] = 1;

        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(i-1 >= 0) {
                    dp[i][j] += dp[i-1][j];
                }
                if(j-1 >= 0) {
                    dp[i][j] += dp[i][j-1];
                }
            }
        }

        return dp[n-1][m-1];
    }
};
```

---

<br>

## 63. Unique Paths II  
**Link:** [Unique Paths II](https://leetcode.com/problems/unique-paths-ii/description/?envType=problem-list-v2&envId=50izszui)  

### Problem Statement  
Given an m x n integer grid where obstacles are marked as 1 and open spaces as 0, find the number of unique paths from the top-left to the bottom-right corner, avoiding obstacles.  

### DP State  
**dp[i][j] = count of ways to reach from (0,0) to (i,j).**  

### Code  
```cpp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& Grid) {
        const int n = (int)Grid.size();
        const int m = (int)Grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));

        dp[0][0] = Grid[0][0] == 0;

        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(Grid[i][j] == 1) {
                    continue;
                }
                if(i-1 >= 0) {
                    dp[i][j] += dp[i-1][j];
                }
                if(j-1 >= 0) {
                    dp[i][j] += dp[i][j-1];
                }
            }
        }

        return dp[n-1][m-1];
    }
};
```

---

<br>

## 1594. Maximum Non-Negative Product in a Matrix  
**Link:** [Maximum Non-Negative Product in a Matrix](https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/description/?envType=problem-list-v2&envId=2wfuhzoj)  

### Problem Statement  
Given an m x n matrix, find the path from the top-left to the bottom-right corner that yields the maximum non-negative product.  

### DP State  
**dp[i][j][0] = maximum negative product from (0,0) to (i,j).**  
**dp[i][j][1] = maximum positive product from (0,0) to (i,j).**  

### Code  

```cpp
class Solution {
public:

    // dp[i][j][0] = (0,0) to (i,j) porjonto maximum negative product
    // dp[i][j][1] = (0,0) to (i,j) porjonto maximum positive product

    int Mod = 1e9+7;
    long long int dp[16][16][2];

    int maxProductPath(vector<vector<int>>& grid) {
        
        memset(dp, 0, sizeof(dp));
        bool zero = false;

        for(int i=0;i<grid.size();i++) {
            for(int j=0;j<grid[0].size();j++) {
                zero |= grid[i][j] == 0;
            }
        }

        if(grid[0][0] > 0) {
            dp[0][0][1] = grid[0][0]; // pos
        }
        else {
            dp[0][0][0] = grid[0][0]; // neg
        }

        for(int i=0;i<grid.size();i++) {
            for(int j=0;j<grid[0].size();j++) {
                if(i-1>=0) { // up
                    long long int cur = grid[i][j]*dp[i-1][j][0]; // multiply with neg 
                    long long int cur2 = grid[i][j]*dp[i-1][j][1]; // multiply with pos 
                    
                    long long int mx = max(cur, cur2);
                    long long int mn = min(cur, cur2);

                    if(mx > 0) {
                        dp[i][j][1] = mx;
                    }
                    if(mn < 0) {
                        dp[i][j][0] = mn;
                    }
                }
                if(j-1>=0) {
                    long long int cur = grid[i][j]*dp[i][j-1][0]; // multiply with neg 
                    long long int cur2 = grid[i][j]*dp[i][j-1][1]; // multiply with pos 
                    
                    long long int mx = max(cur, cur2);
                    long long int mn = min(cur, cur2);

                    if(mx > 0) {
                        dp[i][j][1] = max(dp[i][j][1], mx);
                    }
                    if(mn < 0) {
                        dp[i][j][0] = min(dp[i][j][0], mn);
                    }
                }
                cout<<i<<" "<<j<<" pos "<<dp[i][j][1]<<" neg "<<dp[i][j][0]<<endl;
            }
        }

        if(dp[grid.size()-1][grid[0].size()-1][0] < 0 && dp[grid.size()-1][grid[0].size()-1][1] == 0 && !zero) {
            return -1;
        }
        return dp[grid.size()-1][grid[0].size()-1][1]%Mod;
    }
};
```

---

<br>

## 1301. Number of Paths with Max Score  
**Link:** [Number of Paths with Max Score](https://leetcode.com/problems/number-of-paths-with-max-score/?envType=problem-list-v2&envId=2wfuhzoj)  

### Problem Statement  
Given a square board of characters, find the maximum sum of numeric characters from the bottom-right to the top-left, counting the number of such paths. Obstacles are marked as 'X'.  

### DP State  
**dp[i][j] = maximum path sum from (0,0) to (i,j).**  
**cnt[i][j] = number of paths achieving the maximum sum from (0,0) to (i,j).**  

### Code  

```cpp
class Solution {
public:
    
    // Bottom up dp.
    int dp[101][101]; // dp[i][j] = maximum path sum from (0,0) to (i,j)
    int cnt[101][101]; // cnt[i][j] = count of paths of maximum sum from (0,0) to (i, j)

    vector<int> pathsWithMaxScore(vector<string>& board) {
        
        board[0][0] = '0';
        int n = board.size();
        int m = board[0].size();
        board[n-1][m-1] = '0';

        dp[0][0] = 0;
        cnt[0][0] = 1;

        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) {
                int mx_up = -1, mx_left = -1, mx_corner = -1;

                if(i-1>=0 && board[i-1][j] != 'X' && cnt[i-1][j]) {
                    mx_up = dp[i-1][j];
                }
                if(j-1>=0 && board[i][j-1] != 'X' && cnt[i][j-1]) {
                    mx_left = dp[i][j-1];
                }
                if(i-1>=0 && j-1>=0 && board[i-1][j-1] != 'X' && cnt[i-1][j-1]) {
                    mx_corner = dp[i-1][j-1];
                }

                int mx = max(mx_up, max(mx_left, mx_corner));
                if(mx == -1) continue;

                if(mx == mx_up) cnt[i][j] += cnt[i-1][j];
                if(mx == mx_left) cnt[i][j] += cnt[i][j-1];
                if(mx == mx_corner) cnt[i][j] += cnt[i-1][j-1];

                cnt[i][j] %= 1000000007;
                dp[i][j] = mx + board[i][j]-'0';
            }
        }
        return {dp[n-1][m-1], cnt[n-1][m-1]};
    }
};

```

<br>
<br>

# Top-Down Problems Example 

<br>

### 174. Dungeon Game  

[Link](https://leetcode.com/problems/dungeon-game/description/?envType=problem-list-v2&envId=2wfuhzoj)

### Problem Statement  
The demons have captured the princess and imprisoned her in the bottom-right corner of a dungeon. The knight starts in the top-left room and must navigate through the dungeon to rescue the princess. Some rooms are guarded by demons (negative values), some contain magic orbs (positive values), and others are empty (zero). The knight can only move right or downward. The task is to determine the knight’s minimum initial health such that he can reach the princess without his health dropping to zero or below.

### DP States  
**dp[i][j]**: Minimum health required to reach the princess, ie from cell (i,j) to (n-1,m-1).

### Code

```cpp
class Solution {
public:
    // its like kadanse algorithm ,
    // for kadanse algorithm we find maximum subarray sum ending at i. using cur = max(a[i], cur+a[i]);
    // we will reverse it to consider top-down approach. which is sort of like , minimum subarray sum starting at i.  
    // for this problem: 
    int dp[201][201]; // dp[i][j] = cell (i,j) to (m, n) maximum of minimum contigious path sum starting from (i, j)
    vector<vector<int>>Grid;
    int n,m;
    int f(int i, int j) {
        if(i == m-1 && j == n-1) {
            return Grid[i][j];
        }
        if(i < 0 || j < 0 || i >= m || j >= n) {
            return INT_MIN;
        }
        if(dp[i][j] != 1) {
            return dp[i][j];
        }
        int take = min(Grid[i][j], max(f(i+1, j), f(i, j+1)) + Grid[i][j]);
        take = min(take, 0);
        dp[i][j] = take;
        return dp[i][j];
    }
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        Grid = dungeon;
        m = dungeon.size();
        n = dungeon[0].size();
        for(int i = 0; i < 201; i++) {
            for(int j = 0; j < 201; j++) {
                dp[i][j] = 1;
            }
        }
        if(f(0, 0) > 0) {
            return 1;
        }
        return -f(0, 0) + 1;
    }
};
```

<br>
<br>

# Special type: Two persons moving at the same time in the grid

---

<br>

### 741. Cherry Pickup [Type: Two person moving at the same time] 

[Link](https://leetcode.com/problems/cherry-pickup/description/?envType=problem-list-v2&envId=2wfuhzoj)

### Problem Statement  
You are given an n x n grid representing a field of cherries, each cell is one of three possible integers.  
0 means the cell is empty, so you can pass through,  
1 means the cell contains a cherry that you can pick up and pass through, or  
-1 means the cell contains a thorn that blocks your way.  
Return the maximum number of cherries you can collect by following the rules below:  

Starting at the position (0, 0) and reaching (n - 1, n - 1) by moving right or down through valid path cells (cells with value 0 or 1).  
After reaching (n - 1, n - 1), returning to (0, 0) by moving left or up through valid path cells.  
When passing through a path cell containing a cherry, you pick it up, and the cell becomes an empty cell 0.  
If there is no valid path between (0, 0) and (n - 1, n - 1), then no cherries can be collected.  

### DP States  
**dp[r1][c1][c2]**: The maximum number of cherries that can be picked up from cells (r1, c1) and (r2, c2) considering the rules above, without counting the same grid cell twice.

### Code

```cpp
class Solution {
public:
    int dp[51][51][51]; // dp[r1][c1][c2] = cell (r1, c1) and (r2, c2) thakia shuru koria (n-1,n-1) porjonto maximum cherry that can be picked up considering not counting same grid cell twice
    vector<vector<int>> Grid;
    int n, m;

    // Since both person move 1 cell at a time, the distance is manhattan distance, or r1+c1 = r2+c2
    int f(int r1, int c1, int c2) {
        int r2 = r1 + c1 - c2;

        if(dp[r1][c1][c2] != -1) {
            return dp[r1][c1][c2];
        }

        if(r1 < 0 || r1 >= n || c1 < 0 || c1 >= n || r2 < 0 || r2 >= n || c2 < 0 || c2 >= n || Grid[r1][c1] == -1 || Grid[r2][c2] == -1) {
            return INT_MIN;
        }

        if(r1 == n-1 && c1 == n-1 && c2 == n-1) {
            return Grid[n-1][n-1];
        }

        int take = 0;
        take += Grid[r1][c1];

        if(r1 == r2 && c1 == c2) {
            // If both persons are in the same cell, only one takes the cherry
        } else {
            take += Grid[r2][c2];
        }

        int temp = INT_MIN;

        // Move for two person
        temp = max(temp, f(r1, c1 + 1, c2 + 1) + take);  // (right, right)
        temp = max(temp, f(r1, c1 + 1, c2) + take);      // (right, down)
        temp = max(temp, f(r1 + 1, c1, c2 + 1) + take);  // (down right)
        temp = max(temp, f(r1 + 1, c1, c2) + take);      // (down, down)

        return dp[r1][c1][c2] = temp;
    }

    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
        Grid = grid;
        memset(dp, -1, sizeof(dp));

        int ans = (f(0, 0, 0) > 0 ? f(0, 0, 0) : 0);
        return ans;
    }
};
```

---

<br>

### 1463. Cherry Pickup II [Type: Two person moving at the same time] 

[Link](https://leetcode.com/problems/cherry-pickup-ii/description/?envType=problem-list-v2&envId=2wfuhzoj)

### Problem Statement  
You are given a `rows x cols` matrix grid representing a field of cherries where grid[i][j] represents the number of cherries that you can collect from the (i, j) cell.  
You have two robots that can collect cherries for you:

- Robot #1 is located at the top-left corner (0, 0),
- Robot #2 is located at the top-right corner (0, cols - 1).

Return the maximum number of cherries collection using both robots by following the rules below:  

From a cell (i, j), robots can move to cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).  
When any robot passes through a cell, it picks up all cherries, and the cell becomes an empty cell.  
When both robots stay in the same cell, only one takes the cherries.  
Both robots cannot move outside of the grid at any moment.  
Both robots should reach the bottom row in grid.

### DP States  
**dp[r][c1][c2]**: The maximum amount of cherries that can be picked up by both robots starting from `(r, c1)` and `(r, c2)` up to the last row  `(r = n-1)`.

### Code

```cpp
class Solution {
public:
    int dp[72][72][72]; // dp[r][c1][c2] = from (r, c1) and (r, c2) cell to row r = n-1 maximum amount of cherry that can be picked
    vector<vector<int>> Grid;
    int n, m;

    int f(int r, int c1, int c2) {
        if(c1 < 0 || c1 >= m || c2 < 0 || c2 >= m) {
            return 0;
        }

        if(r == n - 1) {
            if(c1 == c2) {
                return dp[r][c1][c2] = Grid[r][c1];
            } else {
                return dp[r][c1][c2] = Grid[r][c1] + Grid[r][c2];
            }
        }

        if(dp[r][c1][c2] != -1) {
            return dp[r][c1][c2];
        }

        int take = 0;
        if(c1 == c2) {
            take += Grid[r][c1];
        } else {
            take += Grid[r][c1] + Grid[r][c2];
        }

        int temp = 0;

        for(int cc1 = -1; cc1 <= 1; cc1++) { // First robot's move
            for(int cc2 = -1; cc2 <= 1; cc2++) { // Second robot's move
                temp = max(temp, f(r + 1, c1 + cc1, c2 + cc2) + take); 
            }
        }

        return dp[r][c1][c2] = temp;
    }

    int cherryPickup(vector<vector<int>>& grid) {
        Grid = grid;
        n = grid.size();
        m = grid[0].size();
        memset(dp, -1, sizeof(dp));

        return f(0, 0, m - 1);
    }
};
```
