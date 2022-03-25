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
#include <eagine/c_api_wrap.hpp>
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
    using attrib_type = typename egl_types::attrib_type;
    using device_type = typename egl_types::device_type;
    using native_display_type = typename egl_types::native_display_type;
    using native_window_type = typename egl_types::native_window_type;
    using native_pixmap_type = typename egl_types::native_pixmap_type;
    using client_buffer_type = typename egl_types::client_buffer_type;
    using config_type = typename egl_types::config_type;

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

    // functions
    template <typename W, W egl_api::*F, typename Signature = typename W::signature>
    class func;

    template <typename W, W egl_api::*F, typename RVC, typename... Params>
    class func<W, F, RVC(Params...)>
      : public wrapped_c_api_function<egl_api, api_traits, nothing_t, W, F> {
        using base =
          wrapped_c_api_function<egl_api, api_traits, nothing_t, W, F>;

    private:
        template <typename Res>
        constexpr auto _check(Res&& res) const noexcept {
            res.error_code(this->api().GetError());
            return std::forward<Res>(res);
        }

    protected:
        template <typename... Args>
        constexpr auto _chkcall(Args&&... args) const noexcept {
            return this->_check(this->_call(std::forward<Args>(args)...));
        }

        using base::_conv;

        template <typename... Args>
        constexpr auto _cnvchkcall(Args&&... args) const noexcept {
            return this->_chkcall(_conv(std::forward<Args>(args))...)
              .cast_to(type_identity<RVC>{});
        }

    public:
        using base::base;

        constexpr auto operator()(Params... params) const noexcept {
            return this->_chkcall(_conv(params)...)
              .cast_to(type_identity<RVC>{});
        }

        auto bind(Params... params) const noexcept {
            return [this, params...] {
                return (*this)(params...);
            };
        }
    };

    // numeric query function
    template <
      typename PreTypeList,
      typename QueryClassList,
      typename PostTypeList,
      typename QueryResult,
      typename W,
      W egl_api::*F>
    struct query_func;

    template <
      typename... PreParams,
      typename... QueryClasses,
      typename... PostParams,
      typename QueryResult,
      typename W,
      W egl_api::*F>
    struct query_func<
      mp_list<PreParams...>,
      mp_list<QueryClasses...>,
      mp_list<PostParams...>,
      QueryResult,
      W,
      F> : func<W, F> {
        using func<W, F>::func;

        template <typename Query>
        constexpr auto operator()(
          PreParams... pre_params,
          Query query,
          PostParams... post_params) const noexcept
          requires((true || ... || is_enum_class_value_v<QueryClasses, Query>)&&(
            !std::is_array_v<typename Query::tag_type>)) {
            using RV = typename Query::tag_type;
            QueryResult result{};
            return this
              ->_cnvchkcall(
                pre_params..., int_type(query), post_params..., &result)
              .replaced_with(result)
              .cast_to(type_identity<RV>{});
        }

        template <
          typename Query,
          typename = std::enable_if_t<
            (true || ... || is_enum_class_value_v<QueryClasses, Query>)>>
        auto operator()(
          PreParams... pre_params,
          Query query,
          PostParams... post_params,
          span<QueryResult> dest) const noexcept {
            EAGINE_ASSERT(dest.size());
            return this->_cnvchkcall(
              pre_params..., int_type(query), post_params..., dest.data());
        }
    };

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

    // get_config_attrib
    query_func<
      mp_list<display_handle, config_type>,
      mp_list<config_attribute>,
      mp_list<>,
      int_type,
      EGLPAFP(GetConfigAttrib)>
      get_config_attrib;

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

    // query_surface
    query_func<
      mp_list<display_handle, surface_handle>,
      mp_list<surface_attribute>,
      mp_list<>,
      int_type,
      EGLPAFP(QuerySurface)>
      query_surface;

    // create_stream
    struct : func<EGLPAFP(CreateStream)> {
        using func<EGLPAFP(CreateStream)>::func;

        constexpr auto operator()(display_handle disp) const noexcept {
            return this->_cnvchkcall(disp, nullptr)
              .cast_to(type_identity<stream_handle>{});
        }

        constexpr auto operator()(
          display_handle disp,
          span<const int_type> attribs) const noexcept {
            return this->_cnvchkcall(disp, attribs.data())
              .cast_to(type_identity<stream_handle>{});
        }

        template <std::size_t N>
        constexpr auto operator()(
          display_handle disp,
          const stream_attributes<N> attribs) const noexcept {
            return (*this)(disp, attribs.get());
        }
    } create_stream;

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

    // query_stream
    query_func<
      mp_list<display_handle, stream_handle>,
      mp_list<stream_attribute>,
      mp_list<>,
      int_type,
      EGLPAFP(QueryStream)>
      query_stream;

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

    // get_output_layers
    struct : func<EGLPAFP(GetOutputLayers)> {
        using func<EGLPAFP(GetOutputLayers)>::func;

        auto count(display_handle disp) const noexcept {
            int_type ret_count{0};
            return this->_cnvchkcall(disp, nullptr, nullptr, 0, &ret_count)
              .transformed([&ret_count](auto ok, bool valid) {
                  return limit_cast<span_size_t>(
                    valid && egl_types::bool_true(ok) ? ret_count : 0);
              });
        }

        auto operator()(
          display_handle disp,
          span<attrib_type> attr,
          span<device_type> dest) const noexcept {
            int_type ret_count{0};
            return this
              ->_cnvchkcall(
                disp,
                attr.data(),
                dest.data(),
                limit_cast<int_type>(dest.size()),
                &ret_count)
              .transformed([dest, &ret_count](auto ok, bool valid) {
                  return head(
                    dest,
                    limit_cast<span_size_t>(
                      valid && egl_types::bool_true(ok) ? ret_count : 0));
              });
        }

        template <std::size_t N>
        auto operator()(
          display_handle disp,
          output_layer_attributes<N> attr,
          span<device_type> dest) const noexcept {
            return (*this)(disp, attr.get(), dest);
        }
    } get_output_layers;

    // output_layer_attrib
    struct : func<EGLPAFP(OutputLayerAttrib)> {
        using func<EGLPAFP(OutputLayerAttrib)>::func;
        auto operator()(
          display_handle disp,
          output_layer_handle outl,
          output_layer_attribute_value attr) const noexcept {
            return this->_cnvchkcall(disp, outl, attr._key, attr._value);
        }
    } output_layer_attrib;

    // query_output_layer_attrib
    struct : func<EGLPAFP(QueryOutputLayerAttrib)> {
        using func<EGLPAFP(QueryOutputLayerAttrib)>::func;
        auto operator()(
          display_handle disp,
          output_layer_handle outl,
          output_layer_attribute attr) const noexcept {
            using RV = attrib_type;
            attrib_type result{0};
            return this->_cnvchkcall(disp, outl, attr, &result)
              .replaced_with(result)
              .cast_to(type_identity<RV>{});
        }
    } query_output_layer_attrib;

    adapted_function<
      &egl_api::QueryOutputLayerString,
      string_view(display_handle, output_layer_handle, output_layer_string_query)>
      query_output_layer_string{*this};

    // get_output_ports
    struct : func<EGLPAFP(GetOutputPorts)> {
        using func<EGLPAFP(GetOutputPorts)>::func;

        auto count(display_handle disp) const noexcept {
            int_type ret_count{0};
            return this->_cnvchkcall(disp, nullptr, nullptr, 0, &ret_count)
              .transformed([&ret_count](auto ok, bool valid) {
                  return limit_cast<span_size_t>(
                    valid && egl_types::bool_true(ok) ? ret_count : 0);
              });
        }

        auto operator()(
          display_handle disp,
          span<attrib_type> attr,
          span<device_type> dest) const noexcept {
            int_type ret_count{0};
            return this
              ->_cnvchkcall(
                disp,
                attr.data(),
                dest.data(),
                limit_cast<int_type>(dest.size()),
                &ret_count)
              .transformed([dest, &ret_count](auto ok, bool valid) {
                  return head(
                    dest,
                    limit_cast<span_size_t>(
                      valid && egl_types::bool_true(ok) ? ret_count : 0));
              });
        }

        template <std::size_t N>
        auto operator()(
          display_handle disp,
          output_port_attributes<N> attr,
          span<device_type> dest) const noexcept {
            return (*this)(disp, attr.get(), dest);
        }
    } get_output_ports;

    // output_port_attrib
    struct : func<EGLPAFP(OutputPortAttrib)> {
        using func<EGLPAFP(OutputPortAttrib)>::func;
        auto operator()(
          display_handle disp,
          output_port_handle outp,
          output_port_attribute_value attr) const noexcept {
            return this->_cnvchkcall(disp, outp, attr._key, attr._value);
        }
    } output_port_attrib;

    // query_output_port_attrib
    struct : func<EGLPAFP(QueryOutputPortAttrib)> {
        using func<EGLPAFP(QueryOutputPortAttrib)>::func;
        auto operator()(
          display_handle disp,
          output_port_handle outp,
          output_port_attribute attr) const noexcept {
            using RV = attrib_type;
            attrib_type result{0};
            return this->_cnvchkcall(disp, outp, attr, &result)
              .replaced_with(result)
              .cast_to(type_identity<RV>{});
        }
    } query_output_port_attrib;

    // query_output_port_string
    struct : func<EGLPAFP(QueryOutputPortString)> {
        using func<EGLPAFP(QueryOutputPortString)>::func;
        auto operator()(
          display_handle disp,
          output_port_handle outl,
          output_port_string_query qury) const noexcept {
            return this->_cnvchkcall(disp, outl, qury)
              .cast_to(type_identity<string_view>{});
        }
    } query_output_port_string;

    // create_image
    struct : func<EGLPAFP(CreateImage)> {
        using func<EGLPAFP(CreateImage)>::func;

        constexpr auto operator()(
          display_handle disp,
          context_handle ctxt,
          image_target tgt,
          client_buffer_type buf,
          span<const attrib_type> attribs) const noexcept {
            return this->_cnvchkcall(disp, ctxt, tgt, buf, attribs.data())
              .cast_to(type_identity<image_handle>{});
        }

        template <std::size_t N>
        constexpr auto operator()(
          display_handle disp,
          context_handle ctxt,
          image_target tgt,
          client_buffer_type buf,
          const image_attributes<N> attribs) const noexcept {
            return (*this)(disp, ctxt, tgt, buf, attribs.get());
        }
    } create_image;

    adapted_function<
      &egl_api::DestroyImage,
      bool_type(display_handle, image_handle),
      collapse_bool_map>
      destroy_image{*this};

    adapted_function<&egl_api::BindAPI, bool_type(client_api), collapse_bool_map>
      bind_api{*this};

    adapted_function<&egl_api::QueryAPI, client_api()> query_api{*this};

    // create_context
    struct : func<EGLPAFP(CreateContext)> {
        using func<EGLPAFP(CreateContext)>::func;

        constexpr auto operator()(
          display_handle disp,
          config_type conf,
          context_handle share_ctxt,
          span<const int_type> attribs) const noexcept {
            return this->_cnvchkcall(disp, conf, share_ctxt, attribs.data())
              .cast_to(type_identity<context_handle>{});
        }

        template <std::size_t N>
        constexpr auto operator()(
          display_handle disp,
          config_type conf,
          const context_attributes<N> attribs) const noexcept {
            return (*this)(disp, conf, context_handle{}, attribs.get());
        }

        template <std::size_t N>
        constexpr auto operator()(
          display_handle disp,
          config_type conf,
          context_handle share_ctxt,
          const context_attributes<N> attribs) const noexcept {
            return (*this)(disp, conf, share_ctxt, attribs.get());
        }
    } create_context;

    adapted_function<
      &egl_api::DestroyContext,
      bool_type(display_handle, context_handle),
      collapse_bool_map>
      destroy_context{*this};

    // make_current
    struct : func<EGLPAFP(MakeCurrent)> {
        using func<EGLPAFP(MakeCurrent)>::func;

        constexpr auto operator()(
          display_handle disp,
          surface_handle draw,
          surface_handle read,
          context_handle ctxt) const noexcept {
            return this->_cnvchkcall(disp, draw, read, ctxt);
        }

        constexpr auto operator()(
          display_handle disp,
          surface_handle surf,
          context_handle ctxt) const noexcept {
            return this->_cnvchkcall(disp, surf, surf, ctxt);
        }

        constexpr auto none(display_handle disp) const noexcept {
            return (*this)(disp, surface_handle{}, context_handle{});
        }
    } make_current;

    adapted_function<&egl_api::GetCurrentContext, context_handle()>
      get_current_context{*this};

    adapted_function<&egl_api::WaitClient, bool_type(), collapse_bool_map>
      wait_client{*this};

    // wait_native
    struct : func<EGLPAFP(WaitNative)> {
        using func<EGLPAFP(WaitNative)>::func;

        constexpr auto operator()() const noexcept {
#ifdef EGL_CORE_NATIVE_ENGINE
            return this->_chkcall(EGL_CORE_NATIVE_ENGINE);
#else
            return this->_fake();
#endif
        }
    } wait_native;

    // create_sync
    struct : func<EGLPAFP(CreateSync)> {
        using func<EGLPAFP(CreateSync)>::func;

        constexpr auto operator()(
          display_handle disp,
          sync_type type,
          span<const attrib_type> attribs) const noexcept {
            return this->_cnvchkcall(disp, type, attribs.data())
              .cast_to(type_identity<sync_handle>{});
        }

        template <std::size_t N>
        constexpr auto operator()(
          display_handle disp,
          sync_type type,
          const sync_attributes<N> attribs) const noexcept {
            return (*this)(disp, type, attribs.get());
        }
    } create_sync;

    // client_wait_sync
    struct : func<EGLPAFP(ClientWaitSync)> {
        using func<EGLPAFP(ClientWaitSync)>::func;

        template <typename R, typename P>
        constexpr auto operator()(
          display_handle disp,
          sync_handle sync,
          std::chrono::duration<R, P> timeout) const noexcept {
            return this->_cnvchkcall(
              disp, sync, 0, std::chrono::nanoseconds(timeout).count());
        }

        template <typename R, typename P>
        constexpr auto forever(display_handle disp, sync_handle sync)
          const noexcept {
#ifdef EGL_FOREVER
            return this->_cnvchkcall(disp, sync, 0, EGL_FOREVER);
#else
            return this->_fake({});
#endif
        }
    } client_wait_sync;

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

    // query_string
    struct : func<EGLPAFP(QueryString)> {
        using func<EGLPAFP(QueryString)>::func;

        constexpr auto operator()(display_handle disp, string_query query)
          const noexcept {
            return this->_cnvchkcall(disp, query)
              .cast_to(type_identity<string_view>{});
        }

        constexpr auto operator()() const noexcept {
            return this->fake_empty_c_str().cast_to(
              type_identity<string_view>{});
        }
    } query_string;

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
        return query_string()
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
        return query_string()
#endif
          .transformed(
            [](auto src, bool) { return split_into_string_list(src, ' '); });
    }

    // get_extensions
    auto get_extensions(display_handle disp) const noexcept {
#ifdef EGL_EXTENSIONS
        return query_string(disp, string_query(EGL_EXTENSIONS))
#else
        return query_string()
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

    // release_thread
    func<EGLPAFP(ReleaseThread)> release_thread;

    basic_egl_operations(api_traits& traits);
};
//------------------------------------------------------------------------------
#undef EGLPAFP
//------------------------------------------------------------------------------
} // namespace eagine::eglplus

#endif // EAGINE_EGLPLUS_EGL_API_API_HPP
