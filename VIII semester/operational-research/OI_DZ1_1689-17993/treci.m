function [Z, x] = treci()
% Masovic Haris - Zadatak 3 - Domaca zadaca 1
% funkcija koja racuna 1225 redova, 9 kolona
% zadatak 3 sa zadace, pisano u 2017a, u slucaju nepoznatih poziva
 
% definisanje parametara iz postavke zadace
graniceV = [145 160 105 165 285 110 115 250 210];
ogranicenje = 1225;
brojPredmeta = 9;
 
% processing
% matrica koja pamtriz z(v, s)
matrica = zeros(ogranicenje, brojPredmeta);
% matrica koja pameti da li se za trenutni z(i,j) uzelo iz prethodne kolone
uzimanje = zeros(ogranicenje, brojPredmeta);
 
for i = 1 : 1 : ogranicenje
    for j = 1 : 1 : brojPredmeta
        granica = graniceV(1, j);
        if i >= granica
            if j == 1
                matrica(i, j) = graniceV(1, j);
                uzimanje(i, j) = 1;
            else 
                offset = 0;
                if i - granica == 0
                    offset = 1;
                end 
                prijasnja = granica + matrica(i - granica + offset , j - 1);
                
                if matrica(i, j - 1) > prijasnja
                    matrica(i, j) = matrica(i, j - 1);
                else
                    matrica(i, j) = prijasnja;
                    uzimanje(i, j) = 1;
                end 
            end
        else 
            % slucaj da nisu ispunjeni uslovi
            if i == 1 || j == 1
                matrica(i, j) = 0;
            else 
                matrica(i, j) = matrica(i, j - 1);
            end 
        end 
    end 
end 
 
% ispis u fajl, u istom direktoriju
dlmwrite('treci_tabela.txt', matrica, 'delimiter', '\t');
% formiranje izlaza, ispis optimalnog rjesenja
Z = matrica(ogranicenje, brojPredmeta);
x = zeros(1, brojPredmeta);
 
for i = brojPredmeta : -1 : 1
    if ogranicenje > 0        
        x(i) = uzimanje(ogranicenje, i);
        if x(i) == 1 
            ogranicenje = ogranicenje - graniceV(1, i);
        end 
    else 
        break;
    end
end
end 
