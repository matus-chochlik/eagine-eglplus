/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_EGLPLUS_EGL_API_API_HPP
#define EAGINE_EGLPLUS_EGL_API_API_HPP

#include "c_api.hpp"
#include "config_attribs.hpp"
#include "context_attribs.hpp"
#include "enum_types.hpp"
#include "extensions.hpp"
#include "image_attribs.hpp"
#include "objects.hpp"
#include "output_layer_attribs.hpp"
#include "output_port_attribs.hpp"
#include "platform_attribs.hpp"
#include "stream_attribs.hpp"
#include "surface_attribs.hpp"
#include "sync_attribs.hpp"
#include <eagine/c_api/adapted_function.hpp>
#include <eagine/scope_exit.hpp>
#include <eagine/string_list.hpp>
#include <chrono>

#ifndef EGL_EXTENSIONS
#define EGL_EXTENSIONS 0x3055
#endif

#ifndef EGL_PLATFORM_DEVICE_EXT
#define EGL_PLATFORM_DEVICE_EXT 0x313F
#endif

namespace eagine::eglplus {
using c_api::adapted_function;
//------------------------------------------------------------------------------
#define EGLPAFP(FUNC) decltype(egl_api::FUNC), &egl_api::FUNC
//------------------------------------------------------------------------------
/// @brief Class wrapping the functions from the EGL API.
/// @ingroup egl_api_wrap
/// @see basic_egl_constants
/// @see basic_egl_c_api
template <typename ApiTraits>
class basic_egl_operations : public basic_egl_c_api<ApiTraits> {

public:
    using api_traits = ApiTraits;
    using egl_api = basic_egl_c_api<ApiTraits>;

    using void_ptr_type = typename egl_types::void_ptr_type;
    using int_type = typename egl_types::int_type;
    using bool_type = typename egl_types::char_type;
    using char_type = typename egl_types::char_type;
    using enum_type = typename egl_types::enum_type;
    using time_type = typename egl_types::time_type;
    using attrib_type = typename egl_types::attrib_type;
    using device_type = typename egl_types::device_type;
    using native_display_type = typename egl_types::native_display_type;
    using native_window_type = typename egl_types::native_window_type;
    using native_pixmap_type = typename egl_types::native_pixmap_type;
    using client_buffer_type = typename egl_types::client_buffer_type;
    using config_type = typename egl_types::config_type;
    using output_layer_type = typename egl_types::output_layer_type;
    using output_port_type = typename egl_types::output_port_type;

    struct collapse_bool_map {
        template <typename... P>
        constexpr auto operator()(size_constant<0> i, P&&... p) const noexcept {
            return collapse_bool(
              c_api::trivial_map{}(i, std::forward<P>(p)...));
        }
    };

    // extensions
    template <typename... Args>
    using extension = basic_egl_extension<ApiTraits, Args...>;

    extension<> EXT_device_base;
    extension<> EXT_device_enumeration;
    extension<> EXT_device_query;
    extension<> EXT_device_query_name;
    extension<device_handle> EXT_device_drm;
    extension<device_handle> MESA_device_software;

    extension<> EXT_platform_base;
    extension<> EXT_platform_device;
    extension<> EXT_platform_x11;
    extension<> EXT_platform_xcb;
    extension<> EXT_platform_wayland;
    extension<> KHR_platform_gbm;
    extension<> MESA_platform_surfaceless;

    extension<display_handle> EXT_create_context_robustness;
    extension<display_handle> EXT_swap_buffers_with_damage;

    extension<display_handle> EXT_output_base;
    extension<display_handle> EXT_output_drm;
    extension<display_handle> EXT_stream_consumer_egloutput;

    extension<display_handle> EXT_pixel_format_float;

    extension<display_handle> MESA_configless_context;
    extension<display_handle> MESA_query_driver;

    using _query_devices_t = adapted_function<
      &egl_api::QueryDevices,
      bool_type(span<device_type>, int_type&),
      collapse_bool_map>;

    struct : _query_devices_t {
        using base = _query_devices_t;
        using base::base;

        auto count() const noexcept {
            int_type ret_count{0};
            return base::operator()({}, ret_count)
              .transformed([&ret_count](bool valid) {
                  return limit_cast<span_size_t>(valid ? ret_count : 0);
              });
        }

