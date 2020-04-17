% LINEAR_TRI3DMESH_STVK_DQ2 Compute the Hessian of  St. Venant Kirchoff (StVK) potential energy for a 3D triangle mesh with linear shape functions
%
% H = linear_tri3dmesh_stvk_dq2(V,T, q, dX, volume, N, n, dndq, [lambda mu])
%
% Inputs:
%    V  #T by 3 list of vertices
%    T  #T by 3 list of per tetrahedron indices into V
%    q  3#V by 1 list of deformed mesh vertex positions, arranged as [v1x v1y v1z .... v#Vx v#Vy v#Vz]'
%    dX  #T by 9 list of per triangle shape function gradients (dphi/dX)
%    volume  #T by 1 list of per triangle volumes (triangle area multiplied by a user defined thickness)
%    N #T by 3 list of per element normals computed using the undeformed triangle mesh
%    n #T by 3 list of per element normals computed using the triangle mesh in its deformed configuration
%    dndq #T by 27 the flattened gradient of per-element normal with respect to vertex position.
%    [lambda, mu] #T by 2 material parameters matrix [first lame parameter, second lame parameter]. 
% Outputs:
%    H  3#V by 3#V sparse Hessian matrix 
%
% Example:
%   % 3D triangle mesh (V,T)
%   tri_area = triangle_area(V,T);
%   dX = linear_tri3dmesh_dphi_dX(V,T);
%   q = reshape(V', 3*size(V,1), 1) %initial mesh position
%   N = per_facet_normals(V,T);
%   n = per_facet_normals(reshape(q, 3, size(V,1))',T);
%   dndq = dndq_per_facet_normals(reshape(q, 3, size(V,1))',T);
%   YM = 2e6; %in Pascals
%   pr =  0.45;
%   [lambda, mu] = emu_to_lame(YM*ones(size(T,1),1), pr*ones(size(T,1),1));
%   H = linear_tri3dmesh_stvk_dq2(V,T, q, dX, N, n, dndq, tri_area, [lambda, mu]);