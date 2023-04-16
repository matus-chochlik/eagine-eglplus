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

                    for(const auto config :
                        egl.choose_config(display, attribs, cover(configs))
                          .or_default()) {

                        const auto print_info{[&](
                                                const std::string_view pref,
                                                auto attr,
                                                const std::string_view suff) {
                            std::cout
                              << pref << std::setw(2)
                              << egl.get_config_attrib(display, config, attr)
                                   .value_or(-1)
                              << suff;
                        }};
                        print_info("  ", egl.config_id, ": ");
                        print_info("R:", egl.red_size, "|");
                        print_info("G:", egl.green_size, "|");
                        print_info("B:", egl.blue_size, "|");
                        print_info("A:", egl.alpha_size, "|");
                        print_info("L:", egl.luminance_size, "|");
                        print_info("D:", egl.depth_size, "|");
                        print_info("S:", egl.stencil_size, "|");
                        print_info("Sam:", egl.samples, "|");

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
