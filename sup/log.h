#pragma once

#include "log.inl.h"

namespace sg {
namespace sup {
namespace log {

void Init();
void Deinit();

class Logger {
public:
    Logger();
    ~Logger();

    void Log(const char *src, const char *str);
};

extern Logger *LOGINST;
}

template<typename... R>
inline void LOG(const char *src, R... info) {
    if ( log::LOGINST != nullptr ) {
        std::stringstream infostr;
        log::ILOG( infostr, info... );
        log::LOGINST->Log( src, infostr.str( ).c_str( ));
    }
}

}
}