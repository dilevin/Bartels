
function smooth_distance_collision

    %move two shapes towards each other and stop when constraints violate
    %thresholds 

    %total number of vertices
    numVerts = 0;
   
    %get data
    alpha = 50;
    [V,F] = readOBJ([data_dir() '/meshes_obj/star.obj']);
    Vobj{1} = V;
    Fobj{1} = F;
    Eobj{1} = boundary_faces(F);
    numVerts = numVerts + size(V,1);
    
    [V,F] = readOBJ([data_dir() '/meshes_obj/lemur.obj']);
    Vobj{2} = V;
    Fobj{2} = F;
    Eobj{2} = boundary_faces(F);
    numVerts = numVerts + size(V,1);
    
    [V,F] = readOBJ([data_dir() '/meshes_obj/hillside_surface.obj']);
    Vobj{3} = 2*V + [4 -1 0];
    Fobj{3} = F;
    Eobj{3} = boundary_faces(F);
    numVerts = numVerts + size(V,1);
    
    %Jacobian matrix for mapping translation onto vertices 
    N = [ones(size(Vobj{1},1),1) zeros(size(Vobj{1},1),1); zeros(size(Vobj{2},1),1) ones(size(Vobj{2},1),1); zeros(size(Vobj{3},1),1) zeros(size(Vobj{3},1),1)];
    N = kroneye(N, 3);
    
    t0 = 0;
    dt = 0.005;
    tf = 4;

    q0 = [0 0 0 3 -0.7 0]';
    qm1 = [-.1 0 0 2.9 -0.7 0]'; %collision course !
    f_ext = [0 -9.8 0 0 -9.8 0]';

    c = zeros(1, numel(t0:dt:tf));
    ii = 1;

    p1 = tsurf(Fobj{1}, Vobj{1}+q0(1:3)');
    hold on
    p2 = tsurf(Fobj{2}, Vobj{2}+q0(4:6)');
    p3 = tsurf(Fobj{3}, Vobj{3});
    hold off
    axis equal

    disp('Press ANY key');
    waitforbuttonpress
    
    function [e,g] = cost_func(x)
        
        e = 0.5*(x'*x) - x'*(2*q0 - qm1) - dt.*dt*x'*f_ext;
        
        if nargout > 1
            g = x - (2*q0-qm1 + dt.*dt.*f_ext);
        end
        
    end

    function [c, ceq, dc, dceq] = nonlcon(x)
    
        tmpObj{1} = Vobj{1}+x(1:3)';
        tmpObj{2} = Vobj{2}+x(4:6)';
        tmpObj{3} = Vobj{3};
        
        [c, g] = smooth_min_distance(tmpObj,Eobj, alpha);
        c = -c;
        ceq = [];
        
        
        if nargout > 2
            dc = -N'*cell2mat(g);
            dceq = [];
        end
            
    end

    options = optimoptions('fmincon');
    options.FiniteDifferenceType = 'central';
    options.FiniteDifferenceStepSize = 1e-6;
    options.OptimalityTolerance = 1e-6;
    options.HessianApproximation = 'lbfgs';
    options.UseParallel = true;
    options.SpecifyObjectiveGradient = true;
    options.SpecifyConstraintGradient = true;
    %options.CheckGradients = true;

    for t = t0:dt:tf

        %qm1 = q0;
        q = fmincon(@cost_func, q0, [], [], [], [], [], [], @nonlcon, options);
        qm1 = q0;
        q0 = q;

        p1.Vertices = Vobj{1} + q0(1:3)';
        p2.Vertices = Vobj{2} + q0(4:6)';
        p3.Vertices = Vobj{3};
        
        drawnow
        
        ii = ii + 1;

    end

end