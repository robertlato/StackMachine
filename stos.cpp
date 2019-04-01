/*
    Autor: Robert Latoszewski
    Data utworzenia: 20.03.2019

    Opis: 
        Maszyna stosowa wykonujaca podstawowe 
        operacje na stosie liczb calkowitych
*/
#include <iostream>

using namespace std;

struct stos 
{
    int liczba;
    stos *poprzedni;
};
stos *szczyt = nullptr; // ustawiam szczyt stosu
stos *wsk_wypisz = nullptr; // wskaznik do wypisywania stosu

//*****************************************************************************
//****** deklaracje funkcji *******//
void push(int n);
void pop();
void wypisz();
void zamien();
void suma2();
void przenies(int n);
int zamien_na_int(int n, char *tablica);
int potega(int baza, int pow);

//*****************************************************************************
//****** glowny program ********// 

int main ()
{
    char tab[10]; // poniewaz najwiekszy int sklada sie z 10 cyfr
    int i = 0;
    int x = 0;
    while (cin >> tab)
    {
        if (tab[0] >= '0' && tab[0] <= '9') 
        {
            while (tab[i] != '\0') // licze ile liczb jest w tablicy
            {
                i++;
            }
            push(zamien_na_int(i, tab));
        }
        else
        {
            switch(tab[0])
            {
                case 'p':
                    wypisz();
                    break;
                case 's':
                    zamien();
                    break;
                case 'x':
                    pop();
                    break;
                case '+':
                    suma2();
                    break;
                case 'r':
                    x = szczyt->liczba;
                    pop();
                    przenies(x);
                    break;
                case 'q':
                    return 0;
            }
        }
        i = 0;
    }
    return 0;
}

//*****************************************************************************
//**** definicje funkcji ******//

// dodaje liczbe do stosu
void push(int n)
{
    stos *nowy = new stos;
    nowy->liczba = n;
    nowy->poprzedni = szczyt;
    szczyt = nowy;
}

// usuwa liczbe ze stosu
void pop()
{
    if (!szczyt) cout << "Stos jest pusty!\n";
    else
    {
        stos *wsk = szczyt;
        szczyt = wsk->poprzedni;
        delete wsk;
    }
}

void wypisz()
{
    wsk_wypisz = szczyt;
    while (wsk_wypisz)
    {
        cout << wsk_wypisz->liczba << " ";
        wsk_wypisz = wsk_wypisz->poprzedni;
    }
    cout << endl;
}


// zamienia 2 liczby na szczycie stosu
void zamien()
{
    if (szczyt->poprzedni)
    {
        stos *wsk_pomoc = szczyt;
        szczyt = szczyt->poprzedni;
        wsk_pomoc->poprzedni = szczyt->poprzedni;
        szczyt->poprzedni = wsk_pomoc;
    }
}

// zdjemuje ze szczytu dwie liczby i dodaje na szczyt ich sume
void suma2()
{
    if (szczyt->poprzedni)
    {
        int i = szczyt->liczba + szczyt->poprzedni->liczba;
        pop();
        pop();
        push(i);
    }
    else cout << "Nie wystarczajaca ilosc elementow\n";
}

// przenosi liczbe ze szczytu o n pozycji w dol
void przenies(int n)
{
    stos *wsk_pomoc = szczyt;
    stos *wsk_pomoc2 = szczyt;
    if (n == 0 || n == 1);
    else 
    {
        for (n; n != 1; n--)
        {
            if (wsk_pomoc->poprzedni == nullptr && n > 2) break;
            else wsk_pomoc = wsk_pomoc->poprzedni;
        }
        if (wsk_pomoc->poprzedni == nullptr && n > 2);
        else
        {
            szczyt = szczyt->poprzedni;
            wsk_pomoc2->poprzedni = wsk_pomoc->poprzedni;
            wsk_pomoc->poprzedni = wsk_pomoc2;
        }
    }
}

int zamien_na_int(int n, char *tablica)
{
    int wynik = 0;
    int wykladnik = n-1;
    for (int i = 0; i < n; i++)
    {
        wynik += (tablica[i] - '0') * potega(10, wykladnik);
        wykladnik--;
    }
    return wynik;
}

// oblicza potegi liczb calkowitych nieujemnych 
int potega(int baza, int wykladnik)
{
    if (wykladnik == 0) return 1;
    else if (wykladnik == 1) return baza;
    else
    {
        int wynik = baza;
        for (int i = 1; i < wykladnik; i++) wynik = wynik*baza;
        return wynik;
    }
}