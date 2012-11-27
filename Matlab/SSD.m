function [ Disparity, MatchIndex ] = SSD( left, right, offset )
%SSD Sum of Squared Differences
%   A centre square is chosen in the right image. 
%   Left image is itterated over and the difference is taken from this
%   square and the centre square. Sum of the differences squared is stored
%   and returned.
%   'offset' is the number of pixels the right hand match is done from. 

BoxSize = [50,50];

%Extract Centre Block
RightSquareLocation = size(right) / 2;
RightSquareLocation = [offset, RightSquareLocation(2)];

RBox = GetSubImage(right, BoxSize, RightSquareLocation,3);
%figure; imshow(RBox);

%LYLow = RYLow; %Assume that the image are rectified making this a 1D Problem

%LXLow = 1;
SizeLeft = size(left);
LeftSquareLocation = RightSquareLocation;
LeftSquareLocation(2) = 1;

for a = 1:(SizeLeft(2) - BoxSize/2)
    LeftSquareLocation(2) = a;
    LBox = GetSubImage(left, BoxSize, LeftSquareLocation,3);
    Differences = LBox - RBox;
    Differences = Differences.^2;
    Disparity(a) = sum(Differences(:));
    %Disparity = Differences;
end



[~, index] = min(Disparity);
MatchIndex = [RightSquareLocation(1), index];

right(RightSquareLocation(1) - 25 : RightSquareLocation(1) + 25,...
    RightSquareLocation(2) + 25) = 255;
right(RightSquareLocation(1) - 25 : RightSquareLocation(1) + 25,...
    (RightSquareLocation(2) - 25)) = 255;

right(RightSquareLocation(1) - 25,...
    RightSquareLocation(2) - 25 : RightSquareLocation(2) + 25) = 255;
right(RightSquareLocation(1) + 25,...
    RightSquareLocation(2) - 25 : RightSquareLocation(2) + 25) = 255;

left(MatchIndex(1) - 25 : MatchIndex(1) + 25,...
    MatchIndex(2) + 25) = 255;
left(MatchIndex(1) - 25 : MatchIndex(1) + 25,...
    (MatchIndex(2) - 25)) = 255;

left(MatchIndex(1) - 25,...
    MatchIndex(2) - 25 : MatchIndex(2) + 25) = 255;
left(MatchIndex(1) + 25,...
    MatchIndex(2) - 25 : MatchIndex(2) + 25) = 255;


figure;
subplot(1,2,1); 
imshow(left); 
title('Left Image and block matched');

subplot(1, 2,2);
imshow(right);
title('Right Image and Block to match to shown');

figure;
plot(Disparity);
title('Pixel Number against Disparity Values');

end

