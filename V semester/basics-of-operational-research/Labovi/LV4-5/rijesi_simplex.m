function [X, Z] = rijesi_simplex(A, b, c)
    %%v=0;
    % Priprema za simplex
    simplex_tabela = [A eye(length(b)) b; -c zeros(1, length(b)) 0];
    baza = [size(A,2)+1:size(A,2)+length(b)];
    
    while (any(simplex_tabela(size(simplex_tabela,1),:) < 0))
        [minimum,I] = min(simplex_tabela(size(simplex_tabela,1),:));
        
        vodecaKolona = simplex_tabela(1:size(simplex_tabela,1)-1, I(1));
        
        if (all(vodecaKolona(1:length(vodecaKolona)-1)) <= 0) %Ako svi negativni, odmah izlazi iz programa
            X = Inf;
            Z = Inf;
            return;
        end 
        
        trenutniB = simplex_tabela(1:size(simplex_tabela,1)-1,size(simplex_tabela,2));
        tOvi = trenutniB ./ vodecaKolona;        
        for i = 1:length(tOvi)
            if (tOvi(i,1) < 0)
                tOvi(i,1) = Inf;
            end
        end
        
        [minimum, I1] = min(tOvi);
                
        baza(I1(1)) = I(1);
        pivot = simplex_tabela(I1(1), I(1));
        
        for i=1:size(simplex_tabela,2)
            simplex_tabela(I1(1),i) = simplex_tabela(I1(1),i) ./pivot;
        end
        %%simplex_tabela
        for i=1:size(simplex_tabela,1)
            if (i == I1(1))
                continue
            end
            pivot = simplex_tabela(i, I(1));
            for j=1:size(simplex_tabela,2)
                simplex_tabela (i,j) = simplex_tabela (i,j) - pivot .* simplex_tabela(I1(1),j);
            end
        end
    end
    
    % Postavljanje vanjskih parametara
    X = zeros(1, size(simplex_tabela,2) -1);
    for i = 1:length(baza)
        X(baza(i)) = simplex_tabela(i,size(simplex_tabela, 2));
    
    Z = simplex_tabela(size(simplex_tabela,1),size(simplex_tabela,2));
    end