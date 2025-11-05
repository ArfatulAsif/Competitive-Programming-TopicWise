
// KMP Algorithm : the motto is,
// Longest suffix that ends at i, which is also a prefix

vector<int>prefix_function(string &s)
{
        int n = s.size();
        vector<int>phi(n);

        for(int i=1;i<n;i++)
        {
                int j = phi[i-1];
                
                while(j > 0 && s[j] != s[i])
                {
                        j = phi[j-1];
                }

                if(s[i] == s[j])
                {
                        j++;
                }

                phi[i] = j;
        }
        return phi;
}











// UVA 455 - Periodic Strings
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=396

============  Solve with KMP ========


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
#define int long long int
#define ordered_set tree< int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>
      



// KMP Algorithm : the motto is,
// Longest suffix that ends at i, which is also a prefix

vector<int>prefix_function(string &s)
{
        int n = s.size();
        vector<int>phi(n);

        for(int i=1;i<n;i++)
        {
                int j = phi[i-1];
                
                while(j > 0 && s[j] != s[i])
                {
                        j = phi[j-1];
                }

                if(s[i] == s[j])
                {
                        j++;
                }

                phi[i] = j;
        }
        return phi;
}



int32_t main()  
{
        ios::sync_with_stdio(0);
        cin.tie(0);



        int t;
        cin>>t;

        for(int tt=1;tt<=t;tt++)
        {
                string s;
                cin>>s;

                vector<int>phi = prefix_function(s);

                int n = s.size();

                int repeat_start = n - phi[n-1];


                if(n%repeat_start == 0)
                {
                        cout<<repeat_start<<endl;
                }
                else 
                {
                        cout<<n<<endl;
                }


                if(tt!=t)
                {
                        cout<<endl;
                }

                



        }



}




