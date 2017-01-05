#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
int main(){
	int n,v;
	int c[1000], f[1000];
	cin >> n >> v;
	for (int i = 1; i <= n; i++)
		cin >> c[i];
	memset(f, 0x7f, sizeof(f));
	for (int i = 1; i <= n; i++)
		f[c[i]] = 1;

	for (int i = 1; i <= v; i++){
		if (f[i] != 1){
			for (int j = 1; j <= n; j++){
				if(i > c[j] && j!= c[i]){
					if(f[i]>=f[i-c[j]]){
						f[i]=f[i-c[j]];
						c[j]=100000;
					}
					// else
				}
			}
			f[i]++;

		}
	}	
	for (int i = 0; i <= v; i++)
		cout <<"i= "<<i<<"  "<< f[i] << endl;
	return 0;
}
