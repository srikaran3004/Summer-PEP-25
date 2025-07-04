#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int>s(n),e(n);
    for(int i=0;i<n;i++){
        cin>>s[i]>>e[i];
    }
    sort(s.begin(),s.end());
    sort(e.begin(),e.end());
    int pcnt=0,ans=0,x=0,y=0;
    while(x<n){
        if(s[x]<e[y]){
            pcnt++;
            ans=max(ans,pcnt);
            x++;
        }else{
            pcnt--;
            y++;
        }
    }
    cout<<ans<<endl;
}