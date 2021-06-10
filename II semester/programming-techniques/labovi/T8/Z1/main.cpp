//TP 2016/2017: Tutorijal 8, Zadatak 1
#include <iostream>
#include <iomanip>
#include <stdexcept>

struct Vrijeme {
    int sati, minute, sekunde;
};

void TestirajVrijeme(const Vrijeme &v1)
{
    if(v1.sati <0 || v1.sati > 23 || v1.minute < 0 || v1.minute > 59 || v1.sekunde < 0 || v1.sekunde > 59) throw std::domain_error("Neispravno vrijeme");
}

void IspisiVrijeme(const Vrijeme &v)
{
    try {
        TestirajVrijeme(v);
    } catch(std::domain_error exec) {
        throw std::domain_error("Neispravno vrijeme");
    }
    std::cout << std::setfill('0') << std::setw(2) << v.sati << ":" << std::setfill('0') << std::setw(2) << v.minute << ":" << std::setfill('0') << std::setw(2) << v.sekunde << std::endl;
}

Vrijeme SaberiVrijeme(const Vrijeme &v1, const Vrijeme &v2)
{
    try {
        TestirajVrijeme(v1);
        TestirajVrijeme(v2);
    } catch(std::domain_error exec) {
        throw std::domain_error("Neispravno vrijeme");
    }
    int sekunde = (v1.sati + v2.sati) * 3600 + (v1.minute + v2.minute) * 60 + (v1.sekunde + v2.sekunde);
    sekunde %= 86400; // ostatak od dana
    int sati = sekunde / 3600;
    sekunde %= 3600;
    int minute = sekunde / 60;
    sekunde %= 60;
    return {sati, minute, sekunde}; // struct
}

int main ()
{
    Vrijeme v1, v2;
    std::cout << "Unesite prvo vrijeme (h m s): ";
    std::cin >> v1.sati >> v1.minute >> v1.sekunde;
    try {
        TestirajVrijeme(v1);
    } catch(std::domain_error exec) {
        std::cout << exec.what();
        return 0;
    }

    std::cout << "Unesite drugo vrijeme (h m s): ";
    std::cin >> v2.sati >> v2.minute >> v2.sekunde;
    try {
        TestirajVrijeme(v2);
    } catch(std::domain_error exec) {
        std::cout << exec.what();
        return 0;
    }
    std::cout << "Prvo vrijeme: ";
    IspisiVrijeme(v1);
    std::cout << "Drugo vrijeme: ";
    IspisiVrijeme(v2);
    std::cout << "Zbir vremena: ";
    IspisiVrijeme(SaberiVrijeme(v1, v2));
    return 0;
}