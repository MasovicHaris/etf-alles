function [V] = monteKarloLopte(x1,y1,x2,y2,R1,R2)
% Radili:
% Masovic Haris - 1689/17993
% Muminovic Amir - 1661/17744

% broj tacaka
n = 100000;

% trazimo najvecu i najmanju vrijednost na [a, b], [c, d], [e, f] segmentima
minAb = min(x1-R1, x2-R2);
maxAb = max(x1+R1, x2+R2);
minCd = min(y1-R1, y2-R2);
maxCd = max(y1+R1, y2+R2);
minEf = min(0-R1,0-R2); % treba gledati i negativan radijus
maxEf = max(R1,R2);

% generisanje koordinata
xKoordinate = (maxAb-minAb) .* rand(n,1) + minAb;
yKoordinate = (maxCd-minCd) .* rand(n,1) + minCd;
zKoordinate = (maxEf-minEf) .* rand(n,1) + minEf;

% trazimo broj tacaka u kugli 
brojTacakaUKugli = 0;

for i = 1:n
    % provjera formula za prvu i drugu kuglu
    if (xKoordinate(i)-x1)^2 + (yKoordinate(i)-y1)^2 + (zKoordinate(i)-0)^2 < R1^2      
        if (xKoordinate(i)-x2)^2 + (yKoordinate(i)-y2)^2 + (zKoordinate(i)-0)^2 < R2^2 
            brojTacakaUKugli = brojTacakaUKugli + 1;
        end
    end
end

% racunanje zapremine
V = (brojTacakaUKugli * ((maxAb-minAb) * (maxCd-minCd) * (maxEf-minEf))) / n;
end
