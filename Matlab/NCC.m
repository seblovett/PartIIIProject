
loadimages;
show;
BoxSize = [100,100];
MaxConfMatches = 20;
%SubCoord = [145, 300];
figure(1);
%[rightSub, rect_Sub] = imcrop(right);
figure(2);
imshow(right);
rSubCoord = ginput(1);
%rSubCoord = [190,190]; 
[rSubCoord(2), rSubCoord(1)];
rSubCoord = round(rSubCoord);
close;
tic;
rightSub = GetSubImage(right, BoxSize, rSubCoord);
%imshow(rightSub);
rightSubGray = rgb2gray(rightSub);
leftGray = rgb2gray(left);
rightGray = rgb2gray(right);
cL = normxcorr2(rightSubGray(:,:), leftGray(:,:));
figure(2);
% subplot(1,2,1);
surf(cL), shading flat;
title('Normalised Cross Correlation of Right Sub and Left Image');
toc;
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
          LeftMatchCoord = [j-(BoxSize(1) / 2 ), i-(BoxSize(2) / 2 )];
       end
   end
end

Result = [maxValue, LeftMatchCoord];
figure(1);
if NumConfidentMatches >= 1 && NumConfidentMatches < MaxConfMatches
    left(LeftMatchCoord(1)-(BoxSize(1)/2):LeftMatchCoord(1)+(BoxSize(1)/2),LeftMatchCoord(2)-(BoxSize(2))/2)=255;
    left(LeftMatchCoord(1)-(BoxSize(1)/2):LeftMatchCoord(1)+(BoxSize(1)/2),LeftMatchCoord(2)+(BoxSize(2))/2)=255;
    left(LeftMatchCoord(1)-(BoxSize(1)/2),LeftMatchCoord(2)-(BoxSize(2)/2):LeftMatchCoord(2)+(BoxSize(2))/2)=255;
    left(LeftMatchCoord(1)+(BoxSize(1)/2),LeftMatchCoord(2)-(BoxSize(2)/2):LeftMatchCoord(2)+(BoxSize(2)/2))=255;
    
    right(rSubCoord(1)-(BoxSize(1)/2):rSubCoord(1)+(BoxSize(1)/2),rSubCoord(2)-(BoxSize(2)/2))=255;
    right(rSubCoord(1)-(BoxSize(1)/2):rSubCoord(1)+(BoxSize(1)/2),rSubCoord(2)+(BoxSize(2)/2))=255;
    right(rSubCoord(1)-(BoxSize(1)/2),rSubCoord(2)-(BoxSize(2)/2):rSubCoord(2)+(BoxSize(2)/2))=255;
    right(rSubCoord(1)+(BoxSize(1)/2),rSubCoord(2)-(BoxSize(2)/2):rSubCoord(2)+(BoxSize(2)/2))=255;
    
    subplot(1,2,1);
    imshow(left);
    subplot(1,2,2);
    imshow(right);
%     LeftMatchCoord
%     rSubCoord
%     NumConfidentMatches
    Distance = Range(rSubCoord(2), LeftMatchCoord(2));
    sprintf('Distance to Object = %d metres', Distance)
elseif NumConfidentMatches >= MaxConfMatches
    title(sprintf('Too many matches found : %d', NumConfidentMatches));
else
    title(sprintf('No Reliable Match Found'));
    
end