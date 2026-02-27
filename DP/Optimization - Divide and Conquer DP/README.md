# 🚀 Divide & Conquer DP Optimization

## Primarily for K - partition problems:

This is used to speed up transitions of this exact form:

$$dp[i][k] = \min_{j \le i} \Big( dp[j-1][k-1] + \text{cost}(j, i) \Big)$$

Where:

* `i` = position in the array
* `k` = number of partitions
* `j` = iteration point from (k to i)

---

# 1️⃣ When Is It Applicable?

You can use Divide & Conquer optimization if:

### ✅ The optimal split point is monotonic:

```
opt[i][k] ≤ opt[i+1][k]

```

Where:

* `opt[i][k]` = value of `j` that minimizes `dp[i][k]`

This is called **monotonicity of decision points**.

If this holds → we can reduce complexity significantly.

**Also, if the problem is about K-partition type but the value of N, K is quite large O(KN^2) would give TLE, that means optimizations**

---

# 2️⃣ Why Is Normal DP Slow?

Naive transition:

```cpp
for (int i = 1; i <= N; i++) {
  for (int k = 1; k <= K; k++) {
    for (int j = k; j <= i; j++) {
       // Transition
    }
  }
}

```

Time complexity:
`O(K * N²)`

If N = 5000 and K = 5000 → too slow (will result in TLE).

---

# 3️⃣ Core Idea

Instead of calculating `dp[i][k]` linearly from left to right, we calculate it for the **middle** element of our current search space.

1. Suppose we are calculating `dp[i][k]` for $i$ in the range `[L, R]`, and we know the optimal split point `j` lies in the range `[optL, optR]`.
2. We find the middle point: `mid = (L + R) / 2`.
3. We find the optimal split point for `mid` by iterating `j` from `optL` to `min(mid, optR)`. Let's call this best split point `opt`.
4. Because of monotonicity (`opt[i][k] ≤ opt[i+1][k]`), we now know:
* For all $i < mid$, the optimal split point is $\le opt$.
* For all $i > mid$, the optimal split point is $\ge opt$.


5. We can now recursively solve the left half `[L, mid-1]` with search bounds `[optL, opt]` and the right half `[mid+1, R]` with search bounds `[opt, optR]`.

---

# 4️⃣ The Recursive Structure

The implementation almost always looks like this generic template:

```cpp
void compute(int k, int L, int R, int optL, int optR) {
    if (L > R) return;

    int mid = (L + R) / 2;
    pair<int, int> best = {inf, -1};

    // Find the optimal decision point for 'mid'
    for (int i = optL; i <= min(mid, optR); i++) {
        int val = dp[i-1][k-1] + cost(i, mid);
        if (val < best.first) {
            best = {val, i};
        }
    }

    dp[mid][k] = best.first;
    int opt = best.second;

    // Recursively solve left and right halves
    compute(k, L, mid - 1, optL, opt);
    compute(k, mid + 1, R, opt, optR);
}

```

---

# 5️⃣ Complexity

Because we halve the search space `[L, R]` at each step, the recursion tree has a depth of `O(log N)`.
At each level of the recursion tree, the `for` loops iterate through the valid `opt` ranges, which essentially sweep across the array, taking `O(N)` time across the entire level.

Each row becomes:
`O(N log N)`

Total Time Complexity:
`O(K * N log N)`

In some tighter analyses, it's close to `O(K * N)`.
Huge improvement over `O(K * N²)`.

---

# 6️⃣ When Does Monotonicity Hold?

Usually when cost satisfies:

## Quadrangle Inequality

For all $a \le b \le c \le d$:

$$\text{cost}(a,c) + \text{cost}(b,d) \le \text{cost}(a,d) + \text{cost}(b,c)$$

Many prefix-based cost functions satisfy this.
Common valid costs:

* Prefix related
* Sum of subarray squared
* Number of equal pairs in a segment
* Some prefix-sum-based metrics (like number of distinct elements)

---

# 7️⃣ Classic Example

Partition array into K groups minimizing:

