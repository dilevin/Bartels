% BART2IGL Convert vertex data from bartels stacked format tolibigl matrix format. 
%
% q = bart2igl(V);
%
% Inputs:
%    V  #V by 3 list of mesh vertex positions
% Outputs:
%    q  3#V list of stacked vertex positions
%
% Example:
%   % mesh (V,T)
%   V = bart2igl(q);
function V = bart2igl(q,stride)
    V = reshape(q, stride, numel(q)/stride)';
end