#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string>
using namespace std;

const int N=1e5;
int x;
int dp[N][2];

int fn(int n,int p)
{   

    if(dp[n][p]!=-1) return dp[n][p];

   
    if( n-1 == 0 || n-x==0 || n-2 == 0 )
        {
            dp[n][p] = p;
            return p;
        }

    if( n-1 > 0 )  
        if( fn(n-1,!p) == p ) {dp[n][p] = p;  return p;}
    if( n-2 > 0 )  
        if( fn(n-2,!p) == p ) {dp[n][p] = p;  return p;}
    if( n-x > 0 )  
        if( fn(n-x,!p) == p ) {dp[n][p] = p;  return p;}

    dp[n][p] = !p;    
    return !p; 

}

int main()
{   
    
    double tt=0;
    // for(int j=0;j<1000;j++)
    // {

    
        clock_t start = clock();

        for(int i=0;i<N;i++){
            dp[i][0]=-1;
                dp[i][1]=-1;
        } 


        int n=69999;
        x=4;
        fn(n,1);
        //cout<<  <<endl;
        clock_t end = clock();
        double cpu_time_used = ((double) (end - start)/CLOCKS_PER_SEC);
        tt+=cpu_time_used;
       

    // } 
    
    
    cout << tt <<"\n";
 


    return 0;
}