x1 = 200;
x2 = 155;
y1 = 107;
y2 = 107;
sweepline = 117;
p1 = sweepline - y1;
p2 = sweepline - y2;
a = p2 - p1;
b = (2*p1*x2-2*p2*x1);
c = p2*x1*x1 - p1*x2*x2 + 2*p1*p2*y2 - 2*p1*p2*y1 - p1*p1*p2 + p1*p2*p2;
if a==0
    x = -c/b
else
    x_ = (-b+sqrt(b*b-4*a*c))/2/a
    x = (-b-sqrt(b*b-4*a*c))/2/a
end
%{ 
error but the result is beautiful
figure
for i=1:0.1:500
    hold on
    val1 = -(i-x1)*(i-x1)/2/p1+y1+p1/2;
    val2 = -(i+0.1-x1)*(i+0.1-x1)/2/p2+y2+p2/2;
    plot([i i+0.1],[val1 val2],'r');
end
%}

figure
for i=1:0.1:500
    hold on
    val1 = -(i-x1)*(i-x1)/2/p1+y1+p1/2;
    val2 = -(i+0.1-x1)*(i+0.1-x1)/2/p1+y1+p1/2;
    plot([i i+0.1],[val1 val2],'r');
end
for i=1:0.1:500
    hold on
    val1 = -(i-x2)*(i-x2)/2/p2+y2+p2/2;
    val2 = -(i+0.1-x2)*(i+0.1-x2)/2/p2+y2+p2/2;
    plot([i i+0.1],[val1 val2],'b');
end


