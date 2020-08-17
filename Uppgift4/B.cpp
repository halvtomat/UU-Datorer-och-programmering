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

int berakna_histogram_abs(string text, double histogram[]){
    cout << "a" << endl;
    int antal = 0;
    for(int i = 0; i < text.length(); i++){
        if(text[i] >= 'a') text[i] -= 'a';
        else text[i] -= 'A';
        if(text[i] >= 0 && text[i] < 26){
            histogram[text[i]]++;
            antal++;
        }
        cout << i << endl;
    }
    cout << "Totala antalet bokstäver: " + antal << endl;
    return antal;
}

void abs_till_rel(int antal, double histogram[]){
    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        histogram[i] = (histogram[i]/antal)*100;
    }
}

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

void tolka(double histogram[]){
    double kvadratsumma[ANTAL_SPRAK] = {};
    int most_likely = 0;
    for (int i = 0; i < ANTAL_SPRAK; i++){
        for(int j = 0; j < ANTAL_BOKSTAVER; j++){
            kvadratsumma[i] += pow(histogram[j] - TOLK_HJALP[i][j], 2);
        }
        cout << get_lan(i) + " har kvadratsumma= "   << kvadratsumma[i] << endl;
        if(kvadratsumma[i] > kvadratsumma[most_likely]) most_likely = i;
    }
    cout << "Det är mest troligt att språket är " + get_lan(most_likely) << endl << endl;
}

string namn_pa_fil(){
    string filnamn = "";
    cout << "Ange filnamn:" << endl;
    cin >> filnamn;
    return filnamn;
}

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