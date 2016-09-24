#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>  
using namespace std;

int c[8];
int n=8;
int counter=0;
bool check(int cur){
        for(int j=0;j<cur;j++){
                if(c[j]==c[cur]||abs(j-cur)==abs(c[j]-c[cur])){
                        return false;
                }
        }
        return true;
}
void search(int cur){
        if(cur==n){
                counter++;
                for(int j=0;j<n;j++){
                        cout<<c[j]<<" ";
                }
                cout<<endl;
                return;
        }
        // cout<<"-----";
        for(int i=0;i<n;i++){
                c[cur]=i;
                if(check(cur)){
                        search(cur+1);
                }
        }

}

int main(){
        // memset(c,0,n);
        // printf("%d\n",n );

        for(int i=0;i<n;i++){
                c[i]=0;
        }
        search(0);
        cout<<counter;

        return 0;
}






