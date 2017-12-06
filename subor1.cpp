#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct uzol {
    int data;
    struct uzol *next;
} UZOL;


// funkcia, ktora tlaci zretazeny zoznam
void print_list( UZOL *head )
{
    while( head != NULL ) {
        printf( "%d ", head->data );
        head = head->next;
    }
	printf("\n");
}

// funkcia, ktora pridava uzol do zretazeneho zoznamu na koniec
UZOL* pridajNaKoniec( UZOL *start, int newdata )
{
    UZOL *novy;
	UZOL *tmp = start;

    if( !(novy = (UZOL*)malloc(sizeof(UZOL)))) {
        fprintf( stderr, "Chyba pocas alokacie pamate \n" );
        exit(EXIT_FAILURE);
    }
	novy->data = newdata;
	novy->next = NULL;

    if(tmp){
		while( tmp->next != NULL ) 
			tmp = tmp->next;
		tmp->next = novy;
	}
	else{
		start = novy;
	}
	return start;	
}

// funkcia, ktora vymiena dva uzly v zretazenom zozname
void swap(UZOL **head, UZOL *a, UZOL *b){

	if( (*head) == NULL || a == NULL || b == NULL){  
		printf("\n Nieco nie je v poriadku \n");
		return;
	} 	

	UZOL * pre_a=NULL, *pre_b=NULL; // predchodcovia uzlov a,b
	UZOL * tmp = *head;

	// trivialne vyhladanie predchodcov
	while(tmp!=NULL){
		if((tmp)->next == a)
			pre_a = tmp;
		if((tmp)->next == b)
			pre_b = tmp;
		if(pre_a && pre_b)
			break;
		tmp=tmp->next;
	}

	// vymena predchodcov
	if(pre_a) 
		pre_a->next = b; 
	if(pre_b) 
		pre_b->next = a; 

	// vymena nasledovnikov uzlov a,b
	UZOL* temp = NULL;  
	temp = a->next;
	a->next = b->next;
	b->next = temp;

	// zmena zaciatku zoznamu, ak niektory z uzlov bol zaciatkom
	if((*head)==a){ 
		*head = b;
		return;
	}
	if((*head)==b) {
		*head = a;
		return;
	}
}


// bubbleSort v zozname
void bubbleSortZoznam( UZOL **start )
{
	UZOL * tmp= *start;			// odkladam zaciatok
	UZOL * pokial = NULL;		// pomocny uzol, sluzi na zapamatanie si uzlu, po ktory sme presli v predchadzajucej iteracii ...
								// ... meni sa nasledovne NULL, POSLEDNY, POSLEDNY - 1, POSLEDNY - 2, POSLEDNY - 3,......atd.
	UZOL * tmp2 = NULL;			// pomocny uzol pri swapovani

	if(tmp){ // test ci zoznam existuje
		while((*start)->next!=pokial){		// osetrenie, aby som neisiel zbytocne posledny krat cez cely zoznam, nakolko uz je utriedeny po N-1 prechodoch
			while(tmp->next!=pokial){		// v kazdej iteracii prechadzame vzdy o 1 uzol menej krat, mame uz istotu ze na konci zoznamu sa hromadia usporiadane prvky: to je myslienka bubbleSort-u
				if(tmp->data < tmp->next->data){		// ak je LEFT < RIGHT vtedy urobim swap()
					tmp2=tmp->next;			// odlozim nasledovnika uzla LEFT
					swap(start, tmp, tmp->next);		// urobim swap()
					tmp =tmp2;				// po swape sa musim dostat na tu istu poziciu ako pred swapom
				}
				tmp = tmp->next;				// posuniem sa o jeden uzol dopredu
			}
			pokial = tmp;					// po jednom prechode zoznamom aktualizujem uzol POKIAL (ten sa posuva stale z konca zoznamu dopredu)
			tmp=*start;						// nastavim sa znova na zaciatok zoznamu
		}
	}
}


// ------- FUNKCIE SUVISIACE S POLOM -------- //

// tlac pola
void printPole(int* pole, int len){
	int i;
	for(i=0;i<len;i++)
		printf("%d ", pole[i]);
	printf("\n");
}

// naplnenie pola nahodnymi cislami
void naplnPole(int* pole, int len){
	int i;
	for(i=0;i<len;i++){
		*(pole+i) = rand()%100;
	}
}

// bubbleSort v poli 
void bubbleSortPole(int * array, int size){
   for(int i = 0; i < size - 1; i++){
       for(int j = 0; j < size - i - 1; j++){
           if(array[j+1] < array[j]){
               int tmp = array[j + 1];
               array[j + 1] = array[j];
               array[j] = tmp;
           }   
       }   
   }   
}    


int main(void)
{
	// test bubbleSortu v poli	
	srand((unsigned int)time(NULL));

	printf("BubbleSort: Pole\n------\n");
	int *array = (int*)malloc(sizeof(int)*10);
	naplnPole(array,10); // napln pole

	printf("Neusporiadane ");
	printPole(array,10); // vytlac pole

	bubbleSortPole(array,10); // zotried pole

	printf("Usporiadane: ");
	printPole(array,10); // vytlac pole


	// test bubbleSortu v zretazenom zozname
	printf("\nBubbleSort: Zretazeny zoznam\n------\n");
    UZOL *zoznam=NULL;
    zoznam = pridajNaKoniec( zoznam, 3);
    zoznam = pridajNaKoniec( zoznam, 3);
    zoznam = pridajNaKoniec( zoznam, 2);
	zoznam = pridajNaKoniec( zoznam, 3);
	zoznam = pridajNaKoniec( zoznam, 10);
	zoznam = pridajNaKoniec( zoznam, 8);
	zoznam = pridajNaKoniec( zoznam, 150);
	zoznam = pridajNaKoniec( zoznam, 150);

    printf("Neusporiadany: ");
    print_list(zoznam);

    bubbleSortZoznam(&zoznam);

    printf("Usporiadany: ");
    print_list(zoznam);

	printf("\n");
	system("pause");

    return 0;
}

