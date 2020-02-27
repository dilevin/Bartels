function [f, p] = nice_plot(V,F)

    f = figure;
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