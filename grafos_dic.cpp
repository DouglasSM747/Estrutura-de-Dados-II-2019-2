#include <bits/stdc++.h>
#include <stdlib.h>
#define INF 1000000
using namespace std;
pair<int, int> InitalPair;

// To represent Disjoint Sets
struct DisjointSets
{
    int *parent, *rnk;
    int n;

    // Constructor.
    DisjointSets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n + 1];
        rnk = new int[n + 1];

        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;

            //every element is parent of itself
            parent[i] = i;
        }
    }

    // Find the parent of a node 'u'
    // Path Compression
    int find(int u)
    {
        /* Make the parent of the nodes in the path 
           from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Union by rank
    void merge(int x, int y)
    {
        x = find(x), y = find(y);

        /* Make tree with smaller height 
           a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

class Grafo
{
public:
    map<int, vector<pair<int, int>>> m; //Cria as vertices
    int valor_maximo;
    bool possuiCicloNegativo = false;

    int verificarExisteArresta(int u, int v)
    {
        int existe;

        for (auto x : this->m[u])
        {
            if (v == x.first)
            {
                return 1;
            }
        }
        return -1;
    }

    int verificarExisteVertice(int u)
    {

        for (auto x : this->m)
        {
            if (x.first == u)
            {
                return 1;
            }
        }
        return -1;
    }
    //faz uma bfs a partir da raiz (determinada)
    void BFS(int u)
    {
        queue<int> fila;
        bool visitado[this->valor_maximo];

        for (int i = 0; i <= this->valor_maximo; i++)
            visitado[i] = false; //marca tudo como n visitado

        cout << "Visitando Vertice: " << u << endl;
        visitado[u] = true; //marca o vizinho como visitado

        while (true)
        {

            vector<pair<int, int>>::iterator it;

            //Visita todos os vizinhos do U -> Vertice
            for (it = this->m[u].begin(); it != this->m[u].end(); it++)
            {

                if (!visitado[it->first])
                {
                    cout << "Visitando Vertice: " << it->first << endl;
                    visitado[it->first] = true; //marca o vizinho como visitado
                    fila.push(it->first);       //add na fila
                }
            }
            if (!fila.empty())
            {
                u = fila.front();
                fila.pop();
            }
            else
            {
                break;
            }
        }
    }

    /* Functions returns weight of the MST*/

    int kruskalMST(vector<pair<int, pair<int, int>>> edges)
    {
        int mst_wt = 0; // Initialize result

        // Create disjoint sets
        DisjointSets ds(this->valor_maximo + 1);

        // Iterate through all sorted edges
        vector<pair<int, pair<int, int>>>::iterator it;
        for (it = edges.begin(); it != edges.end(); it++)
        {
            if (verificarExisteVertice(it->second.second) == 1)
            {

                int u = it->second.first;
                int v = it->second.second;

                int set_u = ds.find(u);
                int set_v = ds.find(v);

                // Check if the selected edge is creating
                // a cycle or not (Cycle is created if u
                // and v belong to same set)
                if (set_u != set_v)
                {
                    // Current edge will be in the MST
                    // so print it
                    cout << u << " - " << v << endl;

                    // Update MST weight
                    mst_wt += it->first;

                    // Merge two sets
                    ds.merge(set_u, set_v);
                }
            }
        }
        return mst_wt;
    }

    void primMST(int src)
    {
        // Create a priority queue to store vertices that

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Create a vector for keys and initialize all
        // keys as infinite (INF)
        vector<int> key(this->valor_maximo, INF);

        // To store parent array which in turn store MST
        vector<int> parent(this->valor_maximo, -1);

        // To keep track of vertices included in MST
        vector<bool> inMST(this->valor_maximo, false);

        // Insert source itself in priority queue and initialize
        // its key as 0.
        pq.push(make_pair(0, src));
        key[src] = 0;

        /* Looping till priority queue becomes empty */
        while (!pq.empty())
        {
            // The first vertex in pair is the minimum key
            // vertex, extract it from priority queue.
            // vertex label is stored in second of pair (it
            // has to be done this way to keep the vertices
            // sorted key (key must be first item
            // in pair)
            int u = pq.top().second;
            pq.pop();

            inMST[u] = true; // Include vertex in MST

            // 'i' is used to get all adjacent vertices of a vertex
            vector<pair<int, int>>::iterator i;
            for (i = this->m[u].begin(); i != this->m[u].end(); ++i)
            {
                // Get vertex label and weight of current adjacent
                // of u.
                int v = i->first;
                int weight = i->second;

                //  If v is not in MST and weight of (u,v) is smaller
                // than current key of v
                if (inMST[v] == false && key[v] > weight)
                {
                    // Updating key of v
                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                    parent[v] = u;
                }
            }
        }

        // Print edges of MST using parent array
        for (int i = 1; i < this->valor_maximo; ++i)
            if (verificarExisteVertice(i) == 1)
                cout << parent[i] << "-" << i << endl;
    }
    void BellmanFord(int src)
    {
        //define a distancia como infinito
        int dist[this->valor_maximo];

        for (int i = 0; i < this->valor_maximo; i++)
        {
            dist[i] = INF;
        }

        //a distancia ate si mesmo e' 0
        dist[src] = 0;
        vector<pair<int, int>>::iterator it;

        //compara para todas a vezes que pecorreu o grafo (Visualiza novamente)
        for (int i = 0; i < this->valor_maximo; i++)
        {
            //pecorre todos os vertices
            if (verificarExisteVertice(i) == 1)
            {
                for (it = this->m[i].begin(); it != this->m[i].end(); it++)
                {
                    int u = i;
                    int v = it->first;
                    int peso_arreta = it->second;

                    //RELAXAMENTO
                    if (dist[v] > (peso_arreta + dist[u]))
                    {
                        dist[v] = (dist[u] + peso_arreta);
                    }
                }
            }
        }
        //verifica sem alguma arresta sem relaxamento corrento
        //Se você deseja que o grafo tenha ciclos internos de peso negativo, o algoritmo Bellman Ford não funcionará corretamente.
        for (int i = 0; i < this->valor_maximo; i++)
        {
            if (verificarExisteVertice(i) == 1)
            {
                for (it = this->m[i].begin(); it != this->m[i].end(); it++)
                {

                    int u = i;
                    int v = it->first;
                    int peso_arreta = it->second;

                    if (dist[v] > (dist[u] + peso_arreta))
                    {
                        this->possuiCicloNegativo = true;
                    }
                }
            }
        }
        //Imprime todas las distancias desde el origen hasta todos los vertices.
        if (!possuiCicloNegativo)
        {
            for (int i = 0; i < this->valor_maximo; i++)
            {
                if (verificarExisteVertice(i) == 1)
                    cout << i << " - " << dist[i] << endl;
            }
        }
    }
    int Dijsk(int u, int v)
    {
        int dist[this->valor_maximo];
        bool visitados[this->valor_maximo]; // verificar se foi visitado
        //definos a fila de prioridade pela distancia minima ate outro vertice
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>>
            pq; //armazena a distancia e vertice, utiliza fila de prioridade

        //iniciar visitado e dist

        for (int i = 0; i < this->valor_maximo; i++)
        {
            dist[i] = INF;
            visitados[i] = false;
        }

        //verifica a dist de orgiem para origem e 0
        dist[u] = 0;

        //insere na fila
        pq.push(make_pair(dist[u], u));

        while (!pq.empty())
        {
            //quem vai expandir (primeiro da pq)
            pair<int, int> p = pq.top();
            int vert = p.second; //obtem o vertice do pair que esta sendo analisado
            pq.pop();

            //verifica se foi expandido

            if (visitados[vert] == false)
            {
                visitados[vert] == true;

                vector<pair<int, int>>::iterator it;

                //pecorre os vertices adj de u
                for (it = this->m[vert].begin(); it != this->m[vert].end(); it++)
                {
                    //obter o vertice adjacente e o custo da arresta - RELAXAMENTO
                    int vertice = it->first;    // vertice adj
                    int custo_arr = it->second; // custo da arresta

                    //relaxa U - V

                    if (dist[vertice] > (dist[vert] + custo_arr))
                    {
                        //atualiza a distancia ate o v
                        dist[vertice] = (dist[vert] + custo_arr);
                        pq.push(make_pair(dist[vertice], vertice));
                    }
                }
            }
        }
        //retorna a distancia minima do vertice u ate o x
        return dist[v];
    }
    //faz uma dfs a partir da raiz (determinada)
    void DFS(int u)
    {
        stack<int> pilha;
        bool visitado[this->valor_maximo]; //vetor de visitados

        /*
        Uma vez que o vertice do grafo pode adotar qualquer valor inteiro,
        foi necessario simular um grafo sequencial [0,1,2,3,4], de forma que
        criado um vetor ate o maior numero de um inteiro no grafo.
        */
        //todo mundo n foi visitado
        for (int i = 0; i <= this->valor_maximo; i++)
            visitado[i] = false;

        while (true)
        {
            vector<pair<int, int>>::iterator it;

            if (!visitado[u])
            {
                cout << "Visitando Vertice: " << u << endl;
                visitado[u] = true;
                pilha.push(u);
            }

            bool achou = false;
            //busca por vizinho nao visitado
            for (it = this->m[u].begin(); it != this->m[u].end(); it++)
            {
                if (!visitado[it->first])
                {
                    achou = true;
                    break;
                }
            }
            if (achou)
            {
                u = it->first;
            }
            else //se todos foram visitados ou nao tem vizinho

            {
                //remove da pilha para e volta pro pai
                pilha.pop();
                //se ta no fim, chegou no final
                if (pilha.empty())
                    break;
                u = pilha.top();
            }
        }
        cout << endl;
    }

    int addVertice(int u)
    {
        int continuar = 0;

        if (verificarExisteVertice(u) == -1)
        {
            if (this->m.size() == 0)
                valor_maximo = u;

            if (u > valor_maximo)
                valor_maximo = u;

            this->m[u].push_back(InitalPair); //add uma vertice vazia

            this->m[u].clear();
            //this->m[u].erase(find(this->m[u]. begin(), this->m[u].end(), 0)); //remove o elemento vazio adicionado
            return 1;
        }
        else
        {
            return -1;
        }
    }

    int removeArresta(int u, int v)
    {
        if (verificarExisteVertice(u) == 1 && verificarExisteVertice(u) == 1 && verificarExisteArresta(u, v) == 1)
        {
            pair<int, int> p;

            for (auto s : this->m[u])
            {
                if (s.first == v)
                {
                    p.second = s.second;
                    break;
                }
            }

            p.first = v;

            //Grafo digrafo, apaga u <-> v
            this->m[u].erase(find(this->m[u].begin(), this->m[u].end(), p));

            //this->m[v].erase(find(this->m[v].begin(), this->m[v].end(), u)); //Se quiser transformar em Digrafo
            return 1;
        }
        else
        {
            return -1;
        }
    }

    int removeVertice(int u)
    {
        if (verificarExisteVertice(u) == 1)
        {
            for (auto i : this->m) // busca por todos a lista de vertice e exclue u
            {
                for (int j = 0; j < i.second.size(); j++)
                {
                    if (i.second[j].first == u)
                    {
                        this->m[i.first].erase(find(this->m[i.first].begin(), this->m[i.first].end(), make_pair(i.second[j].first, i.second[j].second)));
                    }
                }
            }
            this->m.erase(u); //esvazia a lista de adj de u
            return 1;
        }
        else
        {
            return -1;
        }
    }

    int addArresta(int u, int v, int w)
    {

        if (verificarExisteVertice(u) == 1 && verificarExisteVertice(v) == 1 && verificarExisteArresta(u, v) == -1)
        {
            //this->m[v].push_back(u); //Se quiser transformar em Digrafo
            this->m[u].push_back(make_pair(v, w));
            return 1;
        }
        else
        {
            return -1;
        }
    }

    int obterGrauSaida(int u)
    {
        bool continuar = false;

        if (verificarExisteVertice(u) == 1)
        {
            return this->m[u].size();
        }
        else
        {
            return -1;
        }
    }

    vector<pair<int, pair<int, int>>> OrdenarPesoVetor()
    {
        vector<pair<int, pair<int, int>>> edges;
        for (auto s : this->m)
        {
            for (auto x : s.second)
            {
                edges.push_back({x.second, {s.first, x.first}});
            }
        }
        sort(edges.begin(), edges.end());
        return edges;
    }

    void printarGrafo()
    {
        for (auto x : this->m)
        {
            cout << "<=== Vertice " << x.first << "=== >" << endl;

            for (auto s : this->m[x.first])
            {
                cout << s.first << " > Peso " << s.second << endl;
            }
            cout << endl;
        }
    }
};

