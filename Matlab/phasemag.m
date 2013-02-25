function [  ] = phasemag( Image )
%PHASEMAG Will show the phase and magnitude of a grey scale image
%   Takes the 2D Fourier Transform of the Image, displays the Magnitude and
%   Phase of the transform. 

try
    Image = rgb2gray(Image);
catch  %#ok<CTCH>
    
end

FT = fft2(Image);
%ift = ifft2(FT);
FT = fftshift(FT);
mod = abs(FT);
arg = angle(FT);

mod = (mod / max(max(mod))) * 255;

figure;
imshow(Image);
title('Original Image');

figure;
subplot(1,2,1);
imshow(mod);
title('Magnitude of Frequency of Image');
subplot(1,2,2);
imshow(arg);
title('Phase of Frequency of Image');
end

