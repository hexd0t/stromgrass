#pragma once 

#include <glm/glm.hpp>
#include <boost/polygon/voronoi.hpp>

namespace boost {
namespace polygon {

//Register GLM point as polygon point
template<>
struct geometry_concept<glm::vec2> {
    typedef boost::polygon::point_concept type;
};

template<>
struct point_traits<glm::vec2> {
    typedef float coordinate_type;

    static coordinate_type get(const glm::vec2 &point, orientation_2d orient) {
        return (orient == boost::polygon::HORIZONTAL) ? point.x : point.y;
    }
};

template<>
struct point_mutable_traits<glm::vec2> {
    typedef float coordinate_type;

    static void set(glm::vec2 &point, orientation_2d orient, float value) {
        if ( orient == boost::polygon::HORIZONTAL )
            point.x = value;
        else
            point.y = value;
    }

    static glm::vec2 construct(float x_value, float y_value) {
        return glm::vec2( x_value, y_value );
    }
};
}
}