#ifndef PQUEUE
#define PQUEUE
#include <limits.h>
#include "Global.h"
#define PRIOR_ERROR INT_MIN
#define POS_ERROR -1

typedef struct    // zachowac oryginalne nazwy!!!!!!  
{
    PQINFO* pInfo;       // Ptr to user info  
    int nPrior;      // prior value (int) for the user info  
} PQItem;         // type of the queue item

typedef struct   // zachowac oryginalne nazwy!!!!!!
{
    PQItem** pPQueue;    // kolejka realizowana w postaci stogu  (dynamiczna tablica) wskaznikow na PQItem
    int nPQSize;     // rozmiar calkowity kolejki priorytetowej
    int nPQCurrSize;  // ilosc elelemntow w kolejce (jednoczensie indeks pierwszego wolnego miejsc w kolejce) 
} PQueue;

PQueue* PQInit( int nSize ); // done
int PQisEmpty( PQueue* q ); //done
int PQSize( PQueue* q ); //done
int PQMaxPrior( PQueue* q ); // ?? bo nie dziala update
int PQEnqueue( PQueue* q, PQINFO* p, int prior ); // chyba done
PQINFO* PQDequeue( PQueue* q ); // chyba done ale poszukaj optymalizacji
void PQClear( PQueue* q, void(__cdecl* freeMem) ( const void*)  ); //????
void PQRelease( PQueue** q, void(__cdecl* freeMem) ( const void* ) ); // wywoluje cleara wiec ??
void PQPrint( PQueue* q, int position, void(__cdecl* printInfo) ( const void* ) ); // done
int PQSetPrior( PQueue* q, PQINFO* p, int newPrior, int(__cdecl* compare) ( const void*, const void* )); //done
int PQsetPrior( PQueue* q, int prior, int position ); // done
int PQGetPrior( PQueue* q, PQINFO* p, int(__cdecl* compare) ( const void*, const void* )); // done
int PQgetPrior( PQueue* q, int position ); // done
int PQFind( PQueue* q, PQINFO* p, int(__cdecl* compare) ( const void*, const void* )); // done

//!!
//!!!
//uwaga do updateup indeks rodzica
//petla z dwoma warunkami
//petla w update up musi otrzymac -1 (jakis warunek inny niz (i-1)/2)


//utworzyc nowy wskaznik i zapisac pqinfo*
//usunac pqitem od 0
//zwolnic pamiec w mainie?

//clear
//freemem od dequeue dopoki nie pusta
//current size na 0
//wypelnic tablice nullami

//release
//clear plus zwalniam tablice plus zwalniam wskaznik q

#endif 
