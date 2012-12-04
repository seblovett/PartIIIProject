%function [ Results ] = SADAll( Left, Right )
%SADALL Function to compute all SADs of an image
%   The sum of absolute differences is calculated and returned on a mesh
%   graph to show how well matched the sub image is to the image. A box out
%   of the right image is taken and compared with the left image.
loadimages;
BoxSize = [50,50];
[~,~,C] = size(right);
[I,J,D] = size(left);
if C ~= D
    error('Images have different number of colour planes');
end

RightSub = GetSubImage(right, BoxSize, [190,190]);

for i = 25:(I-25)
    for j = 25:(J-25)
        LeftSub = GetSubImage(left, BoxSize, [i, j]);
        Diff = LeftSub - RightSub;
        Diff = Diff.^2;
        Results(i,j) = sum(Diff(:));
    end
end

%Display
figure;
subplot(2,2,1);
imshow(left);
title('Left Image');

subplot(2,2,2);
imshow(right);
title('Right Image');

subplot(2,2,3);
imshow(RightSub);
title('Right Sub');

figure;
surf(Results);
shading flat;
%end
