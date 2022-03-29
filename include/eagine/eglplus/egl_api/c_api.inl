/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

namespace eagine::eglplus {
//------------------------------------------------------------------------------
template <typename ApiTraits>
basic_egl_c_api<ApiTraits>::basic_egl_c_api(api_traits& traits)
  : _traits{traits}
  , GetError{"GetError", *this}
  , GetProcAddress{"GetProcAddress", *this}
  , QueryDevices{"QueryDevicesEXT", *this}
  , QueryDeviceString{"QueryDeviceStringEXT", *this}
  , GetPlatformDisplay{"GetPlatformDisplay", *this}
  , GetDisplay{"GetDisplay", *this}
  , GetDisplayDriverName{"GetDisplayDriverName", *this}
  , Initialize{"Initialize", *this}
  , Terminate{"Terminate", *this}
  , QueryString{"QueryString", *this}
  , GetConfigs{"GetConfigs", *this}
  , ChooseConfig{"ChooseConfig", *this}
  , GetConfigAttrib{"GetConfigAttrib", *this}
  , CreatePlatformWindowSurface{"CreatePlatformWindowSurface", *this}
  , CreateWindowSurface{"CreateWindowSurface", *this}
  , CreatePbufferSurface{"CreatePbufferSurface", *this}
  , CreatePlatformPixmapSurface{"CreatePlatformPixmapSurface", *this}
  , CreatePixmapSurface{"CreatePixmapSurface", *this}
  , CreateStreamProducerSurface{"CreateStreamProducerSurfaceKHR", *this}
  , DestroySurface{"DestroySurface", *this}
  , GetCurrentSurface{"GetCurrentSurface", *this}
  , SurfaceAttrib{"SurfaceAttrib", *this}
  , QuerySurface{"QuerySurface", *this}
  , CreateStream{"CreateStreamKHR", *this}
  , DestroyStream{"DestroyStreamKHR", *this}
  , StreamAttrib{"StreamAttribKHR", *this}
  , QueryStream{"QueryStream", *this}
  , StreamConsumerGLTextureExternal{"StreamConsumerGLTextureExternalKHR", *this}
  , StreamConsumerAcquire{"StreamConsumerAcquireKHR", *this}
  , StreamConsumerRelease{"StreamConsumerReleaseKHR", *this}
  , GetOutputLayers{"GetOutputLayersEXT", *this}
  , OutputLayerAttrib{"OutputLayerAttribEXT", *this}
  , QueryOutputLayerAttrib{"QueryOutputLayerAttribEXT", *this}
  , QueryOutputLayerString{"QueryOutputLayerStringEXT", *this}
  , GetOutputPorts{"GetOutputPortsEXT", *this}
  , OutputPortAttrib{"OutputPortAttribEXT", *this}
  , QueryOutputPortAttrib{"QueryOutputPortAttribEXT", *this}
  , QueryOutputPortString{"QueryOutputPortStringEXT", *this}
  , BindTexImage{"BindTexImage", *this}
  , ReleaseTexImage{"ReleaseTexImage", *this}
  , BindAPI{"BindAPI", *this}
  , QueryAPI{"QueryAPI", *this}
  , CreateContext{"CreateContext", *this}
  , DestroyContext{"DestroyContext", *this}
  , MakeCurrent{"MakeCurrent", *this}
  , GetCurrentContext{"GetCurrentContext", *this}
  , QueryContext{"QueryContext", *this}
  , WaitClient{"WaitClient", *this}
  , WaitNative{"WaitNative", *this}
  , CreateSync{"CreateSync", *this}
  , ClientWaitSync{"ClientWaitSync", *this}
  , WaitSync{"WaitSync", *this}
  , GetSyncAttrib{"GetSyncAttrib", *this}
  , DestroySync{"DestroySync", *this}
  , CreateImage{"CreateImage", *this}
  , DestroyImage{"DestroyImage", *this}
  , CopyBuffers{"CopyBuffers", *this}
  , SwapInterval{"SwapInterval", *this}
  , SwapBuffers{"SwapBuffers", *this}
  , SwapBuffersWithDamage{"SwapBuffersWithDamageEXT", *this}
  , ReleaseThread{"ReleaseThread", *this} {}
//------------------------------------------------------------------------------
} // namespace eagine::eglplus
