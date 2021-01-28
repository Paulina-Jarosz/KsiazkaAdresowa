//KSIAZKA ADRESOWA
#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ostream>

using namespace std;

struct Adresat;
struct Uzytkownik;
string wczytajLinie();
string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst);
char wczytajZnak();
int wczytajLiczbeCalkowita();
void dopiszAdresataDoPliku(Adresat adresat);
int wprowadzOsobe (vector <Adresat>& adresaci, int idZalogowanegoUzytkownika, int idOstatniegoAdresata);
Adresat pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami);
int wczytajPlik (vector <Adresat>& adresaci, int idZalogowanegoUzytkownika);
void pokazDaneWybranejOsoby(Adresat adresat);
void listaOsob (vector <Adresat> adresaci);
void znajdzOsobePoNazwisku (vector <Adresat> adresaci);
void znajdzOsobePoImieniu (vector <Adresat> adresaci);
bool zmianaNazwyPliku (fstream& nowyPlik, fstream& plik);
bool usunPlik (fstream& plik);
bool przepiszDoPliku (Adresat adresat);
bool zapisDoplikuPoEdycji (Adresat edytowanyAdresat, int identyfikatorID);
bool wyswietlDane (vector <Adresat> adresaci, int identyfikatorID);
bool sprawdzId (vector <Adresat>& adresaci, int idOsoby);
Adresat pojedynczyAdresat (vector <Adresat>& adresaci, int identyfikatorID);
int usunAdresataZPliku (Adresat edytowanyAdresat, int identyfikatorID);
int usunAdresata (vector <Adresat>& adresaci);
void wyswietlMenuEdycji();
void edytujAdresata (vector <Adresat>& adresaci);
void wyswietlMenuDlaUzytkownika ();
void dopiszUzytkownikaDoPliku(Uzytkownik uzytkownik);
bool sprawdzDlugoscCiagu (string ciagZnakow);
bool sprawdzCzyTakiUzytkownikIstnieje (vector <Uzytkownik>& uzytkownicy, string nazwaUzytkownika);
void rejestracja ( vector <Uzytkownik>& uzytkownicy );
bool zapisDoplikuPoEdycjiUzytkownika (vector <Uzytkownik>& uzytkownicy);
void zmianaHasla(vector <Uzytkownik>& uzytkownicy, int idZalogowanegoUzytkownika);
void wczytajPlikZUzytkownikami ( vector <Uzytkownik>& uzytkownicy);
void wyswietlLogowanie ();
void wyswietlMenuPoZalogowaniu (int idZalogowanegoUzytkownika, vector <Uzytkownik>& uzytkownicy);
int logowanie(vector <Uzytkownik>& uzytkownicy);
void menuGlowne(vector <Uzytkownik>& uzytkownicy, int idZalogowanegoUzytkownika);
int main();


string nazwaPliku = "KsiazkaAdresowa.txt";
string nazwaPliku2 = "ksiazkaAdresowa_tymczasowa.txt";
string nazwaPlikuZUzytkownikami = "uzytkownicyKsiazkiAdresowej.txt";

struct Adresat {
    int id = 0, idUzytkownika = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

struct Uzytkownik {
    int idUzytkownika = 0;
    string nazwaUzytkownika = " ", haslo = " ";
};

string wczytajLinie() {
    string wejscie = "";
    getline(cin, wejscie);
    return wejscie;
}

string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst) {
    if (!tekst.empty()) {
        transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
        tekst[0] = toupper(tekst[0]);
    }
    return tekst;
}

