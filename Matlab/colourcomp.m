function [  ] = colourcomp( left, right)
%COLOURCOMP Makes a red=cyan colour composition of both images
%   Images can be RGB or gray scale. RGB images will be converted to Gray
%   scale before being used.

[A B C] = size(left);
if C == 3
    left = rgb2gray(left);
end

[A B C] = size(right);
if C == 3
    right = rgb2gray(right);
end

figure;
Composite = cat(3,right,left,left);
imshow(Composite), title('Color composite (Right = red, Left = cyan)');
end

