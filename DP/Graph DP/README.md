# DP on Graph 

[![Graph DP Badge](https://img.shields.io/badge/Graph-Dynamic%20Programming-yellow?style=for-the-badge&logo=appveyor&logoColor=white)](https://shields.io/)  

<br>

At the beginner level, most DP on graph problems involve **directed graphs**. A directed graph enforces a one-way flow, much like DP, where the current state is derived from previously computed overlapping subproblems. (In the case of DP on trees, this one-way flow naturally exists from root to leaf, even if the tree is undirected).  

In contrast, **undirected graphs** introduce cycles due to bidirectional edges, creating looping structures that require additional handling for DP calculations, such as computing minimum/maximum values along paths or counting paths.  

Since most of the beginner problems I have solved focus on directed graphs, this README will cover DP on directed graphs.

<br>

# DP on Directed Graph

<br>

## DP on DAG (Directed Acyclic Graph)  

DP on a DAG is relatively straightforward. It follows a recursive DP approach, treating vertices as states. Since there are no cycles, there is no concern about infinite loops or overcounting when computing values for maximization, minimization, or counting paths. The DAG structure ensures that each state is processed in a well-defined order.

## DP on Directed Graph (Not a DAG)  

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

# DP on DAG

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

































