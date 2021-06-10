function [X, V] = din_ranac_og(W, w, c, t)
    z = zeros(1, W);
    wLength = size(w, 2);
    X = zeros(W, wLength);
    
    i = 1;
    while (wLength - i >= 0)
        v = W;
        difference = v - w(1, i);
        
        while difference >= 0
            
            k = 1;
            roundedToFloor = floor(v/w(1, i));
            minVal = min(t(1, i), roundedToFloor );
            
            while minVal - k >= 0
                if 1 - v + w(1, i) * k > 0
                    x = 0;
                else
                    x = z(1, v - w(1, i) * k);
                end
                
                u = c(1, i) * k + x;
                if u - z(1, v) > 0
                    X(v) = 0;
                    X(v, i) = k;
                    z(1, v) = u;
                end
                
                k = k + 1;
            end
            
            v = v - 1;
            difference = v - w(1, i);
            
        end
        i = i + 1;
    end
    
    X = X(W, :);
    V = z(1, W);