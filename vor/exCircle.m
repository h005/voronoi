function center = exCircle(points)
c = [points(1,:),1
    points(2,:),1
    points(3,:),1];
c = 2*det(c);
a = [points(1,1)*points(1,1)+points(1,2)*points(1,2) points(1,2) 1
    points(2,1)*points(2,1)+points(2,2)*points(2,2) points(2,2) 1
    points(3,1)*points(3,1)+points(3,2)*points(3,2) points(3,2) 1];
b = [points(1,1) points(1,1)*points(1,1)+points(1,2)*points(1,2) 1
    points(2,1) points(2,1)*points(2,1)+points(2,2)*points(2,2) 1
    points(3,1) points(3,1)*points(3,1)+points(3,2)*points(3,2) 1];
center = [det(a),det(b)]/c;
