points = [   
   122   50
   155   107
   143   118
   140   117
   200   107];
voronoi(points(:,1),500-points(:,2))
axis([0 500 0 500])
triPoints = [
    points(2,:)
    points(4,:)
    points(5,:)
    ];
exCircle(triPoints)