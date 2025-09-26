#include <emojicpp/emoji.hpp>
#include <internal.hpp>

namespace emojicpp {
    std::string emoji::parse(std::string_view string) {
        std::string result;
        result.reserve(string.size());
        std::size_t checkpoint = 0;

        for (std::size_t i = 0; i < string.size(); i++) {
            if (string[i] == ':') {
                result += string.substr(checkpoint, i-checkpoint);

                std::size_t j = i+1;
                while (j != string.size() && string[j] != ':') {
                    j++;
                }

                if (j == string.size()) {
                    break;
                }

                std::string_view emojiName = string.substr(i, j-i+1);
                const Entry* res = internal::lookup(emojiName.data(), emojiName.size());

                if (res == nullptr) {
                    result += emojiName.substr(0, emojiName.size()-1);
                    i = j-1;
                } else {
                    result += reinterpret_cast<const char*>(res->value);
                    i = j;
                }

                checkpoint = i+1;
            }
        }

        result += string.substr(checkpoint);

        return result;
    }
} // namespace emojicpp
