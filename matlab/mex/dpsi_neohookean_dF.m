% DPSI_NEOHOOKEAN_DF Compute the gradient of the Neohookean Energy, with respect to the deformation gradient F
%
% g = dpsi_neohookean_dF(T,F,[C, D])
%
% Inputs:
%    T  #T by 4 list of per tetrahedron indices into V
%    F  #T by 9 list of flattened deformation gradients, each row is [F11 F21 F31 ... F13 F23 F33]
%    [C,D] #T by 2 list of per-tetrahedron material parameters
% Outputs:
%    g  9#T by 9#T gradient vector
%
% Example:
%   % mesh (V,T)
%   % deformation gradients (F)
%   YM = 2e6; %in Pascals
%   pr =  0.45
%   [lambda, mu] = emu_to_lame(YM*ones(size(T,1),1), pr*ones(size(T,1),1));
%   g = dpsi_neohookean_dF(T,F, [0.5*mu, 0.5*lambda]);