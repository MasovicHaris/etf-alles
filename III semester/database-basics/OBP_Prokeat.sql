-- Kreiranje tabele regije (ogranicenja/sekvence/popunjavanje)
CREATE TABLE Regije (
    region_id  NUMBER(10) NOT NULL,
    region_name varchar(255) NOT NULL,
    CONSTRAINT Regije_region_id_PK PRIMARY KEY (region_id)
);

CREATE  SEQUENCE sekvenca_Regije
START WITH 1
INCREMENT BY 1
NOCACHE
NOCYCLE;

-- nema smisla vise od 4 (ako treba 10 po prosjeku..)

INSERT INTO Regije
VALUES (sekvenca_Regije.nextval, 'Europe');
INSERT INTO Regije
VALUES (sekvenca_Regije.nextval, 'America');
INSERT INTO Regije
VALUES (sekvenca_Regije.nextval, 'Asia');
INSERT INTO Regije
VALUES (sekvenca_Regije.nextval, 'Middle East and Africa');


-- Kreiranje tabele Zemlje (ogranicenja/sekvence/popunjavanje)

CREATE TABLE Zemlje (
    country_id  CHAR(2) NOT NULL,
    country_name varchar(255) NOT NULL,
    region_id NUMBER(10) NOT NULL,
    CONSTRAINT Zemlje_country_id_PK PRIMARY KEY (country_id),
    CONSTRAINT Zemlje_region_id_FK FOREIGN KEY (region_id) REFERENCES Regije (region_id)
);


INSERT INTO Zemlje
VALUES ('MX', 'Mexico', 3);
INSERT INTO Zemlje
VALUES ('AU', 'Australia', 5);
INSERT INTO Zemlje
VALUES ('BE', 'Belgium', 2);
INSERT INTO Zemlje
VALUES ('BR', 'Brazil', 3);
INSERT INTO Zemlje
VALUES ('CA', 'Canada', 3);
INSERT INTO Zemlje
VALUES ('CH', 'Switzerland', 2);
INSERT INTO Zemlje
VALUES ('CN', 'China', 4);
INSERT INTO Zemlje
VALUES ('DE', 'Germany', 2);
INSERT INTO Zemlje
VALUES ('DK', 'Denmark', 2);
INSERT INTO Zemlje
VALUES ('EG', 'Egypt', 5);

-- update zemalja
ALTER TABLE zemlje ADD(porez float);
UPDATE zemlje
SET porez = 0.15;
ALTER TABLE zemlje MODIFY porez NOT NULL NOVALIDATE;


-- Kreiranje tabele Lokacije (ogranicenja/sekvence/popunjavanje)

CREATE TABLE Lokacije (
    location_id  NUMBER(10) NOT NULL,
    adresa varchar(255) NOT NULL,
    postal_sfira NUMBER(10) NOT NULL,
    grad VARCHAR(255) NOT NULL,
    country_id CHAR(2) NOT NULL,
    CONSTRAINT Lokacije_location_id_PK PRIMARY KEY (location_id),
    CONSTRAINT Lokacije_country_id_FK FOREIGN KEY (country_id) REFERENCES Zemlje (country_id)
);

CREATE SEQUENCE sekvenca_Lokacije
START WITH 1
INCREMENT BY 1
NOCACHE
NOCYCLE;

INSERT INTO Lokacije
VALUES (sekvenca_Lokacije.nextval, dbms_random.string('l', 10),  Dbms_Random.value(1,1000),
'Ciuadad de Juarez', 'MX');
INSERT INTO Lokacije
VALUES (sekvenca_Lokacije.nextval, dbms_random.string('l', 10),  Dbms_Random.value(1,1000),
dbms_random.string('l', 10), 'MX');
INSERT INTO Lokacije
VALUES (sekvenca_Lokacije.nextval, dbms_random.string('l', 10),  Dbms_Random.value(1,1000),
dbms_random.string('l', 10), 'MX');
INSERT INTO Lokacije
VALUES (sekvenca_Lokacije.nextval, dbms_random.string('l', 10),  Dbms_Random.value(1,1000),
dbms_random.string('l', 10), 'AU');
INSERT INTO Lokacije
VALUES (sekvenca_Lokacije.nextval, dbms_random.string('l', 10),  Dbms_Random.value(1,1000),
dbms_random.string('l', 10), 'AU');
INSERT INTO Lokacije
VALUES (sekvenca_Lokacije.nextval, dbms_random.string('l', 10),  Dbms_Random.value(1,1000),
dbms_random.string('l', 10), 'BR');
INSERT INTO Lokacije
VALUES (sekvenca_Lokacije.nextval, dbms_random.string('l', 10),  Dbms_Random.Value(1,1000),
dbms_random.string('l', 10), 'BR');
INSERT INTO Lokacije
VALUES (sekvenca_Lokacije.nextval, dbms_random.string('l', 10),  Dbms_Random.value(1,1000),
dbms_random.string('l', 10), 'CN');
INSERT INTO Lokacije
VALUES (sekvenca_Lokacije.nextval, dbms_random.string('l', 10),  Dbms_Random.value(1,1000),
dbms_random.string('l', 10), 'CN');
INSERT INTO Lokacije
VALUES (sekvenca_Lokacije.nextval, dbms_random.string('l', 10),  Dbms_Random.value(1,1000),
dbms_random.string('l', 10), 'BE');
INSERT INTO Lokacije
VALUES (sekvenca_Lokacije.nextval, dbms_random.string('l', 10),  Dbms_Random.value(1,1000),
dbms_random.string('l', 10), 'BE');

-- Kreiranje tabele Poslovnice (ogranicenja/sekvence/popunjavanje)

CREATE TABLE Poslovnice (
    poslovnica_id  NUMBER(10) NOT NULL,
    naziv_poslovnice varchar(255) NOT NULL,
    manager_poslovnice NUMBER(10) NOT NULL,
    poslovnica_gid NUMBER(10),
    location_id NUMBER(10) NOT NULL
);

CREATE SEQUENCE sekvenca_Poslovnica
START WITH 1
INCREMENT BY 1
NOCACHE
NOCYCLE;

INSERT INTO Poslovnice
VALUES (sekvenca_Poslovnica.nextval, dbms_random.string('U', 7),  2, NULL, 2);
INSERT INTO Poslovnice
VALUES (sekvenca_Poslovnica.nextval, dbms_random.string('U', 7),  2, 2, 2);
INSERT INTO Poslovnice
VALUES (sekvenca_Poslovnica.nextval, dbms_random.string('U', 7),  3, 2, 2);

INSERT INTO Poslovnice
VALUES (sekvenca_Poslovnica.nextval, dbms_random.string('U', 7),  3, 3, 3);
INSERT INTO Poslovnice
VALUES (sekvenca_Poslovnica.nextval, dbms_random.string('U', 7),  4, 3, 4);

 -- update poslovnica
ALTER TABLE poslovnice ADD(stanje_poslovnice NUMBER);

UPDATE poslovnice
SET stanje_poslovnice = 10000;
ALTER TABLE poslovnice MODIFY stanje_poslovnice NOT NULL NOVALIDATE;


-- Kreiranje tabele Zaposleni (ogranicenja/sekvence/popunjavanje)

CREATE TABLE Zaposleni (
    zaposleni_id  NUMBER(10) NOT NULL,
    first_name VARCHAR(20) NOT NULL,
    last_name VARCHAR(20) NOT NULL,
    email VARCHAR(40) NOT NULL,
    hire_date DATE,
    manager_id NUMBER(10),
    odjel_id NUMBER(10)
);

CREATE SEQUENCE sekvenca_Zaposleni
START WITH 1
INCREMENT BY 1
NOCACHE
NOCYCLE;

INSERT INTO Zaposleni
VALUES (sekvenca_Zaposleni.NEXTVAL, 'Haris', 'Prasovic', 'email', SYSDATE, NULL, 2);
INSERT INTO Zaposleni
VALUES (sekvenca_Zaposleni.NEXTVAL, dbms_random.string('U', 5), dbms_random.string('U', 8),
 'email', SYSDATE, 2, 3);
INSERT INTO Zaposleni
VALUES (sekvenca_Zaposleni.NEXTVAL, dbms_random.string('U', 5), dbms_random.string('U', 8),
 'email', SYSDATE, 2, 4);
