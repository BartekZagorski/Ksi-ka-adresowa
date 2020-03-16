#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <cstdlib>

using namespace std;

struct Uzytkownik
{
    int Id;
    string nazwa, haslo;
};

struct Znajomy
{
    int idZnajomego;
    string Imie;
    string Nazwisko;
    string NumerTelefonu;
    string Email;
    string Adres;
};

bool czyJestTakiUzytkownik (vector <Uzytkownik> uzytkownicy, string podanaNazwa)
{
    bool czyUzytkownikIstnieje = false;
    for (int i = 0; i < uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].nazwa == podanaNazwa)
        {
            czyUzytkownikIstnieje = true;
            break;
        }
    }
    return czyUzytkownikIstnieje;
}

void zarejestrujNowegoUzytkownika (int& ostatniNumerIdUzytkownika, vector <Uzytkownik>& uzytkownicy)
{
    string podanaNazwa="";
    cout << "podaj nazwe uzytkownika:";
    cin >> podanaNazwa;
    if (czyJestTakiUzytkownik(uzytkownicy, podanaNazwa))
    {
        cout << "podana nazwa jest juz zajeta";
        system ("pause >null");
    }
    else
    {
        ostatniNumerIdUzytkownika++;
        Uzytkownik dodawanyUzytkownik;
        dodawanyUzytkownik.Id = ostatniNumerIdUzytkownika;
        dodawanyUzytkownik.nazwa = podanaNazwa;
        cout<<"podaj haslo:";
        cin >> dodawanyUzytkownik.haslo;
        uzytkownicy.push_back(dodawanyUzytkownik);
        fstream plikPrzechowujacyUzytkownikow;
        plikPrzechowujacyUzytkownikow.open("uzytkownicy.txt", ios::out | ios::app);
        if (uzytkownicy.size() > 1)
        {
            plikPrzechowujacyUzytkownikow << endl << dodawanyUzytkownik.Id << "|" << dodawanyUzytkownik.nazwa
                                          << "|" << dodawanyUzytkownik.haslo << "|";
        }
        else
        {
            plikPrzechowujacyUzytkownikow << dodawanyUzytkownik.Id << "|" << dodawanyUzytkownik.nazwa
                                          << "|" << dodawanyUzytkownik.haslo << "|";
        }
        plikPrzechowujacyUzytkownikow.close();
    }
}

int wczytajUzytkownikow (vector <Uzytkownik>& uzytkownicy, int ostatniNumerIdUzytkownika)
{
    fstream plikPrzechowujacyUztykownikow;
    plikPrzechowujacyUztykownikow.open ("uzytkownicy.txt", ios::in);
    if (!(plikPrzechowujacyUztykownikow.good()))
        return 0;
    else
    {
        string* podzieloneDane;
        string pobranaLinia = "";
        Uzytkownik pobieranyUzytkownik;
        while (getline(plikPrzechowujacyUztykownikow, pobranaLinia))
        {
            podzieloneDane = new string [3];
            int j = 0;
            for (int i = 0; i < pobranaLinia.length(); i++)
            {
                if (pobranaLinia[i] != '|')
                {
                    *(podzieloneDane + j) += pobranaLinia[i];
                }
                else
                {
                    j++;
                }
            }
            pobieranyUzytkownik.Id = atoi ((*podzieloneDane).c_str());
            pobieranyUzytkownik.nazwa = *(podzieloneDane + 1);
            pobieranyUzytkownik.haslo = *(podzieloneDane + 2);
            delete podzieloneDane;
            uzytkownicy.push_back(pobieranyUzytkownik);
        }
    }
    plikPrzechowujacyUztykownikow.close();
    return uzytkownicy[uzytkownicy.size()-1].Id;
}

int znajdzIndeksUzytkownika (vector <Uzytkownik> uzytkownicy, string nazwa)
{
    for (int i = 0; i < uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].nazwa == nazwa)
            return i;
    }
    return 0;
}