char wczytajZnak() {
    string wejscie = "";
    char znak  = {0};

    while (true) {
    cin.clear();
    cin.sync();
        getline(cin, wejscie);

        if (wejscie.length() == 1) {
            znak = wejscie[0];
            break;
        } else
            cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return znak;
}

int wczytajLiczbeCalkowita() {
    string wejscie = "";
    int liczba = 0;

    while (true) {
    cin.clear();
    cin.sync();
        getline(cin, wejscie);

        stringstream myStream(wejscie);
        if (myStream >> liczba)
            break;
        else
            cout << "To nie jest liczba. Wpisz ponownie. " << endl;
    }
    return liczba;
}

void dopiszAdresataDoPliku(Adresat adresat) {
    fstream plik;
    plik.open(nazwaPliku.c_str(), ios::out | ios::app);

    if (plik.good() == true) {
        plik << adresat.id << '|';
        plik << adresat.idUzytkownika << '|';
        plik << adresat.imie << '|';
        plik << adresat.nazwisko << '|';
        plik << adresat.numerTelefonu << '|';
        plik << adresat.email << '|';
        plik << adresat.adres << '|' << endl;
        plik.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}

int wprowadzOsobe (vector <Adresat>& adresaci, int idZalogowanegoUzytkownika, int idOstatniegoAdresata) {

    Adresat nowy;

    system("cls");
    cout << "--- DODAWANIE NOWEGO ADRESATA ---" << endl << endl;

    if (idOstatniegoAdresata == 0) {
        nowy.id = 1;
    } else {
        nowy.id = idOstatniegoAdresata + 1;
    }
    cout << "Podaj imie: ";
    cin.sync();
    nowy.imie = wczytajLinie();
    nowy.imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nowy.imie);
    cout << "Podaj nazwisko: ";
    nowy.nazwisko = wczytajLinie();
    nowy.nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nowy.nazwisko);
    cout << "Podaj nr telefonu: ";
    nowy.numerTelefonu = wczytajLinie();
    cout << "Podaj email: ";
    nowy.email = wczytajLinie();
    cout << "Podaj adres: ";
    nowy.adres = wczytajLinie();
    nowy.idUzytkownika = idZalogowanegoUzytkownika;

    adresaci.push_back( nowy );
    dopiszAdresataDoPliku(nowy);

    cout << endl << "Adresat zostal dodany" << endl;
    Sleep (1500);
    return idOstatniegoAdresata+1;
}

Adresat pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami) {

    Adresat adresat;
    string fragmentLinii = "";
    int iloscOdczytanychFragmentowLinii = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneAdresataOddzielonePionowymiKreskami.length(); pozycjaZnaku++) {
        if (daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku] != '|') {
            fragmentLinii += daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku];
        } else {
            switch (iloscOdczytanychFragmentowLinii) {
            case 1:
                adresat.id = atoi (fragmentLinii.c_str());
                break;
            case 2:
                adresat.idUzytkownika = atoi (fragmentLinii.c_str());
                break;
            case 3:
                adresat.imie = fragmentLinii;
                break;
            case 4:
                adresat.nazwisko = fragmentLinii;
                break;
            case 5:
                adresat.numerTelefonu = fragmentLinii;
                break;
            case 6:
                adresat.email = fragmentLinii;
                break;
            case 7:
                adresat.adres = fragmentLinii;
                break;
            }
            fragmentLinii = "";
            iloscOdczytanychFragmentowLinii++;
        }
    }
    return adresat;
}

int wczytajPlik (vector <Adresat>& adresaci, int idZalogowanegoUzytkownika) {

    Adresat adresat;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    int idOstatniegoAdresata = 0;

    fstream plik;
    plik.open(nazwaPliku.c_str(), ios::in);

    if (plik.good() == true) {
        while (getline(plik, daneJednegoAdresataOddzielonePionowymiKreskami)) {
            adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
            if(adresat.idUzytkownika == idZalogowanegoUzytkownika) {
                adresaci.push_back(adresat);
                idOstatniegoAdresata = adresat.id;
            } else {
                idOstatniegoAdresata = adresat.id;
            }
        }
        plik.close();
    }
    return idOstatniegoAdresata;
}

void pokazDaneWybranejOsoby(Adresat adresat) {

    cout << "ID: " << adresat.id << endl;
    cout << "Imie: " << adresat.imie << endl;
    cout << "Nazwisko: " << adresat.nazwisko << endl;
    cout << "Nr Tel: " << adresat.numerTelefonu << endl;
    cout << "email: " << adresat.email << endl;
    cout << "Adres: " << adresat.adres << endl;
    cout << endl;
}

