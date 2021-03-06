/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_EGLPLUS_EGL_API_CONFIG_HPP
#define EAGINE_EGLPLUS_EGL_API_CONFIG_HPP

#include "../config/basic.hpp"

#ifndef EGLPLUS_HAS_EGL
#if defined(EGL_SUCCESS)
#define EGLPLUS_HAS_EGL 1

#ifndef EGL_BAD_STREAM_KHR
#define EGL_BAD_STREAM_KHR 0x321B
#endif

#ifndef EGL_BAD_STATE_KHR
#define EGL_BAD_STATE_KHR 0x321C
#endif

#ifndef EGL_PLATFORM_DEVICE_EXT
#define EGL_PLATFORM_DEVICE_EXT 0x313F
#endif

#ifndef EGL_BAD_OUTPUT_LAYER_EXT
#define EGL_BAD_OUTPUT_LAYER_EXT 0x322D
#endif

#ifndef EGL_BAD_OUTPUT_PORT_EXT
#define EGL_BAD_OUTPUT_PORT_EXT 0x322E
#endif

#else
#define EGLPLUS_HAS_EGL 0
#endif
#endif // EGLPLUS_HAS_EGL

#if !EGLPLUS_HAS_EGL
#include <eagine/nothing.hpp>
#include <cstdint>
#endif

namespace eagine::eglplus {
//------------------------------------------------------------------------------
/// @brief Collection of aliases for EGL types.
/// @ingroup egl_api_wrap
struct egl_types {
    /// @brief Untyped non-const pointer type.
    using void_ptr_type = void*;

    /// @brief String character type.
    using char_type = char;

    /// @brief Device handle type.
    using device_type = void*;

    /// @brief Stream handle type.
    using stream_type = void*;

    /// @brief Output layer handle type.
    using output_layer_type = void*;

    /// @brief Output port handle type.
    using output_port_type = void*;
#if EGLPLUS_HAS_EGL
    static constexpr bool has_api = true;

    /// @brief Native display handle type.
    using native_display_type = EGLNativeDisplayType;

    /// @brief Native window handle type.
    using native_window_type = EGLNativeWindowType;

    /// @brief Native pixmap handle type.
    using native_pixmap_type = EGLNativePixmapType;

    /// @brief Client buffer handle type.
    using client_buffer_type = EGLClientBuffer;

    /// @brief EGL display handle type.
    using display_type = EGLDisplay;

    /// @brief Config handle type.
    using config_type = EGLConfig;

    /// @brief Config attribute handle type.
    using attrib_type = EGLAttrib;

    /// @brief Rendering context handle type.
    using context_type = EGLContext;

    /// @brief Rendering surface handle type.
    using surface_type = EGLSurface;

    /// @brief EGL image type.
    using image_type = EGLImage;

    /// @brief Sync object handle type.
    using sync_type = EGLSync;

    /// @brief Time type.
    using time_type = EGLTime;

    /// @brief Boolean type.
    using bool_type = EGLBoolean;

    /// @brief Enumeration type.
    using enum_type = EGLenum;

    /// @brief Signed integer type.
    using int_type = EGLint;
#else
    static constexpr bool has_api = false;
    using native_display_type = int;
    using native_window_type = int;
    using native_pixmap_type = int;
    using client_buffer_type = int;
    using display_type = int;
    using config_type = int;
    using attrib_type = std::intptr_t;
    using context_type = int;
    using surface_type = int;
    using image_type = int;
    using sync_type = int;
    using time_type = int;
    using bool_type = bool;
    using enum_type = int;
    using int_type = int;
#endif

    static constexpr auto bool_true(bool_type b) noexcept -> bool {
#if EGLPLUS_HAS_EGL
        return b == EGL_TRUE;
#else
        return b;
#endif
    }

    static constexpr auto error_code_no_error(
      [[maybe_unused]] const int_type ec) noexcept -> bool {
#if EGLPLUS_HAS_EGL
        return ec == EGL_SUCCESS;
#else
        return false;
#endif
    }
};
//------------------------------------------------------------------------------
} // namespace eagine::eglplus

#endif // EAGINE_EGLPLUS_EGL_API_CONFIG_HPP
