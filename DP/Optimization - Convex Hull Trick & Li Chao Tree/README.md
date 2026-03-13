# Dynamic Programming Optimizations: Line Envelope Techniques

In many Dynamic Programming problems, you will encounter a recurrence relation that looks like this:


$$dp[i] = \min_{j < i} or \max_{j < i}  (m_j \cdot x_i + b_j) + C_i$$

Where:

* $x_i$: A variable dependent strictly on the current state $i$.
* $m_j$: A variable (slope) dependent strictly on the previous state $j$.
* $b_j$: A variable (y-intercept, often containing $dp[j]$) dependent strictly on $j$.
* $C_i$: A constant factor dependent strictly on $i$ (optional).

A naive nested loop calculating this takes $O(N^2)$ time. However, notice that for a fixed $j$, the equation $y = m_j \cdot x + b_j$ is simply a **straight line**. Therefore, finding the minimum (or maximum) DP value is equivalent to finding the line that gives the lowest (or highest) $y$ value at a specific $x$-coordinate ($x_i$).

To optimize this to $O(N)$ or $O(N \log N)$, we can maintain a collection of lines and efficiently query the optimal line for any $x$. The two main data structures for this are the **Convex Hull Trick (CHT)** and the **Li Chao Tree**.

---

## 1. Convex Hull Trick (Deque-based)

### When to use:

You should use the Deque-based CHT when **both of the following monotonicity conditions hold**:

1. **Slopes ($m_j$) are monotonic:** The lines are added in strictly increasing or strictly decreasing order of their slopes.
2. **Queries ($x_i$) are monotonic:** The $x$-coordinates being queried are strictly increasing or strictly decreasing.

### Why it works:

Because the slopes are inserted in sorted order, the lines form a convex envelope (or lower/upper hull).

* When adding a new line $L_3$, we look at the last two lines $L_1$ and $L_2$ in the deque. If $L_3$ makes $L_2$ completely redundant (meaning $L_2$ will never be the optimal line for any future $x$), we pop $L_2$. This is checked using the intersection point in the `bad(l1, l2, l3)` function.
* Because the queries $x_i$ are also monotonic, the optimal line shifts sequentially in one direction. Thus, if the first line in the deque is worse than the second line at the current $x_i$, it will *always* be worse for future queries. We can safely `pop_front()` irrelevant lines.

### Variable Name Convention:

* `m`: Slope of the line ($m_j$).
* `b`: Y-intercept of the line ($b_j$ or $c_j$).
* `x`: The query value ($x_i$).
* `convex_hull`: A deque storing the actively relevant lines forming the envelope.

---

### Problem Use Case 1: Z - Frog 3 (using CHT)

**Monotonicity Check:** The heights $h_i$ are strictly increasing. Thus, query points $x_i = h_i$ are monotonic. Slopes $m_j = -2h_j$ are strictly decreasing. CHT is perfect here.

