function [Z, X, status] = CLP_BB(goal, A, b, c, ogranicenje, predznak)
    % Radili:
    % Masovic Haris - 1689/17993
    % Muminovic Amir - 1661/17744
    
    if goal == "max"
        c = -c;
    end
    Aeq = [];
    Beq = [];
    Anew = [];
    Bnew = [];
    for i = 1 : size(A, 1)
        if ogranicenje == '='
            Aeq(i, :) = A(i, :);
            Beq(i, :) = b(i, :);
        elseif ogranicenje == '>='
            Anew(i, :) = -A(i, :);
            Bnew(i, :) = -b(i, :);
        else
            Anew(i, :) = A(i, :);
            Bnew(i, :) = b(i, :);
        end
    end
    % rjesavanje linearne relaksacije i bb
    lb = zeros(1, size(c, 2));
    ub = ones(1, size(c, 2)) * Inf;
    
    for i = 1 : size(predznak, 1)
        if(predznak(i, 1) == -1)
            lb(1, i) = -Inf;
            ub(1, i) = 0;
        end 
    end 
    
    [variables, solutions] = BB(c, Anew, Bnew, Aeq, Beq, lb, ub, [], []);

    % provjeravamo postoji li rješenje
    if size(solutions, 1) == 0
        status = 2;
        X = variables;
        Z = solutions;
        return
    end
    % pronalazimo optimum(e)
    min = [solutions(1, 1)];
    indexMin = [1];
	for i = 1:size(solutions, 1)
        if solutions(i, 1) < min(1, 1)
            min = solutions(i, 1);
            indexMin = i;
        elseif solutions(i, 1) == min(1, 1)
            min(size(min, 1) + 1, 1) = solutions(i, 1);
            indexMin(size(indexMin, 1) + 1, 1) = i;
        end
    end
	if size(min, 1) > 1
        status = 1;
    else
        status = 0;
    end
    
    X = transpose(variables(:, indexMin(1,1)));
    Z = solutions(indexMin(1,1), 1);
    if goal == "max"
        Z = -Z;
    end

function [V, S] = BB(c, Anew, Bnew, Aeq, Beq, lb, ub, variables, solutions)
	V = variables;
	S = solutions;
    [X, Z, status, ~] = linprog(c, Anew, Bnew, Aeq, Beq, lb, ub);
    
    % provjeravamo ima li problem rjesenje
    if status ~= 1
        return
    end
    % bb
    doubleX = [];
    for i = 1 : size(X, 1)
        if abs(round(X(i, 1)) - X(i, 1)) > 0.0000001
            doubleX(i, 1) = 1;
        else
            doubleX(i, 1) = 0;
        end
    end
    % nema necjelobrojnih promjenjivih
    if max(doubleX) == 0
        V(:, size(V, 2) + 1) = X;
        S(size(S, 1) + 1, :) = Z;
        return
    end
    
    for i = 1 : size(doubleX, 1)
        if doubleX(i, 1) == 1
            lbnew = lb;
            if round(X(i, 1)) ~= lb(1, i)
               lbnew(1, i) = round(X(i, 1));
               [V, S] = BB(c, Anew, Bnew, Aeq, Beq, lbnew, ub, V, S);
            end 
            ubnew = ub;
            if floor(X(i, 1)) ~= ub(1, i)
               ubnew(1, i) = floor(X(i, 1));
               [V, S] = BB(c, Anew, Bnew, Aeq, Beq, lb, ubnew, V, S);
            end 
        end
    end