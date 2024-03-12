#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <set>
#include <list>
using namespace std;

using edge = pair<int,int>;

class graph {
public:
    int n, m;
    vector<list<edge>> adj;
    vector<vector<int>> weight;

    void read() {
        cin >> n >> m;
        adj.assign(n+1, list<edge>());
        weight.assign(n+1, vector<int>(n+1, INT_MAX));

        int a, b, c;
        for(int i = 0; i < m; ++i) {
            cin >> a >> b >> c;
            adj[a].push_back({b,c});
            adj[b].push_back({a,c});
            weight[a][b] = weight[b][a] = c;
        }
    }

    void print_list() {
        set<edge> printed;

        cout << n << ' ' << m << endl;
        for(int u = 1; u < n+1; ++u) {
            for(edge e : adj[u]) {
                edge tmp { min(u, e.first), max(u, e.first) };
                if(printed.find(tmp) == printed.end()) {
                    cout << u << ' '
                         << e.first << ' ' 
                         << e.second << endl;
                    printed.insert(tmp);
                }
            }
        }
    }

    void print_matrix() {
        cout << n << ' ' << m << endl;
        for(int u = 1; u < n+1; ++u) {
            for(int v = u; v < n+1; v++) {
                if(weight[u][v] == INT_MAX) continue;
                cout << u << ' ' << v << ' ' 
                     << weight[u][v] << endl;
            }
        }
    }
};

int main() {
    graph G = graph();

    G.read();

    cout << "Dados armazenados por lista :\n";
    G.print_list();
    
    cout << "\nDados armazenados por matriz :\n";
    G.print_matrix();

    return 0;
}
