#include<bits/stdc++.h>
using namespace std;

bool compare(string a,string b){
    return a+b>b+a;
}

int main(){
    int n; cin>>n;
    vector<string>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    sort(a.begin(),a.end(),compare);
    if(a[0]=="0") cout<<"0";
    string res="";
    for(string s:a){
        res+=s;
    }
    cout<<res<<endl;
}

//Josh technology question