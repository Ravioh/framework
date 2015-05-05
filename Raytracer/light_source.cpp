#include "light_source.hpp"
#include "../include/color.hpp"
#include "../include/point.hpp"
#include <string>
#include <ostream>

light_source::light_source():
position_(),la_(),ld_(),name_()
{}

light_source::light_source(std::string const& name , math3d::point const& p, color const& la, color const& ld):
position_(p), la_(la), ld_(ld), name_(name)
{}

light_source::light_source(const light_source& orig):
position_(orig.position_), la_(orig.la_), ld_(orig.ld_), name_(orig.name_)
{}

light_source::~light_source()
{}

std::ostream& operator<<(std::ostream& str, light_source const& ls)
{
    ls.print_on(str);
    return str;
}

void light_source::print_on(std::ostream& str) const
{
    str<<name_<<":   "<<position_<<"   "<<la_<<"   "<<ld_;
}

math3d::point light_source::get_pos() const
{
    return position_;
}

color light_source::get_la() const
{
    return la_;
}

color light_source::get_ld() const
{
    return ld_;
}