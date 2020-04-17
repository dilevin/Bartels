function n = per_facet_normals(V,T)

    v = cross(V(T(:, 2), :) - V(T(:, 1), :), V(T(:, 3), :) - V(T(:, 1), :), 2);
    mag_v = sqrt(sum(v.*v,2));
    n = diag(1./mag_v)*v;

end