```cpp
//Intermediary
//Young kid on the block
//AIAsif try's Continuing the journey
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
#define inf 1000000000000000000
#define int long long int
#define ordered_set tree< int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>
     

// For watching how CHT only keeps the relevent lines that gives minimum or maximum  value of y for any x
// https://www.youtube.com/watch?v=u-kNMIVNbjo



struct line 
{
        int m, b;
};

struct CHT 
{
        deque<line> convex_hull;

        int f(const line &l,int x) 
        {
                return l.m* x +l.b;
        }

        bool bad(line l1, line l2, line l3) 
        {
                return (__int128 )( l3.b -  l1.b)* (l1.m - l2.m) <= ( __int128)( l2.b - l1.b) *(l1.m -l3.m);
        }

        void add_line(line l) 
        {

                while (convex_hull.size() >= 2 && bad(convex_hull[convex_hull.size()-2],convex_hull.back(), l))convex_hull.pop_back();

                convex_hull.push_back(l);

        }

        int query(int x) 
        {
                while (convex_hull.size() >= 2 && f(convex_hull[0], x) >= f(convex_hull[1], x))convex_hull.pop_front();

                return f(convex_hull[0],x);

        }
};





const int N = 2e5+100;
int dp[N];


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,c;
        cin>>n>>c;



        vector<int>h;

        for(int i=0;i<n;i++)
        {
                int a;
                cin>>a;

                h.push_back(a);

                dp[i] = inf;
        }

        // cost function = dp[j] + (h[j]-h[i])*(h[j]-h[i]) + c

        // cost function = h[i]^2    -2h[j]*h[i] + h[j]^2+dp[j]+c
        // consider                  (-2h[j] = m),   (h[i] = x), (h[j]^2+dp[j]+c = C)
        // goal is to         for each h[i] = x, at i point finding the minimum -2h[j]*h[i] + h[j]^2+dp[j]+c     for some value of {m,C} or (-2h[j] = m) & (h[j]^2+dp[j]+c = C)

        



        // Also given x is monotonic, ie, h[i] < h[i+1] < h[i+2] ........

        // so deque based CHT will work

        dp[0] = 0;


        CHT cht;

        cht.add_line({-2*h[0], h[0]*h[0]+dp[0]+c});

        for(int i=1;i<n;i++)
        {
                int mn = cht.query(h[i]); // h[i] = x;

                dp[i] =  h[i]*h[i] + mn;

                cht.add_line({-2*h[i], h[i]*h[i]+dp[i]+c});
                
        }


        cout<<dp[n-1]<<endl;







}

```

---

## 2. Li Chao Tree

### When to use:

You should use a Li Chao Tree when **either the slopes ($m_j$) OR the query points ($x_i$) are NOT monotonic**.
If lines are added in an arbitrary slope order, or queried at arbitrary $x$-coordinates, the simple deque approach fails because lines can intercept randomly and old lines might become useful again.

### Why it works:

Li Chao Tree relies on the properties of a Segment Tree over the domain $[L, R]$ of the $x$-coordinates.
Each node in the segment tree represents an interval $[l, r]$ and stores exactly one line. This line is guaranteed to be the **most optimal line at the midpoint** `mid = (l + r) / 2` of that interval.

* **Addition:** When adding a new line, we evaluate it at the midpoint. If it's better than the node's current line, they are swapped. Since two lines can intersect at most once, the "losing" line can only be better on *one* half of the remaining interval. We recursively push the losing line down to the appropriate child (left or right).
* **Querying:** To find the minimum for a specific $x$, we traverse the tree down to the leaf representing $x$. The optimal value is simply the minimum evaluated value among all lines stored on the path from the root to that leaf.




## Visualization


```text
                              [0, 8)
                             Line: L2
                           (y = -x + 10)
                          /             \
                         /               \
                  [0, 4)                   [4, 8)
                 Line: L3                   null
               (y = x + 2)
                /       \
               /         \
           [0, 2)       [2, 4)
          Line: L1       null
        (y = 2x + 1)
          /    \
       null    null

```

#### Visualizing the Query for $x = 1$:

When querying for the minimum at $x = 1$, you follow the path down the tree where $1$ falls into the range. You evaluate the stored line at each step and keep a running minimum:

1. **Visit [0, 8):** * $x = 1$ is in the left half $[0, 4)$.
* Evaluate L2 at $x = 1$: $-(1) + 10 = 9$.
* **Current Min: 9**
* *Move Left* ↙️


2. **Visit [0, 4):**
* $x = 1$ is in the left half $[0, 2)$.
* Evaluate L3 at $x = 1$: $(1) + 2 = 3$.
* **Current Min: min(9, 3) = 3**
* *Move Left* ↙️


3. **Visit [0, 2):**
* $x = 1$ is in the right half $[1, 2)$. (Midpoint is 1).
* Evaluate L1 at $x = 1$: $2(1) + 1 = 3$.
* **Current Min: min(3, 3) = 3**
* *Move Right* ↘️


