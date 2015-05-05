#ifndef RAY_INFO_HPP
#define	RAY_INFO_HPP

#include "../include/vector.hpp"

struct ray_info{
    bool hit;
    double t;
    math3d::vector n;
};

#endif	/* RAY_INFO_HPP */

