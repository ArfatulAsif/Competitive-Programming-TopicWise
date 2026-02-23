# 🔥 The Standard Reroot Pattern

## Solution for any root problems:

For ANY reroot problem, the structure is always:

### 1️⃣ `dfs1(node, parent)`

* Compute DP assuming tree rooted at 1.
* Only use subtree information.
* Merge children into parent.

---

### 2️⃣ `reroot(from, to)`

When moving root from `from → to`: (where `to` is the children of `from` vertex)

```
remove child's contribution from parent
add parent's contribution into child
```
That’s the universal idea.

As now `from` vertex is at the subtree of  `to`  vertex, where previously `to` was in the subtree of `from` . Now we have to remove `to` vertex's contribution from `from` vertex and add `from` vertex's contribution in the `to` vertex (after removal  of `to` s contribution from `from`).




---

### 3️⃣ `dfs2(node, parent)`

For each child:

```
save state
reroot(node, child) // transition
dfs2(child)
reroot(child,node)  // restore
```

Always:

* Save
* Transition
* Recurse
* Restore

---

# 🧠 General Mental Formula

When rerooting edge `u → v`:

```
dp[v] = combine( dp[v] (its subtree), and contribution from u excluding v)
```

That is the entire philosophy of rerooting.

---





# 🌳 Standard Rerooting DP Template (Tree)

This is the classic structure used in most reroot problems. 

**Problem:** Maximum distant from each node to any other node.

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5+5;

vector<int> graph[N];

struct DP {
    // store whatever your problem needs
    int best1, best2; 
};

DP dp[N];
int ans[N];


// --------------------------------------------
// 1️⃣ First DFS
// Compute DP considering tree rooted at 1
// --------------------------------------------
void dfs1(int node, int par)
{
    // initialize base value
    dp[node] = {0, 0};

    for(auto child : graph[node])
    {
        if(child == par) continue;

        dfs1(child, node);

        // merge child into node
        int val = dp[child].best1 + 1;

        if(val >= dp[node].best1)
        {
            dp[node].best2 = dp[node].best1;
            dp[node].best1 = val;
        }
        else if(val > dp[node].best2)
        {
            dp[node].best2 = val;
        }
    }
}


// --------------------------------------------
// 2️⃣ Reroot Transition
// Move root from `from` → `to`
// --------------------------------------------
void reroot(int from, int to)
{
    // STEP 1: Remove `to` contribution from `from`

    int val = dp[to].best1 + 1;

    if(dp[from].best1 == val)
    {
        dp[from].best1 = dp[from].best2;
        dp[from].best2 = 0;
    }
    else if(dp[from].best2 == val)
    {
        dp[from].best2 = 0;
    }

    // STEP 2: Add `from` contribution into `to`

    int candidate = dp[from].best1 + 1;

    if(candidate >= dp[to].best1)
    {
        dp[to].best2 = dp[to].best1;
        dp[to].best1 = candidate;
    }
    else if(candidate > dp[to].best2)
    {
        dp[to].best2 = candidate;
    }
}


// --------------------------------------------
// 3️⃣ Second DFS
// Apply reroot transitions
// --------------------------------------------
void dfs2(int node, int par)
{
    ans[node] = dp[node].best1;   // final answer for this root

    for(auto child : graph[node])
    {
        if(child == par) continue;

        // Save old states
        DP old_node = dp[node];
        DP old_child = dp[child];

        // Apply reroot
        reroot(node, child);

        dfs2(child, node);

        // Restore
        dp[node] = old_node;
        dp[child] = old_child;
    }
}
```

---


**Problem** : Sum of distances from each node to all other node.

```cpp

const int N = 2e5+100;
vector<int>graph[N];

int dp[N];  
int SZ[N];


void dfs1(int node, int par)
{
       

        dp[node] = 0;

        SZ[node] = 1;

        
        for(auto child : graph[node])
        {
                if(child == par)
                {
                        continue;
                }

                dfs1(child, node);

                dp[node] += (SZ[child] + dp[child]); // (for the edge node---child , contributions comes equals to SZ[child], ie number of nodes in the subtree of the child.

                SZ[node] += SZ[child]; 

        }

       

}



void reroot(int from, int to) 
{
        dp[from] -= (dp[to] + SZ[to]);

        SZ[from] -= SZ[to];

        dp[to] += (dp[from] + SZ[from]);

        SZ[to] += SZ[from];
        

}


int ans[N];


void dfs2(int node, int par)
{
        ans[node] = dp[node];

        for(auto child : graph[node])
        {
                if(child == par)
                {
                        continue;
                }

                reroot(node, child);

                dfs2(child, node);

                reroot(child, node);

        }
}






int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;


        for(int i=0;i < n-1;i++)
        {
                int x,y;
                cin>>x>>y;

                graph[x].push_back(y);

                graph[y].push_back(x);
        
        }

        dfs1(1,1);

        dfs2(1,1);



       

        vector<int>v;

        for(int i=1;i<=n;i++)
        {
                cout<<ans[i]<<endl;
               
        }


}
```





# 🎯 These Template Works For

* Maximum distance in tree
* Tree diameter per node
* Sum of distances
* Count of subtree values
* DP on trees with re-root queries
* Any associative merge DP

---





# Problems:

1. [1.  Tree Distances I](https://cses.fi/problemset/task/1132)
2. [2.  Tree Distances II](https://cses.fi/problemset/task/1133)
3. [3.  Tree with Maximum Cost](https://codeforces.com/contest/1092/problem/F)
4. [4.  Choosing Capital for Treeland](https://codeforces.com/contest/219/problem/D)
5. [9.  Distance Sums 2](https://atcoder.jp/contests/abc220/tasks/abc220_f)
6. [7.  Subtree](https://atcoder.jp/contests/dp/tasks/dp_v)



# Vjudge contest list:

```
https://vjudge.net/contest/791606
```
