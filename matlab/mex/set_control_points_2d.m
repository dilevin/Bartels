%add control points to a 2d mesh by clicking
fprintf( ...
  ['\nCLICK on mesh at each location where you would like to add a ' ...
  'point handle.\n' ...
  'Press ENTER when finished.\n\n']);
% User clicks many times on mesh at locations of control points
try
  [Cx,Cy] = getpts;
catch e
  % quit early, stop script
  return
end
% store control points in single #P by 2 list of points
C = [Cx,Cy];