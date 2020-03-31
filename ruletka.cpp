#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <math.h>
#include <cmath>
#include <time.h>
#include <string>
using namespace std;

float ruletka(int N,float kasa, float stawka, string wariant)
{
    int n=36;
    float kasa_start=kasa;
    float kasa_stop=kasa;
    srand(time(0));
    float wygrana=0;
    if (wariant=="a")
    {
        n=38;
    }
    if (wariant=="e")
    {
        n=37;
    }
    for(int i=0;i<N;i++)
    {
        int x = 36*(rand()%1000)/1000; // liczba obstawiona przez gracza
        int y = n*(rand()%1000)/1000; // liczba wylosowana w ruletce
        if(x==y) // sprawdzenie, czy gracz trafił
        {
            kasa_stop+=35*stawka; //trafił, więc wygrywa 35-krotność
            wygrana+=1; // licznik wygranych
        }
        else
        {
            kasa_stop-=stawka; //nie trafił, azbieramy z portfela
        }
    }
    cout << "Stan portfela: ";
    cout << kasa_stop <<endl;
    cout << "% wygranych: ";
    cout << (100.*wygrana)/N<<endl;
    cout << "Stopa zwrotu: ";
    cout << 100*(kasa_start-kasa_stop)/(stawka*N)<<"%"<<endl;
    return 0;
}

int main()
{
    string wariant="";
    float kasa_start = 0;
    float stawka = 0;
    int iteracje = 1;
    bool a=true;
    while (a==true)
    {
        cout << "W jaką ruletkę dzisiaj zagramy?" << endl;
        cout << "u - uczciwa" << endl;
        cout << "e - europejska" << endl;
        cout << "a - amerykańska" << endl;
        cin >> wariant;
        if (wariant == "a" or wariant == "e" or wariant == "u")
        {
            a=false;
        }
        else
        {
            cout << "Nie ma takiego typu! Zadam pytanie jeszcze raz." << endl;
        }
    }
    cout << "Ile pieniędzy masz na starcie?" << endl;
    cin >> kasa_start;
    cout << "Ile chcesz stawiać w każdym rzucie?" << endl;
    cin >> stawka;
    cout << "W ilu zakładach chcesz wziąć udział?" << endl;
    cin >> iteracje;
    cout << ruletka(iteracje,kasa_start,stawka,wariant) << endl;
}


    
