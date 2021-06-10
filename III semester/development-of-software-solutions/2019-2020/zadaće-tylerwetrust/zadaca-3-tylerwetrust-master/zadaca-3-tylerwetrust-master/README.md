# zadaca-3-tylerwetrust
zadaca-3-tylerwetrust created by GitHub Classroom

Napomena za tutora koji bude pregledao:
U testnim klasama KorisnikController i Zadatak2 na kraju svake metode je dodan poziv regenerisi() iz razloga što na Windows OS-ovima
@Start iz nekih meni nepoznatih razloga se ne poziva fino, te baza se ne regeneriše, dok na OS-ovima puput Linuxa slobodno možete izbrisati
te dodatne pozive i svi autotestovi bi trebali proći.
Takeđer, kako sam pri izradi Zadataka 7 importovao custom library: https://github.com/keshrath/Giphy4J?fbclid=IwAR0Nexw7gqWDxiT56Vq2PNCj_tICk4otXJmMMYXshv-sUBhQT55m3DRS14c
(jer nije rečeno da to ne smijemo raditi) struktura projekta se promijenila i došlo je do nekih konflikata sa JUnitom, što je prouzrokovalo
da određeni testovi fail-aju ukoliko se autotestovi pokreni svi od jednom.
Međutim ukoliko se autotetovi pokretaju pojedinačno SVI ĆE PROĆI. Naravno u ispravnost aplikacije se možete uvjeriti ukoliko je ručno testirate.

NAPOMENA:
Ukoliko vam ne prepoznaje klasu Giphy potrebno je u Maven ubaciti odgovarajući dependecies:
https://pastebin.com/U5WrkjdY

Zamilio bih da se prilikom ocjenjivanja zadaće u obzir uzmu pomenute činjenice, jer stvarno nisam imao vremena da istražim šta je to
uzrok padova određenih testova ukoliko se izvršavaju automatski.

Unaprijed zahvalan, Mirza.
