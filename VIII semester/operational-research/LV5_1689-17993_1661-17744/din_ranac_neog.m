function [X, V] = din_ranac_neog(W, w, c)
    z = zeros(1, W);
    wLength = size(w, 2);
    X = zeros(W, wLength);
    
    for v = 1 : W
        for i = 1 : wLength
            if v - w(1, i) < 1
                x = 0;
            else
                x = z(1, v - w(1, i));
            end
            
            u = c(1, i) + x;
            
            if (w(1, i) - v <= 0) 
                if (u - z(1, v) > 0)
                    X(v) = 0;
                    X(v, i) = 1;
                    z(1, v) = u;
                end
            end
        end
    end
    
    V = z(1, W);
    finalX = zeros(1, size(w, 2));
    
    while W > 0
        for i = 1 : size(X, 2)
            if X(W, i) == 1
                W = W - w(1, i);
                finalX(1, i) = finalX(1, i) + 1;
                break
            end
        end
    end
    X = finalX;
    