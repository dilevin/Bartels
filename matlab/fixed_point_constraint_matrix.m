% FIXED_POINT_CONSTRAINT_MATRIX Build the fixed point projection matrix such that q_free = P'*q contains only non-fixed vertices. 
%
% P = fixed_point_constraint_matrix(V, fixed_indices)
%
% Inputs:
%    V  #T by 3 list of vertices
%    fixeD_indices #FIXED by 1 - list of indices into V SORTED IN ASCENDING ORDER, indicating fixed vertices 
% Outputs:
%    P  (size(V,1)*size(V,2) - size(V,2)*#FIXED) by size(V,1)*size(V,2) sparse matrix 
%
% Example:
%  % mesh (V,T)
%  % list of 3d points C
%  [min_d, min_I] = min(bsxfun(@minus, V(:,1), C(:,1)').^2 + bsxfun(@minus, V(:,2), C(:,2)').^2,[],1); %find vertices nearest to points in list
%  P = fixed_point_constraint_matrix(V, sort(min_I))