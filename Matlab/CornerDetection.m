figure;

subplot(1,2,1);
LeftPoints = Harris(left);
title('Harris Corner Detection of Left Image');

subplot(1,2,2);
RightPoints = Harris(right);
title('Harris Corner Detection of Right Image');