% A small example of using matlabs built in optimization algorithms
% to implement an implicit time stepper
function implicit_integration

    %load a mesh
    [V,T,F] = readMESH([data_dir(), '/meshes_mesh/coarser_bunny.mesh']);
    
    F = boundary_faces(T);
    V = V./max(max(V) - min(V));
    
    %find some vertices to pin 
    tol = 5e-2;
    pin_I = find(abs(V(:,2) - min(V(:,2))) < tol);
    
    P = fixed_point_constraint_matrix(V, sort(pin_I));
    %P = speye(3*size(V,1));
    vol = volume(V,T);
    M = linear_tetmesh_mass_matrix(V, T, ones(size(T,1),1), vol);
    
    %make some gravity force
    gravity = [0 -9.8 0]'; % We are on krypton 
    gravity = P*M*repmat(gravity, size(V,1),1);
    
    M = P*M*P'; %mass matrix with boundary oncdionts
    dX =  linear_tetmesh_dphi_dX(V,T);
    
    [f,p] = nice_plot(V,F);
    
    qt = reshape(V', 3*size(V,1),1);
    
    %setup all teh variables I need using bc projection matrix
    b = qt - P'*P*qt;
    qt = P*qt;
    vt = 0*qt;
    
    %material properties 
    YM = 9e1; %in Pascals
    pr =  0.4;
    [lambda, mu] = emu_to_lame(YM*ones(size(T,1),1), pr*ones(size(T,1),1));
     
    %time step
    dt = 0.01;
    
    options = optimoptions('fmincon');
    options.Algorithm = 'trust-region-reflective';
    options.Display = 'none';
    options.SpecifyObjectiveGradient = true;
    options.MaxIterations = 10;
    options.HessianFcn = 'objective';
    %options.CheckGradients = true;
    
    disp('Press SPACEBAR to CONTINUE');
    pause 
    
    h = text(0.5*(max(V(:,1)) + min(V(:,1))), 0.9*max(V(:,2)), num2str(0));
    h.FontSize = 28;
    for ti = 1:1000
        
        h.String = num2str(ti);
        
        vt = fmincon(@energy, 0*vt, [], [], [],[], [],[], [], options);
        qt = qt + dt*vt;
        
        p.Vertices = reshape(P'*qt + b, 3, size(V,1))';
        drawnow;
    end
    
    
    %objective needs to return energy, gradient and hessian values
    function [e, g, H] = energy(v)
        
        e = 0.5*v'*M*v - v'*M*vt + ...
            linear_tetmesh_neohookean_q(V,T, P'*(qt+dt*v)+b, dX, vol, [0.5*mu, 0.5*lambda]) - ...
            dt*v'*gravity; 
        
        if nargout > 1
            g = M*(v - vt) + ...
                dt*P*linear_tetmesh_neohookean_dq(V,T, P'*(qt+dt*v)+b, dX, vol, [0.5*mu, 0.5*lambda]) + ...
                - dt*gravity;
            
            if nargout > 2
                H = M + dt*dt*P*linear_tetmesh_neohookean_dq2(V,T, P'*(qt+dt*v)+b, dX, vol, [0.5*mu, 0.5*lambda], 'fixed')*P';
            end
        end
    end

end