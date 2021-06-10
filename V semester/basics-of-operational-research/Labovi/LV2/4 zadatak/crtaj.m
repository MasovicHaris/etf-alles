function crtaj(str)
    X = linspace(-5,5,100);
    Y = linspace(-5,5,100);
    [x,y] = meshgrid(X,Y);
    z = eval(str);
    mesh(x,y,z);
end