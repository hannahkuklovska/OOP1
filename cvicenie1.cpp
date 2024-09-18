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
     string priezvisko;
     double rozpocet;
     PRODUKT kupene_produkty[50];
     int pocet_kupenych_pr = 0;
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

     for (int i = 0; i < pocetProduktov; i++)
     {
          file >> produkty[i].ID;
          file >> produkty[i].nazov;
          file >> produkty[i].vyrobca;
          file >> produkty[i].pocet_na_sklade;
          file >> produkty[i].cena;
     }

     file.close();

     // informácie o zákazníkovi

     ZAKAZNIK zakaznik;
     cout << "Zadajte vase meno:";
     cin >> zakaznik.meno;
     cout << "Zadajte vase priezvisko:";
     cin >> zakaznik.priezvisko;
     cout << "Zadajte vas rozpocet: ";
     cin >> zakaznik.rozpocet;

     // volba produktu
     int volba = 0;
     while (volba != 3)
     {
          cout << "\nVyhladavanie produktu podľa:\n1 - názvu\n2 - výrobcu\n3 - ukončiť nákup\nZadajte voľbu: ";
          cin >> volba;
          cin.ignore();

          // hladanie podla nazvu
          if (volba == 1)
          {
               string hladany_nazov;
               cout << "Zadajte nazov produktu: ";
               getline(cin, hladany_nazov);

               bool najdeny = false;
               for (int i = 0; i < pocetProduktov; i++)
               {
                    if (produkty[i].nazov == hladany_nazov)
                    {
                         cout << produkty[i].ID << ". " << produkty[i].nazov << " " << produkty[i].vyrobca << " " << produkty[i].cena << "ks na sklade" << produkty[i].pocet_na_sklade << endl;
                         najdeny = true;
                    }
               }

               if (najdeny == false)
               {
                    cout << "Produkt nebol najdeny. " << endl;
               }
          }
          // hladanie podla vyrobcu
          if (volba == 2)
          {
               string hladany_vyrobca;
               cout << "Zadajte hladaneho vyrobcu: ";
               getline(cin, hladany_vyrobca);

               bool najdeny = false;
               for (int i = 0; i < pocetProduktov; i++)
               {
                    if (produkty[i].vyrobca == hladany_vyrobca)
                    {
                         cout << produkty[i].ID << ". " << produkty[i].nazov << " " << produkty[i].vyrobca << " " << produkty[i].cena << "ks na sklade" << produkty[i].pocet_na_sklade << endl;
                         najdeny = true;
                    }
               }

               if (najdeny == false)
               {
                    cout << "Produkt nebol najdeny." << endl;
               }
          }
          else if (volba == 3)
          {
               cout << "Nakup bol ukonceny. " << endl;
               break;
          }
     }

     if (volba == 1 || volba == 2)
     {
          int zvolene_ID;
          cout << "Zvolte ID chceneho produktu: ";
          cin >> zvolene_ID;

          bool najdeny = false;
          for (int i = 0; i < pocetProduktov; i++)
          {
               if (produkty[i].ID == zvolene_ID)
               {
                    najdeny = true;

                    if (produkty[i].pocet_na_sklade > 0)
                    {
                         char odpoved;
                         cout << "Vybrany produkt: " << produkty[i].nazov << "za" << produkty[i].cena << "€" << endl;
                         cout << "Mate zaujem o kupu tohto produktu? (A - áno, N - nie):" << endl;
                         cin >> odpoved;

                         if (odpoved == 'A')
                         {
                              if (zakaznik.rozpocet >= produkty[i].cena)
                              {
                                   zakaznik.kupene_produkty[zakaznik.pocet_kupenych_pr++] = produkty[i];
                                   zakaznik.rozpocet -= produkty[i].cena;
                                   produkty[i].pocet_na_sklade--;
                                   cout << "Predaj prebehol uspesne! Zostavajuci rozpocet: " << zakaznik.rozpocet << "€." << endl;
                              }

                              else
                              {
                                   cout << "Nemate dostatocny rozpopcet." << endl;
                              }
                         }
                    }

                    else
                    {
                         cout << "Produkt nie je na skalde. ";
                         break;
                    }
               }

               if (najdeny == false)
               {
                    cout << "Zle zadane ID." << endl;
               }
          }
     }
}