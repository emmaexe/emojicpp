# emojicpp

[![GitHub License](https://img.shields.io/github/license/emmaexe/emojicpp)](https://github.com/emmaexe/emojicpp/blob/main/LICENSE)
[![GitHub Tag](https://img.shields.io/github/v/tag/emmaexe/ntfyDesktop?label=Latest%20stable%20version)](https://github.com/emmaexe/emojicpp/releases/latest)

A library for parsing emoji names into emoji.

**Example:**

```c++
std::string parsed = emojicpp::emoji::parse("Hello, World! :earth_africa:");
// parsed == "Hello, World! 🌍"
```

**Example program:**

```c++
#include <format>
#include <emojicpp/emoji.hpp>

int main() {
    std::print("Hello there {}", emojicpp::emoji::parse(":wave:"));
}
```

The library makes use of and requires [gperf(1)](https://www.gnu.org/software/gperf/manual/gperf.html) to generate a very fast emoji lookup table.

## Usage guide

The recommended way to include this in your project is using [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake):

```CMake
file(
    DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.42.0/CPM.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
    EXPECTED_HASH SHA256=2020b4fc42dba44817983e06342e682ecfc3d2f484a581f11cc5731fbe4dce8a
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

CPMAddPackage("gh:emmaexe/emojicpp@3.0.0")
```

This will download and make available the library and its header.

The library's namespace `emojicpp` currently contains one static class `emoji` with one function, `parse`:

```c++
std::string emojicpp::emoji::parse(std::string_view string);
```

It takes as input anything compatible with `std::string_view` and returns a parsed `std::string`.

## Supported Emoji

[The full list of all supported emoji is available here](src/emoji.gperf).

### License

Distributed under the [MIT License](LICENSE).

### Contributors

![Repository Contributors](https://contrib.rocks/image?repo=emmaexe/emojicpp)
