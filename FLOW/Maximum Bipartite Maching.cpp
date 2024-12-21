// Matching: In a Graph G, Matching is the task of selecting a set of edges, such that no two edges have same end points(vertices).

// Bipartite Matching: Selecting a set of edges in a bipartite graph, such that no two edges have same end points.
// Maximum Bipartite Matching = The maximum possible number of edges that can exists in a bipartite matching.

// This can be solved using max flow algorithms.


============================= Maximum Bipartite Matching Using Dinics Algorithms ====================

// This will give TLE 
// Just for understanding, not for uses
// I personally understand this code
  
const int N = 1000;

struct edge
{
	int v;                  // to
	int rev;                // Reverse edge index in graph[v]
	int residual_capacity;  // Residual capacity of the edge
	int edge_id;            // Edge ID (optional, if needed)
};

vector<edge> graph[N];
int level[N];
int done[N]; //  done[u] array is to keep track of which edges have already been tried for a given node during a DFS call. This ensures that we don't revisit the same edges unnecessarily and speeds up the process.


// This is for directed, for undirected make sure to include edges in both direction  addEdge(u,v,c) and addEdge(v,u,c).
void addEdge(int u, int v, int capacity, int id = -1)
{
	graph[u].push_back({v, (int)graph[v].size(), capacity, id});
	graph[v].push_back({u, (int)graph[u].size()-1, 0, -id});
}


// BFS to build Level Graph
bool bfs(int source, int sink)
{
	fill(level, level+N, -1);
	level[source] = 0;
	queue<int>q;
	q.push(source);

	while(!q.empty())
	{
		int u = q.front();
		q.pop();

		for(auto &[v, rev, residual_capacity, id]: graph[u])
		{
			if(level[v] != -1 || residual_capacity == 0)
			{
				continue;
			}

			level[v] = level[u] + 1;
			q.push(v);
		}
	}

	return level[sink] != -1;  // sink is reachable = true
}



// DFS to send flow along augmenting paths
int dfs(int u, int sink, int flow)
{
	if(u == sink)
	{
		return flow;
	}

	for(; done[u] < graph[u].size(); done[u]++)
	{
		auto &[v, rev, residual_capacity, id] = graph[u][done[u]];

		if(level[v] == level[u]+1 && residual_capacity > 0) // only traversing trough level graph
		{
			int pathFlow = min(flow, residual_capacity);
			int pushedFlow = dfs(v, sink, pathFlow);

			if(pushedFlow > 0)
			{
				residual_capacity -= pushedFlow;
				graph[v][rev].residual_capacity += pushedFlow;

				return pushedFlow;
			}
		}
	}

	return 0;
}


int Dinic(int source, int sink)
{
	int max_flow = 0;

	while(bfs(source, sink)) // build the level graph
	{
		fill(done, done+N, 0);

		while(true)  // traverse on the same level graph multiple time, which is efficiant than Edmonds-Karp. As we are blocking multiple edges(residual_capacity = 0) using the same level graph.
		{
			int flow = dfs(source, sink, inf);

			if(flow == 0)
			{
				break;
			}

			max_flow += flow;
		}

	}

	return max_flow;
}


vector<pair<int,int>> FindBipartiteMatching(int left_size)
{
	vector<pair<int,int>>matching;

	for(int u = 1; u<= left_size; u++)
	{
		for(auto &[v, rev, residual_capacity, id]: graph[u])
		{
			if(residual_capacity == 0 && v > left_size) // residual_capacity = 0 means this edge is in matching and v > left_size means v is in right side
			{
				int vv = v - left_size;
				matching.push_back({u,vv});
			}
		}
	}

	return matching;
}

      
int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int left_size, right_side, k;   // in a bipartite graph, we have seperated vertices into two sets left set and right set. Both set of vertices have 1 based indexing
                                        // If both set of vertices don't have 1 based indexing, we need to modify next lines as such [Easy Peasy]

        cin>>left_size>>right_side>>k;

        for(int i=0;i<k;i++)
        {
        	int u,v;
        	cin>>u>>v;

        	v += left_size; // to avoid overlap with left side vertices

        	addEdge(u,v,1);
        }


        int source = 0;
        int sink = left_size + right_side + 1;

        for(int i=1;i<=left_size;i++)
        {
        	addEdge(source, i, 1);
        }

        for(int i=left_size+1; i<= right_side+left_size; i++)
        {
        	addEdge(i, sink, 1);
        }



        cout<<Dinic(source, sink)<<endl; // maximum bipartite matching = max flow


        vector<pair<int,int>> matching = FindBipartiteMatching(left_size);

        for(auto x : matching)
        {
        	cout<<x.first<<" "<<x.second<<endl;
        }

}
https://cses.fi/problemset/task/1696/




