void listaOsob (vector <Adresat> adresaci) {
    if (adresaci.size() == 0) {
        cout<<"Ksiazka adresowa jest pusta" << endl;
    } else {
        for (int i = 0; i < adresaci.size(); i++) {
            pokazDaneWybranejOsoby(adresaci[i]);
        }
    }
    system("pause");
}

void znajdzOsobePoNazwisku (vector <Adresat> adresaci) {

    string nazwisko;
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty()) {
        cout << " --- WYSZUKIWANIE ADRESAT\242W PO NAZWISKU ---" << endl << endl;
        cout << "Wyszukaj adresat\242w o nazwisku: ";
        nazwisko = wczytajLinie();

        nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwisko);

        for (int i = 0; i < adresaci.size(); i++) {
            if(adresaci[i].nazwisko == nazwisko) {
                pokazDaneWybranejOsoby(adresaci[i]);
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0) {
            cout<<"Nie ma takiego nazwiska w ksiazce adresowej."<<endl;
        } else {
            cout << endl << "Ilosc adresatow z nazwiskiem: >>> " << nazwisko << " <<<";
            cout << " w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
        }
    } else {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

void znajdzOsobePoImieniu (vector <Adresat> adresaci) {

    string imie;
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty()) {
        cout << " --- WYSZUKIWANIE ADRESAT\242W PO IMIENIU ---" << endl << endl;
        cout << "Wyszukaj adresat\242w o imieniu: ";
        imie = wczytajLinie();

        imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(imie);

        for (int i = 0; i < adresaci.size(); i++) {
            if(adresaci[i].imie == imie) {
                pokazDaneWybranejOsoby(adresaci[i]);
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0) {
            cout << "Nie ma takiego nazwiska w ksiazce adresowej." << endl;
        } else {
            cout << endl << "Ilosc adresatow z imieniem: >>> " << imie << " <<<";
            cout << " w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
        }
    } else {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

bool zmianaNazwyPliku (fstream& nowyPlik, fstream& plik) {

    if( rename("ksiazkaAdresowa_tymczasowa.txt", "KsiazkaAdresowa.txt" ) == 0 )
        return 0;
    else
        return 1;
}

bool usunPlik (fstream& plik) {
    if( remove( nazwaPliku.c_str() ) == 0 )
        return 0;
    else
        return 1;
}

bool przepiszDoPliku (Adresat adresat) {
    fstream nowyPlik;
    nowyPlik.open(nazwaPliku2.c_str(), ios::out | ios::app);

    if (nowyPlik.good() == true) {
        nowyPlik << adresat.id << '|';
        nowyPlik << adresat.idUzytkownika << '|';
        nowyPlik << adresat.imie << '|';
        nowyPlik << adresat.nazwisko << '|';
        nowyPlik << adresat.numerTelefonu << '|';
        nowyPlik << adresat.email << '|';
        nowyPlik << adresat.adres << '|' << endl;
        nowyPlik.close();

    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
    return true;
}

bool zapisDoplikuPoEdycji (Adresat edytowanyAdresat, int identyfikatorID) {

    Adresat adresat;
    string fragmentLinii;
    int iloscOdczytanychFragmentowLinii = 0;

    fstream plik;
    plik.open(nazwaPliku.c_str(), ios::in);
    fstream nowyPlik;
    nowyPlik.open(nazwaPliku2.c_str(), ios::out | ios::app);
    if( plik.is_open() ) {
        if(plik.good () == false) {
            cout << "Nie udalo sie otworzyc pliku.";
        }

        while(getline(plik, fragmentLinii, '|')) {
            switch (iloscOdczytanychFragmentowLinii) {
            case 0:
                adresat.id = atoi (fragmentLinii.c_str());

                break;
            case 1:
                adresat.idUzytkownika = atoi (fragmentLinii.c_str());
                break;
            case 2:
                adresat.imie = fragmentLinii;
                break;
            case 3:
                adresat.nazwisko = fragmentLinii;
                break;
            case 4:
                adresat.numerTelefonu = fragmentLinii;
                break;
            case 5:
                adresat.email = fragmentLinii;
                break;
            case 6:
                adresat.adres = fragmentLinii;
                break;
            }
            if (iloscOdczytanychFragmentowLinii >= 6) {
                if (adresat.id == identyfikatorID) {
                    przepiszDoPliku(edytowanyAdresat);
                    iloscOdczytanychFragmentowLinii = 0;
                } else {
                    przepiszDoPliku(adresat);
                    iloscOdczytanychFragmentowLinii = 0;
                }
            } else {
                iloscOdczytanychFragmentowLinii++;
            }
        }
    }
    plik.close();
    usunPlik(plik);
    nowyPlik.close();
    zmianaNazwyPliku(nowyPlik, plik);
    return true;
}

bool wyswietlDane (vector <Adresat> adresaci, int identyfikatorID) {

    string imie, nazwisko;
    char dowolnyZnak;
    int znalezionaOsoba = 0;
    for (vector<Adresat>:: iterator itr = adresaci.begin(); itr != adresaci.end(); ++itr) {
        if (itr -> id == identyfikatorID) {
            imie = itr -> imie;
            nazwisko = itr -> nazwisko;
            cout << imie << " " << nazwisko << endl << endl;
            znalezionaOsoba++;
            return true;
        }
    }
    if (znalezionaOsoba == 0) {
        cout << "Nie ma takiej osoby w ksiazce adresowej." << endl;
        return false;
    }
}

bool sprawdzId (vector <Adresat>& adresaci, int idOsoby) {

    for(int i = 0; i < adresaci.size(); i++) {
        if(adresaci[i].id == idOsoby) {
            return true;
        }
    }
    return false;
}

Adresat pojedynczyAdresat (vector <Adresat>& adresaci, int identyfikatorID) {
    Adresat pojedynczyAdresat;
    for (int i = 0; i < adresaci.size(); i++) {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); ++itr) {
            if (itr -> id == identyfikatorID) {
                pojedynczyAdresat.id = itr -> id;
                pojedynczyAdresat.idUzytkownika = itr -> idUzytkownika;
                pojedynczyAdresat.imie = itr -> imie;
                pojedynczyAdresat.nazwisko = itr -> nazwisko;
                pojedynczyAdresat.nazwisko = itr -> numerTelefonu;
                pojedynczyAdresat.email = itr -> email;
                pojedynczyAdresat.adres = itr -> adres;
            }
        }
    }
    return pojedynczyAdresat;
}

int usunAdresataZPliku (Adresat edytowanyAdresat, int identyfikatorID) {
    Adresat adresat;
    string fragmentLinii;
    int iloscOdczytanychFragmentowLinii = 0;
    int idOstatniegoAdresata = 0;

    fstream plik;
    plik.open(nazwaPliku.c_str(), ios::in | ios::out);
    fstream nowyPlik;
    nowyPlik.open(nazwaPliku2.c_str(), ios::out);
    if( plik.is_open() ) {
        if(plik.good () == false) {
            cout << "Nie udalo sie otworzyc pliku.";
        }

        while(getline(plik, fragmentLinii, '|')) {
            switch (iloscOdczytanychFragmentowLinii) {
            case 0:
                adresat.id = atoi (fragmentLinii.c_str());

                break;
            case 1:
                adresat.idUzytkownika = atoi (fragmentLinii.c_str());
                break;
            case 2:
                adresat.imie = fragmentLinii;
                break;
            case 3:
                adresat.nazwisko = fragmentLinii;
                break;
            case 4:
                adresat.numerTelefonu = fragmentLinii;
                break;
            case 5:
                adresat.email = fragmentLinii;
                break;
            case 6:
                adresat.adres = fragmentLinii;
                break;
            }
            if (iloscOdczytanychFragmentowLinii >= 6) {
                if (adresat.id != identyfikatorID) {
                    przepiszDoPliku(adresat);
                    idOstatniegoAdresata = adresat.id;
                    iloscOdczytanychFragmentowLinii = 0;
                } else {
                    iloscOdczytanychFragmentowLinii = 0;
                }
            } else {
                iloscOdczytanychFragmentowLinii++;
            }
        }
    }
    plik.close();
    nowyPlik.close();
    usunPlik(plik);
    zmianaNazwyPliku(nowyPlik, plik);

    return idOstatniegoAdresata;
}

int usunAdresata (vector <Adresat>& adresaci) {

    Adresat usuwanyAdresat;
    int identyfikatorID;
    char znak;
    int zaktualizowaneIDOstatniegoadresata = 0;

    cout << "Podaj id osoby kt\242r\245 chcesz usun\245\206: " << endl;
    cin >> identyfikatorID;
    bool czyJestTakieId = sprawdzId (adresaci, identyfikatorID);

    if (czyJestTakieId == true) {
        cout << "Adresat kt\242rego chcesz usun\245\206 to: " << endl;
        wyswietlDane(adresaci, identyfikatorID);

        for (int i = 0; i < adresaci.size(); i++) {
            if(adresaci[i].id == identyfikatorID) {
                usuwanyAdresat = pojedynczyAdresat(adresaci, identyfikatorID);
                cout << "Je\230li na pewno chcesz usun\245\206 ten kontakt to naci\230nij klawisz 't'" << endl;
                cout << "Aby przejsc do menu g³\242wnego nacisnij dowolny klawisz" << endl;
                znak = wczytajZnak();
                if (znak == 't' || znak =='T') {
                    zaktualizowaneIDOstatniegoadresata = usunAdresataZPliku(usuwanyAdresat, identyfikatorID);
                    adresaci.erase(
                    std::remove_if(adresaci.begin(), adresaci.end(), [&](Adresat const & adresaci) {
                        return adresaci.id == identyfikatorID;
                    }),
                    adresaci.end());
                    cout << "Osoba zosta\210a usuni\251ta z listy kontakt\242w!" << endl << endl;
                } else break;
            }
        }
    } else cout << "Nie ma takiego ID" << endl;
    cin.clear();
    system("pause");

    return zaktualizowaneIDOstatniegoadresata;
}

void wyswietlMenuEdycji() {

    cout << " --- EDYCJA KONTAKTU --- " << endl << endl;
    cout << " Kt\242re dane chcesz edytowa\206: " << endl;
    cout << " 1. imi\251" << endl;
    cout << " 2. nazwisko" << endl;
    cout << " 3. numerTelefonu" << endl;
    cout << " 4. email" << endl;
    cout << " 5. adres" << endl;
    cout << " 6. powr\242t do menu g\210\242wnego" << endl << endl;
}

void edytujAdresata (vector <Adresat>& adresaci) {
    {
        Adresat edytowanyAdresat;
        int idWybranegoAdresata = 0;
        char wybor;
        bool czyIstniejeAdresat = false;

        system("cls");
        if (!adresaci.empty()) {
            cout << ">>> EDYCJA WYBRANEGO ADRESATA <<<" << endl << endl;
            cout << "Podaj numer ID adresata u ktorego chcesz zmienic dane: ";
            idWybranegoAdresata = wczytajLiczbeCalkowita();

            for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
                if (itr->id == idWybranegoAdresata) {
                    czyIstniejeAdresat = true;
                    wyswietlDane (adresaci, idWybranegoAdresata);
                    wyswietlMenuEdycji();
                    wybor = wczytajZnak();

                    switch (wybor) {
                    case '1':
                        cout << "Podaj nowe imie: ";
                        itr->imie = wczytajLinie();
                        itr->imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr->imie);
                        edytowanyAdresat = pojedynczyAdresat(adresaci, idWybranegoAdresata);
                        pokazDaneWybranejOsoby(edytowanyAdresat);
                        cout << "Imi\251 zosta\210o zmienione "<< endl;
                        Sleep(1500);
                        zapisDoplikuPoEdycji(edytowanyAdresat, idWybranegoAdresata);
                        break;
                    case '2':
                        cout << "Podaj nowe nazwisko: ";
                        itr->nazwisko = wczytajLinie();
                        itr->nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr->nazwisko);
                        edytowanyAdresat = pojedynczyAdresat(adresaci, idWybranegoAdresata);
                        pokazDaneWybranejOsoby(edytowanyAdresat);
                        cout << "Nazwisko zosta\210o zmienione "<< endl;
                        Sleep(1500);
                        zapisDoplikuPoEdycji(edytowanyAdresat, idWybranegoAdresata);
                        break;
                    case '3':
                        cout << "Podaj nowy numer telefonu: ";
                        itr->numerTelefonu = wczytajLinie();
                        edytowanyAdresat = pojedynczyAdresat(adresaci, idWybranegoAdresata);
                        pokazDaneWybranejOsoby(edytowanyAdresat);
                        cout << "Numer telefonu zosta\210 zmieniony "<< endl;
                        Sleep(1500);
                        zapisDoplikuPoEdycji(edytowanyAdresat, idWybranegoAdresata);
                        break;
                    case '4':
                        cout << "Podaj nowy email: ";
                        itr->email = wczytajLinie();
                        edytowanyAdresat = pojedynczyAdresat(adresaci, idWybranegoAdresata);
                        pokazDaneWybranejOsoby(edytowanyAdresat);
                        cout << "Email zosta\210 zmieniony "<< endl;
                        Sleep(1500);
                        zapisDoplikuPoEdycji(edytowanyAdresat, idWybranegoAdresata);
                        break;
                    case '5':
                        cout << "Podaj nowy adres zamieszkania: ";
                        itr->adres = wczytajLinie();
                        edytowanyAdresat = pojedynczyAdresat(adresaci, idWybranegoAdresata);
                        pokazDaneWybranejOsoby(edytowanyAdresat);
                        cout << "Adres zosta\210 zmieniony "<< endl;
                        Sleep(1500);
                        zapisDoplikuPoEdycji(edytowanyAdresat, idWybranegoAdresata);
                        break;
                    case '6':
                        cout << endl << "Powrot do menu glownego" << endl << endl;
                        break;
                    default:
                        cout << endl << "Nie ma takiej opcji w menu! Powrot do menu glownego." << endl << endl;
                        break;
                    }
                }
            }
            if (czyIstniejeAdresat == false) {
                cout << endl << "Nie ma takiego adresata w ksiazce adresowej." << endl << endl;
            }
        } else {
            cout << "Ksiazka adresowa jest pusta." << endl << endl;
        }
        system("pause");
    }
}

