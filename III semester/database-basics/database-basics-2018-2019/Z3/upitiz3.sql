--1 (K1) Napisati upit koji ce prikazati sve ugovore koji su zakljuceni poslije najstarije izdate garancije
SELECT pl.brUgovora FROM pravna_lica pl
WHERE pl.datumPotpisivanja > (SELECT Min(g.datumPocetka) FROM garancija g);
--2 (K2) Napisati upit koji ce prikazati nazive svih proizvoda koji su iste kategorije kao i proizvod koji ima najvecu ukupnu kolicinu u svim skladistima.
SELECT p.naziv, p.idKategorije, Max(k.kolicinaRobe) FROM proizvod p, kolicina k
WHERE p.idProizvoda=k.idProizvoda
GROUP BY p.naziv, p.idKategorije;
--3 (K4) Izlistati uposlenike koji su poceli raditi minimalno 6 mjeseci prije makar jednog uposlenika koji nije sef odjela u kojem taj uposlenik radi.
SELECT* FROM uposlenici u, uposlenici u2, odjel o, pravna_lica pl, pravna_lica pl2
WHERE u.idOdjela = o.idOdjela AND u.idUposlenika=pl.idLica AND u2.idUposlenika=pl2.idLica AND u.idOdjela = u2.idOdjela AND o.sefOdjela!=u2.idUposlenika AND Months_Between(pl.datumPotpisivanja, pl2.datumPotpisivanja)>6;
--4 (K5) Napisati upit koji ce izlistati sve proizvode cija je cijena veca od prosjecne cijene svih maksimalnih cijena proizvoda u odgovarajucim kategorijama.
SELECT p.naziv, p.cijena FROM proizvod p, kategorija k
WHERE p.idKategorije=k.idKategorije AND p.cijena> (SELECT Avg(p3.cijena)FROM proizvod p3 WHERE p3.cijena<>(SELECT Max(p2.cijena) FROM proizvod p2));
--5 (K5) Pronaci sve proizvodace sa barem jednim proizvodom, koji je u posljednjih 6 mjeseci prodavan po prosjecnoj cijeni (sa uracunatim popustom), koja je za barem 10% manja u odnosu na cijenu proizvoda bez popusta.
SELECT pl.naziv, Avg(p.cijena) FROM popust po, garancija g, faktura f, kolicina k, proizvod p, proizvodjaci pr, pravna_lica pl
WHERE p.idProizvoda=po.idProizvoda AND g.idFakture=f.idFakture AND Months_Between(f.datumProdaje, g.datumIsteka)<-6 AND po.procenatPopusta>10 AND pr.brUgovora=pl.brUgovora AND f.idFakture=k.idFakture AND k.idProizvoda=p.idProizvoda
GROUP BY pl.naziv;
--6 (K5) Napisati upit koji ce prikazati kurirske sluzbe koje su u prethodnih godinu dana izvrsile makar jednu isporuku fakture sa minimalno tri proizvoda na akciji u grad iz kojeg ne potje¡ce ta kurirska slu¡zba.
SELECT DISTINCT pl.naziv, pl.sjediste FROM kurirske_sluzbe ks, faktura f, kolicina k, pravna_lica pl, popust p
WHERE f.idFakture=k.idFakture AND ks.brUgovora=pl.brUgovora AND k.kolicinaRobe>3  AND Months_Between(SYSDATE, f.datumProdaje)<=12 AND pl.idLica!=f.idKupca AND p.idProizvoda=k.idProizvoda AND p.aktuelniPopust!=0;
--7 (K4) Napisati upit koji ce pronaci one isporuke koje ukljucuju fakturu kod koje barem jedna stavka fakture ima i popust i garanciju
SELECT DISTINCT f.idFakture, f.idKupca, f.datumProdaje, f.iznosRacuna FROM faktura f, popust p, garancija g, kolicina k
WHERE f.idFakture=g.idFakture AND p.idProizvoda = k.idProizvoda AND p.aktuelniPopust!=0 AND (SYSDATE-g.datumIsteka)<0;
--8 (K3) Napisati upit koji ´ce prikazati naziv proizvoda, kategoriju i nadkategoriju za proizvod koji trenutno nije na stanju u skladi¡stu ili su njegove koli¡cine manje od prosje¡cne koli¡cine tog proizvoda u svim skladi¡stima. U slu¡caju da ga nema na stanju treba ispisati “Nije dostupan”.
SELECT DISTINCT p.naziv, k.idKategorije, k.nadKategorija, Nvl(To_Char(ko.kolicinaRobe), 'Nije dostupan') "Kolicina proizvoda" FROM proizvod p, kategorija k, kolicina ko
WHERE p.idProizvoda=ko.idProizvoda AND ko.idFakture=k.idKategorije AND  ko.kolicinaRobe < (SELECT Avg(k2.kolicinaRobe) FROM kolicina k2) OR ko.kolicinaRobe=0;
--9 Napisati upit koji ce vratiti sve kupce koji su kupovali SAMO artikle sa popustom i uz svako od tih lica, treba da se nalazi njihova ukupna vrijednost tokom vremena (lifetime value), sto predstavlja koliko ukupno novca su potro¡sili u ovoj trgovini.
SELECT fl.ime || ' ' || fl.prezime "Naziv kupca", Sum(f.iznosRacuna) "Lifetime value" FROM fizicka_lica fl, kupci k, faktura f, kolicina ko, popust p
WHERE fl.idLica = f.idKupca AND f.idKupca=k.idKupca AND ko.idFakture=f.idFakture AND ko.idProizvoda=p.idProizvoda AND p.aktuelniPopust!=0
GROUP BY fl.ime || ' ' || fl.prezime
ORDER BY 2 DESC;
--10 Napisati upit koji ce vratiti ime i prezime kupca (“Kupac”) i ustedu koju je ostvario tokom svih svojih kupovina (“Usteda”) kupujuci proizvode na popustu.
SELECT fl.ime || ' ' || fl.prezime "Naziv kupca", Round(Sum ((f.iznosRacuna/(f.iznosRacuna-(p.procenatPopusta*0.01)))-f.iznosRacuna),3)*-1 "Usteda"  FROM fizicka_lica fl, kupci k, faktura f, kolicina ko, popust p
WHERE fl.idLica = f.idKupca AND f.idKupca=k.idKupca AND ko.idFakture = f.idFakture AND ko.idProizvoda=p.idProizvoda AND p.procenatPopusta IS NOT NULL
GROUP BY fl.ime || ' ' || fl.prezime
ORDER BY 2 DESC;