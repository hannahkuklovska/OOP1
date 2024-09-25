#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>

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
     PRODUKT kupene_produkty[50]; // statické pole produktov
     int pocet_kupenych_pr = 0;
     int mnozstvo_kupenych_produktov[50]; // staticky alokovane
};

void informacie_o_zakaznikovi(ZAKAZNIK &zakaznik)
{
     cout << "Zadajte vače meno: ";
     cin >> zakaznik.meno;
     cout << "Zadajte vaše priezvisko: ";
     cin >> zakaznik.priezvisko;

     // Kontrola zadaného rozpočtu (overenie, či je dobrého typu a nezáporný)
     cout << "Zadajte váš rozpočet: ";
     while (!(cin >> zakaznik.rozpocet) || zakaznik.rozpocet <= 0)
     {
          cin.clear();
          cin.ignore(100, '\n');
          cout << "Neplatný vstup, zadajte prosím platný rozpočet: ";
     }
}

void tlac_blocku(const ZAKAZNIK zakaznik)
{
     // Vypis blocku
     ofstream blocek("blocek.txt");

     double total = 0;

     if (blocek.is_open())
     {

          blocek << "~~~~~~~~~~~ Bloček ~~~~~~~~~ \n";
          blocek << "-----------------------------\n";
          blocek << "Meno a priezvisko zákazníka : " << zakaznik.meno << " " << zakaznik.priezvisko << endl;
          blocek << "-----------------------------\n";
          blocek << "Zakúpené produkty:\n";

          for (int i = 0; i < zakaznik.pocet_kupenych_pr; i++)
          {

               // vypocitanie celkovej sumy pre jednotlive pr (viac ks napr)
               double cena_spolu = zakaznik.kupene_produkty[i].cena * zakaznik.mnozstvo_kupenych_produktov[i];

               blocek << zakaznik.kupene_produkty[i].nazov << " - " << zakaznik.mnozstvo_kupenych_produktov[i] << " ks, cena za jednotku: " << zakaznik.kupene_produkty[i].cena << " €, spolu: " << cena_spolu << " €\n";

               total += cena_spolu; // celkova suma (zvysenie)
          }

          blocek << "-----------------------------\n";
          blocek << "Celkova vyplatená suma: " << total << " €\n";
          blocek << "Pôvodný rozpočet: " << zakaznik.rozpocet + total << " €\n";
          blocek << "Zostatkový rozpočet: " << zakaznik.rozpocet << " €\n";
          blocek << "-----------------------------\n";
          cout << "Ďakujeme za nákup, zoberte si bloček prosím" << endl;
     }

     // prípad ak sa nepodarí otvoriť súbor
     else
     {
          cout << " Nepodarilo sa otvoriť súbor pre vytvorenie bločku. " << endl;
     }

     // zatvorenie súboru

     blocek.close();
}

