cmake_minimum_required(VERSION 2.8)
if (POLICY CMP0042)
	cmake_policy(SET CMP0042 NEW)
endif()

project(serut)
set(VERSION 1.1.0)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
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

if (NOT MSVC)
	set(SERUT_COMPILE_STATIC_ONLY OFF CACHE BOOL "Flag indicating if only a static library should be built, or both a dynamic and static one")
else (NOT MSVC)
	set(SERUT_COMPILE_STATIC ON CACHE BOOL "Flag indicating if a static library should be built, or a dynamic one")
endif (NOT MSVC)

if (NOT MSVC OR SERUT_COMPILE_STATIC)
	set(SERUT_IMPORT "")
	set(SERUT_EXPORT "")
else (NOT MSVC OR SERUT_COMPILE_STATIC)
	set(SERUT_IMPORT "__declspec(dllimport)")
	set(SERUT_EXPORT "__declspec(dllexport)")
endif (NOT MSVC OR SERUT_COMPILE_STATIC)

configure_file("${PROJECT_SOURCE_DIR}/src/serutconfig.h.in" "${PROJECT_BINARY_DIR}/src/serutconfig.h")
list(APPEND SERUT_INTERNAL_INCLUDES "${PROJECT_SOURCE_DIR}/src/")
list(APPEND SERUT_INTERNAL_INCLUDES "${PROJECT_BINARY_DIR}/src/")

add_subdirectory(src)

if (NOT MSVC)
	set(SERUT_LIBS "-L${LIBRARY_INSTALL_DIR}" "-lserut")
else (NOT MSVC)
	set(SERUT_LIBS optimized "${LIBRARY_INSTALL_DIR}/serut.lib" 
		       debug "${LIBRARY_INSTALL_DIR}/serut_d.lib")
endif (NOT MSVC)

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

