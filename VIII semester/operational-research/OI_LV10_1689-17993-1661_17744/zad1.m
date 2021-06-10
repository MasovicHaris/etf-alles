% Radili:
% Masovic Haris - 1689/17993
% Muminovic Amir - 1661/17744

figure
state = 0;

% normalna raspodjela, mean 5, devijacija 1
randn('state', state);
r = 5+1.*randn(1000);
subplot(1,3,1); 
histogram(r);
title('a) Normalna raspodjela');
najcesciUzorakA = mode(mode(r)) 

% uniformna raspodjela od 0 do 10
rand('state', state);
r = 10.*rand(1000);
subplot(1,3,2);
histogram(r);
title('b) Uniformna raspodjela');
najcesciUzorakB = mode(mode(r))

% poisionova srednja vrijednost 5
r = poissrnd(5, 1000, 1000);
subplot(1,3,3); 
histogram(r);
title('c) Poissonova raspodjela');
najcesciUzorakC = mode(mode(r))

% Da li su vrijednosti rezultata bile jednake pri ponovnom pozivu?
% - jesu
% Ako jesu, kako je to mogu?e, ako su brojevi slu?ajni?
% - zato sto rand generise brojeve na osnovu pre-defined algoritma
% - da bi se dobilo razlicito, treba reci npr srand(time(null))
% Prodiskutovati sli?nosti i razlike me?u rezultatima
% - klasicne raspodjele, onakve kakve i trebaju biti
