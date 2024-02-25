/// @example eglplus/001_basic_info.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
import eagine.core;
import eagine.eglplus;

namespace eagine {

auto main(main_ctx& ctx) -> int {
    using namespace eagine::eglplus;

    const egl_api egl;
    const main_ctx_object out{"EGLplus", ctx};

    if(const ok display{egl.get_open_display()}) {
        if(const ok dev_count{egl.query_devices.count()}) {
            out.cio_print("Devices: ${count}").arg("count", dev_count);
        }

        if(const ok vendor{egl.query_string(display, egl.vendor)}) {
            out.cio_print("Vendor: ${vendor}").arg("vendor", vendor);
        }

        if(const ok version{egl.query_string(display, egl.version)}) {
            out.cio_print("Version: ${version}").arg("version", version);
        }
    } else {
        out.cio_error("failed to get default display");
    }
    return 0;
}
} // namespace eagine
//------------------------------------------------------------------------------
auto main(int argc, const char** argv) -> int {
    return eagine::default_main(argc, argv, eagine::main);
}