int wyswietlZnajomego (vector <Znajomy> daneZnajomych, int indeksZnajomego)
{
    cout<<endl<<daneZnajomych[indeksZnajomego].idZnajomego<<". "<<daneZnajomych[indeksZnajomego].Imie<<" "
        <<daneZnajomych[indeksZnajomego].Nazwisko<<endl;
    cout<<daneZnajomych[indeksZnajomego].NumerTelefonu<<endl;
    cout<<daneZnajomych[indeksZnajomego].Email<<endl;
    cout<<daneZnajomych[indeksZnajomego].Adres<<endl<<endl;
    return indeksZnajomego+1;
}

void przyporzadkujDaneDoOdpowiednichSzufladek (int idUzytkownika, vector <Znajomy>& daneZnajomych,
        int& aktualnyIdZnajomego, fstream& ksiazkaAdresowa)
{
    string daneDodawanegoZnajomego;
    getline (ksiazkaAdresowa, daneDodawanegoZnajomego);
    if (daneDodawanegoZnajomego == "")
        return;
    string* podzieloneDane = new string [7];
    int j=0;
    for (int i=0; i<daneDodawanegoZnajomego.length(); i++)
    {
        if (daneDodawanegoZnajomego[i] != '|')
            *(podzieloneDane + j) += daneDodawanegoZnajomego[i];
        else
            j++;
    }
    aktualnyIdZnajomego = atoi(podzieloneDane[0].c_str());
    if (atoi (podzieloneDane[1].c_str()) == idUzytkownika)
    {
        Znajomy daneZnajomegoWOdpowiednichSzufladkach;
        daneZnajomegoWOdpowiednichSzufladkach.idZnajomego = atoi(podzieloneDane[0].c_str());
        daneZnajomegoWOdpowiednichSzufladkach.Imie = podzieloneDane[2];
        daneZnajomegoWOdpowiednichSzufladkach.Nazwisko = podzieloneDane[3];
        daneZnajomegoWOdpowiednichSzufladkach.NumerTelefonu = podzieloneDane[4];
        daneZnajomegoWOdpowiednichSzufladkach.Email = podzieloneDane[5];
        daneZnajomegoWOdpowiednichSzufladkach.Adres = podzieloneDane[6];
        daneZnajomych.push_back(daneZnajomegoWOdpowiednichSzufladkach);
    }
    delete podzieloneDane;
}

int wczytajDaneZksiazkiAdresowej(int idUzytkownika, vector <Znajomy>& daneZnajomych, int liczbaZnajomych,
                                 int& aktualnyidZnajomego, fstream& ksiazkaAdresowa)
{
    ksiazkaAdresowa.open("ksiazka.txt", ios::in);

    if (ksiazkaAdresowa.good()==false);
    else
    {
        while (ksiazkaAdresowa.eof()==false)
        {
            przyporzadkujDaneDoOdpowiednichSzufladek(idUzytkownika, daneZnajomych, aktualnyidZnajomego, ksiazkaAdresowa);
            if (daneZnajomych.size() > liczbaZnajomych)
                liczbaZnajomych++;
        }
    }
    ksiazkaAdresowa.close();
    return liczbaZnajomych;
}

