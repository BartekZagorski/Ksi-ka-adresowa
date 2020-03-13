#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <vector>

using namespace std;

struct Znajomy
{
    int idZnajomego;
    string Imie;
    string Nazwisko;
    string NumerTelefonu;
    string Email;
    string Adres;
};

int wyswietlZnajomego (vector <Znajomy> daneZnajomych, int indeksZnajomego)
{
    cout<<endl<<daneZnajomych[indeksZnajomego].idZnajomego<<". "<<daneZnajomych[indeksZnajomego].Imie<<" "
        <<daneZnajomych[indeksZnajomego].Nazwisko<<endl;
    cout<<daneZnajomych[indeksZnajomego].NumerTelefonu<<endl;
    cout<<daneZnajomych[indeksZnajomego].Email<<endl;
    cout<<daneZnajomych[indeksZnajomego].Adres<<endl<<endl;
    return indeksZnajomego+1;
}

void przyporzadkujDaneDoOdpowiednichSzufladek (vector <Znajomy>& daneZnajomych, int& aktualnyidZnajomego, fstream& ksiazkaAdresowa)
{
    string daneDodawanegoZnajomego;
    getline (ksiazkaAdresowa, daneDodawanegoZnajomego);
    if (daneDodawanegoZnajomego == "") return;
    string* podzieloneDane = new string [6];
    int j=0;
    for (int i=0; i<daneDodawanegoZnajomego.length(); i++)
    {
        if (daneDodawanegoZnajomego[i] != '|')
            *(podzieloneDane + j) += daneDodawanegoZnajomego[i];
        else
            j++;
    }
    Znajomy daneZnajomegoWOdpowiednichSzufladkach;
    daneZnajomegoWOdpowiednichSzufladkach.idZnajomego = atoi(podzieloneDane[0].c_str());
    aktualnyidZnajomego = daneZnajomegoWOdpowiednichSzufladkach.idZnajomego;
    daneZnajomegoWOdpowiednichSzufladkach.Imie = podzieloneDane[1];
    daneZnajomegoWOdpowiednichSzufladkach.Nazwisko = podzieloneDane[2];
    daneZnajomegoWOdpowiednichSzufladkach.NumerTelefonu = podzieloneDane[3];
    daneZnajomegoWOdpowiednichSzufladkach.Email = podzieloneDane[4];
    daneZnajomegoWOdpowiednichSzufladkach.Adres = podzieloneDane[5];
    daneZnajomych.push_back(daneZnajomegoWOdpowiednichSzufladkach);
    delete podzieloneDane;
}

int wczytajDaneZksiazkiAdresowej(vector <Znajomy>& daneZnajomych, int liczbaZnajomych, int& aktualnyidZnajomego, fstream& ksiazkaAdresowa)
{
    ksiazkaAdresowa.open("ksiazka.txt", ios::in);

    if (ksiazkaAdresowa.good()==false);
    else
    {
        while (ksiazkaAdresowa.eof()==false)
        {
            przyporzadkujDaneDoOdpowiednichSzufladek(daneZnajomych, aktualnyidZnajomego, ksiazkaAdresowa);
            if (daneZnajomych.size() == 0) break;
            liczbaZnajomych++;
        }
    }
    ksiazkaAdresowa.close();
    return liczbaZnajomych;
}

