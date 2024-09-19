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
     cout << "Zadajte vače meno: ";
     cin >> zakaznik.meno;
     cout << "Zadajte vaše priezvisko: ";
     cin >> zakaznik.priezvisko;
     cout << "Zadajte váš rozpočet: ";
     cin >> zakaznik.rozpocet;

     // volba produktu
     int volba = 0;
     while (volba != 3 && zakaznik.rozpocet > 0)
     {
          cout << "\nVyhĺadávanie produktu podľa:\n1 - názvu\n2 - výrobcu\n3 - ukončiť nákup\nZadajte voľbu: ";
          cin >> volba;
          cin.ignore();

          // hladanie podla nazvu
          if (volba == 1)
          {
               string hladany_nazov;
               cout << "Zadajte názov hľadaného produktu: ";
               getline(cin, hladany_nazov);

               bool najdeny = false;
               for (int i = 0; i < pocetProduktov; i++)
               {
                    if (produkty[i].nazov == hladany_nazov)
                    {
                         cout << produkty[i].ID << ". " << produkty[i].nazov << " " << produkty[i].vyrobca << " " << "cena: " << produkty[i].cena << " ks na sklade: " << produkty[i].pocet_na_sklade << endl;
                         najdeny = true;
                    }
               }

               if (najdeny == false)
               {
                    cout << "Produkt nebol nájdený. " << endl;
               }
          }
          // hladanie podla vyrobcu
          else if (volba == 2)
          {
               string hladany_vyrobca;
               cout << "Zadajte hľadaného výrobcu: ";
               getline(cin, hladany_vyrobca);

               bool najdeny = false;
               for (int i = 0; i < pocetProduktov; i++)
               {
                    if (produkty[i].vyrobca == hladany_vyrobca)
                    {
                         cout << produkty[i].ID << ". " << produkty[i].nazov << ", " << produkty[i].vyrobca << ", " << "cena: " << produkty[i].cena << " ks na sklade: " << produkty[i].pocet_na_sklade << endl;
                         najdeny = true;
                    }
               }

               if (najdeny == false)
               {
                    cout << "Ľutujem, produkt nebol nájdený." << endl;
               }
          }
          else if (volba == 3)
          {
               cout << "Nákup bol ukončeny. " << endl;
               break;
          }

          if (volba == 1 || volba == 2)
          {
               int zvolene_ID;
               cout << "Zvoľte ID želaného produktu: ";
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
                              cout << "Vami vybratý produkt: " << produkty[i].nazov << "za" << produkty[i].cena << "€" << endl;
                              cout << "Máte záujem o kúpu tohto produktu? (A - áno, N - nie):" << endl;
                              cin >> odpoved;

                              if (odpoved == 'A')
                              {
                                   if (zakaznik.rozpocet >= produkty[i].cena)
                                   {
                                        zakaznik.kupene_produkty[zakaznik.pocet_kupenych_pr++] = produkty[i];
                                        zakaznik.rozpocet -= produkty[i].cena;
                                        produkty[i].pocet_na_sklade--;
                                        cout << "Predaj prebehol úspešne!\n Zostávajúci rozpočet: " << zakaznik.rozpocet << "€." << endl;
                                   }

                                   else
                                   {
                                        cout << "Ľutujem, nemáte dostatočný rozpočet." << endl;
                                        break;
                                   }
                              }
                         }

                         else
                         {
                              cout << "Produkt nie je na sklade. " << endl;
                         }
                    }
               }
               if (najdeny == false)
               {
                    cout << "Zle zadané ID." << endl;
               }
          }
     }
     // Vypis blocku
     ofstream blocek("blocek.txt");

     double total = 0;

     if (blocek.is_open())
     {

          blocek << "^^^ Bloček ^^^\n";
          blocek << "Meno a priezvisko zákazníka : " << zakaznik.meno << " " << zakaznik.priezvisko << endl;
          blocek << "-----------------------------\n";
          blocek << "Zakúpené produkty:\n";

          for (int i = 0; i < zakaznik.pocet_kupenych_pr; i++)
          {
               blocek << zakaznik.kupene_produkty[i].nazov << " " << zakaznik.kupene_produkty[i].cena << " €\n";
               total += zakaznik.kupene_produkty[i].cena;
          }

          blocek << "-----------------------------\n";
          blocek << "Celkova vyplatená suma: " << total << " €\n";
          blocek << "Pôvodný rozpočet: " << zakaznik.rozpocet + total << " €\n";
          blocek << "Zostatkový rozpočet: " << zakaznik.rozpocet << " €\n";
          blocek << "-----------------------------\n";
          cout << "Bloček bol úspešne uložený do súboru" << endl;
     }

     else
     {
          cout << "Nepodarilo sa otvoriť súbor pre vytvorenie bločku. " << endl;
     }

     blocek.close();

     return 0;
}