        auto operator()(span<device_type> dest) const noexcept {
            int_type ret_count{0};
            return base::operator()(dest, ret_count)
              .transformed([dest, &ret_count](bool valid) {
                  return head(
                    dest, limit_cast<span_size_t>(valid ? ret_count : 0));
              });
        }
    } query_devices{*this};

    adapted_function<
      &egl_api::QueryDeviceString,
      string_view(device_handle, device_string_query)>
      query_device_string{*this};

    // get_device_extensions
    auto get_device_extensions(device_handle dev) const noexcept {
        return query_device_string(dev, device_string_query(EGL_EXTENSIONS))
          .transformed(
            [](auto src, bool) { return split_into_string_list(src, ' '); });
    }

    using _get_platform_display_t = adapted_function<
      &egl_api::GetPlatformDisplay,
      display_handle(platform, void_ptr_type, span<const attrib_type>)>;

    struct : _get_platform_display_t {
        using base = _get_platform_display_t;
        using base::base;
        using base::operator();

        constexpr auto operator()(platform pltf, void_ptr_type disp)
          const noexcept {
            return base::operator()(pltf, disp, {});
        }

        constexpr auto operator()(device_handle dev) const noexcept {
            return base::operator()(
              platform(EGL_PLATFORM_DEVICE_EXT), device_type(dev), {});
        }
    } get_platform_display{*this};

    using _get_display_t =
      adapted_function<&egl_api::GetDisplay, display_handle(native_display_type)>;

    struct : _get_display_t {
        using base = _get_display_t;
        using base::base;
        using base::operator();

        constexpr auto operator()() const noexcept {
#ifdef EGL_DEFAULT_DISPLAY
            return base::operator()(EGL_DEFAULT_DISPLAY);
#else
            return base::fail();
#endif
        }
    } get_display{*this};

    adapted_function<&egl_api::GetDisplayDriverName, string_view(display_handle)>
      get_display_driver_name{*this};

    using _initialize_t = adapted_function<
      &egl_api::Initialize,
      bool_type(display_handle, int&, int&),
      collapse_bool_map>;

    struct : _initialize_t {
        using base = _initialize_t;
        using base::base;
        using base::operator();

        constexpr auto operator()(display_handle disp) const noexcept {
            int_type maj{-1};
            int_type min{-1};
            return base::operator()(disp, maj, min);
        }
    } initialize{*this};

    adapted_function<
      &egl_api::Terminate,
      string_view(display_handle),
      collapse_bool_map>
      terminate{*this};

    using _get_configs_t = adapted_function<
      &egl_api::GetConfigs,
      string_view(display_handle disp, span<config_type> dest, int_type&),
      collapse_bool_map>;

    struct : _get_configs_t {
        using base = _get_configs_t;
        using base::base;

        auto count(display_handle disp) const noexcept {
            int_type ret_count{0};
            return base::operator()(disp, {}, ret_count)
              .transformed([&ret_count](bool valid) {
                  return limit_cast<span_size_t>(valid ? ret_count : 0);
              });
        }
        auto operator()(display_handle disp, span<config_type> dest)
          const noexcept {
            int_type ret_count{0};
            return base::operator()(disp, dest, ret_count)
              .transformed([&ret_count, dest](bool valid) {
                  return head(
                    dest, limit_cast<span_size_t>(valid ? ret_count : 0));
              });
        }
    } get_configs{*this};

    using _choose_config_t = adapted_function<
      &egl_api::ChooseConfig,
      bool_type(
        display_handle disp,
        span<const int_type>,
        span<config_type> dest,
        int_type&),
      collapse_bool_map>;

    struct : _choose_config_t {
        using base = _choose_config_t;
        using base::base;
        using base::operator();

        auto count(display_handle disp, span<const int_type> attribs)
          const noexcept {
            int_type ret_count{0};
            return base::operator()(disp, attribs, {}, ret_count)
              .transformed([&ret_count](bool valid) {
                  return limit_cast<span_size_t>(valid ? ret_count : 0);
              });
        }

        template <std::size_t N>
        auto count(display_handle disp, const config_attributes<N>& attribs)
          const {
            return count(disp, attribs.get());
        }

        auto count(display_handle disp, const config_attribute_value& attribs)
          const {
            return count(disp, config_attributes<2>{attribs});
        }

        auto operator()(
          display_handle disp,
          span<const int_type> attribs,
          span<config_type> dest) const noexcept {
            int_type ret_count{0};
            return base::operator()(disp, attribs, dest, ret_count)
              .transformed([&ret_count, dest](bool valid) {
                  return head(
                    dest, limit_cast<span_size_t>(valid ? ret_count : 0));
              });
        }

