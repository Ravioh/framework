/*
 * File:   scene.cpp
 * Author: onkeliroh
 *
 * Created on 30. August 2011, 14:53
 */

#include "scene.hpp"

#include "../include/glutwindow.hpp"
#include "../include/ppmwriter.hpp"
#include "../include/pixel.hpp"
#include <cmath>
#include <math.h>
#include <cstring>
#include "../include/boost/thread/thread.hpp"
#include "../include/boost/bind.hpp"
#include "../include/vector.hpp"
#include "../include/matrix.hpp"
#include "../include/point.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <ostream>
#include <list>
#include "../include/color.hpp"
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "material.hpp"
#include "light_source.hpp"
#include "camera.hpp"
#include "ray.hpp"

#ifdef __APPLE__
    #include "../include/GLUT/glut.h"
#else
    #include "../include/GL/glut.h"
#endif

scene::scene() {
}

scene::scene(const scene& orig) {
}

scene::~scene() {
}

void scene::render(camera const& cam, std::string const& filename, double const& xres, double const& yres)
{
    std::cout<<"Start Render"<<std::endl;

    int argc;
    char* argv[0];

    double vh = yres / xres;
    double fb = 2*(tan((cam.get_fov()*M_PI/180)/2));
    double fh = (vh * fb);

    std::size_t fensterbreite=xres;
    std::size_t fensterhohe=yres;

    std::cout<<"Variablen sind angelegt."<<std::endl;
//    std::cout<<cam.get_fov()<<std::endl;
//    std::cout<<"v: "<<vh<<std::endl;
//    std::cout<<"fb: "<<fb<<" fh: "<<fh<<std::endl;
//    std::cout<<"fb: "<<fensterbreite<<" fh: "<<fensterhohe<<std::endl;

    glutwindow::init(fensterbreite,fensterhohe,100.0,100.0,"hier passiert die Magie",argc,argv);
    glutwindow& window1 = glutwindow::instance();

    ppmwriter image (window1.width(),window1.height(), filename);

    std::cout<<"Vorbereitungen abgeschlossen. ^^"<<std::endl;

    for (std::size_t y=0;y<fensterhohe;++y)
    {
        for (std::size_t x=0;x<fensterbreite;++x)
        {
//            std::cout<<x<<"     "<<y<<std::endl;
            pixel p(x,y);
            ray r(cam.get_position(),math3d::point(((x*(fb/xres))-(fb/2)),(y*(fh/yres))-(fh/2),-1));
            p.rgb = r.intersection(ls_,lls_);
            window1.write(p);
            image.write(p);
        }
    }
    image.save();
    glutwindow::instance().run();
    std::cout<<"Render ist fertig!"<<std::endl;
}

void scene::sdfloader()
{
    std::ifstream scene ("scene.sdf");

    if(scene.is_open())
    {
        std::string line;

        while (std::getline(scene,line))
        {
            std::stringstream ss;
            ss<<line;
            std::string aktion;
            ss >> aktion;

            if (aktion == "define")
            {
                std::string type;
                ss >> type;

                if (type == "material")
                {
                    std::string name;
                    int r1;
                    int g1;
                    int b1;
                    int r2;
                    int g2;
                    int b2;
                    int r3;
                    int g3;
                    int b3;
                    float m;
                    ss >>name>>r1>>g1>>b1>>r2>>g2>>b2>>r3>>g3>>b3>>m;

                    mmat_.insert(std::pair<std::string,material>(name,material(name,color(r1,g1,b1),color(r2,g2,b2),color(r3,g3,b3),m)));
                }

                if (type == "shape")
                {
                    std::string sort;
                    ss >> sort;
                    if (sort == "box")
                    {
                        std::string name;
                        double x1;
                        double y1;
                        double z1;
                        double x2;
                        double y2;
                        double z2;
                        std::string matn;
                        ss>>name>>x1>>y1>>z1>>x2>>y2>>z2>>matn;
                        material mat = mmat_.find(matn)->second;
                        ls_.push_back(new box(math3d::point(x1,y1,z1),math3d::point(x2,y2,z2),name, mat));
                    }
                    if (sort == "sphere")
                    {
                        std::string name;
                        double x, y, z;
                        double r;
                        std::string matn;

                        ss>>name>>x>>y>>z>>r>>matn;
                        material mat = mmat_.find(matn)->second;
                        ls_.push_back(new sphere(math3d::point(x,y,z), r,name, mat));
                    }
                }
                if (type == "light")
                {
                    std::string name;
                    float r1, g1, b1;
                    float r2, g2, b2;
                    double x,y,z;

                    ss>>name>>x>>y>>z>>r1>>g1>>b1>>r2>>g2>>b2;

                    lls_.push_back(light_source(name,math3d::point(x,y,z),color(r1,g1,b1),color(r2,g2,b2)));
                }
                if (type == "camera")
                {
                    std::string name;
                    double fov;

                    ss>>name>>fov;

                    cam_.set_name(name);
                    cam_.set_fov(fov);
                }
            }
//            if (aktion == "transform")
//            {
//                std::string obj,tat;
//                ss >> obj >> tat;
//                shape* s;
//                for (std::list<shape*>::iterator i = ls_.begin();i!=ls_.end();++i){
//                    if((*i).get_name() == obj){
//                        s=*i;
//                        break;
//                    }
//                }
//                if (tat == "scale")
//                {
//                    double x,y,z;
//                    ss>>x>>y>>z;
//                    s->scale(math3d::vector(math3d::point(.0,.0,.0),math3d::point(x,y,z)));
//                }
//                if (tat == "translate")
//                {
//                    double x,y,z;
//                    ss>>x>>y>>z;
//                    s->transform(math3d::vector(math3d::point(.0,.0,.0),math3d::point(x,y,z)));
//                }
//                if (tat == "rotetex")
//                {
//                    double w;
//                    ss>>w;
//                    s->rotatex(w);
//                }
//                if (tat == "rotetey")
//                {
//                    double w;
//                    ss>>w;
//                    s->rotatey(w);
//                }
//                if (tat == "rotetez")
//                {
//                    double w;
//                    ss>>w;
//                    s->rotatez(w);
//                }
//            }
            if (aktion == "render")
            {
                std::string camera;
                std::string filename;
                double xres,yres;

                ss>>camera>>filename>>xres>>yres;

                cam_.set_name(camera);
                scenetest();

                render(cam_,filename,xres,yres);
            }
            ss.clear();
        }
    }
    scene.close();
    std::cout<<"SDF-Loader abgeschlossen."<<std::endl;
}



void scene::scenetest()
{
    for (std::map<std::string,material>::iterator i = mmat_.begin();i!=mmat_.end();++i)
    {
        std::cout<<i->first<<"  "<<i->second<<std::endl;
    }
    for (std::list<shape*>::iterator i = ls_.begin();i!=ls_.end();++i)
    {
        std::cout<<(*(*i))<<std::endl;
    }
    std::cout<<cam_.get_name()<<"       "<<cam_.get_fov()<<std::endl;
    std::cout<<lls_.size()<<std::endl;
}
