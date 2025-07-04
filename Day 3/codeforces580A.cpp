#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int>arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int maxLen=1;
    int ans=1;
    for(int i=1;i<n;i++){
        if(arr[i-1]<=arr[i]){
            maxLen++;
        }
        else{
            maxLen=1;
        }
        ans=max(ans,maxLen);
    }
    cout<<ans;
}