INSERT INTO Zaposleni
VALUES (sekvenca_Zaposleni.NEXTVAL, dbms_random.string('U', 5), dbms_random.string('U', 8),
 'email', SYSDATE, 2, 5);
 INSERT INTO Zaposleni
VALUES (sekvenca_Zaposleni.NEXTVAL, dbms_random.string('U', 5), dbms_random.string('U', 8),
 'email', SYSDATE, 3, 6);
 INSERT INTO Zaposleni
VALUES (sekvenca_Zaposleni.NEXTVAL, dbms_random.string('U', 5), dbms_random.string('U', 8),
 'email', SYSDATE, 3, 7);
 INSERT INTO Zaposleni
VALUES (sekvenca_Zaposleni.NEXTVAL, dbms_random.string('U', 5), dbms_random.string('U', 8),
 'email', SYSDATE, 3, 8);
 INSERT INTO Zaposleni
VALUES (sekvenca_Zaposleni.NEXTVAL, dbms_random.string('U', 5), dbms_random.string('U', 8),
 'email', SYSDATE, 4, 9);
 INSERT INTO Zaposleni
VALUES (sekvenca_Zaposleni.NEXTVAL, dbms_random.string('U', 5), dbms_random.string('U', 8),
 'email', SYSDATE, 5, 10);
 INSERT INTO Zaposleni
VALUES (sekvenca_Zaposleni.NEXTVAL, dbms_random.string('U', 5), dbms_random.string('U', 8),
 'email', SYSDATE, 6, 11);

ALTER TABLE Zaposleni ADD(salary float);

UPDATE Zaposleni
SET salary = 5000;

ALTER TABLE zaposleni MODIFY salary NOT NULL NOVALIDATE;

ALTER TABLE Zaposleni ADD(opis_posla VARCHAR(50));

UPDATE Zaposleni
SET opis_posla = dbms_random.string('U', 7);

ALTER TABLE zaposleni MODIFY opis_posla NOT NULL NOVALIDATE;

-- Kreiranje tabele Odjeli (ogranicenja/sekvence/popunjavanje)

CREATE TABLE Odjeli (
    odjel_id  NUMBER(10) NOT NULL,
    naziv_odjela VARCHAR(30) NOT NULL,
    manager_id NUMBER(10)
);

CREATE SEQUENCE sekvenca_Odjeli
START WITH 1
INCREMENT BY 1
NOCACHE
NOCYCLE;

INSERT INTO Odjeli
VALUES (sekvenca_Odjeli.nextval, dbms_random.string('U', 15), 2);
INSERT INTO Odjeli
VALUES (sekvenca_Odjeli.nextval, dbms_random.string('U', 15), 3);
INSERT INTO Odjeli
VALUES (sekvenca_Odjeli.nextval, dbms_random.string('U', 15), 4);
INSERT INTO Odjeli
VALUES (sekvenca_Odjeli.nextval, dbms_random.string('U', 15), 5);
INSERT INTO Odjeli
VALUES (sekvenca_Odjeli.nextval, dbms_random.string('U', 15), 6);
INSERT INTO Odjeli
VALUES (sekvenca_Odjeli.nextval, dbms_random.string('U', 15), 7);
INSERT INTO Odjeli
VALUES (sekvenca_Odjeli.nextval, dbms_random.string('U', 15), 8);
INSERT INTO Odjeli
VALUES (sekvenca_Odjeli.nextval, dbms_random.string('U', 15), 9);
INSERT INTO Odjeli
VALUES (sekvenca_Odjeli.nextval, dbms_random.string('U', 15), 10);
INSERT INTO Odjeli
VALUES (sekvenca_Odjeli.nextval, dbms_random.string('U', 15), 6);

ALTER TABLE Odjeli ADD(poslovnica_id NUMBER(10));

UPDATE odjeli 
SET poslovnica_id = 2;

ALTER TABLE odjeli MODIFY poslovnica_id NOT NULL NOVALIDATE;

-- Dodavanje ogranicenja na prethodne 3 tabele..

 ALTER TABLE Poslovnice
 ADD CONSTRAINT Poslovnice_poslovnica_id_PK PRIMARY  KEY(poslovnica_id);

 ALTER TABLE Zaposleni
 ADD CONSTRAINT Zaposleni_zaposleni_id_PK PRIMARY  KEY(zaposleni_id);

 ALTER TABLE Odjeli
 ADD CONSTRAINT Odjeli_odjel_id_PK PRIMARY  KEY(odjel_id);

 ALTER TABLE Poslovnice
 ADD CONSTRAINT Poslovnice_mananger_FK FOREIGN KEY(manager_poslovnice)
 REFERENCES Zaposleni (zaposleni_id);

 ALTER TABLE Poslovnice
 ADD CONSTRAINT Poslovnice_poslovnica_gid_FK FOREIGN KEY(poslovnica_gid)
 REFERENCES Poslovnice (poslovnica_id);

 ALTER TABLE Poslovnice
 ADD CONSTRAINT Poslovnice_location_id_FK FOREIGN KEY(location_id)
 REFERENCES Lokacije (location_id);

 -- ogranicenja za zaposlene

 ALTER TABLE Zaposleni
 ADD CONSTRAINT Zaposleni_poslovnica_id_FK FOREIGN KEY(poslovnica_id)
 REFERENCES Poslovnice (poslovnica_id);

 ALTER TABLE Zaposleni
 ADD CONSTRAINT Zaposleni_manager_id_FK FOREIGN KEY(manager_id)
 REFERENCES Zaposleni (zaposleni_id);

 ALTER TABLE Zaposleni
 ADD CONSTRAINT Zaposleni_odjel_id_FK FOREIGN KEY(odjel_id)
 REFERENCES Odjeli (odjel_id);

 -- ogranicenja za odjele
 ALTER TABLE Odjeli
 ADD CONSTRAINT Odjeli_manager_id_FK FOREIGN KEY(manager_id)
 REFERENCES Zaposleni (zaposleni_id);

 ALTER TABLE odjeli
 ADD CONSTRAINT odjeli_poslovnica_id_fk
 FOREIGN KEY(poslovnica_id) REFERENCES poslovnice (poslovnica_id);



 -------------------------------------------------------------------------------
 -- Kreiranje korisnickog djela
 -- Kreiranje tabele Klijenti (ogranicenja/sekvence/popunjavanje)


CREATE TABLE Klijenti (
    klijent_id  NUMBER(10) NOT NULL,
    first_name VARCHAR(30) NOT NULL,
    last_name VARCHAR (30) NOT NULL,
    email VARCHAR(30),
    spol CHAR(1) NOT NULL,
    CONSTRAINT Klijenti_klijent_id_PK PRIMARY KEY(klijent_id),
    CONSTRAINT Klijenti_spol_check CHECK (Upper(spol) IN ('M', 'Z', 'Ž'))
);

CREATE SEQUENCE sekvenca_Klijenti
START WITH 1
INCREMENT BY 1
NOCACHE
NOCYCLE;

INSERT INTO Klijenti
VALUES (sekvenca_Klijenti.NEXTVAL, 'Klijent', 'Broj 1', NULL, 'M');
INSERT INTO Klijenti
VALUES (sekvenca_Klijenti.NEXTVAL, 'Klijent', 'Broj 2', NULL, 'M');
INSERT INTO Klijenti
VALUES (sekvenca_Klijenti.NEXTVAL, 'Klijent', 'Broj 3', NULL, 'M');
INSERT INTO Klijenti
VALUES (sekvenca_Klijenti.NEXTVAL, 'Klijent', 'Broj 4', NULL, 'M');
INSERT INTO Klijenti
VALUES (sekvenca_Klijenti.NEXTVAL, 'Klijent', 'Broj 5', NULL, 'M');
INSERT INTO Klijenti
VALUES (sekvenca_Klijenti.NEXTVAL, 'Klijent', 'Broj 6', NULL, 'M');
INSERT INTO Klijenti
VALUES (sekvenca_Klijenti.NEXTVAL, 'Klijent', 'Broj 7', NULL, 'M');
INSERT INTO Klijenti
VALUES (sekvenca_Klijenti.NEXTVAL, 'Klijent', 'Broj 8', NULL, 'M');
INSERT INTO Klijenti
VALUES (sekvenca_Klijenti.NEXTVAL, 'Klijent', 'Broj 9', NULL, 'M');
INSERT INTO Klijenti
VALUES (sekvenca_Klijenti.NEXTVAL, 'Klijent', 'Broj 10', NULL, 'M');

