function [  ] = colourcomp( left, right)
%COLOURCOMP Summary of this function goes here
%   Detailed explanation goes here

figure;
Composite = cat(3,right,left,left);
imshow(Composite), title('Color composite (Right = red, Left = cyan)');
end

