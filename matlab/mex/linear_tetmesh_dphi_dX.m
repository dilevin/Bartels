% LINEAR_TETMESH_DPHI_dphidX Compute per-tetrahedron 
%
% dphidX = linear_tetmesh_dphi_dphidX(V,T)
%
% Inputs:
%    V  #V by 3 list of mesh vertex positions
%    T  #T by 4 list of mesh tetrahedron indices into V
% Outputs:
%    dphidX  #T by 12 list of gradients of linear tetrahedron shape functions. Each row contains a flattened 3 by 4 gradient matrix 
%        such that grad(phi) = reshape(dphidX(i,:)', 3,4)
%
% Example:
%   % mesh (V,T)
%   dphidX = linear_tetmesh_dphi_dphidX(V,T)
