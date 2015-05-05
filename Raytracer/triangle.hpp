#ifndef TRIANGLE_HPP
#define	TRIANGLE_HPP
#include "../include/point.hpp"
#include "material.hpp"
#include "shape.hpp"

class triangle:public shape {
public:
    triangle();
    triangle(math3d::point const& A,math3d::point const& B,math3d::point const& C, std::string const&, material const&);
    triangle(const triangle& orig);
    virtual ~triangle();
    /*---*/
    bool is_inside (math3d::point const&) const;

private:
    math3d::point a_;
    math3d::point b_;
    math3d::point c_;

};

#endif	/* TRIANGLE_HPP */

