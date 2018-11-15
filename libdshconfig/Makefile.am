check_PROGRAMS =  \
	test-dshconfig test-dshconfig-searchdata

INCLUDES = \
	-I$(top_srcdir)

DSHCONFIG_SONAME = 1:0:0

lib_LTLIBRARIES = libdshconfig.la
libdshconfig_la_LDFLAGS = -export-dynamic -version-info $(DSHCONFIG_SONAME)
include_HEADERS = libdshconfig.h
test_dshconfig_SOURCES = test-dshconfig.c
test_dshconfig_LDADD = libdshconfig.la
test_dshconfig_searchdata_SOURCES=test-dshconfig-searchdata.c
test_dshconfig_searchdata_LDADD = libdshconfig.la

libdshconfig_la_SOURCES= \
	libdshconfig.c \
	libdshconfig.h 

TESTS=	tests/test-basic.sh \
	tests/test-dshconfig-searchdata.sh \
	tests/test-longline.sh
EXTRA_DIST= \
	tests/test-basic.input \
	tests/test-basic.output \
	tests/test-dshconfig-searchdata.data \
	$(TESTS) \
	libdshconfig.spec

clean-local:
	-rm -r doc

doc: ${srcdir}/*.[ch]
	-@DOCPP@ --dir doc ${srcdir}/*.[ch]

# Make debian pristine-source
../@PACKAGE@_@VERSION@.orig.tar.gz: 
	if [ ! -f $@ ]; then $(MAKE) distcheck && dch -v "@VERSION@-1" "New upstream version" && mv @PACKAGE@-@VERSION@.tar.gz ../@PACKAGE@_@VERSION@.orig.tar.gz; \
	else \
	rm -f @PACKAGE@-@VERSION@.tar.gz; \
	fi

debiandist: ../@PACKAGE@_@VERSION@.orig.tar.gz

viper: distcheck
	scp @PACKAGE@-@VERSION@.tar.gz viper2.netfort.gr.jp:public_html/software/downloads
	rm -f @PACKAGE@-@VERSION@.tar.gz

upload-dist-all: distcheck
	scp @PACKAGE@-@VERSION@.tar.gz viper2.netfort.gr.jp:public_html/software/downloads
	$(MAKE) ../@PACKAGE@_@VERSION@.orig.tar.gz