void wyswietlMenuDlaUzytkownika () {

    cout << " --- KSI\244\275KA ADRESOWA ---  " << endl << endl;
    cout << " 1. Wprowad\253 osobe" << endl;
    cout << " 2. Wyszukaj po imieniu" << endl;
    cout << " 3. Wyszukaj po nazwiska" << endl;
    cout << " 4. Wy\230wietl wszystkich adresat\242w" << endl;
    cout << " 5. Usu\344 adresata" << endl;
    cout << " 6. Edytuj adresata" << endl;
    cout << " 7. Zmie\344 has\210o u\276ytkownika" << endl;
    cout << " 8. Wyloguj si\251" << endl;
    cout << " 9. Zako\344cz program" << endl;
    cout << endl;
}

void dopiszUzytkownikaDoPliku(Uzytkownik uzytkownik) {
    fstream plik;
    plik.open(nazwaPlikuZUzytkownikami.c_str(), ios::out | ios::app);

    if (plik.good() == true) {
        plik << uzytkownik.idUzytkownika << '|';
        plik << uzytkownik.nazwaUzytkownika << '|';
        plik << uzytkownik.haslo << '|' << endl;
        plik.close();

        cout << endl << "Uzytkownik zostal dodany" << endl;
        system("pause");
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}

bool sprawdzDlugoscCiagu (string ciagZnakow) {
    int dlugosc;
    dlugosc = ciagZnakow.length();
    if (dlugosc <5 ) {
        cout << "Ciag powinnien sk\210ada\206 si\251 z minimum 5 znak\242w " << endl << endl;
        system("pause");
        return false;
    } else
        return true;
}

bool sprawdzCzyTakiUzytkownikIstnieje (vector <Uzytkownik>& uzytkownicy, string nazwaUzytkownika) {

    int i=0;
    bool dlugoscLoginu = sprawdzDlugoscCiagu (nazwaUzytkownika);
    if (dlugoscLoginu == true ) {
        for(int i = 0; i < uzytkownicy.size(); i++) {
            if(uzytkownicy[i].nazwaUzytkownika == nazwaUzytkownika) {
                return true;
            }
        }
    }
    return false;
}

void rejestracja ( vector <Uzytkownik>& uzytkownicy ) {

    Uzytkownik nowy;
    string nazwaUzytkownika, haslo;
    system("cls");
    cout << "--- DODAWANIE NOWEGO U¯YTKOWNIKA ---" << endl << endl;

    if (uzytkownicy.empty() == true) {
        nowy.idUzytkownika = 1;
    } else {
        nowy.idUzytkownika = uzytkownicy.back().idUzytkownika + 1;
    }
    cout << "Podaj nazwe uzytkownika: ";
    cin.sync();
    nazwaUzytkownika = wczytajLinie();
    bool dlugoscLoginu = sprawdzDlugoscCiagu (nazwaUzytkownika);

    if (dlugoscLoginu == true ) {
        bool czyIstnieje = sprawdzCzyTakiUzytkownikIstnieje (uzytkownicy, nazwaUzytkownika);
        if(czyIstnieje == false) {
            nowy.nazwaUzytkownika = nazwaUzytkownika;
            cout << "Podaj haslo: ";
            cin.sync();
            haslo = wczytajLinie();
            bool dlugoscHasla = sprawdzDlugoscCiagu (haslo);
            if (dlugoscHasla == true ) {
                nowy.haslo = haslo;
                uzytkownicy.push_back( nowy );
                dopiszUzytkownikaDoPliku(nowy);
            } else {
                system("cls");
                cin.clear();
            }
        } else {
            cout << " Taki uzytkownik juz istnieje" << endl;
            system("pause");
        }
    }
}

bool zapisDoplikuPoEdycjiUzytkownika (vector <Uzytkownik>& uzytkownicy) {

    ofstream plik;
    plik.open(nazwaPlikuZUzytkownikami.c_str());
    if( plik.is_open() ) {
        for (int i = 0; i<uzytkownicy.size(); i++) {
            plik << uzytkownicy[i].idUzytkownika <<"|"<< uzytkownicy[i].nazwaUzytkownika <<"|"<< uzytkownicy[i].haslo << "|" << endl;
        }
        return true;
    }
    plik.close();
    return false;
}

void zmianaHasla(vector <Uzytkownik>& uzytkownicy, int idZalogowanegoUzytkownika) {
    string zmianaHasla;
    cout << "Podaj nowe has\210o (minimum 5 znak\242w): ";
    cin.sync();
    zmianaHasla = wczytajLinie();
    bool dlugoscHasla = sprawdzDlugoscCiagu (zmianaHasla);

    if (dlugoscHasla == true) {
        for (int i = 0; i < uzytkownicy.size(); i++) {
            for (vector < Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); ++itr) {
                if (itr-> idUzytkownika == idZalogowanegoUzytkownika) {
                    itr-> haslo = zmianaHasla;
                    zapisDoplikuPoEdycjiUzytkownika(uzytkownicy);
                    break;
                }
            }
        }
        cout << "Nast\245pi\210a zmiana has\210a! " << endl;
        system("pause");
    }
}

