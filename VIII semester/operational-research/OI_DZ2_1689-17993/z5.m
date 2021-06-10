function [V] = z5(N)
a = 24.9;
b = 28.6;
c = 17.2;
zadani_l = 0.23;
n = 0;

brojRavni = ceil(b/zadani_l);

for i = 1 : N
    x = -1*a + (2*a).* rand(1,1);
    y = -1*b + (2*b).* rand(1,1);
    z = -1*c + (2*c).* rand(1,1);
    temp = x^2/a^2 + y^2/b^2 + z^2/c^2;
    % povecati n ukoliko se nalazi na definisanim 
    % granicama iz postavke i unutar elipsoida
    if temp <= 1
        for k = -brojRavni : brojRavni
            temp2 = x + y + z + 2 * k * zadani_l * sqrt(3);
            temp3 = x + y + z + (2 * k + 1) * zadani_l * sqrt(3);
            
            if temp2 < 0 && temp3 > 0
                n = n+1;
            end
        end
    end
end

V = (n/N)*8*a*b*c;
end