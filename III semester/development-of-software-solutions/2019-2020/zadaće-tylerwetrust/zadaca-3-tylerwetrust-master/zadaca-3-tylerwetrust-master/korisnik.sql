BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "korisnik" (
	"id"	INTEGER,
	"ime"	TEXT,
	"prezime"	TEXT,
	"email"	TEXT,
	"username"	TEXT,
	"password"	TEXT,
	"slika"	TEXT,
	PRIMARY KEY("id")
);
INSERT INTO "korisnik" VALUES (1,'Vedran','Ljubović','vljubovic@etf.unsa.ba','vedranlj','test',NULL);
INSERT INTO "korisnik" VALUES (2,'Amra','Delić','adelic@etf.unsa.ba','amrad','test',NULL);
INSERT INTO "korisnik" VALUES (3,'Tarik','Sijerčić','tsijercic@etf.unsa.ba','tariks','test',NULL);
INSERT INTO "korisnik" VALUES (4,'Rijad','Fejzić','rfejzic@etf.unsa.ba','rijadf','test',NULL);
COMMIT;
