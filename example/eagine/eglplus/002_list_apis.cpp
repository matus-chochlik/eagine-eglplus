/// @example eglplus/002_list_extensions.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/eglplus/egl.hpp>
#include <eagine/eglplus/egl_api.hpp>
#include <iostream>

auto main() -> int {
    using namespace eagine;
    using namespace eagine::eglplus;

    const egl_api egl;

    if(egl.get_display) {
        if(const ok display = egl.get_display()) {
            if(auto init_res = egl.initialize(display)) {
                const auto do_cleanup = egl.terminate.raii(display);

                std::cout << "Supported APIs:" << std::endl;

                if(const ok apis{egl.get_client_apis(display)}) {
                    for(const auto name : apis) {
                        std::cout << "  " << name << std::endl;
                    }
                } else {
                    std::cerr << "failed to get API list: " << (!apis).message()
                              << std::endl;
                }
            } else {
                std::cout << "missing required API function." << std::endl;
            }
        }
    }
    return 0;
}
