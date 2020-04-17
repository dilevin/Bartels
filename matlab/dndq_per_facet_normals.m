S
function dndq = dndq_per_facet_normals(V,T)

    v = cross(V(T(:, 2), :) - V(T(:, 1), :), V(T(:, 3), :) - V(T(:, 1), :), 2);
    mag_v = sqrt(sum(v.*v,2));
    n = diag(1./mag_v)*v;
    
    %lazy compute normal derivatives
    dndq = zeros(size(T,1), 27);

    D1 = [-eye(3,3) eye(3,3) zeros(3,3)];
    D2 = [-eye(3,3), zeros(3,3), eye(3,3)];

    %mag_v is magnitude of unnormalized normal
    for jj = 1:size(T,1)

        dndq_mat = (eye(3) - n(jj,:)'*n(jj,:))./mag_v(jj);
        dndq_mat = dndq_mat*((cross(D1', repmat((D2*reshape(V(T(jj,:),:)',9, 1))',9,1),2))' - (cross(D2', repmat((D1*reshape(V(T(jj,:),:)',9, 1))',9,1),2))');
        dndq(jj,:) = dndq_mat(:);
    end

end