        template <std::size_t N>
        auto operator()(
          display_handle disp,
          const config_attributes<N>& attribs,
          span<config_type> dest) const noexcept {
            return (*this)(disp, attribs.get(), dest);
        }

        auto operator()(
          display_handle disp,
          const config_attribute_value& attribs,
          span<config_type> dest) const noexcept {
            return (*this)(disp, config_attributes<2>{attribs}, dest);
        }

        auto operator()(
          display_handle disp,
          const config_attribute_value& attribs) const noexcept {
            return (*this)(disp, config_attributes<2>{attribs});
        }

        template <std::size_t N>
        auto operator()(
          display_handle disp,
          const config_attributes<N>& attribs) const noexcept {
            config_type result;
            return (*this)(disp, attribs.get(), cover_one(&result))
              .replaced_with(result);
        }
    } choose_config{*this};

    adapted_function<
      &egl_api::GetConfigAttrib,
      int_type(display_handle, config_type, config_attribute)>
      get_config_attrib{*this};

    using _create_window_surface_t = adapted_function<
      &egl_api::CreateWindowSurface,
      surface_handle(
        display_handle,
        config_type,
        native_window_type,
        span<const int_type>)>;

    struct : _create_window_surface_t {
        using base = _create_window_surface_t;
        using base::base;
        using base::operator();

        template <std::size_t N>
        constexpr auto operator()(
          display_handle disp,
          config_type conf,
          native_window_type win,
          const surface_attributes<N> attribs) const noexcept {
            return base::operator()(disp, conf, win, attribs.get());
        }
    } create_window_surface{*this};

    using _create_pbuffer_surface_t = adapted_function<
      &egl_api::CreatePbufferSurface,
      surface_handle(display_handle, config_type, span<const int_type>)>;

    struct : _create_pbuffer_surface_t {
        using base = _create_pbuffer_surface_t;
        using base::base;
        using base::operator();

        template <std::size_t N>
        constexpr auto operator()(
          display_handle disp,
          config_type conf,
          const surface_attributes<N> attribs) const noexcept {
            return base::operator()(disp, conf, attribs.get());
        }
    } create_pbuffer_surface{*this};

    using _create_pixmap_surface_t = adapted_function<
      &egl_api::CreatePixmapSurface,
      surface_handle(
        display_handle,
        config_type,
        native_pixmap_type,
        span<const int_type>)>;

    struct : _create_pixmap_surface_t {
        using base = _create_pixmap_surface_t;
        using base::base;
        using base::operator();

        template <std::size_t N>
        constexpr auto operator()(
          display_handle disp,
          config_type conf,
          native_pixmap_type pmp,
          const surface_attributes<N> attribs) const noexcept {
            return base::operator()(disp, conf, pmp, attribs.get());
        }
    } create_pixmap_surface{*this};

    adapted_function<
      &egl_api::DestroySurface,
      bool_type(display_handle, surface_handle),
      collapse_bool_map>
      destroy_surface{*this};

    adapted_function<&egl_api::GetCurrentSurface, surface_handle(read_draw)>
      get_current_surface{*this};

    adapted_function<
      &egl_api::SurfaceAttrib,
      surface_handle(display_handle, surface_handle, surface_attribute, int_type),
      collapse_bool_map>
      surface_attrib{*this};

    adapted_function<
      &egl_api::QuerySurface,
      int_type(display_handle, surface_handle, surface_attribute)>
      query_surface{*this};

    using _create_stream_t = adapted_function<
      &egl_api::CreateStream,
      stream_handle(display_handle, span<const int_type>)>;

    struct : _create_stream_t {
        using base = _create_stream_t;
        using base::base;
        using base::operator();

        template <std::size_t N>
        constexpr auto operator()(
          display_handle disp,
          const stream_attributes<N> attribs) const noexcept {
            return base::operator()(disp, attribs.get());
        }
    } create_stream{*this};

    adapted_function<
      &egl_api::DestroyStream,
      bool_type(display_handle, stream_handle),
      collapse_bool_map>
      destroy_stream{*this};

    adapted_function<
      &egl_api::StreamAttrib,
      surface_handle(display_handle, stream_handle, stream_attribute, int_type),
      collapse_bool_map>
      stream_attrib{*this};

