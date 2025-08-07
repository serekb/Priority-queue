#ifndef GLOBAL_H
#define GLOBAL_H

typedef struct
{
    int key;
    int* pTab;
} PQInfo;

#define PQINFO PQInfo

#endif
//-->>> Modul Kolejki PIORRYTETOWEJ <<---
//UWAGA: mozna uzywac calloc() oraz 
//       NALEZY ZACHOWAC TAKIE NAZWY FUNKCJI, TYPOW I POL STRUKTUR JAK PODANO!!!!!!! - inaczej nie sprawdzam 


//Kolejke priorytetowa mozna zrealizowac na dwa sposoby.
//Pierwsza przy pomocy tablicy - a dokladniej stogu ale odwrotnego niz w sortowaniu
//stogowym - to znaczy najwiekszy element(albo element ktorego priorytet jest najwiekszy) jest
//jako pierwszy w tablicy.Tutaj w stogu kazdy element jest wiekszy od swoich potomkow.
//Potomkiem elementu i jest element 2 * i + 1 oraz 2 * i + 2
//Druga metoda to  w postaci drzewa zrownazonego BST - trudniejsze gdyz trzeba dodatkowo
//przywracac zrownowazenie drzewa.
//
//Nalezy zrealizowac kolejke priorytetowa, przechwujaca dowolne elementy(elementy typu definiowanego
//    przez uzytkownika) z okreslonym priorytetem przy pomocy stogu!.
//
//    - Operacja usuwania z kolejki polega na usunieciu pierwszego(zerowego) elementu z kolejki,
//    zmniejszajac ilosc elementow w kolejce oraz nastepnie wkopiowac ostatni z kolejki w pierwsza pozycje
//    i przywrocic warunek stogu metoda UpdateDown() z sortowania(zmodyfikowana jak do
//        sortowania malejacego - bo priorytety od najwiekszego  do najmniejszego)
//
//    - Operacja  dodania nowego elementu->dodajemy na koncu, zwiekszajac ilosc elementow w kolejce
//    i uaktualniamy stog ale od dolu do gory - UpdateUp(podobnie jak w dol ale latwiej bo jest tylko jeden rodzic)
//
//    - zdefiniowac podobnie jak w przypadku FIFO oraz modulu Listy plik global.h z deklaracja typu
//    definiowanego przez uzytkownika(jaka informacja bedzie przechowywana w kolejce)
//    Prosze tu uzyc tego samego typu co w poprzendich projektach(struktura zalozona z int - a oraz wsk na int
//        czyli tablicy dynamicznej int - ow)
//
//
//    //==============  global.h ====================================//
//
//    typedef struct
//{
//    int  nKey;
//    int* pTab; // moze byc dwuelementowa tablica
//} PQInfo;    // PQINFO - the user identyfier
//
//#define PQINFO PQInfo    // nazwy PQINFO - uzywac WSZEDZIE - NAWET W PROGRAMIE TESTUJACYM!
//
//
////==============   KONIEC global.h  ============================//
//
//
////================================================================
//// Modul MA SIE NAZYWAC:  PQueue - PQueue.h oraz  PQueue.cpp 
//
////---------------------------------
////  PQueue.h
//
//// zdefiniowac dwie stale:
////   - PRIOR_ERROR  jako minimalna wartosc calkowita int_min
////   - POS_ERROR    jako wartosc ujemna np -1 (indeks tablicy jakiego nie ma!)
//
//
//typedef struct    // zachowac oryginalne nazwy!!!!!!  
//{
//    // pInfo;       // Ptr to user info  
//    // nPrior;      // prior value (int) for the user info  
//} PQItem;         // type of the queue item
//
//
//typedef struct   // zachowac oryginalne nazwy!!!!!!
//{
//    // pPQueue     // kolejka realizowana w postaci stogu  (dynamiczna tablica) wskaznikow na PQItem
//    // nPQSize      // rozmiar calkowity kolejki priorytetowej
//    // nPQCurrSize  // ilosc elelemntow w kolejce (jednoczensie indeks pierwszego wolnego miejsc w kolejce) 
//
//} PQueue;
//
////dopisac parametry!!!!
////wszedzie parameetr kolejka
//PQInit();     // kreuje kolejke o zadanym rozmiarze i zwraca wskaznik do niej lub NULL gdy blad    PQ* parametr rozmiar
//PQisEmpty();  // zwraca 0 lub 1 - kolejka pusta/nie pusta
//PQSize();     // zwraca ilosc elementow w kolejce // return wyrazenie pytajnikowe
//PQMaxPrior(); // zwraca najwiekszy priorytet w kolejce (z zerowej pozycji) lub PRIOR_ERROR
//PQEnqueue();  // wstawia do kolejki informacje o zadanym priorytecie, zwraca 0 (niepowodzenie) lub 1 (powodzenie)
//PQDequeue();  // zwraca informacje o najwyzszym priorytecie lub NULL gdy niepowodzenie
//PQClear();    // czysci cala kolejke zwalniajac pamiec alokowana przez uzytkownika (na info), nie znana struktura do zwolnienia 
//// dlatego przekazac trzeba funkcje uzytkownika do zwolnienia pamieci przez parametr 
//PQRelease();  // zwraca w parametrze we-wy NULL (kolejka) usuwajac wszyskto wczesniej (czyszczenie kolejki) // wywoluje clear po sprwadzeniach
//PQPrint();    // drukuje w porzadku preorder (rekurencyjnie) od zadanej pozycji, aby wydrukowac info uzytkownika przekazac 
//// trzeba funkcje drukujaca ta informacje. Dodatkowo, drukuje priorytet w okraglych nawiasach oraz pozycje w 
//// kolejce w kwadratowych nawiasach
//
//PQSetPrior(kolejka, informcja, nowy priorytet, adres funkcji porownujacej); // ustawia nowy priorytet dla zadanej informacji uzytkownika, nie znana struktura informacji, ktora trzeba wyszukac
//// dlatego nalezy przekazac funkcje porownujaca informacje uzytkownika. Funkcja zwraca poprzedni priorytet lub PRIOR_ERROR 
//PQsetPrior(1 linijka z findem, jesli priorytet wiekszy to uaktualniam w gore, jesli mniejszy to w dol); // ustawia nowy priorytet dla informacji uzytkownika bedacej na zadanej pozycji w kolejce (indeks w tablicy),
//// Funkcja zwraca poprzedni priorytet.!!! W przypadku bledu zwraca PRIOR_ERROR 
//
//PQGetPrior(); // zwraca priorytet informacji uzytkownika w kolejce lub PRIOR_ERROR, nie znana struktura informacji, ktora trzeba wyszukac
//// dlatego nalezy przekazac funkcje porownujaca informacje uzytkownika  
//PQgetPrior(); // zwraca priorytet informacji uzytkownika z zadanej pozycji w kolejce lub PRIOR_ERROR
//
//PQFind();     // zwraca indeks wyszukiwanej informacji uzytkownika, nie znana struktura informacji uzytkownika dlatego
//// przekazac trzeba funkjce porownujaca informacje uzytkownika
//// Zwaraca POS_ERROR jesli nie ma info w kolejce
//
//
////-----------------------------------------
//// pomocnicze w implementacji 2 funkcje !!!!
//void UpdateDown();  // update heap down between index l and p  <--- modified Update() from HeapSort 
//void UpdateUp();    // update heap up between index l and p  
//
////===================================================================
////===================================================================
//
//UpdateDown()
//{
//    // analogicznie jak w sortowaniu stogowym ale zmienionic
//    // przetestowac najpierw ta funkcje w sortowaniu malejacym!!!
//    //    (wybiera sie element o wiekszym priorytcie)
//    // tak aby pierwszy element mial najwiekszy proirytet
//}
//
//UpdateUp()
//{
//    // analog jak w UpdateDown
//    // tylko uaktualnienie w gore stogu i jest tylko jeden rodzic 
//}
//
//PQDeQueue()
//{
//    // zwraca informacje z indeksu 0
//    // wpisac ostatni do 0-wego
//    // uaktualnic w dol
//}
//
//PQEnQueue(kolejka, priorytet, info)
//{
//    // wstawic na koncu!! current size i potem currentsize +1
//    // uaktualnic w gore // porownac ze stogowym (tam jest  w dol) // znalezc wyrazenie dla potomka
//    //funkcja int
//}
//
//
//
////========================== w pliki z funkcja main()
//
//// naglowek funkcji drukujacej info uzytkownika (parametr typu const void* )
//// naglowek funkcji porownujacej info uzytkowniak. Zwraca -1 pierwszy mniejszy, 1 jesli pierwszy wiekszy else 0.
////          (parametry const void* )
//// naglowek funkcji zwalniajacej pamiec (parametr typu const void* )
//
//// implementacja tych trzech funkcji
//
////---test: dopiero na koniec
//-wykreowac kolejke 20 - sto elementowa
//- dodac 6 elementow z roznymi priorytetami i w rownej kolejnosci priorytetow - wydrukowac
//- usunac z kolejki(z najwiekszym priorytetem) - wydrukowac
//- dodac dwa elementy - wydrukowac
//- wyszukac jeden elem
//- zwiekszyc mu priorytet(unikalny) - wydrukowac
//- zmniejszyc priorytet innemu elementowi(unikalny) - wydrukowac
//- usuac cala kolejke
//
//- przetestowac jak bedzie sie zachowywac modul jesli powtorza sie priorytety niektorych elementow
//(zmienic priorytet np na maksymalny - powtorzy sie i sciagnac dwa razy, po kazdym drukowanie)
//
//1. wykreowac program
//2. dodawc modul kolejki priorytetowej // zabezpieczyc
//3. global
//4. zmienic nawe typu i stalych preprocesora
//5. skopiowac naglowki funkcji alokuj¹cych, zwalniaj¹cych, drukuj¹cych
//6. implementacje tych funkcji
//7. zmienic nazwy typów
//8. zdefiniowac naglowek funkcji compare() dwa elemtny  // parametry  2 razy const void* // porowynywanie kluczy // -1, 1, 0 // 3 linijki
//9. implementacja porowanujacej
//10. definiowac stale wszystkie typy i naglowki funkcji w pliku PQueue.h // struktyry, int_min, 
//11. pqinit
//12. pqclear i PQRelease
//13. pqsize i PQMaxPrior
//14. pqisempty
//15. sprawdzic debuggerem
//16. pozostale funkcje bez setow i getow najpierw enqueue
//17. sety i gety
//
//PQprint(
//    if(!q || !printItem) return;
//if(i >= pQSize(q) ) return;
//    printItem(q->pQueue[i].pInfo);
//    printf(" (%0d [%d] \n", p->pQueue[i].nPrior, i);
//    PQPrint(q, 2 * i + 1, printItem);
//    PQPrint(q, 2 * i + 2, printItem);
//
//    drukowanie preorder(lewe, prawe, korzen)
//
//    ))
