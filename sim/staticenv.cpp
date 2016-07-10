#include "staticenv.h"

#include <random>
#include <fstream>

#include "glm_boostpolygon.h"
#include "../sup/log.h"

using boost::polygon::voronoi_diagram;
using sg::sup::LOG;

namespace sg {
namespace sim {

staticenv::staticenv(uint_fast64_t seed, const env_props &properties)
        : mBaseSeed( seed ), mBaseProps( properties ) {
    std::mt19937_64 subseed_gen( seed );

    generate_terrain( subseed_gen( ) );
}

staticenv::~staticenv() {

}

void staticenv::generate_terrain(uint_fast64_t seed) {
    std::mt19937_64 terrain_rnd( seed );

    float f_map_size = static_cast<float>(mBaseProps.map_size);

    //based on http://www-cs-students.stanford.edu/~amitp/game-programming/polygon-map-generation/
    std::vector<glm::vec2> points;
    points.reserve( mBaseProps.grid_cells );
    std::uniform_real_distribution<float> coorddist( 0.0f, f_map_size );
    for ( uint32_t i = 0u; i < mBaseProps.grid_cells; ++i) {
        points.push_back(glm::vec2(coorddist(terrain_rnd), coorddist(terrain_rnd)));
    }

    auto pcopy = points;

    for ( uint8_t i = 0u; i < mBaseProps.grid_relaxations; ++i ) {
        voronoi_diagram<double> diag;
        boost::polygon::construct_voronoi(points.begin(), points.end(), &diag);

        auto point_it = points.begin();
        for(auto it = diag.cells().begin(); it != diag.cells().end(); ++it) {
            //Move point to average of border vertices
            //This is similar to lloyd's algorithm
            assert(point_it != points.end());
            const auto& cell = *it;
            const auto* edge = cell.incident_edge();
            point_it->x = 0.0f;
            point_it->y = 0.0f;
            size_t pointcount = 0;
            do {
                if(edge->vertex0()) {
                    point_it->x += edge->vertex0()->x();
                    point_it->y += edge->vertex0()->y();
                    ++pointcount;
                }
                if(edge->vertex1()) {
                    point_it->x += edge->vertex1()->x();
                    point_it->y += edge->vertex1()->y();
                    ++pointcount;
                }
                edge = edge->next();
            } while(edge != cell.incident_edge());

            point_it->x = std::min(std::max(point_it->x / pointcount, 0.0f), f_map_size);
            point_it->y = std::min(std::max(point_it->y / pointcount, 0.0f), f_map_size);

            ++point_it;
        }
    }

    std::ofstream newp("newp.csv");
    auto pold = pcopy.begin();
    for(auto& p : points) {
        newp << pold->x << "," << pold->y << ",," << p.x << "," << p.y << "\n";
        ++pold;
    }
    newp.close();
}

}
}