-- Kreiranje tabele Racuni (ogranicenja/sekvence/popunjavanje)

CREATE TABLE Racuni (
    racun_id  NUMBER(10) NOT NULL,
    stanje_klijenta NUMBER(12) NOT NULL,
    klijent_id FLOAT(10) NOT NULL,
    CONSTRAINT Racun_racun_id_PK PRIMARY KEY(racun_id),
    CONSTRAINT Racun_klijent_id_FK FOREIGN KEY(klijent_id) REFERENCES Klijenti (klijent_id)
);

CREATE SEQUENCE sekvenca_Racuni
START WITH 1
INCREMENT BY 1
NOCACHE
NOCYCLE;

INSERT INTO Racuni
VALUES (sekvenca_Racuni.NEXTVAL, dbms_random.Value(0,1000), 2);
INSERT INTO Racuni
VALUES (sekvenca_Racuni.NEXTVAL, dbms_random.Value(0,1000), 3);
INSERT INTO Racuni
VALUES (sekvenca_Racuni.NEXTVAL, dbms_random.Value(0,1000), 4);
INSERT INTO Racuni
VALUES (sekvenca_Racuni.NEXTVAL, dbms_random.Value(0,1000), 5);
INSERT INTO Racuni
VALUES (sekvenca_Racuni.NEXTVAL, dbms_random.Value(0,1000), 6);
INSERT INTO Racuni
VALUES (sekvenca_Racuni.NEXTVAL, dbms_random.Value(0,1000), 7);
INSERT INTO Racuni
VALUES (sekvenca_Racuni.NEXTVAL, dbms_random.Value(0,1000), 8);
INSERT INTO Racuni
VALUES (sekvenca_Racuni.NEXTVAL, dbms_random.Value(0,1000), 9);
INSERT INTO Racuni
VALUES (sekvenca_Racuni.NEXTVAL, dbms_random.Value(0,1000), 10);
INSERT INTO Racuni
VALUES (sekvenca_Racuni.NEXTVAL, dbms_random.Value(0,1000), 11);
INSERT INTO Racuni
VALUES (sekvenca_Racuni.NEXTVAL, dbms_random.Value(0,1000), 2);


-- Kreiranje tabele Listici (ogranicenja/sekvence/popunjavanje)

CREATE TABLE Listici (
    listic_id  NUMBER(10) NOT NULL,
    racun_id NUMBER(10) NOT NULL,
    uplaceno FLOAT(10) NOT NULL,
    dobitak FLOAT(10) NOT NULL,
    pogodnost CHAR(2) NOT NULL,
    dobitan CHAR(2) NOT NULL,
    poslovnica_id NUMBER(10) NOT NULL,
    CONSTRAINT Listici_listic_id_PK PRIMARY KEY (listic_id),
    CONSTRAINT Listici_racun_id_FK FOREIGN KEY(racun_id) REFERENCES Racuni (racun_id),
    CONSTRAINT Listici_pogodnost_CHECK CHECK (Upper(pogodnost) IN ('DA', 'NE')),
    CONSTRAINT Listici_poslovnica_id_FK FOREIGN KEY(poslovnica_id) REFERENCES Poslovnice (poslovnica_id),
    CONSTRAINT Listici_dobitak_CHECK CHECK (Upper(dobitan) IN ('DA', 'NE'))
);

CREATE SEQUENCE sekvenca_Listici
START WITH 1
INCREMENT BY 1
NOCACHE
NOCYCLE;

INSERT INTO Listici 
VALUES (sekvenca_listici.NEXTVAL, 2, 10, 15, 'NE', 'DA', 2);
INSERT INTO Listici 
VALUES (sekvenca_listici.NEXTVAL, 2, 10, 25, 'DA', 'NE', 3);
INSERT INTO Listici 
VALUES (sekvenca_listici.NEXTVAL, 2, 10, 15, 'NE', 'DA', 2);
INSERT INTO Listici 
VALUES (sekvenca_listici.NEXTVAL, 3, 10, 25, 'NE', 'DA', 5);
INSERT INTO Listici 
VALUES (sekvenca_listici.NEXTVAL, 3, 10, 25, 'NE', 'DA', 5);
INSERT INTO Listici 
VALUES (sekvenca_listici.NEXTVAL, 3, 15, 200, 'NE', 'NE', 5);
INSERT INTO Listici 
VALUES (sekvenca_listici.NEXTVAL, 4, 15, 200, 'NE', 'NE', 5);
INSERT INTO Listici 
VALUES (sekvenca_listici.NEXTVAL, 5, 10, 25, 'DA', 'NE', 4);
INSERT INTO Listici 
VALUES (sekvenca_listici.NEXTVAL, 6, 10, 25, 'DA', 'NE', 3);
INSERT INTO Listici 
VALUES (sekvenca_listici.NEXTVAL,8, 10, 2500, 'DA', 'DA', 5);

ALTER TABLE Listici ADD(datum_uplate DATE);

UPDATE listici
SET datum_uplate = SYSDATE;

ALTER TABLE listici MODIFY datum_uplate NOT NULL NOVALIDATE;

ALTER TABLE listici  ADD( isplaceno CHAR(2));

UPDATE listici 
SET isplaceno = 'NE';

ALTER TABLE listici MODIFY isplaceno NOT NULL NOVALIDATE;

ALTER TABLE listici
ADD CONSTRAINT listici_isplaceno_CHECH CHECK (isplaceno IN ('DA','NE'));


-- Kreiranje tabele Opklade (ogranicenja/sekvence/popunjavanje)

CREATE TABLE Opklade (
    opklada_id  NUMBER(10) NOT NULL,
    subjekt1 VARCHAR(200) NOT NULL,
    subjekt2 VARCHAR(200),
    tip_opklade NUMBER(1) NOT NULL,
    CONSTRAINT Opklade_opklada_id_PK PRIMARY KEY (opklada_id),
    CONSTRAINT Opklade_tip_opklade_CHECK CHECK(tip_opklade IN (1,2))
);

CREATE SEQUENCE sekvenca_opklade
START WITH 1
INCREMENT BY 1
NOCACHE
NOCYCLE;



INSERT INTO Opklade 
VALUES (sekvenca_opklade.NEXTVAL, 'FK Zeljeznicar', 'FK Sarajevo', 2);
INSERT INTO Opklade 
VALUES (sekvenca_opklade.NEXTVAL, 'FK Zrinjski', 'FK Celik', 2);
INSERT INTO Opklade 
VALUES (sekvenca_opklade.NEXTVAL, 'Ko daje go - derbi', NULL , 1);
INSERT INTO Opklade 
VALUES (sekvenca_opklade.NEXTVAL, 'Roger Federer', 'Nadal', 2);

INSERT INTO Opklade 
VALUES (sekvenca_opklade.NEXTVAL, 'Utrka kornjaca', NULL , 1);
INSERT INTO Opklade 
VALUES (sekvenca_opklade.NEXTVAL,  'Utrka horoza', NULL ,  1);
INSERT INTO Opklade 
VALUES (sekvenca_opklade.NEXTVAL,  'Utrka kornjaca 2', NULL ,  1);

INSERT INTO Opklade 
VALUES (sekvenca_opklade.NEXTVAL,  'FK Zeljeznicar', 'FK Sarajevo',  2);
INSERT INTO Opklade 
VALUES (sekvenca_opklade.NEXTVAL,  'FK GoskGabela', 'FK Zeljeznicar', 2);
INSERT INTO Opklade 
VALUES (sekvenca_opklade.NEXTVAL,  'Utrka kornjaca 3', NULL , 1);

ALTER TABLE opklade ADD(datum_desavanja DATE);

UPDATE opklade 
SET datum_desavanja = SYSDATE;

ALTER TABLE opklade MODIFY datum_desavanja NOT NULL NOVALIDATE;

-- Kreiranje tabele StatistikaInfo_opklada (ogranicenja/sekvence/popunjavanje)

CREATE TABLE StatistikaInfo_opklada (
    opklada_id  NUMBER(10) NOT NULL,
    informacija VARCHAR2(255) NOT NULL,
    CONSTRAINT SI_opklada_id_FK FOREIGN KEY (opklada_id) REFERENCES Opklade(opklada_id)
);


