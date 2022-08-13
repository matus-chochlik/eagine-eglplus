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
using device_tag = egl_lib_tag<"Device">;

/// @brief Tag type denoting EGL display object.
/// @ingroup egl_api_wrap
/// @see display_handle
using display_tag = egl_lib_tag<"Display">;

/// @brief Tag type denoting EGL surface object.
/// @ingroup egl_api_wrap
/// @see surface_handle
using surface_tag = egl_lib_tag<"Surface">;

/// @brief Tag type denoting EGL context object.
/// @ingroup egl_api_wrap
/// @see context_handle
using context_tag = egl_lib_tag<"Context">;

/// @brief Tag type denoting EGL stream object.
/// @ingroup egl_api_wrap
/// @see stream_handle
using stream_tag = egl_lib_tag<"Stream">;

/// @brief Tag type denoting EGL image object.
/// @ingroup egl_api_wrap
/// @see image_handle
using image_tag = egl_lib_tag<"Image">;

/// @brief Tag type denoting EGL output layer.
/// @ingroup egl_api_wrap
/// @see output_layer_handle
using output_layer_tag = egl_lib_tag<"OutLayer">;

/// @brief Tag type denoting EGL output port.
/// @ingroup egl_api_wrap
/// @see output_port_handle
using output_port_tag = egl_lib_tag<"OutPort">;

/// @brief Tag type denoting EGL sync object.
/// @ingroup egl_api_wrap
/// @see sync_handle
using sync_tag = egl_lib_tag<"Sync">;
//------------------------------------------------------------------------------
/// @brief Alias for EGL device handle wrapper.
/// @ingroup egl_api_wrap
using device_handle = c_api::basic_handle<
  device_tag,
  egl_types::device_type,
  egl_types::device_type(nullptr)>;
//------------------------------------------------------------------------------
#if defined(EGL_NO_DISPLAY)
using display_handle =
  c_api::basic_handle<display_tag, egl_types::display_type, EGL_NO_DISPLAY>;

using owned_display_handle =
  c_api::basic_owned_handle<display_tag, egl_types::display_type, EGL_NO_DISPLAY>;
#else
/// @brief Alias for EGL display  handle wrapper.
/// @ingroup egl_api_wrap
using display_handle =
  c_api::basic_handle<display_tag, egl_types::display_type>;

/// @brief Alias for owned EGL display handle wrapper.
/// @ingroup egl_api_wrap
using owned_display_handle =
  c_api::basic_owned_handle<display_tag, egl_types::display_type>;
#endif
//------------------------------------------------------------------------------
#if defined(EGL_NO_SURFACE)
using surface_handle =
  c_api::basic_handle<surface_tag, egl_types::surface_type, EGL_NO_SURFACE>;

using owned_surface_handle =
  c_api::basic_owned_handle<surface_tag, egl_types::surface_type, EGL_NO_SURFACE>;
#else
/// @brief Alias for EGL surface handle wrapper.
/// @ingroup egl_api_wrap
using surface_handle =
  c_api::basic_handle<surface_tag, egl_types::surface_type>;

/// @brief Alias for owned EGL surface handle wrapper.
/// @ingroup egl_api_wrap
using owned_surface_handle =
  c_api::basic_owned_handle<surface_tag, egl_types::surface_type>;
#endif
//------------------------------------------------------------------------------
#if defined(EGL_NO_CONTEXT)
using context_handle =
  c_api::basic_handle<context_tag, egl_types::context_type, EGL_NO_CONTEXT>;

using owned_context_handle =
  c_api::basic_owned_handle<context_tag, egl_types::context_type, EGL_NO_CONTEXT>;
#else
/// @brief Alias for EGL context handle wrapper.
/// @ingroup egl_api_wrap
using context_handle =
  c_api::basic_handle<context_tag, egl_types::context_type>;

/// @brief Alias for EGL context handle wrapper.
/// @ingroup egl_api_wrap
using owned_context_handle =
  c_api::basic_owned_handle<context_tag, egl_types::context_type>;
#endif
//------------------------------------------------------------------------------
/// @brief Alias for EGL stream handle wrapper.
/// @ingroup egl_api_wrap
using stream_handle = c_api::basic_handle<
  stream_tag,
  egl_types::stream_type,
  egl_types::stream_type(nullptr)>;

/// @brief Alias for owned EGL stream handle wrapper.
/// @ingroup egl_api_wrap
using owned_stream_handle = c_api::basic_owned_handle<
  stream_tag,
  egl_types::stream_type,
  egl_types::stream_type(nullptr)>;
//------------------------------------------------------------------------------
#if defined(EGL_NO_IMAGE)
using image_handle =
  c_api::basic_handle<image_tag, egl_types::image_type, EGL_NO_IMAGE>;

using owned_image_handle =
  c_api::basic_owned_handle<image_tag, egl_types::image_type, EGL_NO_IMAGE>;
#else
/// @brief Alias for EGL image handle wrapper.
/// @ingroup egl_api_wrap
using image_handle = c_api::basic_handle<image_tag, egl_types::image_type>;

/// @brief Alias for owned EGL image handle wrapper.
/// @ingroup egl_api_wrap
using owned_image_handle =
  c_api::basic_owned_handle<image_tag, egl_types::image_type>;
#endif
//------------------------------------------------------------------------------
/// @brief Alias for EGL output layer handle wrapper.
/// @ingroup egl_api_wrap
using output_layer_handle = c_api::basic_handle<
  stream_tag,
  egl_types::output_layer_type,
  egl_types::output_layer_type(nullptr)>;

/// @brief Alias for owned EGL output layer handle wrapper.
/// @ingroup egl_api_wrap
using owned_output_layer_handle = c_api::basic_owned_handle<
  stream_tag,
  egl_types::output_layer_type,
  egl_types::output_layer_type(nullptr)>;
//------------------------------------------------------------------------------
/// @brief Alias for EGL output port handle wrapper.
/// @ingroup egl_api_wrap
using output_port_handle = c_api::basic_handle<
  stream_tag,
  egl_types::output_port_type,
  egl_types::output_port_type(nullptr)>;

/// @brief Alias for EGL output port handle wrapper.
/// @ingroup egl_api_wrap
using owned_output_port_handle = c_api::basic_owned_handle<
  stream_tag,
  egl_types::output_port_type,
  egl_types::output_port_type(nullptr)>;
//------------------------------------------------------------------------------
#if defined(EGL_NO_SYNC)
using sync_handle =
  c_api::basic_handle<sync_tag, egl_types::sync_type, EGL_NO_SYNC>;
#else
/// @brief Alias for EGL sync object handle wrapper.
/// @ingroup egl_api_wrap
using sync_handle = c_api::basic_handle<sync_tag, egl_types::sync_type>;
#endif
//------------------------------------------------------------------------------
} // namespace eagine::eglplus

