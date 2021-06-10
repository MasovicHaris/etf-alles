CREATE TABLE kontinent
(
   nazivKontinenta CHAR(30) PRIMARY KEY
);
CREATE TABLE drzava
(
   naziv CHAR(30) PRIMARY KEY,
   nazivKontinenta CHAR(30) REFERENCES kontinent(nazivKontinenta)
);
CREATE TABLE lica
(
   idLica NUMBER(10) PRIMARY KEY,
   nazivDrzave CHAR(30) REFERENCES drzava(naziv)
);
CREATE TABLE fizicka_lica
(
   idLica NUMBER(10) REFERENCES lica(idLica)
);
CREATE TABLE pravna_lica
(
   brUgovora NUMBER(10) PRIMARY KEY,
   idLica NUMBER(10) REFERENCES lica(idLica),
   naziv  CHAR(30),
   sjediste CHAR(30),
   datumPotpisivanja DATE NOT NULL,
   datumRaskidanja DATE
);
CREATE TABLE proizvodjaci
(
   brUgovora NUMBER(10) REFERENCES pravna_lica(brUgovora)
);

CREATE TABLE kurirske_sluzbe
(
  brUgovora NUMBER(10) REFERENCES pravna_lica(brUgovora)
);
CREATE TABLE kategorija
(
  idKategorije NUMBER(10) PRIMARY KEY,
  nadKategorija NUMBER(10) REFERENCES kategorija(idKategorije)
);
CREATE TABLE kupci
(
  idKupca NUMBER(10) PRIMARY KEY,
  ime NUMBER(10),
  prezime NUMBER(10),
  datumRodjenja DATE NOT NULL,
  grad CHAR(30),
  adresa CHAR(30)
);
CREATE TABLE odjel
(
  idOdjela NUMBER(10) PRIMARY KEY
);

CREATE TABLE uposlenici
(
  idUposlenika NUMBER(10) PRIMARY KEY,
  plata NUMBER(10),
  brojUgovora NUMBER(10),
  brojRacuna NUMBER(10),
  ime NUMBER(10),
  prezime NUMBER(10),
  datumRodjenja DATE NOT NULL,
  grad CHAR(30),
  adresa CHAR(30),
  idOdjela NUMBER(10) REFERENCES odjel(idOdjela)
);

ALTER TABLE odjel
  ADD sefOdjela NUMBER(10) REFERENCES uposlenici(idUposlenika);
CREATE TABLE marketing
(
  idOdjela NUMBER(10) REFERENCES odjel(idOdjela)
);
CREATE TABLE kadrovska_sluzba
(
  idOdjela NUMBER(10) REFERENCES odjel(idOdjela)
);
CREATE TABLE menadzment
(
  idOdjela NUMBER(10) REFERENCES odjel(idOdjela)
);
CREATE TABLE servis
(
  idOdjela NUMBER(10) REFERENCES odjel(idOdjela)
);
CREATE TABLE odjel_za_skladista
(
  idOdjela NUMBER(10) REFERENCES odjel(idOdjela)
);

CREATE TABLE skladista
(
   idSkladista NUMBER(10) PRIMARY KEY,
   odgovornaOsobaId NUMBER(10) REFERENCES uposlenici(idUposlenika),
   nazivDrzave CHAR(30) REFERENCES drzava(naziv),
   naziv CHAR(30),
   adresa CHAR(30),
   grad CHAR(30)
);

CREATE TABLE proizvod
(
  idProizvoda NUMBER(10) PRIMARY KEY,
  cijena NUMBER(10),
  naziv CHAR(30),
  idKategorije NUMBER(10) REFERENCES kategorija(idKategorije)
);
CREATE TABLE faktura
(
  idFakture NUMBER(10) PRIMARY KEY,
  idKupca NUMBER(10) REFERENCES kupci(idKupca),
  datumProdaje DATE NOT NULL,
  iznosRacuna NUMBER(10)
);
CREATE TABLE kolicina
(
  kolicinaRobe NUMBER(10) PRIMARY KEY,
  idFakture NUMBER(10) REFERENCES faktura(idFakture),
  idProizvoda NUMBER(10) REFERENCES proizvod(idProizvoda)
);