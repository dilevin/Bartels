function [f, p] = nice_plot(V,F, fig)
% NICE_PLOT make a nicely rendered plot of a triangle mesh
%
% areas = triangle_area(V,F)
%
% Inputs:
%    V  #V by 3 list of mesh vertex positions
%    F  #T by 3 list of mesh triangle indices into V
% Outputs:
%    f  handle to plot figure
%    p  handle to patch representing the triangle mesh
%
% Example:
%   % mesh (V,F)
%   [f,p] = nice_plot(V,F);

    if nargin < 3
        f = figure;
    else
        f = fig;
        clf(f);
    end
    
    
    axes('Units', 'normalized', 'Position', [0 0 1 1]);
    
    p = patch('Faces',F, 'Vertices', V, 'FaceColor',       [0.8 0.8 1.0], ...
               'EdgeColor',       'none', 'EdgeColor', 0.1*[0.8 0.8 1.0],        ...
               'FaceLighting',    'gouraud',     ...
                'AmbientStrength', 0.15);
    
    material('shiny')
    camlight('headlight')
    axis equal
    axis vis3d
    axis manual
    
    f.Color = [1,1,1];
    f.CurrentAxes.Visible = 'off';
    f.CurrentAxes.XTick = [];
    f.CurrentAxes.YTick = [];
    f.CurrentAxes.ZTick = [];
end