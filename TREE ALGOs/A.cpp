//Intermediary
//Young kid on the block
//AIAsif try's Continuing the journey
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
#define inf 1000000000000000000
//#define int long long int
#define ordered_set tree< int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>
     


const int N = 2e5+100;
vector<int>graph[N];
int level[N];




//LCA Part
const int L = log2(N);
int lca_din[N];
int lca_dout[N];
int up[N][L+1];
int tim_lca;





//SEGMENT Tree Part
int n; // to be taken input as no of vertex

int Tree[2*N] ;
int ara[N];
int tin[N]; 
int tout[N];
int vis_tim_vertex[N];
int nxt[N]; 
int subtree[N];
int tim;


void dfs(int s, int par)
{
        lca_din[s] = tim_lca++;

        up[s][0] = par;

        for(int i=1;i<=L;i++)
        {
                up[s][i] = up[up[s][i-1]][i-1];
        }

        for(auto child : graph[s])
        {
                if(child  == par)
                {
                        continue;
                }

                dfs(child, s);
        }

        lca_dout[s] = tim_lca;
}

bool is_ancestor(int u, int v)
{
        return (lca_din[u] <= lca_din[v] && lca_dout[u] >= lca_dout[v]);
}


int lca(int u, int v)
{
        if(is_ancestor(u,v))
        {
                return v;
        }

        if(is_ancestor(v,u))
        {
                return v;
        }

        for(int i=L;i>=0;i--)
        {
                if(!is_ancestor(up[u][i], v))
                {
                        u = up[u][i];
                }
        }

        u = up[u][0];

        return u;
}


void dfs1(int s, int par)
{
        subtree[s] = 1;

        for(auto &child: graph[s])
        {
                if(child == par)
                {
                        continue;
                }

                dfs1(child, s);

                subtree[s] += subtree[child];


                if(subtree[child] > subtree[graph[s][0]])
                {
                        swap(child, graph[s][0]);
                }
        }


}


void dfs_hld(int s, int par)
{
        tin[s] = ++tim;

        vis_tim_vertex[tim] = s;

        for(auto child : graph[s])
        {
                if(child == par)
                {
                        continue;
                }


                if(child == graph[s][0])
                {
                        nxt[child] = nxt[s];
                }
                else 
                {
                        nxt[child] = child;
                }

                dfs_hld(child, s);
        }

        tout[s] = tim;

}


// Iterative Segment Tree


void build()
{
        for(int i=1;i<=n;i++)
        {
                Tree[n+i-1] = ara[vis_tim_vertex[i]];
        }
        for(int i=n-1;i>=1;i--)
        {
                Tree[i] = max(Tree[i<<1], Tree[i<<1|1]);
        }
}




void update(int pos, int val)
{
        pos = pos + n - 1;
        Tree[pos] = val;
        for(pos >>= 1; pos >= 1; pos >>= 1)
        {
                Tree[pos] = max(Tree[pos<<1], Tree[pos<<1|1]);
        }
}



int query(int l, int r)
{
        int res = 0;
        l = l + n - 1;
        r = r + n - 1;
        while(l <= r)
        {
                if(l & 1) res = max(res, Tree[l++]);
                if(!(r & 1)) res = max(res, Tree[r--]);
                l >>= 1;
                r >>= 1;
        }
        return res;
}


void HLD()
{

        dfs(1,1);


        dfs1(1,1);


        dfs_hld(1,1);
}


int query_up(int l, int u)
{
        int res=0;

        while(nxt[u]!=nxt[l])
        {

                res = max(res, query(tin[nxt[u]],  tin[u]));

                u = up[nxt[u]][0];
        }

        res = max(res, query(tin[l], tin[u]));

        return res;
}


int maximum_query_hld(int u, int v)
{
        if(is_ancestor(u,v))
        {
                return query_up(u,v);
        }
        if(is_ancestor(v,u))
        {
                return query_up(v,u);
        }

        int l = lca(u,v);

        int x = query_up(l,u);
        int y = query_up(l,v);

        return max(x,y);
}


void update_up(int u,int x)
{

        update(tin[u], x);
}






int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int m;
        cin>>n>>m;

        for(int i=1;i<=n;i++)
        {
                cin>>ara[i];
        }

        for(int i=0;i<n-1;i++)
        {
                int x,y;
                cin>>x>>y;
                graph[x].push_back(y);
                graph[y].push_back(x);
        }

        HLD();

        build();

        while(m--)
        {
                int a;
                cin>>a;
                if(a == 1)
                {
                        int s,x;
                        cin>>s>>x;

                        update_up(s,x);
                }
                else 
                {
                        int a,b;
                        cin>>a>>b;
                        cout<<maximum_query_hld(a,b)<<" ";


                }
        

        }

        cout<<endl;



}