-- 2
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'Dame i gospodo dobro dosli na najbolji derbi na svijetu');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'Standardne ekipe kao sto je vec najavljeno prije nas');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'Utakmica je pocela, forza Zeljo fadile!');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'Forza Sarajevo Hasane, idemo!');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'21 minuta, pokusaj Sarajeva, ali kjosevski fenomenalno brani, do sada mirna utakmica');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'33 minuta Zakariiiiiic GO, vodi zeljo 1-0');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'GO GO GOOOOOOOOOOOOOOO');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'E moj fadile, kakvo tvoje sarajevo');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'Utakmica traje 90 minuta Hasane, samo da znas');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'Kraj prvog poluvremena, rezultat 1-0 fenomenalno zeljo vodi protiv sarajeva');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'Pocelo je drugo poluvrijeme');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'67 minuta ASIM ZEC GOOOOOOOOOO');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'Zeljeznicar vodi 2-0 protiv sarajeva, sace 90 minuta Fadile ne sekiraj se');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'69 minuta Haris Hajdarevic GOOOOOOOO');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'Zeljeznicar vodi 3-0, ovo nema smisla vise komentarisati');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'Kraj utakmice, Zeljeznicar je pobjedio sa 3-0 protiv sarajeva');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'E moj fadile pojma ti o zivotu nemas, ali zato vi slusatelji');
INSERT INTO StatistikaInfo_opklada 
VALUES (2,'ostanite sa nama, uskoro ide serija Elif, toliko od nas.');

-- Kreiranje tabele korisnicke_opklade (ogranicenja/sekvence/popunjavanje)

CREATE TABLE Korisnicke_opklade (
    kopklada_id  NUMBER(10) NOT NULL,
    listic_id NUMBER(10) NOT NULL,
    opklada_id NUMBER(10) NOT NULL,
    opis_opklade VARCHAR(200) NOT NULL,
    pogodak CHAR(2),
    CONSTRAINT Kopklade_kopklada_id_PK PRIMARY KEY (kopklada_id),
    CONSTRAINT Kopklade_listic_id_FK FOREIGN KEY (listic_id) REFERENCES listici(listic_id),
    CONSTRAINT Kopklade_opklada_id_FK FOREIGN KEY (opklada_id) REFERENCES opklade(opklada_id),
    CONSTRAINT Kopklade_pogodak_CHECK CHECK (Upper(pogodak) IN ('DA','NE'))
);

CREATE SEQUENCE sekvenca_kopklade
START WITH 1
INCREMENT BY 1
NOCACHE
NOCYCLE;

SELECT sekvenca_kopklade.NEXTVAL FROM dual 

INSERT INTO Korisnicke_opklade 
VALUES (sekvenca_kopklade.NEXTVAL, 2, 2, 'dobija zeljo', 'DA');
INSERT INTO Korisnicke_opklade 
VALUES (sekvenca_kopklade.NEXTVAL, 2, 3, 'dobija zrinjski', 'DA');
INSERT INTO Korisnicke_opklade 
VALUES (sekvenca_kopklade.NEXTVAL, 2, 4, 'Goran Zakaric', 'DA');
INSERT INTO Korisnicke_opklade 
VALUES (sekvenca_kopklade.NEXTVAL, 3, 5, 'Nadal dobija', 'NE');

INSERT INTO Korisnicke_opklade 
VALUES (sekvenca_kopklade.NEXTVAL, 4, 6, 'Dobija zuta kornjaca', 'NE');
INSERT INTO Korisnicke_opklade 
VALUES (sekvenca_kopklade.NEXTVAL, 4, 6, 'Zadnja crvena kornjaca', 'DA');
INSERT INTO Korisnicke_opklade 
VALUES (sekvenca_kopklade.NEXTVAL, 4, 6, 'Drugo mjesto plava kornjaca', 'DA');

INSERT INTO Korisnicke_opklade 
VALUES (sekvenca_kopklade.NEXTVAL, 5, 7, 'Dobija zuti horoz', 'DA');
INSERT INTO Korisnicke_opklade 
VALUES (sekvenca_kopklade.NEXTVAL, 5, 7, 'Zadnji crveni horoz', 'DA');
INSERT INTO Korisnicke_opklade 
VALUES (sekvenca_kopklade.NEXTVAL, 5, 7, 'Trece mjesto plavi horoz', 'DA');




-- 30 SQL upita --

-- 10 jednostavnijih upita

-- 1. lista svih listica koji su uplaceni ikad

SELECT * FROM Listici;                                                                                    

-- 2. lista svih poslovnica i gradovi u kojima se nalaze te poslovnice

SELECT p.naziv_poslovnice AS Naziv_poslovnice, l.grad AS Grad_poslovnice                                  
FROM poslovnice p , lokacije l
WHERE p.location_id = l.location_id;

-- 3. spisak svih poslovnica unutar mexica

SELECT p.naziv_poslovnice AS Naziv_poslovnice, l.grad AS Grad                                             
FROM poslovnice p, lokacije l, zemlje z
WHERE p.location_id = l.location_id AND l.country_id = z.country_id AND z.country_id = 'MX';                                                            

-- 4. spisak klijenata i identfikacionih racuna koje imaju

SELECT k.first_name || ' ' || k.last_name AS Naziv_klijenta, r.racun_id AS Racun_klijenta                 
FROM klijenti k, racuni r
WHERE k.klijent_id = r.klijent_id;                                                                                        

-- 5. spisak svih listica koji su imali dobitak preko 2k

SELECT listic_id AS Listic_broj , dobitak AS Dobitan, racun_id AS Racun_korisnika                         
FROM listici 
WHERE dobitan = 'DA' AND dobitak > 2000;                                                                                           

-- 6. prikaz racuna za odredenog klijenta, samo klijent treba da pamti broj racuna

SELECT k.first_name || ' ' || k.last_name AS Naziv, r.stanje_klijenta, l.uplaceno, l.dobitak, l.dobitan   
FROM klijenti k, racuni r, listici l
WHERE k.klijent_id = r.klijent_id AND r.racun_id = l.racun_id AND r.racun_id = 2; 

-- 7. prikaz svih poslovnica i managera, uz novcano stanje svake poslovnice

SELECT p.naziv_poslovnice AS Naziv_poslovnice, p.stanje_poslovnice AS Stanje_poslovnice,                  
zap.first_name || ' ' || zap.last_name AS Manager_poslovnice
FROM poslovnice p, zaposleni zap
WHERE p.manager_poslovnice = zap.zaposleni_id;

-- 8. spisak svih regija u kojima su zastupljene poslovnice

SELECT DISTINCT reg.region_name AS Regije_poslovnica                                                      
FROM poslovnice p, lokacije l, zemlje z, regije reg
WHERE p.location_id = l.location_id AND z.country_id = l.country_id AND reg.region_id = z.region_id;

-- 9. spisak svih kladenja samo na 1 subjekta

SELECT k.listic_id AS Broj_listica, o.subjekt1 AS ID_opklada,                                             
opis_opklade AS Opis_opklade, k.Pogodak AS Rezultat 
FROM korisnicke_opklade k, opklade o
WHERE o.tip_opklade = 1 AND k.opklada_id = o.opklada_id;

-- 10. spisak listica koji su uplaceni u zadnjih 7 dana i 
-- u kojim poslovnicama su uplaceni

SELECT l.racun_id AS Sifra_racuna, l.Uplaceno, l.Dobitak, l.Dobitan,                                      
p.naziv_poslovnice AS Naziv_poslovnice_gdje_uplaceno                                                                                                                                                   
FROM listici l, poslovnice p
WHERE SYSDATE - datum_uplate <= 7 AND l.poslovnica_id = p.poslovnica_id;
                                                                                                          

-- 5 upita sa grupnim funkcijama (minimalno 2 sa HAVING klauzulom)

INSERT INTO Zaposleni
VALUES (sekvenca_Zaposleni.NEXTVAL, 'Haris', 'Zrasovic', 'email', SYSDATE, 2, 3, 3000, 'CAWLULS');

-- 1. Broj po poslovima u citavim firmama, tj. sveukupno koliko ima radnika razlicite vrste

SELECT z.opis_posla AS "Naziv posla",                                                                     
Count(z.zaposleni_id) AS "Broj po poslovima"
FROM zaposleni z
GROUP BY z.opis_posla;
                            
-- 2. Spisak odjela, odjeli u tim gradovima, broj zaposlenih i prosjecna plata za 
-- sve zaposlene po odjelima koji prosjecnu platu manju od 5k  (kontrola biznisa)   
                                                                                                          
