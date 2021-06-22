/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#ifndef EAGINE_EGLPLUS_CONFIG_BASIC_HPP
#define EAGINE_EGLPLUS_CONFIG_BASIC_HPP

// TODO

#ifndef EGLPLUS_LINK_LIBRARY
#define EGLPLUS_LINK_LIBRARY 0
#endif

#if EGLPLUS_LINK_LIBRARY
#define EGLPLUS_LIB_FUNC
#else
#define EGLPLUS_LIB_FUNC inline
#endif

#endif // EAGINE_EGLPLUS_CONFIG_BASIC_HPP
