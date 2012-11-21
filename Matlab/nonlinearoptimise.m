% Create dummy points.
C1 = [size(leftI,2)*[1 1 3 3]/4;
      size(leftI,1)*[1/4 3/4 1/3 2/3];
      ones(1,4)];
C2 = [size(leftI,2)*[1 1 3 3]/4;
      size(leftI,1)*[1 3 1 3]/4;
      ones(1,4)];

figure(6), clf, hold on, axis ij;
imagesc([leftI rightI]), axis image, colormap gray;
plot(C1(1,:),C1(2,:),'r*');
plot(C1(1,[1 2 4 3 1]), C1(2,[1 2 4 3 1]),'r-');
plot(size(leftI,2)+C2(1,:),C2(2,:),'r*');
plot(size(leftI,2)+C2(1,[1 2 4 3 1]), C2(2,[1 2 4 3 1]),'r-');
plot([C1(1,:); size(leftI,2)+C2(1,:)], ...
     [C1(2,:); C2(2,:)],'y-.');
set(gca,'XTick',[],'YTick',[]);
text(size(leftI,2)/2,0,'Left tie points (trapezoid)',...
    'HorizontalAlignment','center','VerticalAlignment','bottom');
text(size(leftI,2)+size(rightI,2)/2,0,'Right tie points (square)',...
    'HorizontalAlignment','center','VerticalAlignment','bottom');


% Set parameters of optimization.
[h,w] = size(leftI);
lambda = 0.1;
options = optimset('Jacobian','off', 'Display','off');
options.MaxFunEvals = 10000;
options.MaxIter = 1000;
bounds = [1; pi/2*ones(5,1)];

% Run optimization to discover rotation between cameras.
% Initialize with slightly random values for focal length parameter and the
% five angles (in radians).
rn = 1;
while rn > 0.0035
    % Loop until derived error is below a threshold.
    start = [2*rand-1.0; 0.2*rand(5,1)-0.1];
    [m,rn] = lsqnonlin(@(x)viprectification_lsqnl(x,C1,C2,...
        double(size(leftI,2)),double(size(leftI,1)),...
        lambda),start,-bounds,bounds,options);
end
% Recover rotation matrices between cameras from m.
a = (3^m(1))*(w+h)';
K = [a 0 w/2; 0 a h/2; 0 0 1];
% Generate rotation matrix from returned angles.
RectifiedRight = viprectification_rotmat(m(2:4), 'YZX');
RectifiedLeft = viprectification_rotmat(m(5:6), 'YZ');

% Compute fundamental matrix and rectifying homographies.
F = inv(K)'*(RectifiedRight'*[0 0  0
                              0 0 -1
                              0 1  0]*RectifiedLeft)/K;
Hright = (K*RectifiedRight)/K;
Hleft = (K*RectifiedLeft)/K;
% Recenter homographies on shifted image center.
wh2 = [w; h]/2;
l_cent = Hleft*[wh2;1]; % Reprojected left center.
del_l = wh2 - l_cent(1:2)/l_cent(3);
r_cent = Hright*[wh2;1]; % Reprojected right center.
del_r = wh2 - r_cent(1:2)/r_cent(3);
del_r(2) = del_l(2);
Kr = K; % Modify the old intrinsics to construct different new ones.
Kr(1:2,3) = Kr(1:2,3) + del_r;
Kl = K;
Kl(1:2,3) = Kl(1:2,3) + del_l;
Hright = (Kr*RectifiedRight)/K; % Recompute the homographies.
Hleft = (Kl*RectifiedLeft)/K;

[RectifiedLeft,RectifiedRight,off] = ...
    viprectification_rectifywarp(leftI,rightI,Hleft,Hright);

%---------------------------------------------------------------------------
% The results of the rectification can be seen in the figure below.
%---------------------------------------------------------------------------

figure(7), clf;
montage(cat(4,leftI,rightI)), clf, hold on, axis ij;
imagesc([RectifiedLeft RectifiedRight]), axis image, colormap gray;
C1p = Hleft*C1;
C1p = bsxfun(@rdivide,C1p,C1p(3,:));
C2p = Hright*C2;
C2p = bsxfun(@rdivide,C2p,C2p(3,:));
plot(C1p(1,:)+off(1),C1p(2,:)+off(2),'r*');
plot(C1p(1,[1 2 4 3 1])+off(1),C1p(2,[1 2 4 3 1])+off(2),'r-');
plot(size(RectifiedLeft,2)+C2p(1,:)+off(1),C2p(2,:)+off(2),'r*');
plot(size(RectifiedLeft,2)+C2p(1,[1 2 4 3 1])+off(1),...
    C2p(2,[1 2 4 3 1])+off(2),'r-');
plot([C1p(1,:); size(RectifiedLeft,2)+C2p(1,:)]+off(1), ...
     [C1p(2,:); C2p(2,:)]+off(2),'y-.');
set(gca,'XTick',[],'YTick',[]);
text(size(RectifiedLeft,2)/2,0,'Rectified left image',...
    'HorizontalAlignment','center','VerticalAlignment','bottom');
text(size(RectifiedLeft,2)+size(RectifiedRight,2)/2,0,...
    'Rectified right image','HorizontalAlignment','center',...
    'VerticalAlignment','bottom');