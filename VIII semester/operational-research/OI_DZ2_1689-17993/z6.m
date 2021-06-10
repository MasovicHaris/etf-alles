function [] = z6(brojRedova)

intenzitetDolaska = 10;
intenzitetUsluzivanja = 6;

od11do13BrojNovihKorisnika = 30;
od13NoviKorisnici = 36;
sigma = 0.6;

% radno vrijeme u minutama, od 9 do 14
t = 5 * 60; 

% poisonova raspodjela po minut lagano
brojDolazakaTrenutnihKlijenata = poissrnd(intenzitetDolaska , 1, t);
ukupnoKlijanata = sum(brojDolazakaTrenutnihKlijenata) + od11do13BrojNovihKorisnika + od13NoviKorisnici;
vremenaDolazaka = zeros(1, ukupnoKlijanata);

trenutniTrenutak = 1;

for i = 1 : t
    for j = 1 : brojDolazakaTrenutnihKlijenata(i)
        vremenaDolazaka(trenutniTrenutak) = rand(1) + i - 1;
        trenutniTrenutak = trenutniTrenutak + 1;
    end
end

for i = 1 : od11do13BrojNovihKorisnika
    % od11do13BrojNovihKorisnika tj. novi korisnici ce doci
    % izmedju 120 i 140e minute, odnosno izmedju 11 i 13
    vrijemeDolaskaNovog = unifrnd(120,240);
    vremenaDolazaka(trenutniTrenutak) = vrijemeDolaskaNovog + rand(1);
    trenutniTrenutak = trenutniTrenutak + 1;
end

for i = 1 : od13NoviKorisnici 
    % od13NoviKorisnici tj. novi ce doci u 13
    vremenaDolazaka(trenutniTrenutak) = normrnd(240, sigma);
    trenutniTrenutak = trenutniTrenutak + 1;
end

vremenaDolazaka = sort(vremenaDolazaka);
vrijemePotrebnoZaUslugu = 1 ./ poissrnd(intenzitetUsluzivanja, 1, ukupnoKlijanata);
vrijemeOdlaskaKlijenta = zeros(1, ukupnoKlijanata);
vrijemeOdlaskaKlijenta(1) = vremenaDolazaka(1) + vrijemePotrebnoZaUslugu(1);

for i = 2 : ukupnoKlijanata
   vrijemeOdlaskaKlijenta(i) = vremenaDolazaka(i) + vrijemePotrebnoZaUslugu(i);
   if vremenaDolazaka(i) < vrijemeOdlaskaKlijenta(i-1)
        vrijemeOdlaskaKlijenta(i) = vrijemeOdlaskaKlijenta(i) + vrijemePotrebnoZaUslugu(i-1);
   end
end

% gledamo svakih 10 sekundi stanje
duzina = (t * 60) / 6;
indexiPo10Sekundi = 1 : duzina;

svakih10Sekundi = 1 : 0.1 : 301;
kolikoKorisnikaCekaURedovima = zeros(1, duzina);
brojSlobodnihSaltera = ones(1, duzina) .* brojRedova;

for i = indexiPo10Sekundi
    for j = 1 : ukupnoKlijanata
        if vremenaDolazaka(j) < svakih10Sekundi(i) && vrijemeOdlaskaKlijenta(j) > svakih10Sekundi(i)
            if brojSlobodnihSaltera(i) > 0
                brojSlobodnihSaltera(i) = brojSlobodnihSaltera(i) - 1;
            else
                kolikoKorisnikaCekaURedovima(i)= kolikoKorisnikaCekaURedovima(i) + 1;
            end
        end
    end
end

plot(indexiPo10Sekundi, kolikoKorisnikaCekaURedovima, 'r');
title('Broj klijenata koji ceka u definisanim redovima')
ylabel('klijent')
xlabel('s')

end