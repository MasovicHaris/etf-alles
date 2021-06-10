function [Z, X] = resursi(Q, F)
% Zadatak 7 - Masovic Haris
% Domaca zadaca 1 - 1689/17993

% Q predstavlja kolicinu resura koja se treba raspod
% F je vektor funkcija, pri cemu svaka funkcija govori koliko je dobit od 
% ulaganja x jedinica za i-ti subjekt
% kao rezultat vracamo Z optimalno i vektor x-ova koji govori koliko
% resursa treba dati pojedinacnim subjektima

zIteracije = zeros(1, Q + 1); % inicijaliziranje z na 1xQ+1 matricu nula
brojSubjekata = size(F, 2); % broj subjekata za raspodjelu resursa
% pamcenje za svakog subjekta kolicinu uzetog resursa
kolicineSubjekata = []; 

% uzorom na pseudo kod iz predavanja, vrtimo petlju po broju subjekata
for i = 1 : brojSubjekata
    % na osnovu vektora funkcija, uzima se funkcija i pravi se
    % anonimna funkcija u matlabu sa parametrom x za svakog subjekta
    string = strjoin(F(i));
    anonFunction = strcat('@(x)', string);
    cFunction = str2func(anonFunction); % funkcija koja prima x kao param
    for q = Q : -1 : 1
        % prolazimo dalje kroz sve resurse, i gledamo da nadjemo max efekat
        % za i subjekata i kolicinu resursa q
        for x = 1 : q
            value = cFunction(x);
            newValue = value + zIteracije(q - x + 1); % racunanje u
            % trazi se max z, i pamti se vrijednost z i kolicina x
            if newValue > zIteracije(q + 1)
                zIteracije(q + 1) = newValue;
                kolicineSubjekata(i, q + 1) = x;
            end
        end
    end
end
Z = zIteracije(Q + 1);
% uzimamo optimalno Z sa zadnje pozicije i nakon toga vrsimo preraspodjelu
% resursa, tako sto idemo od n do 1 sve dok Q ne postane 0
for i = brojSubjekata : -1 : 1
    if Q ~= 0        
        % dodjeljujemo x(i) resurs ka i-tom subjektu i skidamo sa Q
        X(i) = kolicineSubjekata(i, Q + 1);
        Q = Q - X(i);
    else 
        break;
    end
end
end