4. **Visit [1, 2) (Right child of [0, 2)):**
* Node is `null`.
* **Stop Search.**

**Final Result:** The minimum value is **3**.




### Variable Name Convention:

* `L`, `R`: The minimum and maximum possible values for the domain of $x$.
* `root`: The root node of the dynamic pointer-based segment tree.
* `nw`: The new line being inserted into the tree.

---

### Problem Use Case 1: Z - Frog 3 (using Li Chao Tree)

Even though CHT works for Frog 3, Li Chao Tree is entirely generalized and will easily pass. It requires no assumption about the sorting of $h_i$.

```cpp
//Intermediary
//Young kid on the block
//AIAsif try's Continuing the journey
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
#define inf 1000000000000000000
#define int long long int
#define ordered_set tree< int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>
     





struct Line 
{
        int m, b;

        int   get(int x)
        {
                return m *x+b;
        }
};

struct Node 
{
        Line line;
        
        Node *left= nullptr;
        
        Node *right =nullptr;

        Node(Line v ) : line(v ) {}
};

struct LiChao 
{
        int L, R;
        
        Node *root;

        LiChao(int l ,  int r) 
        {
                L = l;
                
                R = r;

                root = new Node({0, inf});
        }

        void add_line(Line nw) 
        {
                add_line(root, L , R , nw);
        }

        void add_line(Node* node, int l, int r, Line nw) 
        {
                int mid = (l + r) / 2;

                bool left = nw.get(l) <node->line.get(l);

                bool middle = nw.get(mid)< node->line.get(mid);

                if(middle) 
                {
                        swap(node->line, nw);
                }

                if(r - l == 1)
                {
                        return;
                }

                if(left != middle) 
                {
                        if(!node->left) 
                        {
                                node->left= new Node({0, inf});
                        }

                        add_line(node->left, l, mid, nw);

                }
                else 
                {
                        if(!node->right)
                        {
                                node->right =new Node({0 , inf});
                        }

                        add_line(node->right, mid, r, nw);
                }
        }

        int query(int x) 
        {
                return query(root, L, R, x);
        }

        int query(Node* node, int l, int r, int x) 
        {
                if(!node) 
                {
                        return inf;
                }

                int res = node->line.get(x);

                if(r - l ==1)
                {
                        return res;
                }

                int mid = (l + r) / 2;

                if(x < mid && node->left)
                {
                        res = min(res,query(node->left, l, mid, x));
                }
                else if(x >=mid &&node->right)
                {
                        res = min(res,query(node->right, mid, r, x));
                }

                return res;
        }
};






const int N = 2e5+100;
int dp[N];


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,c;
        cin>>n>>c;



        vector<int>h;

        for(int i=0;i<n;i++)
        {
                int a;
                cin>>a;

                h.push_back(a);

                dp[i] = inf;
        }

        // cost function = dp[j] + (h[j]-h[i])*(h[j]-h[i]) + c

        // cost function = h[i]^2    -2h[j]*h[i] + h[j]^2+dp[j]+c
        // consider                  (-2h[j] = m),   (h[i] = x), (h[j]^2+dp[j]+c = C)
        // goal is to         for each h[i] = x, at i point finding the minimum -2h[j]*h[i] + h[j]^2+dp[j]+c     for some value of {m,C} or (-2h[j] = m) & (h[j]^2+dp[j]+c = C)

        

        dp[0] = 0;


        LiChao Tree(-1e7, 1e7); // range of h[i], or x

        Tree.add_line({-2*h[0], h[0]*h[0]+dp[0]+c});

        for(int i=1;i<n;i++)
        {
                int mn = Tree.query(h[i]); // h[i] = x;

                dp[i] =  h[i]*h[i] + mn;

                Tree.add_line({-2*h[i], h[i]*h[i]+dp[i]+c});
                
        }


        cout<<dp[n-1]<<endl;







}

```

