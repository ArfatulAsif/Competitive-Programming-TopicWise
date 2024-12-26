# Flow network
---

# Terminologies:

**Flow Network:** A flow network **N** is a weighted directed graph **G**, where the weight of edges is called capacity.

<br>

**Flow:** The value of the flow of a network **f**, denoted **|f|**, is the total flow going from the source **s**, which is equal to the total flow coming into the sink **t**.

<img src = "images/1.png">

<br>

**Maximum Flow:** The maximum flow problem involves finding the maximum flow from the source **s** to the sink **t** in a flow network **N**.

<img src ="images/2.png">

<br>

---

**Cut:** A cut of a flow network **N** is a partition of vertices **X = (Vs, Vt)**, where **Vs** is the set of vertices that includes the source **s**, and **Vt** is the set of vertices that includes the destination **t**.

<img src ="images/3.png">

**Forward edge of a cut X:** Origin in **Vs** and destination in **Vt**.  
**Backward edge of a cut X:** Origin in **Vt** and destination in **Vs**.

<br>

**Capacity of a cut C(X):** Total capacity of forward edges. 

<br>

**Flow of a cut f(X):** Total flow of forward edges minus the total flow of backward edges.

---
<br>

**Theorem:** The flow value across the network **N**, **|f|**, is equal to the flow of any cut **f(X)**.  

<br>

**Theorem:** The value of any flow (flow of a cut or the entire network) is less than or equal to the capacity of any cut.

<img src ="images/4.png">

---

**Minimum Cut:** A minimum cut is the cut whose capacity is the smallest among all possible cuts.  

<br>

In a graph, there can be multiple minimum cuts.

<br>

**Theorem (Max-Flow Min-Cut):** The value of the maximum flow is equal to the capacity of the minimum cut.

<img src ="images/4.png">
For example in this graph max flow = minimum cut = 23.

<br>
<br>

**If we can find the capacity of the minimum cut, then we have found the maximum flow. However, finding the capacity of the minimum cut is more difficult than finding the maximum flow using max flow algorithms.**

---

**Residual capacity of edge and path:**

**Residual Capacity (RC) of edges:**  

- **RC of a edge $\textbf{e}$, in forward direction from $\textbf{u}$ to $\textbf{v}$:**  
  $\Delta f(\textbf{u}, \textbf{v}) = c(\textbf{e}) - f(\textbf{e})$  
  (This is the capacity of the edge minus the flow of the edge.)  

- **RC of a edge $\textbf{e}$ in reverse direction from $\textbf{v}$ to $\textbf{u}$:**  
  $\Delta f(\textbf{v}, \textbf{u}) = f(\textbf{e})$  
  (This is the flow of the edge in forward direction. why do we consider edges in reverse direction? explained below)  
  
<br>

**Residual Capacity of a path from source to destination:**  
Let $\pi$ be a path from $\textbf{s}$ to $\textbf{t}$. The residual capacity $\Delta f(\pi)$ of $\pi$ is the smallest of the residual capacities of the edges in $\pi$.

<img src ="images/5.png">

<br>

**Augmenting Path:**  

<img src ="images/6.png">

<br>

**Residual Network:** If we replace the flow/capacity of the edges with the residual capacity of the edges, then the flow network we get is called the residual network.

<img src ="images/7.png">

<br>

---

<br>

## Flow Augmentation:

**Flow Augmentation:** This is the key iteration in all flow algorithms when finding the maximum flow.

While running the max flow algorithm, in each DFS or BFS iteration, it involves increasing the flow along an augmenting path.

<img src ="images/8.png">

<br>

