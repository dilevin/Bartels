% LINEAR_TETMESH_MASS_MATRIX Compute the consistent mass matrix for a tetmesh with linear shape functions
%
% M = linear_tetmesh_mass_matrix(V,T, density, volume);
%
% Inputs:
%    V  #T by 3 list of vertices
%    T  #T by 4 list of per tetrahedron indices into V
%    density  #T by 1 list of per tetrahedron densities
%    volume   #T by 1 list of per tetrahedron volumes
% Outputs:
%    M  3#V by 3#V sparse, consistent mass-matrix
%
% Example:
%   % mesh (V,T)
%   vol = volume(V,T); %using gptoolbox volume command
%   rho =  1000.0*ones(size(T,1),1);
%   M = linear_tetmesh_mass_matrix(V,T, rho, vol);