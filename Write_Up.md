# RayTracer Write Up

### Before Implementation
---
The Image produce when executing the file, should produce a blue screen before any implementations

<img src="images/before.png" alt="image" width="300"/>

### Task 1 & Task 3
---
Located in: *src/scenes/RayTracer.cpp*

`Ray RayTracer::ray_thru_pixel(int i, int j)`

**Math Behind it**

The pixel (i, j) can be defined with

> (2 * ((i + 0.5) / width) - 1, 1 - 2 * ((j + 0.5)/ height))

to get a random point, we can replace 0.5 with any value between [0,1]


`x,y = [0,1]`

>> (2 * ((i + x) / width) - 1, 1 - 2 * ((j + x)/ height))

This is implemented for Task 3, this allows us to change the first args `<int: samples_per_pixel>`
to a higher value to minimize noise:

<img src="images/Task3.png" alt="image" width="300"/>

 to which we can define:

> alpha = 2 * ((i + 0.5) / width) - 1
>
> beta = 1 - 2 * ((j + 0.5)/ height)

calculating this, allows us to use these variables to calculate the ray direction with the formula

> normalize(alpha *  a * (tan(fovy/2) * u) + beta * (tan(fovy/2) * v) - w);

where:
- a is the aspect/(width/height)
- u,v,w are vec3 of the Camera Matrix

After implementation yields:

<img src="images/Task1.png" alt="image" width="300"/>

### Task 2.1 & 2.2
---

Located in: *src/geometries/GeomSphere.cpp*

`Function: vector<Intersection> GeomSphere::intersect(Ray &ray)`

**Math Behind it**

variables:
- c: sphere center
- r: sphere radius
- p_0: ray Source
- d: ray direction
  

this funtion follow the sphere intersection quadratic equation for finding the sphere intersect:

> ||p_0 + td - c||^2 = r^2

to find t, we need to find where the point lies on the sphere, the point only lies on the sphere if and only if: 

> (q - c) * (q -c) = r^2

subsituting the formulas gives us:

> (p_0 + td - c) * (p_0 + td - c) = r^2

Expand:

>|d|^2t^2 + 2d * (p_0 - c)t + |p_0 = c|^2 - r^2 = 0 , 
where ==|d|^2 = 1, because of normalization==

> t^2 + 2d * (p_0 - c)t + |p_0 = c|^2 - r^2 = 0

which gives us:

> t = -d * (p_0 - c) +- sqrt((d * (p_0 - c))^2 - |p_0 - c|^2 + r^2)

where if the expression within the sqrt is
  - negative: there is no intersection
  - 0 : there is only one intersection(tangent)
  - positive: there are two instersection, and we put plus in the smallest positive t value.

after finding the intersection, we would then find the point posiiton and the Normal:

> Point position: q = p_0 + td
>
> Normal: normalize(q - c)

Image produced after Implemetation:

<img src="images/Task2.1.png" alt="image" width="300"/>



