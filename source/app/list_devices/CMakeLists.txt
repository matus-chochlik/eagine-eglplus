# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt
add_executable(eagine-list-egl-devices main.cpp)

eagine_add_exe_analysis(eagine-list-egl-devices)
eagine_target_modules(
	eagine-list-egl-devices
	std
	eagine.core
	eagine.eglplus)

eagine_embed_target_resources(
	TARGET eagine-list-egl-devices
	RESOURCES
		BoostLcnse "../../../LICENSE_1_0.txt"
		Manual     "resource/eagine-list-egl-devices.man"
		BashCmpltn "resource/eagine-list-egl-devices.bco"
	PACKED
	ENABLE_SEARCH)

install(
	TARGETS eagine-list-egl-devices
	DESTINATION bin)

