function [R, matricaCijenaNova, izvoristaNova, odredistaNova] = sjeveroZapad(matricaCijena, izvorista, odredista)
[m,n] = size(matricaCijena);
R = zeros(m,n);
sumaIzvorista = sum(izvorista);
sumaOdredista = sum(odredista);
% balansiramo nas transport
if sumaIzvorista > sumaOdredista
    razlika = sumaIzvorista - sumaOdredista;
    odredista = [odredista razlika];
    matricaCijena = [matricaCijena zeros(m, 1)];
elseif sumaIzvorista < sumaOdredista
    razlika = sumaOdredista - sumaIzvorista;
    izvorista = [izvorista; razlika];
    matricaCijena = [matricaCijena; zeros(1, n)];
end

% vršimo algoritam sjevera i zapada sve dok vektori ne budu nulu tj njihova
% suma bude 0
[m,n] = size(matricaCijena);
i = 1;
j = 1;
eps = 1e-10;
while((sum(izvorista) ~= 0 | sum(odredista) ~= 0) & i <= m & j <= n)
    potreba = odredista(j);
    zaliha = izvorista(i, 1);
    min = potreba;
    if(zaliha < potreba) 
        min = zaliha;
    end
    izvorista(i) = izvorista(i, 1) - min;
    odredista(j) = odredista(j) - min;
    R(i, j) = min;
    if(odredista(j) == 0 & izvorista(i) == 0)
        j = j + 1;
        if(j <= n)
            R(i,j) = eps;
        end 
        i = i + 1;
    elseif(odredista(j) == 0)
        j = j + 1;
    else
        i = i + 1;
    end
end
    matricaCijenaNova = matricaCijena;
    izvoristaNova = izvorista;
    odredistaNova = odredista;
end 