function [zbir,razlika] = zbir_razlika(arg1, arg2)

% prima dva argumenta i 
% racuna zbir i razliku  arg1 i arg2 i vraca njihove vrijednosti 
% ukoliko su prazni argument ili empty uzima se default value 0

[m1,n1] = size(arg1);
[m2,n2] = size(arg2);

if (nargin < 2) || isempty(arg2)
   arg2 = 0;
end
if (nargin < 1) || isempty(arg2)
   arg1 = 0;
end

if (isempty(n1) == false)
    if(isempty(n2)) 
        arg1 = 0;
        arg2 = 0;
    end
    if((m1 ~= m2))
        arg1 = 0;
        arg2 = 0;
    end
end

zbir = arg1 + arg2;
razlika = arg1 - arg2;