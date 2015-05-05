#ifndef BOX_HPP
#define	BOX_HPP

#include <iostream>
#include <string>
#include "material.hpp"
#include "../include/point.hpp"
#include "shape.hpp"
#include "ray_info.hpp"
#include "../include/matrix.hpp"

class box:public shape {
public:
    box();
    box(math3d::point const&, math3d::point const&, std::string const&, material const&);
    box(const box& orig);
    virtual ~box();
    /*---*/
    bool is_inside(math3d::point const&)const;
    ray_info intersect(math3d::point const&, math3d::vector const&) const;
    void scale(math3d::vector const&);
    void transform(math3d::vector const&);
    void rotatex(double const&);
    void rotatey(double const&);
    void rotatez(double const&);
    /*---*/
    void print_on(std::ostream&) const;
    math3d::point const& findmin(math3d::point const&);
    math3d::point const& findmax(math3d::point const&);

private:
    math3d::point a_,b_,c_,d_,e_,f_,g_,h_,mitte_;
    math3d::matrix xrot,yrot,zrot;
    double xw,yw,zw;


    //     h--------g
    //    /|       /|
    //   / |      / |
    //  e--------f  |
    //  |  d-----|--c
    //  | /      | /
    //  |/       |/
    //  a--------b
};

#endif	/* BOX_HPP */

