#include "the3.h"
#define INT_MAX1 147483647



// You  can define extra functions here

void dfsVisit(int** &edgeList,int n,int index,int* colorArray,int renk){
    colorArray[index] = renk;
    for(int i=0;i<n;i++){
        if(edgeList[index][i] > 0){
            if(colorArray[i] == 0){
                dfsVisit(edgeList,n,i,colorArray,renk);
            }
        }
    }
    //colorArray[index] = 2;
}


//0 means white, 1 means grey, 2 means black

int depthFirstSearch(int **&edgeList,int n,bool** sameComponentArray){
    int components=0;
    int renk = 1;
    int colorArray[n];
    for(int i=0;i<n;i++){
        colorArray[i] = 0;
    }
    for(int i=0;i<n;i++){
        if(colorArray[i] == 0){ //means white
            components++;
            dfsVisit(edgeList,n,i,colorArray,renk);
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(colorArray[i] == renk && colorArray[j] ==renk){
                        sameComponentArray[i][j] = true;
                    }
                }
            }
            renk++;
        }
    }
    return components;
}


// INPUT :
//            n         : number of nodes in the graph
//            edgeList  : edges in the graph
//            scores    : importance scores
// return value :
//                 number of disconnected components
int Important (int n, int**& edgeList, double*& scores){
   double returnValue = 0;
   int pairLength[n][n];
   bool** sameComponentArray;
   sameComponentArray = new bool*[n];
   for(int i = 0; i < n; i++){
       sameComponentArray[i] = new bool[n];
   }
   for(int i=0;i<n;i++){
       for(int j=0;j<n;j++){
           if(i == j){
               sameComponentArray[i][j] = true;
           }
           else{
               sameComponentArray[i][j] = false;
           }
       }
   }
   int numberOfDisconnectedComponents = depthFirstSearch(edgeList,n,sameComponentArray);
   for(int i=0;i<n;i++){
       for(int j=0;j<n;j++){
           if(edgeList[i][j] != 0){
               pairLength[i][j] = edgeList[i][j];
           }
           else if(i==j){
               pairLength[i][j] =1;
           }
           else{
               pairLength[i][j] = INT_MAX1;
           }
       }
   }

   for(int k=0;k<n;k++){
       for(int i=0;i<n;i++){
           for(int j=0;j<n;j++){
               if(pairLength[i][k]+pairLength[k][j] < pairLength[i][j] && i!=j){
                   pairLength[i][j] = pairLength[i][k] + pairLength[k][j];
               }
           }
       }
   }

   for(int i=0;i<n;i++){
       for(int j=0;j<n;j++){
           if(pairLength[i][j] == INT_MAX1){
               pairLength[i][j] = 0;
           }
       }
   }


   for(int i=0;i<n;i++){
       returnValue = 0;
       for(int j=0;j<n;j++){
           for(int k=0;k<n;k++){
               if(sameComponentArray[i][j] && sameComponentArray[i][k] && sameComponentArray[j][k]){
                   double ust;
                   double alt;
                   if(j == k){
                       alt = 1;
                   }
                   else{
                       alt = pairLength[j][k];
                   }
                   if(i == j || i == k){
                       ust = 0;
                   }
                   else{
                       ust = pairLength[j][i]+pairLength[i][k];
                   }
                   returnValue+=(ust/alt);
                }
           }
       }
       scores[i] = returnValue;
   }
   for(int i=0;i<n;i++){
       delete[] sameComponentArray[i];
   }
   delete[] sameComponentArray;
   return numberOfDisconnectedComponents;
}