**Flow augmentation involves:**  
**Forward edges:** Increasing the flow of each edge by the amount of the residual capacity of the augmenting path.  (In residual graph, decreasing residual capacity of edges, by the amount of the residual capacity of the augmenting path. (which is normally done in algorithms implementations).

**Backward edges:** Decreasing the flow of each edge by the amount of the residual capacity of the augmenting path (you can consider this as cancelling or undoing flow of forward edge). (In residual graph, increasing residual capacity of edges, by the amount of the residual capacity of the augmenting path. (which is normally done in algorithms implementations).

<img src ="images/9.png">

<br>

**Example of flow augmentation:**
<br>

<img src ="images/10.png">

Here **w -> v** is a backward edge. Or edge in reverse direction.

<br>

---

## Why decrease backward edges flow? (this is a very crucial to understand):  

Let’s say the current flow considered is:

<img src ="images/11.jpg">

By direct observation, if we don't undo **v → w** flow **5** and consider flow **5** towards **v → t**, there is no way to increase the max flow of the network.

<br>

OK!!, let’s consider an augmenting path in the flow **s → u → w → v → t**.  

<img src ="images/12.jpg">

Look at the **w → v** edge. It is reversed, i.e., **v → w** exists but not **w → v**. But we have to consider **w → v** because there might be the possibility of undoing **v → w** flow. How? Let’s look.

<br>

If we perform flow augmentation along **s → u → w → v → t**, the network becomes:

<img src ="images/13.jpg">

Previously, **s → v** flow was **5**, which went through **v → w** and then **w → t**. Now **v → w** is **0**, and **v → t** is **5**.

<br>

Now the question is: does this mean a flow is happening in this path **s → u → w → v → t**? The answer is NO. What actually happened was, initially, we considered flow **s → v → w → t**, but it blocked any flow in **s → u →** direction.  

<br>

So, we needed to cancel out or undo **v → w** flow, which we did by considering **w → v** along **s → u → w → v → t**.  

<br>

Thus, the flow is actually happening along **s → v → t (5)** and **s → u → w → t (5)**.
<img src ="images/14.jpg"> <img src ="images/15.jpg">

---

<br>

**If we don’t consider flow undoing (sending flow through reverse edges), we would have to find an algorithm that always chooses augmenting paths intelligently. This is an NP-Hard problem.**

<br>

**However, if we consider flow undoing (sending flow through reverse edges), we can arbitrarily choose any augmenting path without worry. Because if the current path was not ideal, in later iterations, we can undo the flow of edges.**

<br>

This is exactly what max flow algorithms do, which is why they have polynomial complexity.

---

### So, For max flow algorithms, we add a reverse edge for each edge to acheive flow undoing.**

<img src ="images/16.jpg"> <img src ="images/17.jpg">

<br>


**For max flow algorithms:**

<br>

**Capacity of edge:** Equal to the capacity of the edge.  
<br>

**Capacity of reverse edge:** Equal to the flow of the edge (in forward direction). **(Why? Because that is the maximum amount of flow we can cancel or undo for this edge.)**

<br>

---

# Now you are ready for flow algorithms, you know all basic terminologies

## Pathway:

1. **Max flow Ford-Fulkerson (O(E * maxflow))**  
2. **Max flow Edmond-karp (O(V * E^2))**  
3. **Max flow Dinics (O(V^2*E)) preferred to use.**  
4. **Minimum cut with dinics (O(V^2*E))**  
5. **Maximum bipartite matching with dinics for learning (O(V^2*E))**  
6. **Maximum bipartite matching hopcraft-karp (O(E * √V)) for use.**  
7. **Minimum cost Maximum Flow using Dijkstra, without negative cycle (O(min(E^2 * V log V, E log V * flow)))**  
8. **Minimum Weighted Maximum Bipartite Matching using MCMF ([O(min(E^2 * V log V, E log V * flow)))**  
9. **Weighted Maximum Bipartite Matching Hungarian (O(V^3))**  
10. **Vertex Cover & Independent Set topic learning.**  
11. **Minimum Vertex Cover/Maximum Independent Set in a Bipartite graph using hopcroft-karp (O(E * √V))**  
