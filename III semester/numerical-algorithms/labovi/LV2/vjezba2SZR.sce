clc
mode(1)
//Zadatak za samostalni 2


scicv_Init()
img_gray = imread(getSampleImage("lena.jpg"), CV_LOAD_IMAGE_GRAYSCALE);
figure
matplot(img_gray);
title('Original');
img_mat=img_gray(:,:);
A=double(img_mat)
n = size(A,1);
[U,S,V] = svd(A);
k = 5;
figure
subplot(2,3,1)
Ak = U(:,1:k)*S(1:k,1:k)*V(:,1:k)';
matplot(Ak); title('k=5')
k = 10;
subplot(2,3,2)
Ak = U(:,1:k)*S(1:k,1:k)*V(:,1:k)';
matplot(Ak); title('k=10')
k = 25;
subplot(2,3,3)
Ak = U(:,1:k)*S(1:k,1:k)*V(:,1:k)';
matplot(Ak); title('k=25')
k = 50;
subplot(2,3,4)
Ak = U(:,1:k)*S(1:k,1:k)*V(:,1:k)';
matplot(Ak); title('k=50')
k = 100;
subplot(2,3,5)
Ak = U(:,1:k)*S(1:k,1:k)*V(:,1:k)';
matplot(Ak); title('k=100')
k = 200;
subplot(2,3,6)
Ak = U(:,1:k)*S(1:k,1:k)*V(:,1:k)';
matplot(Ak); title('k=200')
