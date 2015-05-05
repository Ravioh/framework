#include "box.hpp"
#include "shape.hpp"
#include <cmath>
#include <iostream>
#include <assert.h>
#include "ray_info.hpp"
#include "../include/matrix.hpp"

box::box():
shape(), a_(math3d::point(0,0,0)), g_(math3d::point(1,1,1)),
b_(math3d::point(1,0,0)),
c_(math3d::point(0,1,0)),
d_(math3d::point(1,0,0)),
e_(math3d::point(0,0,1)),
f_(math3d::point(0,1,1)),
h_(math3d::point(1,0,1)),
mitte_(.5,.5,.5)
{}

box::box(math3d::point const& a, math3d::point const& g, std::string const& name, material const& mat):
shape(name,mat), a_(a), g_(g),
b_(math3d::point (a_[0],g_[1],a_[0])),
c_(math3d::point (g_[0],g_[1],a_[0])),
d_(math3d::point (g_[0],a_[1],a_[0])),
e_(math3d::point (a_[0],a_[1],g_[0])),
f_(math3d::point (a_[0],g_[1],g_[0])),
h_(math3d::point (g_[0],a_[1],g_[0])),
mitte_(g_[0]/2,g_[1]/2,g_[2]/2)
{}

box::box(const box& orig):
shape(orig),a_(orig.a_),g_(orig.g_),b_(orig.b_),c_(orig.c_),d_(orig.d_),e_(orig.e_),f_(orig.f_),h_(orig.h_),mitte_(orig.mitte_)
{}

box::~box() {
}

/*---------------------------------*/
template <class T> void swap ( T& a, T& b )
{
  T c(a); a=b; b=c;
}
/*---------------------------------*/

bool box::is_inside(math3d::point const& p) const
{
    math3d::point g=g_;
    math3d::point a=a_;
    if (p[0]>g[0] || p[0]<a[0]) return false;
    if (p[1]>g[1] || p[1]<a[1]) return false;
    if (p[2]>g[2] || p[2]<a[2]) return false;

    return true;
}
void box::print_on(std::ostream& str) const
{
    shape::print_on(str);
    str<<a_<<", "<<b_<<", "<<c_<<", "<<d_<<", "<<e_<<", "<<f_<<", "<<g_<<", "<<h_<<std::endl;
}

 ray_info box::intersect(math3d::point const& p0, math3d::vector const& v0) const
{
//    p0=p0*xrot;
//    p0=p0*yrot;
//    p0=p0*zrot;
//    v0=v0*xrot;
//    v0=v0*yrot;
//    v0=v0*zrot;
//    float t1, t2, tmp;
//    float tfar = 0;
//    float tnear = 0;
//    math3d::point pmin = box::findmin(p0);
//    math3d::point pmax = box::findmax(p0);
//    ray_info returnv;
//    returnv.hit=true;
//
//
//    if (v0[0] == 0)
//    {
//        if (v0[0] > pmax[0] || p0[0] < pmin[0])
//        {
//            returnv.hit = false;
//            return returnv;
//        }
//    }
//    else
//    {
//        tmp = 1.0 / v0[0];
//        t1 = (pmin[0] - p0[0]) * tmp;
//        t2 = (pmax[0] - p0[0]) * tmp;
//        if (t1 > t2)    {swap(t1, t2);}
//        if (t1 > tnear) tnear = t1;
//        if (t2 < tfar) tfar = t2;
//        if (tnear > tfar || tfar < 0.0)
//        {
//            returnv.hit = false;
//            return returnv;
//        }
//    }
//
//    if (v0[1] == 0)
//    {
//        if (p0[1] > pmax[1] || p0[1] < pmin[1])
//        {
//            returnv.hit = false;
//            return returnv;
//        }
//    }
//    else
//    {
//        tmp = 1.0 / v0[1];
//        t1 = (pmin[1] - p0[1]) * tmp;
//        t2 = (pmax[2] - p0[1]) * tmp;
//        if (t1 > t2){swap(t1, t2);}
//        if (t1 > tnear) tnear = t1;
//        if (t2 < tfar) tfar = t2;
//        if (tnear > tfar || tfar < 0)
//        {
//            returnv.hit = false;
//            return returnv;
//        }
//    }
//
//    if (v0[2] == 0)
//    {
//        if (p0[2] > pmax[2] || p0[2] < pmin[2])
//        {
//            returnv.hit = false;
//            return returnv;
//        }
//    }
//    else
//    {
//        tmp = 1.0 / v0[2];
//        t1 = (pmin[2] - p0[2]) * tmp;
//        t2 = (pmax[2] - p0[2]) * tmp;
//        if (t1 > t2){swap(t1, t2);}
//        if (t1 > tnear) tnear = t1;
//        if (t2 < tfar) tfar = t2;
//        if (tnear > tfar || tfar < 0)
//        {
//            returnv.hit = false;
//            return returnv;
//        }
//    }
//    if (tnear > 0)
//    {
//        returnv.t = tnear;
//        return returnv;
//    }
//    else
//    {
//        returnv.t = tfar;
//        return returnv;
//    }
}


