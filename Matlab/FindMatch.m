loadimages;
show;

MaxConfMatches = 20;
%SubCoord = [145, 300];
figure(1);
%[rightSub, rect_Sub] = imcrop(right);
figure(2);
imshow(right);
rSubCoord = ginput(1);
rSubCoord = [rSubCoord(2), rSubCoord(1)];
rSubCoord = round(rSubCoord);
close;
rightSub = GetSubImage(right, [20,20], rSubCoord);
%imshow(rightSub);
rightSubGray = rgb2gray(rightSub);
leftGray = rgb2gray(left);
rightGray = rgb2gray(right);
cL = normxcorr2(rightSubGray(:,:), leftGray(:,:));
figure(2);
% subplot(1,2,1);
surf(cL), shading flat;
title('Normalised Cross Correlation of Right Sub and Left Image');

% cR = normxcorr2(rightSubGray(:,:), rightGray(:,:));
% subplot(1,2,2);
% surf(cR), shading flat;
% title('Normalised Cross Correlation of Right Sub and Right Image');

% cD = cL - cR;
% 
% figure;
% surf(cD), shading flat;
% title('Differences of the Normalised Cross Correlation of Right and Left');

%Find coordintes of best match. 
[Y,X] = size(cL);
maxValue = 0;
LeftMatchCoord = [0,0];
NumConfidentMatches = 0;

for i = 1:X
   for j = 1:Y
       Val = cL(j,i);
       if Val > 0.9
           NumConfidentMatches = NumConfidentMatches + 1; 
       end
       if Val > maxValue
          maxValue = Val;
          LeftMatchCoord = [j-10, i-10];
       end
   end
end

Result = [maxValue, LeftMatchCoord];

if NumConfidentMatches >= 1 && NumConfidentMatches < MaxConfMatches
    left(LeftMatchCoord(1)-20:LeftMatchCoord(1)+20,LeftMatchCoord(2)-20)=255;
    left(LeftMatchCoord(1)-20:LeftMatchCoord(1)+20,LeftMatchCoord(2)+20)=255;
    left(LeftMatchCoord(1)-20,LeftMatchCoord(2)-20:LeftMatchCoord(2)+20)=255;
    left(LeftMatchCoord(1)+20,LeftMatchCoord(2)-20:LeftMatchCoord(2)+20)=255;
    
    right(rSubCoord(1)-20:rSubCoord(1)+20,rSubCoord(2)-20)=255;
    right(rSubCoord(1)-20:rSubCoord(1)+20,rSubCoord(2)+20)=255;
    right(rSubCoord(1)-20,rSubCoord(2)-20:rSubCoord(2)+20)=255;
    right(rSubCoord(1)+20,rSubCoord(2)-20:rSubCoord(2)+20)=255;
    
    figure(3);
    subplot(1,2,1);
    imshow(left);
    subplot(1,2,2);
    imshow(right);
    LeftMatchCoord
    rSubCoord
    NumConfidentMatches
elseif NumConfidentMatches >= MaxConfMatches
    error('Too many matches found : %d', NumConfidentMatches);
else
    error('No Reliable Match Found');
    
end