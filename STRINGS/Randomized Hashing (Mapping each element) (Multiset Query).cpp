
// https://atcoder.jp/contests/abc367/tasks/abc367_f


// randomized hashing

// Our goal is to determine whether two multisets contains same elements

// Using randomized hashing : numbers elements sum differs for different set.


// Its a probabilisitc solution

const int Mod = (1LL << 61) - 1;

const int N = 2e5+10;
int H1[N];
int H2[N];


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,q;
        cin>>n>>q;

        vector<int>v1,v2;
        
        for(int i=0;i<n;i++)
        {
                int a;
                cin>>a;
                v1.push_back(a);
        }

        for(int i=0;i<n;i++)
        {
                int a;
                cin>>a;
                v2.push_back(a);
        }

        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        
        vector<int> Hash(N);

        for (int i = 0; i < N; i++) 
        {
                Hash[i] = uniform_int_distribution<int>(1, Mod-1)(rng);

        }

        for(int i=0;i<n;i++)
        {
                H1[i+1] = (H1[i]+Hash[v1[i]])%Mod;   // 1 based

                H2[i+1] = (H2[i]+Hash[v2[i]])%Mod;
        }


        while(q--)
        {
                int l1,r1,l2,r2;
                cin>>l1>>r1>>l2>>r2;

                int take1 = (H1[r1] - H1[l1-1] + Mod)%Mod;

                int take2 = (H2[r2] - H2[l2-1] + Mod)%Mod;


                if(take1 == take2)
                {
                        cout<<"Yes"<<endl;
                }
                else 
                {
                        cout<<"No"<<endl;
                }
        }





}