math3d::point const& box::findmin(math3d::point const& p0)
{
    math3d::vector v1(p0,a_);
    math3d::point pc = a_;
    double tc = v1.length();

    math3d::vector v2(p0,b_);
    if (v2.length() < tc){ pc = b_; tc = v2.length();}

    math3d::vector v3(p0,c_);
    if (v3.length() < tc){ pc = c_; tc = v3.length();}

    math3d::vector v4(p0,d_);
    if (v4.length() < tc){ pc = d_; tc = v4.length();}

    math3d::vector v5(p0,e_);
    if (v5.length() < tc){ pc = e_; tc = v5.length();}

    math3d::vector v6(p0,f_);
    if (v6.length() < tc){ pc = f_; tc = v6.length();}

    math3d::vector v7(p0,g_);
    if (v7.length() < tc){ pc = g_; tc = v7.length();}

    math3d::vector v8(p0,h_);
    if (v8.length() < tc){ pc = h_; tc = v8.length();}

    return pc;
}

math3d::point const& box::findmax(math3d::point const& p0)
{
    math3d::vector v1(p0,a_);
    math3d::point pc;
    pc = a_;
    double tc = v1.length();

    math3d::vector v2(p0,b_);
    if (v2.length() > tc){ pc = b_; tc = v2.length();}

    math3d::vector v3(p0,c_);
    if (v3.length() > tc){ pc = c_; tc = v3.length();}

    math3d::vector v4(p0,d_);
    if (v4.length() > tc){ pc = d_; tc = v4.length();}

    math3d::vector v5(p0,e_);
    if (v5.length() > tc){ pc = e_; tc = v5.length();}

    math3d::vector v6(p0,f_);
    if (v6.length() > tc){ pc = f_; tc = v6.length();}

    math3d::vector v7(p0,g_);
    if (v7.length() > tc){ pc = g_; tc = v7.length();}

    math3d::vector v8(p0,h_);
    if (v8.length() > tc){ pc = h_; tc = v8.length();}

    return pc;
}

void box::scale(math3d::vector const& v0)
{
    math3d::matrix m0 = math3d::make_scale(v0);
    a_=m0*a_;
    b_=m0*b_;
    c_=m0*c_;
    d_=m0*d_;
    e_=m0*e_;
    f_=m0*f_;
    g_=m0*g_;
    h_=m0*h_;
    mitte_=m0*mitte_;
}

void box::transform(math3d::vector const& v0)
{
    double a0[16]={1.0,.0,v0[0],.0,1.0,.0,v0[1],.0,.0,1.0,v0[2],.0,.0,.0,1.0};
    math3d::matrix m1(a0);
    a_=m1*a_;
    b_=m1*b_;
    c_=m1*c_;
    d_=m1*d_;
    e_=m1*e_;
    f_=m1*f_;
    g_=m1*g_;
    h_=m1*h_;
    mitte_=m1*mitte_;
}

void box::rotatex(double const& w)
{
    xrot = math3d::make_rotation_x(w);
    xw=w;
}

void box::rotatey(double const& w)
{
    yrot = math3d::make_rotation_y(w);
    yw=w;
}

void box::rotatez(double const& w)
{
    zrot = math3d::make_rotation_z(w);
    zw=w;
}
