/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_EGLPLUS_EGL_API_API_TRAITS_HPP
#define EAGINE_EGLPLUS_EGL_API_API_TRAITS_HPP

#include "result.hpp"

namespace eagine::eglp {
//------------------------------------------------------------------------------
/// @brief Policy customizing the generic C-API wrappers for the EGL API
/// @ingroup egl_api_wrap
/// @see default_c_api_traits
class egl_api_traits : public default_c_api_traits {
public:
    /// @brief Alias for result type of currently unavailable functions.
    template <typename R>
    using no_result = egl_no_result<R>;

    /// @brief Alias for result type of functions.
    template <typename R>
    using result = egl_result<R>;

    /// @brief Alias for result type of optionally available functions.
    template <typename R>
    using opt_result = egl_opt_result<R>;

    /// @brief Links an EGL function with the specified name and Signature.
    template <typename Api, typename Tag, typename Signature>
    auto link_function(Api& api, Tag, string_view name, type_identity<Signature>)
      -> std::add_pointer_t<Signature>;

private:
    std::string _full_name;
};
//------------------------------------------------------------------------------
} // namespace eagine::eglp

#endif // EAGINE_EGLPLUS_EGL_API_API_TRAITS_HPP
