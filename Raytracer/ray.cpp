#include "ray.hpp"
#include <list>
#include <map>
#include <cmath>
#include <iterator>
#include "ray_info.hpp"
#include "scene.hpp"
#include <iostream>

ray::ray():
direction_(),source_(),color_()
{}

ray::ray(math3d::point const& p1, math3d::point const& p2):
source_(p1),direction_(p1,p2)
{}

ray::ray(ray const& orig):
direction_(orig.direction_), source_(orig.source_), color_(orig.color_)
{}

ray::~ray()
{}

color ray::intersection(std::list<shape*> const& ls,std::list<light_source> const& lls)
{
    shape* closest;
    ray_info closesd;
    closesd.t = INFINITY;
    bool hit=false;

    for(std::list<shape*>::const_iterator i = ls.begin(); i!=ls.end();++i)
    {
        ray_info erg = (*i)->intersect(source_,direction_);
        if (erg.hit == true && erg.t < closesd.t)
        {
            closest = *i;
            closesd = erg;
            hit=true;
        }
    }
    //if no hit
    if (hit != true)
    {
        return lls.front().get_la();
    }
    //if something was hit
    else
    {
//        direction_=direction_.normalize();
//        math3d::point hit= math3d::point(source_+direction_*closesd.t);
        return calcclr(closesd,closest,ls,lls);
//        return color(0.5,.5,.5);
    }

}

color ray::calcclr(ray_info const& hitinfo, shape* const& s,std::list<shape*> const& lls,std::list<light_source> const& ls)
{
    math3d::point hitp(source_+direction_*hitinfo.t);
    color result(0, 0, 0);
    color ka = s->get_material().get_ka();
    color kd = s->get_material().get_kd();
    color ks = s->get_material().get_ks();
    color la, ld;
    result[0] += ka[0] * ls.front().get_la()[0];
    result[1] += ka[1] * ls.front().get_la()[1];
    result[2] += ka[2] * ls.front().get_la()[2];
    for (std::list<light_source>::const_iterator i = ls.begin(); i != ls.end(); ++i)
    {
        la = i->get_la();
        ld = i->get_ld();
        math3d::vector n = hitinfo.n;
        n = n.normalize();
        math3d::vector l(hitp, i->get_pos());
        math3d::vector v0=l.normalize();
        double diffuse = n[0] * l[0] + n[1] * l[1] + n[2] * l[2];
        math3d::vector v(math3d::vector(hitp, source_));
        v = v.normalize();
        bool obstacle = false;
        for (std::list<shape*>::const_iterator j = lls.begin(); j != lls.end(); ++j)
        {
            if (*j == s) {continue;}
            ray_info hitabf = (*j)->intersect(hitp, l);
            math3d::vector hitobj(math3d::point(source_+direction_*hitabf.t),i->get_pos());
            if (hitabf.hit == true)
            {
                if (hitabf.t>0 && hitabf.t < hitinfo.t)
                {
                    obstacle = true;
                    break;
                }
            }
        }
        if (hindernis == false)
        {

            if (diffuse > 0)
            {
                result[0] += (kd[0] * ld[0]) * diffuse;
                result[1] += (kd[1] * ld[1]) * diffuse;
                result[2] += (kd[2] * ld[2]) * diffuse;
            }

            math3d::vector r(math3d::vector((2 * (n[0] * v0[0] + n[1] * v0[1] + n[2] * v0[2]) * n) - v0));
            r = r.normalize();
            double specular = r[0] * v[0] + r[1] * v[1] + r[2] * v[2];
            if (specular > 0)
            {
                result[0] += (ks[0] * ld[0]) * pow(specular, (s->get_material().get_m()));
                result[1] += (ks[1] * ld[1]) * pow(specular, (s->get_material().get_m()));
                result[2] += (ks[2] * ld[2]) * pow(specular, (s->get_material().get_m()));
            }
        }
        //        if (s->get_material().get_ks() != color(0, 0, 0) && RECURRENCES >= recurrence) {
        //            math3d::vector r(math3d::vector(2 * math3d::dot(n, v) * n - v));
        //            result += trace(ray(p + EPSILON*r, r), recurrence + 1) * shp->mat()->kr;
        //        }
        hindernis=false;
    }
    return result;
}
