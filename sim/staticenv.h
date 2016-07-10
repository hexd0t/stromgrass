#include <cstdint>

namespace sg {
namespace sim {
struct env_props {
    uint32_t grid_cells;
    uint16_t map_size; //maps are always square
    uint8_t grid_relaxations;
};

class staticenv {
private:
    uint_fast64_t mBaseSeed;
    env_props mBaseProps;
public:
    staticenv(uint_fast64_t seed, const env_props& properties);
    ~staticenv();
private:
    void generate_terrain(uint_fast64_t seed);
};
}
}
