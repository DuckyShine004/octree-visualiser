#pragma once

#include <array>
#include <string>

namespace utility {

class ColourUtility {
  public:
    static std::string get_ansi_foreground_from_hex(const std::string &hex);

    static std::string get_ansi_background_from_hex(const std::string &hex);

  private:
    static std::array<int, 3> get_RGB_from_hex(const std::string &hex);
};

} // namespace utility
