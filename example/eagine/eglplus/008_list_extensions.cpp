/// @example eglplus/008_list_extensions.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///

import eagine.core;
import eagine.eglplus;
import std;

auto main() -> int {
    using namespace eagine;
    using namespace eagine::eglplus;

    const egl_api egl;

    std::cout << "Generic extensions: " << std::endl;

    if(const ok extensions{egl.get_extensions()}) {
        for(const auto name : extensions) {
            std::cout << "  " << name << std::endl;
        }
    } else {
        std::cerr << "failed to get extension list: "
                  << (not extensions).message() << std::endl;
    }

    std::cout << std::endl;

    if(const ok dev_count{egl.query_devices.count()}) {
        const auto n{std_size(dev_count)};
        std::cout << "Device count: " << n << std::endl;
        std::vector<egl_types::device_type> devices;
        devices.resize(n);
        if(egl.query_devices(cover(devices))) {
            for(const auto d : integer_range(n)) {
                std::cout << "Device: " << d << std::endl;

                std::cout << " Device extensions: " << std::endl;
                if(const ok extensions{
                     egl.get_device_extensions(device_handle(devices[d]))}) {
                    for(const auto name : extensions) {
                        std::cout << "  " << name << std::endl;
                    }
                } else {
                    std::cerr << "failed to get device extension list: "
                              << (not extensions).message() << std::endl;
                }

                if(egl.get_platform_display) {
                    if(const ok display{egl.get_platform_display(
                         egl.platform_device, devices[d])}) {
                        if(const ok init_res{egl.initialize(display)}) {
                            const auto do_cleanup = egl.terminate.raii(display);

                            if(const ok vendor{
                                 egl.query_string(display, egl.vendor)}) {
                                std::cout << " Vendor:  " << vendor
                                          << std::endl;
                            }

                            if(const ok version{
                                 egl.query_string(display, egl.version)}) {
                                std::cout << " Version: " << version
                                          << std::endl;
                            }

                            if(egl.MESA_query_driver(display)) {
                                if(ok driver_name{
                                     egl.get_display_driver_name(display)}) {
                                    std::cout << " Driver: " << driver_name
                                              << std::endl;
                                }
                            }

                            if(egl.EXT_output_base(display)) {
                                if(ok count{
                                     egl.get_output_layers.count(display)}) {
                                    std::cout << " Output layers: " << count
                                              << std::endl;
                                }
                                if(const ok count{
                                     egl.get_output_ports.count(display)}) {
                                    std::cout << " Output ports: " << count
                                              << std::endl;
                                }
                            }

                            std::cout << " Display extensions: " << std::endl;

                            if(const ok extensions{
                                 egl.get_extensions(display)}) {
                                for(auto name : extensions) {
                                    std::cout << "  " << name << std::endl;
                                }
                            } else {
                                std::cerr << "failed to get extension list: "
                                          << (not extensions).message()
                                          << std::endl;
                            }
                        } else {
                            std::cerr << "failed to initialize display: "
                                      << (not init_res).message() << std::endl;
                        }
                    } else {
                        std::cerr << "failed to get platform display: "
                                  << (not display).message() << std::endl;
                    }
                } else {
                    std::cout << "missing required API function." << std::endl;
                }
                std::cout << std::endl;
            }
        }
    }

    return 0;
}
