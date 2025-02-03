# DP on Graph 

[![Graph DP Badge](https://img.shields.io/badge/Graph-Dynamic%20Programming-yellow?style=for-the-badge&logo=appveyor&logoColor=white)](https://shields.io/)  

<br>

At the beginner level, most DP on graph problems involve **directed graphs**. A directed graph enforces a one-way flow, much like DP, where the current state is derived from previously computed overlapping subproblems. (In the case of DP on trees, this one-way flow naturally exists from root to leaf, even if the tree is undirected).  

In contrast, **undirected graphs** introduce cycles due to bidirectional edges, creating looping structures that require additional handling for DP calculations, such as computing minimum/maximum values along paths or counting paths.  

Since most of the beginner problems I have solved focus on directed graphs, this README will cover DP on directed graphs.

<br>

# DP on Directed Graph

<br>

- ## DP on DAG (Directed Acyclic Graph): 

DP on a DAG is relatively straightforward. It follows a recursive DP approach, treating vertices as states. Since there are no cycles, there is no concern about infinite loops or overcounting when computing values for maximization, minimization, or counting paths. The DAG structure ensures that each state is processed in a well-defined order.

- ## DP on Not a DAG (Not a Directed Acyclic Graph):   

In this case, cycles or strongly connected components (SCCs) may exist, which prevents the direct use of a recursive DP approach. Traditional DP on graphs relies on a clear dependency order, but cycles create a looping structure that causes issues. Consider the following example:  

```
1 ← 4  
↓   ↑  
2 → 3  
```

Here, dp[1] depends on dp[2], dp[2] depends on dp[3], dp[3] depends on dp[4], and dp[4] again depends on dp[1], forming a cycle. This cycle prevents a straightforward DP approach from working correctly.  

To handle this, we first convert the directed graph into a **DAG** using Kosaraju's or Tarjan’s algorithm to identify SCCs. Each **SCC** in the DAG can then be treated as a **single node**, allowing us to apply DP for **along-path** type calculations.

<br>
<br>

# DP on DAG Problems: 

<br>

## Problem 1: Game Routes

[Game Routes - CSES](https://cses.fi/problemset/task/1681/)

In this problem, there are n levels connected by m teleporters, forming a directed acyclic graph (DAG). The goal is to determine the number of ways to reach level n from level 1. Since the graph is a DAG, there are no cycles, ensuring a clear topological order for DP calculations.

### DP State, dp[v]:

- `dp[v]` : dp[v] = count of ways from vertex `v` to vertex `n`.
 

### Solution

```cpp
const int N = 1e5+100;
vector<int>graph[N];
int dp[N]; // dp[v] = count of ways to reach from v to n
int n, m;
const int MOD = 1e9+7;

int dfs(int s) {
    if(s == n) {
        return dp[s] = 1;
    }
    if(dp[s] != -1) {
        return dp[s];
    }
    int cnt = 0;
    for(auto child : graph[s]) {
        cnt += dfs(child);
        cnt %= MOD;
    }
    return dp[s] = cnt;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
    }

    memset(dp, -1, sizeof(dp));
    cout << dfs(1) << endl;
}
```

<br>
<br>

## Problem 2: MADMAX  
[Codeforces - MADMAX](https://codeforces.com/contest/918/problem/D)  

Max and Lucas play a game on a directed acyclic graph (DAG) with n vertices and m edges. Each edge has a lowercase English letter assigned to it. Players take turns moving their marble along an edge, ensuring that the character associated with the current move is lexicographically greater than or equal to the previous move’s character. A player loses if they cannot make a valid move. Given that both players play optimally, we need to determine the winner for every possible pair of starting positions.  

### DP State, dp[v][u][move][c]:  

- `dp[v][u][move][c]` :  represents whether the current player wins if Max's marble is at vertex v, Lucas's marble is at vertex u, it is the current player’s turn (move = 0 for Max, move = 1 for Lucas), and the last used character is c.  

- If the current player can force the opponent into a losing position, they win. Otherwise, they lose.  

- `Transition` : If it is Max's turn (move = 0), she will explore all outgoing edges from v, choosing a move that guarantees Lucas reaches a losing state or `dfs(v1.first, u, 1, v1.second) == false`. Similarly, Lucas (move = 1) will try to do the same for Max or `dfs(v, u1.first, 0, u1.second) == false`.  

### Solution  

```cpp

const int N = 101;
int dp[N][N][2][N+50]; // dp[v][u][move][c] = First person is at v and second is at u and it's turn of (move == 0 for max, move == 1 for locus) with last used character c
vector<pair<int,char>> graph[N];

bool dfs(int v, int u, int move, char c)  
{        
        if(dp[v][u][move][c] != -1)  
        {  
                return dp[v][u][move][c];  
        }  
        bool ret = false;  
        if(move == 0)  // Max's turn; she tries to make Lucas lose  
        {  
                bool take = false;  
                for(auto v1 : graph[v])  
                {  
                        if(v1.second >= c)  
                        {  
                                take |= !(dfs(v1.first, u, 1, v1.second));  // If Max can force Lucas into a losing state, she wins  
                        }  
                }  
                ret = take;  
        }  
        else  // Lucas's turn; he tries to make Max lose  
        {  
                bool take = false;  
                for(auto u1 : graph[u])  
                {  
                        if(u1.second >= c)  
                        {  
                                take |= !(dfs(v, u1.first, 0, u1.second));  // If Lucas can force Max into a losing state, he wins  
                        }  
                }  
                ret = take;  
        }  
        return dp[v][u][move][c] = ret;  
}  

int32_t main()  
{  
        ios::sync_with_stdio(0);  
        cin.tie(0);  
        int n, m;  
        cin >> n >> m;  
        for(int i = 0; i < m; i++)  
        {  
                int x, y;  
                char c;  
                cin >> x >> y >> c;  
                graph[x].push_back({y, c});  
        }  
        memset(dp, -1, sizeof(dp));  
        for(int i = 1; i <= n; i++)  
        {  
                for(int j = 1; j <= n; j++)  
                {  
                        if(dfs(i, j, 0, 0))  // here we are sending c = 0, which is lexicographically smaller than all. 
                        {  
                                cout << "A";  
                        }  
                        else  
                        {  
                                cout << "B";  
                        }  
                }  
                cout << endl;  
        }  
}  
```































