function crtaj2(funkcija, intervali, N, metoda)
    % Funkcija crta grafik funkcije dvije promjenjive
    % Ulazni argumenti su: 
    % 1. funckija - string izraz koji predstavlja funkciju koju treba racunati
    % 2. intervali - matrica 2 x 2
    % 3. N - broj tacaka za interpolaciju
    % 4. metoda - string koji opisuje zeljenu metodu crtanja
    % Moze se pozvati sa 1, 2, 3 ili 4 argumentom
    % Predpostavljena metoda: mesh, broj tacaka:100, interval [-5,5]
    
    if (nargin == 1)
        intervali=[5 -5; 5 -5];
        N = 100;
        metoda = 'mesh';
    elseif (nargin == 2)
        N = 100;
        metoda = 'mesh';
    elseif (nargin == 3) 
        metoda == 'mesh';
    end
    
    x1 = intervali(1,1);
    x2 = intervali(1,2);
    y1 = intervali(2,1);
    y2 = intervali(2,2);
    
    X = linspace(x1,x2,N);
    Y = linspace(y1,y2,N);
    [x,y] = meshgrid(X,Y);
    z = eval(funkcija);
    
    switch (metoda)
        case 'surf'
            surf(x,y,z);
        case 'contour'
            contour(x,y,z);
        case 'contour3'
            contour3(x,y,z);
        otherwise
            mesh(x,y,z);
    end
end