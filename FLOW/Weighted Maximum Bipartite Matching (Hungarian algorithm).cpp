
/* Hungarian Algorithm:
   - Complexity: O(V^3), optimized for both minimum and maximum cost maximum matching.
   - Minimum Cost Maximum Matching: Uses original costs.
   - Maximum Cost Maximum Matching: Negates the costs and returns the negated result. [ add_edge(u, v, -cost) and cout<<(-M.MaximumBipartiteMatching())<<endl]
   - Works for 1-indexed input. Both left and right is 1 based, no need to do v += left_size */


const int N = 509;

struct Hungarian 
{
        int c[N][N], fx[N], fy[N], d[N];
        int l[N], r[N], arg[N], trace[N];
        queue<int> q;
        int start, finish, n;

        Hungarian() {}

        Hungarian(int n1, int n2): n(max(n1, n2)) 
        {
                for (int i = 1; i <= n; ++i) 
                {
                        fy[i] = l[i] = r[i] = 0;
                        for (int j = 1; j <= n; ++j) 
                        {
                                c[i][j] = inf; // Set to 0 for maximum cost matching
                        }
                }
        }

        void add_edge(int u, int v, int cost) 
        {
                c[u][v] = min(c[u][v], cost);
        }

        inline int getC(int u, int v) 
        {
                return c[u][v] - fx[u] - fy[v];
        }

        void initBFS() 
        {
                while (!q.empty()) q.pop();
                q.push(start);
                
                for (int i = 0; i <= n; ++i) trace[i] = 0;
                
                for (int v = 1; v <= n; ++v) 
                {
                        d[v] = getC(start, v);
                        arg[v] = start;
                }
                finish = 0;
        }

        void findAugPath() 
        {
                while (!q.empty()) 
                {
                        int u = q.front();
                        q.pop();
                        for (int v = 1; v <= n; ++v) 
                        {
                                if (!trace[v])
                                {
                                        int w = getC(u, v);
                                        if (!w) 
                                        {
                                                trace[v] = u;
                                                if (!r[v]) 
                                                {
                                                        finish = v;
                                                        return;
                                                }
                                                q.push(r[v]);
                                        }
                                        if (d[v] > w) 
                                        {
                                                d[v] = w;
                                                arg[v] = u;
                                        }
                                }
                        }
                }
        }

        void subX_addY() 
        {
                int delta = inf;
                for (int v = 1; v <= n; ++v) 
                {
                        if (!trace[v] && d[v] < delta) 
                        {
                                delta = d[v];
                        }
                }

                fx[start] += delta;

                for (int v = 1; v <= n; ++v) 
                {
                        if (trace[v]) 
                        {
                                int u = r[v];
                                fy[v] -= delta;
                                fx[u] += delta;
                        } 
                        else 
                        {
                                d[v] -= delta;
                        }
                }
                for (int v = 1; v <= n; ++v) 
                {
                        if (!trace[v] && !d[v]) 
                        {
                                trace[v] = arg[v];
                                if (!r[v]) 
                                {
                                        finish = v;
                                        return;
                                }
                                q.push(r[v]);
                        }
                }
        }

        void Enlarge() 
        {
                do {
                        int u = trace[finish];
                        int next = l[u];
                        l[u] = finish;
                        r[finish] = u;
                        finish = next;
                } while (finish);
        }

        int MaximumBipartiteMatching() 
        {
                for (int u = 1; u <= n; ++u) 
                {
                        fx[u] = c[u][1];
                        for (int v = 1; v <= n; ++v) 
                        {
                                fx[u] = min(fx[u], c[u][v]);
                        }
                }
                for (int v = 1; v <= n; ++v) 
                {
                        fy[v] = c[1][v] - fx[1];

                        for (int u = 1; u <= n; ++u) 
                        {
                                fy[v] = min(fy[v], c[u][v] - fx[u]);
                        }
                }
                for (int u = 1; u <= n; ++u) 
                {
                        start = u;
                        initBFS();
                        while (!finish) 
                        {
                                findAugPath();
                                if (!finish) subX_addY();
                        }
                        Enlarge();
                }
                int ans = 0;
                for (int i = 1; i <= n; ++i) 
                {
                        if (c[i][l[i]] != inf) ans += c[i][l[i]];
                        else l[i] = 0;
                }
                return ans;
        }


        vector<pair<int,int>>  FindBipartiteMatching(int left_size, int right_size)
        {
        	vector<pair<int,int>>matching;
        	for(int i=1;i<=left_size;i++)
        	{
        		if(l[i] != 0) // l[i] = left i, is connected to l[i] in right
        		{
        			matching.push_back({i, l[i]});
        		}
        	}

        	return matching;
        }
};



int32_t main() 
{
        ios_base::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;

        int left_size, right_size;

        left_size = right_size = n; // for this problem

        Hungarian M(left_size, right_size);

        for(int i=1;i<=n;i++)
        {
        	for(int j=1;j<=n;j++)
        	{
        		int cost;
        		cin>>cost;
        		M.add_edge(i,j,cost); // for Maximum Matching M.add_edge(i,j,-cost)
        	}
        }

        cout<<M.MaximumBipartiteMatching()<<endl;


        vector<pair<int,int>>matching = M.FindBipartiteMatching(left_size,right_size);


        for(auto x : matching)
        {
        	cout<<x.first<<" "<<x.second<<endl;
        }

        return 0;


}

// https://cses.fi/problemset/task/2129/