void wczytajPlikZUzytkownikami ( vector <Uzytkownik>& uzytkownicy) {

    Uzytkownik uzytkownik;
    string fragmentLinii;
    int iloscOdczytanychFragmentowLinii = 0;

    fstream plik;
    plik.open(nazwaPlikuZUzytkownikami.c_str(), ios::in);
    if(plik.good () == false) {
        cout << "Nie udalo sie otworzyc pliku.";
    }

    while(getline(plik, fragmentLinii, '|')) {
        switch (iloscOdczytanychFragmentowLinii) {
        case 0:
            uzytkownik.idUzytkownika = atoi (fragmentLinii.c_str());
            break;
        case 1:
            uzytkownik.nazwaUzytkownika = fragmentLinii;
            break;
        case 2:
            uzytkownik.haslo = fragmentLinii;
            break;
        }

        if (iloscOdczytanychFragmentowLinii >= 2) {
            uzytkownicy.push_back(uzytkownik);
            iloscOdczytanychFragmentowLinii = 0;
        } else {
            iloscOdczytanychFragmentowLinii++;
        }
    }
    plik.close();
}

void wyswietlLogowanie () {

    cout << " 1. Rejestracja " << endl;
    cout << " 2. Logowanie " <<endl;
    cout << " 9. Zamknij program " <<endl;
    cout << endl;
}

