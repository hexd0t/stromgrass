#include "staticenv.h"
#include <random>
#include <boost/polygon/voronoi.hpp>

using boost::polygon::voronoi_builder;
using boost::polygon::voronoi_diagram;

namespace sg {
namespace sim {

staticenv::staticenv(uint_fast64_t seed) {
    std::mt19937_64 subseed_gen( seed );

    generate_terrain( subseed_gen( ) );
}

staticenv::~staticenv() {

}

void staticenv::generate_terrain(uint_fast64_t seed) {

}

}
}