$$\text{cost}(l,r) = (\text{prefix}[r] - \text{prefix}[l-1])^2$$

Very common in advanced problems on:

* Codeforces
* AtCoder

---

# Problem 1 : [https://codeforces.com/gym/103536/problem/A](https://codeforces.com/gym/103536/problem/A)

**Guards**
Assigning guards so that the total escaping possibility (prefix sum squared) is minimized.

**Divide and conquer solution:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define inf 1000000000000000000
const int N = 8001;
const int KK = 3001;

int dp[N][KK];
int pre[N];

int f(int l, int r) {
    int k = r - l + 1;
    if(l == 0) return (pre[r] * k);
    return ((pre[r] - pre[l-1]) * k);
}

void compute(int k, int L, int R, int optL, int optR) {
    if(L > R) return;
    int mid = (L + R) / 2;
    pair<int,int> best = {inf, -1};

    for(int i = optL; i <= min(optR, mid); i++) {
        int val = dp[i-1][k-1] + f(i, mid);                
        if(val < best.first) best = {val, i};
    }

    dp[mid][k] = best.first;
    int opt = best.second;

    compute(k, L, mid - 1, optL, opt);
    compute(k, mid + 1, R, opt, optR);
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, K; cin >> n >> K;
    vector<int> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];

    pre[0] = v[0];
    for(int i = 1; i < n; i++) pre[i] = pre[i-1] + v[i];

    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= K; j++)
            dp[i][j] = inf;

    for(int i = 0; i < n; i++) dp[i][0] = f(0, i);

    for(int k = 1; k < K; k++) {
        compute(k, k, n - 1, k, n - 1);
    }

    cout << dp[n-1][K-1] << "\n";
}

```

---

## Problem 2: [https://codeforces.com/problemset/problem/868/F](https://codeforces.com/problemset/problem/868/F)

**Yet Another Minimization Problem**
Minimize the number of unordered pairs of distinct indices within subsegments that contain equal elements. Uses Mo's algorithm style tracking for the cost function.

**Divide and conquer solution:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define inf 1000000000000000000
const int N = 100001;
const int KK = 21;

int dp[N][KK]; // dp[i][k] = minimum cost from 1.....i and having k+1 segments
int ara[N], cnt[N];
int nl=1, nr=0, ans=0;

void add(int p) { ans += cnt[ara[p]]++; }
void del(int p) { ans -= --cnt[ara[p]]; }

int f(int l, int r) {
    while(nl < l) del(nl++);
    while(nl > l) add(--nl);
    while(nr > r) del(nr--);
    while(nr < r) add(++nr);
    return ans;
}

void compute(int k, int L, int R, int optL, int optR) {
    if (L > R) return;
    int mid = (L + R) / 2;
    pair<int,int> best = {inf, -1};

    for(int i = optL; i <= min(mid, optR); i++) {
        int val = dp[i-1][k-1] + f(i, mid);
        if(val < best.first) best = {val, i};
    }

    dp[mid][k] = best.first;
    int opt = best.second;

    compute(k, L, mid - 1, optL, opt);
    compute(k, mid + 1, R, opt, optR);
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, K; cin >> n >> K;
    for(int i = 1; i <= n; i++) cin >> ara[i];

    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= K; j++)
            dp[i][j] = inf;

    for(int i = 1; i <= n; i++) dp[i][0] = f(1, i);

    for(int k = 1; k < K; k++) {
        compute(k, k + 1, n, k + 1, n);
    }

    cout << dp[n][K-1] << "\n";
}

```

---

## Problem: [https://codeforces.com/problemset/problem/834/D](https://codeforces.com/problemset/problem/834/D)

**The Bakery**
Maximize the number of distinct cake types in the boxes. Note that this is a *maximization* problem, so we reverse our `<` and `>` comparisons.

**Divide and conquer solution:**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 35005;
const int KK = 53;

int dp[N][KK]; 
int n, k, res, curl = 0, curr = -1, A[N];
int mp[N];

void add(int i) { if(mp[A[i]]++ == 0) res++; }
void rem(int i) { if(--mp[A[i]] == 0) res--; }

