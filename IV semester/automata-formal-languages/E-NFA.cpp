#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <stack>
#include <queue>

class EpsilonNka {
    // definisanje po postavci zadatka
    std::vector<std::list<std::pair<int, char>>*> delta;
    std::set<char> alfabet;
    int pocetnoStanje, finalnoStanje;


    // definisanje steka za citanje regexa
    std::stack<std::pair<char, std::pair<int, int>>> stekProtoka;

    bool isMaloSlovo(char a){
        // sva slova osim malog e su alfabet, e je rezervisano za epsilon prelaz
        return (a >= 'a' && a <= 'z' && a != 'e');
    }

    void ispisPokazivacaListe(){
        // privatna funkcija za ispis na ekranu
        // koristena stranica -> http://ivanzuzak.info/noam/webapps/fsm_simulator/
        // za prikaz automata

        std::cout << "#states" << std::endl;
        for (int j = 0; j < delta.size(); ++j) {
            std::cout << j << std::endl;
        }
        std::cout << "#initial" << std::endl;
        std::cout << 0 << std::endl;
        std::cout << "#accepting" << std::endl;
        std::cout << 1 << std::endl;
        std::cout << "#alphabet" << std::endl;
        std::cout << "e" << std::endl;
        for (auto const& val : alfabet)
        {
            std::cout << val << std::endl;
        }
        std::cout << "#transitions" << std::endl;
        for (int i = 0; i < delta.size(); ++i) {
            for(auto it = delta[i]->begin(); it != delta[i]->end(); it++)
            {
                std::cout << i << ":" << it->second << ">" << it->first << std::endl;
            }
        }

        std::cout << std::endl;
    }

