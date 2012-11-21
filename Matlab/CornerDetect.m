%Create needed system objects
hIdtc = video.ImageDataTypeConverter();
hCsc = video.ColorSpaceConverter('Conversion','RGB to intensity');
harris = video.CornerDetector( 'MaximumCornerCount', 1000, ...
                               'CornerThreshold', 1e-4, ...
                               'NeighborhoodSize', [9 9] );
                           
%Reduce uint8 to single
leftI3chan = step(hIdtc,left);
rightI3chan = step(hIdtc, right);

%Convert to grey scale
%leftI = step(hCsc,leftI3chan);
%rightI = step(hCsc,rightI3chan);
leftI = leftI3chan;
rightI = rightI3chan;
%Do edge detection
pointsLeft = flipud(step(harris, leftI))+1;
pointsRight = flipud(step(harris, rightI))+1;

% Trim point lists to minimum size.
pointsLeft = pointsLeft(:, 1:find(all(pointsLeft==1,1),1) - 1);
pointsRight = pointsRight(:, 1:find(all(pointsRight==1,1),1) - 1);

%Display
figure, clf;
subplot(121), imshow(leftI), hold on;
plot(pointsLeft(1,:),pointsLeft(2,:),'c+');
title('Strong corners found in left image');
subplot(122), imshow(rightI), hold on;
plot(pointsRight(1,:),pointsRight(2,:),'r+');
title('Strong corners found in right image');

