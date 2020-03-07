% LINEAR_TRI2DMESH_DPHI_DX Compute per-triangle shape function derivative with respect to the reference space 
%
% dX = linear_tri2dmesh_dphi_dx(V,T)
%
% Inputs:
%    V  #V by 2 list of mesh vertex positions
%    T  #T by 3 list of mesh tetrahedron indices into V
% Outputs:
%    dX  #T by 6 list of gradients of linear tetrahedron shape functions. Each row contains a flattened 3 by 4 gradient matrix 
%        such that grad(phi) = reshape(dX(i,:)', 2,3)
%
% Example:
%   % mesh (V,T)
%   dX = linear_tri2dmesh_dphi_dx(V,T)
