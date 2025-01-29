---
# Tree DP Common Approach

[![Tree DP Badge](https://img.shields.io/badge/Tree-Dynamic%20Programming-green?style=for-the-badge&logo=appveyor&logoColor=white)](https://shields.io/)

Tree DP is a technique used in problems where states are dependent on subtrees, and computations are made recursively while aggregating results from child nodes.

# Tree DP Properties:

1. **Base Case Handling:** The DP solution starts from leaf nodes, as they have no children to contribute to their state. The base case is defined by what needs to be returned for a leaf node.  

2. **Subtree Dependency:** The DP value of a node depends on its entire subtree, including its children, grandchildren, and further descendants. The recursion naturally propagates values upward through the tree.  

3. **Sometimes No Explicit Memoization Needed:** Unlike traditional DP, For single state Tree DP often doesn’t require explicit memoization since each node is visited only once in a DFS traversal. 



# SOME TREE DP PROBLEMS And Solution



## Problem Statement : PT07X - Vertex Cover  

[PT07X - Vertex Cover](https://www.spoj.com/problems/PT07X/)  

You are given an unweighted, undirected tree. The task is to find the minimum vertex cover, which is the smallest set of vertices such that every edge has at least one endpoint in the set.  

### DP States  

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



