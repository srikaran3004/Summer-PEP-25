// https://cses.fi/problemset/task/1634
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

void solve()
{
	int n, sm;
	cin>>n>>sm;
	int v[n];
	int dp[sm+1];
	
	for(auto &c:v) cin>>c;
	
	dp[0]=0;
	for(int i=1;i<=sm;i++) dp[i] = 1e9;
	
	for(int i=1;i<=sm;i++)
		for(int j=0;j<n;j++)
			if(i-v[j]>=0)
				dp[i] = min(dp[i], dp[i-v[j]] +1);
	cout<<(dp[sm] == 1e9 ? -1 : dp[sm]);
}	
 
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL), cout.tie(NULL);
	//cout.setf(std::ios::fixed); cout.precision(9);
	
    solve();
    //int t; cin>>t; while(t--){solve();}
    return 0;
}