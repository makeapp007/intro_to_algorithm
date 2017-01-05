#include <iostream>

#include <fstream>
#include <math.h> 
using namespace std;
int im[1000][1000];
int tmp[1000][1000];
int seam[1000];
FILE* stream;


int main()
{
	stream = fopen("data.txt","r");
	int h,w;
	int element;
	fscanf(stream,"%d",&h);  /*格式化*/
	fscanf(stream,"%d",&w);

	cout<<w<<" "<<h<<endl;
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			fscanf(stream,"%d",&element);
			im[i][j]=element;
		}
	}
	// for(int i=0;i<10;i++){
	// 	for(int j=0;j<10;j++){
	// 		// fscanf(stream,"%d",&w);
	// 		cout<<im[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
	ofstream outfile;
	outfile.open("data_seam.txt");



	int totround=w/2;
	for(int round=0;round<1;round++){

		// calculating gradient
		for(int i=1;i<h-1;i++){
			for(int j=1;j<w-1;j++){
				tmp[i][j]=int(sqrt((im[i][j+1]-im[i][j-1])*(im[i][j+1]-im[i][j-1])+(im[i+1][j]-im[i-1][j])*(im[i+1][j]-im[i-1][j])));
			}
		}

		// calculate energy
		int tmp1,tmp2,tmp3;
		for(int i=2;i<h-1;i++){
			for(int j=2;j<w-2;j++){
				tmp1=tmp[i-1][j-1];
				tmp2=tmp[i-1][j];
				tmp3=tmp[i-1][j+1];
				tmp[i][j]=min(min(tmp1,tmp2),tmp3)+im[i][j];
			}
		}

		// for(int i=0;i<100;i++){
		// 	for(int j=0;j<100;j++){
		// 		cout<<tmp[i][j]<<" ";
		// 	}
		// 	cout<<endl;
		// }

		// cout<<tmp[h-2][w-2]<<endl;

		// find min in last row
		int min=10000,min_index=0;	
		for(int j=1;j<w-1;j++){
			if(min>=tmp[h-2][j]){
				min=tmp[h-2][j];
				min_index=j;
			}
		}
		seam[h-2]=min_index;
		cout<<"min_index  "<<min_index<<endl;
		// trace back to find the seam
		for(int i=h-3;i>0;i--){
			if(min_index>w-1 && min_index<=0) min_index=w-2;
			else if(min_index<=0) min_index=1;
		
			tmp1=tmp[i][min_index-1];
			tmp2=tmp[i][min_index];
			tmp3=tmp[i][min_index+1];
			if(tmp3>=tmp1 && tmp2>=tmp1) seam[i]=min_index-1;
			else if(tmp1>=tmp2&& tmp3>=tmp2) seam[i]=min_index;
			else if(tmp2>=tmp3&& tmp1>=tmp3) seam[i]=min_index+1;
			min_index=seam[i];
		}

		// for(int i=0;i<h;i++){
		// 	cout<<seam[i]<<" ";
		// }
		// cut the seam in the image
		for(int i=1;i<h-1;i++){
			for(int j=seam[i];j<w-1;j++){
				im[i][j]=im[i][j+1];
			}
		}
		// cout<<"image"<<endl;
		// for(int i=1;i<h-1;i++){
		// 	for(int j=seam[i];j<w-1;j++){
		// 		im[i][j]=im[i][j+1];
		// 	}
		// }

		w--;
		// cout<<w<<endl;
	}

	cout<<w<<endl;
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			outfile << im[i][j]<< " ";
		}
		outfile<<endl;
	}



	outfile.close();



}



