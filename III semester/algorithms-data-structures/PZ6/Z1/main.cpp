#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

// bubble sort
template <typename Tip>
void bubble_sort(Tip* niz, int vel) {
    for (int i= vel-1; i >= 1; --i) {
        for (int j=1; j <=i; j++) {
            if (niz[j-1] > niz[j]) {
                auto temp(niz[j-1]);
                niz[j-1]=niz[j];
                niz[j] = temp;
            }
        }
    }
}

// selection sort
template <typename Tip>
void selection_sort(Tip* niz, int vel) {
    for (int i=0; i<= vel-2; i++) {
        Tip min = niz[i];
        int pmin = i;
        for (int j=i+1; j <= vel-1; j++) {
            if(niz[j] < min) {
                min = niz[j];
                pmin=j;
            }
        }
        niz[pmin]=niz[i];
        niz[i]=min;
    }
}

// merge sort
template <typename Tip>
void merge2(Tip* prvi, int l, int p, int q, int u) {                  // spajanje nizova
    int i=0, j=q-l, k=l;
    auto pomocni = new Tip[u-l+1];                                    // kreiranje pomocnog
    for (int m=0; m <=u-l; m++) pomocni[m] = prvi[l+m];               // cp prvi u pomocni

    while (i <= (p-l) && j <= (u-l)) {                                // metoda odaberi
        if (pomocni[i] < pomocni[j]) {
            prvi[k] = pomocni[i];
            i++;
        } else {
            prvi[k] = pomocni[j];
            j++;
        }
        k++;
    }
    while (i <= p-l) {                                                // dodaj ako fali 1
        prvi[k] = pomocni[i];
        i++; k++;
    }
    while (j <= u-l) {                                                // dodaj ako fali 2
        prvi[k] = pomocni[j];
        j++; k++;
    }
    delete[] pomocni; pomocni = nullptr;                              // obrisi pomocni
}
template <typename Tip>
void merge1(Tip* niz, int l, int u) {                                 // l pocetak niza, u kraj finalnog
    if (u > l) {
        int p = int(std::trunc((l+u-1)/2)), q = p+1;
        merge1(niz, l, p);                                            // prvi niz djelimo sve dok ne dobijemo 1
        merge1(niz, q, u);                                            // isto i vazi i za drugu polovinu
        merge2(niz, l, p, q, u);                                      // spajamo
    }
    else return;
}
template <typename Tip>
void merge_sort(Tip* niz, int vel) {
    merge1(niz, 0, vel-1);
}

// quick sort
template <typename Tip>
int partManijak(Tip *niz, int prvi, int zadnji) {
    Tip pivot(niz[prvi]);
    int p(prvi+1);
    while (p <= zadnji && niz[p] < pivot) p++;

    for (int i=p+1; i <= zadnji; i++) {
        if (niz[i] < pivot) {
            auto temp(niz[i]);
            niz[i] = niz[p];
            niz[p] = temp;
            p++;
        }
    }
    auto temp(niz[prvi]);
    niz[prvi] = niz[p-1];
    niz[p-1] = temp;
    return p-1;
}

template <typename Tip>
void kvikSort(Tip *niz, int p, int z) {
    if(p < z) {
        int j = partManijak(niz, p, z);
        kvikSort(niz, p, j-1);
        kvikSort(niz, j+1, z);
    }
}
template <typename Tip>
void quick_sort(Tip *niz, int vel) {
    kvikSort(niz, 0, vel-1);
}

void ucitaj(const std::string &filename, int* &niz, int &vel) {
    std::ifstream izlaz(filename);
    if(!izlaz) {
        std::cout << "Hej tugo mojaaaaa..";
        return;
    }
    int broj, i=0;
    vel=0;
    while(izlaz >> broj) vel++;

    izlaz.close();
    izlaz.open(filename);
    niz = new int[vel];
    while(izlaz >> broj && i < vel) { niz[i]=broj; i++; }
}

void generisi(const std::string &filename, int vel) {                   // funkcija za generisanje niza sa proizvoljnom velicinom
    std::ofstream ulaz;
    ulaz.open(filename);
    for(int i=0; i < vel; i++) {
        int rng = std::rand() % 1000;
        ulaz << rng << " ";
    }
    ulaz.close();
}


void funkcija(){

    std::srand(std::time(NULL));                     // uvijek rng da bude
    std::string nazivDatoteke;
    std::string izlaznaDatoteka;
    std::cout<<"Unesite naziv datoteke: ";
    std::cin >> nazivDatoteke;
    std::cout<<"Unesite naziv upisne datoteke: ";
    std::cin >> izlaznaDatoteka;

    int *niz = nullptr;
    int vel;
    generisi(nazivDatoteke, std::rand() % 15); // max 15 brojeva
    ucitaj(nazivDatoteke, niz, vel);
    int izbor;
    std::cout << "Izaberite algoritam sortiranja: \n1. Bubble sort\n2. Selection sort\n3. Quick sort\n4. Merge sort : " << std::endl;
    std::cin >> izbor;

    clock_t vrijeme1 = clock();
    switch(izbor) {
        case 1 : bubble_sort(niz, vel);
            break;
        case 2 : selection_sort(niz, vel);
            break;
        case 3 : quick_sort(niz, vel);
            break;
        case 4 : merge_sort(niz, vel);
            break;
        default:
            break;
    }
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja odabranog algoritma sortiranja: " << ukvrijeme << " ms." << std::endl;


    for(int i=0; i < vel; ++i) std::cout << niz[i] << " ";
    // upis u izlaznu datoteku
    std::ofstream ulaz;
    ulaz.open(izlaznaDatoteka);
    for(int i=0; i < vel; i++) {
        ulaz << niz[i] << " ";
    }
    ulaz.close();

    for (int i=1; i<vel; i++) {
        if (niz[i-1] > niz[i]) {
            std::cout << std::endl << "Niz nije dobro sortiran!";
            delete[] niz;
            return;
        }
    }
    std::cout << std::endl << "Niz je dobro sortiran!";
    delete[] niz;
}


int main() {
    funkcija();
    return 0;
}