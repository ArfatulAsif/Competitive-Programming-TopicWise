
// https://cses.fi/problemset/task/1111


// Longest palindromic substring

vector<int> manacher_odd(string s) 
{
        int n = s.size();

        s = "$" + s + "^";

        vector<int> p(n + 2);

        int l = 0, r = 1;

        for(int i = 1; i <= n; i++) 
        {
                p[i] = min(r - i, p[l + (r - i)]);

                while(s[i - p[i]] == s[i + p[i]]) 
                {
                        p[i]++;
                }
                if(i + p[i] > r) 
                {
                        l = i - p[i], r = i + p[i];
                }
        }
        return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) 
{
        string t;
        for(auto c: s) 
        {
                t += string("#") + c;
        }
            
        auto res = manacher_odd(t + "#");

        return vector<int>(begin(res) + 1, end(res) - 1);


}



// p[i] = radious of the palindromic substring centered at i.


pair<int, int> longest_palindrome_indices(string &s)
{

        vector<int>p = manacher(s);
        int n = p.size();
        int center = 0, radius = 0;

        for(int i=0;i<n;i++)
        {
                if(p[i] > radius)
                {
                        radius = p[i];
                        center = i;
                }
        }

        int start = (center - radius) / 2;
        int end = start+radius-1;

        return {start+1, end};


}






int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        string s;
        cin>>s;

        auto x = longest_palindrome_indices(s);

        cout<<s.substr(x.first, x.second-x.first+1)<<endl;



}
