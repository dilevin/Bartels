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
    
    p = patch('Faces',F, 'Vertices', V, 'FaceColor',       [0.5 0.5 1.0], ...
               'EdgeColor',       'none', 'EdgeColor', 0.1*[0.8 0.8 1.0],        ...
               'FaceLighting',    'gouraud',     ...
                'AmbientStrength', 0.15);
    
    axis equal
    axis vis3d
    axis manual
    
    material([0.3 0.6 0.9 2]);
    %l0 = camlight('right')
    %l1 = camlight('left')
    l2 = camlight('headlight')
    l2.Color = [0.4, 0.4, 0.4];
    
    f.Color = [1,1,1];
    f.CurrentAxes.Visible = 'off';
    f.CurrentAxes.XTick = [];
    f.CurrentAxes.YTick = [];
    f.CurrentAxes.ZTick = [];
    
    h = rotate3d(f);
    set(h,'Enable','on');
    
     % add a callback which will be executed after each rotation
     set(h,'ActionPostCallback',{@move_light_source, l2});
    
     % This function will move the light after each rotation
     function move_light_source(src, evt, l2)
        camlight(l2, 'headlight');
     end

%     set(f,'windowbuttonmotionfcn',@oncontrolsdrag)
%         
%     
%      % Callback for mouse drag on control points
%     function oncontrolsdrag(src,ev)
%         disp('here');
%        l2 = camlight('headlight');
%     end

end