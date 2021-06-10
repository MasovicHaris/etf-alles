function [finalna] = steppingStone(matricaCijena,R,jedinicna)
uslov = 1;
while (uslov == 1)
    % Prvo treba naci nulte elemente da vrtimo konture
    sviNulti = find(~jedinicna);
    matricaDova =zeros(size(jedinicna));
    for i=1:size(sviNulti,1)
        [red, kolona] = ind2sub(size(jedinicna),sviNulti(i));
        matricaDova(red,kolona) = nadjiCiklus(matricaCijena,red,kolona,jedinicna);
    end
    if (all(matricaDova(:)>=0))
        uslov = 0;
    else
        [~,index] = min(matricaDova(:));
        [red, kolona] = ind2sub(size(matricaDova),index);
        [~,ciklusVraceni] = nadjiCiklus(matricaCijena,red,kolona,jedinicna);
        [R,jedinicna] = urediMatricu(R,ciklusVraceni,red,kolona,jedinicna);
    end
end
    finalna = R;
end

% Pozivamo ovu funkciju prilikom transformacije samih elemenata tj. 
% +-+- itd
function [izlaznaMatrica,izlaznaJedinicna] = urediMatricu(R,element,red,kolona, jedinicna)
    pamtiVrijednost = Inf;
    index = Inf;
    izlaznaJedinicna = jedinicna;
    izlaznaMatrica = R;
    duzina=length(element);
for i=2:2:duzina
 if (R(element(i,1),element(i,2)) < pamtiVrijednost)
    pamtiVrijednost = R(element(i,1),element(i,2));
    index = i;
 end
end
    izlaznaMatrica(red,kolona) = pamtiVrijednost;
for i=2:duzina-1
    izlaznaMatrica(element(i,1),element(i,2))=izlaznaMatrica(element(i,1),element(i,2))+(-1)^(i-1) * pamtiVrijednost;
end
    izlaznaJedinicna(red,kolona) = 1;
    izlaznaJedinicna(element(index,1),element(index,2)) = 0;
end


% Posebna funkcija koja trazi ciklus i nase d trazeno
function [dTrazeno,element]=nadjiCiklus(matricaCijena,red,kolona,b)
element=[red kolona];
b(red,kolona)=Inf;
[m,n]=size(matricaCijena);
uslov = 1;    
while (element(1,1) ~= red | element(1,2)~=kolona | length(element) == 2)
    % vrsimo provjeru prvo po redovima, zatim po kolonama
    % moze i obrnuto, svejedno je
    if (uslov == 1)  
      j = 1;
      while (uslov == 1)  
            if (b(element(1,1),j)~=0) && (j~=element(1,2))  
                element = [element(1,1) j ; element]; 
                uslov =0; 
            elseif (j==n)    
                b(element(1,1),element(1,2))=0;
                element=element(2:length(element),:);
                uslov =0;
            else
            	j=j+1; 
            end
      end
  else  
    i = 1;
    while (uslov == 0)
       if (b(i,element(1,2))~=0) && (i~=element(1,1)) 
         element = [i element(1,2) ; element];
         uslov = 1;
       elseif i==m
         b(element(1,1),element(1,2)) = 0;
         element = element(2:length(element),:);
         uslov = 1;
       else
         i=i+1;
       end
    end
  end
end

dTrazeno =matricaCijena(red,kolona);

m=size(element,1)-1;

for i=3:2:m
   dTrazeno = dTrazeno + matricaCijena(element(i,1),element(i,2));    
end
for i=2:2:m
   dTrazeno = dTrazeno - matricaCijena(element(i,1),element(i,2));
end

end
