% IGL2BART Convert vertex data from libigl matrix format to bartels stacked format. 
%
% q = igl2bart(V);
%
% Inputs:
%    V  #V by 3 list of mesh vertex positions
% Outputs:
%    q  3#V list of stacked vertex positions
%
% Example:
%   % mesh (V,T)
%   q = igl2bart(V);