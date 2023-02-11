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
	eagine.eglplus PARTITION extensions
	IMPORTS
		config objects
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus PARTITION constants
	IMPORTS
		config enum_types c_api
		eagine.core.types
		eagine.core.memory
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus PARTITION from_string
	IMPORTS
		enum_types constants
		eagine.core.types
		eagine.core.memory
		eagine.core.string
)

eagine_add_module(
	eagine.eglplus PARTITION api
	IMPORTS
		config enum_types
		api_traits
		attributes constants
		extensions c_api
		eagine.core.types
		eagine.core.memory
		eagine.core.string
		eagine.core.c_api
)

eagine_add_module(
	eagine.eglplus
	PP_NAME EGLPLUS
	INTERFACES eglplus
	PARTITIONS
		config
		enum_types
		extensions
		attributes
		objects
		result
		api_traits
		c_api
		constants
		from_string
		api
	SOURCES
		constants
)
target_link_libraries(
	eagine.eglplus
	PUBLIC
	EGL
)
