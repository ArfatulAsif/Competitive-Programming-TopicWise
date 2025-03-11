The **Möbius function** (denoted as **μ(n)**) is an important function in number theory, especially in combinatorial mathematics and number-theoretic transformations like the **Inclusion-Exclusion Principle** and **Dirichlet convolution**. It is used to count the number of square-free divisors of an integer and plays a crucial role in problems involving **coprime counting** and **multiplicative functions**.

# **Definition of the Möbius Function (μ(n)):**

The Möbius function μ(n) is defined for all positive integers `n` as follows:


$$
\mu(n) =
\begin{cases} 
1 & \text{if } n = 1 \\ 
(-1)^k & \text{if } n \text{ is square-free and has } k \text{ distinct prime factors} \\ 
0 & \text{if } n \text{ is not square-free (i.e., divisible by } p^2 \text{ for some prime } p)
\end{cases}
$$



1. **μ(n) = 1** if `n = 1`.
2. **μ(n) = 0** if `n` is divisible by a perfect square (other than 1). That is, if `n` has a prime factor **p** such that **p²** divides `n`, then `μ(n) = 0`.
3. **μ(n) = (-1)^k** if `n` is the product of `k` distinct prime numbers.  
   - If `n` has an **even** number of distinct prime factors, then `μ(n) = 1`.  
   - If `n` has an **odd** number of distinct prime factors, then `μ(n) = -1`.

# **Properties of the Möbius Function:**

