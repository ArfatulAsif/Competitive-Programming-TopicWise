
// For weighted Maximum Bipartite Matching We use Minimum Cost Maximum Flow code.
// Complexity is O(min(E^2 *V log V, E logV * flow)), sometimes number of edges |E| can be large, but flow can be small, so this still applies



// Our target can be Minimum Weighted Maximum Bipartite Matching or Maximum Weighted Maximum Bipartite Matching.
// This code is for Minimum Weighted Maximum Bipartite Matching.

// To adjust it for Maximum Weighted Maximum Bipartite Matching,  take cost as -cost. And answer is -mcmf.MinimumCostMaximumFlow(source,sink,target_flow).second

const int N = 1000;

struct MCMF
{

	struct edge
	{
		int v; 			// to
		int rev; 		//Reverse edge index in graph[v]
		int residual_capacity;  // Residual capacity of the edge
		int cost;               // Cost per unit of flow through the edge
		int edge_id;            // Edge ID (optional, if needed)
	};

	vector<edge>graph[N];

	int n;
	int source, sink;

	vector<int> dist;
	vector<int>h; // potential array

	vector<pair<int,int>> parent; //  parent[v] = {u, rev} = {parent node u, parent node u's index in graph[v]}


	MCMF(int _n)
	{
		n = _n+1;
	}

	// This is for directed, for undirected make sure to include edges in both direction  addEdge(u,v) and addEdge(v,u).
	void addEdge(int u, int v, int capacity, int cost, int id = -1)
	{
		graph[u].push_back({v, (int)graph[v].size(), capacity, cost, id});
		graph[v].push_back({u, (int)graph[u].size()-1, 0, -cost, -id});
	}


	bool BellmanFord()
	{
		dist.assign(n, inf);
		dist[source] = 0;
		vector<pair<int,edge>>AllEdges; // {u, edge(v,rev, residual_capacity, cost, id)}

		for(int i=0;i<n;i++)  // vertex,  i < n because we already increased n by 1.
		{
			for(auto &e: graph[i])
			{
				AllEdges.push_back({i, e}); 
			}
		}

		bool flag = true;

		for(int i=0;i<n-1; i++) // number of vertices, for zero based graph, i < n
		{
			flag = false;

			for(auto &e: AllEdges)
			{
				int u = e.first;
				auto &[v, rev, residual_capacity, cost, id] = e.second;

				if(dist[v] > dist[u]+cost && residual_capacity>0)
				{
					dist[v] = dist[u]+cost;
					flag = true;
				}

			}

			if(flag == false)
			{
				break;
			}
		}

		for(auto &e: AllEdges)
		{
			int u = e.first;
			auto &[v, rev, residual_capacity, cost, id] = e.second;

			if(dist[v] > dist[u]+cost && residual_capacity>0)
			{
				dist[v] = dist[u]+cost;

				return false; // neg cycle exists
			}

		}

		for(int i=0;i<n;i++)
		{
			if(dist[i] < inf)
			{
				h[i] = dist[i]; // taking the initial potential function
			}
		}


		return dist[sink] != inf; // reachable
	}

	// Use Dijkstra to find minimum cost augmenting path
	bool Dijkstra()
	{
		parent.assign(n, {-1,-1});
		dist.assign(n, inf);

		priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

		dist[source] = 0;

		pq.push({0, source});

		while(!pq.empty())
		{
			int u = pq.top().second;
			int u_cost = pq.top().first;  // cost of 1 unit of flow from source to u
			pq.pop();

			if(u_cost != dist[u])
			{
				continue;
			}

			for(auto &[v, rev, residual_capacity, cost, id]: graph[u])
			{
				int adjusted_weight = cost + h[u] - h[v];  // this is always non_negative, even if h[u] or h[v] is negative.

				if(dist[v] > dist[u]+adjusted_weight && residual_capacity > 0)
				{
					dist[v] = dist[u]+adjusted_weight;
					parent[v] = {u, rev}; // {u, position of u in graph[v]}
					pq.push({dist[v], v});
				}
			}
		}

		for(int i=0;i<n;i++)
		{
			if(dist[i] < inf)
			{
				dist[i] += h[i]-h[source]; // retriving the true distance = dijkstra[u,v] + h[v] - h[u]
			}
		}

		for(int i=0;i<n;i++)
		{
			if(dist[i] < inf)
			{
				h[i] = dist[i]; // setting new potential value, as after using each augmenting path, some edges residual_capacity could becomes 0, and we might not be able to use these
				// that's why we need new potential values
			}
		}

		return dist[sink] != inf; // sink is reachable, which means in this iteration augmenting path is found. Not reachable means no more augmenting path remains.
	}

