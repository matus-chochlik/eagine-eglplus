/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///

#include <eagine/testing/unit_begin.hpp>
import std;
import eagine.core;
import eagine.eglplus;
//------------------------------------------------------------------------------
void constants_enum_by_name(auto& s) {
    eagitest::case_ test{s, 1, "EGL enum by name"};
    std::set<eagine::eglplus::egl_types::enum_type> distinct;

    const auto check{[&](eagine::string_view name) {
        if(auto value{eagine::eglplus::egl_enum_by_name(name)}) {
            distinct.insert(*value);
        } else {
            test.fail(name);
        }
    }};
    check("luminance_buffer");
    check("no_texture");
    check("rgb_buffer");
    check("texture_2d");

    test.check_equal(distinct.size(), 4U, "constant count");
}
//------------------------------------------------------------------------------
auto main(int argc, const char** argv) -> int {
    eagitest::suite test{argc, argv, "constants", 1};
    test.once(constants_enum_by_name);
    return test.exit_code();
}
//------------------------------------------------------------------------------
#include <eagine/testing/unit_end.hpp>
