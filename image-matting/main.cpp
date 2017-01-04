#include <iostream>  
#include <queue>  
#include <vector>  
#include <cmath>  
#include <stdio.h>  
#include <fstream>
#include "graph.h"

using namespace std;  
FILE* stream;
FILE* stream1;


// is the default value zero??
// store output degree
// struct Edge{
//     // constructor
//     Edge():up(0),down(0),left(0),right(0),above(0),below(0){}
//     int up;
//     int down;
//     int left;
//     int right;
//     int above;
//     int below;
// };

int main(){
	stream = fopen("source.txt","r");
	stream1 = fopen("priori.txt","r");
	int h,w;
	int unuse;
	// int *im=new int[h][w];
	fscanf(stream1,"%d",&unuse);
	fscanf(stream1,"%d",&unuse);
	fscanf(stream,"%d",&h);
	fscanf(stream,"%d",&w);
	cout<<"Building the graph"<<endl;
	cout<<"picture size: "<<h<<"*"<<w<<endl;
	build_rGraph(stream,stream1,h,w);
	cout<<"running mincut maxflow algorithm"<<endl;
    cout << "The maximum possible flow is " << fordFulkerson(h,w);



	// ofstream outfile;

	// outfile.open("nlinks.txt");
	// for(int i=0;i<h;i++){
	// 	for(int j=0;j<w;j++){
	// 		for(int k=0;k<6;k++){
	// 			outfile << nlinks[i][j][k]<< " ";
	// 		}	
	// 	}
	// 	outfile<<endl;
	// }
	// outfile.close();






	// cout<<w<<" "<<h<<endl;
	// for(int i=0;i<h;i++){
	// 	for(int j=0;j<w;j++){
	// 		fscanf(stream,"%d",&element);
	// 		im[i][j]=element;
	// 	}
	// }




	return 0;
}