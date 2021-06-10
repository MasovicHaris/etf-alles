//TP 2016/2017: Tutorijal 1, Zadatak 2
#include <iostream>
#include <cmath>
int main ()
{
    const double PI(4 * atan(1));
    double a,b,c;
    double alfa, beta, gama;
    std::cout << "Unesite tri broja: ";
    std::cin >> a >> b >> c;

    if(a>0 && b>0 && c>0 && ((a+b)>c && (a+c)>b && (c+b)>a)) {

        alfa = acos((a*a + b*b - c*c) / (2*a*b));
        beta = acos((a*a + c*c - b*b) / (2*a*c));
        gama = acos((c*c + b*b - a*a) / (2*c*b));

        double minugao;
        minugao=alfa;
        if(beta < minugao) minugao=beta;
        if(gama < minugao) minugao=gama;

        double s, Povrsina, obim;
        s = (a+b+c) / 2;
        Povrsina = std::sqrt(s * (s-a) * (s-b) * (s-c));
        obim = s*2;

        double stepen1;
        stepen1 = minugao * 180./PI;
        int stepen;
        stepen = (int)stepen1;

        double ostatak;
        ostatak = stepen1 - stepen;

        double minutes1;
        minutes1 = ostatak * 60;
        int minutes;
        minutes = (int)minutes1;

        double ostatak1;
        ostatak1 = minutes1 - minutes; 

        double seconds;
        seconds = ostatak1*60;
        int sec = (int)seconds;

        std::cout << "Obim trougla sa duzinama stranica "<< a << ", " << b << " i " << c << " iznosi " << obim << "." << std::endl;
        std::cout << "Njegova povrsina iznosi " << Povrsina << "." << std::endl;
        std::cout << "Njegov najmanji ugao ima "<< stepen << " stepeni, " << minutes << " minuta i " <<sec << " sekundi.";
    } else {
        std::cout<< "Ne postoji trougao cije su duzine stranica " << a <<", " << b << " i " << c <<"!";
    }
    return 0;
}