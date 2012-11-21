halfBlockSize = 4; % Block half-size.
blockSize = 2*halfBlockSize+1; % Full block size.
[r,c] = size(leftI);
matchThreshold = 0.7;

% Extract features for pointsRight
features = zeros(blockSize^2,size(pointsRight,2), 'single');
for i=1:size(pointsRight,2)
    T = zeros(blockSize, 'single');
    minr = max(1,pointsRight(2,i)-halfBlockSize);
    maxr = min(r,pointsRight(2,i)+halfBlockSize);
    minc = max(1,pointsRight(1,i)-halfBlockSize);
    maxc = min(c,pointsRight(1,i)+halfBlockSize);
    T( halfBlockSize+1-(pointsRight(2,i)-minr):halfBlockSize+1+(maxr-pointsRight(2,i)), ...
       halfBlockSize+1-(pointsRight(1,i)-minc):halfBlockSize+1+(maxc-pointsRight(1,i)) ) = ...
       rightI( minr:maxr, minc:maxc );
    features(:,i) = T(:);
end

% Loop over pointsLeft, looking for best matches in pointsRight via features.
ix1 = zeros(1,size(pointsLeft,2), 'single');
d = zeros(size(ix1), 'single');
for i=1:size(pointsLeft,2)
    T = zeros(blockSize, 'single');
    minr = max(1,pointsLeft(2,i)-halfBlockSize);
    maxr = min(r,pointsLeft(2,i)+halfBlockSize);
    minc = max(1,pointsLeft(1,i)-halfBlockSize);
    maxc = min(c,pointsLeft(1,i)+halfBlockSize);
    T( halfBlockSize+1-(pointsLeft(2,i)-minr):halfBlockSize+1+(maxr-pointsLeft(2,i)), ...
       halfBlockSize+1-(pointsLeft(1,i)-minc):halfBlockSize+1+(maxc-pointsLeft(1,i)) ) = ...
       leftI( minr:maxr, minc:maxc );
    % Find matching point in pointsRight with features features.
    [v,ix] = min( sum(bsxfun(@minus,features,T(:)).^2,1) );
    if v < matchThreshold
        ix1(i) = ix;
    end
end

% Extract indices of matched points on each side.
ix2 = nonzeros(ix1);
ix1 = find(ix1);
% Create subselected, homogenized point lists.
pointsLeftH  = [double(pointsLeft(:,ix1));  ones(1,length(ix1), 'single')];
pointsRightH = [double(pointsRight(:,ix2)); ones(1,length(ix2), 'single')];


% Display
figure(4), clf;
imshow(cat(3,rightI,leftI,leftI)), hold on;
plot(pointsLeftH(1,:),pointsLeftH(2,:),'x','Color',[0 0 1],'MarkerSize',8);
plot(pointsRightH(1,:),pointsRightH(2,:),'x','Color',[1 1 0],'MarkerSize',8);
plot([pointsLeftH(1,:);pointsRightH(1,:)],...
     [pointsLeftH(2,:);pointsRightH(2,:)],'-','Color',[0 1 0]);
set(gca,'XTick',[],'YTick',[]);
title('Initial corresponded points between the two images');
