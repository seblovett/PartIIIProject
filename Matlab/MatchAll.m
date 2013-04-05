for i = 1:10
    l = sprintf('Range_Test_Images/Duck_L_%d00.bmp', i);
    r = sprintf('Range_Test_Images/Duck_R_%d00.bmp', i);
    
    left = imread(l);
    right = imread(r);
    
    Matches(i) = Match(left,right); 
    
end