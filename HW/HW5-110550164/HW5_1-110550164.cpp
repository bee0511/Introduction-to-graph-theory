#include <iostream>
#include <vector>

using namespace std;

class Graph{
	public:
	int V;
	vector<vector<int>> adj;
	vector<int> deg;
	Graph(int V){
		this->V = V;
		adj = vector<vector<int>> (V, vector<int>(V, 0));
		deg = vector<int>(V, 0);
	}

	int k5(){
		static int p[8];
		int i, k;
		for (p[0] = 0, k = 0; k >= 0;){
			if (++p[k] > V){
				k--;
				continue;
			}
			for (i = 0; i < k; i++){
				if (!adj[p[k]][p[i]]) break;
			}
			if (i < k){
				k--;
				continue;
			}
			if (k == 4){
				return 1;
			}
			p[k + 1] = p[k];
			k++;
		}
	return 0;
	}

	int k33(){
	/*
	   a     b     c
	   | \ / | \ / |
	   d     e     f
	*/
		int a, b, c, d, e, f;
		for (a = 1; a < V; a++){

			for (d = 1; d < V; d++){

				if (!adj[a][d]) continue;

				for (b = 1; b < V; b++){
					if (!adj[b][d] || a == b) continue;

					for (e = 1; e < V; e++){
						if (!adj[a][e] || !adj[b][e] || d == e) continue;

						for (c = 1; c < V; c++){
							if (!adj[d][c] || !adj[e][c] || c == a || c == b) continue;

							for (f = 1; f < V; f++){
								if (!adj[a][f] || !adj[b][f] || !adj[c][f] || f == d || f == e) continue;
								return 1;
							}
						}
					}
				}
			}
		}
		return 0;
	}
	void print(){
		for(int i = 1 ; i < V ; i ++){
            for(int j = 1 ; j < V ; j++){
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
	}
	void pushEdge(int u, int v){
		adj[u][v] = 1;
		adj[v][u] = 1;
		deg[u] = deg[v]++;
	}
};



int main()
{
    int Q;
	int n, m, x, y;
	int i, j, k;
    cin >> Q;
	while (Q--){
        cin >> n >> m;
		Graph g(n + 1);
		while (m--){
			int u, v;
			cin >> u >> v;
			g.pushEdge(u, v);
		}
		
		g.print();
		cout << "k5(): " << g.k5() << " k33(): " << g.k33() << endl;
		printf((g.k5() || g.k33()) ? "No\n" : "Yes\n");
	}
	return 0;
}