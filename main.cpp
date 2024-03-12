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

    void read(bool directed = false) {
        cin >> n >> m;
        adj.assign(n+1, list<edge>());
        weight.assign(n+1, vector<int>(n+1, INT_MAX));

        int a, b, c;
        for(int i = 0; i < m; ++i) {
            cin >> a >> b >> c;
            adj[a].push_back({b,c});
            weight[a][b] = c;
            if(!directed) {
                adj[b].push_back({a,c});
                weight[b][a] = c;
            }
        }
    }

    void print_list() {
        for(int u = 1; u < n+1; ++u) {
            cout << u << " : ";
            for(edge e : adj[u]) {
                cout << "(" << e.first 
                     << "," << e.second
                     << ") ";
            }
            cout << endl;
        }
    }

    void print_matrix() {
        for(int u = 1; u < n+1; ++u) {
            for(int v = 1; v < n+1; v++) {
                if(weight[u][v] == INT_MAX) cout << "-";
                else cout << weight[u][v];
                cout << " ";
            }
            cout << endl;
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
