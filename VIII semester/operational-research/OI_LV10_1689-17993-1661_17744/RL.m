function [finalnaStruja] = RL(R,L,E,i0,h,t)
% Radili:
% Masovic Haris - 1689/17993
% Muminovic Amir - 1661/17744

% dodan E u parametar, ulazni napon
finalnaStruja = i0;
iteracija = i0;

for n = h : h : t  
    iteracija = iteracija + h*(E - R*in) / L;
    finalnaStruja = [finalnaStruja iteracija];
end

end 
