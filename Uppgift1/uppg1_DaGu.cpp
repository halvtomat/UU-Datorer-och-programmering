/*
================================================================================
Datorer och programmering, DoP, 10 hsp, termin/år:Sommar/2020

Inlämningsuppgift nr 1

Namn: Daniel Gustafsson

Personummer: 19980827-5110

Fyll i (alt. stryk det som INTE är relevant) av nedanstående:

Den fil som jag lämnar in går att kompilera och
programmet fungerar för alla de testdata som finns för uppgiften: Ja

Jag har använt kompilator/editor (namn/version) gcc 9.2.1/Visual studio code 1.46

Jag har använt följande dator (t.ex. PC, Mac, Annat):        PC
      med operativsystemet (t.ex. WindowsXP, Windows7,...) : Ubuntu 19.10

Jag har arbetat ungefär  0.000001 timmar med denna uppgift

================================================================================
*/

#include <iostream>
using namespace std;

int main(){

  int a;
  int b = 12;
  a = 0;        //; tillagt

  cout << "a = " << a << endl;
  cout << a+b << '\n' << "a-b = " << a-b << endl;

  return 0;
}

/*
================================================================================
Här följer programkörningar för alla testdata:
==============================================

a = 0
12
a-b = -12

================================================================================
Här skriver du en kort rapport om uppgiften:

Kompileringsfelet som uppstod var på grund av ett saknat semicolon.

*/