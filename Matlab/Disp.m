loadimages; %Load in some colour images
left = rgb2gray(left); % Convert them to gray
right = rgb2gray(right);
%figure; imshowpair(I1,I2,'ColorChannels','red-cyan');
%title('Red-cyan composite view of the stereo images');
d = disparity(left, right, 'BlockSize', 35,'DisparityRange', [-6 10], 'UniquenessThreshold', 0);
marker_idx = (d == -realmax('single'));
d(marker_idx) = min(d(~marker_idx));
figure; imshow(mat2gray(d));