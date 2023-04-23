#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
 
const int MAXN = 200001;
const int MAXK = 21;
 
int dp[MAXN][MAXK];
int depth[MAXN];
int x;
 
void dfs(int node, int par, vector<int> adj[]) {
    dp[node][0] = par;
    for (int k = 1; k <= x; k++) {
        dp[node][k] = dp[dp[node][k - 1]][k - 1];
    }
    for (auto nnode : adj[node]) {
        if (par != nnode) {
            depth[nnode] = depth[node] + 1;
            dfs(nnode, node, adj);
        }
    }
}
 
int binaryLifting(int node, int k) {
    for (int c = x; c >= 0; c--) {
        if (k & (1 << c)) {
            node = dp[node][c];
            k -= (1 << c);
        }
    }
    return node;
}
 
int lca(int a, int b) {
    if (a == b) return a;   //if both the node are same
    if (depth[a] > depth[b]) swap(a, b);   //assuming depth[b]>depth[a] or else swaping the value
    int diff = depth[b] - depth[a];    //difference between the depth of two nodes
    b = binaryLifting(b, diff);      //moving node b to same level as a, by binaryLifting 
    if (a == b) return a;           // if both the nodes are same
 
    for (int j = x; j >= 0; j--) {      //making the maximum jump till the parents of both the nodes are not same)
        if (dp[a][j] != dp[b][j]) {
            a = dp[a][j];
            b = dp[b][j];
        }
    }
    return dp[a][0];   //since the parents of two nodes are dissimilar, we know that the next node has to be the LCA,therefore jumping only 1step
}
 
int main() {
    int n, q;
    cin >> n >> q;
    x = log2(n) + 1;
    vector<int> adj[n + 1];
    for (int i = 2; i <= n; i++) {
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    depth[1] = 0;   //depth of root is 0;
    dfs(1, 0, adj);   //has to take parent of root as 0 not -1;
    while (q--) {
        int m, n;
        cin >> m >> n;
        int ans=depth[m]+depth[n]-(2*depth[lca(m,n)]);    // formula !!! derieve it :))
        cout<<ans<<"\n";
    }
    return 0;
}
