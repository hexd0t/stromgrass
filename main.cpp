#include <stdexcept>

#include "sup/log.h"
#include "sim/staticenv.h"

int main(int argc, char** argv) {
    sg::sup::log::Init();
    try {
        sg::sim::env_props ep;
        ep.grid_cells = 200;
        ep.map_size = 500;
        ep.grid_relaxations = 2;

        sg::sim::staticenv se(2u, ep);
        return 0;
    }
    catch (std::exception& ex) {
        sg::sup::LOG("expt", ex.what());
        return 1;
    }
    catch (...) {
        sg::sup::LOG("expt", "Unknown exception!");
        return 1;
    }
}