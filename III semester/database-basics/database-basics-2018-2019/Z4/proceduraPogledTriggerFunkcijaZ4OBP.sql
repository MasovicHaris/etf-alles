--PROCEDURE
CREATE OR REPLACE PROCEDURE brisi_fakture ( godina faktura.idFakture%TYPE) IS
BEGIN
  DELETE FROM faktura
  WHERE To_Number(To_Char(faktura.datumProdaje,'YYYY')) < godina-1;
END;


CREATE OR REPLACE PROCEDURE izlistaj_fakture ( kupac kupci.idKupca%TYPE, podaci_o_Fakturi IN OUT faktura.idFakture%TYPE) IS
BEGIN
  SELECT faktura.idFakture
  INTO podaci_o_fakturi
   FROM faktura
  WHERE faktura.idKupca=kupac;
END;
--POGLEDI
--4 (K5) Napisati upit koji ce izlistati sve proizvode cija je cijena veca od prosjecne cijene svih maksimalnih cijena proizvoda u odgovarajucim kategorijama.
CREATE OR REPLACE VIEW skupljiOdProsjeka (Naziv_proizvoda, Cijena_proizvoda) AS
SELECT p.naziv, p.cijena FROM proizvod p, kategorija k
WHERE p.idKategorije=k.idKategorije AND p.cijena> (SELECT Avg(p3.cijena)FROM proizvod p3 WHERE p3.cijena<>(SELECT Max(p2.cijena) FROM proizvod p2));

--2 (K2) Napisati upit koji ce prikazati nazive svih proizvoda koji su iste kategorije kao i proizvod koji ima najvecu ukupnu kolicinu u svim skladistima.
CREATE VIEW istaKategorijaKaoMaxKolicina (Naziv_proizvoda, ID_Kategorije_Proizvoda, Kolicina_u_skladistu) AS
SELECT p.naziv, p.idKategorije, Max(k.kolicinaRobe) FROM proizvod p, kolicina k
WHERE p.idProizvoda=k.idProizvoda
GROUP BY p.naziv, p.idKategorije;

--7 (K4) Napisati upit koji ce pronaci one isporuke koje ukljucuju fakturu kod koje barem jedna stavka fakture ima i popust i garanciju
CREATE VIEW faktureSPopustomIGarancijom (ID_Fakture, ID_Kupca, Datum_prodaje_robe, Iznos_racuna_fakture)  AS
SELECT DISTINCT f.idFakture, f.idKupca, f.datumProdaje, f.iznosRacuna FROM faktura f, popust p, garancija g, kolicina k
WHERE f.idFakture=g.idFakture AND p.idProizvoda = k.idProizvoda AND p.aktuelniPopust!=0 AND (SYSDATE-g.datumIsteka)<0;


--TRIGGERI
CREATE OR REPLACE TRIGGER uposlenici_plata
BEFORE INSERT OR UPDATE ON uposlenici
FOR EACH ROW
BEGIN
IF (:new.plata < 0) THEN
Raise_Application_Error(-123, 'Plata uposlenog mora biti pozitivna!');
END IF;
END;

CREATE OR REPLACE TRIGGER id_fiz_l_trig
BEFORE UPDATE ON fizicka_lica
FOR EACH ROW
BEGIN
Raise_Application_Error(-234, 'Zabranjeno mijenjati identifikacione brojeve kupaca!');
END;

CREATE OR REPLACE TRIGGER unos_uposl_trig
AFTER INSERT
   ON uposlenici
   FOR EACH ROW

DECLARE
   username varchar2(10);

BEGIN

   -- Nalazi osobu koja radi INSERT
   SELECT user INTO username
   FROM dual;

   insert into uposlenici (iduposlenika, plata, brojugovora, brojracuna, idodjela)
   VALUES
   ( username,
     :new.plata,
     :new.brojugovora,
     :new.brojracuna,
     :new.idOdjela
     );

END;


--FUNKCIJA
CREATE OR REPLACE FUNCTION preracunajCijenu(kategorija_id kategorija.idKategorije%TYPE, promjena_procenat NUMBER) RETURN VARCHAR2
IS
cijenaProizvoda NUMBER :=0;
BEGIN
   SELECT proizvod.cijena INTO cijenaProizvoda FROM proizvod;
   UPDATE proizvod
   SET cijena = cijenaProizvoda*(1+promjena_procenat)/100
   WHERE idKategorije=kategorija_id;
   RETURN 'Uspjesno azurirane cijene za ' || promjena_procenat || ' posto';
 END preracunajCijenu;