SELECT d.naziv_odjela AS Odjel , l.grad AS "Grad", Count (e.zaposleni_id) AS                              
"Broj zaposlenih", Avg(e.salary) AS "Prosjecna plata"                                                                                                                                                                                                                              
FROM zaposleni e, odjeli d, lokacije l, poslovnice p
WHERE e.odjel_id = d.odjel_id AND d.poslovnica_id = p.poslovnica_id
AND p.location_id = l.location_id
GROUP BY d.naziv_odjela, l.grad
HAVING Avg(e.salary) < 5000;                                                                                                   

-- 3. Broj zaposlenih u zadnje 4 godine

SELECT Sum(Decode(TO_CHAR(hire_date,'yyyy'),2015,1,0)) "2015g",                                           
       Sum(Decode(TO_CHAR(hire_date,'yyyy'),2016,1,0)) "2016g",
       Sum(Decode(TO_CHAR(hire_date,'yyyy'),2017,1,0)) "2017g", 
       Sum(Decode(TO_CHAR(hire_date,'yyyy'),2018,1,0)) "2018g"
FROM zaposleni;

 -- 4. Max,Min,Suma,Avg plata po odjelima

SELECT                                                                                                   
Round(Max(e.salary),6) "Max",
Round(Min(e.salary),6) "Min",
Round( Sum(e.salary),6) "Suma",
Round( Avg(e.salary),6) "Prosjek"
FROM zaposleni e, odjeli j
WHERE e.odjel_id = j.odjel_id
GROUP BY j.odjel_id;

 -- 5. Daje broj listica i klijente koji imaju vise od 3 listica, naravno moze biti n listica :D

SELECT k.first_name || ' ' || k.last_name  AS "Naziv klijenta " ,                                        
Count(l.listic_id) AS  "Broj listica po klijentima"                                                       
FROM klijenti k, racuni r, listici l
WHERE k.klijent_id = r.klijent_id AND
r.racun_id = l.racun_id
GROUP BY k.first_name || ' ' || k.last_name
HAVING Count(l.listic_id) >= 3                                                                            -- n
ORDER BY k.first_name || ' ' || k.last_name;


-- 5 upita sa korištenjem podupita

-- 1. Spisak svih kolega koje rade u istom odjelu kao Haris Zrasovic
-- ima samo 1 osoba

SELECT e.first_name || ' ' || e.last_name AS Naziv, d.naziv_odjela AS Naziv_odjela,                       
e.opis_posla AS Naziv_posla                                                                               
FROM zaposleni e, odjeli d
WHERE e.odjel_id = d.odjel_id AND 
e.first_name NOT LIKE 'Haris' AND last_name NOT LIKE 'Zrasovic' AND 
e.odjel_id = (SELECT odjel_id
                   FROM zaposleni
                   WHERE first_name LIKE 'Haris' AND last_name LIKE 'Zrasovic'
             )

-- 2. Spisak svih opklada u kojima se desila neka statistika
-- u ovom slucaju utakmice sa 2 subjekta gdje se spominje rezultat 2-2
-- treba biti prazno za nasu tabelu

SELECT *                                                                                                 
FROM opklade                                                                                             
WHERE opklada_id = ANY (SELECT opklada_id                                                                 
                         FROM statistikainfo_opklada
                         WHERE Upper(informacija) LIKE '%2-2%'
                        )  

-- 3. spisak svih zaposlenih, id, naziv zaposlenog, kao i naziv posla za sve
-- zaposlene koji rade u odjelu koji je locairan u Ciuadad de Juarez

SELECT e.zaposleni_id  AS Sifra, e.first_name || ' ' || e.last_name AS Naziv, e.opis_posla AS Posao       
FROM zaposleni e, odjeli d, lokacije l, poslovnice p                                                     
WHERE e.odjel_id = d.odjel_id AND p.location_id = l.location_id 
AND p.poslovnica_id = d.poslovnica_id
AND e.odjel_id = ANY( SELECT d1.odjel_id
                           FROM odjeli d1, lokacije l1, poslovnice p1
                           WHERE d1.poslovnica_id = p1.poslovnica_id 
                           AND p1.location_id = l1.location_id
                           AND l1.grad LIKE 'Ciuadad de Juarez')
ORDER BY e.zaposleni_id;

 -- 4. spisak svih zaposlenih koji imaju skoro pa najvecu platu, odosno -15% 
 -- u odnosu na max platu

SELECT e.zaposleni_id  AS Sifra, e.first_name || ' ' || e.last_name AS Naziv,                            
e.opis_posla AS Posao, e.salary AS Plata                                                                  
FROM zaposleni e
WHERE e.salary > (SELECT Max(salary) - 0.15 * Max(salary)
                  FROM zaposleni
                  )
ORDER BY e.zaposleni_id;

-- 5. Spisak svih zaposlenih ciji je nadredeni Haris Prasovic

SELECT *                                                                                                  
FROM zaposleni                                                                                           
WHERE manager_id = ANY ( SELECT zaposleni_id
                         FROM zaposleni
                         WHERE last_name LIKE 'Prasovic'
                        )


-- 5 upita sa više od jednog nivoa podupita

 -- 1. Spisak svih zaposlenih, cija je plata veca od pola maximalne plate 

SELECT *                                                                                                 
FROM (SELECT first_name || ' ' || last_name AS Naziv,                                                    
      SALARY AS plata FROM zaposleni 
      WHERE salary > (SELECT Max(salary)/2
                     FROM zaposleni)
      ORDER BY zaposleni_id
      )

-- 2. Spisak svih opklada koje imaju popratne statistike u vezi njih

SELECT * 
FROM (SELECT o.* FROM opklade o WHERE o.opklada_id = ANY (SELECT p.opklada_id                             
                                                          FROM statistikainfo_opklada p 
                                                          WHERE p.opklada_id = o.opklada_id
                                                         )
     )

-- 3. Top 3 najmanje placenih zaposlenih u kladionicama

SELECT *                                                                                                  
FROM ( SELECT first_name || ' ' || last_name AS Naziv, salary AS Plata                                    
       FROM zaposleni
       WHERE salary < (SELECT Max(salary) FROM zaposleni)
       ORDER BY salary DESC
     )     
WHERE ROWNUM <= 3;

-- 4. Spisak svih zaposlenih koji rade bilo kojem odjelu, ali u tom odjelu mora biti zaposleni
-- tako da mu ime pocinje sa istim slovom kao kod sefa tj. u ovom slucaju slovo H

SELECT *                                                                                                 
FROM zaposleni                                                                                            
WHERE odjel_id = ANY (SELECT odjel_id                                                                     
                         FROM zaposleni
                         WHERE first_name LIKE (SELECT SubStr(first_name,0,1) || '%'
                                                FROM zaposleni 
                                                WHERE zaposleni_id = (SELECT zaposleni_id
                                                                      FROM zaposleni 
                                                                      WHERE manager_id IS NULL
                                                                      )
                                                )
                      )
AND manager_id IS NOT NULL;    

 
-- 5. Daje spisak svih listica koji su uplacei u poslovnicama koje drzi glavni sef 
                                                                                                           
SELECT *                                                                                                  
FROM listici
WHERE poslovnica_id = ANY ( SELECT poslovnica_id
                        FROM poslovnice
                        WHERE manager_poslovnice = (SELECT zaposleni_id
                                            FROM zaposleni 
                                            WHERE manager_id IS NULL
                                           )
                      )
ORDER BY listic_id;


-- 2 upita sa subtotalima (ROLLUP, CUBE, GROUPING SETS)

-- 1. Prvih 50 odjela, zajedno sa platama po odjelima i sumarna plata

SELECT odjel_id, opis_posla, SUM(salary)                                                                 
FROM zaposleni 
WHERE odjel_id < 50
GROUP BY ROLLUP(odjel_id, opis_posla);

-- 2. Grupiranje prvo po odjelima za svakog zaposlenog
-- zatim po manager_id-u, pri cemu su zajednicki opis_posla

SELECT odjel_id , opis_posla, manager_id , Avg(salary) AS plata                                          
FROM zaposleni                                                                                           
WHERE odjel_id < 50
GROUP BY GROUPING SETS ((odjel_id,opis_posla), (opis_posla,manager_id))


-- 2 upita sa TOP N analizom

-- 1. top-3 zaposlena po imenu, tj. sortirana po imenu
SELECT *                                                                                                  
FROM ( SELECT first_name || ' ' || last_name AS Naziv FROM zaposleni ORDER BY first_name ASC ) 
WHERE ROWNUM <= 3; 

