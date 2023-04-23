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
    if (a == b) return a;
    if (depth[a] > depth[b]) swap(a, b);
    int diff = depth[b] - depth[a];
    b = binaryLifting(b, diff);
    if (a == b) return a;
    for (int j = x; j >= 0; j--) {
        if (dp[a][j] != dp[b][j]) {
            a = dp[a][j];
            b = dp[b][j];
        }
    }
    return dp[a][0];
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
    depth[1] = 0;
    dfs(1, 0, adj);
    while (q--) {
        int m, n;
        cin >> m >> n;
        int ans=depth[m]+depth[n]-(2*depth[lca(m,n)]);
        cout<<ans<<"\n";
    }
    return 0;
}
