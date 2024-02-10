/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
/// https://www.boost.org/LICENSE_1_0.txt
///
module;

#if __has_include(<EGL/egl.h>)
#include <EGL/egl.h>
#define EAGINE_HAS_EGL 1
#else
#define EAGINE_HAS_EGL 0
#endif

export module eagine.eglplus:objects;
import eagine.core.types;
import eagine.core.identifier;
import eagine.core.c_api;
import :config;

namespace eagine::eglplus {
//------------------------------------------------------------------------------
export template <identifier_value Id>
using egl_lib_tag = static_message_id<"egl", Id>;

/// @brief Tag type denoting EGL device object.
/// @ingroup egl_api_wrap
/// @see device_handle
export using device_tag = egl_lib_tag<"Device">;

/// @brief Tag type denoting EGL display object.
/// @ingroup egl_api_wrap
/// @see display_handle
export using display_tag = egl_lib_tag<"Display">;

/// @brief Tag type denoting EGL surface object.
/// @ingroup egl_api_wrap
/// @see surface_handle
export using surface_tag = egl_lib_tag<"Surface">;

/// @brief Tag type denoting EGL context object.
/// @ingroup egl_api_wrap
/// @see context_handle
export using context_tag = egl_lib_tag<"Context">;

/// @brief Tag type denoting EGL stream object.
/// @ingroup egl_api_wrap
/// @see stream_handle
export using stream_tag = egl_lib_tag<"Stream">;

/// @brief Tag type denoting EGL image object.
/// @ingroup egl_api_wrap
/// @see image_handle
export using image_tag = egl_lib_tag<"Image">;

/// @brief Tag type denoting EGL output layer.
/// @ingroup egl_api_wrap
/// @see output_layer_handle
export using output_layer_tag = egl_lib_tag<"OutLayer">;

/// @brief Tag type denoting EGL output port.
/// @ingroup egl_api_wrap
/// @see output_port_handle
export using output_port_tag = egl_lib_tag<"OutPort">;

/// @brief Tag type denoting EGL sync object.
/// @ingroup egl_api_wrap
/// @see sync_handle
export using sync_tag = egl_lib_tag<"Sync">;
//------------------------------------------------------------------------------
/// @brief Alias for EGL device handle wrapper.
/// @ingroup egl_api_wrap
export using device_handle = c_api::basic_handle<
  device_tag,
  egl_types::device_type,
  egl_types::device_type(nullptr)>;
//------------------------------------------------------------------------------
#if defined(EGL_NO_DISPLAY)
export using display_handle =
  c_api::basic_handle<display_tag, egl_types::display_type, EGL_NO_DISPLAY>;

export using owned_display_handle =
  c_api::basic_owned_handle<display_tag, egl_types::display_type, EGL_NO_DISPLAY>;
#else
/// @brief Alias for EGL display  handle wrapper.
/// @ingroup egl_api_wrap
export using display_handle =
  c_api::basic_handle<display_tag, egl_types::display_type>;

/// @brief Alias for owned EGL display handle wrapper.
/// @ingroup egl_api_wrap
export using owned_display_handle =
  c_api::basic_owned_handle<display_tag, egl_types::display_type>;
#endif

export template <typename Api>
using initialized_display_object =
  c_api::basic_object_from_handle_t<Api, display_handle>;
//------------------------------------------------------------------------------
#if defined(EGL_NO_SURFACE)
export using surface_handle =
  c_api::basic_handle<surface_tag, egl_types::surface_type, EGL_NO_SURFACE>;

export using owned_surface_handle =
  c_api::basic_owned_handle<surface_tag, egl_types::surface_type, EGL_NO_SURFACE>;
#else
/// @brief Alias for EGL surface handle wrapper.
/// @ingroup egl_api_wrap
export using surface_handle =
  c_api::basic_handle<surface_tag, egl_types::surface_type>;

/// @brief Alias for owned EGL surface handle wrapper.
/// @ingroup egl_api_wrap
export using owned_surface_handle =
  c_api::basic_owned_handle<surface_tag, egl_types::surface_type>;
#endif
//------------------------------------------------------------------------------
#if defined(EGL_NO_CONTEXT)
export using context_handle =
  c_api::basic_handle<context_tag, egl_types::context_type, EGL_NO_CONTEXT>;

export using owned_context_handle =
  c_api::basic_owned_handle<context_tag, egl_types::context_type, EGL_NO_CONTEXT>;
#else
/// @brief Alias for EGL context handle wrapper.
/// @ingroup egl_api_wrap
export using context_handle =
  c_api::basic_handle<context_tag, egl_types::context_type>;

/// @brief Alias for EGL context handle wrapper.
/// @ingroup egl_api_wrap
export using owned_context_handle =
  c_api::basic_owned_handle<context_tag, egl_types::context_type>;
#endif
//------------------------------------------------------------------------------
/// @brief Alias for EGL stream handle wrapper.
/// @ingroup egl_api_wrap
export using stream_handle = c_api::basic_handle<
  stream_tag,
  egl_types::stream_type,
  egl_types::stream_type(nullptr)>;

/// @brief Alias for owned EGL stream handle wrapper.
/// @ingroup egl_api_wrap
export using owned_stream_handle = c_api::basic_owned_handle<
  stream_tag,
  egl_types::stream_type,
  egl_types::stream_type(nullptr)>;
//------------------------------------------------------------------------------
#if defined(EGL_NO_IMAGE)
export using image_handle =
  c_api::basic_handle<image_tag, egl_types::image_type, EGL_NO_IMAGE>;

export using owned_image_handle =
  c_api::basic_owned_handle<image_tag, egl_types::image_type, EGL_NO_IMAGE>;
#else
/// @brief Alias for EGL image handle wrapper.
/// @ingroup egl_api_wrap
export using image_handle =
  c_api::basic_handle<image_tag, egl_types::image_type>;

/// @brief Alias for owned EGL image handle wrapper.
/// @ingroup egl_api_wrap
export using owned_image_handle =
  c_api::basic_owned_handle<image_tag, egl_types::image_type>;
#endif
//------------------------------------------------------------------------------
/// @brief Alias for EGL output layer handle wrapper.
/// @ingroup egl_api_wrap
export using output_layer_handle = c_api::basic_handle<
  stream_tag,
  egl_types::output_layer_type,
  egl_types::output_layer_type(nullptr)>;

/// @brief Alias for owned EGL output layer handle wrapper.
/// @ingroup egl_api_wrap
export using owned_output_layer_handle = c_api::basic_owned_handle<
  stream_tag,
  egl_types::output_layer_type,
  egl_types::output_layer_type(nullptr)>;
//------------------------------------------------------------------------------
/// @brief Alias for EGL output port handle wrapper.
/// @ingroup egl_api_wrap
export using output_port_handle = c_api::basic_handle<
  stream_tag,
  egl_types::output_port_type,
  egl_types::output_port_type(nullptr)>;

/// @brief Alias for EGL output port handle wrapper.
/// @ingroup egl_api_wrap
export using owned_output_port_handle = c_api::basic_owned_handle<
  stream_tag,
  egl_types::output_port_type,
  egl_types::output_port_type(nullptr)>;
//------------------------------------------------------------------------------
#if defined(EGL_NO_SYNC)
export using sync_handle =
  c_api::basic_handle<sync_tag, egl_types::sync_type, EGL_NO_SYNC>;
#else
/// @brief Alias for EGL sync object handle wrapper.
/// @ingroup egl_api_wrap
export using sync_handle = c_api::basic_handle<sync_tag, egl_types::sync_type>;
#endif
//------------------------------------------------------------------------------
} // namespace eagine::eglplus

