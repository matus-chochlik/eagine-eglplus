/// @example eglplus/003_list_extensions.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/eglplus/egl.hpp>
#include <eagine/eglplus/egl_api.hpp>
#include <iostream>
#include <vector>

auto main() -> int {
    using namespace eagine;
    using namespace eagine::eglplus;

    const egl_api egl;

    std::cout << "Generic extensions: " << std::endl;

    if(const ok extensions = egl.get_extensions()) {
        for(const auto name : extensions) {
            std::cout << "  " << name << std::endl;
        }
    } else {
        std::cerr << "failed to get extension list: " << (!extensions).message()
                  << std::endl;
    }

    std::cout << std::endl;

    if(egl.get_display) {
        if(const ok display{egl.get_display()}) {
            if(egl.initialize(display)) {
                const auto do_cleanup = egl.terminate.raii(display);

                if(const ok vendor{egl.query_string(display, egl.vendor)}) {
                    std::cout << "Vendor:  " << extract(vendor) << std::endl;
                }

                if(const ok version{egl.query_string(display, egl.version)}) {
                    std::cout << "Version: " << extract(version) << std::endl;
                }

                std::cout << "Display extensions: " << std::endl;

                if(const ok extensions{egl.get_extensions(display)}) {
                    for(const auto name : extensions) {
                        std::cout << "  " << name << std::endl;
                    }
                } else {
                    std::cerr << "failed to get extension list: "
                              << (!extensions).message() << std::endl;
                }
            } else {
                std::cout << "missing required API function." << std::endl;
            }
        }
    }
    return 0;
}
