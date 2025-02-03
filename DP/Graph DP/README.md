# DP on Graph 

[![Graph DP Badge](https://img.shields.io/badge/Graph-Dynamic%20Programming-yellow?style=for-the-badge&logo=appveyor&logoColor=white)](https://shields.io/)  

<br>

At the beginner level, most DP on graph problems involve **directed graphs**. A directed graph enforces a one-way flow, much like DP, where the current state is derived from previously computed overlapping subproblems. (In the case of DP on trees, this one-way flow naturally exists from root to leaf, even if the tree is undirected).  

In contrast, **undirected graphs** introduce cycles due to bidirectional edges, creating looping structures that require additional handling for DP calculations, such as computing minimum/maximum values along paths or counting paths.  

Since most of the beginner problems I have solved focus on directed graphs, this README will cover DP on directed graphs.

<br>

# DP on Directed Graph

