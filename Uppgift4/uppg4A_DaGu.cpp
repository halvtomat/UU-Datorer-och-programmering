/*================================================================================
Datorer och programmering, DoP, 10 hsp, termin/år: Sommar/2020

Inlämningsuppgift nr 4

Namn: Daniel Gustafsson

Personummer: 19980827-5110

Den fil som jag lämnar in går att kompilera och
programmet fungerar för alla de testdata som finns för uppgiften: Ja

Jag har använt kompilator/editor (namn/version) GCC 9.2.1/  Visual Studio Code 1.44.2

Jag har använt följande dator (t.ex. PC, Mac, Annat):        PC
      med operativsystemet (t.ex. WindowsXP, Windows7,...) : Ubuntu 19.10

Jag har arbetat ungefär 1 timmar med denna uppgift

================================================================================*/

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

const int ANTAL_BOKSTAVER = 26;  //A-Z

//Beräknar ett histogram (hur många av varje bokstav) utifårn en text, returnerar hur många totala bokstäver som förekom.
int berakna_histogram_abs(string text, int histogram[]){
    int antal = 0;
    for(int i = 0; i < text.length(); i++){
        if(text[i] >= 'a') text[i] -= 'a';
        else text[i] -= 'A';
        if(text[i] >= 0 && text[i] < 26){
            histogram[text[i]]++;
            antal++;
        }
    }
    return antal;
}

//Skriver ut ett histogram på ett (för människor) lättläst sett.
void skriv_histogram_abs(int antal, int histogram []){
    char bokstav = 'A';
    cout << "Resultat för bokstäverna A-Z" << endl << endl;
    cout << "Totala antalet bokstäver: " << antal << endl;
    cout << "Bokstavsfördelning:" << endl << endl;
    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        cout << bokstav << ": ";
        cout << histogram[i] << endl;
        bokstav++;
    }
}

int main(){
    string text;
    int histogram [ANTAL_BOKSTAVER] = {};
    int antal;
  
    cout << "Ge en rad med text:" << endl;
    getline(cin, text);

    antal = berakna_histogram_abs(text, histogram);
    skriv_histogram_abs(antal, histogram);

    return 0;
}

/*
================================================================================
Här följer programkörningar för alla testdata:
==============================================

TestA1

Ge en rad med text:
AbCdNNooPPwXyZ

Resultat för bokstäverna A-Z

Totala antalet bokstäver: 14
Bokstavsfördelning:

A: 1
B: 1
C: 1
D: 1
E: 0
F: 0
G: 0
H: 0
I: 0
J: 0
K: 0
L: 0
M: 0
N: 2
O: 2
P: 2
Q: 0
R: 0
S: 0
T: 0
U: 0
V: 0
W: 1
X: 1
Y: 1
Z: 1


TestA2

Ge en rad med text:
1234ddddacccbb!?

Resultat för bokstäverna A-Z

Totala antalet bokstäver: 10
Bokstavsfördelning:

A: 1
B: 2
C: 3
D: 4
E: 0
F: 0
G: 0
H: 0
I: 0
J: 0
K: 0
L: 0
M: 0
N: 0
O: 0
P: 0
Q: 0
R: 0
S: 0
T: 0
U: 0
V: 0
W: 0
X: 0
Y: 0
Z: 0


TestA3

Ge en rad med text:
Denna rad innehåller ett å!

Resultat för bokstäverna A-Z

Totala antalet bokstäver: 20
Bokstavsfördelning:

A: 2
B: 0
C: 0
D: 2
E: 4
F: 0
G: 0
H: 1
I: 1
J: 0
K: 0
L: 2
M: 0
N: 4
O: 0
P: 0
Q: 0
R: 2
S: 0
T: 2
U: 0
V: 0
W: 0
X: 0
Y: 0
Z: 0


TestA4

Ge en rad med text:


Resultat för bokstäverna A-Z

Totala antalet bokstäver: 0
Bokstavsfördelning:

A: 0
B: 0
C: 0
D: 0
E: 0
F: 0
G: 0
H: 0
I: 0
J: 0
K: 0
L: 0
M: 0
N: 0
O: 0
P: 0
Q: 0
R: 0
S: 0
T: 0
U: 0
V: 0
W: 0
X: 0
Y: 0
Z: 0


================================================================================
Uppgiften gick ut på att beräkna ett histogram av en rad text.

(Svar på frågor finns i 4B)
*/