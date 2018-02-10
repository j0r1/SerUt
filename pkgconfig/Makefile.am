### all of the standard pc files we need to generate
pcfiles = 							\
	serut.pc

pcfiles_uninstalled =						\
	serut-uninstalled.pc

all-local: $(pcfiles) $(pcfiles_uninstalled)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = $(pcfiles)

EXTRA_DIST =							\
	serut.pc.in						\
	serut-uninstalled.pc.in

CLEANFILES = $(pcfiles) $(pcfiles_uninstalled)
