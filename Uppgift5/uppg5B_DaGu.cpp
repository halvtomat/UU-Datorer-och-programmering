/*================================================================================
Datorer och programmering, DoP, 10 hsp, termin/år: Sommar/2020

Inlämningsuppgift nr 5

Namn: Daniel Gustafsson

Personummer: 19980827-5110

Den fil som jag lämnar in går att kompilera och
programmet fungerar för alla de testdata som finns för uppgiften: Ja

Jag har använt kompilator/editor (namn/version) GCC 9.2.1/  Visual Studio Code 1.44.2

Jag har använt följande dator (t.ex. PC, Mac, Annat):        PC
      med operativsystemet (t.ex. WindowsXP, Windows7,...) : Ubuntu 19.10

Jag har arbetat ungefär 1 timmar med denna uppgift

================================================================================*/

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Globala konstanter:
const int ANTAL_BOKSTAVER = 26;  //A-Z
const int ANTAL_SPRAK = 4;


const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
       {{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, //engelska
         7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
         0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
         1.89,0.03},
        {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, //franska
         7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
         1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
         0.30,0.15},
        {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,  //svenska
         3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
         0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
         0.45,0.00},
        {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, //tyska
         8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
         0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
         0.69,1.24}};

//--------------------------------------------------------
// H�r kommer klassdeklarationen 
class Text{
    private:
        string text;
        int antal;
        int histogram[ANTAL_BOKSTAVER];
        double histogramRel[ANTAL_BOKSTAVER];

    public:
        Text();
        void setText(string nyText);
        bool beraknaHistogramAbs();
        void beraknaHistogram();
        void skrivHistogramAbs();
        void absTillRel();
        void plottaHistogramRel();
        string tolka();
};

// -------------------------------------------------------
// Funktioner

// Läser in ett filnamn.
string namn_pa_fil(){
    string filnamn = "";
    cout << "Ange filnamn:" << endl;
    cin >> filnamn;
    return filnamn;
}

// Läser in en fil baserat på ett filnamn.
string inlasning(string filnamn){
    string text = "";
    string rad;
    ifstream fil(filnamn);
    if(!fil.is_open()) {
        cout << "Det finns ingen fil med namnet " + filnamn << endl;
        return "";
    }
    while(getline(fil, rad)) text.append(rad);
    fil.close();
    return text;
}

// Huvudprogram:

int main(){
    // Deklarera variabler
    string text;
    Text minText;  // Ett objekt av typen Text skapas

    // Läs in en text ifrån en fil
    text = inlasning(namn_pa_fil());
    if(text == "") return 0;

    // Skicka str�ngen text till objektet minText
    minText.setText( text );

    // Ber�kna och skriv ut histogrammet
    minText.beraknaHistogram();
    minText.plottaHistogramRel();
    cout << minText.tolka() << endl;

    return 0;
}

// -------------------------------------------------------
// Klassimplementationen
Text::Text():histogram {}, histogramRel {}{
    text = "";
    antal = 0;
}

void Text::setText(string nyText){
    text = nyText;
}

bool Text::beraknaHistogramAbs(){
    for(int i = 0; i < text.length(); i++){
        if(text[i] >= 'a') text[i] -= 'a';
        else text[i] -= 'A';
        if(text[i] >= 0 && text[i] < 26){
            histogram[text[i]]++;
            antal++;
        }
    }
    if(antal > 0) return true;
    else return false;
}

void Text::skrivHistogramAbs(){
    char bokstav = 'A';
    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        cout << bokstav << ": ";
        cout << histogram[i] << endl;
        bokstav++;
    }
}
void Text::absTillRel(){
    for(int i = 0; i < ANTAL_BOKSTAVER; i++)
        histogramRel[i] = (((double) histogram[i])/antal)*100;
}

void Text::plottaHistogramRel(){
    char bokstav = 'A';
    cout << "Bokstavsfördelning:" << endl << endl;
    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        cout << bokstav << " ";
        for(int j = 0; j < nearbyint(histogramRel[i]); j++){
            cout << '*';
        }
        cout << endl;
        bokstav++;
    }
}

void Text::beraknaHistogram(){
    if(beraknaHistogramAbs()) absTillRel();
}

string Text::tolka(){
    double kvadratsumma[ANTAL_SPRAK] = {};
    int most_likely = 0;
    for (int i = 0; i < ANTAL_SPRAK; i++){
        for(int j = 0; j < ANTAL_BOKSTAVER; j++)
            kvadratsumma[i] += pow(histogramRel[j] - TOLK_HJALP[i][j], 2);
        if(kvadratsumma[i] < kvadratsumma[most_likely]) most_likely = i;
    }
    switch(most_likely){
        case 0:
            return "engelska";
        case 1:
            return "franska";
        case 2:
            return "svenska";
        case 3:
            return "tyska";
        default:
            return "undefined";
    }
}

/*
================================================================================
Här följer programkörningar för alla testdata:
==============================================
TestB1

Ange filnamn:
doyle.txt
Bokstavsfördelning:

A ********
B *
C ***
D ****
E ************
F **
G *
H ******
I ********
J 
K *
L ****
M ***
N ******
O ********
P **
Q 
R ******
S ******
T *********
U ***
V *
W **
X 
Y **
Z 
engelska


TestB2

Ange filnamn:
goethe.txt
Bokstavsfördelning:

A *****
B **
C ****
D *****
E *****************
F *
G ***
H ******
I *********
J 
K *
L ***
M ***
N ***********
O **
P 
Q 
R ******
S *******
T ******
U ****
V *
W **
X 
Y *
Z *
tyska


TestB3

Ange filnamn:
lagerlof.txt
Bokstavsfördelning:

A ***********
B *
C *
D ******
E **********
F **
G ****
H ****
I ****
J *
K ***
L *****
M ****
N *********
O ****
P *
Q 
R *******
S *******
T *********
U **
V ***
W 
X 
Y 
Z 
svenska


TestB4

Ange filnamn:
verne.txt
Bokstavsfördelning:

A ********
B *
C ****
D ****
E *****************
F *
G *
H *
I *******
J 
K 
L *****
M ***
N ********
O *****
P ***
Q *
R *******
S ********
T *******
U ******
V *
W 
X *
Y 
Z 
franska


TestB5

Ange filnamn:
finnsInte.txt
Det finns ingen fil med namnet finnsInte.txt

================================================================================
Uppgiften gick ut på att beräkna ett histogram utifrån en text med hjälp av en klass.

Anledningen till att räkna ut båda i samma funktionsanrop är för att det blir
mycket lättare att räkna det relativa histogramet om man redan har ett absolut
histogram.

För att lösa problemet med ny text efter uträknat histogram kan man göra ett 
konstruktor anrop i setText innan man setar texten, då kommer antal, histogram
och histogramRel bli resettade.

Man kan inkludera funktionerna i klassen men det är väldigt dålig programmering.
Inläsningsfunktionerna borde inte vara en del av en klass vars syfte är att 
beräkna histogram och tolka en text, det borde vara en del av huvudprogrammet
eller en separat klass i så fall. Resultatet hade dock blivit samma i det här fallet.
*/