#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 1 zadatak
void BrojiSabaneTrebatCeTi(vector<int> &a, int broj){
    vector<int> pomocni(a.size());                                                           // pomocni
    int count[10] = {0};                                                                     // imamo 10 cifara
    for (int i = 0; i < a.size(); i++) count[(a[i]/ broj)%10]++;                             // brojanje i-te decimale
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];                                   // dalje je counting sort
    for (int i = a.size() - 1; i >= 0; i--) {
        count[(a[i]/ broj )%10]--;
        pomocni[count[(a[i]/ broj )%10]] = a[i];
    }
    a = pomocni;
}


void radixSort(vector<int> &a) {                                                             // sortiramo po svakoj cifri pomocu counting sort-a
    if(a.empty()) return;
    int max=a[0];
    for (int i=0; i<a.size(); i++) if(a[i]>max) max=a[i];
    for (int broj = 1; max/broj > 0; broj *= 10) BrojiSabaneTrebatCeTi(a, broj);
}



// 2 zadatak
void popraviDolje(vector<int> &a, int i) {
    while (i < a.size()/2) {                                                    // ako nije list
        int pomoc1 = 2*i+1, pomoc2 =2*i+2;
        if (pomoc2 < a.size() && a[pomoc2] > a[pomoc1]) pomoc1 = pomoc2;
        if (a[i] > a[pomoc1]) return;
        std::swap(a[i], a[pomoc1]);
        i = pomoc1;
    }
}

void popraviGore(vector<int> &a, int i) {                                       // popravljamo vrijednost u nizu ka vrhu
    while (i!=0 && a[i] > a[(i-1)/2]) {                                         // tj. guramo element ka vrhu dokle moze
        std::swap(a[i], a[(i-1)/2]);
        i=(i-1)/2;
    }
}

void stvoriGomilu(vector<int> &a) {                                             // stvaranje gomile od kraja
    int velicina = a.size();
    for (int i=velicina/2; i>=0; i--) popraviDolje(a, i);
}

void gomilaSort(vector<int> &a) {
    stvoriGomilu(a);
    vector<int> pomocni(a.size());
    int vel(a.size());
    for (int i=0; i<vel; i++) {                                                 // imamo obrnut poredak
        pomocni[i] = a[0];
        a.erase(a.begin());
        stvoriGomilu(a);
    }
    for (int i=0; i<vel; i++) a.push_back(pomocni[vel-i-1]);                    // samo obrnemo, kad vracamo
}


void umetniUGomilu(vector<int> &a, int umetnuti, int &velicina) {               // umecemo na kraj vektora nas element
    a.push_back(umetnuti);                                                      // i pomocu popraviGore stimamo ga ka vrhu
    velicina++;
    popraviGore(a, a.size()-1);
}

int izbaciPrvi(vector<int> &a, int &velicina) {                                 // vraca izbaceni
    if (a.empty()) return -1;                                                   // ukoliko je gomila prazna, vraca -1 kao gresku
    velicina--;
    int temp(a[0]);
    std::swap(a[0], a[velicina]);
    vector<int> v(velicina);
    for (int i=0; i<v.size(); i++) v[i]=a[i];                                   //  brisemo zadnji element
    stvoriGomilu(v);                                                            // 'sortirati' po gomili
    for (int i=0; i<v.size(); i++) a[i]=v[i];                                   //  vracamo tu gomilu
    return temp;
}



int main() {
    std::cout << "Zadaća 3, Zadatak 1";
    return 0;
}
