EXTRA_DIST = test.sh

if HAVE_CXXTEST
cxxtest_src = tests.cpp
cxxtest_test = test.sh
else
cxxtest_src = 
cxxtest_test =
endif


BUILT_SOURCE = $(cxxtest_src)
CLEANFILES = $(cxxtest_src)

test_sources = spritetest.h 
tests.cpp: $(test_sources) cxxtest
	$(CXXTESTGEN) -o $@ $^
cxxtest:
	if [ ! -x ../bin/cxxtestgen ]; then \
	cd ../cxxtest/python && \
	python setup.py build && \
	python setup.py install --home ../.. && \
	cp -r cxxtest ../../bin/ && \
	cd ../../src/; \
fi

lib_LTLIBRARIES = libgameengine.la
libgameengine_la_LIBADD = $(LIB_SDL) $(LIB_SDL_IMAGE) $(LIB_SDL_TTF)
libgameengine_la_LDFLAGS = $(all_libraries) -version-info 0:0:0 -no-undefined
libgameengine_la_SOURCES = \
	button.cpp button.h \
	component.cpp component.h \
	gameengine.cpp gameengine.h \
	gui.cpp gui.h \
	sprite.cpp sprite.h 

bin_PROGRAMS = enginetest

enginetest_SOURCES = \
	main.cpp \
	$(cxxtest_src) $(test_sources)
