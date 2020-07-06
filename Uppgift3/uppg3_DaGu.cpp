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

Jag har arbetat ungefär 1 timmar med denna uppgift

================================================================================*/

#include <iostream>
using namespace std;

//Skriver ut info om programmet
void skrivInfo(){
    cout << "Det här programmet läser in 2 tal och en operator för att sedan göra en beräkning och skriva ut svaret" << endl;
}

//Läser in ett tal från cin och returnerar det.
int lasEttTal(){
    int tal;
    cout << "Skriv in ett tal: " << endl;
    cin >> tal;
    return tal;
}

//Läser in en karaktär från cin och returnerar den.
char lasOp(){
    char op;
    cout << "Skriv in en operator: " << endl;
    cin >> op;
    return op;
}

//Tar in 2 tal och ser till så att tal1 är det mindre talet.
void ordna(int* tal1, int* tal2){
    if(*tal1 > *tal2){
        int temp = *tal1;
        *tal1 = *tal2;
        *tal2 = temp;
    }
}

//Utför en beräkning beroende på en operator-karaktär och 2 tal.
long berakna(int tal1, int tal2, char op){
    long svar = 0;
    switch (op){
        case 'a':
            for(tal1; tal1 <= tal2; tal1++){
                svar += tal1;
            }
            break;

        case 'm':
            svar = 1;
            for(tal1; tal1 <= tal2; tal1++){
                svar *= tal1;
            }
            break;

        case 'k':
            for(tal1; tal1 <= tal2; tal1++){
                svar += (tal1 * tal1);
            }
            break;

        default:
            cout << "Ogiltig operator" << endl;
            break;
    }
    return svar;
}

//Skriver ut ett resultat.
void skrivResultat(long svar){
    cout << "Svaret är: " << svar << endl;
}

int main(){

    int tal1, tal2;
    long svar;
    char op;

    skrivInfo();

    tal1 = lasEttTal();
    tal2 = lasEttTal();
    op = lasOp();

    ordna(&tal1, &tal2);

    svar = berakna(tal1, tal2, op);

    skrivResultat(svar);

    return 0;
}

/*
================================================================================
Här följer programkörningar för alla testdata:
==============================================

Det här programmet läser in 2 tal och en operator för att sedan göra en beräkning och skriva ut svaret
Skriv in ett tal: 3
Skriv in ett tal: 5
Skriv in en operator: a
Svaret är: 12
 
Det här programmet läser in 2 tal och en operator för att sedan göra en beräkning och skriva ut svaret
Skriv in ett tal: 3
Skriv in ett tal: 5
Skriv in en operator: m
Svaret är: 60
 
Det här programmet läser in 2 tal och en operator för att sedan göra en beräkning och skriva ut svaret
Skriv in ett tal: 3
Skriv in ett tal: 5
Skriv in en operator: k
Svaret är: 50
 
Det här programmet läser in 2 tal och en operator för att sedan göra en beräkning och skriva ut svaret
Skriv in ett tal: -3
Skriv in ett tal: 5
Skriv in en operator: m
Svaret är: 0
 
Det här programmet läser in 2 tal och en operator för att sedan göra en beräkning och skriva ut svaret
Skriv in ett tal: 5
Skriv in ett tal: 3
Skriv in en operator: a
Svaret är: 12
 
Det här programmet läser in 2 tal och en operator för att sedan göra en beräkning och skriva ut svaret
Skriv in ett tal: -3
Skriv in ett tal: -5
Skriv in en operator: a
Svaret är: -12
 
Det här programmet läser in 2 tal och en operator för att sedan göra en beräkning och skriva ut svaret
Skriv in ett tal: 1
Skriv in ett tal: 100
Skriv in en operator: k
Svaret är: 338350
 
Det här programmet läser in 2 tal och en operator för att sedan göra en beräkning och skriva ut svaret
Skriv in ett tal: 1
Skriv in ett tal: 1000
Skriv in en operator: m
Svaret är: 0

================================================================================
Uppgiften gick ut på att göra beräkningar beroende på 2 tal och en operator. Den enda svårigheten med den
här uppgiften var att det stod att pointers inte fick användas men samtidigt förväntades man använda
"referensparametrar"(pointers), eftersom att "referensparametrar" är pointers trodde jag inte det var tillåtet.

Funktioner är bra när man ska utföra samma sekvens flera gånger, i det här programmet känns det överflödigt
men funktioner kan också göra programmet lite mer lättläst (för oss människor).

Referensparametrar ska bara användas när man vill ändra på en specifik variabel som redan finns, om det användes
i andra fall finns risken att man råkar skriva över ett värde som man behövde spara.
*/