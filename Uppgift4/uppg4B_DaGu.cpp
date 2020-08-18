/*================================================================================
Datorer och programmering, DoP, 10 hsp, termin/år: Sommar/2020

Inlämningsuppgift nr 2

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

const int ANTAL_BOKSTAVER = 26;  //A-Z
const int ANTAL_SPRAK = 4;

// 2d-arrayen TOLK_HJALP inneh�ller bokstavsfrekvensen i %
// f�r fyra spr�k. TOLK_HJALP[0][0] �r frekvensen av
// bokstaven a f�r engelska.TOLK_HJALP[0][25] �r frekvensen av
// bokstaven z f�r engelska.
// Arrayen �r en GLOBAL KONSTANT och skall allts� ej skickas 
// som parameter till den funktion som beh�ver den.
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


//En simpel switch för att få vilket språk som är vilket index.
string get_lan(int i){
    switch(i){
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

//Beräknar ett histogram (hur många av varje bokstav) utifårn en text, returnerar hur många totala bokstäver som förekom.
int berakna_histogram_abs(string text, double histogram[]){
    int antal = 0;
    for(int i = 0; i < text.length(); i++){
        if(text[i] >= 'a') text[i] -= 'a';
        else text[i] -= 'A';
        if(text[i] >= 0 && text[i] < 26){
            histogram[text[i]]++;
            antal++;
        }
    }
    cout << "Totala antalet bokstäver: " << antal << endl;
    return antal;
}

//Beräknar om histogramets absoluta värden till relativa (10 x, 30 y => 25% x, 75% y)
void abs_till_rel(int antal, double histogram[]){
    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        histogram[i] = (histogram[i]/antal)*100;
    }
}

//Plottar ett histogram.
void plotta_histogram(double histogram[]){
    char bokstav = 'A';
    cout << "Bokstavsfördelning:" << endl << endl;
    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        cout << bokstav << " ";
        for(int j = 0; j < nearbyint(histogram[i]); j++){
            cout << '*';
        }
        cout << endl;
        bokstav++;
    }
}

//Tolkar baserat på ett histogram vilket språk som antagligen används i texten.
void tolka(double histogram[]){
    double kvadratsumma[ANTAL_SPRAK] = {};
    int most_likely = 0;
    for (int i = 0; i < ANTAL_SPRAK; i++){
        for(int j = 0; j < ANTAL_BOKSTAVER; j++){
            kvadratsumma[i] += pow(histogram[j] - TOLK_HJALP[i][j], 2);
        }
        cout << get_lan(i) + " har kvadratsumma= "   << kvadratsumma[i] << endl;
        if(kvadratsumma[i] < kvadratsumma[most_likely]) most_likely = i;
    }
    cout << "Det är mest troligt att språket är " + get_lan(most_likely) << endl << endl;
}

//Läser in ett filnamn.
string namn_pa_fil(){
    string filnamn = "";
    cout << "Ange filnamn:" << endl;
    cin >> filnamn;
    return filnamn;
}

//Läser in en fil baserat på ett filnamn.
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

int main(){
    string text;
    double histogram [ANTAL_BOKSTAVER] = {};
    int antal;  

    text = inlasning(namn_pa_fil());
    if(text == "") return 0;

    antal = berakna_histogram_abs(text, histogram);
    abs_till_rel(antal, histogram);
    tolka(histogram);
    plotta_histogram(histogram);

    return 0;
}

/*
================================================================================
Här följer programkörningar för alla testdata:
==============================================

TestB1

Ange filnamn:
doyle.txt

Totala antalet bokstäver: 12885
engelska har kvadratsumma= 1.75771
franska har kvadratsumma= 96.1956
svenska har kvadratsumma= 73.3371
tyska har kvadratsumma= 116.072
Det är mest troligt att språket är engelska

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


TestB2

Ange filnamn:
goethe.txt

Totala antalet bokstäver: 14027
engelska har kvadratsumma= 107.856
franska har kvadratsumma= 85.205
svenska har kvadratsumma= 160.318
tyska har kvadratsumma= 1.04313
Det är mest troligt att språket är tyska

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


TestB3

Ange filnamn:
lagerlof.txt

Totala antalet bokstäver: 12221
engelska har kvadratsumma= 86.6804
franska har kvadratsumma= 145.722
svenska har kvadratsumma= 8.88258
tyska har kvadratsumma= 170.223
Det är mest troligt att språket är svenska

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


TestB4

Ange filnamn:
verne.txt

Totala antalet bokstäver: 11417
engelska har kvadratsumma= 112.425
franska har kvadratsumma= 0.885142
svenska har kvadratsumma= 149.256
tyska har kvadratsumma= 90.491
Det är mest troligt att språket är franska

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


TestB5

Ange filnamn:
finnsInte.txt

Det finns ingen fil med namnet finnsInte.txt


================================================================================
Uppgiften gick ut på att beräkna ett histogram av en textfil.

Jag tror att syftet med att testa på en liten fil är för att enklare kunna identifiera
var det går fel (debugging), det kan vara svårare att se om en funktion fungerar om du 
inte vet om den ska returnera 12543 eller 13434 men 20 eller 25 är lättare.

För att inkludera specialkaraktärer som å, ä och ö skulle man kunna lägga till några specialfall
i berakna_histogram_abs funktionen. Istället för att titta på om ASCII-koden är mellan a-z så
kan man kolla a-z OCH å, ä och ö. Denna metod kan dock bli krånglig om man börjar inkludera många
olika språk med specialtecken, i det fallet kanske man borde göra ett histogram av alla tecken
och sedan skippa att plotta de som inte förekommer.
*/