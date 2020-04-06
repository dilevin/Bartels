% LINEAR_TETMESH_NEOHOOKEAN_DQ Compute the gradient of Neohookean potential energy for a tetmesh with linear shape functions
%
% g = linear_tetmesh_neohookean_dq(V,T, q, dX, volume, [C D])
%
% Inputs:
%    V  #T by 3 list of vertices
%    T  #T by 4 list of per tetrahedron indices into V
%    q  3#V by 1 list of deformed mesh vertex positions, arranged as [v1x v1y v1z .... v#Vx v#Vy v#Vz]'
%    dX  #T by 12 list of per tetrahedron shape function gradients (dphi/dX)
%    volume  #T by 1 list of per tetrahedron volumes
%    [C,D] #T by 2 material parameters matrix. 
% Outputs:
%    g  3#V by 1 gradient vector
%
% Example:
%   % mesh (V,T)
%   vol = volume(V,T); %using gptoolbox volume command
%   dX = linear_tetmesh_dphi_dX(V,T);
%   q = reshape(V', 3*size(V,1), 1) %initial mesh position
%   YM = 2e6; %in Pascals
%   pr =  0.45
%   [lambda, mu] = emu_to_lame(YM*ones(size(T,1),1), pr*ones(size(T,1),1));
%   g = linear_tetmesh_neohookean_dq(V,T, q, dX, vol, [0.5*mu, 0.5*lambda]);