lib_LTLIBRARIES = libserut.la
libserut_la_SOURCES = serializationinterface.cpp dummyserializer.cpp fileserializer.cpp \
		      memoryserializer.cpp tcpserializer.cpp
libserut_la_LDFLAGS = -release @VERSION@

libserutincludedir = ${includedir}/serut
libserutinclude_HEADERS = serializationinterface.h dummyserializer.h fileserializer.h \
			  memoryserializer.h tcpserializer.h

