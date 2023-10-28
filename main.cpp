#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int INF = numeric_limits<int>::max();

void bellman(vector<vector<pair<int,int>>> grafo){
    int N = grafo.size();
    vector<long long> minimos(N,INF); //Inicio el vector con todas las distancias a la prim pos, con inf
    minimos[0] = 0; //Ir de la primer pos a primer pos cuesta 0
    bool hayCambios; //Indica si hice algún cambio en los caminos en la iteración i
    while(hayCambios){
        hayCambios = false; //Inicio con cambio negativo
        vector<long long> minimosTemp = minimos; //Hago una copia de los caminos minimos para ver si hago cambios
        for(int i = 1; i < N ;i++){ //itero sobre, ttodo el grafo
            long long posibleNuevo = INF; // Posible nueva distancia de 0 a i
            long long TEMP;
            for(int j = 0; j<i+1; j++){ //recorro todos los vertices anteriores al que estoy parado
                for(int k = 0; k < grafo[j].size(); k++){ //recorro todos los lugares a los que llegan esos vertices (aristas)
                    if(grafo[j][k].first == i){ //Veo si alguno de esos caen en el vertice donde estoy parado
                        TEMP = minimos[j] + grafo[j][k].second; //Guardo la distancia de 0 a j + j a i
                        posibleNuevo = min(posibleNuevo,TEMP); //Guardo el menor entre la actual encontrada y la que estaba antes
                    }
                }

            }
            if(posibleNuevo != minimosTemp[i]){
                hayCambios = true;
                minimos[i] = posibleNuevo;
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
        bellman(caminos);
    }
    return 0;
}

