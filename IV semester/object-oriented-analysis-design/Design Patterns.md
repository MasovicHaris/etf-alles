### Tema: Vicinor - Design Patterns
\
![vicinor-logo](https://user-images.githubusercontent.com/37186899/37522627-c259062e-2924-11e8-9f06-1c6eb6394c94.png)

## 1. Iterator - Pattern ponašanja

- Q: Kada koristimo? 

A: Ovaj pattern se koristi kada je potrebno imati uniforan način pristupa bilo kojoj kolekciji. Ako recimo želimo iz nekog razloga da primimo ArrayList, Array i HashMapu, možemo iskoristiti iterator interface pomoću kojeg ćemo najbolje omogućiti uniforan pristup, skratiti kod, napraviti bolji polimorfizam.

- Q: Kako koristimo?

A: Potrebno je napraviti interface Iterator (ne mora nužno taj naziv) i naslijediti sve naše klase iz tog interface-a, na kraju taj interface ćemo realizirati u nekoj drugoj klasi pomoću koje ćemo realizovati specifične metode tog interface-a. Naravno svaka klasa koja naslijedi Interface metodu će vraćati Interface. (ref. Java pristup)

- Q: Iskorišteno u projektu?

A: Ne.

- Q: Ako nije, gdje bi bilo dobro mjesto za njihovu upotrebu i zašto?

A: Ukoliko imamo rad sa više vrsta kolekcija implementacija ovog paterna je veoma korisna. Pošto u našoj implementaciji imamo samo listu upotreba ovog paterna nije od nekog značaja. Mogao bi se iskoristiti u nekoj posebnoj klasi koja bi imala realizovan Iterator interface i imala npr. metodu koja će raditi nešto sa elementima svih kolekcija..

## 2. Singleton - Kreacijski pattern

- Q: Kada koristimo? 

A: Singleton patern koristimo kada je potrebno imati isključivo jednu instancu neke klase te kada klasa sadrži nešto zajedničko za čitavu aplikaciju/dio aplikacije koji treba iskoristiti.

- Q: Kako koristimo?

A: Realizujemo klasu da ima private statičku instancu te iste klase, da ima prazan konstruktor obični, i metodu getInstance() pri čemu se možemo odlučiti za lazy singleton. Svaka instanca vraća jednu te istu instancu čime je održana validnost. Ukoliko radimo sa threadovima može se koristiti synchronized opcija (ref. Java pristup)

- Q: Iskorišteno u projektu?

A: Ne.

- Q: Ako nije, gdje bi bilo dobro mjesto za njihovu upotrebu i zašto?

A: Ne bi nigdje, jer nemamo takav specifičan tip klase sa kojom čuvamo dosta ključnih podataka vezan za aplikaciju/dio nje.

## 3. Strategy - Pattern ponašanja

- Q: Kada koristimo? 

A: Strategy patern je koristan kada postoje različiti primjenjivi algoritmi (strategije) za neki problem. Ukoliko imamo ograničeno, ali obavezano ponašanje različitih podklasa u hijerarhiji, tada je ovaj patern zgodno iskoristiti.

- Q: Kako koristimo?

A: Prvo napravimo interface pomoću kojeg definišemo neku obaveznu metodu, zatim implementiramo sve klase aka. algoritme pri čemu implementiramo prvokreirani interface. Sada kada imamo već kreiranu hijerahiju klasa, možemo unutar glavne (base) klase realizovati instancu tog interface-a. Može staviti neki defaultni algoritam, a možemo i kasnije dinamički mijenjati. To možemo kroz naslijeđivanje novih klasa iskoristiti pogotovo.

- Q: Iskorišteno u projektu?

A: Ne.

- Q: Ako nije, gdje bi bilo dobro mjesto za njihovu upotrebu i zašto?

A: Prilikom samog prijavljivanja korisnika, znamo sigurno da imamo 3 opcije prilikom registracije koje su: registrovani korisnik, neregistrovani korisnik, guest. Na osnovu datog tipa klase tj. korisnika možemo realizovati 'set-up' nakon registracije, svaki tip korisnika ima drugačiji prikaz, samim tim možemo i drugačije podatke dobiti pomoću api request-a prema našoj bazi. Na osnovu ovoga imamo bolju enkapsulaciju, uz malo polimorfizma. Dodavanje novog tipa user-a pogotovo nije na odmet..

## 4. Prototype - Kreacijski pattern

- Q: Kada koristimo? 

A: Kada je potrebno da kreiramo nove objekte klonirajući jednu od postojećih prototip instanci (postojeći objekat). Ako je trošak kreiranja novog objekta velik i kreiranje objekta je resursno zahtjevno tada se vrši kloniranje već postojećeg objekata. Tj. možemo imati shallow i deep copy (zavisno od naše implementacije).
Prototype pattern je često koristan i prilikom višestrukog korištenja podataka iz baze: Npr.
Potrebno je uraditi analizu prodaje na skupu podataka iz baze. Potrebno je kopirati podatke iz
baze podataka, enkapsulirati ih u objekat i nad njima raditi analizu. Ako je potrebno uraditi i
druge analize nad istim skupom podataka nije dobra ideja ponovo pristupati bazi podataka,
čitati podatke i kreirati objekat za njihovo smještanje. Ako se koristi Prototype pattern tada se
objekat koji se koristi za analizu prodaje klonira i koristi za drugu analizu.

- Q: Kako koristimo?

A: Potrebno je da napravimo interface klasu i nju implementirati na sve tipove prototipa tj. klase koje želimo da imaju mogućnost kopiranja. Također potrebno je implementirati metodu koja vraća tip Interface-a tog istog. Prilikom korištenja metode clone uvijek ćemo pozivati super klasu tj. njenu metodu (Da bi omogućili kloniranje podataka moramo specificirati interface-u da može se klonirati, npr. da extenda klasu Cloneable).

- Q: Iskorišteno u projektu?

A: Ne.

- Q: Ako nije, gdje bi bilo dobro mjesto za njihovu upotrebu i zašto?

A: Ukoliko želimo unutar administracije (in the future) dodati novi tip statistike koji ćemo raditi nad registrovanim korisnicima, možemo baš tu iskoristiti prototype pattern. Prvim api pozivom ka bazi dobijemo sve registrovane korisnike, zatim ih kloniramo za tu neku novu upotrebu.

## 5. Chain of Responsibility - Pattern ponašanja

- Q: Kada koristimo? 

A: Chain of Responsibility pattern se koristi kada imamo ograničen skup algoritama specifičnih za neku namjenu, a pri tom želimo to bez dodatnog pisanja koda tj. promjenom jednog parametra unutar nekog Handlera mi specificiramo koji algoritam će se izvršiti. Odnosno kako tok pretrage izvršavanja ide, traži se responsible klasa koja će uraditi neki algoritam koji smo mi specificirali.

- Q: Kako koristimo?

A: Moramo specicificirati Handler klasu pomoću koje ćemo rasporediti koji će se algoritam izvršavati za određeni izbor, interface 'Chain' koji će imati 2 metode npr. izvrsiAlgoritam() i postaviNaredniChain(). Svaka klasa koja definira neki algoritam mora imati instancu tog interface-a i mora implementirati taj sami interface, na taj način pravimo chain za određeni izbor.  

- Q: Iskorišteno u projektu?

A: Ne.

- Q: Ako nije, gdje bi bilo dobro mjesto za njihovu upotrebu i zašto?

A: Ukoliko želimo unutar administracije izabrati neki tip statistike pri čemu ćemo svaki put koristiti različit algoritam, možemo ovo iskoristiti. Na ovaj način možemo uvijek dodavati nove algoritme, a promjena unutar glavnog poziva algoritma bi bila samo u nazivu algoritma koji mi hoćemo (npr)..

## 6. Adapter pattern - Strukturalni pattern

-Q: Kada koristimo?

A: Pattern možemo koristiti da omogućimo širu upotrebu već postojećih klasa kada nam je potreban drugačiji interfejs već postojeće klase, a ne želimo mijenjati postojeću klasu. Novokreirana adapter klasa služi kao posrednik između  originalne klase i  željenog interfejsa. 

-Q: Kako koristimo?

A: Potrebno je napraviti novi interfejs Itarget (zahtjevani interfejs) kojeg implementira klasa Adapter koja prilagođava stari interfejs. Klasa Adaptee definira već postojeći interfejs kojeg prilagođavamo. U klasi ITarget definišemo metode koje treba izmijeniti. Klasa adapter implementira te metode na odgovarajući način s ciljem da se postigne zahtjevani interfejs.

-Q: Iskorišteno u projektu?

A: Ne

-Q: Ako nije, gdje bi bilo dobro mjesto za njihovu upotrebu i zašto?

A: 	Ovaj pattern bi se mogao iskoristiti kod prikaza statistike. AdminStatistikaViewModel definiše metode koje vraćaju statistiku o korisnicima (procenat registrovanih i neregistrovanih korisnika) u vidu decimalnog broja sa preciznosti od dva decimalna mjesta. Ako bi htjeli promijeniti ispis željenih podataka možemo definisati novi interfejes IadminStatistka sa metodama procenatReg() i procenatNereg() koje ćemo implementirsti u Adapteru na način koji nama odgovara.

## 7. Decorator pattern - Strukturalni pattern

-Q: Kada koristimo?

A: Osnovna namjena Decorator patterna je da omogući dinamičko dodavanje novih elemenata i funkcionalnosti postojećim objektima. 
Decorator pattern se koristi i kada postojeće klase komponenti nisu podesne za podklase, npr. nisu raspoložive ili bi rezultiralo u mnogo podklasa. Objekat pri tome nezna da je urađena dekoracija što je veoma korisno za iskoristljivost i ponovnu upotrebu komponenti softverskog sistema. Može se koristi i za implementaciju različitih kompresija videa, simultano prevođenje, i sl. 

-Q: Kako koristimo?

A: Decorator pattern se ne oslanja na čisto nasljeđivanje prilikom dodavanja novih atributa i ponašanja.
Decorator pattern nasljeđuje originalnu klasu i sadrži instancu originalne klase. Postojeći objekti se ne
mijenjaju već se kreiraju novi. To se postiže sa Decorator klasom koja uključuje dva tipa relacija sa
IComponent interfejsom: Decorator realizira IComponent interfejs (isprekidanim strelicama ili
nasljeđivanjem), Decorator je povezan kompozicijom sa IComponent interfejsom. To znači da
Decorator instancira jedan ili više IComponent objekata i 'decorate' objekte – uključuje nove operacije
i override postojeće.

-Q: Iskorišteno u projektu?

A: Nije.

-Q: Ako nije, gdje bi bilo dobro mjesto za njihovu upotrebu i zašto?

A: Decorator pattern koristimo da pruzimo dodatne funkcionalnost izvedenoj klasi a da se pri tome ne vidi razlika od bazne klase. Mi u nasoj implementaciji imamo Registrovanog i Neregistrovanog korisnika, oba objekta pretrazuju restorane ali samo registrovani korisnik ima dodatnu mogucnost za dodavanje omiljenih restorana.


## 8. Factory Method - Kreacijski pattern

-Q: Kada koristimo?

A: Uloga Factory Method patterna je da omogući kreiranje objekata na način da podklase odluče koju klasu instancirati. Različite podklase mogu na različite načine implementirati interfejs. Factory Method često se primjenjuje jer dopušta projektu da blisko slijedi SOLID principe. Konkretno, principe međusobne segregacije i inverzije ovisnosti.

-Q: Kako koristimo?

A: Factory Method instancira odgovarajuću podklasu(izvedenu klasu) preko posebne metode na osnovu informacije od strane klijenta ili na osnovu tekućeg stanja.

-Q: Iskorišteno u projektu?

A: Ne

-Q: Ako nije, gdje bi bilo dobro mjesto za njihovu upotrebu i zašto?

A: Ne vidimo nigdje efektivan nacin gdje bi se ovaj pattern mogao iskoristiti.

## 9. State pattern - Patterni ponašanja

-Q: Kada koristimo?

A: State pattern je dinamička verzija Strategy patterna gdje objekat mijenja način ponašanja na osnovu trenutnog stanja.

-Q: Kako koristimo?

A: Uvodimo nove klase Context, IState te StateA, StateB itd. Klasa Context održava instancu stanja koja definira tekući kontekst i interfejs koji je od interesa za klijenta, a klasa Client komunicira sa ovom klasom. Interfejs IState definira ponašanje povezano sa svim mogućim stanjima klijenta. Klase StateA, State B itd. su klase koje implementiraju konkretno stanje objekta Context klase.

-Q: Iskorišteno u projektu?

A: Ne

-Q: Ako nije, gdje bi bilo dobro mjesto za njihovu upotrebu i zašto?

A: Ne vidimo nigdje efektivan način gdje bi se ovaj pattern mogao iskoristiti.

## 10. Observer pattern - Patterni ponašanja

-Q: Kada koristimo?

A: Observer patern koristimo kada je potrebno uspostaviti relaciju između objekata tako da kada jedan objekat promijeni stanje, drugi zainteresirani objekti dobijaju obavijest o promjeni.

-Q: Kako koristimo?

A: Uvodimo nove klase Subject klasu i Observer klasu. Instanca klase Subject mijenja svoje stanje i obavještava Observer klase koje predstavljaju konkretne klase koje obezbjeđuju konkretnu implementaciju za IObserver interfejs(sadrži samo jednu metodu - Update koja se poziva nakon promjene stanja neke Subject instance). Subject klasa sadrži privatni događaj Notify(Event mehanizam za pozivanje Update metode za sve posmatrače).

-Q: Iskorišteno u projektu?

A: Ne

-Q: Ako nije, gdje bi bilo dobro mjesto za njihovu upotrebu i zašto?

A: Ne vidimo nigdje efektivan način gdje bi se ovaj pattern  mogao iskoristiti.

