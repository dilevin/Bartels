% LINEAR_TRI3DMESH_F Compute the deformation gradient for a 2D triangle mesh embedded in 3D
%
% F = linear_tri3dmesh_F(V,T, q, dphidX, N, n)
%
% Inputs:
%    V  #V by 3 list of mesh vertex positions
%    T  #T by 3 list of mesh tetrahedron indices into V
%    q  3#V by 1 vector of deformed vertex coordinates
%    dphidX #T by 9 matrix of flattened shape function derivatives
%    N  #T by 3 matrix of undeformed surface normals
%    n  #T by 3 matrix of deformed surface normals 
% Outputs:
%    F  #T by 9 list of deformation gradients. Each row contains a flattened 3 by 3 gradient matrix 
%
% Example:
%   % mesh (V,T)
%   F = linear_tri3dmesh_F(V,T, q, dphidX, N, n);
