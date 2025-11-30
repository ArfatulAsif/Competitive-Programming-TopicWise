// https://cses.fi/problemset/task/3138/

struct Manacher 
{
        vector<int> man;
        int n;

        Manacher(const string& s) 
        {
                n = s.size();
                if (n == 0) return;

                int l = 0, r = -1;
                vector<int> d1(n);

                for (int i = 0; i < n; i++) 
                {
                        int k = i > r ? 1 : min(d1[l + r - i], r - i);
                        while (i + k < n && i - k >= 0 && s[i + k] == s[i - k]) 
                        {

                                k++;
                        }
                        
                        d1[i] = k--;

                        if (i + k > r)
                        {
                                l = i - k, r = i + k;
                        }
                }


                l = 0, r = -1;
                vector<int> d2(n);
                for (int i = 0; i < n; i++) 
                {
                        int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1); 

                        k++;
                        

                        while (i + k <= n && i - k >= 0 && s[i + k - 1] == s[i - k])
                        {
                                k++;
                        }

                        d2[i] = --k;


                        if (i + k - 1 > r) 
                        {
                                l = i - k;
                                r = i + k - 1;
                        }
                }

                
                man.resize(2 * n - 1);

                for (int i = 0; i < n; i++)
                {
                        man[2 * i] = 2 * d1[i] - 1;
                }
                for (int i = 0; i < n - 1; i++) 
                {
                        man[2 * i + 1] = 2 * d2[i + 1];
                }
        
        }

        // Check if substring s[i..j] is a palindrome
        bool isPalindrome(int i, int j) 
        {
                if (i > j)
                {
                         return true;
                }
                return man[i + j] >= j - i + 1;
        }

        // Returns vector where ret[i] is the length of the longest palindrome
        // ending at index i.
        vector<int> getEndingLengths() 
        {
                if (n == 0) return {};
                
                vector<int> ret(n);

                ret[0] = 1;
                for (int i = 1; i < n; i++) 
                {
                        ret[i] = min(ret[i - 1] + 2, i + 1);

                        while (!isPalindrome(i - ret[i] + 1, i))
                        {
                                ret[i]--;
                        }
                }
                return ret;
        }
};



int32_t main() 
{
        string s;
        cin>>s;
        
        Manacher m(s);

        vector<int> lengths = m.getEndingLengths();

        for(int i=0;i<s.size();i++)
        {
                cout<<lengths[i]<<" ";
        }

        cout<<endl;
        

        return 0;
}