    adapted_function<
      &egl_api::QueryStream,
      int_type(display_handle, stream_handle, stream_attribute)>
      query_stream{*this};

    adapted_function<
      &egl_api::StreamConsumerGLTextureExternal,
      bool_type(display_handle, stream_handle),
      collapse_bool_map>
      stream_consumer_gl_texture_external{*this};

    adapted_function<
      &egl_api::StreamConsumerAcquire,
      bool_type(display_handle, stream_handle),
      collapse_bool_map>
      stream_consumer_acquire{*this};

    adapted_function<
      &egl_api::StreamConsumerRelease,
      bool_type(display_handle, stream_handle),
      collapse_bool_map>
      stream_consumer_release{*this};

    using _get_output_layers_t = adapted_function<
      &egl_api::GetOutputLayers,
      bool_type(
        display_handle,
        span<const attrib_type>,
        span<output_layer_type>,
        int_type&),
      collapse_bool_map>;

    struct : _get_output_layers_t {
        using base = _get_output_layers_t;
        using base::base;

        auto count(display_handle disp) const noexcept {
            int_type ret_count{0};
            return base::operator()(disp, {}, {}, ret_count)
              .transformed([&ret_count](bool valid) {
                  return limit_cast<span_size_t>(valid ? ret_count : 0);
              });
        }

        auto operator()(
          display_handle disp,
          span<const attrib_type> attr,
          span<output_layer_type> dest) const noexcept {
            int_type ret_count{0};
            return base::operator()(disp, attr, dest, ret_count)
              .transformed([dest, &ret_count](bool valid) {
                  return head(
                    dest, limit_cast<span_size_t>(valid ? ret_count : 0));
              });
        }

        template <std::size_t N>
        auto operator()(
          display_handle disp,
          output_layer_attributes<N> attr,
          span<output_layer_type> dest) const noexcept {
            return (*this)(disp, attr.get(), dest);
        }
    } get_output_layers{*this};

    adapted_function<
      &egl_api::OutputLayerAttrib,
      bool_type(display_handle, output_layer_handle, output_layer_attribute),
      collapse_bool_map>
      output_layer_attrib{*this};

    adapted_function<
      &egl_api::QueryOutputLayerAttrib,
      int_type(display_handle, output_layer_handle, output_layer_attribute)>
      query_output_layer_attrib{*this};

    adapted_function<
      &egl_api::QueryOutputLayerString,
      string_view(display_handle, output_layer_handle, output_layer_string_query)>
      query_output_layer_string{*this};

    using _get_output_ports_t = adapted_function<
      &egl_api::GetOutputPorts,
      bool_type(
        display_handle,
        span<const attrib_type>,
        span<output_port_type>,
        int_type&),
      collapse_bool_map>;

    struct : _get_output_ports_t {
        using base = _get_output_ports_t;
        using base::base;

        auto count(display_handle disp) const noexcept {
            int_type ret_count{0};
            return base::operator()(disp, {}, {}, ret_count)
              .transformed([&ret_count](bool valid) {
                  return limit_cast<span_size_t>(valid ? ret_count : 0);
              });
        }

        auto operator()(
          display_handle disp,
          span<const attrib_type> attr,
          span<output_port_type> dest) const noexcept {
            int_type ret_count{0};
            return base::operator()(disp, attr, dest, ret_count)
              .transformed([dest, &ret_count](bool valid) {
                  return head(
                    dest, limit_cast<span_size_t>(valid ? ret_count : 0));
              });
        }

        template <std::size_t N>
        auto operator()(
          display_handle disp,
          output_port_attributes<N> attr,
          span<output_port_type> dest) const noexcept {
            return (*this)(disp, attr.get(), dest);
        }
    } get_output_ports{*this};

    adapted_function<
      &egl_api::OutputPortAttrib,
      bool_type(display_handle, output_port_handle, output_port_attribute),
      collapse_bool_map>
      output_port_attrib{*this};

    adapted_function<
      &egl_api::QueryOutputPortAttrib,
      int_type(display_handle, output_port_handle, output_port_attribute)>
      query_output_port_attrib{*this};

    adapted_function<
      &egl_api::QueryOutputPortString,
      string_view(display_handle, output_port_handle, output_port_string_query)>
      query_output_port_string{*this};

    using _create_image_t = adapted_function<
      &egl_api::CreateImage,
      image_handle(
        display_handle,
        context_handle,
        image_target,
        client_buffer_type,
        span<const int_type>)>;

