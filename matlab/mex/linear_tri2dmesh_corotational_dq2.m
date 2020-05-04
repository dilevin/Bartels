% LINEAR_TRI2DMESH_COROTATIONAL_DQ2 Compute the Hessian of Corotational potential energy for a 2D triangle mesh with linear shape functions
%
% H = linear_tri2dmesh_corotational_dq2(V,T, q, dphidX, volume, [lambda mu])
%
% Inputs:
%    V  #T by 2 list of vertices
%    T  #T by 3 list of per tetrahedron indices into V
%    q  2#V by 1 list of deformed mesh vertex positions, arranged as [v1x v1y v1z .... v#Vx v#Vy v#Vz]'
%    dphidX  #T by 12 list of per tetrahedron shape function gradients (dphi/dphidX)
%    volume  #T by 1 list of per tetrahedron volumes
%    [lambda, mu] #T by 2 material parameters matrix [first lame parameter, second lame parameter]. 
% Outputs:
%    H  2#V by 2#V sparse Hessian matrix 
%
% Example:
%   % 2D mesh (V,T)
%   tri_area = triangle_area(V(:,1:2),T);
%   dphidX = linear_tri2dmesh_dphi_dphidX(V,T);
%   q = reshape(V', 2*size(V,1), 1) %initial mesh position
%   YM = 2e6; %in Pascals
%   pr =  0.45
%   [lambda, mu] = emu_to_lame(YM*ones(size(T,1),1), pr*ones(size(T,1),1));
%   H = linear_tri2dmesh_corotational_dq2(V,T, q, dphidX, vol, [lambda, mu]);