#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include "GeomTriangle.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "Intersection.h"
#include "Ray.h"

GeomTriangle::GeomTriangle(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals) {
    this->vertices[0] = vertices[0];
    this->vertices[1] = vertices[1];
    this->vertices[2] = vertices[2];

    this->normals[0] = normals[0];
    this->normals[1] = normals[1];
    this->normals[2] = normals[2];
}

std::vector<Intersection> GeomTriangle::intersect(Ray &ray) {
    using namespace glm;
    /**
     * NOTE: Ray is already transformed to the Model coordinate space.
     */

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
    //ray dir and Source
     vec3 d = ray.dir;
     vec3 p_0  = ray.p0;


     //points of the triangle
    vec3 p1 = vertices[0];
    vec3 p2 = vertices[1];
    vec3 p3 = vertices[2];

     mat4 A = mat4(
         vec4(p1, 1.0f),
         vec4(p2, 1.0f),
         vec4(p3, 1.0f),
         vec4(-d, 0.0f)
     ); 

     vec4 C = vec4(p_0, 1.0f);

     //sovle for the coefficients and t
     vec4 D = inverse(A) * C;

    float coef1 = D.x;
    float coef2 = D.y;
    float coef3 = D.z;
    float t = D.w;

    vec3 n1 = normals[0];
    vec3 n2 = normals[1];
    vec3 n3 = normals[2];

    if(coef1 >= 0.0f && coef2 >= 0.0f && coef3 >= 0.0f && t >= 0.0f){
        vec3 p = (p1 * coef1) + (p2 * coef2) + (p3 * coef3);
        vec3 n = normalize((coef1 * n1) + (coef2 * n2) + (coef3 * n3));
        intersections.push_back({t, p, n, this, nullptr});
    }
    /**
     * TODO: Update `intersections`
     */
    return intersections;
}