void wyswietlMenuPoZalogowaniu (int idZalogowanegoUzytkownika, vector <Uzytkownik>& uzytkownicy) {

    vector <Adresat> adresaci;
    vector <Adresat> adresaciUzytkownika;
    char wybor;
    int idOstatniegoAdresata = 0;

    idOstatniegoAdresata = wczytajPlik(adresaci, idZalogowanegoUzytkownika);

    while(idZalogowanegoUzytkownika > 0) {
        system("cls");
        wyswietlMenuDlaUzytkownika();
        cout << "Tw\242j wyb\242r: ";
        wybor = wczytajZnak();
        cout<<endl;

        switch (wybor) {
        case '1':
            idOstatniegoAdresata  = wprowadzOsobe(adresaci, idZalogowanegoUzytkownika, idOstatniegoAdresata);
            break;
        case '2':
            znajdzOsobePoImieniu(adresaci);
            break;
        case '3':
            znajdzOsobePoNazwisku(adresaci);
            break;
        case '4':
            system("cls");
            listaOsob(adresaci);
            break;
        case '5':
            idOstatniegoAdresata = usunAdresata(adresaci);
            break;
        case '6':
            system("cls");
            edytujAdresata(adresaci);
            break;
        case '7':
            zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
            break;
        case '8':
            system("cls");
            idZalogowanegoUzytkownika = 0;
            cout << endl << "Wylogowano u\276ytkownika" << endl << endl;
            Sleep (1500);
            menuGlowne(uzytkownicy, idZalogowanegoUzytkownika);
            break;
        case '9':
            exit(0);
        }
    }
}

