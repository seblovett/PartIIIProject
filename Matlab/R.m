function [ D ] = R( Delta_x, x0 , phi0, B)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

if ~exist('B')
    B = 42;
end

if ~exist('phi0')
    phi0 = 0.6249;
end

if ~exist('x0')
    x0 = 320;
end

D = (B*x0)/(2*tan(phi0/2)*Delta_x);


end

