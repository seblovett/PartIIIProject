function [ SubImage ] = GetSubImage( Image, BoxSize, StartCoordinates)
%GETSUBIMAGE Returns a sub section of the image according to the other
%inputs
%   Image - The image of which a subimage is to be taken from
%   BoxSize - A 2x1 matrix containing the size of the subImage
%   StartCoordinates - A 2x1 matrix with the start point of the image
%   Dimensions - How many planes - 3 for colour, 1 for grey scale

XLow = StartCoordinates(1)-(BoxSize(1)/2);
YLow = StartCoordinates(2)-(BoxSize(2)/2);
if(XLow<1)
    XLow = 1; 
end

if(YLow < 1)
    YLow = 1;
end

XHigh = XLow + BoxSize(1);
YHigh = YLow + BoxSize(2);
[~, ~, LZ] = size(Image);

%SubImage = zeros(BoxSize);
for i = XLow:XHigh
    for j = YLow:YHigh
        if LZ == 3
            for z = 1:3
                SubImage(i-XLow+1,j-YLow+1,z) = Image(i,j,z);
            end
        elseif LZ == 1
            SubImage(i-XLow+1,j-YLow+1) = Image(i,j);
        else
            error('Number of Dimensions "%d" are not supported', LZ);
        end
    end
end

end

