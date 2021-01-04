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

struct Adresat
{
int id = 0;
string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

string wczytajLinie()
{
    string wejscie = "";
    getline(cin, wejscie);
    return wejscie;
}

int znajdzOstatnieId (vector <Adresat>& adresaci)
{
    int numer;
    for (auto itr = adresaci.begin(); itr != adresaci.end(); ++itr) {
        numer=itr->id;
    }
    return numer;
}

void wprowadzOsobe (vector <Adresat>& adresaci) {

    Adresat nowy;
    int ostatnieID=znajdzOstatnieId(adresaci);
    int id=ostatnieID+1;
    cout<<"Podaj imie (imię powinno zaczynać sie od dużej litery): ";
    cin.sync();
    getline( cin, nowy.imie );
    cout<<"Podaj nazwisko (imię powinno zaczynać sie od dużej litery): ";
    cin.sync();
    getline( cin, nowy.nazwisko );
    cout<<"Podaj nr telefonu: ";
    cin.sync();
    getline( cin, nowy.numerTelefonu);
    cout<<"Podaj email: ";
    cin.sync();
    getline( cin, nowy.email );
    cout<<"Podaj adres: ";
    cin.sync();
    getline( cin, nowy.adres );
    nowy.id=id;
    adresaci.push_back( nowy );

    cout<<"Osoba dodana do książki adresowej "<<endl;
    Sleep (1000);

    fstream plik;
    plik.open("ksiazkaTest.txt", ios::app);
    if( plik.is_open() ) {
        plik<<nowy.id<<"|"<<nowy.imie<<"|"<<nowy.nazwisko<<"|"<<nowy.numerTelefonu<<"|"<<nowy.email<<"|"<<nowy.adres<<"|"<<endl;
    }
    plik.close();
}

void wczytajPlik(vector <Adresat>& adresaci) {

    Adresat adresat;
    string fragmentLinii;
    int iloscOdczytanychFragmentowLinii=0;

    fstream plik;
    plik.open("ksiazkaTest.txt", ios::in);
    if(plik.good () == false) {
        cout << "Nie udalo sie otworzyc pliku.";
    }

    while(getline(plik, fragmentLinii, '|')) {
        switch (iloscOdczytanychFragmentowLinii) {
        case 0:
            adresat.id = atoi (fragmentLinii.c_str());
            break;
        case 1:
            adresat.imie = fragmentLinii;
            break;
        case 2:
            adresat.nazwisko = fragmentLinii;
            break;
        case 3:
            adresat.numerTelefonu = fragmentLinii;
            break;
        case 4:
            adresat.email = fragmentLinii;
            break;
        case 5:
            adresat.adres = fragmentLinii;
            break;
        }

        if (iloscOdczytanychFragmentowLinii>=5) {
            adresaci.push_back(adresat);
            iloscOdczytanychFragmentowLinii=0;
        } else {
            iloscOdczytanychFragmentowLinii++;
        }
    }
    plik.close();
}

void listaOsob ( const vector <Adresat>& adresaci) {

    if (adresaci.size() == 0) {
        cout<<"Ksiazka adresowa jest pusta"<<endl;
    } else {
        for (int i=0; i<adresaci.size(); i++) {
            cout <<"ID: "<<adresaci[i].id<<endl; // to nie koniecznie wyswietlac
            cout<<"Imie: "<<adresaci[i].imie<<endl;
            cout<<"Nazwisko: "<<adresaci[i].nazwisko<<endl;
            cout<<"Nr Tel: "<<adresaci[i].numerTelefonu<<endl;
            cout<<"email: "<<adresaci[i].email<<endl;
            cout<<"Adres: "<<adresaci[i].adres<< endl;
            cout<<endl;
        }
    }
    system("pause");
}

void znajdzOsobePoNazwisku (const vector <Adresat>& adresaci) {

    string nazwisko;
    cout<<"Podaj nazwisko: ";
    cin.sync();
    getline(cin,nazwisko );
    int znalezioneNazwisko = 0;

    for (int i = 0; i<adresaci.size(); i++) {
        if(adresaci[i].nazwisko == nazwisko) {
            cout<< adresaci[i].id<<endl;
            cout<< adresaci[i].nazwisko<<" "<<adresaci[i].imie<<endl;
            cout<< adresaci[i].numerTelefonu<<endl;
            cout<< adresaci[i].email<<endl;
            cout<< adresaci[i].adres<<endl;
            znalezioneNazwisko++;
        }
    }
    if (znalezioneNazwisko == 0) {
        cout<<"Nie ma takiego nazwiska w ksiazce adresowej."<<endl;
    }
    system("pause");
}

void znajdzOsobePoImieniu (const vector <Adresat>& adresaci) {

    string imie;
    cout<<"Podaj imie: ";
    cin.sync();
    getline(cin,imie );
    int znalezioneNazwisko = 0;

    for (int i = 0; i<adresaci.size(); i++) {
        if(adresaci[i].imie == imie) {
            cout<< adresaci[i].id<<endl;
            cout<< adresaci[i].imie<<" "<<adresaci[i].nazwisko<<endl;
            cout<< adresaci[i].numerTelefonu<<endl;
            cout<< adresaci[i].email<<endl;
            cout<< adresaci[i].adres<<endl;
            znalezioneNazwisko++;
        }
    }
    if (znalezioneNazwisko == 0) {
        cout<<"Nie ma takiego nazwiska w ksiazce adresowej."<<endl;
    }
    system("pause");
}

bool zapisDopliku (vector <Adresat>& adresaci){

    ofstream plik;
    plik.open("ksiazkaTest.txt");
    cout<<adresaci.size();
    if( plik.is_open() ) {
    for (int i = 0; i<adresaci.size(); i++) {
        plik<<adresaci[i].id<<"|"<<adresaci[i].imie<<"|"<<adresaci[i].nazwisko<<"|"<<adresaci[i].numerTelefonu<<"|"<<adresaci[i].email<<"|"<<adresaci[i].adres<<"|"<<endl;
        }
    return true;
    }

    plik.close();
    return false;
}

bool wyswietlDane (vector <Adresat>& adresaci, int identyfikatorID) {

    string imie, nazwisko;
    char dowolnyZnak;
    int znalezionaOsoba=0;
    for (vector<Adresat>:: iterator itr = adresaci.begin(); itr != adresaci.end(); ++itr) {
        if (itr->id == identyfikatorID) {
            imie=itr->imie;
            nazwisko =itr->nazwisko;
            cout<<imie<<" "<<nazwisko<<endl<<endl;
            znalezionaOsoba++;
            return true;
        }
    }
    if (znalezionaOsoba == 0) {
        cout<<"Nie ma takiej osoby w ksiazce adresowej."<<endl;
        return false;
    }

}

void usunAdresata (vector <Adresat>& adresaci) {

    int identyfikatorID;
    char znak;

    cout<<"Podaj id osoby którą chcesz usunąć: "<<endl;
    cin>>identyfikatorID;

    wyswietlDane(adresaci, identyfikatorID);

    for (int i = 0; i<adresaci.size(); i++) {
        if(adresaci[i].id == identyfikatorID) {
            cout<<"Je\230li na pewno chcesz usun\245\206 ten kontakt to naciśnij klawisz 't', a je\230li chcesz powr\242ci\206 do menu g\210\242wnego naci\230nij dowolny klawisz :"<<endl;
            cin>>znak;
            if (znak == 't') {
                adresaci.erase(
                std::remove_if(adresaci.begin(), adresaci.end(), [&](Adresat const & adresaci) {
                    return adresaci.id == identyfikatorID;
                }),
                adresaci.end());
                cout<<"Osoba zosta\210a usuni\251ta z listy kontakt\242w!"<<endl<<endl;
                zapisDopliku(adresaci);
            } else break;
        }
    }
    cin.clear();
    system("pause");
}

void zmianaImienia (vector <Adresat>& adresaci, int identyfikatorID) {

    string zmiana;
    cout<<"wprowadz zmian\251: "<<endl;
    cin.sync();
    getline(cin, zmiana);

    for (int i = 0; i<adresaci.size(); i++) {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); ++itr) {
            if (itr->id == identyfikatorID){
                itr->imie = zmiana;
                break;
            }
        }
    }
    zapisDopliku(adresaci);
    cout<<"nastąpiła zmiana imienia na "<<zmiana<<endl;
    system("pause");
}