    void dfs(int brojac, const std::string &rijec, std::vector<int> &dfs_obilazak, int cvor, int ukupniBrojac) {

        if(cvor == 1 && brojac != rijec.length()) return;

        if(ukupniBrojac > 10 + rijec.size() * rijec.size()) return;

        dfs_obilazak.push_back(cvor);

        for(auto j = delta[cvor]->begin(); j != delta[cvor]->end(); j++) {
            if ( (j->second == rijec[brojac])) {
                dfs(brojac+1, rijec, dfs_obilazak, j->first,ukupniBrojac+1);
            }
            else if( (j->second == 'e')){
                dfs(brojac, rijec, dfs_obilazak, j->first, ukupniBrojac+1);
            }
            if(dfs_obilazak.size() > 1 && dfs_obilazak[dfs_obilazak.size()-1] == 1) return;
        }
    }

public:
    EpsilonNka(const std::string &regex){

        // kreiranje pocetnog i finalnog stanja

        std::list<std::pair<int, char>>* pokPocetni = nullptr;
        std::list<std::pair<int, char>>* pokFinalni = nullptr;

        pokPocetni = new std::list<std::pair<int, char>>();
        pokFinalni = new std::list<std::pair<int, char>>();

        delta.push_back(pokPocetni);
        delta.push_back(pokFinalni);

        pocetnoStanje = 0;
        finalnoStanje = 1;

        // dobavljanje alfabeta tj. kupimo sve karaktere iz regexa

        auto i = regex.length();
        for(i = 0; i < regex.length(); ++i){
            if(isMaloSlovo(regex[i])) alfabet.insert(regex[i]);
        }

        // imamo definisano pocetno, finalno stanje, imamo definisan alfabet
        // odavde na osnovu regexa kreiramo sve čvorove i prelaze

        for(i = 0; i < regex.length(); ++i){

            if(isMaloSlovo(regex[i])){

                int pamti1 =0, pamti2 = 0;
                if(stekProtoka.empty()) {
                    int redniBrojStanja1, redniBrojStanja2;
                    std::list<std::pair<int, char>> *pomocni1 = nullptr;
                    pomocni1 = new std::list<std::pair<int, char>>();

                    std::list<std::pair<int, char>> *pomocni2 = nullptr;
                    pomocni2 = new std::list<std::pair<int, char>>();
                    delta.push_back(pomocni1);
                    redniBrojStanja1 = delta.size() - 1;
                    delta.push_back(pomocni2);
                    redniBrojStanja2 = delta.size() - 1;

                    std::list<std::pair<int, char>> *pok = delta[0];
                    auto par = std::make_pair(redniBrojStanja1, 'e');
                    pok->push_back(par);

                    std::list<std::pair<int, char>> *pok2 = delta[redniBrojStanja1];
                    auto par2 = std::make_pair(redniBrojStanja2, regex[i]);
                    pok2->push_back(par2);

                    pamti2 = redniBrojStanja2;
                    pamti1 = redniBrojStanja1;
                }
                else {
                    int redniBrojStanja1, redniBrojStanja2;
                    std::list<std::pair<int, char>> *pomocni1 = nullptr;
                    pomocni1 = new std::list<std::pair<int, char>>();

                    std::list<std::pair<int, char>> *pomocni2 = nullptr;
                    pomocni2 = new std::list<std::pair<int, char>>();
                    delta.push_back(pomocni1);
                    redniBrojStanja1 = delta.size() - 1;
                    delta.push_back(pomocni2);
                    redniBrojStanja2 = delta.size() - 1;

                    std::list<std::pair<int, char>> *pok = delta[redniBrojStanja1];
                    auto par = std::make_pair(redniBrojStanja2, regex[i]);
                    pok->push_back(par);

                    pamti2  = redniBrojStanja2;
                    pamti1  = redniBrojStanja1;
                }
                auto par = std::make_pair(pamti1, pamti2);
                auto par2 = std::make_pair(regex[i], par);
                stekProtoka.push(par2);

            }
            else if(regex[i] == '+'){               // 2 operanda
                auto elementBezGlave = stekProtoka.top(); stekProtoka.pop();
                auto elementSaGlavom = stekProtoka.top(); stekProtoka.pop();

                int redniBrojStanja1, redniBrojStanja2;

                std::list<std::pair<int, char>> *pomocni1 = nullptr;
                pomocni1 = new std::list<std::pair<int, char>>();

                std::list<std::pair<int, char>> *pomocni2 = nullptr;
                pomocni2 = new std::list<std::pair<int, char>>();
                delta.push_back(pomocni1);
                redniBrojStanja1 = delta.size() - 1;
                delta.push_back(pomocni2);
                redniBrojStanja2 = delta.size() - 1;

                pomocni1->push_back(std::make_pair(elementBezGlave.second.first, 'e'));
                pomocni1->push_back(std::make_pair(elementSaGlavom.second.first, 'e'));


                for(auto it = pokPocetni->begin(); it != pokPocetni->end(); ++it){
                    if(it->first == elementSaGlavom.second.first) {
                        // prebacivanje pokazivaca
                        it->first = redniBrojStanja1;
                        break;
                    }
                }

                delta[elementBezGlave.second.second]->push_back(std::make_pair(redniBrojStanja2, 'e'));
                delta[elementSaGlavom.second.second]->push_back(std::make_pair(redniBrojStanja2, 'e'));

                auto parx = std::make_pair(redniBrojStanja1, redniBrojStanja2);
                auto pary = std::make_pair('e', parx);
                stekProtoka.push(pary);

            }
            else if(regex[i] == '*'){               // 1 operand
                auto zadnjiElementStacka = stekProtoka.top();
                stekProtoka.pop();

                std::list<std::pair<int, char>> * pokazivacNaDrugi = delta[zadnjiElementStacka.second.second];

                int inet = zadnjiElementStacka.second.first;
                auto par = std::make_pair(inet, 'e');
                pokazivacNaDrugi->push_back(par);
                int redniBrojStanja1, redniBrojStanja2;

                if(i+1 < regex.size()) {
                    std::list<std::pair<int, char>> *pomocni1 = nullptr;
                    pomocni1 = new std::list<std::pair<int, char>>();

                    std::list<std::pair<int, char>> *pomocni2 = nullptr;
                    pomocni2 = new std::list<std::pair<int, char>>();
                    delta.push_back(pomocni1);
                    redniBrojStanja1 = delta.size() - 1;
                    delta.push_back(pomocni2);
                    redniBrojStanja2 = delta.size() - 1;

                    std::list<std::pair<int, char>> *pok = delta[redniBrojStanja1];
                    auto par2 = std::make_pair(redniBrojStanja2, 'e');
                    auto par3 = std::make_pair(zadnjiElementStacka.second.first, 'e');
                    pok->push_back(par2);
                    pok->push_back(par3);

                    auto par4 = std::make_pair(redniBrojStanja2, 'e');
                    pokazivacNaDrugi->push_back(par4);

                    for(auto it = pokPocetni->begin(); it != pokPocetni->end(); ++it){
                        if(it->first == zadnjiElementStacka.second.first) {
                            // prebacivanje pokazivaca
                            it->first = redniBrojStanja1;
                            break;
                        }
                    }
                }
                else {                                                                      // ako je * nad svim
                    std::list<std::pair<int, char>> *pomocni1 = nullptr;
                    pomocni1 = new std::list<std::pair<int, char>>();

                    std::list<std::pair<int, char>> *pomocni2 = nullptr;
                    pomocni2 = new std::list<std::pair<int, char>>();
                    delta.push_back(pomocni1);
                    redniBrojStanja1 = delta.size() - 1;
                    delta.push_back(pomocni2);
                    redniBrojStanja2 = delta.size() - 1;

                    pokPocetni->clear();
                    auto pair = std::make_pair(redniBrojStanja1, 'e');
                    pokPocetni->push_back(pair);

                    auto  pokc = delta[redniBrojStanja1];
                    pokc->push_back(std::make_pair(inet, 'e'));
                    pokc->push_back(std::make_pair(redniBrojStanja2, 'e'));

                    pokazivacNaDrugi->push_back(std::make_pair(redniBrojStanja2, 'e'));
                }
                auto parx = std::make_pair(redniBrojStanja1, redniBrojStanja2);
                auto pary = std::make_pair('e', parx);
                stekProtoka.push(pary);

            }
            else if(regex[i] == '.'){               // 2 operanda
                auto element2 = stekProtoka.top(); stekProtoka.pop();
                auto element1 = stekProtoka.top(); stekProtoka.pop();

                std::list<std::pair<int, char>> * pokazivacNaPrvi = delta[element1.second.second];

                // std::list<std::pair<int, char>> * pokazivacNaDrugi = delta[element2.second.first];

                auto par = std::make_pair(element2.second.first, 'e');
                pokazivacNaPrvi->push_back(par);

                auto parx = std::make_pair(element1.second.first, element2.second.second);
                auto pary = std::make_pair('e', parx);
                stekProtoka.push(pary);

            }
        }

        // stavljanje eps prelaza za finalnom stanju pri cemu znamo
        // da stanje ako nije redni broj 1 i ako nema prelaza to je kandidat za finalno
        for(int i = 0; i < delta.size(); ++i){
            if(delta[i]->empty() && i != 1){

                auto par = std::make_pair(1, 'e');
                delta[i]->push_back(par);
            }
        }
    }

