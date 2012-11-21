function [ Disparity ] = SSD( left, right )
%SSD Sum of Squared Differences
%   A centre square is chosen in the right image. 
%   Left image is itterated over and the difference is taken from this
%   square and the centre square. Sum of the differences squared is stored
%   and returned.

BoxSize = [50,50];

%Extract Centre Block
RightSquareLocation = size(right) / 2;
RightSquareLocation = [RightSquareLocation(1)+50, RightSquareLocation(2)];

RBox = GetSubImage(right, BoxSize, RightSquareLocation,1);
figure; imshow(RBox);

%LYLow = RYLow; %Assume that the image are rectified making this a 1D Problem

%LXLow = 1;
SizeLeft = size(left);
LeftSquareLocation = RightSquareLocation;
LeftSquareLocation(2) = 1;

for a = 1:(SizeLeft(2) - BoxSize/2)
    LeftSquareLocation(2) = a;
    LBox = GetSubImage(left, BoxSize, LeftSquareLocation,1);
    Differences = LBox - RBox;
    Differences = Differences.^2;
    Disparity(a) = sum(Differences(:));
    %Disparity = Differences;
end


figure; plot(Disparity);
end

