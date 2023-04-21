// Online C++ compiler to run C++ program online
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int solve(int node,int par,int pick,vector<int> adj[],vector<vector<int>>& dp){
    if(dp[node][pick]!=-1) return dp[node][pick];
    //cout<<node<<" "<<pick<<"\n";
    if (pick){
        int ans=0;
        int total=0;
        for(auto nnode:adj[node]){
            if(par!=nnode){
                total+=solve(nnode,node,1,adj,dp);
            }
        }
        for(auto nnode:adj[node]){
            if(par!=nnode){
                int temp=total-dp[nnode][1]+1+solve(nnode,node,0,adj,dp);
                ans=max(ans,temp);
            }
        }
        return dp[node][pick]=ans;
    }else{
        int ans=0;
        for(auto nnode:adj[node]){
            if(par!=nnode){
              ans+=solve(nnode,node,1,adj,dp);  
            }
        }
        return dp[node][pick]=ans;
    }
    return -1;
}

int main() {
    // Write C++ code here
    int x,y,n;
    cin>>n;
    vector<int>adj[n+1];
    for(int i=2;i<=n;i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<vector<int>>dp(n+2,vector<int>(2,-1));
    int ans=max(solve(1,0,0,adj,dp),solve(1,0,1,adj,dp));
    cout<<ans<<" ";
    
    return 0;
}
