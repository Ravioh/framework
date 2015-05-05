#ifndef LIGHT_SOURCE_HPP
#define	LIGHT_SOURCE_HPP

#include "../include/point.hpp"
#include "../include/color.hpp"
#include <string>
#include <ostream>

class light_source {
public:
    light_source();
    light_source(std::string const&,math3d::point const&, color const&, color const&);
    light_source(const light_source& orig);
    virtual~ light_source();

    void print_on(std::ostream& str) const;
    math3d::point get_pos()const;
    color get_la()const;
    color get_ld()const;

private:
    std::string name_;
    math3d::point position_;
    color la_;
    color ld_;

};

std::ostream& operator<<(std::ostream& str, light_source const& ls);

#endif	/* LIGHT_SOURCE_HPP */

