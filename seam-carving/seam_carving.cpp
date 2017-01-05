#include <iostream>
#include <fstream>
#include <math.h> 
using namespace std;
// Readme
// I didnot use malloc since it is time consuming to use malloc to allocate and free while storing data on the stack is fast and enough.
// if the image is bigger than 1000*1000, for example, 2000*2000
// please set im, tmp, seam size to 2000*2000 correspondingly.
// Usage:
// input: data2.txt, storing pixel value.
// output: data_seam.txt, storing pixel which has been performed seam carving.

// record the source image
int im[1000][1000];
// record the energy
int tmp[1000][1000];
// recording the seam
int seam[1000];

FILE* stream;


int main()
{
	stream = fopen("data2.txt","r");
	int h,w;
	int element;


	if(stream==0){
		cout<<"ERROR, file does not exist"<<endl;
		return 0;
	}

	fscanf(stream,"%d",&h);
	fscanf(stream,"%d",&w);


	cout<<w<<" "<<h<<endl;
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			fscanf(stream,"%d",&element);
			im[i][j]=element;
		}
	}
	// for(int i=0;i<h;i++){
	// 	for(int j=0;j<w;j++){
	// 		cout<<im[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }

	ofstream outfile;
	outfile.open("data_seam.txt");

	int totround=w/2;
	for(int round=0;round<totround;round++){

		// calculating gradient
		for(int i=0;i<h;i++){
			for(int j=0;j<w;j++){
				// set the margin to a long number, at least long than 255
				if(i==0 || j==0 ||i==h-1 ||j==w-1) tmp[i][j]=100000;
				else{
					tmp[i][j]=int(sqrt((im[i][j+1]-im[i][j-1])*(im[i][j+1]-im[i][j-1])+(im[i+1][j]-im[i-1][j])*(im[i+1][j]-im[i-1][j])));
				}
			}
		}

		// calculate energy
		int tmp1,tmp2,tmp3;
		for(int i=2;i<h-1;i++){
			for(int j=1;j<w-1;j++){

				tmp1=tmp[i-1][j-1];
				tmp2=tmp[i-1][j];
				tmp3=tmp[i-1][j+1];
				tmp[i][j]=min(min(tmp1,tmp2),tmp3)+tmp[i][j];
			}
		}
		// cout<<endl;
		// 	for(int i=0;i<h;i++){
		// 		for(int j=0;j<w;j++){
		// 			cout<<tmp[i][j]<<" ";
		// 		}
		// 		cout<<endl;
		// 	}
		// cout<<tmp[h-2][w-2]<<endl;

		// find min in last row
		int min=10000,min_index=0;	
		for(int j=0;j<w;j++){
			if(min>tmp[h-2][j]){
				min=tmp[h-2][j];
				min_index=j;
			}
		}
		seam[h-2]=min_index;
		// cout<<"min_index  "<<min_index<<endl;
		// trace back to find the seam
		for(int i=h-3;i>1;i--){
			tmp1=tmp[i][min_index-1];
			tmp2=tmp[i][min_index];
			tmp3=tmp[i][min_index+1];
			if(tmp3>tmp1 && tmp2>tmp1) seam[i]=min_index-1;
			else if(tmp1>=tmp2&& tmp3>=tmp2) seam[i]=min_index;
			else if(tmp2>=tmp3&& tmp1>=tmp3) seam[i]=min_index+1;
			min_index=seam[i];
		}

		// for(int i=0;i<h;i++){
		// 	cout<<seam[i]<<" ";
		// }
		// cut the seam in the image
		for(int i=0;i<h;i++){
			int start=seam[i];
			for(int j=start;j<w;j++){
				im[i][j]=im[i][j+1];
			}
		}
		// cout<<endl;
		// for(int i=0;i<h;i++){
		// 	for(int j=0;j<w;j++){
		// 		// fscanf(stream,"%d",&w);
		// 		cout<<im[i][j]<<" ";
		// 	}
		// 	cout<<endl;
		// }


		w--;
		cout<<w<<endl;
	}

	// write im to file
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			outfile << im[i][j]<< " ";
		}
		outfile<<endl;
	}

	outfile.close();
	return 0;
}



