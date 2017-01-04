using namespace std;  

#include <limits.h>
#include <string.h>

#include <iostream>  
#include <queue>  
#include <vector>  
#include <cmath>  
#include <stdio.h>  
#include <fstream>


int nlinks[620][800][6];
int s[620*800];
int t[620*800];
#define e 2.71828
#define r_lambda 3
#define PI 3.14159
#define K 10000000
#define V (620*800)

int build_rGraph(FILE * stream,FILE * stream1,int h, int w){
    if(stream==0){
        cout<<"ERROR, file does not exist"<<endl;
        return 0;
    }
    int im[620][800];
    int element;
    // loading the image
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            fscanf(stream,"%d",&element);
            im[i][j]=element;
        }
    }
    // computing nlinks
    cout<<"starting computing nlinks"<<endl;
    int sigma=5;
    double denominator=2*sigma*sigma;
    int nratio=50;
    double diff1=0;
    double diff2=0;
    double diff3=0;
    double diff4=0;

    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if(j+1<w){
                diff1=(im[i][j]-im[i][j+1])*(im[i][j]-im[i][j+1])/denominator;
                nlinks[i][j][2]=int(nratio*pow(e,-diff1));
            }   
            if(j-1>=0){
                diff2=(im[i][j]-im[i][j-1])*(im[i][j]-im[i][j-1])/denominator;
                nlinks[i][j][3]=int(nratio*pow(e,-diff2));
            }   
            if(i-1>=0){
                diff3=(im[i][j]-im[i-1][j])*(im[i][j]-im[i-1][j])/denominator;
                nlinks[i][j][4]=int(nratio*pow(e,-diff3));
            }   
            if(i+1<h){
                diff4=(im[i][j]-im[i+1][j])*(im[i][j]-im[i+1][j])/denominator;
                nlinks[i][j][5]=int(nratio*pow(e,-diff4));
            }
        }
    }
    // cout<<nlinks[100][20][3]<<endl; 
    // cout<<nlinks[100][210][4]<<endl;    
    // cout<<nlinks[100][202][5]<<endl;    




// building tlinks
    cout<<"prepare to compute tlinks"<<endl;
    int black_mean=0;
    int black_sig2=0;
    int black_tot=0;
    int white_mean=0;
    int white_sig2=0;
    int white_tot=0;
    if(stream1==0){
        cout<<"ERROR, file does not exist"<<endl;
        return 0;
    }
    int trimap[620][800];
    int white[620*100];
    int black[620*300];
    int white_index=0;
    int black_index=0;
    // loading trimap to an array
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            fscanf(stream1,"%d",&element);
            trimap[i][j]=element;
        }   
    }   
    // calculate mean and variance and use it as a Gaussian distribution
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if(trimap[i][j]==0){
                black_mean+=im[i][j];
                black_tot++;
                black[black_index++]=trimap[i][j];
            }
            else if(trimap[i][j]==255){
                white_mean+=im[i][j];
                white_tot++;
                white[white_index++]=trimap[i][j];
            }
        }
    }
    white_mean=white_mean/white_tot;
    black_mean=black_mean/black_tot;
    // count variance
    int tmp=0;
    for(int i=0;i<white_tot;i++){
        tmp+=(white[i]-white_mean)*(white[i]-white_mean);
    }   
    tmp=tmp/white_tot;
    white_sig2=tmp;
    tmp=0;
    for(int i=0;i<black_tot;i++){
        tmp+=(black[i]-black_mean)*(black[i]-black_mean);
    }   
    tmp=tmp/black_tot;
    black_sig2=tmp;
    tmp=0;
    // cout<<black_sig2<<"  "<<black_tot<<"  "<<black_mean<<endl;
    // cout<<white_sig2<<"  "<<white_tot<<"  "<<white_mean<<endl; 
    double b_para=1/sqrt(2*PI)/sqrt(black_sig2);
    double w_para=1/sqrt(2*PI)/sqrt(white_sig2);

    cout<<"computing tlinks"<<endl;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            // this is a background
            if(trimap[i][j]==0){
                s[i*800+j]=0;
                // t[i*800+j]=K;
                nlinks[i][j][1]=K;
            }
            else if(trimap[i][j]==255){
                // this is an object 
                s[i*800+j]=K;
                // t[i*800+j]=0;
                // nlinks[i][j][0]=K;
                nlinks[i][j][1]=0;

            }
            else {
                s[i*800+j]=-r_lambda*log(b_para*pow(e,-(im[i][j]-black_mean)*(im[i][j]-black_mean)/2/black_sig2));
                nlinks[i][j][1]=-r_lambda*log(w_para*pow(e,-(im[i][j]-white_mean)*(im[i][j]-white_mean)/2/white_sig2));
            }
        }
    }



    // ofstream outfile;
    // outfile.open("t.txt");
    // for(int i=0;i<h;i++){
    //  for(int j=0;j<w;j++){
    //     for(int k=0;k<6;k++){
    //          outfile << nlinks[i][j][k]<< " ";
    //      }   
    //  }    
    // }
    // outfile<<endl;    
    // outfile.close();


    return 0;
}


