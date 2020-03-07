% FIXED_POINT_CONSTRAINT_MATRIX Build the fixed point projection matrix such that q_free = P'*q contains only non-fixed vertices. 
%
% P = fixed_point_constraint_matrix(V, fixed_indices)
%
% Inputs:
%    V  #T by 3 list of vertices
%    fixeD_indices #FIXED by 1 list of indices into V, indicating fixed vertices 
% Outputs:
%    P  (size(V,1)*size(V,2) - size(V,2)*#FIXED) by size(V,1)*size(V,2) sparse matrix 
%
% Example:
%   % mesh (V,T)
%   vol = volume(V,T); %using gptoolbox volume command
%   rho =  0.1*ones(size(T,1),1);
%   M = linear_tetmesh_mass_matrix(V,T, rho, vol);