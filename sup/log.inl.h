#pragma once
#include <string>
#include <sstream>

namespace sg {
    namespace sup {
        namespace log {
            using ss = std::stringstream;
            inline void ILOG(ss&);

// Specialize like this if needed:
//            template<typename... R>
//            inline void ILOG(ss&, const char *text, R... remainder);

            template<typename T, typename... R>
            inline void ILOG(ss&, T val, R... remainder);

            inline void ILOG(ss& str) {
                str.seekp(-1, std::ios_base::end);
            }

            template<typename T, typename... R>
            inline void ILOG(ss& str, T val, R... remainder) {
                str << val << " ";
                ILOG(str, remainder...);
            }
        }
    }
}