#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

class Grafo
{
public:
    map<int, vector<int>> m; //Cria as vertices
    int valor_maximo;
    int verificarExisteArresta(int u, int v)
    {
        int existe;

        for (auto x : this->m[u])
        {
            if (v == x)
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
            
            vector<int>::iterator it;

            //Visita todos os vizinhos do U -> Vertice
            for (it = this->m[u].begin(); it != this->m[u].end(); it++)
            {
                if (!visitado[*it])
                {
                    cout << "Visitando Vertice: " << *it << endl;
                    visitado[*it] = true; //marca o vizinho como visitado
                    fila.push(*it); //add na fila
                }
            }
            if(!fila.empty()){
                u = fila.front();
                fila.pop();
            }else{
                break;
            }
        }
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
            vector<int>::iterator it;

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
                if (!visitado[*it])
                {
                    achou = true;
                    break;
                }
            }
            if (achou)
            {
                u = *it;
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

            this->m[u].push_back({});                                        //add uma vertice vazia
            this->m[u].erase(find(this->m[u].begin(), this->m[u].end(), 0)); //remove o elemento vazio adicionado
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
            //Grafo digrafo, apaga u <-> v
            this->m[u].erase(find(this->m[u].begin(), this->m[u].end(), v));
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
                    if (i.second[j] == u)
                    {
                        this->m[i.first].erase(find(this->m[i.first].begin(), this->m[i.first].end(), i.second[j]));
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

    int addArresta(int u, int v)
    {

        if (verificarExisteVertice(u) == 1 && verificarExisteVertice(v) == 1 && verificarExisteArresta(u, v) == -1)
        {
            //this->m[v].push_back(u); //Se quiser transformar em Digrafo
            this->m[u].push_back(v);
            return 1;
        }
        else
        {
            return -1;
        }
    }

    int obterGrau(int u)
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

    void printarGrafo()
    {
        for (auto x : this->m)
        {
            cout << x.first << ": ";
            for (int i = 0; i < x.second.size(); i++)
            {
                cout << x.second[i] << " ";
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

int AntesMenu()
{
    system("clear");
    int op;
    cout << "-------BEM VINDO AO SISTEMA DE GRAFOS--------" << endl;
    cout << "-->Criar Grafo (1)" << endl;
    cout << "-->Acessar Grafo (2)" << endl;
    cout << "-->ListarGrafos (3)" << endl;
    cout << "-->Sair do Sistema (4)" << endl;

    cin >> op;
    return op;
}

int acessoGrafo(int n_grafo, int size)
{
    system("clear");
    if (n_grafo > size)
    {
        return -1;
    }
    else
    {
        return n_grafo;
    }
}

int menu()
{
    int op = 0;
    cout << "---------------" << endl;
    cout << "-->Que operacao deseja realizar ?" << endl;
    cout << "-->Adicionar vertice (1)" << endl;
    cout << "-->Adicionar arresta (2)" << endl;
    cout << "-->Remover vertice (3)" << endl;
    cout << "-->Remover arresta (4)" << endl;
    cout << "-->Obter Grau do vertice (5)" << endl;
    cout << "-->Printar Grafo (6)" << endl;
    cout << "-->Voltar antes Menu (7)" << endl;

    cout << "\n Digite a opcao: ";
    cin >> op;
    system("clear");
    return op;
}
int main()
{
    int op = 1, v, v1, v2, cont_grafo, grafo;
    vector<Grafo> vg;
    Grafo g;
    vg.push_back(g);

    vg[0].addVertice(11);
    vg[0].addVertice(12);
    vg[0].addVertice(13);
    vg[0].addVertice(5);
    vg[0].addVertice(7);
    vg[0].addVertice(2);
    vg[0].addVertice(4);
    vg[0].addVertice(16);

    vg[0].addArresta(11, 12);
    vg[0].addArresta(11, 7);
    vg[0].addArresta(12, 13);
    vg[0].addArresta(12, 5);
    vg[0].addArresta(7, 2);
    vg[0].addArresta(7, 4);
    vg[0].addArresta(4, 16);
    //vg[0].printarGrafo();
    vg[0].BFS(11);
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
