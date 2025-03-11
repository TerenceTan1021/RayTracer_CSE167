#include "GeomSphere.h"

#include <iostream>
#include <utility>
//debugging
#include <glm/gtx/string_cast.hpp>
#include "Intersection.h"
#include "Ray.h"

std::vector<Intersection> GeomSphere::intersect(Ray &ray) {
    /**
     * NOTE: Ray is already transformed to the Model coordinate space.
     */
    using namespace glm;

    // vector to store the intersections
    std::vector<Intersection> intersections;

    /**
     * TODO: Implement the Ray intersection with the current geometry
     */

    /**
     * Once you find the intersection, add it to the `intersections` vector.
     *
     * Example:
     * Suppose the ray intersects the current geometry at a point `vec3 point`
     * at a distance `float t`, and the unit normal vector at the intersection
     * point is `vec3 normal`. You would then insert an intersection into the
     * vector as follows:
     *
     * intersections.push_back({t, point, normal, this, nullptr});
     *
     * Note:
     * - Here we pass the Model pointer as `nullptr` because it will be
     *   populated by the Model::intersect() function call.
     * - Only add intersections that are in front of the camera, i.e.,
     *   where t > 0.
     */

    //Sphere center and radius
    vec3 c = this->center;
    float r = this->radius;

    //ray dir and Source
    vec3 d = ray.dir;
    vec3 p_0 = ray.p0;

    //t formula broken into 4 parts
    vec3 pc = p_0 - c;
    float tempA = dot(-d, pc);

    //inside the sqrt
    float tempB = dot(d, pc) * dot(d, pc);      //(d * (p_0 - c))^2
    float tempC = dot(pc, pc);                  //(p_0 - c)^2
    float tempD = pow(r, 2);                    //r^2

    float section = tempB - tempC + tempD;


    //if the expression in sqrt is negative --> no intersection
    if(section < 0.0f){
        return intersections;
    }
    //if the expression in sqrt is a zero --> tangent
    else if(section == 0.0f){
        float t = tempA;
        if(t > 0.0f){
            vec3 q = p_0 + (t * d);
            vec3 n = normalize(q - c);
            intersections.push_back({t, q, n, this, nullptr});
        }
    }
     /*
    if the expression in sqrt is positive --> two intersections
                                          --> take smallest pos t
    */
    else if(section > 0.0f){
        //calculate the two t values
        float sqrt_section = sqrt(section);

        float t1 = tempA + sqrt_section;
        float t2 = tempA - sqrt_section;

        //take in the smalest positve t
        if((t1 < t2) && (t1 > 0.0f)){
            vec3 q = p_0 + (t1 * d);
            vec3 n = normalize(q - c);
            intersections.push_back({t1, q, n, this, nullptr});
        }
        if((t2 < t1) && (t2 > 0.0f)){
            vec3 q = p_0 + (t2 * d);
            vec3 n = normalize(q - c);
            intersections.push_back({t2, q, n, this, nullptr});
        }
    }

    /**
     * TODO: Update `intersections`
     */
    return intersections;
};