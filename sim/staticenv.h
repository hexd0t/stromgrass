#include <cstdint>

namespace sg {
namespace sim {
class staticenv {
public:
    staticenv(uint_fast64_t seed);
    ~staticenv();
private:
    void generate_terrain(uint_fast64_t seed);
};
}
}
