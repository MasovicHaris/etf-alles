function [max, x, V] = kvadratno_programiranje(M, b, c)
% Radili:
% Masovic Haris - 1689/17993
% Muminovic Amir - 1661/17744

% simetrica kako god
M = (M + M') / 2;
% pocetni parametri
V = NaN;
% min 0
% max 1 
% nedefinisano 2
max = 2;
x = [];
matrica_velicina = size(M,1);

% hesian
H = 2 * M;

% determinante +
[positive_or_not, min_or_max] = ustanoviZnakMaxMin(H);

for i = 2 : matrica_velicina
    D = det(H(1:i,1:i));
    if D < 0 
        if positive_or_not ~= 1 || (i == 2 && positive_or_not == 1)
            return
        else
            positive_or_not = -1;
        end
    elseif D > 0
        if (min_or_max == 0 && positive_or_not ~= 1) || (min_or_max == 1 && positive_or_not ~= -1)
            return
        else
            positive_or_not = 1;
        end
    else 
        return
    end

max = min_or_max;   
end

% finalni rezultati
x = -inv(H) * b;
V = x' * M * x + b' * x + c;

if(max == 0)
    max = "min";
elseif(max == 1)
    max = "max";
else
    max = "nedefinisano";
end 

end 

function [znak, max_or_min] = ustanoviZnakMaxMin(H)
if H(1,1) < 0
    znak = -1;
elseif H(1,1) > 0
	znak = 1;
else 
    return
end

if znak == -1
    max_or_min = 1; 
else
    max_or_min = 0; 
end

end 