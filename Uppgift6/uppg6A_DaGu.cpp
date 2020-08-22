/*================================================================================
Datorer och programmering, DoP, 10 hsp, termin/år: Sommar/2020

Inlämningsuppgift nr 6

Namn: Daniel Gustafsson

Personummer: 19980827-5110

Den fil som jag lämnar in går att kompilera och
programmet fungerar för alla de testdata som finns för uppgiften: Ja

Jag har använt kompilator/editor (namn/version) GCC 9.2.1/  Visual Studio Code 1.44.2

Jag har använt följande dator (t.ex. PC, Mac, Annat):        PC
      med operativsystemet (t.ex. WindowsXP, Windows7,...) : Ubuntu 19.10

Jag har arbetat ungefär 3 timmar med denna uppgift

================================================================================*/

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int MAX_KOMPISAR = 10;
const int MAX_PERSONER = 10;
const int MAX_TRANSAKTIONER = 30;

class Transaktion{
    private:
        string datum;
        string typ;
        string namn;
        double belopp;
        int ant_kompisar;
        string kompisar[MAX_KOMPISAR];

    public:
        Transaktion();
        ~Transaktion();
        string haemta_namn();
        double haemta_belopp();
        int haemta_ant_kompisar();
        bool finnsKompis(string namnet);
        bool laesEnTrans(istream &is);
        void skrivEnTrans(ostream &os);
}; 

class Person{
    private:
        string namn;
        double betalat_andras;   // ligger ute med totalt
        double skyldig;          // skyldig totalt

    public:
        Person();
        Person(string n, double b, double s);
        string haemta_namn();
        double haemta_betalat();
        double haemta_skyldig();
        void skrivUt();
};

class PersonLista{
    private:
        int antal_pers;
        Person pers[MAX_PERSONER];

    public:
        PersonLista();
        ~PersonLista();
        void laggTillEn(Person pny);
        void skrivUtOchFixa();
        double summaSkyldig();
        double summaBetalat();
        bool finnsPerson(const string &namn);
}; 

class TransaktionsLista{
    private:
        Transaktion trans[MAX_TRANSAKTIONER];
        int antalTrans;

    public:
        TransaktionsLista();
        ~TransaktionsLista();
        void laesin(istream & is);
        void skrivut(ostream & os);
        void laggTill(Transaktion &t);
        double totalkostnad();
        double liggerUteMed(string namnet);
        double aerSkyldig(string namnet);
        PersonLista FixaPersoner();
};

//-------------------------------------- FUNKTIONER --------------------------------------

void printMenu(){
    cout << endl << endl;
    cout << "Välj i menyn nedan:" << endl;
    cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
    cout << "1. Läs in en transaktion från tangentbordet." << endl;
    cout << "2. Skriv ut information om alla transaktioner." << endl;
    cout << "3. Beräkna totala kostnaden." << endl;
    cout << "4. Hur mycket är en viss person skyldig?" << endl;
    cout << "5. Hur mycket ligger en viss person ute med?" << endl;
    cout << "6. Lista alla personer mm och FIXA!!!" << endl;
    cout << endl;
}

TransaktionsLista laesInTransaktioner(){
    TransaktionsLista tl;
    string filnamn;
    cout << "Data-fil namn: ";
    cin >> filnamn;
    cout << endl << endl;
    ifstream fil(filnamn);
    tl.laesin(fil);
    fil.close();
    return tl;
}

void sparaTransaktioner(TransaktionsLista tl){
    string filnamn;
    cout << "Spar-fil namn: ";
    cin >> filnamn;
    cout << endl << endl;
    ofstream fil(filnamn);
    tl.skrivut(fil);
    fil.close();
}

//-------------------------------------- MAIN --------------------------------------------

