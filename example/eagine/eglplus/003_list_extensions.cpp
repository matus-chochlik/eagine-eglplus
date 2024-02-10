/// @example eglplus/003_list_extensions.cpp
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

    const egl_api egl;
    const main_ctx_object out{"EGLplus", ctx};

    const auto gen_ext_cio{
      out.cio_print("Generic extensions:").to_be_continued()};

    if(const ok extensions{egl.get_extensions()}) {
        for(const auto name : extensions) {
            gen_ext_cio.print(name);
        }
    } else {
        gen_ext_cio
          .print(
            console_entry_kind::error,
            "failed to get extension list: ${message}")
          .arg("message", (not extensions).message());
    }

    if(egl.get_display) {
        const auto disp_cio{out.cio_print("Display info:").to_be_continued()};
        if(const ok display{egl.get_open_display()}) {

            if(const ok vendor{egl.query_string(display, egl.vendor)}) {
                disp_cio.print("Vendor: ${info}").arg("info", vendor);
            }

            if(const ok version{egl.query_string(display, egl.version)}) {
                disp_cio.print("Version: ${info}").arg("info", version);
            }

            const auto disp_ext_cio{
              disp_cio.print("extensions:").to_be_continued()};

            if(const ok extensions{egl.get_extensions(display)}) {
                for(const auto name : extensions) {
                    disp_ext_cio.print(name);
                }
            } else {
                disp_ext_cio
                  .print(
                    console_entry_kind::error,
                    "failed to get extension list: ${message}")
                  .arg("message", (not extensions).message());
            }
        } else {
            disp_cio.print(
              console_entry_kind::error, "failed to initialize EGL display");
        }
    }
    return 0;
}

} // namespace eagine
//------------------------------------------------------------------------------
auto main(int argc, const char** argv) -> int {
    return eagine::default_main(argc, argv, eagine::main);
}

