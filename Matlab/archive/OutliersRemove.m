
nInliers = 0;
while nInliers < 100
    [M, x1inliers, ~] = vipfmatrix_ransac(...
        pointsLeftH(1:2,:), pointsRightH(1:2,:), 2500, 0.2);
    nInliers = size(x1inliers, 2);
end
% Recover inlier indices of x1.
[~,inliers] = find(all(bsxfun(@eq, permute(x1inliers,[2 3 1]), ...
    permute(pointsLeftH(1:2,:),[3 2 1]) ),3));

%---------------------------------------------------------------------------
% The correspondences qualified as inliers are plotted below.
%---------------------------------------------------------------------------

figure(5), clf;
imshow(cat(3,rightI,leftI,leftI)), hold on;
plot(pointsLeftH(1,inliers),pointsLeftH(2,inliers),'x','Color',[0 0 1],'MarkerSize',8);
plot(pointsRightH(1,inliers),pointsRightH(2,inliers),'x','Color',[1 1 0],'MarkerSize',8);
plot([pointsLeftH(1,inliers);pointsRightH(1,inliers)],...
     [pointsLeftH(2,inliers);pointsRightH(2,inliers)],'-','Color',[0 1 0]);
set(gca,'XTick',[],'YTick',[]);
title('Correct correspondences according to RANSAC');