void zmianaNazwiska (vector <Adresat>& adresaci, int identyfikatorID) {

    string zmiana;
    cout<<"wprowadz zmian\251: "<<endl;
    cin.sync();
    getline(cin, zmiana);

    for (int i = 0; i<adresaci.size(); i++) {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); ++itr) {
            if (itr->id == identyfikatorID){
                itr->nazwisko = zmiana;
                break;
            }
        }
    }
    zapisDopliku(adresaci);
    cout<<"nastąpiła zmiana nazwiska na "<<zmiana<<endl;
    system("pause");
}

void zmianaNumeruTelefonu (vector <Adresat>& adresaci, int identyfikatorID) {

    string zmiana;
    cout<<"wprowadz zmian\251: "<<endl;
    cin.sync();
    getline(cin, zmiana);

    for (int i = 0; i<adresaci.size(); i++) {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); ++itr) {
            if (itr->id == identyfikatorID){
                itr->numerTelefonu = zmiana;
                break;
            }
        }
    }
    zapisDopliku(adresaci);
    cout<<"nastąpiła zmiana numeru telefonu na "<<zmiana<<endl;
    system("pause");
}

void zmianaEmail (vector <Adresat>& adresaci, int identyfikatorID) {

    string zmiana;
    cout<<"wprowadz zmian\251: "<<endl;
    cin.sync();
    getline(cin, zmiana);

    for (int i = 0; i<adresaci.size(); i++) {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); ++itr) {
            if (itr->id == identyfikatorID){
                itr->email = zmiana;
                break;
            }
        }
    }
    zapisDopliku(adresaci);
    cout<<"nastąpiła zmiana emaila na "<<zmiana<<endl;
    system("pause");
}

