/// @example eglplus/002_list_extensions.cpp
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

auto main(main_ctx& ctx) -> int {
    using namespace eagine::eglplus;

    const egl_api egl{ctx};
    const main_ctx_object out{"EGLplus", ctx};

    if(egl.get_display) {
        if(const ok display{egl.get_open_display()}) {
            const auto api_cio{
              out.cio_print("Supported APIs:").to_be_continued()};

            if(const ok apis{egl.get_client_apis(display)}) {
                for(const auto name : apis) {
                    api_cio.print(name);
                }
            } else {
                api_cio.error("failed to get API list: ${message}")
                  .arg("message", (not apis).message());
            }
        }
    } else {
        out.cio_error("missing required API function");
    }
    return 0;
}

} // namespace eagine
//------------------------------------------------------------------------------
auto main(int argc, const char** argv) -> int {
    return eagine::default_main(argc, argv, eagine::main);
}

