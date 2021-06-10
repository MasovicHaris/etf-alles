function [X, V] = rijesi_ranac(W, w, c, t) 
    X = zeros(1, length(w));
    V = 0;
    takenWeight = 0;
    while takenWeight < W
        jedinicnaCijena = c ./ w;
        [val, index] = max(jedinicnaCijena);
        maxElementsCanFit = floor((W - takenWeight) / (w(index)));
        X(index) = min(maxElementsCanFit, t(index));
        V = V + X(index) * c(index);
        takenWeight = takenWeight + X(index) * w(index);
        if (min(w) > W - takenWeight)
            break
        end
        c(index) = 0;
    end
end