    struct : _create_image_t {
        using base = _create_image_t;
        using base::base;
        using base::operator();

        template <std::size_t N>
        constexpr auto operator()(
          display_handle disp,
          context_handle ctxt,
          image_target tgt,
          client_buffer_type buf,
          const image_attributes<N> attribs) const noexcept {
            return base::operator()(disp, ctxt, tgt, buf, attribs.get());
        }
    } create_image{*this};

    adapted_function<
      &egl_api::DestroyImage,
      bool_type(display_handle, image_handle),
      collapse_bool_map>
      destroy_image{*this};

    adapted_function<&egl_api::BindAPI, bool_type(client_api), collapse_bool_map>
      bind_api{*this};

    adapted_function<&egl_api::QueryAPI, client_api()> query_api{*this};

    using _create_context_t = adapted_function<
      &egl_api::CreateContext,
      context_handle(
        display_handle,
        config_type,
        context_handle,
        span<const int_type>)>;

    struct : _create_context_t {
        using base = _create_context_t;
        using base::base;
        using base::operator();

        template <std::size_t N>
        constexpr auto operator()(
          display_handle disp,
          config_type conf,
          const context_attributes<N> attribs) const noexcept {
            return base::operator()(
              disp, conf, context_handle{}, attribs.get());
        }

        template <std::size_t N>
        constexpr auto operator()(
          display_handle disp,
          config_type conf,
          context_handle sctx,
          const context_attributes<N> attribs) const noexcept {
            return base::operator()(disp, conf, sctx, attribs.get());
        }
    } create_context{*this};

    adapted_function<
      &egl_api::DestroyContext,
      bool_type(display_handle, context_handle),
      collapse_bool_map>
      destroy_context{*this};

    using _make_current_t = adapted_function<
      &egl_api::MakeCurrent,
      bool_type(display_handle, surface_handle, surface_handle, context_handle),
      collapse_bool_map>;

    struct : _make_current_t {
        using base = _make_current_t;
        using base::base;
        using base::operator();

        constexpr auto operator()(
          display_handle disp,
          surface_handle surf,
          context_handle ctxt) const noexcept {
            return base::operator()(disp, surf, surf, ctxt);
        }

        constexpr auto none(display_handle disp) const noexcept {
            return base::operator()(
              disp, surface_handle{}, surface_handle{}, context_handle{});
        }
    } make_current{*this};

    adapted_function<&egl_api::GetCurrentContext, context_handle()>
      get_current_context{*this};

    adapted_function<&egl_api::WaitClient, bool_type(), collapse_bool_map>
      wait_client{*this};

    using _wait_native_t =
      adapted_function<&egl_api::WaitNative, bool_type(engine), collapse_bool_map>;

    struct : _wait_native_t {
        using base = _wait_native_t;
        using base::base;
        using base::operator();

        constexpr auto operator()() const noexcept {
#ifdef EGL_CORE_NATIVE_ENGINE
            return base::operator()(engine{EGL_CORE_NATIVE_ENGINE});
#else
            return base::fail();
#endif
        }
    } wait_native{*this};

    using _create_sync_t = adapted_function<
      &egl_api::CreateSync,
      sync_handle(display_handle, sync_type, span<const int_type>)>;

    struct : _create_sync_t {
        using base = _create_sync_t;
        using base::base;
        using base::operator();

        template <std::size_t N>
        constexpr auto operator()(
          display_handle disp,
          sync_type typ,
          const sync_attributes<N> attribs) const noexcept {
            return base::operator()(disp, typ, attribs.get());
        }
    } create_sync{*this};

    using _client_wait_sync_t = adapted_function<
      &egl_api::ClientWaitSync,
      bool_type(display_handle, sync_handle, int_type, time_type),
      collapse_bool_map>;

    struct : _client_wait_sync_t {
        using base = _client_wait_sync_t;
        using base::base;

        template <typename R, typename P>
        constexpr auto operator()(
          display_handle disp,
          sync_handle sync,
          std::chrono::duration<R, P> timeout) const noexcept {
            return base::operator()(
              disp, sync, 0, std::chrono::nanoseconds(timeout).count());
        }

        template <typename R, typename P>
        constexpr auto forever(display_handle disp, sync_handle sync)
          const noexcept {
#ifdef EGL_FOREVER
            return base::operator()(disp, sync, 0, EGL_FOREVER);
#else
            return base::fail();
#endif
        }
    } client_wait_sync{*this};