	// Solve the Min-Cost Max-Flow problem
	pair<int,int> MinimumCostMaximumFlow(int _source, int _sink, int target_flow = inf)
	{
		source = _source;
		sink = _sink;

		int total_flow_sent = 0;
		int total_cost = 0;

		h.assign(n, 0);

		if(!BellmanFord())  // using bellman-Ford for adjusting weight to accomodate negative neg weight edges
		{
			return {inf,inf}; // Either sink is not reachable or negative cycle exists
		}

		while( total_flow_sent < target_flow)
		{
			if(!Dijkstra()) // Use Dijkstra to find shortest augmenting path
			{
				// If no augmenting pathfound
				break;
			}


	                int v = sink;
	                int augmenting_path_flow = inf;
	                int cost_per_unit_of_flow_from_source_to_sink = dist[sink];
	 	         
	                while(v != source)
	                {
	                	int u = parent[v].first;
	                	int rev = parent[v].second;	

	                	int idx_of_v_in_u = graph[v][rev].rev;

	                	int residual_capacity = graph[u][idx_of_v_in_u].residual_capacity;
	                	
	                	augmenting_path_flow = min(augmenting_path_flow, residual_capacity);
	 
	                        v = parent[v].first;
	                        
	                }
	                            
	 	                	 
	 		//adjust the residual capacity 

	                v = sink;	                
	                while(v != source)
	                {
	                	int u = parent[v].first;
	                	int rev = parent[v].second;	

	                	int idx_of_v_in_u = graph[v][rev].rev;

	                	graph[u][idx_of_v_in_u].residual_capacity -= augmenting_path_flow;
	                	graph[v][rev].residual_capacity += augmenting_path_flow;

	                        v = parent[v].first;
	                        
	                }


	                if(total_flow_sent + augmenting_path_flow >= target_flow)
	                {
	                        int take = target_flow - total_flow_sent;
	                        total_cost += (take*cost_per_unit_of_flow_from_source_to_sink);
	                        total_flow_sent = target_flow;
	                        break;
	                }
	                else 
	                {
	                        total_flow_sent += augmenting_path_flow;

	                        total_cost += (augmenting_path_flow*cost_per_unit_of_flow_from_source_to_sink);
	                }

		}


		if(total_flow_sent < target_flow)
		{
			return {inf, inf};
		}


		return {total_flow_sent, total_cost};
	}

};



vector<pair<int,int>> FindBipartiteMatching(int left_size, int right_side, MCMF &mcmf)
{
	vector<pair<int,int>>matching;
	for(int u=1;u<=left_size;u++)
	{
		for(auto &[v, rev, residual_capacity, cost, id]: mcmf.graph[u])
		{
			if(residual_capacity == 0 && v > left_size)
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

        int n;
        cin>>n;
        
        int left_size, right_side;
        left_size = right_side = n; // for this problem

        MCMF mcmf(left_size+right_side+2);

        for(int i=1;i<=n;i++)
        {
        	for(int j=1;j<=n;j++)
        	{
        		int cost;
        		cin>>cost;

        		mcmf.addEdge(i, j + left_size, 1, cost);
        	}
        }

        int source = 0;
        int sink = left_size+right_side+1;

        for(int i=1;i<=left_size;i++)
        {
        	mcmf.addEdge(source, i, 1, 0);
        }

        for(int i=left_size+1;i<=left_size+right_side;i++)
        {
        	mcmf.addEdge(i, sink , 1 , 0);
        }


        cout<<mcmf.MinimumCostMaximumFlow(source,sink,n).second<<endl; // target_flow = n for this problem

        vector<pair<int,int>>matching = FindBipartiteMatching(left_size,right_side, mcmf);

        for (auto x : matching)
        {
        	cout<<x.first<<" "<<x.second<<endl;
        }
        

}
// https://cses.fi/problemset/task/2129/
