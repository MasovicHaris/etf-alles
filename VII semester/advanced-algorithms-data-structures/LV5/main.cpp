#include <iostream>
#include <utility>
#include <vector>
#include <sstream>
#include <cmath>

// Zadatak 1
class Formula3CNF {
    std::vector<std::vector<int>> klauze;
    std::vector<std::vector<int>> tabelaKombinacija;
    int n = 0;

    int provjeriKlauzeSaVrijednostima(std::vector<int> vrijednostiLiterala){
        // vrijednostLiterala je vektor: 1 1 0 0,
        // pod pretpostavkom da imamo 4 varijable
        // i salju se sve 4 varijable
        // tj. njihove values kao true/false odnosno 1/0

        int verificationControl = 1;

        for(unsigned int i = 0; i < klauze.size(); ++i){
            bool provjeraKlauza = false;
            for(unsigned int j = 0; j < klauze[i].size(); ++j){
                const int index = abs(klauze[i][j]) - 1;
                if(klauze[i][j] > 0 && vrijednostiLiterala[index]){
                    provjeraKlauza = true;
                    break;
                } else if (klauze[i][j] < 0 && !vrijednostiLiterala[index]) {
                    provjeraKlauza = true;
                    break;
                }
            }

            if(!provjeraKlauza) {
                verificationControl = 0;
                break;
            }
        }

        return verificationControl;
    }

    void generisiTabeluKombinacija(){
        std::vector<std::vector<int>> output(n, std::vector<int>(1 << n));

        unsigned num_to_fill = 1U << (n - 1);
        for(unsigned col = 0; col < n; ++col, num_to_fill >>= 1U)
        {
            for(unsigned row = num_to_fill; row < (1U << n); row += (num_to_fill * 2))
            {
                std::fill_n(&output[col][row], num_to_fill, 1);
            }
        }
        tabelaKombinacija = output;
    }

public:
    void unos3CNF(){
        std::cout << "Unesite 3-CNF formulu, za zavrsetak kliknuti enter: " << std::endl;

        std::string str;
        int i = 0;
        while(getline(std::cin, str)){
            if(str.empty()) break;
            klauze.emplace_back();

            std::istringstream ss(str);
            for (int k; ss >> k;) {
                klauze[i].push_back(k);
                if (abs(k) > n) n = abs(k);
                if (ss.peek() == ',') ss.ignore();
            }
            ++i;
        }

        generisiTabeluKombinacija();
    }

    int rjesenje3CNF(){
        int provjera = 0;
        for(unsigned x = 0; x < (1 << n); ++x){
            std::vector<int> temp;
            for(unsigned y = 0; y < n; ++y) temp.push_back(tabelaKombinacija[y][x]);

            if(provjeriKlauzeSaVrijednostima(temp)){
                provjera = 1;
                break;
            }
        }
        return provjera;
    }

    int verifikacija3CNF(std::vector<int> vrijednostiLiterala){
        return provjeriKlauzeSaVrijednostima(std::move(vrijednostiLiterala));
    }
};

// Zadatak 2
class KlikaINDSETGraf {
    std::vector<std::vector<int>> grafMatrica;
    std::vector<std::vector<int>> kontraMatrica;

    std::vector<std::vector<int>> susjediMatrica;
    std::vector<std::vector<int>> susjediKontraMatrica;

    // provjera independent seta tj. k vrijednosti independent seta
    // koristeci algoritam bojenje cvorova tj. pamcenje setova povezanosti (obojanih)
    // i eliminisuci susjede
    // ovaj algoritam se moze svesti i na k-klika problem, samo ako se obrnu matrice tj.
    // values 0 i 1 pri unosu i naprave nove, kao sto je uradjeno ovdje

    int dajBrojCvorovaPovezanosti(const std::vector<int> &setCvorova) {
        // prima setCvorova i vraca broj cvorova koji su povezani
        // sa cvorom odakle se poziva funkcija
        int count = 0;
        for (int i = 0; i < setCvorova.size(); i++) if (setCvorova[i] == 1) count++;
        return count;
    }

    std::vector<int> eliminisiSveSusjedneCvoroveUSetu(const std::vector<std::vector<int>> &susjedi, std::vector<int> setCvorova) {
        std::vector<int> tempSet = std::move(setCvorova);
        int r = 0;
        while (r != -1) {
            r = maxPovezanostCvorova(susjedi, tempSet);
            if (r != -1) tempSet[r] = 0;
        }
        return tempSet;
    }

    int maxPovezanostCvorova(std::vector<std::vector<int>> susjedi, std::vector<int> setCvorova){
        // pronalazak cvora koji ima najvise povezanosti
        // sa svim ostalim cvorovima
        // vraca se index tog cvora
        int r = -1, max = -1;
        for (unsigned  int i = 0; i < setCvorova.size(); i++) { // prelazak svih cvorova susjeda
            if (setCvorova[i] == 1 && provjeraSusjedaUSetu(susjedi[i], setCvorova)) {
                // cilj je zapamtiti susjedni cvor za koji
                // se dobija najveca povezanost sa ostalim pocetnim susjedima
                // npr. 2 cvora su povezana a ujedno su susjedi prvobitnog
                std::vector<int> tempSet = setCvorova;
                tempSet[i] = 0;
                int sum = 0;
                for (unsigned int j = 0; j < tempSet.size(); j++) if (tempSet[j] == 1 && provjeraSusjedaUSetu(susjedi[j], tempSet)) sum++;

                if (sum > max) {
                    max = sum;
                    r = i;
                }
            }
        }
        return r;
    }

