#ifndef SHAPE_HPP
#define	SHAPE_HPP
#include "../include/point.hpp"
#include <ostream>
#include <string>
#include "material.hpp"
#include "ray_info.hpp"

class shape {
public:
    shape();
    shape(std::string const&,material const&);
    shape(shape const& orig);
    virtual ~shape();

    virtual bool is_inside(math3d::point const&) const = 0;
    virtual ray_info intersect(math3d::point const&, math3d::vector const&) const=0;
//    virtual void scale(math3d::vector const&) const=0;
//    virtual void transform(math3d::vector const&) const=0;
//    virtual void rotatex(double const&) const=0;
//    virtual void rotatey(double const&) const=0;
//    virtual void rotatez(double const&) const=0;
    virtual void print_on(std::ostream&)const;
    std::string get_name()const;
    material get_material() const;
    void set_name(std::string const&);
    void set_material(material const&);
private:
    std::string name_;
    material mat_;
};

std::ostream& operator<<(std::ostream& str , shape const& s);

#endif	/* SHAPE_HPP */


