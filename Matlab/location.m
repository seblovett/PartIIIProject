%Attempts to match the centre line of 50 pixels up

%take a letter box out of both images
for i = 100:140
    for j = 1:320
        for k = 1:3
            LEFT_Sub(i-99,j, k) = LEFT(i-3,j,k);
            RIGHT_Sub(i-99,j,k) = RIGHT(i,j,k);
        end
    end
end

figure(1)
subplot(2,2,1);
imshow(LEFT_Sub);
subplot(2,2,2);
imshow(RIGHT_Sub);

for i = 1:40
    for j = 1:40
        for k = 1:3
            LEFT_Sub_sub(i,j,k) = LEFT_Sub(i,j+200,k);
        end
    end
end 

subplot(2,2,3);
imshow(LEFT_Sub_sub);
Results = zeros(1,280);
for x = 40:280
   %Extract Right Sub Sub
   for i = 1:40
        for j = 1:40
            for k = 1:3
                RIGHT_Sub_sub(i,j,k) = RIGHT_Sub(i,j+x-1,k);
            end
        end
   end
    
    %subtract left from right
    RES = RIGHT_Sub_sub - LEFT_Sub_sub;
    
    %take mean
    Results(x-39) = mean2(RES);
    
    
end
subplot(2,2,4);
plot(Results);