1. **Multiplicative Property:**  
   - The Möbius function is **multiplicative**, meaning that if `gcd(a, b) = 1`, then:  
     **μ(a × b) = μ(a) × μ(b)**  
   - Example: Since `μ(3) = -1` and `μ(5) = -1`, we get `μ(15) = μ(3) × μ(5) = (-1) × (-1) = 1`.
   - [Proof](https://en.wikipedia.org/wiki/M%C3%B6bius_function#Properties)

2. **Summation Property for Divisors:**  
   - The sum of the Möbius function over all divisors of `n` is:  
     **Σ μ(d) = 1 if n = 1, otherwise 0**, where the sum runs over all divisors `d` of `n`.
     

3. **Relation to Prime Factorization:**  
   - If `n` is square-free (does not contain any repeated prime factors), then `μ(n) = (-1)^k`, where `k` is the number of distinct prime factors.
   - If `n` is **not** square-free (contains `p²` for some prime `p`), then `μ(n) = 0`.

4. **Dirichlet Inversion:**  
   - The Möbius function is the inverse of the **constant 1 function** under Dirichlet convolution.  
   - That is, for any function `f(n) = Σ g(d)`, we can recover `g(n)` using the Möbius function:  
     **g(n) = Σ μ(d) * f(n/d)**.

5. **Relation to Euler's Totient Function (φ(n)):**  
   - The Möbius function is connected to the **Euler totient function** via the formula:  
     **φ(n) = Σ μ(d) × (n/d)**, where the sum is over all divisors `d` of `n`.

### **Example Values of Möbius Function:**
| n  | Prime Factorization | μ(n) |
|----|--------------------|------|
| 1  | -                  | 1    |
| 2  | 2                  | -1   |
| 3  | 3                  | -1   |
| 4  | 2²                 | 0    |
| 5  | 5                  | -1   |
| 6  | 2 × 3              | 1    |
| 7  | 7                  | -1   |
| 8  | 2³                 | 0    |
| 9  | 3²                 | 0    |
| 10 | 2 × 5              | 1    |
| 12 | 2² × 3             | 0    |
| 15 | 3 × 5              | 1    |
| 30 | 2 × 3 × 5          | -1   |


<br>
<br>

---

<br>

# **Using Möbius Function to Find the Number of Coprime Pairs**  

To understand how the **Möbius function** helps in counting **coprime pairs** using the **Inclusion-Exclusion Principle**, let's define the problem formally and derive the formula.  

## **Problem Definition**  
Given a list of $n$ numbers, we want to count the number of pairs $(a, b)$ such that **$\gcd(a, b) = 1$**.  

### **Approach Using Inclusion-Exclusion**  
Instead of directly counting coprime pairs, we first count **all pairs** and then subtract pairs that share common factors.  

#### **Step 1: Total Number of Pairs**  
If we have $n$ numbers, the total number of unordered pairs is:  

$$
\frac{n(n - 1)}{2}
$$

(since each element can be paired with $n-1$ others, and each pair is counted twice).  

#### **Step 2: Count Pairs That Are NOT Coprime**  
To count pairs $(a, b)$ that are **not** coprime, we consider numbers divisible by some integer $d > 1$.  

1. **Define $cnt(d)$:** The number of elements in the list that are divisible by $d$.  
2. If both $a$ and $b$ are divisible by $d$, their **gcd is at least $d$**, meaning they are not coprime.  
3. The number of such pairs is given by:  


$$
\frac{cnt(d) \times (cnt(d) - 1)}{2}
$$

---

# **Step 3: Inclusion-Exclusion with the Möbius Function**  

The Möbius function determines the **sign** in the inclusion-exclusion count.  

In inclusion-exclusion, we:  
- **Add** contributions of sets with an **odd** number of items.  
- **Subtract** contributions of sets with an **even** number of items.  

## **Understanding the Role of the Möbius Function**  
Consider counting the number of **coprime pairs** in a given list. For simplicity, assume that numbers in the list have at most two prime factors, $p_1$ and $p_2$.  

1. Start with the total number of pairs: **$\frac{n(n - 1)}{2}$**  
2. Subtract the pairs that are divisible by $p_1$ (sign = -1).  
3. Subtract the pairs that are divisible by $p_2$ (sign = -1).  
4. Add back the pairs that are divisible by $p_1 \times p_2$ (sign = +1).  

This follows the inclusion-exclusion pattern.  

The **Möbius function** determines the sign for each number:  
- If a number has an **odd** number of distinct prime factors, the sign is **$-1$**, meaning we **remove** its contribution.  
- If a number has an **even** number of distinct prime factors, the sign is **$+1$**, meaning we **add** its contribution.  
- If a number is divisible by a **perfect square** (such as $p^2$), it contributes nothing (**$\mu(d) = 0$**) because its contribution cancels out.  

Using the **Inclusion-Exclusion Principle**, we subtract pairs with **gcd $> 1$** from the total.  

### **Final Formula for Counting Coprime Pairs**  

$$
\frac{n(n-1)}{2} - \sum_{d=2}^{\max_x} \mu(d) \times \frac{\text{cnt}(d) \times (\text{cnt}(d)-1)}{2}
$$

where:  
- $\text{cnt}(d)$ is the count of numbers divisible by $d$ in the array.  
- $\mu(d)$ is the Möbius function.  

---

## **Example Calculation**  
Consider the array **$[2, 3, 4, 6]$**.  
Total pairs:  

$$
\frac{4 \times 3}{2} = 6
$$

Now, count pairs with **gcd $> 1$** using the Möbius function.  

1. $cnt(2) = 3$ (Numbers: $2, 4, 6$)  , we remove $\frac{3*(3-1)}{2}$ or **sign = -1**.
2. $cnt(3) = 2$ (Numbers: $3, 6$)  we remove $\frac{2*(2-1)}{2}$
3. $cnt(6) = 1$ (Number: $6$)  " we add  $\frac{1*(1-1)}{2}$


Applying the formula:  

$$
\text{Non-coprime pairs} = \frac{3(3-1)}{2} \times \mu(2) + \frac{2(2-1)}{2} \times \mu(3) + \frac{1(1-1)}{2} \times \mu(6)
$$

$$
= (3 \times 1) + (1 \times 1) + (0 \times (-1)) = 3 + 1 + 0 = 4
$$

So, the number of coprime pairs is:  

$$
6 - 4 = 2
$$

---

## **Why This Works?**  

The **Möbius function acts as a correction term** in the Inclusion-Exclusion sum, ensuring that we do not double-count or miss any numbers while applying the principle.  

Thus, we efficiently count coprime pairs in **$O(n \log x)$ complexity** instead of the brute-force **$O(n^2)$** approach.



**Solution:**

[Counting Coprime Pairs](https://cses.fi/problemset/result/12307319/)

```cpp
const int N = 1e6+100;
int cnt[N];
bool sieve[N];
int mobius[N];
int D[N];
int arr[N];

void pre()
{
        memset(sieve, true, sizeof(sieve));

        for(int i=2;i<N;i++)
        {
                if(sieve[i])
                {
                        cnt[i] = 1;

                        for(int j=i+i;j<N;j += i)
                        {
                                sieve[j] = false;

                                if(cnt[j] == -1)
                                {
                                        continue;
                                }

                                cnt[j]++;

                                if(j % (i*i) ==0)
                                {
                                        cnt[j] = -1;
                                }
                        }
                }
        }

        mobius[1] = 1;
        mobius[2] = -1;

        for(int i=3;i<N;i++)
        {
                if(cnt[i]==-1)
                {
                        mobius[i] = 0;
                }
                else if(cnt[i]%2==0)
                {
                        mobius[i] = 1;
                }
                else 
                {
                        mobius[i] = -1;
                }
        }


}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;

        vector<int>v;
        for(int i=0;i<n;i++)
        {
                int a;
                cin>>a;
                v.push_back(a);
                arr[a]++;
        }

        pre();

        for(int d = N-50; d >= 1; d--)
        {
                int count = 0;
                for(int i = d; i<N; i += d)
                {
                        count += arr[i];
                }

                D[d] = count;
        }


        int ans = n*(n-1);
        ans /= 2;

        for(int i=2;i<N;i++)
        {
                ans += mobius[i]* (D[i]*(D[i]-1))/2; // Here mobius[i] works as a sign for inclusion exclusion.

                
        }

        cout<<ans<<endl;





}
```

<br>


**The problem can be extended to find `triplets`, or `more`** 
