
# 📚 Knuth Optimization

## This dp optimization is for Interval DP or Range DP:

**Knuth optimization** (also called **Knuth’s DP optimization**) is a technique that speeds up certain dynamic programming (DP) algorithms from **O(n³)** to **O(n²)** by exploiting structural properties of the cost function.

It was originally introduced by Donald Knuth to optimize the construction of Optimal Binary Search Trees.

---

# 1️⃣ The Type of DP It Applies To

Knuth optimization applies to **Interval DP** transitions of the specific form:

$$dp[i][j] = \min_{i < k < j} \big(dp[i][k] + dp[k][j] + C(i,j)\big)$$

*Note: The exact range of $k$ ($i \le k < j$ or $i < k < j$) depends on whether the split points are on the elements (like BST) or between them (like Matrix Chain).*

**Where:**

* We are partitioning an interval $[i, j]$.
* $k$ is the split point.
* $C(i,j)$ is a cost function associated with the interval, **independent** of $k$.

---

# 2️⃣ Why Normal DP is Slow

A standard implementation requires three nested loops:

```cpp
for (len = 1..n-1)
  for (i = 0..n-len-1)
    j = i + len
    for (k = i..j) // Iterating all split points

```

**Complexity Analysis:**

* **States:** $O(n^2)$ states for interval $[i, j]$.
* **Transitions:** $O(n)$ choices for split point $k$.
* **Total:** $O(n^3)$

---

# 3️⃣ The Key Insight

Knuth observed that for cost functions satisfying specific properties, the **optimal split point** moves monotonically.

Let $opt[i][j]$ be the value of $k$ that minimizes the transition for $dp[i][j]$.

**The Optimization Condition:**


$$opt[i][j-1] \le opt[i][j] \le opt[i+1][j]$$

This means we do not need to iterate $k$ from $i$ to $j$. We only need to search in the restricted range defined by the optimal splits of the **sub-intervals**:

$$k \in [opt[i][j-1], \quad opt[i+1][j]]$$

This drastically reduces the search space for $k$.

---

# 4️⃣ The Required Conditions

For the monotonicity of $opt[i][j]$ to hold, the cost function $C(i,j)$ must satisfy two conditions:

### ✅ 1. Quadrangle Inequality (Monge Property)

$$C(a,c) + C(b,d) \le C(a,d) + C(b,c)$$


For all $a \le b \le c \le d$. (Intuitively: "crossing" arcs are cheaper than "nested" arcs).

### ✅ 2. Monotonicity of Cost

$$C(b,c) \le C(a,d)$$


For all $a \le b \le c \le d$. (The cost of a sub-interval is less than or equal to the cost of the larger interval).

---

### 🛠️ Common Cost Functions That Work

1. **Prefix SUM type function**
2. **Sum of Elements / Length:** 
3. **Interval Length:** $C(i, j) = j - i$.

---

# 5️⃣ Complexity

When we restrict the search range of $k$:

* The inner loop runs approx $(opt[i+1][j] - opt[i][j-1])$ times.
* This creates a telescoping sum when analyzing the total complexity across diagonals.
* The amortized cost for computing all states reduces to **O(n²)**.

---

# 6️⃣ Implementation Pattern

The loops must be ordered by **length** of the interval to ensure sub-problems are solved first.

```cpp
// Iterate by length of the interval
for (int len = 1; len < m; len++) {
    // Iterate start index
    for (int i = 0; i < m - len; i++) {
        int j = i + len;
        
        dp[i][j] = INF;
        
        // Optimization: Restrict k search space
        // opt[i][j-1] <= k <= opt[i+1][j]
        for (int k = opt[i][j-1]; k <= opt[i+1][j]; k++) {
            
            int val = dp[i][k] + dp[k][j] + cost(i, j);
            
            if (val < dp[i][j]) {
                dp[i][j] = val;
                opt[i][j] = k; // Store optimal k
            }
        }
    }
}

```

---

# 7️⃣ Classic Problems & Implementations

### Problem 1: Breaking Strings (SPOJ BRKSTRNG)

