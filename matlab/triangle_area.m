function a = triangle_area(V,F)

    dx1 = V(F(:,2),:) - V(F(:,1),:);
    dx2 = V(F(:,3),:) - V(F(:,1),:);

    a = 0.5*(dx1(:,1).*dx2(:,2) - dx1(:,2).*dx2(:,1)); 

end