function[p, q, v] = igreLP(matrica)
% OI - LV6  
% Radili:
% Masovic Haris - 1689/17993
% Muminovic Amir - 1661/17744

% parametri
[m, ~] = size(matrica);
c = ones(1,m);
b = ones(m,1);

% ogranicenja
LB = zeros(1, m);
UB = Inf * ones(1, m);

% v i q
A = matrica;
[y] = linprog(-c, A, b, [],[], LB, UB);
v = 1/sum(y);
q = y .* v;

% finalno p
A = matrica';
[x] = linprog(c, -A, -b, [],[], LB, UB);
p = x .* v;
end 