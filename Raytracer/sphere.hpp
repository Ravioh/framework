#ifndef SPHERE_HPP
#define	SPHERE_HPP

#include "../include/point.hpp"
#include "shape.hpp"
#include <iostream>
#include <string>
#include "material.hpp"
#include "ray_info.hpp"

class sphere:public shape {
public:
    sphere();
    sphere(math3d::point const& m, double const& r, std::string const&, material const& mat);
    sphere(const sphere& orig);
    virtual ~sphere();
    /*---*/
    bool is_inside(math3d::point const& p) const;
    ray_info intersect(math3d::point const&, math3d::vector const&) const;
    void scale(math3d::vector const&);
    void transform(math3d::vector const&);
    void rotatex(double const&)const;
    void rotatey(double const&)const;
    void rotatez(double const&)const;
    void print_on(std::ostream&) const;
    math3d::point getmiddle() const;
    double getradius() const;

private:
    math3d::point middle_;
    double radius_;
};

#endif	/* SPHERE_HPP */

