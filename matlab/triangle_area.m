function a = triangle_area(V,F)
% TRIANGLE_AREA Compute areas of a triangle mesh
%
% areas = triangle_area(V,F)
%
% Inputs:
%    V  #V by 3 list of mesh vertex positions
%    F  #T by 3 list of mesh triangle indices into V
% Outputs:
%    areas  #T by 1 list of per triangle areas
% Example:
%   % mesh (V,F)
%   areas = triangle_area(V,F)

    dphidX1 = V(F(:,2),:) - V(F(:,1),:);
    dphidX2 = V(F(:,3),:) - V(F(:,1),:);

    if size(V,2) == 2
        a = 0.5*(dphidX1(:,1).*dphidX2(:,2) - dphidX1(:,2).*dphidX2(:,1)); 
    else
        a = cross(dphidX1,dphidX2,2);
        a = 0.5*sqrt(sum(a.*a,2));
    end

end