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

     if (!file.is_open())
     {
          cout << "Nepodarilo sa otvoriť súbor!" << endl;
          return 1;
     }

     file >> pocetProduktov;
     PRODUKT *produkty = new PRODUKT[pocetProduktov];
}