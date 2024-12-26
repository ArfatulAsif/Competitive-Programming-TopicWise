
# Vertex Cover:
<br>

**A vertex cover in a graph is a set of vertices that includes at least one endpoint of every edge.**

<img src="images/vertex_cover1.png">

In the given graph, consider the vertex set **V_c = {1, 2, 3, 4}**. This set qualifies as a vertex cover because every edge in the graph has at least one endpoint within **V_c**. 
<br>

<img src="images/vertex_cover3_1234.jpg">

<br>

Similarly, the sets **V_c = \{1, 2, 4, 5\}**, **V_c = \{2, 3, 5\}** and **V_c = \{1, 2, 3, 4, 5\}** also serve as valid vertex covers.
<br>

<img src="images/vertex_cover3_1245.jpg"> <img src="images/vertex_cover3_235.jpg">

<br>

But **V_c = \{1, 2, 5\}** is **not** a vertex cover, because as we can see below, there is an edge which is not covered.

<br>

<img src="images/vertex_cover2.png">

<br> 
<br>
<br>

**Finding any vertex cover set is a simple task because the set of all vertices always serves as a vertex cover surely. However, the real challenge lies in finding the minimum vertex cover.**

<br>

## Minimum Vertex Cover:
<br>

**A vertex cover is minimum if no other vertex cover has fewer vertices. Number of vertices in the minimum vertex cover set is lowest among all the vertex cover sets**

<br>

For example in the graph, **V_c = \{2, 3, 5\}** is a minimum vertex cover.

<img src="images/vertex_cover3_235.jpg">

<br>


---


# Independent Set:
<br>

**An independent set in a graph is a set of vertices such that no edge in the graph connects any pair of vertices in the independent set.**

<img src="images/vertex_cover1.png">

For example in the graph, vertex set **I = {1, 4}** or **I = {1, 3}** is an independent set. Because no edge in the graph connects any pair of vertices in the independent set **I**. 

<br>

<img src="images/independent_set1.png"> <img src="images/independent_set2.png">


But **Set {1, 4, 5} or {1, 2, 3}** is not an independent set. As we can see, an edge connect the pair of vertices (4, 5) which are in **{1, 4, 5}** and two edges connets the pairs of vertices (1, 2) and (2, 3) which are in **{1, 2, 3**.

<img src="images/independent_set3.png"> <img src="images/independent_set4.png">


<br>
<br>
<br>

**Finding any independent set is very easy, as any single vertex set can serve as an independent set. example I = {1} or I = {2} ..**
<br>
**But the real challenge lies in finding the maximum independent set.**

<br>
<br>

## Maximum Independent Set:
<br>

**An independent set is maximum if no other independent set contains more vertices.**
<br>
For example in the above graph **I = {1, 4}** is a maximum independent set. or **I = {1, 3}**. 

<br>
<br>

**Example for an bipartite graph:**
<br>

<img src ="images/Independent_bipartite1.png">

The **left** vertices set or **right** vertices set can be considered an **independent set**. But maximum independent set could be different. 
<br>

<img src ="images/Independent_bipartite2.png">

These independent set contains **3** vertices, But below the Maximum Independent set contains **4** vertices......
<br>
<img src ="images/Independent_bipartite3.png">


---

# The minimum vertex cover is the exact opposite of the maximum independent set:
<br>

**In a graph, the vertices in the maximum independent set are precisely those not included in the minimum vertex cover, and vice versa.**

<br>

For example minimum vertex cover **V_c = {2, 3, 5}** and maximum independent set **I = {1, 4}**. <br>
They are excatly opposite/complement of each other, ie. **I = {V - V_c} or V_c = {V - I}**.


<img src="images/vertex_cover3_235.jpg">  <img src="images/independent_set1.png">



<br>
<br>

**For a graph, if we find the minimum vertex cover, we can also determine the maximum independent set by simply taking the complement of the minimum vertex cover.**


<br>
<br>

**However, finding the minimum vertex cover or the maximum independent set for any graph is an NP-hard problem.**

<br>

**However, things become interesting when we consider a bipartite graph.**

<br>

---

# Kőnig's theorem: In any bipartite graph, the number of edges in a maximum matching |M|, equals the number of vertices in a minimum vertex cover |V_c|.

<br>
For proof check the example section of : https://en.wikipedia.org/wiki/K%C5%91nig%27s_theorem_(graph_theory)#Example
<br>



---

<br>

# Find Minimum Vertex Cover in a Bipartite Graph Algorithm:
<br>

1. **Find the Maximum Matching**:
   - Use an algorithm like the **Hopcroft-Karp algorithm** or the **Edmonds-Karp algorithm** to find the maximum matching in the bipartite graph. This will give you the set of edges that form the matching. For contest use **Hopcroft-Karp algorithm**, as it is **O(E*√V)**.
<br>
<img src="images/konigs_1.png">
<br>

2. **Construct the Alternating Forest ( (left)--unmatching_edge--(right)--matching_edge--(left)--unmatching_edge--(right)--..**:
   - Start with all unmatched vertices in the **Left** set of the bipartite graph. For example in the graph below, **A1** is not an endpoint of a matching edge.
   <br>
   <img src="images/konigs_1.png">
   <br>
   
   - Perform a BFS or DFS to explore alternating paths starting from the unmatched vertices in **Left**. Alternate between edges that are not part of the matching and edges that are part of the matching.
   - Mark all vertices visited during this exploration.
   - For the graph above, this traversing would look like:
   - (A1)-----(B1)**------**(A2)------(B2)**--------**(A3)

<br>

3. **Mark Vertices**:
   - After the BFS/DFS, mark all vertices in **Left** that are reachable starting from an unmatched vertex in **Left** via alternating paths (using unmatched---matched edges--unmatched edges.... exploration).
   - Also, mark all vertices in **Right** that are connected to the marked vertices in **Left** by a matching edge.
   <br>
   <img src="images/konigs_3.png">
   <br>

4. **Identify the Minimum Vertex Cover**:
   - The minimum vertex cover will consist of:
     - All unmarked vertices in **Left** (since they are not reachable by alternating paths).
     - All marked vertices in **Right** (since they are connected to unmarked vertices in **Left** by a matching edge).
   <br>
   <img src="images/konigs_4.png">
   <br>

5. **Output the Minimum Vertex Cover**:
   - The set of vertices identified in the previous step forms the minimum vertex cover.
   For the above graph, it is **V_c = {A4, A5, B1, B2}.**
















<br>
Also check this video : https://www.youtube.com/watch?v=K-g5AzHACWs
<br>