    adapted_function<
      &egl_api::WaitSync,
      bool_type(display_handle, sync_handle),
      collapse_bool_map>
      wait_sync{*this};

    adapted_function<
      &egl_api::DestroySync,
      bool_type(display_handle, sync_handle),
      collapse_bool_map>
      destroy_sync{*this};

    adapted_function<
      &egl_api::QueryString,
      string_view(display_handle, string_query)>
      query_string{*this};

    // query_strings
    auto query_strings(display_handle disp, string_query query, char separator)
      const noexcept {
        return query_string(disp, query)
          .transformed([separator](auto src, bool) {
              return split_into_string_list(src, separator);
          });
    }

    // get_client_apis
    auto get_client_apis(display_handle disp) const noexcept {
#ifdef EGL_CLIENT_APIS
        return query_string(disp, string_query(EGL_CLIENT_APIS))
#else
        return query_string
          .fail()
#endif
          .transformed(
            [](auto src, bool) { return split_into_string_list(src, ' '); });
    }

    auto get_client_api_bits(display_handle disp) const noexcept {
        enum_bitfield<client_api_bit> result{};

        if(ok apis{get_client_apis(disp)}) {
            for(auto api : apis) {
#ifdef EGL_OPENGL_BIT
                if(are_equal(api, string_view("OpenGL"))) {
                    result.add(client_api_bit(EGL_OPENGL_BIT));
                }
#endif
#ifdef EGL_OPENGL_ES_BIT
                if(are_equal(api, string_view("OpenGL_ES"))) {
                    result.add(client_api_bit(EGL_OPENGL_ES_BIT));
                }
#endif
#ifdef EGL_OPENVG_BIT
                if(are_equal(api, string_view("OpenVG"))) {
                    result.add(client_api_bit(EGL_OPENVG_BIT));
                }
#endif
            }
        }

        return result;
    }

    // get_extensions
    auto get_extensions() const noexcept {
#if defined(EGL_EXTENSIONS) && defined(EGL_NO_DISPLAY)
        return query_string(
                 display_handle(EGL_NO_DISPLAY), string_query(EGL_EXTENSIONS))
#else
        return query_string
          .fail()
#endif
          .transformed(
            [](auto src, bool) { return split_into_string_list(src, ' '); });
    }

    // get_extensions
    auto get_extensions(display_handle disp) const noexcept {
#ifdef EGL_EXTENSIONS
        return query_string(disp, string_query(EGL_EXTENSIONS))
#else
        return query_string
          .fail()
#endif
          .transformed(
            [](auto src, bool) { return split_into_string_list(src, ' '); });
    }

    // has_extension
    auto has_extension(string_view which) const noexcept {
        if(ok extensions{get_extensions()}) {
            for(auto ext_name : extensions) {
                if(ends_with(ext_name, which)) {
                    return true;
                }
            }
        }
        return false;
    }

    auto has_extension(device_handle dev, string_view which) const noexcept {
        if(ok extensions{get_device_extensions(dev)}) {
            for(auto ext_name : extensions) {
                if(ends_with(ext_name, which)) {
                    return true;
                }
            }
        }
        return false;
    }

    auto has_extension(display_handle disp, string_view which) const noexcept {
        if(ok extensions{get_extensions(disp)}) {
            for(auto ext_name : extensions) {
                if(ends_with(ext_name, which)) {
                    return true;
                }
            }
        }
        return false;
    }

    adapted_function<
      &egl_api::SwapInterval,
      bool_type(display_handle, int_type),
      collapse_bool_map>
      swap_interval{*this};

    adapted_function<
      &egl_api::SwapBuffers,
      bool_type(display_handle, surface_handle),
      collapse_bool_map>
      swap_buffers{*this};

    adapted_function<
      &egl_api::SwapBuffersWithDamage,
      bool_type(display_handle, surface_handle, span<const int_type>),
      collapse_bool_map>
      swap_buffers_with_damage{*this};

    adapted_function<&egl_api::ReleaseThread, bool_type(), collapse_bool_map>
      release_thread{*this};

    basic_egl_operations(api_traits& traits);
};
//------------------------------------------------------------------------------
#undef EGLPAFP
//------------------------------------------------------------------------------
} // namespace eagine::eglplus

#endif // EAGINE_EGLPLUS_EGL_API_API_HPP
