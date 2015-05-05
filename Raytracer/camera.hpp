#ifndef CAMERA_HPP
#define	CAMERA_HPP

#include <string>
#include "../include/point.hpp"
#include "../include/vector.hpp"


class camera {
public:
    camera();
    camera(std::string const&, double const&);
    camera(const camera& orig);
    virtual ~camera();

    math3d::point const& get_position() const;
    math3d::vector const& get_direction() const;
    std::string const& get_name() const;
    double const& get_fov() const;

    void set_position(math3d::point const&);
    void set_direction(math3d::vector const&);
    void set_fov(double const&);
    void set_name(std::string const&);
private:
    math3d::point pos_;
    math3d::vector dir_;
    double fov_;
    std::string name_;
};

#endif	/* CAMERA_HPP */