int main(){
    bool running = true;
    TransaktionsLista tl = laesInTransaktioner();

    while(running){
        int val;
        printMenu();
        cin >> val;
        switch(val){
            case 0:{
                sparaTransaktioner(tl);
                running = false;
                break;
            }
            case 1:{
                Transaktion t;
                t.laesEnTrans(cin);
                tl.laggTill(t);
                break;
            }
            case 2:{
                tl.skrivut(cout);
                break;
            }
            case 3:{
                cout << "Total Kostnad: ";
                cout << tl.totalkostnad();
                cout << endl << endl;
                break;
            }
            case 4:{
                string namn;
                cout << "Namn på personen: ";
                cin >> namn;
                cout << endl << endl;
                cout << namn << " är skyldig: ";
                cout << tl.aerSkyldig(namn);
                cout << endl << endl;
                break;
            }
            case 5:{
                string namn;
                cout << "Namn på personen: ";
                cin >> namn;
                cout << endl << endl;
                cout << namn << " ligger ute med: ";
                cout << tl.liggerUteMed(namn);
                cout << endl << endl;
                break;
            }
            case 6:{
                PersonLista pl = tl.FixaPersoner();
                pl.skrivUtOchFixa();
                break;
            }
        }
    }
    
    return 0;
}

//-------------------------------------- KLASSMETODER ------------------------------------
//TRANSAKTION

Transaktion::Transaktion():kompisar {}{
    datum = "";
    typ = "";
    namn = "";
    belopp = 0;
    ant_kompisar = 0;
}

Transaktion::~Transaktion(){}

string Transaktion::haemta_namn() {return namn;}
double Transaktion::haemta_belopp() {return belopp;}
int Transaktion::haemta_ant_kompisar() {return ant_kompisar;}

bool Transaktion::finnsKompis(string namnet){
    for(int i = 0; i < ant_kompisar; i++)
        if(kompisar[i] == namnet) return true;
    return false;
}

bool Transaktion::laesEnTrans(istream &is){
    if(is.eof()) return false;
    is >> datum;
    is >> typ;
    is >> namn;
    is >> belopp;
    is >> ant_kompisar;
    for(int i = 0; i < ant_kompisar; i++)
        is >> kompisar[i];
    return true;
}

void Transaktion::skrivEnTrans(ostream &os){
    os << datum;
    os << '\t' << typ;
    os << '\t' << namn;
    os << '\t' << belopp;
    os << '\t' << ant_kompisar;
    for(int i = 0; i < ant_kompisar; i++)
        os << '\t' << kompisar[i];
}

//-------
//TRANSAKTIONSLISTA

TransaktionsLista::TransaktionsLista(): trans {}{
    antalTrans = 0;
}

TransaktionsLista::~TransaktionsLista(){}

void TransaktionsLista::laesin(istream &is){
    //En inläsningsmetod i klassen TransaktionsLista.
    Transaktion t;
  
    //Så länge det går bra att läsa (filen ej slut)
    while (t.laesEnTrans(is)){
        laggTill( t );
    }
}

void TransaktionsLista::skrivut(ostream &os){
    for(int i = 0; i < antalTrans; i++){
        trans[i].skrivEnTrans(os);
        if(i != antalTrans-1)os << '\n';
    }
}

void TransaktionsLista::laggTill(Transaktion &t){trans[antalTrans++] = t;}

double TransaktionsLista::totalkostnad(){
    double total = 0;
    for(int i = 0; i < antalTrans; i++)
        total += trans[i].haemta_belopp();
    return total;
}

double TransaktionsLista::liggerUteMed(string Namnet){
    double liggerUteMed = 0;
    for(int i = 0; i < antalTrans; i++){
        if(trans[i].haemta_namn() != Namnet) continue;
        liggerUteMed += trans[i].haemta_belopp()*trans[i].haemta_ant_kompisar()/(trans[i].haemta_ant_kompisar() + 1);
    }
    return liggerUteMed;
}

double TransaktionsLista::aerSkyldig(string Namnet){
    double aerSkyldig = 0;
    for(int i = 0; i < antalTrans; i++){
        if(!trans[i].finnsKompis(Namnet)) continue;
        aerSkyldig += trans[i].haemta_belopp()/(trans[i].haemta_ant_kompisar() + 1);
    }
    return aerSkyldig;
}