    bool provjeraSusjedaUSetu(const std::vector<int> &susjedi, const std::vector<int> &setCvorova) {
        bool check = true;
        for (unsigned int i = 0; i < susjedi.size(); i++)
            if (setCvorova[susjedi[i]] == 0) {
                check = false;
                break;
            }
        return check;
    }

    std::vector<int> provjeraVanjskihCvorova(std::vector<std::vector<int>> susjedi, std::vector<int> setCvorova, int k) {
        int count = 0;
        std::vector<int> tempSet = setCvorova;
        for (unsigned int i = 0; i < tempSet.size(); i++) {
            if (tempSet[i] == 1) {
                int sum = 0, index = 0;
                // pronalazak svih cvorova susjeda, koji nisu povezani sa inicijalnim cvorom
                for (unsigned  int j = 0; j < susjedi[i].size(); j++) if (tempSet[susjedi[i][j]] == 0) { index = j; sum++; }

                // ukoliko se nadje takav jedan cvor, treba se postaviti njegova povezanost kao 1
                // te se ispitati jel povezan taj cvor sa inicijalnom pozivom eliminisiSveSusjedneCvoroveUSetu u trenutnom setu
                // i povecati counter
                if (sum == 1 && setCvorova[susjedi[i][index]] == 0) {
                    tempSet[susjedi[i][index]] = 1;
                    tempSet[i] = 0;
                    tempSet = eliminisiSveSusjedneCvoroveUSetu(susjedi, tempSet);
                    count++;
                }
                // ukoliko je nas counter presao vrijednost trazenog k, mozemo terminirati
                if (count > k) break;
            }
        }
        // vratiti tempSet i izmjeriti koliko ima nula za nas cvor tj. nepovezanost sa ostalim cvorovima
        return tempSet;
    }


    int pronalazakIndependetSetaKlike(int trazenoK, std::vector<std::vector<int>> &matrica, std::vector<std::vector<int>> &susjedi) {
        // pomocna funkcija pomocu koje saznajemo minimal independet set/k klike
        // a ujedno gledamo da li je pronadjen independent set

        bool found = false;
        int k = int(matrica.size()) - trazenoK;
        int min = int(matrica.size()) + 1;

        std::vector<int> sviSetoviCvorova;

        // postavljanje defaultnog setaCvorova koji ce se ponavljati iteracijama
        for(unsigned int i = 0; i < matrica.size(); ++i) sviSetoviCvorova.push_back(1);

        for(unsigned int i = 0; i < sviSetoviCvorova.size(); ++i) {
            std::vector<int> noviSet = sviSetoviCvorova;
            noviSet[i] = 0; // skidanje 1 sa samog cvora

            noviSet = eliminisiSveSusjedneCvoroveUSetu(susjedi, noviSet);
            int s = dajBrojCvorovaPovezanosti(noviSet); // poziv za dobijanje broja povezanih cvorova
            if (s < min) min = s;
            if (s <= k) {
                found = true;
                break;
            }

            for (int j = 0; j < k; j++) noviSet = provjeraVanjskihCvorova(susjedi, noviSet, j);
            s = dajBrojCvorovaPovezanosti(noviSet);
            if (s < min) min = s;
            if (s <= k) {
                found = true;
                break;
            }
        }

        return found;
    }

    bool testirajVeririfikaciju(const std::vector<int> &testVrijednosti, const std::vector<std::vector<int>> &matrica, int trueOrFalse) {
        bool check = true;
        for(unsigned int i = 0; i < testVrijednosti.size(); ++i) {
            for(unsigned int j = 0; j < testVrijednosti.size(); ++j) {
                if(i == j) continue;
                if (grafMatrica[testVrijednosti[i]][testVrijednosti[j]] != trueOrFalse
                    || grafMatrica[testVrijednosti[j]][testVrijednosti[i]] != trueOrFalse) {
                    check = false;
                    break;
                }
            }
        }
        return check;
    }

public:
    void unosGrafa() {
        int size;
        std::cout << "Unesite broj redova i kolona: " << std::endl;
        std::cin >> size;
        std::cout << "Unesite elemente matrice: " << std::endl;

        grafMatrica.resize(size);
        kontraMatrica.resize(size);

        for(int i = 0; i < size; ++i) {
            grafMatrica[i].resize(size);
            kontraMatrica[i].resize(size);
            for(int j = 0; j < size; ++j){
                int temp;
                std::cin >> temp;
                grafMatrica[i][j] = temp;
                if(!temp) kontraMatrica[i][j] = 1;
                else kontraMatrica[i][j] = 0;
            }
        }

        // cuvanje indexa susjeda
        // pronalazak susjeda za prvi problem
        for (unsigned int i = 0; i < grafMatrica.size(); i++) {
            std::vector<int> neighbor;
            for (int j = 0; j < grafMatrica[i].size(); j++) if (grafMatrica[i][j] == 1) neighbor.push_back(j);
            susjediMatrica.push_back(neighbor);
        }

        // pronalazak susjeda za drugi problem
        for (unsigned int i = 0; i < kontraMatrica.size(); i++) {
            std::vector<int> neighbor;
            for (int j = 0; j < kontraMatrica[i].size(); j++) if (kontraMatrica[i][j] == 1) neighbor.push_back(j);
            susjediKontraMatrica.push_back(neighbor);
        }

    }

