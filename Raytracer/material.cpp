#include "material.hpp"
#include <string>
#include "../include/color.hpp"
#include <ostream>
#include <iostream>

material::material():
name_(),ka_(),kd_(),ks_(),m_(0)
{}

material::material(std::string const& s, color const& ka, color const& kd, color const& ks, float const& m):
name_(s), ka_(ka), kd_(kd), ks_(ks), m_(m)
{}

material::material(const material& orig):
name_(orig.name_), ka_(orig.ka_), kd_(orig.kd_), ks_(orig.ks_), m_(orig.m_)
{}

material::~material()
{}

std::ostream& operator<<(std::ostream& str, material const& mat)
{
    mat.print_on(str);
    return str;
}

void material::print_on(std::ostream& str) const
{
    str<<name_<<"   "<<std::endl<<ka_<<"   "<<kd_<<"   "<<ks_<<"   "<<m_;
}

std::string const& material::get_name() const
{
    return name_;
}

float const& material::get_m() const
{
    return m_;
}

color const& material::get_ka() const
{
    return ka_;
}

color const& material::get_kd() const
{
    return kd_;
}

color const& material::get_ks() const
{
    return ks_;
}
