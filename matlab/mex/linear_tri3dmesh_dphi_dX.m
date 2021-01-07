% LINEAR_TRI3DMESH_DPHI_dphidX Compute per-triangle shape function derivative with respect to the reference space 
%
% dphidX = linear_tri3dmesh_dphi_dphidX(V,T)
%
% Inputs:
%    V  #V by 3 list of mesh vertex positions
%    T  #T by 3 list of mesh tetrahedron indices into V
% Outputs:
%    dphidX  #T by 9 list of gradients of linear tetrahedron shape functions. Each row contains a flattened 3 by 3 gradient matrix 
%        such that grad(phi) = reshape(dphidX(i,:)', 3,3)
%
% Example:
%   % mesh (V,T)
%   dphidX = linear_tri3dmesh_dphi_dX(V,T)
