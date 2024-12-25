
# Vertex Cover:
<br>

**A vertex cover in a graph is a set of vertices that includes at least one endpoint of every edge.**

<img src="images/vertex_cover1.png">

In the given graph, consider the vertex set **V_c = {1, 2, 3, 4}**. This set qualifies as a vertex cover because every edge in the graph has at least one endpoint within **V_c**. 
<br>

<img src="images/vertex_cover3_1234.png">

<br>

Similarly, the sets **V_c = \{1, 2, 3, 5\}**, **V_c = \{2, 3, 5\}** and **V_c = \{1, 2, 3, 4, 5\}** also serve as valid vertex covers.
<br>

<img src="images/vertex_cover3_1235.png"> <img src="images/vertex_cover3_235.png">

<br>

But **V_c = \{1, 2, 5\}** is **not** a vertex cover, because as we can see below, there is an edge which is not covered.
<br>
<img src="images/vertex_cover2.png">

<br> 

**Finding any vertex cover set is a simple task because the set of all vertices always serves as a vertex cover surely. However, the real challenge lies in finding the minimum vertex cover.**

## Minimum Vertex Cover:
<br>

**A vertex cover is minimum if no other vertex cover has fewer vertices. Number of vertices in the minimum vertex cover set is lowest among all the vertex cover sets**

<br>

For example in the graph, **V_c = \{2, 3, 5\}** is a minimum vertex cover.

<img src="images/vertex_cover3_235.png">

<br>


---









