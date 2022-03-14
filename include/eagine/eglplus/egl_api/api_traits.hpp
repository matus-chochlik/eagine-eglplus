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

namespace eagine::eglplus {
//------------------------------------------------------------------------------
/// @brief Policy customizing the generic C-API wrappers for the EGL API
/// @ingroup egl_api_wrap
class egl_api_traits : public c_api::default_traits {
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
    auto link_function(
      Api& api,
      const Tag,
      const string_view name,
      const type_identity<Signature>) -> std::add_pointer_t<Signature>;

private:
    std::string _full_name;
};
//------------------------------------------------------------------------------
} // namespace eagine::eglplus

#endif // EAGINE_EGLPLUS_EGL_API_API_TRAITS_HPP
