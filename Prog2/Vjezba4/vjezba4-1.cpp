#include<iostream>
#include<fstream>
#include "../biblioteka_vrijeme_linux.cc"

struct slog{
    int sifra;
    char prez_ime[50];
    char naslov[50];
    double vrijeme;
};

void unos(){
    std::fstream datoteka("podatci.dat", std::ios::app | std::ios::binary); //otvori datoteku u append modu
    slog element; //inicijaliziraj element

    std::cout << "\n---UNOS---\n"; //pocetak unosa
    vrijeme_pocetak();
    std::cout << "Sifra: "; std::cin >> element.sifra; std::cin.ignore();
    std::cout << "Ime i prezime autora: "; std::cin.getline(element.prez_ime, 50);
    std::cout << "Naslov dijela: "; std::cin.getline(element.naslov, 50);
    vrijeme_kraj();
    element.vrijeme = vrijeme_proteklo();
    std::cout << "----------\n\n"; //kraj unosa

    datoteka.write((char*)&element, sizeof(element)); //.write koji zapise sve to na kraj datoteke (append)

    //zatvori datoteku
    datoteka.close();
    datoteka.clear();
}

void unos_provjera(){
    std::fstream datoteka("podatci.dat", std::ios::in | std::ios::app | std::ios::binary); //otvori datoteku u modu za citanje i dodavanje na kraj
    slog element; //inicijaliziraj element ZA CITANJE
    slog element_unos; //element za unos
    bool pronaden = false;

    std::cout << "\n---UNOS---\n"; //pocetak unosa -- koristi element_unos
    vrijeme_pocetak();
    std::cout << "Sifra: "; std::cin >> element_unos.sifra; std::cin.ignore();
    std::cout << "Ime i prezime autora: "; std::cin.getline(element_unos.prez_ime, 50);
    std::cout << "Naslov dijela: "; std::cin.getline(element_unos.naslov, 50);
    vrijeme_kraj();
    element_unos.vrijeme = vrijeme_proteklo();
    std::cout << "----------\n"; //kraj unosa

    std::cout << "\n";
    while(true){ //iteriraj do kraja
        datoteka.read((char*)&element, sizeof(element)); //procitaj element -- NE ELEMENT_UNOS
        if(datoteka.eof()) break;
        if (element.sifra == element_unos.sifra) pronaden = true; break; //ako pronades, postavi pronaden i breakaj
    }

    if(pronaden){
        std::cout << "Ne mogu upisati stavku, vec postoji element s tom sifrom\n\n";
    }else{
        datoteka.write((char*)&element_unos, sizeof(element_unos));
    }

    //zatvori datoteku
    datoteka.close();
    datoteka.clear();
}

void ispis(){
    std::fstream datoteka("podatci.dat", std::ios::in | std::ios::binary); //otvori datoteku u read modu
    slog element; //inicijaliziraj element
    std::cout << "\n";

    while(true){ //vrti dok ne breakas manually
        datoteka.read((char*)&element, sizeof(element)); //procitaj stavku u datoteci
        if(datoteka.eof()) break; //ako je stavka eof() breakaj loop, uostalom ispisi

        std::cout << "---ELEMENT---\n";
        std::cout << "Sifra: " << element.sifra << "\n";
        std::cout << "Ime i prezime: " << element.prez_ime << "\n";
        std::cout << "Naslov dijela: " << element.naslov << "\n";
        std::cout << "-------------\n";
    }
    std::cout << "\n";
    //zatvori datoteku
    datoteka.close();
    datoteka.clear();
}

void pretrazivanje(){
    std::fstream datoteka("podatci.dat", std::ios::in | std::ios::binary); //ucitaj datoteku u modu za citanje
    slog element; //inicijaliziraj element
    int sifra;
    std::cout << "\nUnesite primarni kljuc elementa kojeg trazite: "; std::cin >> sifra;

    while(true){ //iteriraj kroz datoteku
        datoteka.read((char*)&element, sizeof(element)); //procitaj stavku iz datoteke
        if(datoteka.eof()) break; //ako je kraj breakaj
        if(element.sifra == sifra){ //ako je pronaden element s sifrom -- ispisi ju
            std::cout << "---ELEMENT---\n";
            std::cout << "Sifra: " << element.sifra << "\n";
            std::cout << "Ime i prezime: " << element.prez_ime << "\n";
            std::cout << "Naslov dijela: " << element.naslov << "\n";
            std::cout << "-------------\n";
            break;
        }
    }

    //zatvori datoteku
    datoteka.close();
    datoteka.clear();
}

int main(){
    int izbor = 0;
    do{
        std::cout << "Izbornik:\n";
        std::cout << "  1. Unos podataka u datoteku\n";
        std::cout << "  2. Unos uz provjeru jedinstvenosti primarnog kljuca\n";
        std::cout << "  3. Ispis sadrzaja cijele datotek\n";
        std::cout << "  4. Pretrazivanje datoteke\n";
        std::cout << "  9. Izlaz iz programa\n";
        std::cout << "Izbor: "; std::cin >> izbor;

        switch(izbor){
            case 1: unos(); break;
            case 2: unos_provjera(); break;
            case 3: ispis(); break;
            case 4: pretrazivanje(); break;
            case 9: break;
            default: std::cout << "Pogresan unos\n";
        }
    }while(izbor != 9);
}