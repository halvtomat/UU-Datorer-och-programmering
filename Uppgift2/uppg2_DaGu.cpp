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

Jag har arbetat ungefär  2 timmar med denna uppgift

================================================================================*/

#include <iostream>
using namespace std;

int main(){
    int antalTavlande = 0;
    int bastStartNummer = -1;
    int bastSlutTid = 25 * 3600;
    bool running = true;

    while(running){
        int startNummer, slutTid, startTid, malTid;
        int startSek, startMin, startTim;
        int malSek, malMin, malTim;

        cout << "Startnummer?"<< endl;
        cin >> startNummer;
        if(startNummer <= 0){
            running = false;
        }
        else{
            cout << "Starttid?"<< endl;
            cin >> startTim >> startMin >> startSek;

            cout << "Måltid?" << endl;
            cin >> malTim >> malMin >> malSek;

            antalTavlande++;

            startTid = startTim * 3600 + startMin * 60 + startSek;
            malTid = malTim * 3600 + malMin * 60 + malSek;

            if(malTid < startTid) slutTid = malTid - (startTid - 24 * 3600);
            else slutTid = malTid - startTid;

            if(slutTid < bastSlutTid){
                bastSlutTid = slutTid;
                bastStartNummer = startNummer;
            };
        }
    }

    if(antalTavlande == 0) cout << "Inga tävlande" << endl;
    else{
        cout << "Vinnar är startnr: " << bastStartNummer << endl;
        cout << "Tim: " << bastSlutTid/3600 << " Min: " << (bastSlutTid%3600)/60 << " Sek: " << bastSlutTid%60 << endl;
        cout << "Antal Tävlande: " << antalTavlande << endl;
    }

    cout << "Programmet avslutas" << endl;
    return 0;
}

/*
================================================================================
Här följer programkörningar för alla testdata:
==============================================

Startnummer? 33
Starttid? 17 30 15
Måltid? 18 22 35
Startnummer? -1
Vinnar är startnr: 33
Tim: 0 Min: 52 Sek: 20
Antal Tävlande: 1
Programmet avslutas
 
Startnummer? 33
Starttid? 0 30 15
Måltid? 19 22 35
Startnummer? -1
Vinnar är startnr: 33
Tim: 18 Min: 52 Sek: 20
Antal Tävlande: 1
Programmet avslutas
 
Startnummer? 33
Starttid? 17 30 15
Måltid? 18 22 35
Startnummer? 14
Starttid? 23 35 0
Måltid? 0 12 24
Startnummer? 26
Starttid? 10 11 12
Måltid? 20 21 22
Startnummer? -1
Vinnar är startnr: 14
Tim: 0 Min: 37 Sek: 24
Antal Tävlande: 3
Programmet avslutas
 
Startnummer? 14
Starttid? 23 35 0
Måltid? 0 12 24
Startnummer? 26
Starttid? 10 11 12
Måltid? 20 21 22
Startnummer? 33
Starttid? 17 30 15
Måltid? 18 22 35
Startnummer? -1
Vinnar är startnr: 14
Tim: 0 Min: 37 Sek: 24
Antal Tävlande: 3
Programmet avslutas
 
Startnummer? 26
Starttid? 10 11 12
Måltid? 20 21 22
Startnummer? 33
Starttid? 17 30 15
Måltid? 18 22 35
Startnummer? 14
Starttid? 23 35 0
Måltid? 0 12 24
Startnummer? -1
Vinnar är startnr: 14
Tim: 0 Min: 37 Sek: 24
Antal Tävlande: 3
Programmet avslutas
 
Startnummer? 17
Starttid? 0 0 50
Måltid? 0 0 30
Startnummer? -1
Vinnar är startnr: 17
Tim: 23 Min: 59 Sek: 40
Antal Tävlande: 1
Programmet avslutas
 
Startnummer? -1
Inga tävlande
Programmet avslutas
 
Startnummer? 15
Starttid? 10 0 0
Måltid? 11 0 0
Startnummer? 12
Starttid? 11 0 0
Måltid? 10 0 10
Startnummer? -1
Vinnar är startnr: 15
Tim: 1 Min: 0 Sek: 0
Antal Tävlande: 2
Programmet avslutas
 
Startnummer? 8
Starttid? 0 0 10
Måltid? 0 0 20
Startnummer? -1
Vinnar är startnr: 8
Tim: 0 Min: 0 Sek: 10
Antal Tävlande: 1
Programmet avslutas

================================================================================
Uppgiften gick ut på att beräkna den vinnande tiden av olika löpare utifrån endast start och sluttid.
Svårigheten va att översätta timmar, minuter och sekunder till bara sekunder för att kunna jämföra olika tider.

Om två har samma sluttid så vinner den första eftersom att programmet testar ifall den nya tiden är kortare
än den förre bästa, vilket den inte är för den är samma, och därför kommer det inte uppdatera den bästa tiden.

Vi har många testdata för att se till så att programmet kan hantera många (helst alla) "corner cases", 
det vill säga att programmet inte bara kan hantera de allra normalaste fallen eller vissa specifika fall.

Att skriva tester före programmet gör det lättare att veta hur man ska designa sin kod, det är bara att se
till så den klarar testerna.
*/