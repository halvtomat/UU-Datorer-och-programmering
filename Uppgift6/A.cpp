#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int MAX_KOMPISAR = 6;
const int MAX_PERSONER = 6;
const int MAX_TRANSAKTIONER = 20;

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

class Person{
    private:
        string namn;
        double betalat_andras;   // ligger ute med totalt
        double skyldig;          // skyldig totalt

    public:
        Person();
        Person(string n, double b, double s);
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





//-------------------------------------- KLASSMETODER------------------------------------
//TRANSAKTION

Transaktion::Transaktion():kompisar {}{
    datum = "";
    typ = "";
    namn = "";
    belopp = 0;
    ant_kompisar = 0;
}

string Transaktion::haemta_namn() {return namn;}
double Transaktion::haemta_belopp() {return belopp;}
int Transaktion::haemta_ant_kompisar() {return ant_kompisar;}

bool Transaktion::finnsKompis(string namnet){
    for(int i = 0; i < MAX_KOMPISAR; i++)
        if(kompisar[i] == namnet) return true;
    return false;
}

bool Transaktion::laesEnTrans(istream &is){
    is >> datum;
    is >> typ;
    is >> namn;
    is >> belopp;
    is >> ant_kompisar;
    for(int i = 0; i < ant_kompisar; i++){
        is >> kompisar[i];
    }
}

void Transaktion::skrivEnTrans(ostream &os){
    os << "Datum: " << datum << endl;
    os << "Typ: " << typ << endl;
    os << "Namn: " << namn << endl;
    os << "Belopp: " << belopp << endl;
    os << "Antal Kompisar: " << ant_kompisar << endl;
    for(int i = 0; i < ant_kompisar; i++){
        os << "Kompis nr " << i << ": ";
        os << kompisar[i] << endl;
    }
    os << endl;
}

//-------
//TRANSAKTIONSLISTA

TransaktionsLista::TransaktionsLista(): trans {}{
    antalTrans = 0;
}

void TransaktionsLista::laesin(istream &is){
    //En inläsningsmetod i klassen TransaktionsLista.
    Transaktion t;
  
    //Så länge det går bra att läsa (filen ej slut)
    while (t.laesEnTrans(is)){
        laggTill( t );
    }
}

void TransaktionsLista::skrivut(ostream &os){
    os << "Antal Transaktioner: " << antalTrans << endl;
    for(int i = 0; i < antalTrans; i++){
        os << "Transaktion nr " << i << ": ";
        os << trans[i] << endl;
    }
    os << endl;
}

void TransaktionsLista::laggTill(Transaktion &t){
    trans[antalTrans] = t;
    antalTrans++;
}

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
        aerSkyldig += trans[i].haemta_belopp()*(trans[i].haemta_ant_kompisar() + 1);
    }
    return aerSkyldig;
}

PersonLista TransaktionsLista::FixaPersoner(){

}

//-------
//PERSON

Person::Person(){
    namn = "";
    betalat_andras = 0;
    skyldig = 0;
}

double Person::haemta_betalat(){return betalat_andras;}
double Person::haemta_skyldig(){return skyldig;}

void Person::skrivUt(){
    cout << namn << "ligger ute med: " << betalat_andras << " och är skyldig: " << skyldig << " Skall ha " << betalat_andras-skyldig << "från potten!" << endl;
}

//-------
//PERSONLISTA



//-------