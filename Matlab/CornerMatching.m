%Globals
BoxSize = [20,20]; %Size of comparison Box

%Load images and show
loadimages;
left = im2double(left);
right = im2double(right);
left = rgb2gray(left);
right = rgb2gray(right);

figure; subplot(1,2,1);
LCorners = Harris(left);
subplot(1,2,2);
RCorners = Harris(right);

%Compares a corner with the other corners to find a best match



figure;
for l = 1:size(LCorners)
    %Get a corner
    LCorner = [LCorners(l,1), LCorners(l,2)];% [y, x]
    LeftSub = GetSubImage(left, BoxSize, LCorner, 3);
    for i = 1:size(RCorners)
        RCorner = [RCorners(i, 1) , RCorners(i, 2)];
        RightSub = GetSubImage(right, [20,20], RCorner);
        
        %Diff = LeftSub - RightSub;
        %Diff = Diff.^2;
        %Match(i) = sum(Diff(:));
        %Diff = normxcorr2(LeftSub, RightSub);
        Diff = xcorr2(LeftSub, RightSub);
    end
    subplot(3,3,l);
    plot(Diff);
    %subplot(2,2,l);
    %plot(Match);
    title(sprintf('Matching Values of Corner %d in left to all corners in right', l));
    
end