/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */
bool bfs(int parent[],int h,int w){
    // Create a visited array and mark all vertices as not visited
    bool visited[V+2];
    memset(visited, 0, sizeof(visited));

    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    queue <int> q;
    int source=620*800;
    int terminal=620*800+1;

    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    // Standard BFS Loop
    while (!q.empty()){
        // cout<<"queue.size: "<<q.size()<<endl;
        int u = q.front();
        q.pop();
        // if it is source
        // traverse all neighbouring nodes
        if(u==620*800){
            for(int i=0;i<h;i++){
                for(int j=0;j<w;j++){
                    int v=i*800+j;
                    if(s[v]>0 && visited[v]==false){
                        q.push(v);
                        parent[v] = u;
                        visited[v] = true;
                    }
                }
            }
        }
        // if it is sink
        else if(u==620*800+1){
            for(int i=0;i<h;i++){
                for(int j=0;j<w;j++){
                    int v=i*800+j;
                    if(t[v]>0 && visited[v]==false){
                        q.push(v);
                        parent[v] = u;
                        visited[v] = true;
                    }
                }
            }

        }
        else{
            // normal pixels
            int i=u/800;
            int j=u-int(u/800)*800;
            // cout<<i<<"  "<<j<<endl;
            // if in the up
            if(nlinks[i][j][0]>0 && visited[source]==false){
                cout<<"actually it is impossible"<<endl;
            }
            // if in the down
            if(nlinks[i][j][1]>0 && visited[terminal]==false){
                q.push(terminal);
                parent[terminal]=u;
                visited[terminal]=true;
            }    
            // if in the left
            if(nlinks[i][j][2]>0 && visited[i*800+j-1]==false){
                q.push(i*800+j-1);
                parent[i*800+j-1]=u;
                visited[i*800+j-1]=true;                
            }
            // if in the right
            if(nlinks[i][j][3]>0 && visited[i*800+j+1]==false){
                q.push(i*800+j+1);
                parent[i*800+j+1]=u;
                visited[i*800+j+1]=true;                
            }

            // if in the above
            if(nlinks[i][j][4]>0 && visited[(i-1)*800+j]==false){
                q.push((i-1)*800+j);
                parent[(i-1)*800+j]=u;
                visited[(i-1)*800+j]=true;                
            }
            // if in the down
            if(nlinks[i][j][5]>0 && visited[(i+1)*800+j]==false){
                q.push((i+1)*800+j);
                parent[(i+1)*800+j]=u;
                visited[(i+1)*800+j]=true;                
            }

        }
        if(visited[terminal]==true){
            cout<<"early termination "<<endl;
            break;
        }

    }

    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[terminal] == true);
}

// Returns tne maximum flow from s to t in the given graph
int fordFulkerson(int h,int w){
    int u, v;

    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    int parent[V+2];  // This array is filled by BFS and to store path
    int source=620*800;
    int terminal=620*800+1;

    int max_flow = 0;  // There is no flow initially

    // Augment the flow while there is path from source to sink
    while (bfs(parent,h,w)){
        // cout<<"------find one augmenting path, start augmenting----"<<endl;
        // find the bottleneck capacity
        int path_flow = INT_MAX;
        for (v=terminal; v!=source; v=parent[v]){
            u = parent[v];
            if(v==terminal && u!=620*800){  
                // down
                path_flow = min(path_flow, nlinks[u/800][u-int(u/800)*800][1]);
            }    
                // up
            else if(u==620*800 && v!=terminal){
                path_flow = min(path_flow, s[v]);
            }
            // left
            else if(u>v){
                // v is in u's above
                if(int((u-v)/800)==(u-v)/800){
                    path_flow = min(path_flow, nlinks[u/800][u-int(u/800)*800][4]);
                }
                // v is in u's left
                else{
                    path_flow = min(path_flow, nlinks[u/800][u-int(u/800)*800][2]);
                }
            }
            else if(u<v){
                // v is in u's down
                if(int((v-u)/800)==(v-u)/800){
                    path_flow = min(path_flow, nlinks[u/800][u-int(u/800)*800][5]);
                }
                // v is in u's right
                else{
                    path_flow = min(path_flow, nlinks[u/800][u-int(u/800)*800][3]);
                }
            }
        }

        // update residual capacities of the edges and reverse edges
        // along the path
        for (v=terminal; v!= source; v=parent[v]){
            u = parent[v];
            if(v==terminal && u!=620*800){  
                // down
                nlinks[u/800][u-int(u/800)*800][1]-=path_flow;
                t[u]+=path_flow;
            }    
                // up
            else if(u==620*800 && v!=terminal){
                s[v]-=path_flow;
                nlinks[v/800][v-int(v/800)*800][0]+=path_flow;
            }    
            // left
            else if(u>v){
                // v is in u's above
                if(int((u-v)/800)==(u-v)/800){
                    nlinks[u/800][u-int(u/800)*800][4]-=path_flow;
                    nlinks[v/800][v-int(v/800)*800][5]+=path_flow;
                }
                // v is in u's left
                else{
                    nlinks[u/800][u-int(u/800)*800][2]-=path_flow;
                    nlinks[v/800][v-int(v/800)*800][3]+=path_flow;
                }
            }
            else if(u<v){
                // v is in u's down
                if(int((v-u)/800)==(v-u)/800){
                    nlinks[u/800][u-int(u/800)*800][5]-=path_flow;
                    nlinks[v/800][v-int(v/800)*800][4]+=path_flow;
                }
                // v is in u's right
                else{
                    nlinks[u/800][u-int(u/800)*800][3]-=path_flow;
                    nlinks[v/800][v-int(v/800)*800][2]+=path_flow;
                }
            }
        }

        // Add path flow to overall flow
        max_flow += path_flow;
        cout<<"current max_flow is "<<max_flow<<"  increased:  "<<path_flow<<endl;
    }

    // Return the overall flow
    return max_flow;
}


