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

export module eagine.eglplus:enum_types;
import eagine.core.types;
import eagine.core.identifier;
import eagine.core.c_api;
import :config;

namespace eagine::eglplus {
//------------------------------------------------------------------------------
/// @brief Typed wrapper class for EGL enum constants/values.
/// @ingroup egl_api_wrap
///
/// This wrapper uses the specified Id to group various EGL constants logically
/// belonging together and prevents accidental mismatches and use of EGL constants
/// from unrelated groups. For example using a config attribute constant in place
/// of context attribute constants. Such mismatches result in compilation errors.
export template <typename Self, identifier_value Id>
using egl_int_class = c_api::enum_class<Self, egl_types::int_type, "EGL", Id>;

export template <typename Self, identifier_value Id>
using egl_enum_class = c_api::enum_class<Self, egl_types::enum_type, "EGL", Id>;

/// @brief Type erasure alias for EGL enum classes.
/// @ingroup egl_api_wrap
export using egl_any_enum_class = c_api::any_enum_class<"EGL">;

/// @brief Type erasure alias for EGL enum values.
/// @ingroup egl_api_wrap
export using egl_any_enum_value = c_api::any_enum_value<"EGL">;

export constexpr auto same_enum_class(
  const egl_any_enum_class a,
  const egl_any_enum_class b) noexcept -> bool {
    return ::eagine::c_api::same_enum_class(a, b);
}
//------------------------------------------------------------------------------
/// @brief Wrapper for true, false EGL enums.
/// @ingroup egl_api_wrap
export struct true_false : egl_int_class<true_false, "TrueFalse"> {
    using enum_class::enum_class;

    constexpr explicit operator bool() const noexcept {
#ifdef EGL_TRUE
        return this->_value == EGL_TRUE;
#else
        return false;
#endif
    }
};

/// @brief Typed enumeration for EGL error code constants.
/// @ingroup egl_api_wrap
export struct error_code : egl_int_class<error_code, "ErrorCode"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL platform constants.
/// @ingroup egl_api_wrap
export struct platform : egl_enum_class<platform, "Platform"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL engine constants.
/// @ingroup egl_api_wrap
export struct engine : egl_int_class<engine, "Engine"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL platform attribute constants.
/// @ingroup egl_api_wrap
export struct platform_attribute
  : egl_int_class<platform_attribute, "PltfrmAttr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL string query constants.
/// @ingroup egl_api_wrap
export struct string_query : egl_int_class<string_query, "StrQuery"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL device string query constants.
/// @ingroup egl_api_wrap
export struct device_string_query
  : egl_int_class<device_string_query, "DevStrQury"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL config attribute constants.
/// @ingroup egl_api_wrap
export struct config_attribute : egl_int_class<config_attribute, "ConfAttrib"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL config caveat constants.
/// @ingroup egl_api_wrap
export struct config_caveat : egl_int_class<config_caveat, "ConfCaveat"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL surface attribute constants.
/// @ingroup egl_api_wrap
export struct surface_attribute
  : egl_int_class<surface_attribute, "SurfAttrib"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL surface type bit constants.
/// @ingroup egl_api_wrap
export struct surface_type_bit : egl_int_class<surface_type_bit, "SurfTypBit"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL renderable type bit constants.
/// @ingroup egl_api_wrap
export struct renderable_type_bit
  : egl_int_class<renderable_type_bit, "RndrTypBit"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL client API type constants.
/// @ingroup egl_api_wrap
export struct client_api : egl_enum_class<client_api, "ClientApi"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL client API bit constants.
/// @ingroup egl_api_wrap
export struct client_api_bit : egl_int_class<client_api_bit, "ClntApiBit"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL context attribute constants.
/// @ingroup egl_api_wrap
export struct context_attribute
  : egl_int_class<context_attribute, "CtxtAttrib"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL OpenGL profile bit constants.
/// @ingroup egl_api_wrap
export struct context_opengl_profile_bit
  : egl_int_class<context_opengl_profile_bit, "OGLPrflBit"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL stream attribute constants.
/// @ingroup egl_api_wrap
export struct stream_attribute : egl_int_class<stream_attribute, "StreamAttr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL stream state constants.
/// @ingroup egl_api_wrap
export struct stream_state : egl_int_class<stream_attribute, "StreamStat"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL output layer attribute constants.
/// @ingroup egl_api_wrap
export struct output_layer_attribute
  : egl_int_class<output_layer_attribute, "OutLyrAttr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL output layer string query constants.
/// @ingroup egl_api_wrap
export struct output_layer_string_query
  : egl_int_class<output_layer_string_query, "OutLyrStrQ"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL output port attribute constants.
/// @ingroup egl_api_wrap
export struct output_port_attribute
  : egl_int_class<output_port_attribute, "OutPrtAttr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL output port string query constants.
/// @ingroup egl_api_wrap
export struct output_port_string_query
  : egl_int_class<output_port_string_query, "OutPrtStrQ"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL image attribute constants.
/// @ingroup egl_api_wrap
export struct image_attribute : egl_int_class<image_attribute, "ImageAttr"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL image target constants.
/// @ingroup egl_api_wrap
export struct image_target : egl_enum_class<image_target, "ImgeTarget"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL sync object type constants.
/// @ingroup egl_api_wrap
export struct sync_type : egl_enum_class<sync_type, "SyncType"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL sync object attribute constants.
/// @ingroup egl_api_wrap
export struct sync_attribute : egl_int_class<sync_attribute, "SyncAttrib"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL color buffer type constants.
/// @ingroup egl_api_wrap
export struct color_buffer_type
  : egl_int_class<color_buffer_type, "ClrBufType"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL color component type constants.
/// @ingroup egl_api_wrap
export struct color_component_type
  : egl_int_class<color_component_type, "ClrCmpType"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL read/draw specifier constants.
/// @ingroup egl_api_wrap
export struct read_draw : egl_int_class<read_draw, "ReadDraw"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL texture format constants.
/// @ingroup egl_api_wrap
export struct texture_format : egl_int_class<texture_format, "TexFormat"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL texture target constants.
/// @ingroup egl_api_wrap
export struct texture_target : egl_int_class<texture_target, "TexTarget"> {
    using enum_class::enum_class;
};

/// @brief Typed enumeration for EGL OpenGL colorspace constants.
/// @ingroup egl_api_wrap
export struct gl_colorspace : egl_int_class<gl_colorspace, "GLClrspace"> {
    using enum_class::enum_class;
};
//------------------------------------------------------------------------------
} // namespace eagine::eglplus
