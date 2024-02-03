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

export module eagine.eglplus:c_api;
import eagine.core.types;
import eagine.core.memory;
import eagine.core.c_api;
import :config;
import :result;

#ifndef EGLPLUS_EGL_STATIC_FUNC
#if EAGINE_HAS_EGL
#define EGLPLUS_EGL_STATIC_FUNC(NAME) &::egl##NAME
#else
#define EGLPLUS_EGL_STATIC_FUNC(NAME) nullptr
#endif
#endif

namespace eagine::eglplus {
//------------------------------------------------------------------------------
/// @brief Class wrapping the C-functions from the EGL API.
/// @ingroup egl_api_wrap
/// @see basic_egl_constants
/// @see basic_egl_operations
export template <typename ApiTraits>
class basic_egl_c_api {
    ApiTraits& _traits;

public:
    using this_api = basic_egl_c_api;

    /// @brief Alias for the API traits policy type passed as template argument.
    using api_traits = ApiTraits;

    static constexpr bool has_api = egl_types::has_api;

    /// @brief Untyped non-const pointer type.
    using void_ptr_type = typename egl_types::void_ptr_type;

    /// @brief Alias for time duration type.
    using time_type = typename egl_types::time_type;

    /// @brief Alias for sync type.
    using sync_type = typename egl_types::sync_type;

    /// @brief Alias for enumeration type.
    using enum_type = typename egl_types::enum_type;

    /// @brief Alias for boolean type.
    using bool_type = typename egl_types::bool_type;

    /// @brief Alias for string character type.
    using char_type = typename egl_types::char_type;

    /// @brief Alias for signed integer type.
    using int_type = typename egl_types::int_type;

    /// @brief Alias for device handle type.
    using device_type = typename egl_types::device_type;

    /// @brief Alias for native display handle type.
    using native_display_type = typename egl_types::native_display_type;

    /// @brief Alias for native window handle type.
    using native_window_type = typename egl_types::native_window_type;

    /// @brief Alias for native pixmap handle type.
    using native_pixmap_type = typename egl_types::native_pixmap_type;

    /// @brief Alias for client buffer handle type.
    using client_buffer_type = typename egl_types::client_buffer_type;

    /// @brief Alias for display handle type.
    using display_type = typename egl_types::display_type;

    /// @brief Alias for surface handle type.
    using surface_type = typename egl_types::surface_type;

    /// @brief Alias for config handle type.
    using config_type = typename egl_types::config_type;

    /// @brief Alias for attribute type.
    using attrib_type = typename egl_types::attrib_type;

    /// @brief Alias for context handle type.
    using context_type = typename egl_types::context_type;

    /// @brief Alias for stream handle type.
    using stream_type = typename egl_types::stream_type;

    /// @brief Alias for output layer handle type.
    using output_layer_type = typename egl_types::output_layer_type;

    /// @brief Alias for output port handle type.
    using output_port_type = typename egl_types::output_port_type;

    /// @brief Alias for image handle type.
    using image_type = typename egl_types::image_type;

    template <typename Result, typename... U>
    constexpr auto check_result(Result res, U&&...) const noexcept {
        res.error_code(this->GetError());
        return res;
    }

    template <typename Result, typename Info, c_api::result_validity Validity>
    static constexpr auto collapse(
      c_api::result<Result, Info, Validity>&& r) noexcept {
        return r.collapsed(
          [](egl_types::bool_type value) { return bool(value); },
          [](auto& info) { info.set_unknown_error(); });
    }

    /// @brief Alias for EGL C-API function wrapper template.
    template <
      typename Signature,
      c_api::function_ptr<api_traits, nothing_t, Signature> Function>
    using egl_api_function = c_api::opt_function<
      api_traits,
      nothing_t,
      Signature,
      Function,
      has_api,
      bool(Function)>;

    /// @var GetError
    /// @eglfuncwrap{GetError}
    egl_api_function<int_type(), EGLPLUS_EGL_STATIC_FUNC(GetError)> GetError{
      "GetError",
      *this};

    /// @var GetProcAddress
    /// @eglfuncwrap{GetProcAddress}
    egl_api_function<
      void (*(const char_type*))(),
      EGLPLUS_EGL_STATIC_FUNC(GetProcAddress)>
      GetProcAddress{"GetProcAddress", *this};

