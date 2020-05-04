% LINEAR_TRI2DMESH_DPHI_dphidX Compute per-triangle shape function derivative with respect to the reference space 
%
% dphidX = linear_tri2dmesh_dphi_dphidX(V,T)
%
% Inputs:
%    V  #V by 2 list of mesh vertex positions
%    T  #T by 3 list of mesh tetrahedron indices into V
% Outputs:
%    dphidX  #T by 6 list of gradients of linear tetrahedron shape functions. Each row contains a flattened 3 by 4 gradient matrix 
%        such that grad(phi) = reshape(dphidX(i,:)', 2,3)
%
% Example:
%   % mesh (V,T)
%   dphidX = linear_tri2dmesh_dphi_dphidX(V,T)
