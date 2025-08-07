#include "PQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define MAXSIZE 100

void UpdateDown( int l, int r, PQItem** pPQueue );
void UpdateUp( int l, int r, PQItem** pPQueue );

PQueue* PQInit( int nSize )
{
    if( nSize > MAXSIZE )
        nSize = MAXSIZE;
    if( nSize < 1 ) return NULL;
    PQueue* p = (PQueue*)calloc( 1, sizeof(PQueue) );
    if( !p ) 
        return NULL;
    p->pPQueue = (PQItem**)calloc( nSize, sizeof(PQItem*) );
    if( !(p->pPQueue) )
        return NULL;
    p->nPQSize = nSize;
    return p;
}

int PQisEmpty( PQueue* q )
{
    return !q || !(q->nPQCurrSize);
}

int PQSize( PQueue* q )
{
    return (q)? q->nPQCurrSize : 0;
}

int PQMaxPrior( PQueue* q )
{
    return ( PQisEmpty(q) )? PRIOR_ERROR : q->pPQueue[0]->nPrior;
}

int PQEnqueue( PQueue* q, PQINFO* p, int prior )
{
    if( !q )
        return 0;
    PQItem* r = (PQItem*)calloc( 1, sizeof(PQItem) );
    if( !r )
        return 0;
    r->pInfo = p;
    r->nPrior = prior;
    q->pPQueue[PQSize(q)] = r;
    if( q->nPQCurrSize >= q->nPQSize )
    {
        //printf( "ERROR: queue overload\n" );
        return 0;
    }
    //!!!!pod jakm warunkime
    if( PQSize( q ) > 1 )
        UpdateUp( 0, PQSize(q), q->pPQueue );
    q->nPQCurrSize++;
    return 1;
    //w main alokacja na pqinfo
    //wywolam enqueue na pamiec z priorytetem
    //zawsze tablice wskaznikow nigdy struktur
}

PQINFO* PQDequeue( PQueue* q ) 
{
    if( PQisEmpty(q) ) return NULL;
    PQINFO* val = q->pPQueue[0]->pInfo;
    PQItem* item = q->pPQueue[0];
    int ix = --q->nPQCurrSize;
    if( ix > 0 )
    {
        q->pPQueue[0] = q->pPQueue[ix];
    }
    q->pPQueue[ix] = NULL;


 // !!pod jakim warunkiem
    if( ix > 1 )
        UpdateDown( 0, ix - 1, q->pPQueue );
    free( item );
    return val;
}

void PQClear( PQueue* q, void(__cdecl* freeMem) (const void*) )
{
    if( !q || !freeMem )
    {
        printf("\nERROR: queue or function not existing\n");
        return;
    }
    while( !PQisEmpty(q) )
        freeMem( PQDequeue(q) );//nieefekt!!!!
}

void PQRelease( PQueue** q, void(__cdecl* freeMem) (const void*) )
{
    if( !q || !*q )
    {
        printf("queue or function not existing");
        return ;
    }
    PQClear( *q, freeMem );
    //!!!!!!!!!!!!!!!!!
    free( *q );
    q = NULL;
}

void PQPrint( PQueue* q, int i, void(__cdecl* printItem) (const void*)) // i to pozycja
{
    if( !q || !printItem )
    {
        printf( "queue or function not existing" );
        return;
    }
    if( i >= PQSize(q) ) 
        return;
    printItem( q->pPQueue[i]->pInfo );
    printf( " %0d [%d] \n", q->pPQueue[i]->nPrior, i );
    PQPrint( q, 2 * i + 1, printItem );
    PQPrint( q, 2 * i + 2, printItem );
}

int PQSetPrior( PQueue* q, PQINFO* p, int newPrior, int(__cdecl* compare) (const void*, const void*) )
{
    return PQsetPrior( q, newPrior, PQFind( q, p, compare ) );//??
}

int PQsetPrior( PQueue* q, int newPrior, int i )
{
   /* if ( i == POS_ERROR || i == PRIOR_ERROR ) 
        return PRIOR_ERROR;
    if( !q )
    {
        printf("queue not existing");
        return PRIOR_ERROR;
    }*/
    int oldPrior = PQgetPrior( q, i );
    if( oldPrior == PRIOR_ERROR ) return PRIOR_ERROR;
    q->pPQueue[i]->nPrior = newPrior;
    if( newPrior > oldPrior )
        UpdateUp( i, PQSize(q) - 1, q->pPQueue );
    else if(newPrior < oldPrior)
        UpdateDown( 0, i, q->pPQueue );
    return oldPrior;
}

int PQGetPrior( PQueue* q, PQINFO* p, int(__cdecl* compare) (const void*, const void*) )
{
    return PQgetPrior( q , PQFind( q, p, compare ) );
}

int PQgetPrior( PQueue* q, int position )
{
    if( position == POS_ERROR || position == PRIOR_ERROR || 
        position>=PQSize( q ) || position<0 )
        return PRIOR_ERROR;
    if( PQisEmpty(q)/* || position>PQSize(q)*/ )
        return PRIOR_ERROR;
    int prior = q->pPQueue[position]->nPrior;
    return prior;
}

int PQFind( PQueue* q, PQINFO* p, int(__cdecl* compare) ( const void*, const void* ) )
{
    if( !q ) return PRIOR_ERROR;//PRIOR_E
    if ( !compare ) return POS_ERROR;//POS_E
    for( int i = 0; i < PQSize( q ); i++)
        if( !compare( p, q->pPQueue[i]->pInfo ) )
            return i;
    return POS_ERROR;
}

void UpdateDown( int l, int r, PQItem** pPQueue )
{
    if( !&pPQueue || l>r || (2*l+1)>r )
        return;
    int i = l;
    int j = 2 * i + 1;
    PQItem* x = pPQueue[i];
    while( j <= r ) {
        if( j < r && pPQueue[j]->nPrior < pPQueue[j + 1]->nPrior)
            j++;
        if( x->nPrior >= pPQueue[j]->nPrior )
            break;
        pPQueue[i] = pPQueue[j];
        i = j;
        j = 2 * i + 1;
    }
    pPQueue[i] = x;
}

void UpdateUp( int l, int r, PQItem** pPQueue )
{
    if( l >= r ) return;
    int i = r;
    int j = (i+1)/2-1;
    PQItem* x = pPQueue[i];
    while( i > l && x->nPrior > pPQueue[j]->nPrior )
    {
            pPQueue[i] = pPQueue[j];
            i = j;
            j=(i+1)/2-1;
    }
    pPQueue[i] = x;
}
    //drukowanie preorder(lewe, prawe, korzen)