    /// @var QueryDevices
    /// @eglfuncwrap{QueryDevices}
    egl_api_function<bool_type(int_type, device_type*, int_type*), nullptr>
      QueryDevices{"QueryDevicesEXT", *this};

    /// @var QueryDeviceString
    /// @eglfuncwrap{QueryDeviceString}
    egl_api_function<const char_type*(device_type, int_type), nullptr>
      QueryDeviceString{"QueryDeviceStringEXT", *this};

    /// @var GetPlatformDisplay
    /// @eglfuncwrap{GetPlatformDisplay}
    egl_api_function<
      display_type(enum_type, void_ptr_type, const attrib_type*),
      EGLPLUS_EGL_STATIC_FUNC(GetPlatformDisplay)>
      GetPlatformDisplay{"GetPlatformDisplay", *this};

    /// @var GetDisplay
    /// @eglfuncwrap{GetDisplay}
    egl_api_function<
      display_type(native_display_type),
      EGLPLUS_EGL_STATIC_FUNC(GetDisplay)>
      GetDisplay{"GetDisplay", *this};

    /// @var GetDisplayDriverName
    /// @eglfuncwrap{GetDisplayDriverName}
    egl_api_function<const char_type*(display_type), nullptr>
      GetDisplayDriverName{"GetDisplayDriverName", *this};

    /// @var Initialize
    /// @eglfuncwrap{Initialize}
    egl_api_function<
      bool_type(display_type, int_type*, int_type*),
      EGLPLUS_EGL_STATIC_FUNC(Initialize)>
      Initialize{"Initialize", *this};

    /// @var Terminate
    /// @eglfuncwrap{Terminate}
    egl_api_function<bool_type(display_type), EGLPLUS_EGL_STATIC_FUNC(Terminate)>
      Terminate{"Terminate", *this};

    /// @var QueryString
    /// @eglfuncwrap{QueryString}
    egl_api_function<
      const char_type*(display_type, int_type),
      EGLPLUS_EGL_STATIC_FUNC(QueryString)>
      QueryString{"QueryString", *this};

    /// @var GetConfigs
    /// @eglfuncwrap{GetConfigs}
    egl_api_function<
      bool_type(display_type, config_type*, int_type, int_type*),
      EGLPLUS_EGL_STATIC_FUNC(GetConfigs)>
      GetConfigs{"GetConfigs", *this};

    /// @var ChooseConfig
    /// @eglfuncwrap{ChooseConfig}
    egl_api_function<
      bool_type(display_type, const int_type*, config_type*, int_type, int_type*),
      EGLPLUS_EGL_STATIC_FUNC(ChooseConfig)>
      ChooseConfig{"ChooseConfig", *this};

    /// @var GetConfigAttrib
    /// @eglfuncwrap{GetConfigAttrib}
    egl_api_function<
      bool_type(display_type, config_type, int_type, int_type*),
      EGLPLUS_EGL_STATIC_FUNC(GetConfigAttrib)>
      GetConfigAttrib{"GetConfigAttrib", *this};

    /// @var CreatePlatformWindowSurface
    /// @eglfuncwrap{CreatePlatformWindowSurface}
    egl_api_function<
      surface_type(display_type, config_type, void_ptr_type, const attrib_type*),
      EGLPLUS_EGL_STATIC_FUNC(CreatePlatformWindowSurface)>
      CreatePlatformWindowSurface{"CreatePlatformWindowSurface", *this};

    /// @var CreateWindowSurface
    /// @eglfuncwrap{CreateWindowSurface}
    egl_api_function<
      surface_type(display_type, config_type, native_window_type, const int_type*),
      EGLPLUS_EGL_STATIC_FUNC(CreateWindowSurface)>
      CreateWindowSurface{"CreateWindowSurface", *this};

    /// @var CreatePbufferSurface
    /// @eglfuncwrap{CreatePbufferSurface}
    egl_api_function<
      surface_type(display_type, config_type, const int_type*),
      EGLPLUS_EGL_STATIC_FUNC(CreatePbufferSurface)>
      CreatePbufferSurface{"CreatePbufferSurface", *this};

    /// @var CreatePlatformPixmapSurface
    /// @eglfuncwrap{CreatePlatformPixmapSurface}
    egl_api_function<
      surface_type(display_type, config_type, void_ptr_type, const attrib_type*),
      EGLPLUS_EGL_STATIC_FUNC(CreatePlatformPixmapSurface)>
      CreatePlatformPixmapSurface{"CreatePlatformPixmapSurface", *this};

