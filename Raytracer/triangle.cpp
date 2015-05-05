#include "triangle.hpp"
#include "../include/point.hpp"
#include "material.hpp"
#include "shape.hpp"

triangle::triangle():
shape(),a_(),b_(),c_()
{}

triangle::triangle(math3d::point const& A, math3d::point const& B, math3d::point const& C, std::string const& name, material const& mat):
shape(name,mat),a_(A),b_(B),c_(C)
{}

triangle::triangle(const triangle& orig):
shape(orig),a_(orig.a_),b_(orig.b_),c_(orig.c_)
{}

triangle::~triangle() {
}

bool triangle::is_inside(math3d::point const& p) const
{

}
