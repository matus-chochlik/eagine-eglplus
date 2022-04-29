/// @example eglplus/003_list_extensions.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/console/console.hpp>
#include <eagine/eglplus/egl.hpp>
#include <eagine/eglplus/egl_api.hpp>
#include <eagine/main.hpp>

namespace eagine {

auto main(main_ctx& ctx) -> int {
    using namespace eagine::eglplus;

    const egl_api egl;
    const auto& cio = ctx.cio();

    const auto gen_ext_cio{
      cio.print(EAGINE_ID(GL), "Generic extensions:").to_be_continued()};

    if(const ok extensions{egl.get_extensions()}) {
        for(const auto name : extensions) {
            gen_ext_cio.print(name);
        }
    } else {
        gen_ext_cio
          .print(
            console_entry_kind::error,
            "failed to get extension list: ${message}")
          .arg(EAGINE_ID(message), (!extensions).message());
    }

    if(egl.get_display) {
        if(const ok display{egl.get_display()}) {
            const auto disp_cio{
              cio.print(EAGINE_ID(GL), "Display info:").to_be_continued()};
            if(egl.initialize(display)) {
                const auto do_cleanup = egl.terminate.raii(display);

                if(const ok vendor{egl.query_string(display, egl.vendor)}) {
                    disp_cio.print("Vendor: ${info}")
                      .arg(EAGINE_ID(info), extract(vendor));
                }

                if(const ok version{egl.query_string(display, egl.version)}) {
                    disp_cio.print("Version: ${info}")
                      .arg(EAGINE_ID(info), extract(version));
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
                      .arg(EAGINE_ID(message), (!extensions).message());
                }
            } else {
                disp_cio.print(
                  console_entry_kind::error,
                  "failed to initialize EGL display");
            }
        }
    }
    return 0;
}

} // namespace eagine