void listarGrafos(int size)
{
    system("clear");
    if (size == 0)
    {
        cout << "Nenhum grafo foi adicionado" << endl;
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            cout << "Grafo de ID:  " << i << endl;
        }
    }
}

// int AntesMenu()
// {
//     system("clear");
//     int op;
//     cout << "-------BEM VINDO AO SISTEMA DE GRAFOS--------" << endl;
//     cout << "-->Criar Grafo (1)" << endl;
//     cout << "-->Acessar Grafo (2)" << endl;
//     cout << "-->ListarGrafos (3)" << endl;
//     cout << "-->Sair do Sistema (4)" << endl;

//     cin >> op;
//     return op;
// }

// int acessoGrafo(int n_grafo, int size)
// {
//     system("clear");
//     if (n_grafo > size)
//     {
//         return -1;
//     }
//     else
//     {
//         return n_grafo;
//     }
// }

// int menu()
// {
//     int op = 0;
//     cout << "---------------" << endl;
//     cout << "-->Que operacao deseja realizar ?" << endl;
//     cout << "-->Adicionar vertice (1)" << endl;
//     cout << "-->Adicionar arresta (2)" << endl;
//     cout << "-->Remover vertice (3)" << endl;
//     cout << "-->Remover arresta (4)" << endl;
//     cout << "-->Obter Grau do vertice (5)" << endl;
//     cout << "-->Printar Grafo (6)" << endl;
//     cout << "-->Voltar antes Menu (7)" << endl;