PersonLista TransaktionsLista::FixaPersoner(){
    PersonLista pl;
    for(int i = 0; i < antalTrans; i++){
        string namn = trans[i].haemta_namn();
        if(pl.finnsPerson(namn)) continue;
        double uteMed = liggerUteMed(namn);
        double skyldig = aerSkyldig(namn);
        Person p(namn, uteMed, skyldig);
        pl.laggTillEn(p);
    }
    return pl;
}

//-------
//PERSON

Person::Person(){
    namn = "";
    betalat_andras = 0;
    skyldig = 0;
}

Person::Person(string n, double b, double s){
    namn = n;
    betalat_andras = b;
    skyldig = s;
}

string Person::haemta_namn(){return namn;}
double Person::haemta_betalat(){return betalat_andras;}
double Person::haemta_skyldig(){return skyldig;}

void Person::skrivUt(){
    cout << namn; 
    cout << " ligger ute med: " << betalat_andras;
    cout << " och är skyldig: " << skyldig;
    if(betalat_andras < skyldig) cout << " Skall lägga " << skyldig-betalat_andras<< " till potten!" << endl;
    else cout << " Skall ha " << betalat_andras-skyldig << " från potten!" << endl;
}

//-------
//PERSONLISTA

PersonLista::PersonLista(): pers {}{antal_pers = 0;}

PersonLista::~PersonLista(){}

void PersonLista::laggTillEn(Person pny){pers[antal_pers++] = pny;}

void PersonLista::skrivUtOchFixa(){
    for(int i = 0; i < antal_pers; i++){
        pers[i].skrivUt();
    }
    cout << endl;
    cout << "Potten innehåller: " << summaBetalat();
    cout << " och folk ska ta: " << summaSkyldig() << endl;
    if(nearbyint(summaBetalat()) == nearbyint(summaSkyldig())) cout << "Potten stämmer!" << endl;
    else cout << "Potten är fel! :(" << endl;
}

double PersonLista::summaBetalat(){
    double betalat = 0;
    for(int i = 0; i < antal_pers; i++)
        betalat += pers[i].haemta_betalat();
    return betalat;
}

double PersonLista::summaSkyldig(){
    double skyldig = 0;
    for(int i = 0; i < antal_pers; i++)
        skyldig += pers[i].haemta_skyldig();
    return skyldig;
}

bool PersonLista::finnsPerson(const string &namn){
    for(int i = 0; i < antal_pers; i++)
        if(pers[i].haemta_namn() == namn) return true;
    return false;
}

/*
================================================================================
Här följer programkörningar för alla testdata:
==============================================

Välj i menyn nedan:
0. Avsluta. Alla transaktioner sparas på fil.
1. Läs in en transaktion från tangentbordet.
2. Skriv ut information om alla transaktioner.
3. Beräkna totala kostnaden.
4. Hur mycket är en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA!!!

6
Eva ligger ute med: 5850 och är skyldig: 1350 Skall ha 4500 från potten!
Paul ligger ute med: 366.667 och är skyldig: 2500 Skall lägga 2133.33 till potten!
Bosse ligger ute med: 3750 och är skyldig: 1350 Skall ha 2400 från potten!
Stina ligger ute med: 2500 och är skyldig: 1333.33 Skall ha 1166.67 från potten!
Kristin ligger ute med: 100 och är skyldig: 2600 Skall lägga 2500 till potten!
Torsten ligger ute med: 200 och är skyldig: 3633.33 Skall lägga 3433.33 till potten!

Potten innehåller: 12766.7 och folk ska ta: 12766.7
Potten stämmer!

================================================================================
Uppgiften gick ut på att göra ett program som kan räkna ut data om hur vänner ska 
dela upp pengar efter ett antal transaktioner (Med statiska arrayer).

(Svar på frågor finns i 6B)
*/