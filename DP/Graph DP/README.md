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

DP on a DAG is relatively straightforward. It follows a recursive DP approach, treating vertices as states. Since there are **no cycles**, there is no concern about infinite loops or overcounting when computing values for maximization, minimization, or counting paths. The DAG structure ensures that each state is processed in a well-defined order.

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


<br>
<br>
<br>

# DP on NOT DAG Problems:
<br>

## Problem 1: Visiting Friends  
[CodeChef - Visiting Friends](https://www.codechef.com/problems/MCO16405)  

Fluffy the squirrel lives in a city with n towns and m uni-directional roads. Each town i has c_i inhabitants. Starting from any town i, Fluffy can travel **along the roads** for as long as possible, aiming to maximize the number of distinct people he visits, including the inhabitants of town i itself. 


**Solution strategy: Converting to a DAG:**
Since the graph may contain cycles, we cannot directly apply DP on it. Instead, we must first convert the directed graph into a DAG by identifying its strongly connected components (SCCs) and then apply DP on the resulting DAG to compute the maximum number of people Fluffy can visit from each town.  

### DP State, dp[v]:  

- `dp[v]` : represents the maximum number of people Fluffy can meet if he starts from SCC `v` in the DAG.  

- Since an SCC forms a cycle, all nodes within the same SCC are considered as a single node in the DAG. The population of an SCC is the sum of the populations of all towns within it.  

- `Transition` : Fluffy can move from SCC `v` to SCC `child` if there is a directed edge from `v` to `child` in the DAG. The optimal value for dp[v] is obtained by taking the maximum `dp[child]` value among all reachable child SCCs.

### Solution  

```cpp
const int N = 1e5+100;
vector<int>graph[N];
vector<int>Rgraph[N];
bool vis1[N];
bool vis2[N];
int group_id[N];
vector<int>forder;
int DAG_val[N];
int ara[N];
vector<int>DAG[N];

void dfs1(int s)
{
        vis1[s] = true;
        for(auto child : graph[s])
        {
                if(vis1[child])
                {
                        continue;
                }
                dfs1(child);
        }
        forder.push_back(s);
}

void dfs2(int s , int no)
{
        vis2[s] = true;
        group_id[s] = no;
        for(auto child : Rgraph[s])
        {
                if(vis2[child])
                {
                        continue;
                }
                dfs2(child , no);
        }
}

int dp[N]; // dp[v] = maximum amount of people that I can meet, if I start from SCC v in the DAG

int dfs_on_dag(int s)
{
        if(dp[s] != -1)
        {
                return dp[s];
        }
        dp[s] = DAG_val[s];
        int ret = 0;
        for(auto child : DAG[s])
        {
                ret = max(ret, dfs_on_dag(child));
        }
        return dp[s] += ret;
}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);
        int n,m;
        cin>>n>>m;

        for(int i=1;i<=n;i++)
        {
                cin>>ara[i];
        }

        for(int i=0;i<m;i++)
        {
                int x,y;
                cin>>x>>y;
                graph[x].push_back(y);
                Rgraph[y].push_back(x);
        }

        for(int i=1;i<=n;i++)
        {
                if(vis1[i]==false)
                {
                        dfs1(i);
                }
        }

        reverse(forder.begin(), forder.end());
        int no = 1;
        for(auto x : forder)
        {
                if(vis2[x]==false)
                {
                        dfs2(x , no);
                        no++;
                }
        }

        for(int i=1;i<=n;i++)
        {
                for(auto child : graph[i])
                {
                        if(group_id[i]!=group_id[child])
                        {
                                DAG[group_id[i]].push_back(group_id[child]);
                        }
                }
        }

        for(int i=1;i<=n;i++)
        {
                DAG_val[group_id[i]] += ara[i];
        }

        memset(dp, -1, sizeof(dp));

        for(int i=1;i<=n;i++)
        {
                cout<<dfs_on_dag(group_id[i])<<" ";
        }
        cout<<endl;
}
```


<br>
<br>
<br>



# A Special DP on Directed Graph problem: 

[DAGCNT2 - Counting in a DAG](https://www.spoj.com/problems/DAGCNT2/)


You are given a weighted DAG. For each vertex, calculate the sum of the weights of the vertices within its reach (including itself).


## Why it is a special dp on directed graph problem?:

This is a special DP problem on a directed graph. Here, we are not going **along a path**; rather, we need to consider all vertices that are reachable. Traditional DP introduces overcounting in this problem.

For example, consider the following code:

```cpp
const int N = 3e4;
vector<int> graph[N];
int ara[N];
int dp[N]; // dp[v] = total sum achievable starting from node v...

int dfs(int s)
{
    if(dp[s] != -1)
    {
        return dp[s];
    }

    dp[s] = ara[s];

    for(auto child : graph[s])
    {
        dp[s] += dfs(child);
    }

    return dp[s];
}

```

<br>

Directly using DP will not work here. This is because we are calculating the sum of the weights of the vertices within its reach. It's not like calculating or following **along-path** that maximizes, minimizes, or counts anything. 

Consider the following test case:

```
1
5 5
1 2 3 4 5
1 2
1 3
2 4
3 4
4 5

```

In this case, for `dp[1]`, which is calculated as `dp[1] += dp[2] + dp[3]`, but `dp[2] += dp[4] + dp[5]`, and `dp[3] += dp[4] + dp[5]`, so for `dp[1]`;  `dp[4]` and `dp[5]` are calculated twice.

**This issue arises because traditional DP doesn’t account for the fact that vertices can be reachable from multiple other vertices, which leads to overcounting.**

To handle this, we use a special **Bitmask** approach with `bitset<>` to find all the vertices that are reachable from a given vertex. We calculate the reachable vertices (`dp_reach`) by maintaining the topological order of the graph. This ensures we process vertices in a way that respects their **dependencies** ( dependencies = which vertex should we calculate before which vertex).


<br>


## Solution: 

Since, this is not just a **along-path** problem, as vertices can be reached from multiple directions, leading to repeated calculations. The traditional DP approach would cause overcounting.

To handle this, a **Bitmask** approach with `bitset<>` is used to track the vertices reachable from each vertex. The solution also employs **topological sorting** to process vertices in the correct order of dependencies, ensuring that each vertex is processed only after all of its **predecessors** have been processed.

## DP State dp_reach[v]:

-   `dp_reach[v]`: A `bitset` representing all the vertices reachable from vertex `v`. This includes vertex `v` itself.


## Solution: 

```cpp
const int N = 2e4 + 100;
vector<int> graph[N];
int ara[N], in[N], sum[N];
vector<bitset<N + 1>> dp_reach(N + 1, bitset<N + 1>());
queue<int> q;
vector<int> topo;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;
        
        for (int i = 1; i <= n; i++) {
            graph[i].clear();
            cin >> ara[i];
            sum[i] = 0;
            dp_reach[i] = bitset<N+1>();
             
            dp_reach[i].set(i); // Initially, each node can reach itself
        }

        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            graph[x].push_back(y);
            in[y]++;
            dp_reach[x].set(y); // x can directly reach y
        }

        for (int i = 1; i <= n; i++) {
            if (in[i] == 0) q.push(i);
        }

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            topo.push_back(node);
            for (int neighbor : graph[node]) {
                in[neighbor]--;
                if (in[neighbor] == 0) q.push(neighbor);
            }
        }

        // Reverse the topological order
        reverse(topo.begin(), topo.end());

        /*
        Now from reverse topo order, we build up the reach dp array, why? it should be obvious,

        Consider this directed graph,
                1 2
                1 3 
                2 4 
                3 4 
                4 5
                
             Here, for dp_reach[1], we calculate it,,
        dp_reach[1] |= dp_reach[2], dp_reach[1] |= dp_reach[3].
        
        But for this, we need to calculate dp_reach[2] and dp_reach[3] before.

        Now in which order we follow to calculate dp_reach? For example, here vertex 1 is calculated from 2 and 3.

        That’s when topological order takes place.

        We follow reverse topo order to build up the dp_reach, because it will maintain perfect dp_reach dependency.
        */


        for (int x : topo) {
            for (int child : graph[x]) {
                dp_reach[x] |= dp_reach[child]; // x can reach all vertices that child can reach
            }
        }

        // Calculate the sum of weights for each vertex based on reachable vertices
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dp_reach[i].test(j)) {
                    sum[i] += ara[j]; // Add the weight of the reachable vertex
                }
            }
        }

        // Output the result
        for (int i = 1; i <= n; i++) {
            cout << sum[i] << " ";
        }
        cout << endl;
    }

    return 0;
}

```
**If the directed graph was not a **DAG**. ie. the problem was for any directed graph, We would have to convert the directed graph to a **DAG**. Then we can similarly apply this **bitmask** based reachable DP.**




---

# A special DP on NOT a DAG problem 

## Problem Statement:
You are given a directed graph with `N` vertices, labeled from 1 to `N`. The edges are represented by a matrix `C` where each element `C[i][j]` is either a lowercase English letter or `-`.

- If `C[i][j]` is a lowercase letter, there is exactly one directed edge from vertex `i` to vertex `j` labeled `C[i][j]`.
- If `C[i][j]` is `-`, there is no edge from vertex `i` to vertex `j`.

You need to answer the following query for each pair `(i, j)`:
- **Among all (not necessarily simple) paths from vertex `i` to vertex `j`, where the concatenation of the edge labels forms a palindrome, what is the length of the shortest such path?**
- If no such path exists, return `-1`.


## Solution Explanation:

To solve this problem, we use a **Breadth-First Search (BFS)** approach with dynamic programming (DP). The idea is to maintain a DP table where `dp[i][j]` represents the minimum length of a palindrome path from vertex `i` to vertex `j`.

**DP States:**` dp[i][j]` represents the minimum length of a palindrome path from vertex `i` to vertex `j`.

**Step-by-step approach:**

1. **Initialization:**
   - We initialize a DP table `dp` where `dp[i][j]` is set to infinity (`inf`) for all pairs of vertices except the diagonal (`i == j`), which is set to `0` (indicating no edge needed to form a palindrome path from a vertex to itself).
   - We use a queue `q` to store pairs of vertices that can potentially form a palindrome path.

2. **Process Direct Edges:**
   - For each pair of vertices `(i, j)`, if there is a direct edge from `i` to `j` with a label, set `dp[i][j] = 1` (a single edge forms a palindrome if the label is identical when traversed in reverse).

3. **BFS Search:**
   - We then perform BFS from all pairs of vertices that have already been processed to find if longer palindrome paths can be formed by connecting two vertices through intermediate vertices.
   - If `graph[i][x] == graph[y][j]` and both `graph[i][x]` and `graph[y][j]` are not `-`, it means the edge labels from `i` to `x` and from `y` to `j` can form a palindrome when added to the path, so we update `dp[i][j]`.

4. **Final Answer:**
   - After completing the BFS, the `dp[i][j]` table will hold the minimum length of the palindrome path for each pair `(i, j)`. If a path doesn't exist, `dp[i][j]` will still be `inf`, and we print `-1` for such cases.

---

### Solution Code:

```cpp
const int N = 105;
const int inf = 1e9;  // Use a large number for infinity
char graph[N][N];  
int dp[N][N];    // dp[i][j] = minimum length of palindrome from i to j

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    queue<pair<int, int>> q;

    int n;
    cin >> n;

    // Read the graph matrix
    for (int i = 1; i <= n; i++)
    {
        q.push({i, i});
        for (int j = 1; j <= n; j++)
        {
            dp[i][j] = inf;  // Initialize all distances to infinity
            cin >> graph[i][j];  // Read each edge label or '-'
        }
    }

    // Process the direct edges
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)  // No path needed for same vertex
            {
                dp[i][j] = 0;
                q.push({i, j});
            }
            else if (graph[i][j] != '-')  // If there is an edge
            {
                dp[i][j] = 1;  // Direct edge forms a palindrome of length 1
                q.push({i, j});
            }
        }
    }

    // Perform BFS to find shortest palindrome paths
    while (!q.empty())
    {
        auto [x, y] = q.front();  // Get current pair (x, y) from the queue
        q.pop();

        for (int i = 1; i <= n; i++)  // For each vertex pair (i, j)
        {
            for (int j = 1; j <= n; j++)
            {
                if (dp[i][j] != inf)  // If dp[i][j] is already calculated
                    continue;

                // Check if we can form a palindrome path by adding edges
                if (graph[i][x] == graph[y][j] && graph[i][x] != '-')
                {
                    dp[i][j] = dp[x][y] + 2;  // Update the palindrome path length
                    q.push({i, j});  // Push to queue for further exploration
                }
            }
        }
    }

    // Output the result
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (dp[i][j] == inf)  // If no palindrome path exists
            {
                cout << -1 << " ";
            }
            else
            {
                cout << dp[i][j] << " ";  // Print the length of the palindrome path
            }
        }
        cout << endl;
    }

}
```














