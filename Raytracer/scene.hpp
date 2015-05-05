#ifndef SCENE_HPP
#define	SCENE_HPP
#include <list>
#include "shape.hpp"
#include "light_source.hpp"
#include "camera.hpp"
#include "material.hpp"
#include <string>
#include <map>

struct scene {
public:
    scene();
    scene(std::string const& datei);
    scene(const scene& orig);
    virtual ~scene();

    void render(camera const& cam, std::string const& filename, double const&, double const&);
    void sdfloader();
//    void sdfloader(std::string const&);
    void scenetest();

    std::list<shape*> ls_;
    std::list<light_source> lls_;
    std::map<std::string,material> mmat_;
    camera cam_;
    light_source ambientl_;
private:
};

#endif	/* SCENE_HPP */

