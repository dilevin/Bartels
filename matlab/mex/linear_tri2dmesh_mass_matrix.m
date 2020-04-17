% LINEAR_TRI2DMESH_MASS_MATRIX Compute the consistent mass matrix for a two-dimensional triangle mesh with linear shape functions
%
% M = linear_tri2dmesh_mass_matrix(V,T, density, volume);
%
% Inputs:
%    V  #V by 2 list of vertices
%    T  #T by 3 list of per triangle indices into V
%    density  #T by 1 list of per tetrahedron densities
%    areas   #T by 1 list of per triangle areas
% Outputs:
%    M  2#V by 2#V sparse, consistent mass-matrix
%
% Example:
%   % mesh (V,T)
%   areas = triangle_area(V,T); 
%   rho =  1000.0*ones(size(T,1),1);
%   M = linear_tri2smesh_mass_matrix(V,T, rho, areas);