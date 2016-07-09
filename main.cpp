#include <stdexcept>

#include "sup/log.h"

int main(int argc, char** argv) {
    sg::sup::log::Init();
    try {
        sg::sup::LOG("main", "hallo!", 10, 10.1);
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