void zmianaAdresu (vector <Adresat>& adresaci, int identyfikatorID) {

    string zmiana;
    cout<<"wprowadz zmian\251: "<<endl;
    cin.sync();
    getline(cin, zmiana);

    for (int i = 0; i<adresaci.size(); i++) {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); ++itr) {
            if (itr->id == identyfikatorID){
                itr->adres = zmiana;
                break;
            }
        }
    }
    zapisDopliku(adresaci);
    cout<<"nastąpiła zmiana adresu na "<<zmiana<<endl;
    system("pause");
}

void wyswietlMenuEdycji(){

    cout<<" --- EDYCJA KONTAKTU --- "<<endl<<endl;
    cout<<" Które dane chcesz edytować: "<<endl;
    cout<<" 1. imi\251"<<endl;
    cout<<" 2. nazwisko"<<endl;
    cout<<" 3. numerTelefonu"<<endl;
    cout<<" 4. email"<<endl;
    cout<<" 5. adres"<<endl;
    cout<<" 6. powr\242t do menu g\210\242wnego"<<endl<<endl;
}

void edytujAdresata (vector <Adresat>& adresaci) {

    char numerZmiany;
    int identyfikatorID=0;
    string imie, nazwisko;

    cout<<"Podaj id osoby którą chcesz edytowac: "<<endl;
    cin>>identyfikatorID;

    wyswietlDane(adresaci, identyfikatorID);
    cin.clear();
    wyswietlMenuEdycji();

    cout<<"Twój wybór: ";
    cin>>numerZmiany;

    if (numerZmiany =='1') {
        zmianaImienia(adresaci, identyfikatorID);
    } else if (numerZmiany =='2') {
        zmianaNazwiska (adresaci, identyfikatorID);
    } else if (numerZmiany =='3') {
        zmianaNumeruTelefonu(adresaci, identyfikatorID);
    } else if (numerZmiany =='4') {
        zmianaEmail(adresaci, identyfikatorID);
    } else if (numerZmiany =='5') {
        zmianaAdresu(adresaci, identyfikatorID);
    } else if (numerZmiany =='6') {
        system("cls");
    }
}

void wyswietlMenuGlowne () {

    cout<<" --- KSIĄŻKA ADRESOWA ---  "<<endl<<endl;
    cout<<" 1. Wprowadz osobe"<< endl;
    cout<<" 2. Wyszukaj po imieniu"<<endl;
    cout<<" 3. Wyszukaj po nazwiska" <<endl;
    cout<<" 4. Wyswietl wszystkich adresat\242w" <<endl;
    cout<<" 5. Usu\344 adresata" <<endl;
    cout<<" 6. Edytuj adresata" <<endl;
    cout<<" 9. Zako\344cz program" <<endl;
    cout<<endl;
}

int main() {

    vector <Adresat> adresaci;
    char wybor;

    wczytajPlik(adresaci);

    while(1) {
        system("cls");
        wyswietlMenuGlowne();
        cout<<"Tw\242j wyb\242r: ";
        cin>> wybor;

        if (wybor =='1') {
            wprowadzOsobe(adresaci);
        } else if (wybor =='2') {
            znajdzOsobePoImieniu(adresaci);
        } else if (wybor =='3') {
            znajdzOsobePoNazwisku(adresaci);
        } else if (wybor =='4') {
            system("cls");
            listaOsob(adresaci);
        } else if (wybor =='5') {
            usunAdresata(adresaci);
        } else if (wybor =='6') {
            system("cls");
            edytujAdresata(adresaci);
        } else if (wybor =='9') {
            exit(0);
        }
    }
    return 0;
}