int dodajZnajomego(int aktualnyidZnajomego, int& liczbaZnajomych, vector <Znajomy>& daneZnajomych, fstream& ksiazkaAdresowa)
{
    ksiazkaAdresowa.open("ksiazka.txt", ios::out|ios::app);
    Znajomy daneWprowadzanegoZnajomego;
    daneWprowadzanegoZnajomego.idZnajomego = aktualnyidZnajomego + 1;
    if (liczbaZnajomych==0)
    {
        ksiazkaAdresowa<<aktualnyidZnajomego+1<<"|";
    }
    else
    {
        ksiazkaAdresowa<<endl<<aktualnyidZnajomego+1<<"|";
    }
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
        cout<<"Liczba znajomych w ksiazce adresowej wynosi: "<<liczbaZnajomych<<endl<<endl;
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

void eksportujKsiazkeDoPliku (vector <Znajomy> daneZnajomych, fstream& ksiazkaAdresowa)
{
    ksiazkaAdresowa.open("ksiazka.txt", ios::out);
    for (int i=0; i<daneZnajomych.size(); i++)
    {
        if (i > 0)
            ksiazkaAdresowa<<endl;
        ksiazkaAdresowa<<daneZnajomych[i].idZnajomego<<"|"<<daneZnajomych[i].Imie<<"|"<<daneZnajomych[i].Nazwisko<<"|"
                       <<daneZnajomych[i].NumerTelefonu<<"|"<<daneZnajomych[i].Email<<"|"<<daneZnajomych[i].Adres<<"|";
    }
    ksiazkaAdresowa.close();
}

void edytujZnajomego (vector <Znajomy>& daneZnajomych, fstream& ksiazkaAdresowa, int liczbaZnajomych)
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
            numerIdZnajomego = znajdzIndeksZnajomego(daneZnajomych, numerIdZnajomego);
            char wybranaOpcja = '0';
            while (wybranaOpcja != '6')
            {
                system("cls");
                wyswietlZnajomego(daneZnajomych, numerIdZnajomego);
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
                    getline(cin, daneZnajomych[numerIdZnajomego].Imie);
                    cout<<"Imie zostalo zmienione pomyslnie";
                    system ("pause >null");
                }
                break;
                case '2':
                {
                    cout<<"Podaj nowe nazwisko: ";
                    cin.sync();
                    getline(cin, daneZnajomych[numerIdZnajomego].Nazwisko);
                    cout<<"Nazwisko zostalo zmienione pomyslnie";
                    system ("pause >null");
                }
                break;
                case '3':
                {
                    cout<<"Podaj nowy numer telefonu: ";
                    cin.sync();
                    getline(cin, daneZnajomych[numerIdZnajomego].NumerTelefonu);
                    cout<<"Numer telefonu zostal zmieniony pomyslnie";
                    system ("pause >null");
                }
                break;
                case '4':
                {
                    cout<<"Podaj nowy email: ";
                    cin.sync();
                    getline (cin, daneZnajomych[numerIdZnajomego].Email);
                    cout<<"Email zostal zmieniony pomyslnie";
                    system ("pause >null");
                }
                break;
                case '5':
                {
                    cout<<"Podaj nowy adres: ";
                    cin.sync();
                    getline(cin, daneZnajomych[numerIdZnajomego].Adres);
                    cout<<"Adres zostal zmieniony pomyslnie";
                    system ("pause >null");
                }
                break;
                case '6':
                {
                    eksportujKsiazkeDoPliku (daneZnajomych, ksiazkaAdresowa);
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

int ustawAktualnyidZnajomego (vector <Znajomy> daneZnajomych, int aktualnyidZnajomego)
{
    int maksimum=0;
    for (int i=0; i<daneZnajomych.size(); i++)
    {
        if ( daneZnajomych[i].idZnajomego > maksimum)
        {
            maksimum = daneZnajomych[i].idZnajomego;
        }
    }
    return maksimum;
}

int usunZnajomego (vector <Znajomy>& daneZnajomych, fstream& ksiazkaAdresowa, int liczbaZnajomych, int& aktualnyidZnajomego)
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
            eksportujKsiazkeDoPliku (daneZnajomych, ksiazkaAdresowa);
            if (idZnajomegoWybranePrzezUzytkownika == aktualnyidZnajomego)
            {
                aktualnyidZnajomego = ustawAktualnyidZnajomego(daneZnajomych, aktualnyidZnajomego);
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

int main()
{
    vector <Znajomy> daneZnajomych;
    fstream ksiazkaAdresowa;
    int liczbaZnajomych=0;
    char wybranaOpcja;
    int aktualnyidZnajomego=0;
    liczbaZnajomych=wczytajDaneZksiazkiAdresowej(daneZnajomych, liczbaZnajomych, aktualnyidZnajomego, ksiazkaAdresowa);
    while(1)
    {
        system("cls");
        cout<<"Liczba znajomych w ksiazce adresowej wynosi: "<<liczbaZnajomych<<endl<<endl;
        cout<<"---------------------MENU--------------------"<<endl;
        cout<<"1. Dodaj znajomego"<<endl;
        cout<<"2. Szukaj znajomego"<<endl;
        cout<<"3. Wyswietl wszystkich znajomych"<<endl;
        cout<<"4. Edytuj znajomego"<<endl;
        cout<<"5. Usun znajomego"<<endl;
        cout<<"9. Wyjscie z programu ksiazka adresowa"<<endl;
        while(true)
        {
            wybranaOpcja=getch();
            if (wybranaOpcja=='1'||wybranaOpcja=='2'||wybranaOpcja=='3'
                    ||wybranaOpcja=='4'||wybranaOpcja=='5'||wybranaOpcja=='9')
                break;
        }
        switch (wybranaOpcja)
        {
        case '1':
        {
            aktualnyidZnajomego = dodajZnajomego(aktualnyidZnajomego, liczbaZnajomych, daneZnajomych, ksiazkaAdresowa);
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
            edytujZnajomego(daneZnajomych, ksiazkaAdresowa, liczbaZnajomych);
        }
        break;
        case '5':
        {
            liczbaZnajomych = usunZnajomego(daneZnajomych, ksiazkaAdresowa, liczbaZnajomych, aktualnyidZnajomego);
        }
        break;
        case '9':
        {
            exit(0);
        }
        break;
        }
    }
    return 0;
}
