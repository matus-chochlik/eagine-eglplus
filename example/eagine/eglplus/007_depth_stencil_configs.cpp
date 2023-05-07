/// @example eglplus/007_depth_stencil_configs.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

import eagine.core;
import eagine.eglplus;
import std;

auto main() -> int {
    using namespace eagine;
    using namespace eagine::eglplus;

    const egl_api egl;

    if(egl.get_display) {
        if(const ok display{egl.get_display()}) {
            if(egl.initialize(display)) {
                const auto do_cleanup = egl.terminate.raii(display);

                const auto attribs =
                  (egl.depth_size | 24) + (egl.stencil_size | 8);

                if(const ok count{egl.choose_config.count(display, attribs)}) {

                    std::vector<egl_api::config_type> configs(count);

                    std::cout << "found " << configs.size()
                              << " depth/stencil configs:" << std::endl;

                    const std::vector<std::tuple<
                      std::string_view,
                      config_attribute,
                      std::string_view>>
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

                    for(const auto config :
                        egl.choose_config(display, attribs, cover(configs))
                          .or_default()) {

                        for(const auto& [pref, attr, suff] : properties) {
                            std::cout
                              << pref << std::setw(2)
                              << egl.get_config_attrib(display, config, attr)
                                   .value_or(-1)
                              << suff;
                        }

                        std::cout << std::endl;
                    }
                }
            }
        }
    } else {
        std::cerr << "missing required API" << std::endl;
    }
    return 0;
}
