% LINEAR_TETMESH_B Compute gradient matrix for linear tetrahedral finite elements
%
% B = linear_tetmesh_B(V,T)
%
% Inputs:
%    V  #V by 3 list of mesh vertex positions
%    T  #T by 4 list of mesh tetrahedron indices into V
% Outputs:
%    B  #T by #V gradient matrix
%
% Example:
%   % mesh (V,T)
%   B = linear_tetmesh_B(V,T)