-- 2. top-5 zaposlenih po platama
SELECT * 
FROM (SELECT first_name || ' ' || last_name AS Naziv,                                                     
      SALARY AS plata FROM zaposleni ORDER BY salary DESC)
WHERE ROWNUM <= 5;                                                                                                         


-- 1 upit sa korištenjem UNION, SET

-- 1. Upit koji spaja, tj. prikazuje sve managere i njihove odjele
SELECT manager_id, odjel_id                                                                               
FROM odjeli;
UNION 
SELECT manager_id, odjel_id
FROM zaposleni



-- 5 indeksa uz detaljno objašnjenje kako ti indeksi doprinose bržem izvršenju nekih od
-- napisanih upita pod d)

-- Ako predpostavimo da su sve tabele koje trebaju biti vecinom velike (u odnosu na ovaj slucaj gdje ima ~10 slogova)
-- i ako kazemo da tabele koje se cesto azuriraju nema smisla koristiti index na njima imamo, odnosno te tabele su:
-- racuni,klijenti,listici,korisnicke_opklade,opklade,statistikainfo
-- te tabele se ucestalno dodavaju nove stvari, samim tim nema smisla dodavati nove indexe jer moze usporiti db      (*)

-- Imamo sljedece indexe (koji zadovoljavaju (*)):
-- 1. zaposleni @ salary - posto se ucestalo salary koristi u WHERE klauzuli ili JOIN uslovu spajanja
                        -- napisani upiti generalno vracaju 2-4% zaposlenih po odredenim platama

-- 2. zaposleni @ odjel_id - posto se vecina upita koristi/manipulise oko odjel_id moze se kreirati index za ovu kolonu
                          -- takoder moze sadrzavati citav spektar koji omogucava tabela odjeli

-- 3. poslovnice @ manager_poslovnice - posto pod vecine upita imamo vezu sa zaposlenim, takoder uslovi koriste ovu kolonu


-- 4. lokacije @ country_id - obicno se trazi zemlja u kojoj se lokacija nalazi, takoder koristi se u where klauzuli
                           -- zgodno pri pretrazi

-- 5. odjeli @ naziv_odjela - where klauzula vecinom, rijetko kad se dodaju novi odjeli
                           -- vraca relativno malo slogova tabela u odnosu na recimo zaposlene

CREATE INDEX zaposleni_salary_IX ON zaposleni(salary);
CREATE INDEX zaposleni_odjel_id_IX ON zaposleni(odjel_id);
CREATE INDEX poslovnice_manager_IX ON poslovnice(manager_poslovnice);
CREATE INDEX lokacije_country_id_IX ON lokacije(country_id);
CREATE INDEX odjeli_naziv_odjela_IX ON odjeli(naziv_odjela);



-- 10 funkcija

-- 1. vraca platu zaposlenika kad se proslijedi njegov id
CREATE OR REPLACE FUNCTION plata_zaposlenika (x zaposleni.zaposleni_id%TYPE) RETURN NUMBER                
IS
temp_stanje NUMBER:=0;
BEGIN
  SELECT salary
  INTO temp_stanje
  FROM zaposleni
  WHERE zaposleni_id = x;
  RETURN temp_stanje;
END plata_zaposlenika;
/

-- 2. vraca broj poslovnica u nekom gradu
CREATE OR REPLACE FUNCTION broj_poslovnica_grad(f_grad lokacije.grad%TYPE) RETURN NUMBER 
IS
temp_broj NUMBER:=0;
BEGIN
SELECT Count(p.poslovnica_id)
INTO temp_broj
FROM poslovnice p, lokacije l
WHERE l.grad=f_grad AND p.location_id = l.location_id;
RETURN temp_broj;
END broj_poslovnica_grad;
/

-- 3. vraca ukupan trosak na zaposlene, ne ukljucujuci vlasnika glavnog sefa
CREATE OR REPLACE FUNCTION ukupne_plate RETURN NUMBER 
IS
temp_suma NUMBER:=0;
BEGIN
  SELECT Sum(salary)
  INTO temp_suma
  FROM zaposleni
  WHERE manager_id IS NOT NULL;
  RETURN temp_suma;
END ukupne_plate;
/

-- 4. vraca ukupan trosak na zaposlene u jednoj poslovnice, ne ukljucujuci vlasnika poslovnice
CREATE OR REPLACE FUNCTION ukupne_plate_poslovnica(f_poslovnica poslovnice.naziv_poslovnice%TYPE) RETURN NUMBER 
IS
temp_suma NUMBER:=0;
BEGIN
  SELECT Sum(zp.salary)
  INTO temp_suma
  FROM zaposleni zp, poslovnice p, odjeli o
  WHERE zp.odjel_id = o.odjel_id AND p.poslovnica_id = o.poslovnica_id AND p.naziv_poslovnice = f_poslovnica
  AND  p.manager_poslovnice != zp.zaposleni_id;
  RETURN temp_suma;
END ukupne_plate_poslovnica;
/

-- 5. ukupan broj listica za klijenta tj. njegov racun
CREATE OR REPLACE FUNCTION broj_listica (racun_trazeni racuni.racun_id%TYPE) RETURN NUMBER 
IS
temp_ukupno NUMBER:=0;
BEGIN
  SELECT Count(listic_id)
  INTO temp_ukupno
  FROM listici 
  WHERE racun_id = racun_trazeni;
  RETURN temp_ukupno;
END broj_listica;
/

-- 6. koliko neki odjel ima zaposlenih, da se time provjerava da li ima visak radne snage
CREATE OR REPLACE FUNCTION broj_zaposlenih_u_odjelu (p_odjel odjeli.naziv_odjela%TYPE) RETURN CHAR 
IS
temp_broj NUMBER:=0;
BEGIN
  SELECT Count(z.zaposleni_id)
  INTO temp_broj
  FROM zaposleni z, odjeli o
  WHERE z.odjel_id = o.odjel_id AND o.naziv_odjela = p_odjel;
  RETURN 'UKUPNO ZAPOSLENIH: ' || To_Char(temp_broj);
END broj_zaposlenih_u_odjelu;
/

-- 7. ako poslovnica ima fond < 5000 onda ona ne radi kako treba
CREATE OR REPLACE FUNCTION funkcionalnost_poslovnice (n_poslovnice poslovnice.naziv_poslovnice%TYPE) RETURN CHAR 
IS
temp_broj NUMBER:=0;
BEGIN
  SELECT stanje_poslovnice
  INTO temp_broj
  FROM poslovnice
  WHERE naziv_poslovnice = n_poslovnice;
  IF (temp_broj < 5000) THEN
  RETURN 'Poslovnica ne radi kako treba!';
  ELSE
  RETURN 'Poslovnica radi kako treba, te njen prihod trenutni je: ' || To_Char(temp_broj);
  END IF;
END funkcionalnost_poslovnice;
/

-- 8. vraca ime covjeka koji ima najvise listica
CREATE OR REPLACE FUNCTION covjek_kes_max RETURN varCHAR2 
IS
ime_covjeka VARCHAR2(32767):='';
broj NUMBER :=0;
BEGIN

SELECT k.first_name || ' ' || k.last_name AS Ime_Prezime, k1.brojac
INTO ime_covjeka, broj
FROM racuni r, klijenti k, ( SELECT racun_id, Count(listic_id) AS brojac
                                                     FROM listici
                                                     GROUP BY racun_id 
                                                     ORDER BY Count(listic_id) DESC 
                                                   ) k1
WHERE r.klijent_id = k.klijent_id AND r.racun_id = k1.racun_id
AND ROWNUM <= 1;

IF(broj = 0) THEN 
RETURN 'Nema nijednog takvog';
ELSE 
RETURN 'Covjek koji je najvise listica odigrao: ' || To_Char(ime_covjeka) || ' a taj broj listica je: ' || To_Char(broj);
END IF;
END covjek_kes_max;
/

-- 9. vraca broj zaposlenih koji rade posao poslat kao parametar
CREATE OR REPLACE FUNCTION broj_zaposlenih_posao (opis_poslica zaposleni.opis_posla%TYPE) RETURN NUMBER 
IS
temp_broj NUMBER:=0;
BEGIN
  SELECT Count(zaposleni_id)
  INTO temp_broj
  FROM zaposleni
  WHERE opis_posla = opis_poslica;
  RETURN temp_broj;
END broj_zaposlenih_posao;
/


