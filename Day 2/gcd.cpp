#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b; cin>>a>>b;
    int mx=1;
    for(int i=1;i<=min(a,b);i++){
        if(a%i==0 && b%i==0){
            mx=i;
        }
    }
    cout<<mx;
}