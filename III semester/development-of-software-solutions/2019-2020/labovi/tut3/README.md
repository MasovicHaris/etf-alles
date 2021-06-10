Univerzitet u Sarajevu\
Elektrotehnički fakultet Sarajevo\
Predmet: Razvoj programskih rješenja 2019/2020

# Tutorijal 3 
### Priprema za tutorijal
>Kreirajte GitHub repozitorij koristeći pozivnicu koju ste dobili.
Pokušajte kod kuće uraditi jedan dio koda kako biste na samom tutorijalu 
imali dovoljno vremena da dovršite zadatak i prodiskutujete eventualne nedoumice s tutorom. 
Potrebno je minimalno implementirati jednu klasu.
>
Zadatak 1
----------------------
Cilj vježbe je napraviti aplikaciju <b>"ETF Telefonski imenik"</b>. 
Aplikacija se treba sastojati od sljedećih klasa:
- Apstraktna klasa <b>TelefonskiBroj</b> sadrži <i>javnu apstraktnu</i> metodu <b>String ispisi()</b> 
koja vraća broj u tekstualnoj formi pogodnoj za ispis, 
te <i>apstraktnu metodu</i> <b>int hashCode()</b> objašnjenu na predavanjima. 
Iz ove klase izvedene su sljedeće klase:
  - <b>FiksniBroj</b> sadrži <i>konstruktor</i> <b>FiksniBroj(Grad grad, String broj)</b>. 
  Parametar broj je dio telefonskog broja bez pozivnog broja npr. "123-456", a grad je promjenljiva pobrojanog tipa koji označava pozivni broj koji treba koristiti npr.:
	<b>enum Grad { SARAJEVO, TUZLA, ZENICA…}</b>
Spisak pozivnih brojeva se može naći [ovdje](https://bs.wikipedia.org/w/index.php?title=Spisak_pozivnih_brojeva_u_Bosni_i_Hercegovini&oldid=2947297). 
Umjesto imena kantona koristite ime glavnog grada kantona (kao u primjeru iznad), 
a umjesto Brčko distrikta stavite BRCKO. Metoda ispisi() treba vratiti broj oblika "033/123-456".
  - <b>MobilniBroj</b> ima <i>konstruktor</i> <b>MobilniBroj(int mobilnaMreza, String broj)</b> pri čemu oznaka mobilne mreže predstavlja drugu i treću cifru pozivnog broja tj. 60-67 (detaljnije informacije možete naći na [istoj stranici](https://bs.wikipedia.org/w/index.php?title=Spisak_pozivnih_brojeva_u_Bosni_i_Hercegovini&oldid=2947297)). 
  Metoda ispisi vraća broj istog oblika "061/987-654".
  - <b>MedunarodniBroj</b> ima <i>konstruktor</i> <b>MedunarodniBroj(String drzava, String broj)</b> pri čemu string drzava sadrži kompletan pozivni broj za državu npr. "+387".


- Klasa <b>Imenik</b> omogućuje da se pretražuju brojevi koristeći klasu <b>HashMap</b>. 
Ova klasa treba sadržavati sljedeće javne metode:
  - <b>void dodaj(String ime, TelefonskiBroj broj)</b>
  - <b>String dajBroj(String ime)</b> - vraća telefonski broj osobe pod imenom ime u formi stringa pozivajući metodu <b>ispisi()</b> klase <b>TelefonskiBroj</b>,
  - <b>String dajIme(TelefonskiBroj broj)</b> - vraća ime osobe čiji telefonski broj je broj - i ova operacija treba koristiti <b>HashMapu</b>,
  - <b>String naSlovo(char s)</b> - vraća sve brojeve u telefonskom imeniku za osobe čije ime počinje na slovo s u formatu:
    <div>
    1. Ime Prezime - broj<br>
    2. Ime Prezime - broj<br>
    ...
    </div>
  
  - <b>Set\<String> izGrada(Grad g)</b> - vraća skup Stringova koji sadrži imena i prezimena svih osoba koje žive u gradu g (istog pobrojanog tipa koji je dat u klasi FiksniBroj), što se može saznati ako osoba ima fiksni broj telefona u tom gradu. Pri tome skup treba biti sortiran abecedno.
  - <b>Set\<TelefonskiBroj> izGradaBrojevi(Grad g)</b> - vraća brojeve za osobe iz grada g. Ovaj skup treba biti sortiran po stringu koji se dobije metodom ispisi().

- Klasa <b>Program</b> treba sadržavati main metodu koja korisniku omogućuje da unosom naredbi pomoću tastature pozove sve metode klasa navedenih iznad.

Dodajte nedostajuće testove po potrebi. Prilikom rješavanja zadatka obavezno se pridržavati pravila rada koja su navedena na predavanjima, između ostalog:
- <b>ispravno imenovanje paketa klasa, metoda i promjenljivih
- primjenu komentara
- atomic commits.</b>

