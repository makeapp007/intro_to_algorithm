// A Dynamic Programming based solution for 0-1 Knapsack problem
#include <stdio.h>
#include <iostream>
// A utility function that returns maximum of two integers
using namespace std;
int max(int a, int b) { return (a > b)? a : b; }
int K[100][100];

 
// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n)
{
   int i, w;
 
   // Build table K[][] in bottom up manner
   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= W; w++)
       {
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   }
 
   return K[n][W];
}
 
int main()
{
    int val[] = {1,6,18,22,28};
    int wt[] = {1,2,5,6,7};
    int  W = 11;
    int n = sizeof(val)/sizeof(val[0]);
    printf("%d\n", knapSack(W, wt, val, n));
    for(int i=0;i<=n;i++){
      for(int j=0;j<=W;j++){
        cout<<K[i][j]<<"  ";

      }
      cout<<endl;
    }
    return 0;
}

