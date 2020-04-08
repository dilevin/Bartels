function test_tet_materials

    % a little script to make testing material models on triangle meshes easier
    [V,T,F] = readMESH([data_dir(), '/meshes_mesh/beam.mesh']);

    F = boundary_faces(T);
    
    %setup simulation variables
    %triangle areas
    vol = volume(V,T);

    %triangle gradients 
    dX = linear_tetmesh_dphi_dX(V,T);

    %Mass Matrix
    rho =  1000.0*ones(size(T,1),1);
    M = linear_tetmesh_mass_matrix(V,T, rho, vol);

    %material properties 
    YM = 7e6; %in Pascals
    pr =  0.45;
    [lambda, mu] = emu_to_lame(YM*ones(size(T,1),1), pr*ones(size(T,1),1));

    %boundary conditions are fun
    min_I = find(V(:,1) == min(V(:,1)));
    P = fixed_point_constraint_matrix(V, sort(min_I));

    %external forces
    gravity = [0 -9.8 0]'; % We are on krypton 
    gravity = P*M*repmat(gravity, size(V,1),1);

    %project mass matrix down
    M = P*M*P';

    %warm up the display
    [~,p] = nice_plot(V,F);

    %simulation setup and loop

    %time step
    dt = 0.01;

    qt = reshape(V', 3*size(V,1),1);

    %setup all thw variables I need using bc projection matrix
    b = qt - P'*P*qt;
    qt = P*qt;
    vt = 0*qt;

    options = optimoptions('fmincon');
    options.Algorithm = 'trust-region-reflective';
    options.Display = 'none';
    options.SpecifyObjectiveGradient = true;
    options.MaxIterations = 2;
    options.HessianFcn = 'objective';

    disp('Press SPACEBAR to CONTINUE');
    pause 

    h = text(0.5*(max(V(:,1)) + min(V(:,1))), 0.9*max(V(:,2)), num2str(0));
    h.FontSize = 28;

    % Neohookean
%     energy_func = @(a,b, c, d, e) linear_tetmesh_neohookean_q(a,b,c,d,e,[0.5*mu, 0.5*lambda]);
%     gradient_func = @(a,b, c, d, e) linear_tetmesh_neohookean_dq(a,b,c,d,e,[0.5*mu, 0.5*lambda]);
%     hessian_func = @(a,b, c, d, e) linear_tetmesh_neohookean_dq2(a,b,c,d,e,[0.5*mu, 0.5*lambda], 'fixed');
%     
    % StVK
%      energy_func = @(a,b, c, d, e) linear_tetmesh_stvk_q(a,b,c,d,e,[lambda, mu]);
%      gradient_func = @(a,b, c, d, e) linear_tetmesh_stvk_dq(a,b,c,d,e,[lambda, mu]);
%      hessian_func = @(a,b, c, d, e) linear_tetmesh_stvk_dq2(a,b,c,d,e,[lambda, mu], 'fixed');
    
    %Co-Rotational
%      energy_func = @(a,b, c, d, e) linear_tetmesh_corotational_q(a,b,c,d,e,[lambda, mu]);
%      gradient_func = @(a,b, c, d, e) linear_tetmesh_corotational_dq(a,b,c,d,e,[lambda, mu]);
%      hessian_func = @(a,b, c, d, e) linear_tetmesh_corotational_dq2(a,b,c,d,e,[lambda, mu], 'fixed');
% %      
    
    %ARAP
%     energy_func = @(a,b, c, d, e) linear_tetmesh_arap_q(a,b,c,d,e,[0.5*lambda, mu]);
%     gradient_func = @(a,b, c, d, e) linear_tetmesh_arap_dq(a,b,c,d,e,[0.5*lambda, mu]);
%     hessian_func = @(a,b, c, d, e) linear_tetmesh_arap_dq2(a,b,c,d,e,[0.5*lambda, mu], 'fixed');
    
    opt_func = @(vel) sim_function(vel, energy_func, gradient_func, hessian_func);
    for ti = 1:200
        h.String = num2str(ti);

        vt = fmincon(opt_func, 0*vt, [], [], [],[], [],[], [], options);
        qt = qt + dt*vt;

        p.Vertices = reshape(P'*qt + b, 3, size(V,1))';
        drawnow;
    end


    %objective needs to return energy, gradient and hessian values
    function [e, g, H] = sim_function(v, e_func, g_func, h_func)

        e = 0.5*v'*M*v - v'*M*vt + ...
            e_func(V,T, P'*(qt+dt*v)+b, dX, vol) - ...
            dt*v'*gravity; 

        if nargout > 1
            g = M*(v - vt) + ...
                dt*P*g_func(V,T, P'*(qt+dt*v)+b, dX, vol) + ...
                - dt*gravity;

            if nargout > 2
                H = M + dt*dt*P*h_func(V,T, P'*(qt+dt*v)+b, dX, vol)*P';
            end
        end
    end 

end


