function [ ] = z4(krajnjeVrijeme, R, korak)
% iznad su prikazane postavke trazene od korisnika
% krajnjeVrijeme - vrijeme do kojeg da ide
% aktuelna vrijednost otpora
% korak - korak kretanja kroz petlju, iteracija

% pocetne vrijednosti iz postavke
E = 14.7; L = 19.4; C = 0.0136;
% pocetna struja i napon, iz postavke
pocetnaStruja = 0; pocetniNapon = 0;
% vrijednosti koje ce se akumulirati
akumuliranaStruja = []; akumuliraniNapon = []; ukupniNapon = [];

% postupak akumulacije    
for k = 0 : korak : krajnjeVrijeme
    iL_s = pocetnaStruja + korak * double(E-pocetniNapon)/L;
    pocetnaStruja = iL_s;
    uC_s = pocetniNapon + korak * double(pocetnaStruja - double(pocetniNapon/R))/C;
    pocetniNapon = uC_s;
    ukupniNapon = [ukupniNapon, k];
    akumuliranaStruja = [akumuliranaStruja, iL_s];
    akumuliraniNapon = [akumuliraniNapon, uC_s];
end

% ispis finalne struje i napona
disp("ukupna struja: ");
disp(akumuliranaStruja(end));
disp("ukupni napon: ");
disp(akumuliraniNapon(end));
    
% plottanje grafa
hold off;
plot(ukupniNapon, akumuliranaStruja,'g');
hold on;
plot(ukupniNapon, akumuliraniNapon,'r');
legend('struja', 'napon');

end