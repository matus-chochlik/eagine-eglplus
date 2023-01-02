/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
module;

#if __has_include(<EGL/egl.h>)
#include <EGL/egl.h>
#define EAGINE_HAS_EGL 1
#else
#define EAGINE_HAS_EGL 0
#endif

module eagine.eglplus;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.container;

namespace eagine {
//------------------------------------------------------------------------------
auto within_limits<eglplus::color_buffer_type, eglplus::egl_types::enum_type>::
  check(eglplus::egl_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_EGL
        case EGL_RGB_BUFFER:
        case EGL_LUMINANCE_BUFFER:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
auto within_limits<eglplus::texture_target, eglplus::egl_types::enum_type>::check(
  eglplus::egl_types::enum_type x) const noexcept -> bool {
    switch(x) {
#if EAGINE_HAS_EGL
        case EGL_NO_TEXTURE:
        case EGL_TEXTURE_2D:
            return true;
#endif
        default:
            return false;
    }
}
//------------------------------------------------------------------------------
namespace eglplus {
//------------------------------------------------------------------------------
auto map_egl_enum_by_name() noexcept {
    return basic_lc_identifier_trie<egl_types::enum_type>()
#if EAGINE_HAS_EGL
      .add("luminance_buffer", EGL_LUMINANCE_BUFFER)
      .add("no_texture", EGL_NO_TEXTURE)
      .add("rgb_buffer", EGL_RGB_BUFFER)
      .add("texture_2d", EGL_TEXTURE_2D)
#endif
      ;
}
//------------------------------------------------------------------------------
auto egl_enum_by_name(const string_view name) noexcept
  -> std::optional<egl_types::enum_type> {
    if(not name.empty()) [[likely]] {
        static const auto enums{map_egl_enum_by_name()};
        if(auto found{enums.find(name)}) [[likely]] {
            return {extract(found)};
        }
    }
    return {};
}
//------------------------------------------------------------------------------
} // namespace eglplus
} // namespace eagine
