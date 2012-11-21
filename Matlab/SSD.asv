function [ Disparity ] = SSD( left, right )
%SSD Sum of Squared Differences
%   A centre square is chosen in the right image. 
%   Left image is itterated over and the difference is taken from this
%   square and the centre square. Sum of the differences squared is stored
%   and returned.

BoxSize = [50,50];

%Extract Centre Block
RightSquareLocation = size(right) / 2;
RightSquareLocation = [RightSquareLocation(1), RightSquareLocation(2)];

RBox = GetSubImage(right, BoxSize, RightSquareLocation);
imshow(RBox);

%LYLow = RYLow; %Assume that the image are rectified making this a 1D Problem

%LXLow = 1;


end

