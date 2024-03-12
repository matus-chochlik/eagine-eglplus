/// @example eglplus/005_list_configs.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///

import eagine.core;
import eagine.eglplus;
import std;

namespace eagine {

auto print_info(const eglplus::egl_api& egl, const auto& display) {
    using namespace eagine::eglplus;

    if(const ok count{egl.get_configs.count(display)}) {

        std::vector<egl_api::config_type> configs(count);

        std::cout << "found " << configs.size() << " configs:" << std::endl;

        const std::vector<
          std::tuple<std::string_view, config_attribute, std::string_view>>
          properties{
            {"  ", egl.config_id, ": "},
            {"R:", egl.red_size, "|"},
            {"G:", egl.green_size, "|"},
            {"B:", egl.blue_size, "|"},
            {"A:", egl.alpha_size, "|"},
            {"L:", egl.luminance_size, "|"},
            {"D:", egl.depth_size, "|"},
            {"S:", egl.stencil_size, "|"},
            {"Sam:", egl.samples, "|"}};

        const auto surface_attribs{(egl.width | 64) + (egl.height | 64)};

        for(const auto config :
            egl.get_configs(display, cover(configs)).or_default()) {

            for(const auto& [pref, attr, suff] : properties) {
                std::cout
                  << pref << std::setw(2)
                  << egl.get_config_attrib(display, config, attr).value_or(-1)
                  << suff;
            }

            std::cout << "Surf:";
            if(auto surf{egl.create_pbuffer_surface_object(
                 display, config, surface_attribs)}) {
                std::cout << " OK ";
            } else {
                std::cout << "fail";
            }

            std::cout << std::endl;
        }
    }
}

auto main(main_ctx& ctx) -> int {
    using namespace eagine::eglplus;

    const egl_api egl{ctx};

    if(egl.get_display) {
        if(const ok display{egl.get_open_display()}) {
            print_info(egl, display);
        }
    } else {
        std::cerr << "missing required API" << std::endl;
    }
    return 0;
}
} // namespace eagine

auto main(int argc, const char** argv) -> int {
    return eagine::default_main(argc, argv, eagine::main);
}

