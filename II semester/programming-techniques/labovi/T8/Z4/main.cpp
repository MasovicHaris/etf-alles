//TP 2016/2017: Tutorijal 8, Zadatak 4
#include <iostream>
#include <map>

typedef std::map<std::string, std::string> Mapa;

std::string ZamijeniPremaRjecniku(const std::string &s, const Mapa &mapa)
{

    std::string novi;
    for(int i=0; i < s.length(); i++) {
        while(s[i]==' ' && i < s.length()) {
            novi.push_back(s[i]);
            i++;
        }
        if(s[i]!=' ' && i < s.length()) {
            int k=0;
            int j=i;
            while(s[j]!=' ' && j < s.length()) {
                j++;
                k++;
            }
            auto it(mapa.find(s.substr(i,k)));
            if(it != mapa.end()) {
                novi += mapa.find(s.substr(i, k))->second;
            }
            else {
                novi +=s.substr(i,k);
            }
            j--;
            i=j;
        }
        if(i == s.length()) --i;
    }
    return novi;
}

int main ()
{
    Mapa mapone {{"jabuka", "apple"}, {"da", "yes"}, {"kako", "how"}, {"ne", "no"}, {"majmun", "monkey"}};
    std::cout << ZamijeniPremaRjecniku("  kako   da ne majmun", mapone);
    return 0;
}