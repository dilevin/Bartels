
% SMOOTH_MIN_DISTANCE Compute a smooth approximation of the minimum signed distance between the vertices of all objects in a scene and, 
%                     optionally, the gradient of the approximation with respect to each vertex. 
%                     NOTE: This is highly unoptimized and has ~n^2 complexity in the number of boundary vertices.
%
% [c,g] = smooth_min_distance(V,E, alpha);
%
% Inputs:
%    V  a cell array where each V{i} contains a #V{i}x3 vertex list for the i^th object in the scene
%    E  a cell array where each E{i} contains a #E{i}xd connectivity list describing the boundary of 
%       the i^th shape (lines in 2d, triangles in 3d)
%    alpha a scalar parameter controlling the accuracy and smoothness of the approximation. 
%          Small alpha produces highly smooth but inaccurate results, higher alpha improves
%          accuracy at the cost of smoothness and numerical stability. 
% Outputs:
%    c  the scalar, approximate, minimum distance between objects in the scene
%    g  a cell array where g{i} stores dc/dV{i}, is a #3V{i}x1 vector containing 
%       the gradient of the minimum distance, with respect to V{i}. 
%      
%
% Requires gptoolbox
% Example:
%   mesh (V{1},T{1});
%   mesh (V{2},T{2});
%   mesh (V{3},T{3});
%   [c,g] = smooth_min_distance(V, T, 50);
function [c, g] = smooth_min_distance(V,E, alpha)

    num_obj = numel(V);
    e = 0.5;
    
    tmp = 0;
    g = cell(numel(V),1);
    
    for ii=1:num_obj
        
        g{ii} = zeros(numel(V{ii}),1);
        
        for jj=[1:(ii-1) (ii+1):num_obj]
            % checking ii against jj
            w = winding_number(V{jj}(:,1:2),E{jj}, V{ii}(:,1:2));
            sgn = (-w+e)./e; %use winding number to sign the distance 
            dx = (V{ii}(:,1) - V{jj}(:,1)');
            dy = (V{ii}(:,2) - V{jj}(:,2)');
            dz = (V{ii}(:,3) - V{jj}(:,3)');
            
            d = sgn.*sqrt(dx.^2 + dy.^2 + dz.^2); 
            tmp = tmp+sum(exp(-alpha*d(:)));
            
            g{ii}(1:3:end) = g{ii}(1:3:end) + 2*sum(-alpha*exp(-alpha*d).*dx./d,2);
            g{ii}(2:3:end) = g{ii}(2:3:end) + 2*sum(-alpha*exp(-alpha*d).*dy./d,2);
            g{ii}(3:3:end) = g{ii}(3:3:end) + 2*sum(-alpha*exp(-alpha*d).*dz./d,2);
        end
        
    end
    
    c = -log(tmp)./alpha;
    
    %slow but I'm too lazy too lookup the write cell array function
    for ii=1:num_obj
        g{ii} = -g{ii}./(tmp.*alpha);
    end
    
end