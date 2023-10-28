#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>
using namespace std;

int INF = numeric_limits<int>::max();

struct MinHeap {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    void push(pair<int, int> value) {
        minHeap.push(value);
    }
    void pop() {
        minHeap.pop();
    }
    pair<int, int> top() {
        return minHeap.top();
    }
    size_t size() const {
        return minHeap.size();
    }
    bool isEmpty() const {
        return minHeap.empty();
    }
};

void dijkstra(vector<vector<pair<int,int>>> grafo){
    int N = grafo.size();
    vector<int> minimos(N, INF);
    minimos[0] = 0;
    MinHeap heap;
    heap.push({0,0});

    while(!heap.isEmpty()){
        int distancia = heap.top().first;
        int vertice = heap.top().second;
        heap.pop();

        for(int i = 0; i < grafo[vertice].size(); i++){
            int posibleNuevaDist = minimos[vertice] + grafo[vertice][i].second;
            if(posibleNuevaDist < minimos[grafo[vertice][i].first]){
                minimos[grafo[vertice][i].first] = posibleNuevaDist;
                heap.push({posibleNuevaDist,grafo[vertice][i].first});
            }

        }

    }
    int K = minimos.size()/4;
    long long ceroPuentes = minimos[K - 1];
    long long unPuente = minimos[2*K - 1];
    long long dosPuentes = minimos[3*K - 1];
    long long tresPuentes = minimos[4*K - 1];
    cout << min(ceroPuentes,min(unPuente,min(dosPuentes,tresPuentes))) << endl;
}

int main() {
    int cantTest, cantSalones, cantTuneles, entrada, salida;
    cin >>cantTest;
    for(int i = 0; i < cantTest; i++){
        cin >> cantSalones >> cantTuneles;
        vector<vector<pair<int,int>>> caminos((cantSalones+1)*4);
        for(int j = 0; j < caminos.size()-1;j++){
            caminos[j].push_back({j+1,1});
            //Acá en realidad junta cosas de mas
            //el último de la primer copia del grafo con el primero de la segunda, eso no debería estar
        }
        int N = cantSalones + 1;
        for(int k = 0; k < cantTuneles; k++){
            cin >> entrada >> salida;
            caminos[entrada].push_back({salida+N,2});
            caminos[entrada + N].push_back({salida + 2*N,2});
            caminos[entrada + 2*N].push_back({salida + 3*N,2});
        }
        int a = 0;
        dijkstra(caminos);
        //bellman(caminos);
    }
    return 0;
}

