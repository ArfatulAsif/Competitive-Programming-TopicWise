---
# Tree DP Common Approach

[![Tree DP Badge](https://img.shields.io/badge/Tree-Dynamic%20Programming-green?style=for-the-badge&logo=appveyor&logoColor=white)](https://shields.io/)

Tree DP is a technique used in problems where states are dependent on subtrees, and computations are made recursively while aggregating results from child nodes.

# Tree DP Properties:

1. **Base Case Handling:** The DP solution starts from leaf nodes, as they have no children to contribute to their state. The base case is defined by what needs to be returned for a leaf node.  

2. **Subtree Dependency:** The DP value of a node depends on its entire subtree, including its children, grandchildren, and further descendants. The recursion naturally propagates values upward through the tree.  

3. **Sometimes No Explicit Memoization Needed:** Unlike traditional DP, For single state Tree DP often doesn’t require explicit memoization since each node is visited only once in a DFS traversal. 

<br>
<br>

# SOME TREE DP PROBLEMS And Solution

<br>

## Problem Statement : PT07X - Vertex Cover  

[PT07X - Vertex Cover](https://www.spoj.com/problems/PT07X/)  

You are given an unweighted, undirected tree. The task is to find the minimum vertex cover, which is the smallest set of vertices such that every edge has at least one endpoint in the set.  

### DP States: dp[s][2]   

We define `dp[s][2]` to represent the minimum vertex cover for the subtree rooted at node `s`:  

- `dp[s][0]`: Minimum vertex cover when node `s` is **not included** in the cover. In this case, all of its children **must** be included.  
- `dp[s][1]`: Minimum vertex cover when node `s` **is included** in the cover. Here, its children **may or may not** be included, and we take the minimum of both possibilities for each child.  

### Solution  


```cpp
const int N = 1e5+100;
vector<int>graph[N];

int dp[N][2]; // dp[s][0] =, minimum vertex cover in the subtree of s, not taking node s.
              // dp[s][1] = minimum vertex cover in the subtree of s, taking s in the cover



int dfs(int s, int par, int take)
{
        int &ret = dp[s][take];

        if(ret != -1)
        {
                return ret;
        }

        ret = 0;

        if(take == 0) // s was not taken, we have to take all his children. no choice
        {        
                for(auto child : graph[s])
                {
                        if(child == par)
                        {
                                continue;
                        }

                        ret += dfs(child, s, take^1);
                }
        }

        else // take == 1. which means s was already taken, we could take its children or not take
        {
                for(auto child : graph[s])
                {
                        if(child == par)
                        {
                                continue;
                        }

                        

                        ret += min(dfs(child,s,1),dfs(child, s, take^1));
                }

                ret++; // we need to add taking s count
        }


        return ret;


}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;

        for(int i=0;i<n-1;i++)
        {
                int x,y;
                cin>>x>>y;

                graph[x].push_back(y);
                graph[y].push_back(x);
        }

        memset(dp, -1, sizeof(dp));


        cout<<min(dfs(1, 1, 0), dfs(1,1,1))<<endl;

}

```

<br>

## Problem Statement : 1039 - Anniversary Party

[1039 - Anniversary Party](https://acm.timus.ru/problem.aspx?num=1039&space=1)  

The president of Ural State University is organizing an 80th Anniversary Party. The university has a **hierarchical structure**, meaning the **supervisor relation forms a tree** rooted at the president. To make the party enjoyable, no immediate supervisor and their direct subordinate can both attend.  

Each employee has a **conviviality rating**, and the goal is to **maximize the total conviviality rating** of the guests while ensuring that no immediate supervisor-subordinate pair attends together.  

### DP States : dp[s][2] 

We define `dp[s][2]` to store the maximum conviviality rating for the **subtree rooted at node s**:  

- `dp[s][0]`: Maximum conviviality if **employee s is not invited**. In this case, children **may or may not** be invited.  
- `dp[s][1]`: Maximum conviviality if **employee s is invited**. In this case, **none of s's direct children can be invited**.  

### Solution  


```cpp
    
const int N = 7000;
vector<int>graph[N];
int ara[N];
int in[N]; // in degree, in[v] = 0, means root


int dp[N][2]; // dp[s][0], maximum value of party fun can be achieve in the subtree of s, not taking s to the party
              // dp[s][1], maximum value of party fun can be achieve in the subtree of s, including taking s to the party


int dfs(int s,int par,int take)
{
        int &ret = dp[s][take];

        if(ret != -1)
        {
                return ret;
        }

        ret = 0;

        if(take == 1) // we cant take its children
        {
                for(auto child : graph[s])
                {
                        if(child == par)
                        {
                                continue;
                        }

                        ret += dfs(child, s, 0);
                }

                ret += ara[s]; // as take = 1, we are taking s.
        }

        else // take == 0, we could take or not take its children
        {
                for(auto child : graph[s])
                {
                        if(child == par)
                        {
                                continue;
                        }

                        ret += max(dfs(child, s, 1), dfs(child, s, 0));
                }
        }

        return ret;
}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;

        for(int i=1;i<=n;i++)
        {
                int a;
                cin>>a;
                ara[i] = a;
        }

        for(int i=0;i<n;i++)
        {
                int x,y;
                cin>>x>>y;
                if(i==n-1)
                {
                        break;
                }

                graph[x].push_back(y);
                graph[y].push_back(x);

                in[x]++;

        }

        int root = -1;

        for(int i=1;i<=n;i++)
        {
                if(in[i] == 0)
                {
                        root = i;
                        break;
                }
        }


        memset(dp, -1,sizeof(dp));


        cout<<max(dfs(root,root,1), dfs(root,root,0))<<endl; // we could take or not take the president too
        

}

```  


## Problem Statement : Diameter of a Tree Using DP



Given a tree with `N` nodes, the goal is to **find the longest path between any two nodes**, which is also known as the **diameter of the tree**.  

### Observations  

1. If we root the tree at node `1`, we observe that for a node `x`, the longest path could be either:  
   - **`f(x)`**: A path that **starts at x** and ends somewhere **in its subtree**.  
   - **`g(x)`**: A path that **starts in the subtree of x**, passes **through x**, and ends **in another subtree of x**.  

2. The **diameter of the tree** is the maximum of `f(x)` and `g(x)` over all nodes `x`.  

3. We define `f(V)`, which represents the **longest path starting from V going into its subtree**. Using **Tree DP**, we compute `f(V)` recursively based on its children.  

4. To compute the second case `g(V)`, we take the **two longest `f(vi)` values** among `V`’s children and sum them.  

### DP states : dp[s]

We define `dp[s]` to store the **longest diameter considering only the subtree of node s**.  

## Solution  

```cpp
const int N = 1e5 + 100;
vector<int> graph[N];

int dp[N]; // dp[s] = longest diameter considering only the subtree of s.

int dfs(int s, int par) { // Returns the longest depth from node s
    priority_queue<int> pq;

    for (auto child : graph[s]) {
        if (child == par) continue;
        pq.push(dfs(child, s));
    }

    if (pq.empty()) return dp[s] = 1; // If leaf node, depth is 1

    if (pq.size() == 1) return dp[s] = pq.top() + 1;

    int take = pq.top();
    pq.pop();

    dp[s] = take + pq.top() + 1; // Combine the two longest paths through s

    return take + 1; // Return the longest depth for parent computation
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(1, 1);

    int mx = 0;
    for (int i = 1; i <= n; i++) {
        mx = max(mx, dp[i]); // Find max diameter in dp values
    }

    cout << mx << endl;
}
```  

<br>

## Problem Statement : 1018. Binary Apple Tree

[1018. Binary Apple Tree](https://acm.timus.ru/problem.aspx?space=1&num=1018)  

We are given a **binary tree** where each edge represents a branch containing apples. The goal is to **prune the tree** while **preserving exactly Q branches** and **maximizing the total number of apples** on the remaining branches.  

The tree is rooted at **node 1** and consists of **N nodes** (2 ≤ N ≤ 100). Each branch has a **weight** representing the number of apples on it. Our task is to determine the maximum number of apples that can be preserved while maintaining exactly Q branches.  



### DP States : dp[s][k] 

Let `dp[s][k]` be the **maximum number of apples** that can be preserved in the **subtree of node s** while keeping exactly `k` branches.  

- If `k = 0`, meaning **no branches are allowed**, then `dp[s][0] = 0` since no apples can be taken.  
- If `s` is a **leaf node**, then `dp[s][k] = 0` because we cannot preserve branches beyond its parent.  
- If we take only one children of `s` (either left or right), then `dp[s][k]` is the result of sending `k-1` branches to that child plus the apples from the connecting branch.  
- If we take both children of `s`, we try distributing `k-2` branches between the two children optimally, since two branches are needed to connect both.  



### Solution  

```cpp
const int N = 105;
int dp[N][N];  // dp[s][k] = maximum number of apple can be preserved in the subtree of s, keeping k branches
vector<pair<int,int>> graph[N];

int dfs(int s, int par, int k)
{

         if(dp[s][k] != -1)
         {
                return dp[s][k];
         }


         if(k == 0)
         {
                return dp[s][k] = 0;
         }

         if(graph[s].size() == 1)
         {
                return dp[s][k] = 0;
         }


         pair<int,int>p1,p2;

         p1 = {-1, -1};

         for(auto child : graph[s])
         {
                if(child.first == par)
                {
                        continue;
                }

                if(p1.first == -1)
                {
                        p1 = child;
                }
                else 
                {
                        p2 = child;
                }
         }


         int mx = dfs(p1.first, s, k-1)+ p1.second;  // we send (k-1) branches to the left child only, not taking right child at all. (Why k-1? Answer: 1 is already used to connect s and left child)

         mx = max(mx, dfs(p2.first, s, k-1)+ p2.second); // // we send (k-1) branches to the right child only, not taking left child at all. (Why k-1? Answer: 1 is already used to connect s and right child)

         for(int i=0;i<=k-2;i++)
         {
                // its a binary tree, so we send i - braches left and (k-2-i) - braches to right,  other 2 branches are used to connect these both children
                mx = max(mx, dfs(p1.first, s, i)+p1.second + dfs(p2.first, s, k-2-i)+p2.second);
         }

         return dp[s][k] = mx;
}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,k;
        cin>>n>>k;

        for(int i=0;i<n-1;i++)
        {
                int x,y,w;
                cin>>x>>y>>w;
                graph[x].push_back({y,w});
                graph[y].push_back({x,w});
        }


        memset(dp, -1, sizeof(dp));


        cout<<dfs(1,1,k)<<endl;


}

```  

<br>

## Problem Statement : Tree Pruning (using dp with Euler Tour Flattening)

[Tree Pruning](https://www.hackerrank.com/challenges/tree-pruning/problem)  

We are given a **tree** with `n` vertices numbered from `1` to `n`, rooted at vertex `1`. Each vertex `i` has an **integer weight** `w[i]`. The **total weight** of the tree is the sum of the weights of all its nodes.  

A **remove operation** deletes the **entire subtree** rooted at some node `v` from the tree. Our goal is to perform **at most k remove operations** to **maximize the total weight** of the remaining tree.  

The task is to determine and print the **maximum possible total weight** of the tree after performing up to `k` removals.  


### DP States  

We use **Euler Tour Flattening** to represent the tree in an array form, which allows us to handle subtree removals efficiently.  

Let `dp[i][j]` be the **maximum weight** that can be obtained considering **the first i nodes** in the flattened tree while performing **exactly j remove operations**.  

- **Base Case:** `dp[1][0] = 0`, meaning no removals and no weight initially.  
- We iterate over all `i` nodes and consider two choices:  
  - **Not removing node i**: Add `w[i]` to the total weight.  
  - **Removing node i**: Move to the end of its subtree (`dout[i]`) and increase the count of removals.  
- The final answer is the maximum weight among all cases with at most `k` removals.  



### Solution  

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 100;
vector<int> graph[N];
int ara[N];  // Node weights

int dp[N][205];  // dp[i][j] = max weight using first i nodes with j removals
int din[N], dout[N], node[N];
int tim = 0;

void dfs(int s, int par) {
    din[s] = ++tim;
    node[tim] = s;
    for (auto child : graph[s]) {
        if (child == par) continue;
        dfs(child, s);
    }
    dout[s] = tim;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        cin >> ara[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = LLONG_MIN;  // Initialize to negative infinity
        }
    }

    dfs(1, 0);

    dp[1][0] = 0;

    for (int i = 1; i <= n; i++) {
        int s = node[i];
        for (int j = 0; j <= k; j++) {
            // Not removing node s
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + ara[s]);

            // Removing the subtree rooted at s
            if (j + 1 <= k) {
                dp[dout[s] + 1][j + 1] = max(dp[dout[s] + 1][j + 1], dp[i][j]);
            }
        }
    }

    int ans = 0;
    for (int j = 0; j <= k; j++) {
        ans = max(ans, dp[n + 1][j]);
    }

    cout << ans << endl;
}
```  








