function [P,Q,V,Strategije] = igreGraficki(matricaPlacanja)
m = size(matricaPlacanja,1);
n = size(matricaPlacanja,2);
hold off
lines = zeros(2,m);
x0 = [0,1];
P0 = zeros(1,n);
P1 = zeros(1,n);

for i=1:n
    lines(i,2) = matricaPlacanja(2,i);
    lines(i,1) = matricaPlacanja(1,i) - matricaPlacanja(2,i);
    
    P0(i) = lines(i,2);
    P1(i) = lines(i,1) + lines(i,2);
    
    plot(x0,[P0(i),P1(i)]);
    hold on
end


x_presek = [];
y_presek = -Inf * ones(size(lines,1),size(lines,1));
for i=1:size(lines,1)-1
    for j=i+1:size(lines,1)
        y1 = [P0(i), P1(i)];
        poly1 = polyfit(x0,y1,1);
        
        y2 = [P0(j), P1(j)];
        poly2 = polyfit(x0,y2,1);
        
        x_presek(i,j) = fzero(@(x) polyval(poly1-poly2,x),3);
        y_presek(i,j) = polyval(poly1,x_presek(i,j));
        
    end
end

for i=1:m
    for j=i+1:n
        for k=1:size(lines,1)
            if(~(k == i && k == j) && lines(k,1)*x_presek(i,j)+lines(k,2) < y_presek(i,j))
                x_presek(i,j) = 0;
                y_presek(i,j) = -inf;
        end        
    end
end

[maxVal, l1] = max(y_presek);
l1 = max(l1);
[maxVal, l2] = max(maxVal);
plot(x_presek(l1,l2),y_presek(l1,l2),'ro');

Vals = [matricaPlacanja(1,l1) matricaPlacanja(1,l2);matricaPlacanja(2,l1) matricaPlacanja(2,l2)];

P(1) = (Vals(2,2)-Vals(2,1))/(Vals(1,1)-Vals(1,2)+Vals(2,2)-Vals(2,1));
P(2) = 1 - P(1);

Q = zeros(1,n);
q1 = (Vals(2,2)-Vals(1,2))/(Vals(1,1)-Vals(1,2)+Vals(2,2)-Vals(2,1));
q2 = 1 - q1;
Q(l1) = q1;
Q(l2) = q2;

V = (Vals(1,1)*Vals(2,2)-Vals(1,2)*Vals(2,1))/(Vals(1,1)-Vals(1,2)+Vals(2,2)-Vals(2,1));
Strategije = [l1 l2];

end
