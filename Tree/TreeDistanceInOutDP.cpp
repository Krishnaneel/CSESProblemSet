#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//calculating the distance from the furthest node of in-subTree of current "node" whose parent is "par"

void dfs1(int node,int par,vector<int> adj[],vector<int>& ins){
    ins[node]=0;
    for(auto nnode:adj[node]){
      if(par==nnode) continue;
        
      dfs1(nnode,node,adj,ins);
      ins[node]=max(ins[node],ins[nnode]+1);
    }
}

//calculating the distance from the furthest node of out-subTree of the children of current "node" whose parent is "par"

void dfs2(int node,int par,vector<int> adj[],vector<int>& out,vector<int>& ins){
    int mx1=-1,mx2=-1;
    for(auto nnode:adj[node]){
        if(par!=nnode){
            if(ins[nnode]>=mx1){
                mx2=mx1;
                mx1=ins[nnode];
            }else if(ins[nnode]>=mx2){
                mx2=ins[nnode];
            }
        }
    }
    for(auto nnode:adj[node]){
        if(par!=nnode){
            int longest;
            if(mx1==ins[nnode]) longest=mx2;
            else longest=mx1;
            out[nnode]=max(out[node],longest+1)+1;
            dfs2(nnode,node,adj,out,ins);
        }
    }
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
    vector<int>ins(n+1,0);
    vector<int>out(n+1,0);
    
    dfs1(1,0,adj,ins);
    dfs2(1,0,adj,out,ins);
    
    //res=max of distance of furthest node of insubtree and outsubtree
    for(int i=1;i<=n;i++){
        cout<<max(ins[i],out[i])<<" ";
    }
    
    return 0;
}
