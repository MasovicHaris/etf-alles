--1    Prikazati sva pravna lica, s kojima kompanija ima ugovor sklopljen nakon 2016. godine.
SELECT* FROM pravna_lica p
WHERE p.datumPotpisivanja>'31-DEC-2016'
--2     . Napisati upit kojim ce se prikazati popusti smanjeni za 5% , za one proizvode koji imaju popust veci od 20%.
SELECT pr.naziv, po.procenatPopusta "Originalni popust", po.procenatPopusta-5 "Reducirani popust" FROM proizvod pr, popust po
WHERE pr.idProizvoda=po.idProizvoda AND po.procenatPopusta>20;
--3       Prikazati kompaniju, te vrijeme koje je proslo od potpisivanja ugovora saradnje u danima, mjesecima i godinama.
SELECT Trunc((SYSDATE-p.datumPotpisivanja)/365) "Vrijeme u godinama", Trunc(Months_Between(SYSDATE,p.datumPotpisivanja)) "Vrijeme u mjesecima", Trunc(SYSDATE-p.datumPotpisivanja) "Vrijeme u danima" FROM pravna_lica p;
--4       Napisati upit koji ce prikazati sve proizvode (naziv, cijenu) i popuste na iste proizvode. Potrebno je prikazati i proizvode koji nemaju popust.
SELECT pr.naziv, pr.cijena, po.procenatPopusta FROM proizvod pr, popust po
WHERE pr.idProizvoda=po.idProizvoda;
--5       Izlistati iz kojeg grada dolazi najvise pravnih lica s kojima kompanija suradjuje
SELECT * FROM (
SELECT pl.sjediste "Grad", count(pl.sjediste) "Broj ponavljanja" FROM pravna_lica pl
GROUP BY pl.sjediste
ORDER BY count(*) DESC)
WHERE ROWNUM = 1;
--6		Izlistati 10 kupovina sa kupcem i svim artiklima kupovine, sortiranih po iznosu kupovine
SELECT* FROM(
SELECT* FROM faktura f
ORDER BY f.iznosRacuna  DESC)
WHERE ROWNUM <=10;
--7		Izlistati nazive kategorije i naziv nadkategorije. U slucaju da kategorija nema nadkategoriju treba ispisati “Nema nadkategoriju”.
SELECT k.idKategorije, Nvl(To_Char(k.nadkategorija), 'Nema nadkategoriju') FROM kategorija k;
--8		Izlistati sve proizvode sa popustom koji imaju garanciju od 2 godine.
SELECT DISTINCT p.naziv, p.cijena, p.cijena*(1-po.aktuelniPopust/100) "Cijena s popustom" FROM proizvod p, popust po, kolicina k, garancija g
WHERE k.idFakture=g.idFakture AND p.idProizvoda=po.idProizvoda AND k.idProizvoda=p.idProizvoda AND (g.datumIsteka-SYSDATE)/365 > 2
ORDER BY 3 desc;
--9		Za svaki kontinent ispisati drzavu i sefa skladista sa najvecom platom.
SELECT Max(u.plata), d.naziv "Naziv drzave", k.nazivKontinenta "Naziv kontinenta" FROM kontinent k, drzava d, uposlenici u, skladista s
WHERE u.idUposlenika=odgovornaOsobaId AND d.naziv=s.nazivDrzave AND d.nazivKontinenta=k.nazivKontinenta
GROUP BY d.naziv, k.nazivKontinenta;
--10 Prikazati broj svih prodatih proizvoda u skladistima jedne drzave, te ukupni prihod ostvaren prodajom njih u prvoj polovini 2018.godine.

SELECT DISTINCT d.naziv, s.naziv "Naziv skladista", count(p.idProizvoda) "Broj prodatih", Sum(p.cijena) "Ostvareni prihod" FROM drzava d, skladista s, proizvod p, kolicina k, faktura f
WHERE s.nazivDrzave=d.naziv AND k.idFakture = f.idFakture AND k.idProizvoda=p.idProizvoda AND f.datumProdaje BETWEEN '30-JUN-2018' AND '1-JAN-2019'
GROUP BY d.naziv, s.naziv; 