---

## 3. Case Study: 2D State DP Optimization

### We can solve K-partition dp problems too, where we generally had to apply Divide and conquer dp, if possible.

### Problem: SPOJ NKLEAVES

In this problem, we are grouping elements into $K$ intervals. It introduces a 2D state $dp[i][kk]$, meaning we must maintain *multiple* CHT envelopes—one for each value of $kk$. Because weights are positive, the `pref[j]` prefix sum is strictly increasing (so $m_j = -pref[j]$ is monotonically decreasing), and the indices $x_i = i$ are strictly increasing. Deque CHT is highly efficient here.

```cpp
//Intermediary
//Young kid on the block
//AIAsif try's Continuing the journey
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
#define inf 1000000000000000000
#define int long long int
#define ordered_set tree< int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>
      

const int N = 1e5+100;
const int K = 12;

int dp[N][K]; // dp[i][k] minimum cost from 0.......i, with k+1 partition

int pref[N];
int f[N];




struct line 
{
        int m, b;
};

struct CHT 
{
        deque<line> convex_hull;

        int f(const line &l,int x) 
        {
                return l.m* x +l.b;
        }

        bool bad(line l1, line l2, line l3) 
        {
                return (__int128 )( l3.b -  l1.b)* (l1.m - l2.m) <= ( __int128)( l2.b - l1.b) *(l1.m -l3.m);
        }

        void add_line(line l) 
        {

                while (convex_hull.size() >= 2 && bad(convex_hull[convex_hull.size()-2],convex_hull.back(), l))convex_hull.pop_back();

                convex_hull.push_back(l);

        }

        int query(int x) 
        {
                while (convex_hull.size() >= 2 && f(convex_hull[0], x) >= f(convex_hull[1], x))convex_hull.pop_front();

                return f(convex_hull[0],x);

        }
} cht[12];



int Cost(int i,int j)
{
        if(i==0)
        {
                return f[j];
        }


        return f[j] - f[i-1]-(j-i+1)*pref[i-1];
}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,k;
        cin>>n>>k;

        vector<int>v;

        for(int i=0;i<n;i++)
        {
                int a;
                cin>>a;
                v.push_back(a);
        }

        reverse(v.begin(), v.end());

        pref[0] = v[0];
        f[0] = v[0];

        for(int i=1;i<n;i++)
        {
                pref[i] = pref[i-1]+v[i];

                f[i] = f[i-1]+pref[i];
        }



        for(int i=0;i<=n;i++)
        {
                for(int j=0;j<=k;j++)
                {
                        dp[i][j] = inf;
                }

        }


        dp[0][0] = 0;

        for(int i=1; i<n; i++)
        {
                dp[i][0] = Cost(0,i-1);

                
        }








        // It can be solved using  Divide and conquer dp optmizition, as the cost function is related to prefix and monotonicity property obayed. But we are solving it using CHT

       

        for(int i=1;i<n;i++)
        {
                for(int kk=1;kk<k;kk++)
                {
                        CHT cht;

                        for(int j=kk; j<i; j++)
                        {
                                            // (-pref[j]*i) + (dp[j][kk-1] - f[j] + pref[j]*j + pref[j]));

                                            //  here m_j * x_i   ............... c_j .................

                                            // m_j = -pref[j]
                                            // x_i = i
                                            // c_j = (dp[j][kk-1] - f[j] + pref[j]*j + pref[j])


                                cht.add_line({-pref[j], (dp[j][kk-1] - f[j] + pref[j]*j + pref[j])});

                                

                                dp[i][kk] =  f[i-1] + cht.query(i);

                                                                                                
                        }
                }
        }



        cout<<dp[n-1][k-1]<<endl;









}

```


---

## Look, All three code are for minimum dp, for maximum dp we need to do modification to both CHT and LiChaoTree implementation




<br>

---
## Problem List:

```
https://vjudge.net/contest/794341#rank
```


