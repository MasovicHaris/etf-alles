function [Z, X, status] = CLP_Gomory(goal, A, b, c, ogranicenje, predznak)

[ST, ibasic] = formirajSimpleksTabelu(A, b, c);

[ST, ibasic, X, Z] = rijesiSimpleks(ST, ibasic);

while 1
    fractions = X;
    for i = 1 : size(fractions, 2)
        if round(fractions(1, i)) - fractions(1, i) < 0.0000001
            fractions(1, i) = 0;
        end
    end
    fractions = fractions - fix(fractions);
    cut = fractions(1, 1);
    cutIndex = 1;
    for i = 1 : size(fractions, 2)
        if fractions(1, i) >= cut
            cut = fractions(1, i);
            cutIndex = i;
        end
    end
    if mod(cut, 1) == 0
    	if min(X) < 0
            status = 2;
        elseif min(ST(1 : size(ST, 1) - 1, 1)) == 0
            status = 1;
        else
            status = 0;
        end
        break;
    end
    for i = 1 : size(ibasic, 1)
        if ibasic(i, 1) ~= cutIndex
            continue
        end
        newRow = ST(i, :);
        newRow = (newRow - floor(newRow)) * (-1);
        newST = [ST(1 : size(ST, 1) - 1, :); newRow; ST(size(ST, 1), :)];
        newColumn = zeros(size(newST, 1), 1);
        newColumn(size(newColumn, 1) - 1, 1) = 1;
        ST = [newST newColumn];
        ibasic = [ibasic; size(ST, 2) - 1];
        [ST, ibasic, X, Z] = rijesiDualniSimpleks(ST, ibasic);
    end
end