-- 10. funkcija koja vraca broj listica koji su uplaceni danas
CREATE OR REPLACE FUNCTION broj_listica_danas RETURN NUMBER 
IS
temp_broj NUMBER:=0;
BEGIN
  SELECT Count(listic_id)
  INTO temp_broj
  FROM listici
  WHERE datum_uplate = SYSDATE;
  RETURN temp_broj;
END broj_listica_danas;
/

-- 10 procedura

-- 1. dodavanje racuna za klijente

CREATE OR REPLACE PROCEDURE provjera_dodavanje_racuna(stanje_klijenta1 racuni.stanje_klijenta%type, klijent racuni.klijent_id%type) IS
BEGIN
  IF (stanje_klijenta1 <=0) THEN
  Raise_Application_Error(-55113, 'Klijent ne moze imati negativno stanje na racunu');
  END IF;

  INSERT INTO racuni VALUES(sekvenca_racuni.NEXTVAL, stanje_klijenta1, klijent);
END;
/

-- 2. procedura koja dodaje komentare/statistiku/stagod iskljucivo samo za tip opklade broj 2!
CREATE OR REPLACE PROCEDURE dodaj_komentar(opkl opklade.opklada_id%TYPE, komentar statistikainfo_opklada.informacija%TYPE) IS
nadjen NUMBER:=0;
BEGIN
    SELECT tip_opklade
    INTO nadjen
    FROM opklade
    WHERE opklada_id = opkl;

    IF(nadjen = 1) THEN
    Raise_Application_Error(-54113, 'Opklada tipa 1 ne moze imati komentar!');
    END IF;

    INSERT INTO statistikainfo_opklada VALUES(opkl, komentar);

END;
/

-- 3. vraca podatke zaposlene osobe za njihov id
CREATE OR REPLACE PROCEDURE daj_podatke_zaposleni ( zap_id zaposleni.zaposleni_id%TYPE, zap_ime IN OUT zaposleni.first_name%TYPE, zap_prezime IN OUT zaposleni.last_name%TYPE, zap_plata IN OUT zaposleni.salary%TYPE) IS
BEGIN
  SELECT first_name, last_name, salary
  INTO zap_ime, zap_prezime, zap_plata
  FROM zaposleni
  WHERE zaposleni_id = zap_id;
END;
/

-- 4. vraca podatke u vezi klijenta za njihov racun id
CREATE OR REPLACE PROCEDURE daj_podatke_klijenti ( zap_id racuni.racun_id%TYPE, zap_ime IN OUT klijenti.first_name%TYPE, zap_prezime IN OUT klijenti.last_name%TYPE) IS
temp NUMBER := 0;
BEGIN
  SELECT klijent_id
  INTO temp
  FROM racuni
  WHERE racun_id = zap_id;

  SELECT first_name, last_name
  INTO zap_ime, zap_prezime
  FROM klijenti
  WHERE klijent_id = temp;
END;
/

-- 5. brisanje opklade 
CREATE OR REPLACE PROCEDURE brisi_opkladu ( opklada opklade.opklada_id%TYPE) IS
BEGIN
  DELETE FROM opklade
  WHERE opklada_id = opklada;
END;
/

-- 6. azuriranje poslovnice
CREATE OR REPLACE PROCEDURE refresh_stanje_poslovnice(p_naziv poslovnice.naziv_poslovnice%TYPE, p_novo_stanje poslovnice.stanje_poslovnice%TYPE) IS 
BEGIN
   UPDATE poslovnice
   SET stanje_poslovnice = p_novo_stanje
   WHERE naziv_poslovnice = p_naziv;
END;
/


-- 7. azuziranje stanja racuna klijenata
CREATE OR REPLACE PROCEDURE refresh_stanje_klijenta(p_naziv racuni.racun_id%TYPE, p_novo_stanje racuni.stanje_klijenta%TYPE) IS 
BEGIN
   UPDATE racuni
   SET stanje_klijenta = p_novo_stanje
   WHERE racun_id = p_naziv;
END;
/

-- 8 uplata listica
CREATE OR REPLACE PROCEDURE uplata_listica(idR listici.racun_id%TYPE, upL listici.uplaceno%TYPE, dobL listici.dobitak%TYPE, posl listici.poslovnica_id%type) IS  
temp NUMBER := 0;
BEGIN

   SELECT stanje_klijenta INTO temp FROM racuni WHERE racun_id = idR;
   IF(temp < upL) THEN
   Raise_Application_Error(-541132322, 'Korisnik nema dovoljno para!');
   END IF;  
   UPDATE racuni 
   SET stanje_klijenta = stanje_klijenta - upL
   WHERE racun_id = idR;

   INSERT INTO listici VALUES(sekvenca_listici.NEXTVAL, idR, upL, dobL, 'NE','NE', posl, SYSDATE, 'NE');
END;
/

-- 9 isplata listica
CREATE OR REPLACE PROCEDURE isplata_listica(idR racuni.racun_id%TYPE, idL listici.listic_id%TYPE) IS  
temp NUMBER := 0;
temp2 NUMBER := 0;
poruk CHAR(2);
BEGIN
   SELECT isplaceno INTO poruk FROM listici WHERE listic_id = idL;
   IF(poruk = 'DA') THEN
   Raise_Application_Error(-54121322, 'Vec isplacen listic!!');
   END IF;
   SELECT stanje_poslovnice INTO temp FROM poslovnice WHERE poslovnica_id = (SELECT poslovnica_id FROM listici WHERE listic_id = idL);
   SELECT dobitak INTO temp2 FROM listici WHERE listic_id = idL;

   IF(temp < temp2) THEN
   Raise_Application_Error(-54121322, 'Poslovnica nema dovoljno para!');
   END IF;  
   UPDATE poslovnice
   SET stanje_poslovnice = stanje_poslovnice - temp2
   WHERE poslovnica_id = (SELECT poslovnica_id FROM listici WHERE listic_id = idL);

   UPDATE listici 
   SET dobitan = 'DA' 
   WHERE listic_id = idL;
   UPDATE listici 
   SET isplaceno = 'DA' 
   WHERE listic_id = idL;
END;
/

-- 10 azuriranje dobitnosti listica
CREATE OR REPLACE PROCEDURE azuziranje_dobitnosti_listica(listic listici.listic_id%TYPE) IS 
BEGIN
   UPDATE listici
   SET dobitan = 'DA'
   WHERE listic_id = listic;
END;
/
                    

-- 10 triggera

-- 1. provjerava da li je plata pozitivna (moze biti 0)
CREATE OR REPLACE TRIGGER Zaposleni_salary_trigg
BEFORE INSERT OR UPDATE ON zaposleni
FOR EACH ROW
BEGIN
IF (:new.salary < 0) THEN
Raise_Application_Error(-34567, 'Plata ne moze biti negativna!');
END IF;
END;
/

-- 2. provjerava da li je stanje poslovnice < 0 (moze biti 0)
CREATE OR REPLACE TRIGGER Poslovnice_sposlovnice_trigg
BEFORE INSERT OR UPDATE ON poslovnice
FOR EACH ROW
BEGIN
IF (:new.stanje_poslovnice < 0) THEN
Raise_Application_Error(-345777, 'Stanje poslovnice ne moze biti negativno!');
END IF;
END;
/

-- 3. ne dozvoljava brisanje lokacija 
CREATE OR REPLACE TRIGGER lokacije_brisanje_trigg
BEFORE DELETE ON lokacije
FOR EACH ROW
BEGIN
Raise_Application_Error(-33340, 'Ne mozete obrisati stavku iz ove tabele');
END;
/

-- 4. ne dozvoljava brisanje drzava 
CREATE OR REPLACE TRIGGER zemlje_brisanje_trigg
BEFORE DELETE ON zemlje
FOR EACH ROW
BEGIN
Raise_Application_Error(-33341, 'Ne mozete obrisati stavku iz ove tabele');
END;
/

-- 5. ne dozvoljava brisanje regija
CREATE OR REPLACE TRIGGER regije_brisanje_trigg
BEFORE DELETE ON regije
FOR EACH ROW
BEGIN
Raise_Application_Error(-33342, 'Ne mozete obrisati stavku iz ove tabele');
END;
/

-- 6. nema rada sa listicima kad ne treba!

