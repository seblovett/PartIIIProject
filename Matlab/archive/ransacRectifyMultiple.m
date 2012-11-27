
nTrials = 10;
theBest.rn = inf;
for i=1:nTrials
    nInliers = 0;
    while nInliers < 20
        [~,x1inliers,~] = vipfmatrix_ransac(...
            pointsLeftH(1:2,:), pointsRightH(1:2,:), 5000, 4e-3);
        nInliers = size(x1inliers, 2);
    end
    % Recover inlier indices of x1.
    [~,inl] = find(all(bsxfun(@eq, permute(x1inliers,[2 3 1]), ...
        permute(pointsLeftH(1:2,:),[3 2 1]) ),3));

    % Run homography optimization on inliers.
    [Hleft,Hright,F,rn] = viprectification_homographies(...
        pointsLeftH(:,inl),pointsRightH(:,inl),...
        size(leftI,2),size(leftI,1),10,10);

    % Check for best result
    if rn < theBest.rn
        theBest.rn = rn;
        theBest.inl = inl;
        theBest.Hleft = Hleft;
        theBest.Hright = Hright;
        theBest.F = F;
    end
end
inliers = theBest.inl;
Hleft = theBest.Hleft;
Hright = theBest.Hright;
F = theBest.F;

[RectifiedLeft,RectifiedRight,off] = ...
    viprectification_rectifywarp(leftI3chan,rightI3chan,Hleft,Hright);

%---------------------------------------------------------------------------
% We plot these rectified images below and the final point correspondences
% used. We also draw a horizontal grid on the image to allow one to easily
% trace that features between the two images are now properly aligned along
% rows.
%---------------------------------------------------------------------------

figure(8), clf;
imshow([RectifiedLeft RectifiedRight]), hold on;
X = axis;
ds = 35:35:X(4);
colours = jet(length(ds));
ds = [ds(1:2:end) ds(2:2:end)];
for i=1:length(ds)
    plot([X(1) X(2)],ds(i)*[1 1],'-','Color',colours(i,:));
end

colormap gray;
Pleft = Hleft * pointsLeftH(:,inliers);
Pleft = bsxfun(@rdivide,Pleft,Pleft(3,:));
Pright = Hright * pointsRightH(:,inliers);
Pright = bsxfun(@rdivide,Pright,Pright(3,:));
plot(Pleft(1,:)+off(1),Pleft(2,:)+off(2),'g.');
plot(size(RectifiedLeft,2)+Pright(1,:)+off(1),Pright(2,:)+off(2),'g.');
text(size(RectifiedLeft,2)/2,0,'Rectified left image',...
    'HorizontalAlignment','center','VerticalAlignment','bottom');
text(size(RectifiedLeft,2)+size(RectifiedRight,2)/2,0,'Rectified right image',...
    'HorizontalAlignment','center','VerticalAlignment','bottom');
text(size(RectifiedLeft,2),0,'(Tie points used in green)',...
    'HorizontalAlignment','center','VerticalAlignment','bottom');