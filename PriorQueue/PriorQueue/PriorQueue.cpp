#include <stdio.h>
#include "PQueue.h"
#include <stdlib.h>
#include <memory.h>


void freeInfo( const void* );
PQINFO* allocInfo( int a, int b, int c );
void printInfo( const void* pInfo );
int compare( const void* p1, const void* p2 );

int main()
{
    //-wykreowac kolejke 20 - sto elementowa
    PQueue* q = PQInit( 20 );
    if( !q )
    {
        printf( "Queue initialization ERROR\n" );
        return 1;
    }
    //- dodac 6 elementow z roznymi priorytetami i w rownej kolejnosci priorytetow - wydrukowac
    for( int i = 1; i <= 6; i++ )
    {
        PQINFO* p = allocInfo( i, i + 1, i + 2 );
        if( !p )
        {
            printf( "Information allocation ERROR\n" );
            return 2;
        }
        if( !PQEnqueue( q, p, (int)rand()%50 ) )
        {
            printf( "Enqueuing ERROR\n" );
            return 3;
        }
    }
    printf( "Pierwsza kolejka\n" );
    PQPrint( q, 0, printInfo );
    //- usunac z kolejki(z najwiekszym priorytetem) - wydrukowac
    PQINFO* p1 = PQDequeue( q );
    if( !p1 )
    {
        printf( "Dequeueing ERROR\n" );
        return 4;
    }
    printf( "\nUsuniety element\n" );
    printInfo( p1 );
    freeInfo( p1 );
    printf( "\nDruga kolejka\n" );
    PQPrint( q, 0, printInfo );
    //- dodac dwa elementy - wydrukowac
    PQINFO* p = allocInfo( 40, 41, 42 );
    if( !p )
    {
        printf( "Information allocation ERROR\n" );
        return 5;
    }
    if( !PQEnqueue( q, p, 42 ) ) 
    {
        printf( "Enqueuing ERROR\n" );
        return 6;
    }
    PQINFO* element = allocInfo( 60, 61, 62 );
    if( !element ) 
    {
        printf( "Information allocation ERROR\n" );
        return 7;
    }
    if( !PQEnqueue( q, element, 62 ) ) 
    {
        printf( "Enqueuing ERROR\n" );
        return 8;
    }
    printf( "\nTrzecia kolejka\n" );
    PQPrint( q, 0, printInfo );

    //- wyszukac jeden elem
    if( PQFind( q, element, compare ) == POS_ERROR )
    {
        printf( "Element couldnt be found\n" );
        return 9;
    }

    //- zwiekszyc mu priorytet(unikalny) - wydrukowac
    if( PQSetPrior( q, element, 69, compare ) == PRIOR_ERROR )
    {
        printf( "Prior ERROR\n" );
        return 10;
    }
    printf( "\nKolejka po zwiekszeniu priorytetu:\n" );
    PQPrint( q, 0, printInfo );

    //- zmniejszyc priorytet innemu elementowi(unikalny) - wydrukowac
    if( PQSetPrior( q, p, 13, compare ) == PRIOR_ERROR )
    {
        printf( "Prior ERROR\n" );
        return 10;
    }
    printf( "\nKolejka po zmniejszeniu priorytetu\n" );
    PQPrint( q, 0, printInfo );

    //- usunac cala kolejke
    PQRelease( &q, freeInfo );
    return 0;
}
void freeInfo( const void* pInfo )
{
    //zwolnic pTab
    free( ((PQINFO*)pInfo )->pTab );
    //zwolnic info
    free( (PQINFO*)pInfo );
}

PQINFO* allocInfo( int a, int b, int c )
{
    //zaalokowac informacje 
    PQINFO* p = (PQINFO*)malloc(sizeof(PQINFO));
    //sprwdzic (jak blad to zwrocic NULL)
    if( !p )
        return NULL;
    //alokacja pTab (pole struktury)
    p->pTab = (int*)malloc( 2 * sizeof(int) );
    //sprawdzic (jesli blad to free na info i zwrocic NULL
    if( !(p->pTab) )
    {
        free( p );
        return NULL;
    }
    //wstawic a do klucza i b i c odpowiednio do zerowego i pierwszego elem tablicy
    p->pTab[0] = b;
    p->pTab[1] = c;
    p->key = a;
    //zwrocic wskaznik na info
    return p;
}

void printInfo( const void* pInfo )
{
    printf("Klucz=%d, pTab[0] = %d, pTab[1] = %d\n",
        ( (PQINFO*)pInfo )->key,
        ( (PQINFO*)pInfo )->pTab[0],
        ( (PQINFO*)pInfo )->pTab[1] );
}

int compare( const void* p1, const void* p2 )/*void(__cdecl* func1) (const void*), void(__cdecl* func2) (const void*)*/
{
    if( ((PQINFO*)p1)->key > ((PQINFO*)p2)->key ) return 1;
    if( ((PQINFO*)p1)->key < ((PQINFO*)p2)->key ) return -1;
    return 0;
}
//pliki txt tam gdzie sa pliki cpp