int main()
{
     // Načítanie produktov zo súboru
     ifstream file("fotoaparaty.txt");
     int pocetProduktov;
     int pocet_zobrazenychIDs;

     // testovanie, či sa súbor otvoril
     if (!file.is_open())
     {
          cout << "Nepodarilo sa otvoriť súbor!" << endl;
          return 1;
     }

     // priradenie

     // dynamicke alokovanie pola premennych typu PRODUKT, ich nacitavanie zo suboru
     file >> pocetProduktov;
     PRODUKT *produkty = new PRODUKT[pocetProduktov];

     // načítanie informácii o každom jednom produkte
     for (int i = 0; i < pocetProduktov; i++)
     {
          file >> produkty[i].ID;
          file >> produkty[i].nazov;
          file >> produkty[i].vyrobca;
          file >> produkty[i].pocet_na_sklade;
          file >> produkty[i].cena;
     }

     file.close();

     // informácie o zákazníkovi cez konzolu, zakaznik na vyzvu vpisuje

     ZAKAZNIK zakaznik;
     informacie_o_zakaznikovi(zakaznik);

     // volba produktu, pokračuje ak nie 3 (koniec) alebo zak nemá rozpočet
     int volba;
     while (volba != 3 && zakaznik.rozpocet > 0)
     {
          // ponuka na vyhľadávanie produktov podla:
          cout << "\nVyhľadávanie produktu podľa:\n1 - názvu\n2 - výrobcu\n3 - ukončiť nákup\nZadajte voľbu: ";
          while (!(cin >> volba) || volba < 1 || volba > 3)
          {
               cin.clear();
               cin.ignore(100, '\n');
               cout << "Neplatná voľba, skúste to znova: ";
          }

          cin.ignore();
          // zobrazene ID budu tvoriť set (kontrola spravnosti neskor)
          set<int> zobrazeneIDs;
          string hladany_nazov; // zadany nazov
          bool najdeny;         // overenie existencie

          // hladanie podla nazvu
          if (volba == 1)
          {
               // Podla nazvu
               cout << "Zadajte názov hľadaného produktu: ";
               getline(cin, hladany_nazov);
               najdeny = false;

               for (int i = 0; i < pocetProduktov; i++)
               {
                    if (produkty[i].nazov == hladany_nazov)
                    {
                         zobrazeneIDs.insert(produkty[i].ID); // pridanie do setu
                         cout << produkty[i].ID << ". " << produkty[i].nazov << " " << produkty[i].vyrobca << " " << "cena: " << produkty[i].cena << " ks na sklade: " << produkty[i].pocet_na_sklade << endl;
                         najdeny = true; // najdeny produkt
                    }
               }

               if (najdeny == false)
               {
                    cout << "Ľutujeme, produkt nebol nájdený. " << endl;
                    continue;
               }
          }
          while (!najdeny && volba != 3)
               ;

          if (najdeny == true)
          {
               int zvolene_ID;
               bool spravne_id = false;
               cout << "Zvoľte ID želaného produktu: ";
               do
               {
                    if (!(cin >> zvolene_ID))
                    // element nie je v sete, return value je true a skočí na koniec setu
                    {
                         cin.clear();
                         cin.ignore(100, '\n');
                         cout << "Neplatné ID, skúste to znova: ";
                    }
                    else if (zobrazeneIDs.find(zvolene_ID) == zobrazeneIDs.end()) // overenie, či vybrané ID je zobrazene
                    {
                         cout << "ID nie je na zozname zobrazených produktov, skúste to znova: ";
                    }
                    else
                    {
                         spravne_id = true; // spravne ID najdene
                    }
               } while (spravne_id == false);
          }
     }

     else if (volba == 2)
     {
          string hladany_vyrobca;
          bool najdeny = false; // nastavenie bool(u) spat na false

          do
          {

               cout << "Zadajte hľadaného výrobcu: ";
               getline(cin, hladany_vyrobca);

               najdeny = false;
               pocet_zobrazenychIDs = 0;

               for (int i = 0; i < pocetProduktov; i++)
               {
                    if (produkty[i].vyrobca == hladany_vyrobca)
                    {
                         zobrazeneIDs.insert(produkty[i].ID);
                         cout << produkty[i].ID << ". " << produkty[i].nazov << ", " << produkty[i].vyrobca << ", " << "cena: " << produkty[i].cena << " ks na sklade: " << produkty[i].pocet_na_sklade << endl;
                         najdeny = true;
                    }
               }

               if (najdeny == false)
               {
                    cout << "Ľutujeme, produkt nebol nájdený." << endl;
               }
          } while (!najdeny && volba != 3);

          if (najdeny == true)
          {
               int zvolene_ID;
               bool spravne_id = false;
               cout << "Zvoľte si ID želaného produktu: ";
               do
               {
                    if (!(cin >> zvolene_ID))
                    // element nie je v sete, return value je true a skočí na koniec setu
                    {
                         cin.clear();
                         cin.ignore(100, '\n');
                         cout << "Neplatné ID, skúste to znova: ";
                    }
                    else if (zobrazeneIDs.find(zvolene_ID) == zobrazeneIDs.end()) // overenie, či vybrané ID je zobrazene
                    {
                         cout << "ID nie je na zozname zobrazených produktov, skúste to znova: ";
                    }

                    else
                    {
                         spravne_id = true; // spravne ID najdene
                    }
               } while (spravne_id == false);
          }
     }

     // zákazník si zvolil ukončiť nákup
     else if (volba == 3)
     {
          cout << "Nákup bol ukončeny. " << endl;
          break;
     }

     if (volba == 1 || volba == 2)
     {
          int zvolene_ID;
          bool najdeny = false;
          bool spravne_id = false;

          cout << "Zvoľte ID želaného produktu: ";

          // cyklus na overenie ID
          do
          {

               if (!(cin >> zvolene_ID))
               // element nie je v sete, return value je true a skočí na koniec setu
               {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Neplatné ID, skúste to znova: ";
               }
               else if (zobrazeneIDs.find(zvolene_ID) == zobrazeneIDs.end()) // overenie, či vybrané ID je zobrazene
               {
                    cout << "ID nie je na zozname zobrazených produktov, skúste to znova: ";
               }

               else
               {
                    spravne_id = true; // spravne ID najdene
               }
          } while (spravne_id == false);

          for (int i = 0; i < pocetProduktov; i++)
          {
               if (produkty[i].ID == zvolene_ID)
               {
                    najdeny = true;

                    if (produkty[i].pocet_na_sklade > 0)
                    {
                         char odpoved;
                         int mnozstvo;

                         cout << "Vami vybratý produkt: " << produkty[i].nazov << "za " << produkty[i].cena << "€ " << endl;
                         cout << "Koľko kusov chcete kúpiť? ";
                         while (!(cin >> mnozstvo) || mnozstvo <= 0)
                         {
                              cin.clear();
                              cin.ignore(100, '\n');
                              cout << "Neplatné množstvo, skúste to znova: ";
                         }

                         // Kontrola, či je dostatok na sklade

                         if (mnozstvo <= produkty[i].pocet_na_sklade)
                         {
                              double total_price = produkty[i].cena * mnozstvo;

                              if (zakaznik.rozpocet >= total_price)
                              {
                                   cout << "Celková cena: " << total_price << " €. Máte záujem o kúpu tohto produktu? (A - áno, N - nie): ";
                                   cin >> odpoved;

                                   while (odpoved != 'A' && odpoved != 'a' && odpoved != 'N' && odpoved != 'n') // aj male a je pripustne
                                   {
                                        cout << "Neplatný vstup, zadajte A alebo N, prosím: ";
                                        cin >> odpoved;
                                   }

                                   if (odpoved == 'A' || odpoved == 'a')
                                   {

                                        zakaznik.kupene_produkty[zakaznik.pocet_kupenych_pr] = produkty[i];          // pridanie produktu do košíka
                                        zakaznik.mnozstvo_kupenych_produktov[zakaznik.pocet_kupenych_pr] = mnozstvo; // pridanie mnozstva
                                        zakaznik.pocet_kupenych_pr++;                                                // zvysenie poctu kupenych pr
                                        zakaznik.rozpocet -= produkty[i].cena;                                       // zmenšenie rozpočtu
                                        produkty[i].pocet_na_sklade -= mnozstvo;                                     // znizenie poctu opr na sklade o mnozstvo
                                        cout << "Predaj prebehol úspešne!\n Zostávajúci rozpočet: " << zakaznik.rozpocet << "€.\n";
                                   }
                                   else if (odpoved == 'N' || odpoved == 'n')
                                   {
                                        cout << "Nákup produktu bol zrušený.\n";
                                   }
                              }

                              else
                              {
                                   cout << "Ľutujeme, nemáte dostatočný rozpočet." << endl;
                                   break;
                              }
                         }

                         else
                         {
                              cout << "Ľutujeme, nemáme dostatok na sklade.\n ";
                         }
                    }
                    else
                    {
                         cout << "Ľutujeme, produkt nie je na sklade.\n ";
                    }
               }
          }
          // neexistuje taký produkt
          if (najdeny == false)
          {
               cout << "Ľutujeme, ID bolo zle zadané.\n";
          }
     }
}
// Vypis blocku
tlac_blocku(zakaznik);
delete[] produkty; // Vymazanie dynamicky alokovanej pamate

return 0;
}