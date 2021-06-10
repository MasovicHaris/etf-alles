ALTER TABLE fizicka_lica
ADD (ime NUMBER(10),
  prezime NUMBER(10),
  datumRodjenja DATE NOT NULL,
  adresa CHAR(30));
ALTER TABLE kupci
DROP (  
    ime,
    prezime,
    datumRodjenja,
    grad,
    adresa);
ALTER TABLE uposlenici
DROP (  
    ime,
    prezime,
    datumRodjenja,
    grad,
    adresa);
	ALTER TABLE skladista
DROP (grad);
CREATE TABLE popust
(
idPopusta NUMBER(10) PRIMARY KEY,
idProizvoda NUMBER(10) REFERENCES proizvod(idProizvoda),
aktuelniPopust NUMBER(10),
procenatPopusta NUMBER(10)
);
CREATE TABLE garancija
(
idGarancije NUMBER(10) PRIMARY KEY,
idFakture NUMBER(10) REFERENCES faktura(idFakture),
datumPocetka DATE,
datumIsteka date
);
ALTER TABLE proizvod
ADD idSkladista NUMBER(10) REFERENCES skladista(idSkladista);
ALTER TABLE faktura
ADD idPopusta NUMBER(10) REFERENCES popust(idPopusta);

DROP TABLE marketing;
DROP TABLE kadrovska_sluzba;
DROP TABLE menadzment;
DROP TABLE servis;
DROP TABLE odjel_za_skladista;