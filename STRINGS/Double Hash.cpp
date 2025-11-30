

struct DoubleHash 
{
        int p1 = 131;

        int p2 = 137;


        int Mod1 = 1e9 + 7;

        int Mod2 = 1e9 + 9;

        vector<int> power1, power2;

        vector<int> inv1, inv2;

        vector<int> H1, H2;



        int binexp(int a, int b, int mod) 
        {
                int ans = 1;

                while (b > 0) 
                {
                        if( b & 1)
                        {
                                ans = (ans*a)%mod;
                        }

                        a = ( a * a) % mod;
                        
                        b >>= 1;
                }
                return ans;
        }


        int inverse_modulo(int a, int mod) 
        {

                return binexp(a,mod - 2, mod);
        }



        DoubleHash(string &s) 
        {
                int n = s.size();

                power1.resize(n+ 1,1);

                power2.resize(n +1,1);

                inv1.resize(n +1, 1);
                inv2.resize(n+ 1,1);

                H1.resize(n + 1, 0);

                H2.resize(n + 1,0);


                int inv_p1 = inverse_modulo(p1, Mod1);

                int inv_p2 = inverse_modulo(p2, Mod2);

                for (int i = 1; i <= n; i++) 
                {
                        power1[i] = (power1[i - 1] * p1)% Mod1;

                        power2[i] = (power2[i- 1] * p2)% Mod2;

                        inv1[i] = (inv1[i - 1] * inv_p1) % Mod1;

                        inv2[i] = (inv2[i -1] * inv_p2)% Mod2;
                }

                for (int i = 0; i < n; i++) 
                {
                        int val = (s[i] - 'a' + 1);

                        H1[i +1] = (H1[i] + val *power1[i]) % Mod1;

                        H2[i + 1] = (H2[i] + val * power2[i]) % Mod2;
                }
        }

        pair<int , int> sub_string_hash(int i , int j) 
        {
                int hash1 = (H1[j+ 1]- H1[i] + Mod1) % Mod1;

                hash1 = (hash1 *inv1[i]) % Mod1;

                int hash2 = (H2[j+ 1] - H2[i] + Mod2) % Mod2;

                hash2 = (hash2 * inv2[i]) % Mod2;

                return {hash1, hash2};
        }


};














================= Double Hash + Segment Tree   (single character change update) (palindrome check)  ================


// https://cses.fi/problemset/task/2420





struct DoubleHash 
{
        int p1 = 131;

        int p2 = 137;


        int Mod1 = 1e9 + 7;

        int Mod2 = 1e9 + 9;

        vector<int> power1, power2;

        vector<int> inv1, inv2;

        vector<int> H1, H2;

        
        int n;

        vector<int>Tree1;
        vector<int>Tree2;



        int binexp(int a, int b, int mod) 
        {
                int ans = 1;

                while (b > 0) 
                {
                        if( b & 1)
                        {
                                ans = (ans*a)%mod;
                        }

                        a = ( a * a) % mod;
                        
                        b >>= 1;
                }
                return ans;
        }


        int inverse_modulo(int a, int mod) 
        {

                return binexp(a,mod - 2, mod);
        }

        void update(int node, int lo, int hi, int pos, int val1, int val2)
        {
                if(lo==hi)
                {
                        Tree1[node] = val1;
                        Tree2[node] = val2;
                        return;
                }

                int mid=(lo+hi)>>1;

                if(pos <= mid)
                {
                        update(node*2, lo, mid, pos, val1, val2);
                }
                else 
                {
                        update(node*2+1, mid+1, hi, pos, val1, val2);

                }

                Tree1[node] = (Tree1[node*2] + Tree1[node*2+1])%Mod1;

                Tree2[node] = (Tree2[node*2] + Tree2[node*2+1])%Mod2;
        }


        pair<int,int> query(int node, int lo, int hi, int i, int j)
        {
                if(lo > j || hi < i)
                {
                        return {0,0};
                }

                if(lo >= i && hi <= j)
                {
                        return {Tree1[node], Tree2[node]};
                }

                int mid = (lo+hi)>>1;

                pair<int,int>x = query(node*2, lo, mid, i, j);
                pair<int,int>y = query(node*2+1,mid+1, hi, i, j);

                return {(x.first+y.first)%Mod1, (x.second+y.second)%Mod2};
        }



        DoubleHash(string &s) 
        {
                n = s.size();

                power1.resize(n+ 1,1);

                power2.resize(n +1,1);

                inv1.resize(n +1, 1);
                inv2.resize(n+ 1,1);

                H1.resize(n + 1, 0);

                H2.resize(n + 1,0);

                Tree1.resize(4*n + 1, 0);
                Tree2.resize(4*n + 1, 0);


                int inv_p1 = inverse_modulo(p1, Mod1);

                int inv_p2 = inverse_modulo(p2, Mod2);

                for (int i = 1; i <= n; i++) 
                {
                        power1[i] = (power1[i - 1] * p1)% Mod1;

                        power2[i] = (power2[i- 1] * p2)% Mod2;

                        inv1[i] = (inv1[i - 1] * inv_p1) % Mod1;

                        inv2[i] = (inv2[i -1] * inv_p2)% Mod2;
                }

                for (int i = 0; i < n; i++) 
                {
                        int val = (s[i] - 'a' + 1);

                        H1[i +1] = (val *power1[i]) % Mod1;

                        H2[i + 1] = (val * power2[i]) % Mod2;

                        update(1,1,n, i+1, H1[i+1], H2[i+1]);
                
                }
        }


        void Update(int i, char c)
        {
                int val = (c -'a'+1);

                int h1 = (val*power1[i])%Mod1;
                int h2 = (val*power2[i])%Mod2;

                update(1,1,n,i+1,h1,h2);
        }



        pair<int , int> sub_string_hash(int i , int j) 
        {
                auto [hash1,hash2] = query(1,1,n,i+1,j+1);

                hash1 = (hash1 *inv1[i]) % Mod1;

                hash2 = (hash2 * inv2[i]) % Mod2;

                return {hash1, hash2};
        }


};



int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,q;
        cin>>n>>q;

        string s;
        cin>>s;

        DoubleHash H1(s);

        reverse(s.begin(), s.end());

        DoubleHash H2(s);


        while(q--)
        {
                int a;
                cin>>a;

                if(a == 1)
                {
                        int pos;
                        char c;

                        cin>>pos>>c;

                        pos--;

                        H1.Update(pos, c);

                        pos++;

                        pos = n-pos+1;

                        pos--;

                        H2.Update(pos,c);


                }


                else 
                {
                        int l,r;
                        cin>>l>>r;

                        int R = n-l+1;
                        int L = n-r+1;

                        l--;
                        r--;
                        R--;
                        L--;


                        if(H1.sub_string_hash(l,r) == H2.sub_string_hash(L,R))
                        {
                                cout<<"YES"<<endl;
                        }
                        else 
                        {
                                cout<<"NO"<<endl;
                        }
                }
        }













}













