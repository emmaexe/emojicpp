#pragma once

#include <emojicpp/export_emojicpp.hpp>
#include <string>
#include <unordered_map>

namespace emojicpp {
    class EMOJICPP_EXPORT emoji {
        public:
            emoji() = delete;
            static std::string parse(std::string str, bool escape = true);
            static std::unordered_map<std::string, std::string> map;
    };
} // namespace emojicpp
