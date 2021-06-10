function [ST, ibasic, x, Z] = rijesiSimpleks(ST, ibasic)
A = ST(1 : size(ST, 1) - 1, 2 : end);
b = ST(1 : size(ST, 1) - 1, 1);
c = ST(size(ST, 1), 2 : end);
Z = ST(size(ST, 1), 1);
[maxC, column] = max(c);
while maxC > 0
    t = transpose(b);
    minC = t(1, 1) / A(1, column);
    row = 1;
    for i = 2 : size(t, 2)
        t(1, i) = t(1, i) / A(i, column);
        if ((minC < 0) && (t(1, i) > 0)) || (t(1, i) < minC) && (t(1, i) > 0)
            minC = t(1, i);
            row = i;
        end
    end
    if minC < 0
        break
    end
    element = A(row, column);
    ibasic(row, 1) = column;
    b(row, 1) = b(row, 1) / element;
    A(row, :) = A(row, :) / element;
    for i = 1 : size(b, 1)
        if i == row
            continue
        end
        temporaryB = b(row, 1) * A(i, column);
        temporaryA = A(row, :) * A(i, column);
        b(i, 1) = b(i, 1) - temporaryB;
        A(i, :) = A(i, :) - temporaryA;
    end
    temporaryB = b(row, 1) * c(1, column);
    temporaryA = A(row, :) * c(1, column);
    Z = Z - temporaryB;
    c = c - temporaryA;
    [maxC, column] = max(c);
end
ST = [b A; Z c];
x = zeros(1, size(A, 2));
for i = 1 : size(ibasic, 1)
    x(ibasic(i, 1)) = b(i, 1);
end
Z = ST(size(ST, 1), 1);
Z = Z * (-1);