    /// @var CreatePixmapSurface
    /// @eglfuncwrap{CreatePixmapSurface}
    egl_api_function<
      surface_type(display_type, config_type, native_pixmap_type, const int_type*),
      EGLPLUS_EGL_STATIC_FUNC(CreatePixmapSurface)>
      CreatePixmapSurface{"CreatePixmapSurface", *this};

    /// @var CreateStreamProducerSurface
    /// @eglfuncwrap{CreateStreamProducerSurface}
    egl_api_function<
      surface_type(display_type, config_type, stream_type, const int_type*),
      nullptr>
      CreateStreamProducerSurface{"CreateStreamProducerSurfaceKHR", *this};

    /// @var DestroySurface
    /// @eglfuncwrap{DestroySurface}
    egl_api_function<
      bool_type(display_type, surface_type),
      EGLPLUS_EGL_STATIC_FUNC(DestroySurface)>
      DestroySurface{"DestroySurface", *this};

    /// @var GetCurrentSurface
    /// @eglfuncwrap{GetCurrentSurface}
    egl_api_function<
      surface_type(int_type),
      EGLPLUS_EGL_STATIC_FUNC(GetCurrentSurface)>
      GetCurrentSurface{"GetCurrentSurface", *this};

    /// @var SurfaceAttrib
    /// @eglfuncwrap{SurfaceAttrib}
    egl_api_function<
      bool_type(display_type, surface_type, int_type, int_type),
      EGLPLUS_EGL_STATIC_FUNC(SurfaceAttrib)>
      SurfaceAttrib{"SurfaceAttrib", *this};

    /// @var QuerySurface
    /// @eglfuncwrap{QuerySurface}
    egl_api_function<
      bool_type(display_type, surface_type, int_type, int_type*),
      EGLPLUS_EGL_STATIC_FUNC(QuerySurface)>
      QuerySurface{"QuerySurface", *this};

    /// @var CreateStream
    /// @eglfuncwrap{CreateStream}
    egl_api_function<surface_type(display_type, const int_type*), nullptr>
      CreateStream{"CreateStreamKHR", *this};

    /// @var DestroyStream
    /// @eglfuncwrap{DestroyStream}
    egl_api_function<bool_type(display_type, stream_type), nullptr>
      DestroyStream{"DestroyStreamKHR", *this};

    /// @var StreamAttrib
    /// @eglfuncwrap{StreamAttrib}
    egl_api_function<
      bool_type(display_type, stream_type, int_type, int_type),
      nullptr>
      StreamAttrib{"StreamAttribKHR", *this};

    /// @var QueryStream
    /// @eglfuncwrap{QueryStream}
    egl_api_function<
      bool_type(display_type, stream_type, int_type, int_type*),
      nullptr>
      QueryStream{"QueryStream", *this};

    /// @var StreamConsumerGLTextureExternal
    /// @eglfuncwrap{StreamConsumerGLTextureExternal}
    egl_api_function<bool_type(display_type, stream_type), nullptr>
      StreamConsumerGLTextureExternal{
        "StreamConsumerGLTextureExternalKHR",
        *this};

    /// @var StreamConsumerAcquire
    /// @eglfuncwrap{GetErrorsumerAcquire}
    egl_api_function<bool_type(display_type, stream_type), nullptr>
      StreamConsumerAcquire{"StreamConsumerAcquireKHR", *this};

    /// @var StreamConsumerRelease
    /// @eglfuncwrap{StreamConsumerRelease}
    egl_api_function<bool_type(display_type, stream_type), nullptr>
      StreamConsumerRelease{"StreamConsumerReleaseKHR", *this};

    /// @var GetOutputLayers
    /// @eglfuncwrap{GetOutputLayers}
    egl_api_function<
      bool_type(
        display_type,
        const attrib_type*,
        output_layer_type*,
        int_type,
        int_type*),
      nullptr>
      GetOutputLayers{"GetOutputLayersEXT", *this};

    /// @var OutputLayerAttrib
    /// @eglfuncwrap{OutputLayerAttrib}
    egl_api_function<
      bool_type(display_type, output_layer_type, int_type, attrib_type),
      nullptr>
      OutputLayerAttrib{"OutputLayerAttribEXT", *this};