CREATE OR REPLACE TRIGGER security_listici
BEFORE INSERT OR UPDATE OR DELETE ON listici
BEGIN
IF (TO_CHAR (sysdate,'DY') IN ('SAT','SUN')) OR (TO_CHAR (sysdate, 'HH24') NOT BETWEEN '08' AND '18') THEN
IF DELETING THEN 
RAISE_APPLICATION_ERROR (-20502, 'Brisanje je dozvoljeno u toku radnih sati.');
ELSIF INSERTING THEN RAISE_APPLICATION_ERROR (-20500, 'Insert. slogova je dozvoljen u toku radnih sati.');
ELSIF UPDATING ('SAL') THEN RAISE_APPLICATION_ERROR (-20503, 'Ažuri. slogova je dozvoljeno u toku ranih sati.');
ELSE RAISE_APPLICATION_ERROR (-20504, 'Ažuriranje slogova nije dozvoljeno.');
END IF;
END IF;
END;
/

-- 7. nema brisanja listica koji nisu isplaceni, a dobitni su
CREATE OR REPLACE TRIGGER listici_isplaceni_DANE
BEFORE DELETE ON listici
FOR EACH ROW
BEGIN
IF (:old.dobitan = 'DA' AND :old.isplaceno = 'NE' ) THEN
Raise_Application_Error(-34597, 'Ne smijete brisati ovaj listic, nije isplacen!');
END IF;
END;
/


-- 8. nema updateovanja opklada od strane klijenata
CREATE OR REPLACE TRIGGER KO_update_trigg
BEFORE UPDATE ON korisnicke_opklade
FOR EACH ROW
BEGIN
Raise_Application_Error(-333424, 'Ne mozete updateovati vec postojece opklade!');
END;
/

-- 9. dodavanje poreza svaki put kad se dodaje novi listic 
CREATE OR REPLACE TRIGGER listici_racunanje_pdv
BEFORE INSERT ON listici
FOR EACH ROW
DECLARE 
pp zemlje.porez%TYPE;
BEGIN
  SELECT z.porez
  INTO pp
  FROM lokacije l, poslovnice p, zemlje z
  WHERE p.location_id = l.location_id AND z.country_id = l.country_id
  AND p.poslovnica_id = :new.poslovnica_id; 
 :new.uplaceno := :new.uplaceno + :new.uplaceno * pp;

END;
/

-- 10. ne moze se izbrisati poslovnica ako ima uposlenih u njoj
CREATE OR REPLACE TRIGGER poslovnice_brisanjeP
BEFORE DELETE ON poslovnice
FOR EACH ROW
DECLARE 
temp NUMBER := 0;
BEGIN
  SELECT Count(z.zaposleni_id)
  INTO temp
  FROM zaposleni z, odjeli o, poslovnice p
  WHERE z.odjel_id = o.odjel_id AND p.poslovnica_id = o.odjel_id
  AND p.poslovnica_id = :old.poslovnica_id;

  IF(temp != 0) THEN 
  Raise_Application_Error(-1337, 'Ne mozete brisati poslovnice, kad ima uspolenih!!');
  END IF;
END;
/

-- PL/SQL SKRIPTA
-- Skripta sluzi za automatizovanje izvjestaja, odnosno slanje izvjestaja svake sedmice svakog petka
-- pomocu skripte poslovnice mogu dodavati sedmicne izvjestaje o poslovnici za tu sedmicu
-- i nadredene poslovnice mogu imati uvid o svojim poslovnicama iz hijerarhije, drugi dio skripte 

CREATE SEQUENCE sekvenca_izvjestaj_poslovnica;

CREATE TABLE izvjestaj_poslovnica (izvjestaj_id INTEGER,
                                   Poslovnica_id INTEGER,
                                   naziv_poslovnice CHAR(255),
                                   Poslovnica_Gid INTEGER,
                                   Poslovnica_adresa VARCHAR2(70) NOT NULL,
                                   Poslovnica_stanje NUMBER,
                                   Datum_izvjestaja DATE,
                                   desioSeIzvjestaj NUMBER,
                                   CONSTRAINT izvjesta_posl_id_pk PRIMARY KEY (izvjestaj_id),
                                   CONSTRAINT izvjesta_desiose_check CHECK (desioSeIzvjestaj IN (0,1))
                                  );


ALTER TABLE izvjestaj_poslovnica
ADD CONSTRAINT IP_poslovnica_id_fK
FOREIGN KEY(Poslovnica_id) REFERENCES poslovnice (poslovnica_id);


CREATE OR REPLACE FUNCTION stanje_posla (f_id poslovnice.poslovnica_id%TYPE) RETURN NUMBER 
IS
temp_stanje NUMBER:=0;
BEGIN 
SELECT stanje_poslovnice
INTO temp_stanje
FROM poslovnice 
WHERE poslovnica_id = f_id;
RETURN temp_stanje;
END;
/


CREATE OR REPLACE FUNCTION daj_adresu(f_id poslovnice.poslovnica_id%TYPE) RETURN CHAR  
IS 
temp_ad lokacije.adresa%TYPE;
BEGIN 
SELECT l.adresa
INTO temp_ad
FROM lokacije l, poslovnice p
WHERE p.poslovnica_id = f_id AND l.location_id = p.location_id;
RETURN temp_ad;
END;
/

CREATE OR REPLACE FUNCTION daj_glavnu_p(f_id poslovnice.poslovnica_id%TYPE) RETURN NUMBER IS 
temp_ad NUMBER := 0;
BEGIN 
SELECT poslovnica_gid
INTO temp_ad
FROM poslovnice
WHERE poslovnica_id = f_id;
RETURN temp_ad;
END;
/

CREATE OR REPLACE PROCEDURE uradi_izvjestaj(idP poslovnice.poslovnica_id%TYPE)IS
naziv izvjestaj_poslovnica.naziv_poslovnice%TYPE;
BEGIN
--  IF (to_char(to_date(SYSDATE,'dd/mm/yyyy'), 'Dy') != 'Fri') THEN
--   Raise_Application_Error(-1233, 'Pogresno vrijeme slanja!');
--  ELSE 
    SELECT naziv_poslovnice INTO naziv FROM poslovnice WHERE poslovnica_id = idP;
    INSERT INTO izvjestaj_poslovnica VALUES (sekvenca_izvjestaj_poslovnica.NEXTVAL, idP, naziv, daj_glavnu_p(idP), daj_adresu(idP),  stanje_posla(idP), SYSDATE, 0);
-- END IF;
END;
/

-- napravit cemo dodatnu proceduru da neka poslovnica moze vidjeti  kako poslovnice ispod rade u toku prosle sedmice
-- za tu sedmicu, odnosno ako se unese id neke poslovnice 

CREATE OR REPLACE FUNCTION broj_poslovnica(giD poslovnice.poslovnica_gid%TYPE) RETURN NUMBER IS
temp_broj NUMBER:=0;
BEGIN
SELECT Count(p.poslovnica_id)
INTO temp_broj
FROM izvjestaj_poslovnica p WHERE poslovnica_gid = giD;
IF temp_broj=0 THEN
Raise_Application_Error(-43810, 'Nema poslovnica!');
END IF;
RETURN temp_broj;
END;
/


CREATE OR REPLACE PROCEDURE izvjestajPoslovnica (idP poslovnice.poslovnica_gid%TYPE)IS
temp1 izvjestaj_poslovnica.naziv_poslovnice%TYPE;
temp2 izvjestaj_poslovnica.poslovnica_adresa%TYPE;
temp3 izvjestaj_poslovnica.poslovnica_Stanje%TYPE;
temp4 izvjestaj_poslovnica.izvjestaj_id%TYPE;
BEGIN
  FOR i IN 1..broj_poslovnica(idP) LOOP 
      SELECT naziv_poslovnice, poslovnica_adresa, poslovnica_stanje, izvjestaj_id
      INTO temp1, temp2, temp3, temp4
      FROM izvjestaj_poslovnica
      WHERE poslovnica_gid = idP AND desioseizvjestaj = 0 AND ROWNUM <= 1
      AND SYSDATE - datum_izvjestaja <= 6;
      dbms_output.put_line(To_Char(i) || '. Naziv poslovnice: ' || SubStr(temp1,0,20) || ' Adresa: ' || To_Char(temp2) || ' Stanje: ' || To_Char(temp3));
      UPDATE izvjestaj_poslovnica
      SET desioseizvjestaj = 1
      WHERE izvjestaj_id = temp4;
    END LOOP;

    UPDATE izvjestaj_poslovnica
    SET desioseizvjestaj = 0;
END;
/
