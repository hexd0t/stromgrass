#include "staticenv.h"

#include <random>
#include <fstream>
#include <iostream>

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
    for ( uint32_t i = 0u; i < mBaseProps.grid_cells; ++i ) {
        points.push_back( glm::vec2( coorddist( terrain_rnd ), coorddist( terrain_rnd ) ) );
    }

    std::ofstream os( "pointdist.svg" );
    os << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
          "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 "<< mBaseProps.map_size
       << " " << mBaseProps.map_size << "\">\n"
          "<style>.o { fill:#333; stroke:#555; } .l { stroke:#012456; }"
          ".n { fill:#ddd; stroke:#bbb; }</style>\n";

    //draw randomgen points
    /*for ( auto &p : points ) {
        os << "<circle class=\"o\" r=\"2\" cx=\"" << p.x << "\" cy=\"" << p.y << "\" />\n";
    }*/

    relax_point_grid( points );

    //draw relaxed points
    for ( auto &p : points ) {
        os << "<circle class=\"n\" r=\"2\" cx=\"" << p.x << "\" cy=\"" << p.y << "\" />\n";
    }

    voronoi_diagram<double> diag;
    boost::polygon::construct_voronoi( points.begin( ), points.end( ), &diag );

    //draw
    for(auto it = diag.edges().begin(); it != diag.edges().end(); ++it) {
        if(it->vertex0() != nullptr && it->vertex1() != nullptr) {
            os << "<line class=\"l\" x1=\"" << it->vertex0( )->x( ) << "\" y1=\""
                << it->vertex0()->y() << "\" x2=\"" << it->vertex1( )->x( ) << "\" y2=\""
                                         << it->vertex1()->y() << "\" />\n";
        }
    }

    os << "</svg>";
    os.close( );
}

void staticenv::relax_point_grid(std::vector<glm::vec2> &points) {
    float f_map_size = static_cast<float>(mBaseProps.map_size);

    for ( uint8_t i = 0u; i < mBaseProps.grid_relaxations; ++i ) {
        voronoi_diagram<double> diag;
        boost::polygon::construct_voronoi( points.begin( ), points.end( ), &diag );

        auto point_it = points.begin( );
        for ( auto it = diag.cells( ).begin( ); it != diag.cells( ).end( ); ++it ) {
            //Move point to average of border vertices
            //This is similar to lloyd's algorithm
            assert( point_it != points.end( ) );
            const auto &cell = *it;
            const auto *edge = cell.incident_edge( );
            point_it->x = 0.0f;
            point_it->y = 0.0f;
            size_t pointcount = 0;
            do {
                for ( size_t j = 0; j < 2; ++j ) {
                    auto *p = (j == 0) ? edge->vertex0( ) : edge->vertex1( );
                    if ( p != nullptr ) { //ignore infinite edges - these are ocean tiles only & not worth the trouble
                        point_it->x += p->x( );
                        point_it->y += p->y( );
                        ++pointcount;
                    }
                }
                edge = edge->next( );
            } while ( edge != cell.incident_edge( ) );

            //restrict points to map range - this is simpler than intersecting voronoi edges with the rect
            //and still gives good results
            point_it->x = std::min(std::max(point_it->x / pointcount, 0.0f), f_map_size);
            point_it->y = std::min(std::max(point_it->y / pointcount, 0.0f), f_map_size);
            ++point_it;
        }
    }
}


}
}