    // K-INDSET
    int rjesenjeKIndSet(int trazenoK) {
        return pronalazakIndependetSetaKlike(trazenoK, grafMatrica, susjediMatrica);
    }

    int verifikacijaSkupaNezavisnihCvorova(const std::vector<int> &testNezavisniCvorovi) {
        return testirajVeririfikaciju(testNezavisniCvorovi, grafMatrica, 0) ? 1 : 0;
    }

    // K-CLIQUE
    int rjesenjeKKlique(int trazenoK) {
        return pronalazakIndependetSetaKlike(trazenoK, kontraMatrica, susjediKontraMatrica);
    }

    int verifikacijaKKlike(const std::vector<int> &testKlike) {
        return testirajVeririfikaciju(testKlike, kontraMatrica, 1) ? 1 : 0;
    }

};





int main() {
    Formula3CNF novi;
    KlikaINDSETGraf klikaIndSetNovi;

    int opcija;
    int broj;
    std::vector<int> verifikacioniVektor;

    do {
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << "Izaberite opciju -" << std::endl;
        std::cout << "1) Unos formule" << std::endl;
        std::cout << "2) Unos grafa" << std::endl;
        std::cout << "3) Je li formula ispunjiva" << std::endl;
        std::cout << "4) Postoji li k-nezavisnih cvorova" << std::endl;
        std::cout << "5) Postoji li k-klika" << std::endl;
        std::cout << "6) Verifikacija formule" << std::endl;
        std::cout << "7) Verifikacija skupa nezavisnih cvorova" << std::endl;
        std::cout << "8) Verifikacija k-klike" << std::endl;
        std::cout << "9) Izlaz" << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cin >> opcija;
        switch (opcija){
            case 1:
                std::cin.clear();
                std::cin.ignore();
                novi.unos3CNF();
                break;
            case 2:
                std::cin.clear();
                std::cin.ignore();
                klikaIndSetNovi.unosGrafa();
                break;
            case 3:
                std::cout << "Ispunjivost formule: " << novi.rjesenje3CNF() << std::endl;
                break;
            case 4:
                std::cout << "Provjeriti jel postoji nezavisnih cvorova stepena: " << std::endl;
                std::cin >> broj;
                std::cout << "Postojanje " << broj << " nezavisnih covora: " << klikaIndSetNovi.rjesenjeKIndSet(broj) << std::endl;
                break;
            case 5:
                std::cout << "Provjeriti jel postoji k-klika stepena: " << std::endl;
                std::cin >> broj;
                std::cout << "Postojanje k-klike stepena " << broj << ": " << klikaIndSetNovi.rjesenjeKKlique(broj) << std::endl;
                break;
            case 6:
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Unesite vrijednosti literala, za zavrsetak unijeti -1:  " << std::endl;

                do {
                    std::cin >> broj;
                    if(broj != -1) verifikacioniVektor.push_back(broj);
                } while(broj != -1);

                std::cout << "Verifikacija unesene vrijednosti: " << novi.verifikacija3CNF(verifikacioniVektor) << std::endl;
                break;
            case 7:
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Unesite nezavisne cvorove numerisano od 0, za zavrsetak unijeti -1:  " << std::endl;

                do {
                    std::cin >> broj;
                    if(broj != -1) verifikacioniVektor.push_back(broj);
                } while(broj != -1);

                std::cout << "Verifikacija skupa nezavisnih cvorova: " << klikaIndSetNovi.verifikacijaSkupaNezavisnihCvorova(verifikacioniVektor) << std::endl;
                break;
            case 8:
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Unesite k kliku numerisano od 0, za zavrsetak unijeti -1:  " << std::endl;

                do {
                    std::cin >> broj;
                    if(broj != -1) verifikacioniVektor.push_back(broj);
                } while(broj != -1);

                std::cout << "Verifikacija k klike: " << klikaIndSetNovi.verifikacijaKKlike(verifikacioniVektor) << std::endl;
                break;
            default:
                break;
        }
    } while (opcija != 9);
    return 0;
}

// primjer unosa
// 0 1 1 1 1
// 1 0 0 0 0
// 1 0 0 0 0
// 1 0 0 0 0
// 1 0 0 0 0
// ima 4 nezavisna cvora
// nema klike nikakve

// test broj 2
// 0 1 1 1
// 1 0 1 1
// 1 1 0 1
// 1 1 1 0
// ima klika velicine 4
// nema nezavisnih cvorova