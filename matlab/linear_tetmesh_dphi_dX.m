% LINEAR_TETMESH_DPHI_DX Compute per-tetrahedron 
%
% dX = linear_tetmesh_dphi_dx(V,T)
%
% Inputs:
%    V  #V by 3 list of mesh vertex positions
%    T  #T by 4 list of mesh tetrahedron indices into V
% Outputs:
%    dX  #T by 12 list of gradients of linear tetrahedron shape functions. Each row contains a flattened 3 by 4 gradient matrix 
%        such that grad(phi) = reshape(dX(i,:)', 3,4)
%
% Example:
%   % mesh (V,T)
%   dX = linear_tetmesh_dphi_dx(V,T)
