#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct PRODUKT
{
     int ID;
     string nazov;
     string vyrobca;
     int pocet_na_sklade;
     double cena;
};

struct ZAKAZNIK
{
     string meno;
     int priezvisko;
     double rozpocet;
     PRODUKT kupene_produkty[50];
};

int main()
{
     // Načítanie produktov zo súboru
     ifstream file("fotoaparaty.txt");
     int pocetProduktov;
}