    /// @var QueryOutputLayerAttrib
    /// @eglfuncwrap{QueryOutputLayerAttrib}
    egl_api_function<
      bool_type(display_type, output_layer_type, int_type, attrib_type*),
      nullptr>
      QueryOutputLayerAttrib{"QueryOutputLayerAttribEXT", *this};

    /// @var QueryOutputLayerString
    /// @eglfuncwrap{QueryOutputLayerString}
    egl_api_function<
      const char_type*(display_type, output_layer_type, int_type),
      nullptr>
      QueryOutputLayerString{"QueryOutputLayerStringEXT", *this};

    /// @var GetOutputPorts
    /// @eglfuncwrap{GetOutputPorts}
    egl_api_function<
      bool_type(
        display_type,
        const attrib_type*,
        output_port_type*,
        int_type,
        int_type*),
      nullptr>
      GetOutputPorts{"GetOutputPortsEXT", *this};

    /// @var OutputPortAttrib
    /// @eglfuncwrap{OutputPortAttrib}
    egl_api_function<
      bool_type(display_type, output_port_type, int_type, attrib_type),
      nullptr>
      OutputPortAttrib{"OutputPortAttribEXT", *this};

    /// @var QueryOutputPortAttrib
    /// @eglfuncwrap{QueryOutputPortAttrib}
    egl_api_function<
      bool_type(display_type, output_port_type, int_type, attrib_type*),
      nullptr>
      QueryOutputPortAttrib{"QueryOutputPortAttribEXT", *this};

    /// @var QueryOutputPortString
    /// @eglfuncwrap{QueryOutputPortString}
    egl_api_function<
      const char_type*(display_type, output_port_type, int_type),
      nullptr>
      QueryOutputPortString{"QueryOutputPortStringEXT", *this};

    /// @var BindTexImage
    /// @eglfuncwrap{BindTexImage}
    egl_api_function<
      bool_type(display_type, surface_type, int_type),
      EGLPLUS_EGL_STATIC_FUNC(BindTexImage)>
      BindTexImage{"BindTexImage", *this};

    /// @var ReleaseTexImage
    /// @eglfuncwrap{ReleaseTexImage}
    egl_api_function<
      bool_type(display_type, surface_type, int_type),
      EGLPLUS_EGL_STATIC_FUNC(ReleaseTexImage)>
      ReleaseTexImage{"ReleaseTexImage", *this};

    /// @var BindAPI
    /// @eglfuncwrap{BindAPI}
    egl_api_function<bool_type(enum_type), EGLPLUS_EGL_STATIC_FUNC(BindAPI)>
      BindAPI{"BindAPI", *this};

    /// @var QueryAPI
    /// @eglfuncwrap{QueryAPI}
    egl_api_function<enum_type(), EGLPLUS_EGL_STATIC_FUNC(QueryAPI)> QueryAPI{
      "QueryAPI",
      *this};

    /// @var CreateContext
    /// @eglfuncwrap{CreateContext}
    egl_api_function<
      context_type(display_type, config_type, context_type, const int_type*),
      EGLPLUS_EGL_STATIC_FUNC(CreateContext)>
      CreateContext{"CreateContext", *this};

    /// @var DestroyContext
    /// @eglfuncwrap{DestroyContext}
    egl_api_function<
      bool_type(display_type, context_type),
      EGLPLUS_EGL_STATIC_FUNC(DestroyContext)>
      DestroyContext{"DestroyContext", *this};

    /// @var MakeCurrent
    /// @eglfuncwrap{MakeCurrent}
    egl_api_function<
      bool_type(display_type, surface_type, surface_type, context_type),
      EGLPLUS_EGL_STATIC_FUNC(MakeCurrent)>
      MakeCurrent{"MakeCurrent", *this};

    /// @var GetCurrentContext
    /// @eglfuncwrap{GetCurrentContext}
    egl_api_function<context_type(), EGLPLUS_EGL_STATIC_FUNC(GetCurrentContext)>
      GetCurrentContext{"GetCurrentContext", *this};

    /// @var QueryContext
    /// @eglfuncwrap{QueryContext}
    egl_api_function<
      bool_type(display_type, context_type, int_type, int_type*),
      EGLPLUS_EGL_STATIC_FUNC(QueryContext)>
      QueryContext{"QueryContext", *this};