int dodajZnajomego(int idUzytkownika, int aktualnyidZnajomego, int& liczbaZnajomych,
                   vector <Znajomy>& daneZnajomych, fstream& ksiazkaAdresowa)
{
    ksiazkaAdresowa.open("ksiazka.txt", ios::out|ios::app);
    Znajomy daneWprowadzanegoZnajomego;
    daneWprowadzanegoZnajomego.idZnajomego = aktualnyidZnajomego + 1;
    if (aktualnyidZnajomego == 0)
    {
        ksiazkaAdresowa<<aktualnyidZnajomego+1<<"|";
    }
    else
    {
        ksiazkaAdresowa<<endl<<aktualnyidZnajomego+1<<"|";
    }
    ksiazkaAdresowa<<idUzytkownika<<"|";
    cin.sync();
    cout<<"Podaj imie: ";
    getline(cin, daneWprowadzanegoZnajomego.Imie);
    ksiazkaAdresowa<<daneWprowadzanegoZnajomego.Imie<<"|";
    cout<<"Podaj nazwisko: ";
    getline(cin, daneWprowadzanegoZnajomego.Nazwisko);
    ksiazkaAdresowa<<daneWprowadzanegoZnajomego.Nazwisko<<"|";
    cout<<"Podaj numer telefonu: ";
    getline(cin, daneWprowadzanegoZnajomego.NumerTelefonu);
    ksiazkaAdresowa<<daneWprowadzanegoZnajomego.NumerTelefonu<<"|";
    cout<<"Podaj e-mail: ";
    getline(cin, daneWprowadzanegoZnajomego.Email);
    ksiazkaAdresowa<<daneWprowadzanegoZnajomego.Email<<"|";
    cout<<"Podaj adres: ";
    getline(cin, daneWprowadzanegoZnajomego.Adres);
    ksiazkaAdresowa<<daneWprowadzanegoZnajomego.Adres<<"|";
    ksiazkaAdresowa.close();
    cout<<"Dodano znajomego do ksiazki";
    system("pause>null");
    daneZnajomych.push_back(daneWprowadzanegoZnajomego);
    liczbaZnajomych++;
    aktualnyidZnajomego++;
    return aktualnyidZnajomego;
}

void wyswietlWszystkichZnajomych (int liczbaZnajomych, int aktualnyidZnajomego, vector <Znajomy> daneZnajomych)
{
    if (liczbaZnajomych==0)
        cout<<"Ksiazka adresowa jest pusta"<<endl;
    else
    {
        for (int i=0; i<liczbaZnajomych; i++)
        {
            wyswietlZnajomego(daneZnajomych, i);
        }
    }
    system("pause>null");
}

void szukajZnajomych (int liczbaZnajomych, vector <Znajomy> daneZnajomych)
{
    if (liczbaZnajomych==0)
        cout<<"Ksiazka adresowa jest pusta"<<endl;
    else
    {
        system("cls");
        cout<<"---------------------MENU--------------------"<<endl;
        cout<<"1. szukaj po imieniu"<<endl;
        cout<<"2. szukaj po nazwisku"<<endl;
        char wybranaOpcja;
        while(true)
        {
            wybranaOpcja=getch();
            if (wybranaOpcja=='1'||wybranaOpcja=='2')
                break;
        }
        int liczbaZnalezionychZnajomych=0;
        if (wybranaOpcja=='1')
        {
            string imie;
            cout<<"Podaj imie: ";
            cin>>imie;
            for (int i=0; i<liczbaZnajomych; i++)
            {
                if (daneZnajomych[i].Imie==imie)
                    liczbaZnalezionychZnajomych=wyswietlZnajomego(daneZnajomych, i);
            }
            if (liczbaZnalezionychZnajomych==0)
                cout<<"Nie ma znajomego o podanym imieniu"<<endl;
        }

        else if (wybranaOpcja=='2')
        {
            string nazwisko;
            cout<<"Podaj nazwisko: ";
            cin>>nazwisko;
            for (int i=0; i<liczbaZnajomych; i++)
            {
                if (daneZnajomych[i].Nazwisko==nazwisko)
                    liczbaZnalezionychZnajomych=wyswietlZnajomego(daneZnajomych, i);
            }
            if (liczbaZnalezionychZnajomych==0)
                cout<<"Nie ma znajomego o podanym nazwisku"<<endl;
        }
    }
    system("pause >null");
}

bool sprawdzCzyPodanyidZnajomegoIstnieje (int podanyidZnajomego, vector <Znajomy> daneZnajomych)
{
    bool czyidZnajomegoIstnieje = false;
    int koniec = daneZnajomych.size();
    for (int i=0; i<koniec; i++)
    {
        if (daneZnajomych[i].idZnajomego == podanyidZnajomego)
            czyidZnajomegoIstnieje = true;
    }
    return czyidZnajomegoIstnieje;
}

