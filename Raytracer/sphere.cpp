#include "sphere.hpp"
#include "shape.hpp"
#include <string>
#include <cmath>
#include <iostream>
#include "material.hpp"
#include "../include/point.hpp"
#include "../include/vector.hpp"
#include "ray_info.hpp"
#include "../include/matrix.hpp"

sphere::sphere() :
shape(), middle_(), radius_(1) {
}

sphere::sphere(math3d::point const& m, double const& r, std::string const& name, material const& mat) :
shape(name, mat), middle_(m), radius_(r) {
}

sphere::sphere(const sphere& orig) :
shape(orig), middle_(orig.middle_), radius_(orig.radius_) {
}

sphere::~sphere() {
}

bool sphere::is_inside(math3d::point const& p) const {
    return (sqrt(pow((middle_[0] - p[0]), 2) + pow(middle_[1] - p[1], 2) + pow(middle_[2] - p[2], 2))) <= radius_;
}

math3d::point sphere::getmiddle() const {
    return middle_;
}

double sphere::getradius() const {
    return radius_;
}

void sphere::print_on(std::ostream& str) const {
    shape::print_on(str);
    str << "middle_: " << middle_ << std::endl << "radius_: " << radius_ << std::endl;
}

ray_info sphere::intersect(math3d::point const& p, math3d::vector const& v) const {
    ray_info rv;
    //math3d::vector (fuß,kopf)
    math3d::vector l(p, middle_);
    math3d::vector ray = v;
    ray = ray.normalize();
    double rad_square = pow(radius_, 2);
    double s = ((l[0] * ray[0])+(l[1] * ray[1])+(l[2] * ray[2]));
    double l_square = ((l[0] * l[0])+(l[1] * l[1])+(l[2] * l[2]));

    if (s < 0) {
        if (l_square > rad_square) {
            rv.hit = false;
            return rv;
        }
    } else {
        double m_square = l_square - pow(s, 2);
        if (m_square > pow(radius_, 2)) {
            rv.hit = false;
            return rv;
        } else {
            double q = sqrt((rad_square - m_square));
            if (l_square > rad_square) {
                double t1 = (s - q);
                rv.hit = true;
                rv.t = t1;
                math3d::point hit = p+ray*rv.t;
                math3d::vector hilf(middle_,hit);
                rv.n=hilf;
//                std::cout<<hit<<std::endl;
                return rv;
            } else {
                double t2 = (s + q);
                rv.hit = true;
                rv.t = t2;
                math3d::point hit = p+ray*rv.t;
                math3d::vector hilf(middle_,hit);
                rv.n=hilf;
                return rv;
            }
        }
    }
}

void sphere::rotatex(double const& w) const {
}

void sphere::rotatey(double const& w) const {
}

void sphere::rotatez(double const& w) const {
}

void sphere::transform(math3d::vector const& v0) {
    double a0[16] = {1.0, .0, v0[0], .0, 1.0, .0, v0[1], .0, .0, 1.0, v0[2], .0, .0, .0, 1.0};
    math3d::matrix m1(a0);
    middle_ = m1*middle_;
}

void sphere::scale(math3d::vector const& v0) {
    radius_ = radius_ + v0.length();
}
