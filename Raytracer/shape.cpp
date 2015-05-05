#include "shape.hpp"
#include <ostream>
#include <string>
#include "../include/color.hpp"
#include <iostream>

shape::shape():
name_("unknown"),mat_()
{}

shape::shape(std::string const& s,material const& mat):
name_(s),mat_(mat)
{}

shape::shape(shape const& orig):
name_(orig.name_),mat_(orig.mat_)
{}

shape::~shape()
{}

material shape::get_material() const
{
    return mat_;
}

std::string shape::get_name() const
{
    return name_;
}

void shape::set_name(std::string const& s)
{
    name_=s;
}

void shape::set_material(material const& mat)
{
    mat_=mat;
}

void shape::print_on(std::ostream& str) const
{
    str<<"name_: "<<name_<<std::endl<<"mat_: "<<mat_;
}

std::ostream& operator<<(std::ostream& str , shape const& s)
{
    s.print_on(str);
    return str;
}