int znajdzIndeksZnajomego (vector <Znajomy> daneZnajomych, int numeridZnajomego)
{
    int indeksZnajomego = 0;
    for (int i=0; i<daneZnajomych.size(); i++)
    {
        if (daneZnajomych[i].idZnajomego == numeridZnajomego)
        {
            indeksZnajomego = i;
            break;
        }
    }
    return indeksZnajomego;
}

int pozyskajIdZnajomego (string daneJednegoZnajomego)
{
    if (daneJednegoZnajomego == "")
        return 0;
    string tekstoweID="";
    int i = 0;
    while (daneJednegoZnajomego[i] != '|')
    {
        tekstoweID += daneJednegoZnajomego[i];
        i++;
    }
    int idZPliku = atoi (tekstoweID.c_str());
    return idZPliku;
}

void edytujPlikZKsiazkaAdresowa (int idUzytkownika, vector <Znajomy> daneZnajomych,
                                 fstream& ksiazkaAdresowa, int idZnajomego, string usunLubEdytuj)
{
    fstream plikTymczasowy;
    plikTymczasowy.open("tymczasowy.txt", ios::out);
    ksiazkaAdresowa.open("ksiazka.txt", ios::in);
    if (!(ksiazkaAdresowa.good()))
        return;
    string pobranaLinia="";
    int numerLinii = 0;
    while (getline(ksiazkaAdresowa, pobranaLinia))
    {
        int numerIdPobranejLinii = pozyskajIdZnajomego(pobranaLinia);
        if (usunLubEdytuj == "edytuj")
        {
            if (numerIdPobranejLinii == idZnajomego)
            {
                int i = znajdzIndeksZnajomego(daneZnajomych, idZnajomego);
                if (numerLinii != 0)
                    plikTymczasowy<<endl;
                plikTymczasowy<<daneZnajomych[i].idZnajomego<<"|"<<idUzytkownika<<"|"<<daneZnajomych[i].Imie<<"|"<<daneZnajomych[i].Nazwisko<<"|"
                              <<daneZnajomych[i].NumerTelefonu<<"|"<<daneZnajomych[i].Email<<"|"<<daneZnajomych[i].Adres<<"|";
            }
            else
            {
                if (numerLinii != 0)
                    plikTymczasowy<<endl;
                plikTymczasowy<<pobranaLinia;
            }
            numerLinii++;
        }
        else
        {
            if (numerIdPobranejLinii == idZnajomego);
            else
            {
                if (numerLinii != 0)
                    plikTymczasowy<<endl;
                plikTymczasowy<<pobranaLinia;
            }
            numerLinii++;
        }
    }
    ksiazkaAdresowa.close();
    plikTymczasowy.close();
    remove ("ksiazka.txt");
    rename ("tymczasowy.txt", "ksiazka.txt");
}

