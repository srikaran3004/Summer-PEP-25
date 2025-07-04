#include<iostream>
using namespace std;
int main(){
    int a,b; cin>>a>>b;
    int temp;
    while(b!=0){
        temp=b;
        b=a%b;
        a=temp;
    }
    cout<<a;
}