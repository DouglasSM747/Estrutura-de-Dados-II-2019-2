#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <windows.h>
#include <stdlib.h>
#define ITER 10000000
using namespace std;


void merge(int arr[], int l, int m, int r) 
{ 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 = r - m; 

	/* criação de arrays temporários */
	int L[n1], R[n2]; 

	/* Copia os dados nos arrays temporarios L[] e R[] */
	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1+ j]; 

	/* Mesclar os arrays temporários de volta arr[l..r]*/
	i = 0; // Índice inicial do primeiro subarray 
	j = 0; // Índice inicial do segundo subarray 
	k = l; // Índice inicial do subarray mesclado 
	while (i < n1 && j < n2) 
	{ 
		if (L[i] <= R[j]) 
		{ 
			arr[k] = L[i]; 
			i++; 
		} 
		else
		{ 
			arr[k] = R[j]; 
			j++; 
		} 
		k++; 
	} 

	/* Copie os elementos restantes de L [], se houver qualquer */
	while (i < n1) 
	{ 
		arr[k] = L[i]; 
		i++; 
		k++; 
	} 

	/* Copie os elementos restantes de R [], se houver qualquer */
	while (j < n2) 
	{ 
		arr[k] = R[j]; 
		j++; 
		k++; 
	} 
} 

/* l é para o índice da esquerda e r é o índice da direita
sub-array de arr para ser classificado */
void mergeSort(int arr[], int l, int r) 
{ 
	if (l < r) 
	{ 
		// O mesmo que (l + r) / 2, mas evita estouro para l e h grandes 
		int m = l+(r-l)/2; 

		// Ordenar primeiro e segundo metades 
		mergeSort(arr, l, m); 
		mergeSort(arr, m+1, r); 

		merge(arr, l, m, r); 
	} 
} 


//funcao para determinar o tempo do algortimo
double performancecounter_diff(LARGE_INTEGER *a,
                               LARGE_INTEGER *b)
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(a->QuadPart - b->QuadPart) /
           (double)freq.QuadPart;
}

void printArray(int A[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", A[i]); 
	printf("\n"); 
}

/* Driver program to test above functions */
int main() 
{ 
	 // declaracoes para funcao merge
	int arr[ITER] = {};
	
	for (int i = 0; i < ITER;i++){
		arr[i] = rand() % ITER;
	}
	
	int arr_size = sizeof(arr)/sizeof(arr[0]); 
		
	 // declaracoes para medir tempo
    LARGE_INTEGER t_ini, t_fin;
    double secs;
	
	//abrir um arquivo para escrever resultado
    fstream fs("result.txt", ios::out | ios::app);
    fs.seekg(0L, ios::end);

    QueryPerformanceCounter(&t_ini);
    
		mergeSort(arr, 0, arr_size - 1); 
		
    QueryPerformanceCounter(&t_fin);
    
    // determina?ao do tempo e escritura no arquivo
    secs = performancecounter_diff(&t_fin, &t_ini); //retorna
    fs << "Tempo (s):" << secs << endl;             // escribir resultado en
    fs.close();
	
	
	return 0; 
}