void edytujZnajomego (int idUzytkownika, vector <Znajomy>& daneZnajomych, fstream& ksiazkaAdresowa, int liczbaZnajomych)
{
    if (liczbaZnajomych == 0)
    {
        cout << "ksiazka adresowa jest pusta, nie ma czego edytowac";
        system ("pause >null");
    }
    else
    {
        int numerIdZnajomego = 0;
        cout<< "podaj numer Id znajomego, ktorego chcesz edytowac: ";
        cin >> numerIdZnajomego;
        if (sprawdzCzyPodanyidZnajomegoIstnieje(numerIdZnajomego, daneZnajomych))
        {
            int indeksZnajomego = znajdzIndeksZnajomego(daneZnajomych, numerIdZnajomego);
            char wybranaOpcja = '0';
            while (wybranaOpcja != '6')
            {
                system("cls");
                wyswietlZnajomego(daneZnajomych, indeksZnajomego);
                cout<<"Wybierz co chcesz edytowac: "<<endl;
                cout<<"1. Imie"<<endl;
                cout<<"2. Nazwisko"<<endl;
                cout<<"3. Numer telefonu"<<endl;
                cout<<"4. Email"<<endl;
                cout<<"5. Adres"<<endl;
                cout<<"6. Powrot do Menu"<<endl;
                while(true)
                {
                    wybranaOpcja = getch();
                    if (wybranaOpcja == '1' || wybranaOpcja == '2' || wybranaOpcja == '3' ||
                            wybranaOpcja == '4' || wybranaOpcja == '5' || wybranaOpcja == '6' )
                        break;
                }
                switch (wybranaOpcja)
                {
                    case '1':
                    {
                        cout<<"Podaj nowe imie: ";
                        cin.sync();
                        getline(cin, daneZnajomych[indeksZnajomego].Imie);
                        cout<<"Imie zostalo zmienione pomyslnie";
                        system ("pause >null");
                    }
                    break;
                    case '2':
                    {
                        cout<<"Podaj nowe nazwisko: ";
                        cin.sync();
                        getline(cin, daneZnajomych[indeksZnajomego].Nazwisko);
                        cout<<"Nazwisko zostalo zmienione pomyslnie";
                        system ("pause >null");
                    }
                    break;
                    case '3':
                    {
                        cout<<"Podaj nowy numer telefonu: ";
                        cin.sync();
                        getline(cin, daneZnajomych[indeksZnajomego].NumerTelefonu);
                        cout<<"Numer telefonu zostal zmieniony pomyslnie";
                        system ("pause >null");
                    }
                    break;
                    case '4':
                    {
                        cout<<"Podaj nowy email: ";
                        cin.sync();
                        getline (cin, daneZnajomych[indeksZnajomego].Email);
                        cout<<"Email zostal zmieniony pomyslnie";
                        system ("pause >null");
                    }
                    break;
                    case '5':
                    {
                        cout<<"Podaj nowy adres: ";
                        cin.sync();
                        getline(cin, daneZnajomych[indeksZnajomego].Adres);
                        cout<<"Adres zostal zmieniony pomyslnie";
                        system ("pause >null");
                    }
                    break;
                    case '6':
                    {
                        edytujPlikZKsiazkaAdresowa (idUzytkownika, daneZnajomych, ksiazkaAdresowa, numerIdZnajomego, "edytuj");
                    }
                }
            }
        }
        else
        {
            cout<< "nie ma takiego Id";
            system ("pause >null");
        }
    }
}

int ustalAktualnyID (fstream& ksiazkaAdresowa)
{
    ksiazkaAdresowa.open("ksiazka.txt", ios::in);
    if (!(ksiazkaAdresowa.good()))
        return 0;
    string pobranaLiniaZPliku;
    int aktualnyID=0;
    while (getline(ksiazkaAdresowa, pobranaLiniaZPliku))
    {
        if (pobranaLiniaZPliku == "")
            return aktualnyID;
        else
        {
            string tekstowyNumerID="";
            int i = 0;
            while (pobranaLiniaZPliku[i] != '|')
            {
                tekstowyNumerID += pobranaLiniaZPliku[i];
                i++;
            }
            int NumerId = atoi (tekstowyNumerID.c_str());
            if (NumerId > aktualnyID)
                aktualnyID = NumerId;
        }
    }
    ksiazkaAdresowa.close();
    return aktualnyID;
}

