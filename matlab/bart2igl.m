% BART2IGL Convert vertex data from bartels stacked format tolibigl matrix format. 
%
% V = bart2igl(q, stride);
%
% Inputs:
%    q  #stride*V stacked list of mesh vertex positions
%    stride dimension of each coordinate in q
% Outputs:
%    V  #V by stride list of stacked vertex positions
%
% Example:
%   % mesh (V,T)
%   V = bart2igl(q);
function V = bart2igl(q,stride)
    V = reshape(q, stride, numel(q)/stride)';
end