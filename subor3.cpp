#define  _CRT_SECURE_NO_WARNINGS
#define LEN 5

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

void swap(int*,int*);
int * generujPole(int *,int);
void tlacPole(int *,int);
void vytvorHeap(int *,int);
void siftUp(int*,int,int);
void heapSort(int *,int);

int main(){
	srand((unsigned int)time(NULL));
	int *pole= NULL;
	pole = generujPole(pole,LEN);
	cout << "HEAP SORT \"siftUp\"" << endl << endl;
	cout << "Pole pred:\t";
	tlacPole(pole, LEN);
	heapSort(pole,LEN);
	cout << "Pole po:\t";
	tlacPole(pole,LEN);
	cin.get();
	return 0;
}

//tlac pola
void tlacPole(int *pole, int len){
	int i;
	for(i=0; i<len;i++)
		cout << pole[i] << " ";
	cout << endl;
}

//alokacia pola a vyplnenie nahodnymi cislami
int * generujPole(int *pole, int len){
	int i;
	pole = new int[len];
	for(i=0; i<len;i++)
		pole[i] = rand()%100;
	return pole;
}

// funkcia na vymenu dvoch prvkov v poli
void swap(int *a, int *b){
	int tmp = *a;
	*a=*b;
	*b=tmp;
}

// funkcia, ktora vytvori v poli haldu, anglicky ekvivalent nazvu "heapify"
void vytvorHeap(int * pole, int len){
	// ideme stavat heap od vrcholu "siftUp"
	int iVrchol = 1; // najdem rodica poslednych dvoch prvkov
	while(iVrchol<len){
		siftUp(pole,0,iVrchol);
		iVrchol = iVrchol+1; // posuniem index, aby som mohol do heapu zaradit dalsi prvok
	}
}

// funkcia, ktora zaradi cislo ako potomka do poslednej vrstvy a postupne vymiena dvojice rodic-potomok az pokial nie je splnena vlastnost "heap"
void siftUp(int * pole, int start, int iVrchol){
	int child = iVrchol;
	int parent = -1;
	while(child >start){ // pokial som este stale v urovni pod korenom 
		parent = floor((child - 1) / 2); // vypocitaj index rodica
		if(pole[parent] < pole[child]){ // ak je potomok vacsi ako jeho rodic
			swap(pole+parent, pole+child); // prehodim rodica s potomkom
			child = parent;// aktualizujem potomka (byvaly rodic)
		}else return;
	}
}

// funkcia, ktora realizuje heapSort
void heapSort(int *pole, int len){
	// 1. krok - vytvorenie haldy z pola 
	vytvorHeap(pole,len);
	cout << "Heap:\t\t";
	tlacPole(pole,len);
	int end = len-1;
	while(end>0){ // vyberaj z heapu, zarad na koniec pola a nasledne zrekonstruuj zostavajucu haldu
		swap(pole+0, pole+end);
		vytvorHeap(pole,end--);
	}
}
