/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
export module eagine.eglplus:from_string;
import std;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.string;
import eagine.core.valid_if;
import :enum_types;
import :constants;

namespace eagine {
//------------------------------------------------------------------------------
template <typename EnumClass>
auto egl_enum_from_string(
  const string_view src,
  std::type_identity<EnumClass>) noexcept -> optionally_valid<EnumClass> {
    if(const auto found{eglplus::egl_enum_by_name(src)}) {
        if(const auto conv{convert_if_fits<EnumClass>(*found)}) {
            return {*conv, true};
        }
    }
    return {};
}
//------------------------------------------------------------------------------
export auto from_string(
  const string_view src,
  const std::type_identity<eglplus::texture_target> tid,
  const default_selector_t) noexcept {
    return egl_enum_from_string(src, tid);
}
//------------------------------------------------------------------------------
} // namespace eagine
