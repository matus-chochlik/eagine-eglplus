# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt
#
add_custom_target(eagine-eglplus-examples ALL)
set_target_properties(
	eagine-eglplus-examples
	PROPERTIES FOLDER "Example/EGLplus"
)

function(eagine_install_example TARGET_NAME)
	install(
		TARGETS ${TARGET_NAME}
		COMPONENT eglplus-examples
		DESTINATION share/eagine/example/eglplus)
endfunction()

function(eagine_example_common EXAMPLE_NAME)
	add_executable(
		eglplus-${EXAMPLE_NAME}
		EXCLUDE_FROM_ALL
		"${EXAMPLE_NAME}.cpp"
		${ARGN}
	)
	eagine_add_exe_analysis(eglplus-${EXAMPLE_NAME})
	eagine_target_modules(
		eglplus-${EXAMPLE_NAME}
		std
		eagine.core
		eagine.eglplus
	)
	add_dependencies(eagine-eglplus-examples eglplus-${EXAMPLE_NAME})

	set_target_properties(
		eglplus-${EXAMPLE_NAME}
		PROPERTIES FOLDER "Example/EGLplus"
	)
	eagine_install_example(eglplus-${EXAMPLE_NAME})
endfunction()

eagine_example_common(001_basic_info)
eagine_example_common(002_list_apis)
eagine_example_common(003_list_extensions)
eagine_example_common(005_list_configs)
eagine_example_common(006_multisample_configs)
eagine_example_common(007_depth_stencil_configs)
eagine_example_common(008_list_extensions)

eagine_add_license(eglplus-examples)
eagine_add_debian_changelog(eglplus-examples)

eagine_add_package_property(
	eglplus-examples
	GENERATOR DEBIAN
	VARIABLE PACKAGE_DEPENDS
	VALUE "\${CXX_RUNTIME_PKGS},\${EAGINE_CORE_RUNTIME_PKGS}")

eagine_add_package_property(
	eglplus-examples
	GENERATOR DEBIAN
	VARIABLE DESCRIPTION
	VALUE "EAGine EGLplus examples.")

