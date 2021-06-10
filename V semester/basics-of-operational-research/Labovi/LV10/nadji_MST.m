function [rjesenje, min_duzina] = nadji_MST(veze)
    %Radili Amir Muminovic 17744, Masovic Haris 17993
    %Nadji sljedeci cvor
    kandidati = ones(1,size(veze,2))*Inf;
    origin = zeros(1,size(veze,2));
    brojElemenata=1;
    trenutni = 1;
    kandidati(trenutni) = 0;
    
    while size(veze,1)~=brojElemenata
        %Neki pokusaj necega        
        for i=1:size(veze,2)
            if (veze(trenutni,i)>0 & (veze(trenutni,i))<kandidati(i))
               kandidati(i) = veze(trenutni,i);
               origin(i) = trenutni;
            end
        end
        
        
        %Nadji najblizu granu
        min = Inf;
        index = -1;
        for i=1:size(kandidati,2)
            if(kandidati(i) > 0 & kandidati(i) < min)
                min=kandidati(i);
                index=i;
            end
        end
        if (index == -1)
            disp('Nema elementa veceg od nule');
            return;
        end
        kandidati(index) = 0;
        rjesenje(brojElemenata,:)= [origin(index), index, min];
        brojElemenata = brojElemenata + 1;
        trenutni = index;
    end
    
    min_duzina = sum(rjesenje(:,3));
end
