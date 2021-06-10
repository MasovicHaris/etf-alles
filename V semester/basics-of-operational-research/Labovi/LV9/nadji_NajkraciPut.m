function [rjesenje] = nadji_NajkraciPut(veze,pocetni)
    %Postavka za dalje rjesavanje
    rjesenje = [transpose([1:size(veze,1)]) zeros(size(veze,1),2)]; %Opci izgled rjesenja
    rjesenje(pocetni,2:3)= [0 pocetni];
    
    %Nadji sljedeci cvor
    kandidati = ones(1,size(veze,2))*Inf;
    origin = zeros(1,size(veze,2));
    brojElemenata=1;
    trenutni = pocetni;
    kandidati(trenutni) = 0;
    
    while size(veze,1)~=brojElemenata
        %Neki pokusaj necega
        povecanje = rjesenje(trenutni,2);
        
        for i=1:size(veze,2)
            if (veze(trenutni,i)>0 & (veze(trenutni,i)+povecanje)<kandidati(i))
               kandidati(i) = veze(trenutni,i)+povecanje;
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
        rjesenje(index,2:3)= [min origin(index)];
        trenutni = index;
        brojElemenata = brojElemenata + 1;
    end
end

