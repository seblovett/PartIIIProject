LEFT = imread('photo_left.bmp');
RIGHT = imread('photo_right.bmp');

figure;
subplot(1,2,1);
title('Images');
imshow(LEFT);
subplot(1,2,2);
imshow(RIGHT);