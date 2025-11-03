

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

                        a = (a * a) % mod;
                        
                        b >>= 1;
                }
                return ans;
        }


        int inverse_modulo(int a, int mod) 
        {

                return binexp(a, mod - 2, mod);
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


