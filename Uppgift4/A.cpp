#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

const int ANTAL_BOKSTAVER = 26;  //A-Z

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
    cout << text << endl << endl;
    

    antal = berakna_histogram_abs(text, histogram);
    skriv_histogram_abs(antal, histogram);

    return 0;
}