    /// @var WaitClient
    /// @eglfuncwrap{WaitClient}
    egl_api_function<bool_type(), EGLPLUS_EGL_STATIC_FUNC(WaitClient)>
      WaitClient{"WaitClient", *this};

    /// @var WaitNative
    /// @eglfuncwrap{WaitNative}
    egl_api_function<bool_type(int_type), EGLPLUS_EGL_STATIC_FUNC(WaitNative)>
      WaitNative{"WaitNative", *this};

    /// @var CreateSync
    /// @eglfuncwrap{CreateSync}
    egl_api_function<
      sync_type(display_type, enum_type, const attrib_type*),
      EGLPLUS_EGL_STATIC_FUNC(CreateSync)>
      CreateSync{"CreateSync", *this};

    /// @var ClientWaitSync
    /// @eglfuncwrap{ClientWaitSync}
    egl_api_function<
      int_type(display_type, sync_type, int_type, time_type),
      EGLPLUS_EGL_STATIC_FUNC(ClientWaitSync)>
      ClientWaitSync{"ClientWaitSync", *this};

    /// @var WaitSync
    /// @eglfuncwrap{WaitSync}
    egl_api_function<
      bool_type(display_type, sync_type, int_type),
      EGLPLUS_EGL_STATIC_FUNC(WaitSync)>
      WaitSync{"WaitSync", *this};

    /// @var GetSyncAttrib
    /// @eglfuncwrap{GetSyncAttrib}
    egl_api_function<
      bool_type(display_type, sync_type, int_type, attrib_type*),
      EGLPLUS_EGL_STATIC_FUNC(GetSyncAttrib)>
      GetSyncAttrib{"GetSyncAttrib", *this};

    /// @var DestroySync
    /// @eglfuncwrap{DestroySync}
    egl_api_function<
      bool_type(display_type, sync_type),
      EGLPLUS_EGL_STATIC_FUNC(DestroySync)>
      DestroySync{"DestroySync", *this};

    /// @var CreateImage
    /// @eglfuncwrap{CreateImage}
    egl_api_function<
      image_type(
        display_type,
        context_type,
        enum_type,
        client_buffer_type,
        const attrib_type*),
      EGLPLUS_EGL_STATIC_FUNC(CreateImage)>
      CreateImage{"CreateImage", *this};

    /// @var DestroyImage
    /// @eglfuncwrap{DestroyImage}
    egl_api_function<
      bool_type(display_type, image_type),
      EGLPLUS_EGL_STATIC_FUNC(DestroyImage)>
      DestroyImage{"DestroyImage", *this};

    /// @var CopyBuffers
    /// @eglfuncwrap{CopyBuffers}
    egl_api_function<
      bool_type(display_type, surface_type, native_pixmap_type),
      EGLPLUS_EGL_STATIC_FUNC(CopyBuffers)>
      CopyBuffers{"CopyBuffers", *this};

    /// @var SwapInterval
    /// @eglfuncwrap{SwapInterval}
    egl_api_function<
      bool_type(display_type, int_type),
      EGLPLUS_EGL_STATIC_FUNC(SwapInterval)>
      SwapInterval{"SwapInterval", *this};

    /// @var SwapBuffers
    /// @eglfuncwrap{SwapBuffers}
    egl_api_function<
      bool_type(display_type, surface_type),
      EGLPLUS_EGL_STATIC_FUNC(SwapBuffers)>
      SwapBuffers{"SwapBuffers", *this};

    /// @var SwapBuffersWithDamage
    /// @eglfuncwrap{SwapBuffersWithDamage}
    egl_api_function<
      bool_type(display_type, surface_type, const int_type*, int_type),
      nullptr>
      SwapBuffersWithDamage{"SwapBuffersWithDamageEXT", *this};

    /// @var ReleaseThread
    /// @eglfuncwrap{ReleaseThread}
    egl_api_function<bool_type(), EGLPLUS_EGL_STATIC_FUNC(ReleaseThread)>
      ReleaseThread{"ReleaseThread", *this};

    basic_egl_c_api(api_traits& traits)
      : _traits{traits} {}

    auto traits() noexcept -> api_traits& {
        return _traits;
    }
};
//------------------------------------------------------------------------------
} // namespace eagine::eglplus

