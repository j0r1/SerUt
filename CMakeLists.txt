cmake_minimum_required(VERSION 2.8)

project(serut)
set(VERSION 1.0.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

include(CheckCXXSourceCompiles)
include(${PROJECT_SOURCE_DIR}/cmake/Macros.cmake)

set(SERUT_EXTERNAL_INCLUDES "")
set(SERUT_INTERNAL_INCLUDES "")
set(SERUT_LINK_LIBS "")

add_additional_stuff(SERUT_EXTERNAL_INCLUDES SERUT_LINK_LIBS)
get_install_directory(LIBRARY_INSTALL_DIR)

find_package(ErrUt REQUIRED)
list(APPEND SERUT_EXTERNAL_INCLUDES "${ERRUT_INCLUDE_DIRS}")
list(APPEND SERUT_LINK_LIBS "${ERRUT_LIBRARIES}")

find_package(ENUt)
if (ENUT_FOUND)
	add_definitions(-DSERUT_SUPPORT_ENUT)
	list(APPEND SERUT_LINK_LIBS "${ENUT_LIBRARIES}")
	list(APPEND SERUT_INTERNAL_INCLUDES "${ENUT_INCLUDE_DIRS}")
endif(ENUT_FOUND)

if (NOT UNIX)
	set(SERUT_COMPILE_STATIC ON CACHE BOOL "Flag indicating if a static library should be built, or a dynamic one")
endif (NOT UNIX)
if (UNIX OR SERUT_COMPILE_STATIC)
	set(SERUT_IMPORT "")
	set(SERUT_EXPORT "")
else (UNIX OR SERUT_COMPILE_STATIC)
	set(SERUT_IMPORT "__declspec(dllimport)")
	set(SERUT_EXPORT "__declspec(dllexport)")
endif (UNIX OR SERUT_COMPILE_STATIC)

configure_file("${PROJECT_SOURCE_DIR}/src/serutconfig.h.in" "${PROJECT_BINARY_DIR}/src/serutconfig.h")
list(APPEND SERUT_INTERNAL_INCLUDES "${PROJECT_SOURCE_DIR}/src/")
list(APPEND SERUT_INTERNAL_INCLUDES "${PROJECT_BINARY_DIR}/src/")

add_subdirectory(src)

if (UNIX)
	get_target_property(SERUT_LOCAL_LIBRARY_NAME serut-shared LOCATION)
	get_filename_component(SERUT_LIBNAME "${SERUT_LOCAL_LIBRARY_NAME}" NAME)
	set(SERUT_LIBS "${LIBRARY_INSTALL_DIR}/${SERUT_LIBNAME}")
else (UNIX)
	if (SERUT_COMPILE_STATIC)
		get_target_property(SERUT_LOCAL_LIBRARY_NAME serut-static RELEASE_LOCATION)
		get_filename_component(SERUT_LIBNAME_RELEASE "${SERUT_LOCAL_LIBRARY_NAME}" NAME_WE)
		get_target_property(SERUT_LOCAL_LIBRARY_NAME serut-static DEBUG_LOCATION)
		get_filename_component(SERUT_LIBNAME_DEBUG "${SERUT_LOCAL_LIBRARY_NAME}" NAME_WE)
	else (SERUT_COMPILE_STATIC)
		get_target_property(SERUT_LOCAL_LIBRARY_NAME serut-shared RELEASE_LOCATION)
		get_filename_component(SERUT_LIBNAME_RELEASE "${SERUT_LOCAL_LIBRARY_NAME}" NAME_WE)
		get_target_property(SERUT_LOCAL_LIBRARY_NAME serut-shared DEBUG_LOCATION)
		get_filename_component(SERUT_LIBNAME_DEBUG "${SERUT_LOCAL_LIBRARY_NAME}" NAME_WE)
	endif (SERUT_COMPILE_STATIC)
	set(SERUT_LIBS optimized "${LIBRARY_INSTALL_DIR}/${SERUT_LIBNAME_RELEASE}.lib" 
		         debug "${LIBRARY_INSTALL_DIR}/${SERUT_LIBNAME_DEBUG}.lib")
endif (UNIX)

set(SERUT_INCDIRS "${SERUT_EXTERNAL_INCLUDES};${CMAKE_INSTALL_PREFIX}/include")
set(SERUT_LIBS "${SERUT_LIBS};${SERUT_LINK_LIBS}")
remove_empty(SERUT_INCDIRS)
list(REMOVE_DUPLICATES SERUT_INCDIRS)
remove_empty(SERUT_LIBS)

foreach(ARG ${SERUT_LIBS})
	set(SERUT_LIBS_CMAKECONFIG "${SERUT_LIBS_CMAKECONFIG} \"${ARG}\"")
endforeach()
foreach(ARG ${SERUT_INCDIRS})
	set(SERUT_INCDIRS_CMAKECONFIG "${SERUT_INCDIRS_CMAKECONFIG} \"${ARG}\"")
endforeach()

configure_file("${PROJECT_SOURCE_DIR}/cmake/SerUtConfig.cmake.in" "${PROJECT_BINARY_DIR}/cmake/SerUtConfig.cmake")
install(FILES "${PROJECT_BINARY_DIR}/cmake/SerUtConfig.cmake" 
	DESTINATION ${LIBRARY_INSTALL_DIR}/cmake/SerUt)

