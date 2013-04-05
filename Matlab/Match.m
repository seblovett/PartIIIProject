function [ MatchDiff ] = Match( left, right )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
%close all;
% Global Constants
BoxSize = 50

% Display Images
f = figure;
subplot(2,2,1); 
imshow(left);
title('Left Image');
subplot(2,2,2);
imshow(right);
title('Right Image');
% Get Template
figure;
imshow(right);
title('Choose location to Cross Correlate with the Left Image');
rSubCoord = ginput(1);
[rSubCoord(2), rSubCoord(1)];
rSubCoord = round(rSubCoord);
Rx = rSubCoord(1);
Ry = rSubCoord(2);
close;
leftG = rgb2gray(left);
rightG = rgb2gray(right);
% Extract Template
RightTemplate = rightG(Ry-(BoxSize/2):Ry+(BoxSize/2), Rx-(BoxSize/2):Rx+(BoxSize/2));

%Cross Correlate
NCC = normxcorr2(RightTemplate, leftG);

%Display
figure(f);
subplot(2,2,3);
surf(NCC);
hold on;
shading interp;

%Find Maximum
[~, l] = max(NCC(:));
%Return Match Coordinates
[~, Lx] = ind2sub(size(NCC),l);
Lx = Lx-BoxSize/2;
fprintf('Right Template at %d\n', Rx);
fprintf('Left Match at %d\n', Lx);

MatchDiff = abs(Lx - Rx);
end
