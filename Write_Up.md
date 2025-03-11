RayTracer.cpp




src/geometries/GeomSphere.cpp

Function: vector<Intersection> GeomSphere::ntersect(Ray &ray)

variables:
- c: sphere center
- r: sphere radius
- p_0: ray Source
- d: ray direction
- 
this funtion follow the sphere intersection quadratic equation for finding the sphere intersect:

||r_o + tr_d - c||^2 = R^2

to find t, we need to find where the point lies on the sphere, the point only lies on the sphere if and only if: (q - c) * (q -c) = r^2

subsituting the formulas gives us:

(p_0 + td - c) * (p_0 + td - c) = r^2

Expand:

|d|^2t^2 + 2d * (p_0 - c)t + |p_0 = c|^2 - r^2 = 0,
where |d|^2 = 1, because of normalization

t^2 + 2d * (p_0 - c)t + |p_0 = c|^2 - r^2 = 0

which gives us:

t = -d * (p_0 - c) +- sqrt((d * (p_0 - c))^2 - |p_0 - c|^2 + r^2)

where if the expression within the sqrt is
  - negative: there is no intersection
  - 0 : there is only one intersection(tangent)
  - positive: there are two instersection, and we put plus in the smallest positive t value.

after finding the intersection, we would then find the point posiiton and the Normal:

Point position: q = p_0 + td
Normal: normalize(q - c)

Image produced after Implemetation:
![image](images/Task2.1.png)