int usunZnajomego (int idUzytkownika, vector <Znajomy>& daneZnajomych, fstream& ksiazkaAdresowa,
                   int liczbaZnajomych, int& aktualnyidZnajomego)
{
    if (liczbaZnajomych == 0)
    {
        cout<<"ksiazka adresowa jest pusta";
        system ("pause >null");
        return liczbaZnajomych;
    }
    int idZnajomegoWybranePrzezUzytkownika;
    cout << "Podaj Id znajomego, ktorego chcesz usunac: ";
    cin >> idZnajomegoWybranePrzezUzytkownika;
    if (sprawdzCzyPodanyidZnajomegoIstnieje(idZnajomegoWybranePrzezUzytkownika, daneZnajomych))
    {
        int indeksZnajomego = znajdzIndeksZnajomego(daneZnajomych, idZnajomegoWybranePrzezUzytkownika);
        cout << "Czy na pewno usunac z ksiazki znajomego: "<< daneZnajomych[indeksZnajomego].idZnajomego <<
             ". " <<daneZnajomych[indeksZnajomego].Imie << " " << daneZnajomych[indeksZnajomego].Nazwisko <<" ? (t/n)";
        char wybranaOpcja;
        while (true)
        {
            wybranaOpcja = getch();
            if (wybranaOpcja == 't' || wybranaOpcja == 'T' || wybranaOpcja == 'n' || wybranaOpcja == 'N')
                break;
        }
        if (wybranaOpcja == 't' || wybranaOpcja == 'T')
        {
            daneZnajomych.erase(daneZnajomych.begin()+indeksZnajomego);
            liczbaZnajomych--;
            edytujPlikZKsiazkaAdresowa (idUzytkownika, daneZnajomych,
                                        ksiazkaAdresowa, idZnajomegoWybranePrzezUzytkownika, "usun");
            if (idZnajomegoWybranePrzezUzytkownika == aktualnyidZnajomego)
            {
                aktualnyidZnajomego = ustalAktualnyID(ksiazkaAdresowa);
            }
            cout << endl <<"Usunieto znajomego pomyslnie";
            system ("pause >null");
        }
    }
    else
    {
        cout << "nie ma w ksiazce znajomego o podanym Id";
        system ("pause >null");
    }
    return liczbaZnajomych;
}

void zmienHaslo (int numerUzytkownika, vector <Uzytkownik>& uzytkownicy)
{
    string podaneDotychczasoweHaslo="";
    for (int i = 0; i < 3; i++)
    {
        cout << "Podaj dotychczasowe haslo: ";
        cin >> podaneDotychczasoweHaslo;
        int indeksUzytkownika = 0;
        for (int i = 0; i < uzytkownicy.size(); i++)
        {
            if (uzytkownicy[i].Id == numerUzytkownika)
            {
                indeksUzytkownika = i;
                break;
            }
        }
        if (podaneDotychczasoweHaslo != uzytkownicy[indeksUzytkownika].haslo)
        {
            cout << "Podane haslo jest nieprawidlowe"<<endl;
            system ("pause >null");
        }
        else
        {
            string noweHaslo = "";
            cout << "Podaj nowe haslo: ";
            cin >> noweHaslo;
            uzytkownicy[indeksUzytkownika].haslo = noweHaslo;
            cout << "Haslo zostalo zmienione";
            system ("pause >null");
            break;
        }
    }
    fstream plikZDanymiUzytkownikow;
    plikZDanymiUzytkownikow.open("uzytkownicy.txt", ios::out);
    for (int i = 0; i < uzytkownicy.size(); i++)
    {
        if (i > 0)
            plikZDanymiUzytkownikow << endl;
        plikZDanymiUzytkownikow << uzytkownicy[i].Id << "|" << uzytkownicy[i].nazwa << "|" << uzytkownicy[i].haslo << "|";
    }
    plikZDanymiUzytkownikow.close();
    return;
}

