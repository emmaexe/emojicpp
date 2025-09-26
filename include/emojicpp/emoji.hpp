#pragma once

#include <string>

namespace emojicpp {
    class emoji {
        public:
            emoji() = delete;
            emoji(const emoji&) = delete;
            emoji& operator=(const emoji&) = delete;

            /**
             * @brief Parses a string by replacing emoji names (in the `:name:` format) with emoji characters
             *
             * @param string The string being parsed
             * @return std::string - The parsed string
             */
            static std::string parse(std::string_view string);
    };
} // namespace emojicpp
