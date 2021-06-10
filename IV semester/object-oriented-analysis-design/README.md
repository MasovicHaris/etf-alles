# Grupa10 ~ Team - something


![gif](https://media.giphy.com/media/l41YzQX6Zf3YgT4Ri/giphy.gif)


### Tema: Vicinor

![vicinor-logo](https://user-images.githubusercontent.com/37186899/37522627-c259062e-2924-11e8-9f06-1c6eb6394c94.png)

### Članovi tima:
- Dženana Šabović
- Haris Mašović 
- Samra Salihić

## Opis projekta

"Basically tinder for restaurants" - Mašović Haris

Vicinor je aplikacija koja omogućava korisniku (user-u) da na jednostavan način pronađe mjesto/objekat koje servira/prodaje hranu kao npr. fast food/restorani itd. pri čemu korisnik bira objekat koji mu se sviđa iz liste ponuđenih objekata.

Često korisnik dolazi u situaciju gdje ne može odlučiti gdje jesti, te pomoću ove aplikacije ima izbor restorana/fast food-ova (generalno food places) u određenom radijusu u odnosu na trenutnu lokaciju. Korisnik može izabrati određeni restoran i/ili dodati u listu svojih omiljenih restorana ponuđene restorane od strane aplikacije ili restorane u odnosu na trenutnu lokaciju definisane određenim radijusom kojeg je korisnik zadao. 

Nakon toga aplikacija daje upustva kako doći na određenu lokaciju koju je korisnik izabrao pomoću mape. Iz napisanih karakteristika, aplikacija omogućava uklanjane dvojbe korisnika vezane za izbor restorana/mjesta gdje može da jede što predstavlja glavni motiv za potražnju aplikacije.

Inače naziv vicinor (vicino - ital. znači nearby/close - blizu, a r kao restorani).

## Procesi

#### Registracija korisnika / izbor izmedju guest i aktivnog korisnika aplikacije /
Korisnik ima mogućnost da izabere tip user-a odnosno da bude obični guest user i da ima osnovne funkcionalnosti aplikacije ili da bude aktivni user, da ima dodatne funkcionalnosti pored osnovnih. 
Korisnik se registruje sa osnovnim podacima o sebi, a to su:
* Ime
* Prezime
* Password
* Korisničko ime 
* E-mail (nije obavezno)
* Datum rođenja (nije obavezno)
* Slika (nije obavezno)

#### Prikaz, filtriranje i odabir restorana u željenom radijusu
Ovaj proces mora biti automatizovan. Kada korisnik zatraži spisak restorana/mjesta za jesti, proces mora prvo provjeriti da li je lokacija ispravno uspostavljena i nakon toga mora pokupiti sva mjesta za jesti koja se nalaze u radijusu koji je definisan unaprijed od strane korisnika (možda korisnik ne želi previše hodati/putovati, samim tim ima mogućnost da bira radjius).
Kada korisnik pokrene pretragu mora dobiti određene restorane unutar tog radijusa u odnosu na poziciju gdje se nalazi. Naravno spisak restorana će biti organizovan u listu, pri čemu korisnik može sačuvati neke restorane kao željene odnosno može ih sačuvati u /wish list/-i. Element liste će sadržiti detaljne informacije o restoranu/mjestu za jesti. Nakon što korisnik izabere (ako izabere, jer ne mora nužno izabrati nijedan od ponuđenih restorana, ili se može desiti da nema restorana u određenom radijusu), korisnik dobija upute preko google maps, odnosno dobija najkraći put koji mora preći da bi došao do odabranog restorana.

#### Proces prikaza recenzija nekog restorana
Korisinik će moći pregledati recenzije i rating-e za određene restorane (googlemaps/api komentare) pri čemu mu te recenzije mogu pomoći pri odabiru restorana. 

#### Prikaz broja za poziv restorana
Korisnik ima mogućnost da dobije broj svakog restorana (koji se dobije pomoću api-a) iz liste restorana. Jednostavni klik na tu opciju mu to i omogućava.

#### Generisanje/prikaz preporučenih restorana
Aplikacija ima za mogućnost da korisniku ponudi spisak restorana (generalno) koji su po nekom algoritmu generisani (npr. top tier restorani, restorani sa najboljom ocjenom, najviše posjećeni restorani pomoću naše aplikacije itd).


## Funkcionalnosti

#### Korisnik:
* Mogućnost izbora/promijene radijusa pretrage restorana u odnosu na lokaciju korisnika
* Mogućnost pregleda restorana u vidu liste
* Mogućnost izbora restorana
* Mogućnost dobijanja uputa do odabranog restorana
* Mogućnost dobijanja broja za poziv restorana/objekta, prilikom izbora restorana
* Mogućnost izbora iz skupa restorana preporučenih od strane aplikacije
* Mogućnost pregleda feedbacka u vidu ratinga i komantara

#### Registrovani korisnik:
* Mogućnost uređivanje korisničkog profila
* Mogućnost pravljenja liste želja (lista omiljenih restorana)

#### Neregistrovani korisnik: 
* Mogućnost registracije korisnika

#### Administrator:
* Prikaz statistike
* Praćenje registrovanih korisnika sistema te banovanje korisnika po potrebi

## Akteri

- Neregistrovani korisnik (guest user) - ima mogućnost da se registruje na sistem i da tako koristi aplikaciju, ali može koristiti aplikaciju i kao guest user.
- Registrovani korisnik - može sve što i neregistrovani korisnik i ima mogućnost ostavljanja recenzija, sastavljanja liste želja idr. 
- Administrator sistema - Ima zadatak da nadgleda sistem.