int logowanie(vector <Uzytkownik>& uzytkownicy) {
    string nazwaUzytkownika, haslo;
    cout<<"Podaj nazwe: ";
    cin.sync();
    nazwaUzytkownika = wczytajLinie();
    int i=0;

    while (i < uzytkownicy.size()) {
        if(uzytkownicy[i].nazwaUzytkownika == nazwaUzytkownika) {
            for (int proby = 0; proby < 3; proby++) {
                cout << "Podaj haslo. Pozostalo prob " << 3-proby << ": ";
                cin.sync();
                haslo = wczytajLinie();
                if(uzytkownicy[i].haslo == haslo) {
                    cout << "Zalogowa\210e\230 si\251." << endl;
                    Sleep(1000);
                    wyswietlMenuPoZalogowaniu(uzytkownicy[i].idUzytkownika, uzytkownicy);
                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkowanika z takim loginem" << endl;
    Sleep(1500);
    return 0;
}


void menuGlowne(vector <Uzytkownik>& uzytkownicy, int idZalogowanegoUzytkownika) {
    char wybor;
    while(1) {
        if (idZalogowanegoUzytkownika == 0) {
            system("cls");
            wyswietlLogowanie();
            cout << "Tw\242j wyb\242r: ";
            wybor = wczytajZnak();

            if (wybor =='1') {
                rejestracja(uzytkownicy);
            } else if (wybor =='2') {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
            } else if (wybor =='9') {
                exit(0);
            }
        } else {
            wyswietlMenuPoZalogowaniu(idZalogowanegoUzytkownika, uzytkownicy);

        }
    }
}

int main() {

    vector <Uzytkownik> uzytkownicy;
    char wybor;
    int idZalogowanegoUzytkownika = 0;

    wczytajPlikZUzytkownikami(uzytkownicy);
    menuGlowne(uzytkownicy, idZalogowanegoUzytkownika);

    return 0;
}