//     cout << "\n Digite a opcao: ";
//     cin >> op;
//     system("clear");
//     return op;
// }
int main()
{
    int op = 1, v, v1, v2, cont_grafo, grafo;
    vector<Grafo> vg;
    Grafo g;
    g.addVertice(0);
    g.addVertice(1);
    g.addVertice(2);
    g.addVertice(3);
    g.addVertice(4);
    g.addVertice(5);
    g.addVertice(6);
    g.addVertice(7);
    g.addVertice(8);

    g.addArresta(0, 1, 4);
    g.addArresta(0, 7, 8);
    g.addArresta(1, 2, 8);
    g.addArresta(1, 7, 11);
    g.addArresta(2, 3, 7);
    g.addArresta(2, 8, 2);
    g.addArresta(2, 5, 4);
    g.addArresta(3, 4, 9);
    g.addArresta(3, 5, 14);
    g.addArresta(4, 5, 10);
    g.addArresta(5, 6, 2);
    g.addArresta(6, 7, 1);
    g.addArresta(6, 8, 6);
    g.addArresta(7, 8, 7);

    int k = g.kruskalMST(g.OrdenarPesoVetor());
    cout << k << endl;

    // while (op >= 1 && op <= 3)
    // {

    //     system("clear");
    //     op = AntesMenu();
    //     system("clear");

    //     if (op == 1)
    //     {
    //         cout << "Grafo criado com sucesso" << endl;
    //         Grafo g;
    //         vg.push_back(g);
    //     }
    //     else if (op == 2)
    //     {
    //         cout << "Deseja acessar que grafo: ";
    //         cin >> v;
    //         int x = acessoGrafo(v, vg.size());
    //         if (x == -1)
    //         {
    //             cout << "Grafo n existe" << endl;
    //         }
    //         else
    //         {
    //             while (1 == 1)
    //             {
    //                 system("clear");
    //                 op = menu();
    //                 if (op > 0 && op <= 6)
    //                 {
    //                     switch (op)
    //                     {
    //                     case 2:
    //                         system("clear");
    //                         cout << "\n Digite o valor da vertice1 seguido do valor vertice1 (ex: 1 2):  ";
    //                         cin >> v1 >> v2;
    //                         v = vg[x].addArresta(v1, v2);
    //                         if (v == 1)
    //                             cout << "\n Arresta adicionada com sucesso";
    //                         else
    //                             cout << "\n Erro ao adicionar arresta";
    //                         break;
    //                     case 1:
    //                         system("clear");
    //                         cout << "\n Digite o valor do vertice:  ";
    //                         cin >> v1;
    //                         v = vg[x].addVertice(v1);
    //                         if (v == 1)
    //                             cout << "\n Vertice adicionada com sucesso";
    //                         else
    //                             cout << "\n Erro ao adicionar vertice";
    //                         break;
    //                     case 3:
    //                         system("clear");
    //                         cout << "\n Digite o valor do vertice a ser apagado:  ";
    //                         cin >> v1;
    //                         v = vg[x].removeVertice(v1);
    //                         if (v == 1)
    //                             cout << "\n Vertice apagada com sucesso";
    //                         else
    //                             cout << "\n Erro ao apagar vertice";
    //                         break;
    //                     case 4:
    //                         system("clear");
    //                         cout << "\n Digite as arrestas a serem apagadas:  ";
    //                         cin >> v1 >> v2;
    //                         v = vg[x].removeArresta(v1, v2);
    //                         if (v == 1)
    //                             cout << "\n Arrestas apagadas com sucesso";
    //                         else
    //                             cout << "\n Erro ao apagar as arrestas";
    //                         break;
    //                     case 5:
    //                         system("clear");
    //                         cout << "\n Digite o vertice que deseja obter o grau:  ";
    //                         cin >> v1;
    //                         v = vg[x].obterGrau(v1);
    //                         if (v == -1)
    //                             cout << "\n Vertice nao existe";
    //                         else
    //                             cout << "\n O grau do vertice:  " << v;
    //                         break;
    //                     case 6:
    //                         system("clear");
    //                         vg[x].printarGrafo();
    //                         break;
    //                     }
    //                 }
    //                 else
    //                 {
    //                     break;
    //                 }
    //                 cout << "\n\nDeseja continuar no Menu ? (Not: 8, Yes: 1):  ";
    //                 cin >> op;
    //             }
    //         }
    //     }
    //     else if (op == 3)
    //     {
    //         listarGrafos(vg.size());
    //     }
    //     else
    //     {
    //         break;
    //     }

    //     cout << "\n\n Deseja voltar pro menu ? (Not: 4, Yes: 1):  ";
    //     cin >> op;
    // }
    vg.clear();

    return 0;
}
