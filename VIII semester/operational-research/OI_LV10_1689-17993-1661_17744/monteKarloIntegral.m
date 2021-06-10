function [m,P,PMC,Greska] = monteKarloIntegral(fun, a, b, n)
% Radili:
% Masovic Haris - 1689/17993
% Muminovic Amir - 1661/17744

% fun se salje sa parametrom x
fun = @(x)eval(fun);
% trazimo najvecu vrijednost na intervalu [a,b]
x = a : 0.1 : b; 
interval = fun(x);
maxValue = max(interval);

% generisanje koordinata
xKoordinate = (b-a) .* rand(n,1) + a; 
yKoordinate = maxValue .* rand(n,1); 

% trazimo tacke ispod funkcije tj. broj
brojTacakaIspodFunkcije = 0;
for i = 1 : n
    x = xKoordinate(i);

    if yKoordinate(i) < fun(x)
        brojTacakaIspodFunkcije = brojTacakaIspodFunkcije + 1;
    end
end

% racunanje povrsine, greske, broj tacaka i vracanje nazad rezultata
P = integral(fun,a,b);
N = n;
PMC = (brojTacakaIspodFunkcije * (maxValue * (b-a))) / N;
Greska = (abs(P-PMC)/P) * 100;
m = brojTacakaIspodFunkcije;

end 

    