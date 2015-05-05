#include "camera.hpp"
#include "point.hpp"

camera::camera() :
pos_(math3d::point(0,0,0)),dir_(math3d::vector(0,0,-1)),name_("eye"),fov_(45)
{}

camera::camera(std::string const& name, double const& fov):
name_(name),fov_(fov), pos_(math3d::point(0,0,0)),dir_(math3d::vector(0,0,-1))
{}

camera::camera(const camera& orig) :
pos_(orig.pos_),dir_(orig.dir_), name_(orig.name_), fov_(orig.fov_)
{}

camera::~camera() {
}

math3d::point const& camera::get_position() const
{
    return pos_;
}

math3d::vector const& camera::get_direction() const
{
    return dir_;
}

std::string const& camera::get_name() const
{
    return name_;
}

double const& camera::get_fov() const
{
    return fov_;
}

void camera::set_direction(math3d::vector const& p)
{
    dir_=p;
}

void camera::set_position(math3d::point const& p)
{
    pos_=p;
}

void camera::set_fov(double const& f)
{
    fov_=f;
}

void camera::set_name(std::string const& n)
{
    name_=n;
}
