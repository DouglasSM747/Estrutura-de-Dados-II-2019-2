#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

class Grafo
{
public:
    map<int, vector<int>> m; //Cria as vertices
    int addVertice(int u)
    {
        int continuar = 0;
    	for (auto x : this->m)
        {
            if (x.first == u)
            {
                continuar += 1;
                break;
            }
        }

    	if(continuar==0){
    		 this->m[u].push_back({});                                        //add uma vertice vazia
    		 this->m[u].erase(find(this->m[u].begin(), this->m[u].end(), 0)); //remove o elemento vazio adicionado
    		 return 1;
    	}else{
    		return -1;
    	}


    }

    int removeArresta(int u, int v)
    {
    	int continuar = 0;

    	        for (auto x : this->m)
    	        {
    	            if (x.first == u)
    	            {
    	                continuar += 1;
    	                break;
    	            }
    	        }

    	        for (auto x : this->m)
    	        {
    	            if (x.first == v)
    	            {
    	                continuar += 1;
    	                break;
    	            }
    	        }
    	if(continuar==2){
            //Grafo digrafo, apaga u <-> v
            this->m[u].erase(find(this->m[u].begin(), this->m[u].end(), v));
            this->m[v].erase(find(this->m[v].begin(), this->m[v].end(), u));
            return 1;
    	}else{
    		return -1;
    	}

    }

    int removeVertice(int u)
    {
        int continuar = 0;
    	for (auto x : this->m)
        {
            if (x.first == u)
            {
                continuar += 1;
                break;
            }
        }
    	if(continuar==1){

            this->m.erase(u); //esvazia a lista de adj de u

            for (auto i : this->m) // busca por todos a lista de vertice e exclue u
            {
                this->m[i.first].erase(find(this->m[i.first].begin(), this->m[i.first].end(), u));
            }
            return 1;
    	}else{
    		return -1;
    	}

    }

    int addArresta(int u, int v)
    {
        int continuar = 0;

        for (auto x : this->m)
        {
            if (x.first == u)
            {
                continuar += 1;
                break;
            }
        }

        for (auto x : this->m)
        {
            if (x.first == v)
            {
                continuar += 1;
                break;
            }
        }

        if (continuar >= 2)
        {
            this->m[v].push_back(u);
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

        for (auto x : this->m) //verifica se o elemento existe
        {
            if (x.first == u)
            {
                continuar = true;
                break;
            }
        }

        if (continuar)
        { //se existir retorna o tamanho de sua lista
        	return this->m[u].size();
        }else{
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

int menu()
{
    int op = 0;
    cout << "---------------" << endl;
    cout << "-->Que operacao deseja realizar ?" << endl;
    cout << "-->Criar grafo (1)" << endl;
    cout << "-->Adicionar arresta (2)" << endl;
    cout << "-->Adicionar vertice (3)" << endl;
    cout << "-->Remover vertice (4)" << endl;
    cout << "-->Remover arresta (5)" << endl;
    cout << "-->Obter Grau do vertice (6)" << endl;
    cout << "-->Printar Grafo (7)" << endl;
    cout << "\n Digite a opcao: ";
    cin >> op;
    system("clear");
    return op;
}

int main()
{
    Grafo g;
    int op,v,v1,v2;
    while (1 == 1)
    {
    	system("clear");
        op = menu();
        if (op > 0 && op <= 7)
        {
            switch (op)
            {
            case 1:
                cout << "\n Grafo criado com sucesso";
                break;
            case 2:
                system("clear");
                cout << "\n Digite o valor da vertice1  seguido do valor vertice1 (ex: 1 2):  ";
                cin >> v1 >> v2;
                v = g.addArresta(v1, v2);
                if (v == 1)
                    cout << "\n Arresta adicionada com sucesso";
                else
                    cout << "\n Erro ao adicionar arresta";
                break;
            case 3:
                system("clear");
                cout << "\n Digite o valor do vertice:  ";
                cin >> v1;
                v = g.addVertice(v1);
                if (v == 1)
                    cout << "\n Vertice adicionada com sucesso";
                else
                    cout << "\n Erro ao adicionar vertice";
                break;
            case 4:
                system("clear");
                cout << "\n Digite o valor do vertice a ser apagado:  ";
                cin >> v1;
                v = g.removeVertice(v1);
                if (v == 1)
                    cout << "\n Vertice apagada com sucesso";
                else
                    cout << "\n Erro ao apagar vertice";
                break;\
            case 5:
                system("clear");
                cout << "\n Digite as arrestas a serem apagadas:  ";
                cin >> v1 >> v2;
                v = g.removeArresta(v1,v2);
                if (v == 1)
                    cout << "\n Arrestas apagadas com sucesso";
                else
                    cout << "\n Erro ao apagar as arrestas";
                break;
            case 6:
                system("clear");
                cout << "\n Digite o vertice que deseja obter o grau:  ";
                cin >> v1;
                v = g.obterGrau(v1);
                if (v == -1)
                    cout << "\n Vertice nao existe";
                else
                    cout << "\n O grau do vertice:  " << v;
                break;
            case 7:
                system("clear");
                g.printarGrafo();
                break;
            }
        }else
        {
            break;
        }
        cout << "\n\n Deseja continuar ? (Not: 8, Yes: 1):  ";
        cin >> op;
    }

    return 0;
}
