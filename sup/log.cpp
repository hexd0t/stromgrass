#include "log.h"
#include <cstdio>

namespace sg {
namespace sup {
namespace log {

Logger *LOGINST = nullptr;

void Init() {
    if ( LOGINST == nullptr ) {
        LOGINST = new Logger( );
    }
}

void Deinit() {
    if ( LOGINST != nullptr ) {
        Logger *ptr = LOGINST;
        LOGINST = 0;
        delete ptr;
    }
}

Logger::Logger() {

}

Logger::~Logger() {

}

void Logger::Log(const char *src, const char *str) {
    printf( "%s: %s", src, str ); //ToDo
}

}
}
}