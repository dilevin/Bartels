% EMUL_TO_LAME Convert list of material properties specified as Young's Modulus and Poisson's ratio
% to the corresonding first (lambda) and second (mu) lame parameters. 
%
% [lambda, mu] = emu_to_lame(E,p)
%
% Inputs:
%    E  #T by 1 list of per tetrahedron Young's Moduli
%    p  #T by 1 list of per tetrahedron Poisson's Ratios
% Outputs:
%    lambda  #T by 1 list of per tetrahedron first lame parameters
%    mu      #T by 1 list of per tetrahedron second lame parameters

% Example:
%   [lambda, mu] =  emu_to_lame(2e6*ones(size(T,1),1), 0.45*ones(size(T,1),1));
function [lambda, mu] = emu_to_lame(E, p)

    lambda = (E.*p)./((1.0+p).*(1.0-2.0.*p));
    mu = E./(2.0.*(1.0+p));
    
end