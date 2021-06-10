scicv_Init();
clf
img_gray = imread("coins.png", CV_LOAD_IMAGE_GRAYSCALE);
img_mat=img_gray(:,:);
subplot(2,2,1)
[counts,X] = imhist(img_mat,255);
histplot(X,counts)
pause
subplot(2,2,2)
plot(X,counts,'g*')
pause
[P,S,mu]=polyfit(X,counts,30);
Y=polyval(P,X,S,mu);
plot(X,Y,'r')
subplot(2,2,3)
pause
[V,ind]=gsort(abs(diff(Y)),'g','i');
secondd=diff(V);
[valuem,i]=min(secondd);
tresh=ind(i);
[thresh, img_bw] = threshold(img_mat, tresh, 255, THRESH_BINARY);
pause
matplot(img_bw);
subplot(2,2,4)
matplot(img_mat)