    ~EpsilonNka(){
        auto i = delta.size();
        for(i = 0; i < delta.size(); ++i){
            if(delta[i] == nullptr) continue;
            else {
                delete delta[i];
                delta[i] = nullptr;
            }
        }
    }

    bool  prihvataRijec(const std::string &rijec){
        std::vector<int> dfs_obilazak;
        dfs(0, rijec, dfs_obilazak, 0, 0);
        bool trenutak = false;
        for(int i=0; i < dfs_obilazak.size(); ++i){
            if(dfs_obilazak[i] == 1){ trenutak = true; }
            // std::cout << dfs_obilazak[i] << " ";
        }

        return trenutak;
    }


};

int main() {

    std::string regular_1 = "aa*.ba.b.+b.";
    auto epsNka = new EpsilonNka(regular_1);
    std::string rijec_1_1 = "babb";
    std::string rijec_1_2 = "aaaab";
    std::string rijec_1_3 = "aaaabb";

    std::cout << "Za regularni izraz: " << regular_1 << " imamo: " << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_1_1 << " ocekivano: 1 " << "dobijeno: " << epsNka->prihvataRijec(rijec_1_1) << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_1_2 << " ocekivano: 1 " << "dobijeno: " << epsNka->prihvataRijec(rijec_1_2) << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_1_3 << " ocekivano: 0 " << "dobijeno: " << epsNka->prihvataRijec(rijec_1_3) << std::endl;
    delete epsNka;
    epsNka = nullptr;
    std::cout << std::endl;

    std::string regular_2 = "a*b*.ab+*.";
    std::string rijec_2_1 = "";
    std::string rijec_2_2 = "aaaab";
    std::string rijec_2_3 = "aaaabb";
    epsNka = new EpsilonNka(regular_2);
    std::cout << "Za regularni izraz: " << regular_2 << " imamo: " << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_2_1 << " ocekivano: 1 " << "dobijeno: " << epsNka->prihvataRijec(rijec_2_1) << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_2_2 << " ocekivano: 1 " << "dobijeno: " << epsNka->prihvataRijec(rijec_2_2) << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_2_3 << " ocekivano: 1 " << "dobijeno: " << epsNka->prihvataRijec(rijec_2_3) << std::endl;
    delete epsNka;
    epsNka = nullptr;
    std::cout << std::endl;

    std::string regular_3 = "a*ab+.b*.";
    std::string rijec_3_1 = "";
    std::string rijec_3_2 = "aaaab";
    std::string rijec_3_3 = "aaaabb";
    epsNka = new EpsilonNka(regular_3);
    std::cout << "Za regularni izraz: " << regular_3 << " imamo: " << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_3_1 << " ocekivano: 0 " << "dobijeno: " << epsNka->prihvataRijec(rijec_3_1) << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_3_2 << " ocekivano: 1 " << "dobijeno: " << epsNka->prihvataRijec(rijec_3_2) << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_3_3 << " ocekivano: 1 " << "dobijeno: " << epsNka->prihvataRijec(rijec_3_3) << std::endl;
    delete epsNka;
    epsNka = nullptr;
    std::cout << std::endl;

    std::string regular_4 = "a*ba.+";
    std::string rijec_4_1 = "";
    std::string rijec_4_2 = "aaaab";
    std::string rijec_4_3 = "aaaabb";
    epsNka = new EpsilonNka(regular_4);
    std::cout << "Za regularni izraz: " << regular_4 << " imamo: " << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_4_1 << " ocekivano: 1 " << "dobijeno: " << epsNka->prihvataRijec(rijec_4_1) << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_4_2 << " ocekivano: 0 " << "dobijeno: " << epsNka->prihvataRijec(rijec_4_2) << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_4_3 << " ocekivano: 0 " << "dobijeno: " << epsNka->prihvataRijec(rijec_4_3) << std::endl;
    delete epsNka;
    epsNka = nullptr;
    std::cout << std::endl;

    std::string regular_5 = "a*b*.ab+*.*";
    epsNka = new EpsilonNka(regular_5);
    std::string rijec_5_1 = "babb";
    std::string rijec_5_2 = "";
    std::string rijec_5_3 = "bbbbbbb";

    std::cout << "Za regularni izraz: " << regular_5 << " imamo: " << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_5_1 << " ocekivano: 1 " << "dobijeno: " << epsNka->prihvataRijec(rijec_5_1) << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_5_2 << " ocekivano: 1 " << "dobijeno: " << epsNka->prihvataRijec(rijec_5_2) << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_5_3 << " ocekivano: 1 " << "dobijeno: " << epsNka->prihvataRijec(rijec_5_3) << std::endl;
    delete epsNka;
    epsNka = nullptr;
    std::cout << std::endl;

    std::string regular_6 = "a*b+b*a+.";
    epsNka = new EpsilonNka(regular_6);
    std::string rijec_6_1 = "babb";
    std::string rijec_6_2 = "";
    std::string rijec_6_3 = "bbbbbbb";

    std::cout << "Za regularni izraz: " << regular_6 << " imamo: " << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_6_1 << " ocekivano: 0 " << "dobijeno: " << epsNka->prihvataRijec(rijec_6_1) << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_6_2 << " ocekivano: 1 " << "dobijeno: " << epsNka->prihvataRijec(rijec_6_2) << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_6_3 << " ocekivano: 1 " << "dobijeno: " << epsNka->prihvataRijec(rijec_6_3) << std::endl;
    delete epsNka;
    epsNka = nullptr;
    std::cout << std::endl;

    std::string regular_7 = "a*ab++";
    epsNka = new EpsilonNka(regular_7);
    std::string rijec_7_1 = "b";
    std::string rijec_7_2 = "";
    std::string rijec_7_3 = "bbbbbbb";

    std::cout << "Za regularni izraz: " << regular_7 << " imamo: " << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_7_1 << " ocekivano: 1 " << "dobijeno: " << epsNka->prihvataRijec(rijec_7_1) << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_7_2 << " ocekivano: 1 " << "dobijeno: " << epsNka->prihvataRijec(rijec_7_2) << std::endl;
    std::cout << "Prihvatanje rijeci " << rijec_7_3 << " ocekivano: 0 " << "dobijeno: " << epsNka->prihvataRijec(rijec_7_3) << std::endl;
    delete epsNka;
    epsNka = nullptr;
    std::cout << std::endl;

    return 0;
}

