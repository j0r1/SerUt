add_definitions(-DSERUT_COMPILING)

set(HEADERS
	dummyserializer.h
	fileserializer.h
	memoryserializer.h
	serializationinterface.h
	tcpserializer.h
	vectorserializer.h
	${PROJECT_BINARY_DIR}/src/serutconfig.h)

set(SOURCES
	dummyserializer.cpp
	fileserializer.cpp
	memoryserializer.cpp
	serializationinterface.cpp
	tcpserializer.cpp
	vectorserializer.cpp
	)

if (MSVC)
	set(CMAKE_DEBUG_POSTFIX _d)
endif (MSVC)

if (NOT MSVC OR SERUT_COMPILE_STATIC)
	add_library(serut-static STATIC ${SOURCES} ${HEADERS})
	set_target_properties(serut-static PROPERTIES OUTPUT_NAME serut)
	set_target_properties(serut-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
	set(SERUT_INSTALLTARGETS serut-static)
	target_link_libraries(serut-static ${SERUT_LINK_LIBS})
endif (NOT MSVC OR SERUT_COMPILE_STATIC)

if ((NOT MSVC AND NOT SERUT_COMPILE_STATIC_ONLY) OR (MSVC AND NOT SERUT_COMPILE_STATIC))
	add_library(serut-shared SHARED ${SOURCES} ${HEADERS})
	set_target_properties(serut-shared PROPERTIES OUTPUT_NAME serut)
	set_target_properties(serut-shared PROPERTIES VERSION ${VERSION})
	set_target_properties(serut-shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)
	set(SERUT_INSTALLTARGETS ${SERUT_INSTALLTARGETS} serut-shared)
	target_link_libraries(serut-shared ${SERUT_LINK_LIBS})
endif ()

apply_include_paths("${SERUT_INTERNAL_INCLUDES}")
apply_include_paths("${SERUT_EXTERNAL_INCLUDES}")

install(FILES ${HEADERS} DESTINATION include/serut)
install(TARGETS ${SERUT_INSTALLTARGETS} DESTINATION ${LIBRARY_INSTALL_DIR})