int f(int l, int r) {
    while(curr < r) add(++curr);
    while(l < curl) add(--curl);
    while(curr > r) rem(curr--);
    while(curl < l) rem(curl++);
    return res;
}

void compute(int k, int L, int R, int optL, int optR) {
    if (L > R) return;
    int mid = (L + R) / 2;
    pair<int,int> best = {0, -1};

    for(int i = optL; i <= min(mid, optR); i++) {
        int val = dp[i-1][k-1] + f(i, mid);
        // Notice the > for max profit
        if(val > best.first) best = {val, i};
    }

    dp[mid][k] = best.first;
    int opt = best.second;

    compute(k, L, mid - 1, optL, opt);
    compute(k, mid + 1, R, opt, optR);
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> A[i];

    for(int i = 1; i <= n; i++) dp[i][0] = f(1, i);

    for(int step = 1; step < k; step++) {
        compute(step, step + 1, n, step + 1, n);
    }

    cout << dp[n][k-1] << "\n";
}

```

---

# Space optimization: Using only two states.

**We can express all divide and conquer DP problems from `dp[N][K]` to `dp[N][2]`!** Because `dp[i][k]` is only calculated from `dp[j][k-1]` (where $j \le i$), all states for the current partition *only* rely on the immediately previous partition's row. So keeping track of `dp[N][2]` (current row and previous row) or just doing a linear array swap is enough to bring space complexity down from `O(N * K)` to `O(N)`.

## Problem: [https://codeforces.com/problemset/problem/1527/E](https://codeforces.com/problemset/problem/1527/E)

**Partition Game**
Split array into `K` segments to minimize the sum of `last(x) - first(x)` for each distinct element.

**Solution:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define inf 1000000000000000000
const int N = 35005;

// SPACE OPTIMIZATION: Only 2 columns instead of KK
int dp[N][2]; 

int n, k, res, curl = 0, curr = -1, A[N];
deque<int> dq[N];

void addR(int i) {
    int x = A[i];
    if(dq[x].size()) res += i - dq[x].back();
    dq[x].push_back(i);
}
void addL(int i) {
    int x = A[i];
    if(dq[x].size()) res += dq[x].front() - i;
    dq[x].push_front(i);
}
void remR(int i) {
    int x = A[i];
    dq[x].pop_back();
    if(dq[x].size()) res -= i - dq[x].back();
}
void remL(int i) {
    int x = A[i];
    dq[x].pop_front();
    if(dq[x].size()) res -= dq[x].front() - i;
}

int f(int l, int r) {
    while(curr < r) addR(++curr);
    while(l < curl) addL(--curl);
    while(curr > r) remR(curr--);
    while(curl < l) remL(curl++);
    return res;
}

// Instead of computing full dp[N][K], we only use dp[N][0] (prev) and dp[N][1] (curr)
void compute(int step, int L, int R, int optL, int optR) {
    if (L > R) return;
    int mid = (L + R) / 2;
    pair<int,int> best = {inf, -1};

    for(int i = optL; i <= min(mid, optR); i++) {
        int val = dp[i-1][0] + f(i, mid); // using previous layer dp[...][0]

        if(val < best.first) best = {val, i};
    }

    dp[mid][1] = best.first; // writing to current layer dp[...][1]
    int opt = best.second;

    compute(step, L, mid - 1, optL, opt);
    compute(step, mid + 1, R, opt, optR);
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> A[i];

    for(int i = 0; i <= n; i++) dp[i][0] = inf;

    for(int i = 1; i <= n; i++) dp[i][0] = f(1, i);

    for(int step = 1; step < k; step++) {
        compute(step, step + 1, n, step + 1, n);

        // Copy current states (1) over to previous states (0) for the next K iteration
        for(int i = 1; i <= n; i++) {
            dp[i][0] = dp[i][1];
        }
    }

    cout << dp[n][k > 1 ? 0 : 0] << "\n";
}

```

---




---

```
Problem List: https://vjudge.net/contest/793031#overview
```
