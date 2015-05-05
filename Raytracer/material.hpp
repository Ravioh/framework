#ifndef MATERIAL_HPP
#define	MATERIAL_HPP

#include <string>
#include "../include/color.hpp"
#include <ostream>

class material {
public:
    material();
    material(std::string const&, color const&, color const&, color const&,float const&);
    material(const material& orig);
    void print_on(std::ostream& str) const;
    virtual ~material();

    std::string const& get_name() const;
    float const& get_m() const;
    color const& get_ka() const;
    color const& get_kd() const;
    color const& get_ks() const;

private:
    std::string name_;
    color ka_;
    color kd_;
    color ks_;
    float m_;


};

std::ostream& operator<<(std::ostream& str, material const& mat);

#endif	/* MATERIAL_HPP */

