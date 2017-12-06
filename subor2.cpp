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
void siftDown(int*,int,int);
void heapSort(int *,int);

int main(){
	srand((unsigned int)time(NULL));
	int *pole= NULL;
	pole = generujPole(pole,LEN);
	cout << "HEAP SORT \"siftDown\"" << endl << endl;
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

// funkcia, ktora vytvori v poli haldu
void vytvorHeap(int * pole, int len){
	// ideme stavat heap od konca "siftDown"
	int iVrchol = floor((len-2)/2); // najdem rodica poslednych dvoch prvkov
	while(iVrchol>=0){
		siftDown(pole,len, iVrchol); // od prvku "vrchol" aktualizujem strukturu heapu
		iVrchol = iVrchol-1; // posuniem index, aby som mohol do heapu zaradit dalsi prvok
	}
	cout << "Heap:\t\t";
	tlacPole(pole,len);
}

// funkcia, ktora v poli vytvori haldu od vrcholu iVrchol az po len
void siftDown(int * pole, int len, int iVrchol){
	int iSwap = 0;
	while((iVrchol*2+1)<len){ // ak je LEFT uz mimo rozsah pola koncime cyklus
		iSwap= iVrchol;
		if(pole[iVrchol] < pole[iVrchol*2+1]) // ak je LEFT vacsi ako rodic
			iSwap=iVrchol*2+1; // ulozim index LEFT potomka
		if((iVrchol*2+2 < len) && (pole[iSwap] < pole[iVrchol*2+2])) // ak existuje RIGHT potomok a je vacsi ako LEFT
			iSwap=iVrchol*2+2;
		if(iSwap!=iVrchol){ // ak je treba swapovat
			swap(pole+iSwap, pole+iVrchol); // swap()
			iVrchol = iSwap; // posun vrcholu aby sme skontrolovali strukturu zostavajucej haldy
		}
		else{
			return; // ak ani LEFT ani RIGHT nie su vacsie koncime, halda je usporiadana
		}
	}
}

// funkcia, ktora realizuje heapSort
void heapSort(int *pole, int len){
	// 1. krok - vytvorenie haldy z pola 
	vytvorHeap(pole,len);
	int end = len-1;
	while(end>0){ // vyberaj z heapu, zarad na koniec pola a nasledne zrekonstruuj zostavajucu haldu
		swap(pole+0, pole+end);
		siftDown(pole, end, 0);
		end--;
	}
}
