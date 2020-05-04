% LINEAR_TETMESH_COROTATIONAL_Q Compute the Neohookean potential energy for a tetmesh with linear shape functions
%
% e = linear_tetmesh_corotational_q(V,T, q, dphidX, volume, [C D])
%
% Inputs:
%    V  #T by 3 list of vertices
%    T  #T by 4 list of per tetrahedron indices into V
%    q  3#V by 1 list of deformed mesh vertex positions, arranged as [v1x v1y v1z .... v#Vx v#Vy v#Vz]'
%    dphidX  #T by 12 list of per tetrahedron shape function gradients (dphi/dphidX)
%    volume  #T by 1 list of per tetrahedron volumes
%    [C,D] #T by 2 material parameters matrix. 
% Outputs:
%    e  the linear corotational energy 
%
% Example:
%   % mesh (V,T)
%   vol = volume(V,T); %using gptoolbox volume command
%   dphidX = linear_tetmesh_dphi_dphidX(V,T);
%   q = reshape(V', 3*size(V,1), 1) %initial mesh position
%   YM = 2e6; %in Pascals
%   pr =  0.45
%   [lambda, mu] = emu_to_lame(YM*ones(size(T,1),1), pr*ones(size(T,1),1));
%   e = linear_tetmesh_corotational_q(V,T, q, dphidX, vol, [0.5*mu, 0.5*lambda]);