* **Goal:** Break a string of length $N$ at given locations $M$. Minimize total cost, where breaking a segment of length $L$ costs $L$.
* **Type:** Cutting Sticks variation.
* **Link:** [SPOJ BRKSTRNG](https://www.spoj.com/problems/BRKSTRNG/en/)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define inf 1000000000000000000

const int N = 1005;
int dp[N][N];
int opt[N][N];
int ara[N];
int pref[N];

// Cost is the length of the string segment being broken
// which corresponds to the sum of the pieces inside it
int f(int i, int j) {
    if(i == 0) return pref[j];
    return pref[j] - pref[i-1];
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m;

    while(cin >> n >> m) {
        vector<int> v;
        for(int i = 0; i < m; i++) {
            int a; cin >> a;
            v.push_back(a);
        }
        v.push_back(n);

        // Preprocessing segment lengths between cuts
        ara[0] = v[0];
        for(int i = 1; i < v.size(); i++) {
            ara[i] = v[i] - v[i-1];
        }

        pref[0] = ara[0];
        for(int i = 1; i <= m; i++) {
            pref[i] = pref[i-1] + ara[i];
        }
        
        // Initialization
        for(int i = 0; i <= m; i++) {
            for(int j = 0; j <= m; j++) {
                dp[i][j] = inf;
                opt[i][j] = 0;
                if(i == j) {
                    dp[i][j] = 0;
                    opt[i][i] = i; // Base case for opt
                }
            }
        }

        m++; // Adjust for total segments including final piece

        // Knuth Optimization Loop
        for(int l = 1; l < m; l++) { // Length
            for(int i = 0; i < m - l; i++) { // Start
                int j = i + l; // End

                // Restricted search range for k
                for(int k = opt[i][j-1]; k <= opt[i+1][j]; k++) {
                    int val = dp[i][k] + dp[k+1][j] + f(i, j);

                    if(val < dp[i][j]) {
                        dp[i][j] = val;
                        opt[i][j] = k;
                    }
                }
            }
        }
        cout << dp[0][m-1] << endl;
    }
}

```

---

### Problem 2: Cutting Sticks (UVa 10003)

* **Goal:** Similar to Breaking Strings. You have to cut a stick at specific coordinates.
* **Link:** [Online Judge 944 / UVa 10003](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=944)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define inf 1000000000000000000

const int N = 1005;
int dp[N][N];
int opt[N][N];
int ara[N];
int pref[N];

int f(int i, int j) {
    if(i == 0) return pref[j];
    return pref[j] - pref[i-1];
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m;

    while(cin >> n >> m) {
        if(n == 0) break;

        vector<int> v;
        for(int i = 0; i < m; i++) {
            int a; cin >> a;
            v.push_back(a);
        }
        v.push_back(n);

        ara[0] = v[0];
        for(int i = 1; i < v.size(); i++) {
            ara[i] = v[i] - v[i-1];
        }

        pref[0] = ara[0];
        for(int i = 1; i <= m; i++) {
            pref[i] = pref[i-1] + ara[i];
        }
        
        // Init DP
        for(int i = 0; i <= m; i++) {
            for(int j = 0; j <= m; j++) {
                dp[i][j] = inf;
                opt[i][j] = 0;
                if(i == j) {
                    dp[i][j] = 0;
                    opt[i][i] = i;
                }
            }
        }

        m++; 

        // Main Loop
        for(int l = 1; l < m; l++) {
            for(int i = 0; i < n - l; i++) { // Note: bound depends on mapped array size
                int j = i + l;

                for(int k = opt[i][j-1]; k <= opt[i+1][j]; k++) {
                    int val = dp[i][k] + dp[k+1][j] + f(i, j);

                    if(val < dp[i][j]) {
                        dp[i][j] = val;
                        opt[i][j] = k;
                    }
                }
            }
        }
        cout << "The minimum cutting is " << dp[0][m-1] << "." << endl;
    }
}

```

---

### Problem 3: Optimal Binary Search Tree (UVa 10304)

* **Goal:** Construct a BST given frequencies of elements to minimize total search cost (Sum of `freq * depth`).
* **Logic:** The transition usually adds the sum of frequencies in the range $(i, j)$ because pushing a subtree down one level increases the cost by the sum of its frequencies.
* **Link:** [Online Judge 1245 / UVa 10304](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1245)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define inf 1000000000000000000

const int N = 1005;
int dp[N][N];
int opt[N][N];
int ara[N];
int pref[N];

int f(int i, int j) {
    if(i > j) return 0;
    if(i == 0) return pref[j];
    return pref[j] - pref[i-1];
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n;

    while(cin >> n) {
        vector<int> v;
        for(int i = 0; i < n; i++) cin >> ara[i];

        pref[0] = ara[0];
        for(int i = 1; i < n; i++) {
            pref[i] = pref[i-1] + ara[i];
        }

        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= n; j++) {
                dp[i][j] = inf;
                opt[i][j] = 0;
                if(i == j) {
                    dp[i][j] = 0; // Cost of empty tree is 0
                    opt[i][i] = i;
                }
            }
        }

        for(int l = 1; l < n; l++) { // Length
            for(int i = 0; i < n - l; i++) {
                int j = i + l;                      

                // Knuth Search Range
                for(int k = opt[i][j-1]; k <= opt[i+1][j]; k++) {
                    
                    int left  = (k > i) ? dp[i][k-1] : 0;
                    int right = (k < j) ? dp[k+1][j] : 0;

                    // Cost = Left + Right + Sum of Frequencies - Root Freq
                    // (Variant of standard formula depending on depth definition)
                    int val = left + right + f(i, j) - ara[k];

                    if(val < dp[i][j]) {
                        dp[i][j] = val;
                        opt[i][j] = k;
                    }
                }
            }
        }
        cout << dp[0][n-1] << endl;
    }
}

```
