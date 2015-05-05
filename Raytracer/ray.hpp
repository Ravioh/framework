#ifndef RAY_HPP
#define	RAY_HPP

#include "../include/vector.hpp"
#include "../include/point.hpp"
#include "../include/color.hpp"
#include <list>
#include "shape.hpp"
#include "light_source.hpp"

class ray {
public:
    ray();
    ray(math3d::point const&, math3d::point const&);
    ray(const ray& orig);
    virtual ~ray();

    color intersection(std::list<shape*> const&,std::list<light_source> const&);
    color calcclr(ray_info const& ,shape* const&,std::list<shape*> const&,std::list<light_source> const&);

private:
    math3d::vector direction_;
    math3d::point source_;
    color color_;
};

#endif	/* RAY_HPP */

