function [ Distance ] = Range( XDr , XDl)
%RANGE Calculates the distance of an object based on the difference in
%position
%

x0 = 320;
phi = 0.655388;
B = 0.0046;
X1 = XDr - (x0/2);
X2 = XDl - (x0 /2 );

if X1 < 0 %LHS of Right
    if X2 > 0 %RHS of Left - easy situation
        Distance = B * x0 / (2 * tan(phi/2)*(X1 - X2));
    elseif X2 < 0 %LHS of Left
%         X1 = abs(X1);
%         X2 = abs(X2);
        phi1 = atan((2 * X1 * tan(phi/2)) / x0);
        phi2 = atan((2 * X2 * tan(phi/2)) / x0);
        
        Distance = (B * cos(phi1) * cos(phi2)) / sin(phi2 - phi1);
    end
elseif X1 > 0
    if X2 > 0
%         X1 = abs(X1);
%         X2 = abs(X2);
        phi1 = atan((2 * X1 * tan(phi/2)) / x0);
        phi2 = atan((2 * X2 * tan(phi/2)) / x0);
        
        Distance = (B * cos(phi1) * cos(phi2)) / sin(phi2 - phi1);
    else
        error('Something is drastically wrong...');
    end
end


end