void wczytajKsiazkeAdresowa(int numerUzytkownika, vector <Uzytkownik>& uzytkownicy)
{
    vector <Znajomy> daneZnajomych;
    fstream ksiazkaAdresowa;
    int liczbaZnajomych=0;
    char wybranaOpcja;
    int aktualnyidZnajomego=ustalAktualnyID(ksiazkaAdresowa);
    liczbaZnajomych=wczytajDaneZksiazkiAdresowej(numerUzytkownika, daneZnajomych, liczbaZnajomych, aktualnyidZnajomego,
                    ksiazkaAdresowa);
    while(1)
    {
        system("cls");
        cout<<"---------------------MENU--------------------"<<endl;
        cout<<"1. Dodaj znajomego"<<endl;
        cout<<"2. Szukaj znajomego"<<endl;
        cout<<"3. Wyswietl wszystkich znajomych"<<endl;
        cout<<"4. Edytuj znajomego"<<endl;
        cout<<"5. Usun znajomego"<<endl;
        cout<<"6. Zmien haslo"<<endl;
        cout<<"9. Wyloguj sie"<<endl;
        while(true)
        {
            wybranaOpcja=getch();
            if (wybranaOpcja=='1'||wybranaOpcja=='2'||wybranaOpcja=='3'
                    ||wybranaOpcja=='4'||wybranaOpcja=='5'||wybranaOpcja=='6'||wybranaOpcja=='9')
                break;
        }
        switch (wybranaOpcja)
        {
        case '1':
        {
            aktualnyidZnajomego = dodajZnajomego(numerUzytkownika, aktualnyidZnajomego, liczbaZnajomych,
                                                 daneZnajomych, ksiazkaAdresowa);
        }
        break;
        case '2':
        {
            szukajZnajomych (liczbaZnajomych, daneZnajomych);
        }
        break;
        case '3':
        {
            wyswietlWszystkichZnajomych(liczbaZnajomych, aktualnyidZnajomego, daneZnajomych);
        }
        break;
        case '4':
        {
            edytujZnajomego(numerUzytkownika, daneZnajomych, ksiazkaAdresowa, liczbaZnajomych);
        }
        break;
        case '5':
        {
            liczbaZnajomych = usunZnajomego(numerUzytkownika, daneZnajomych, ksiazkaAdresowa,
                                            liczbaZnajomych, aktualnyidZnajomego);
        }
        break;
        case '6':
        {
            zmienHaslo (numerUzytkownika, uzytkownicy);
        }
        break;
        case '9':
        {
            return;
        }
        break;
        }
    }
}

void zalogujSie (vector <Uzytkownik>& uzytkownicy)
{
    if (uzytkownicy.size() == 0)
    {
        cout << "Brak zarejestrowanych uzytkownikow";
        system("pause >null");
    }
    else
    {
        string nazwaPodanaPrzezUzytkownika;
        cout << "Podaj nazwe uzytkownika: ";
        cin >> nazwaPodanaPrzezUzytkownika;
        if (czyJestTakiUzytkownik(uzytkownicy, nazwaPodanaPrzezUzytkownika))
        {
            int indeksUzytkownika = znajdzIndeksUzytkownika(uzytkownicy, nazwaPodanaPrzezUzytkownika);
            string podaneHaslo="";
            for (int i = 0; i < 3; i++)
            {
                cout << "Podaj haslo: ";
                cin >> podaneHaslo;
                if (podaneHaslo != uzytkownicy[indeksUzytkownika].haslo)
                {
                    cout << "haslo niepoprawne"<<endl;
                    system ("pause >null");
                }
                else
                {
                    wczytajKsiazkeAdresowa(uzytkownicy[indeksUzytkownika].Id, uzytkownicy);
                    break;
                }
            }
        }
        else
        {
            cout << "Nie istnieje uzytkownik o podanej nazwie";
            system ("pause >null");
        }
    }
}

int main()
{
    vector <Uzytkownik> uzytkownicy;
    int ostatniNumerIdUzytkownika = wczytajUzytkownikow(uzytkownicy, ostatniNumerIdUzytkownika);
    char wybranaOpcja;

    while(true)
    {
        system("cls");
        cout<<"---------------------MENU--------------------"<<endl;
        cout<<"1. Zaloguj sie"<<endl;
        cout<<"2. Zarejestruj sie"<<endl;
        cout<<"3. Wyjdz"<<endl;
        wybranaOpcja = getch();
        switch (wybranaOpcja)
        {
        case '1':
        {
            zalogujSie(uzytkownicy);
        }
        break;
        case '2':
        {
            zarejestrujNowegoUzytkownika(ostatniNumerIdUzytkownika, uzytkownicy);
        }
        break;
        case '3':
        {
            exit(0);
        }
        break;
        }
    }
    return 0;
}
