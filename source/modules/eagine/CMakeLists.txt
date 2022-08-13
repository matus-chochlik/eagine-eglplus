# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
eagine_add_module(
	eagine.eglplus PARTITION config
	IMPORTS eagine.core.types
)

eagine_add_module(
	eagine.eglplus PARTITION enum_types
	IMPORTS
		config
		eagine.core.types
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus PARTITION attributes
	IMPORTS
		config enum_types
		eagine.core.types
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus PARTITION objects
	IMPORTS
		config
		eagine.core.types
		eagine.core.identifier
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus PARTITION result
	IMPORTS
		config
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus PARTITION api_traits
	IMPORTS
		config result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus PARTITION c_api
	IMPORTS
		config result
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus
	PP_NAME EGLPLUS
	INTERFACES eglplus
	PARTITIONS
		config
		enum_types
		attributes
		objects
		result
		api_traits
		c_api
	SOURCES
)
target_link_libraries(
	eagine.eglplus
	PUBLIC
	EGL
)
