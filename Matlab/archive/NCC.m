function [ CrossCorr ] = NCC( left, right )
%NCC Summary of this function goes here
%   Detailed explanation goes here


BoxSize = [50,50];
offset = 280;
%Extract Centre Block
RightSquareLocation = size(right) / 2;
RightSquareLocation = [offset, RightSquareLocation(2)];

RBox = GetSubImage(right, BoxSize, RightSquareLocation,3);

LeftLetBox = GetSubImage(left, [50,350], [offset, 20], 3);
%RBox = im2double(RBox);
%LeftLetBox = im2double(LeftLetBox);
RBox = rgb2gray(RBox);
LeftLetBox = rgb2gray(LeftLetBox);


CrossCorr = normxcorr2(RBox, LeftLetBox);

figure; plot(CrossCorr);
figure; mesh(CrossCorr);
end

