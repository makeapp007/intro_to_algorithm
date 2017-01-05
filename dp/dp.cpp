#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
int main(){
	int n;
	int c[1000][1000], f[1000][1000],v[100];
// c coin category
// f, value function
	n=5;
	v[1]=1;
	v[2]=6;
	v[3]=18;
	v[4]=22;
	v[5]=28;
	int weight=11;
	int w[10];
	w[1]=1;
	w[2]=2;
	w[3]=5;
	w[4]=6;
	w[5]=7;

	f[1][1]=1;
	f[2][3]=7;
	f[3][8]=25;
	f[4][14]=47;
	f[5][21]=75;

	memset(f, 0x00, sizeof(f));

	for (int i = 1; i <= n; i++){
		for(int j=1;j<=weight;j++){
			if (f[i][j] == 0){
				if(i-1>0 && j-w[i]>0 ){
					f[i][j] = max(f[i-1][j-w[i]]+v[i],f[i-1][j]);
				}
			}
		}
	}	
	for (int i = 0; i <= n; i++){
		for(int j=0;j<weight;j++){
			cout << f[i][j]<<"   ";
		}
		cout<<endl;
	}
	return 0;
}


