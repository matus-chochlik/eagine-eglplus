/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
import std;
import eagine.core;
import eagine.eglplus;

namespace eagine {
//------------------------------------------------------------------------------
void print_info(
  const eglplus::egl_api& egl,
  eglplus::display_handle display,
  const console_entry_continuation& dev_cio) {
    if(const ok vendor{egl.query_string(display, egl.vendor)}) {
        dev_cio.print("Vendor: ${vendor}").arg("vendor", vendor);
    }

    if(egl.MESA_query_driver(display)) {
        if(ok driver_name{egl.get_display_driver_name(display)}) {
            dev_cio.print("Driver: ${driver}").arg("driver", driver_name);
        }
    }
}
//------------------------------------------------------------------------------
auto main(main_ctx& ctx) -> int {

    const eglplus::egl_api egl;
    if(const ok dev_count{egl.query_devices.count()}) {
        const auto n{std_size(dev_count)};
        const auto list_cio{ctx.cio()
                              .print("EGLdevices", "device count: ${count}")
                              .arg("count", n)
                              .to_be_continued()};

        std::vector<eglplus::egl_types::device_type> devices;
        devices.resize(n);
        if(egl.query_devices(cover(devices))) {
            for(const auto d : integer_range(n)) {
                const auto dev_cio{list_cio.print("device: ${index}")
                                     .arg("index", d)
                                     .to_be_continued()};

                if(egl.get_platform_display) {
                    if(const ok display{egl.get_platform_display(
                         egl.platform_device, devices[d])}) {
                        if(const ok init_res{egl.initialize(display)}) {
                            const auto do_cleanup{egl.terminate.raii(display)};

                            print_info(egl, display, dev_cio);
                        }
                    }
                }
            }
        }
    }

    return 0;
}
//------------------------------------------------------------------------------
} // namespace eagine
//------------------------------------------------------------------------------
auto main(int argc, const char** argv) -> int {
    eagine::main_ctx_options options{.app_id = "LstEGLDevs"};
    return eagine::main_impl(argc, argv, options, eagine::main);
}
//------------------------------------------------------------------------------

