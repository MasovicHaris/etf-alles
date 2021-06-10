mode(1)
clc
[y,Fs,bits]=wavread("Theme.wav");Fs,bits
y=y(:);
x = linspace(0, 1, size(y,1))'/Fs;
playsnd(y,Fs);

//Downsample
FsDown=1200;
d=splin(x,y);
xDown = linspace(0, 1, size(y,1))'/FsDown;
yDown=interp(xDown,x,y,d);
playsnd(yDown,FsDown)

//Upsample
FsUp=44100;
xUp = linspace(0, 1, size(yDown,1))'/FsUp;
d=splin(xDown,yDown);
yUp= interp(xUp,xDown,yDown,d);
playsnd(yUp,FsUp)

//Plot
subplot(311)
plot(x,y);
title('Original')
subplot(312)
plot(xDown,yDown);
title('Donwsample')
subplot(313)
plot(xUp,yUp);
title('Upsample')
