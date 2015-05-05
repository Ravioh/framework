#include <cstdlib>
#include "../boost/include/boost/thread/thread.hpp"
#include "../include/boost/bind.hpp"
#include "scene.hpp"


int main()
{
    scene s;
    boost::thread thr(boost::bind(&scene::sdfloader, &s));
//    s.sdfloader();
    thr.join();

    return 0;
}

