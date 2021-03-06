/// @example eglplus/001_basic_info.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/eglplus/egl.hpp>
#include <eagine/eglplus/egl_api.hpp>
#include <eagine/main_ctx.hpp>
#include <eagine/main_ctx_object.hpp>

namespace eagine {

auto main(main_ctx& ctx) -> int {
    using namespace eagine::eglplus;

    const egl_api egl;
    const main_ctx_object out{EAGINE_ID(EGLplus), ctx};

    if(const ok display{egl.get_display()}) {
        if(egl.initialize(display)) {
            const auto do_cleanup{egl.terminate.raii(display)};

            if(const ok dev_count{egl.query_devices.count()}) {
                out.cio_print("Devices: ${count}")
                  .arg(EAGINE_ID(count), dev_count);
            }

            if(const ok vendor{egl.query_string(display, egl.vendor)}) {
                out.cio_print("Vendor: ${vendor}")
                  .arg(EAGINE_ID(vendor), vendor);
            }

            if(const ok version{egl.query_string(display, egl.version)}) {
                out.cio_print("Version: ${version}")
                  .arg(EAGINE_ID(version), version);
            }

        } else {
            out.cio_error("failed to initialize EGL");
        }
    } else {
        out.cio_error("failed to get default display");
    }
    return 0;
}
} // namespace eagine

auto main(int argc, const char** argv) -> int {
    return eagine::default_main(argc, argv, eagine::main);
}

