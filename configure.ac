# -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([libgameengine], [0.0.1], [aramande@hackular.com])
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Checks for arguments.
AC_ARG_ENABLE([debug],
              [  --enable-debug          Enable debug (Warning, might slow down execution)],
              debug=$enableval,
              debug="")

AC_ARG_ENABLE([warning],
              [  --disable-warning          Disable warnings],
              warning=$enableval,
              warning=$enableval)

# Unit testing.
AC_ARG_ENABLE(tests, AC_HELP_STRING(
	      [--disable-tests], [Do not include test suite]),
	      enable_tests=$enableval, enable_tests=yes)

AM_CONDITIONAL(HAVE_CXXTEST, test "$enable_tests" = yes)
if test "$enable_tests" = yes; then
	CXXTEST_CFLAGS="-I../cxxtest"
	CXXTESTGEN="../bin/cxxtestgen"
	AM_CXXFLAGS="$AM_CXXFLAGS -DHAVE_CXXTEST $CXXTEST_CFLAGS"
	AC_SUBST(CXXTESTGEN)
	AC_DEFINE(HAVE_CXXTEST, 1, [Defined if we include the test suite])
fi

if test "x${debug}" = "xyes"; then
  AM_CXXFLAGS="$AM_CXXFLAGS -g -DDEBUG"
  AC_MSG_RESULT([Debug mode initiated])
else
  AM_CXXFLAGS="$AM_CXXFLAGS -DNDEBUG"
fi

if test "x${warning}" = "xyes"; then
  AM_CXXFLAGS="$AM_CXXFLAGS -DWARN"
  AC_MSG_RESULT([Warnings activated])
fi

AM_CXXFLAGS="$AM_CXXFLAGS -DDATADIR=\"${datadir}\""

# Checks for libraries
SDL_VERSION=1.2.13
AM_PATH_SDL($SDL_VERSION,
            :,
            AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
)

AC_CHECK_LIB([SDL_ttf], [TTF_OpenFont],,check_sdl_ttf="no")
AC_CHECK_LIB(SDL_image, IMG_Load,,check_sdl_image="no")
#AC_CHECK_LIB(guichan, gcnGuichanVersion,,check_guichan="no")
#AC_CHECK_LIB(guichan_sdl, gcnSDL,,check_guichan_sdl="no")
#AC_CHECK_LIB([GL], [glBegin],,check_ogl="no")

if test x${check_sdl_ttf} = xno; then
       AC_MSG_ERROR([SDL_ttf library required])
fi
if test x${check_sdl_image} = xno; then
       AC_MSG_ERROR([SDL_image library required])
fi
#if test x${check_guichan} = xno; then
#  			  AC_MSG_ERROR([Guichan library required (http://guichan.sourceforge.net)])
#fi
#if test x${check_guichan_sdl} = xno; then
#   		  AC_MSG_ERROR([Guichan SDL library required (http://guichan.sourceforge.net)])
#fi
#if test x${check_ogl} = xno; then
#   		  AC_MSG_ERROR([OpenGL library required])
#fi

AM_CXXFLAGS="$AM_CXXFLAGS $SDL_CFLAGS"
AM_LDFLAGS="$AM_LDFLAGS $SDL_LIBS"

DATA_FILES=`cd data ; find . \( -name CVS -o -name ".svn*" -o -name "Makefile*" \) -prune -o -name ".#*" -o -type d -o -print`
DATA_FILES=`echo $DATA_FILES`


AC_SUBST([DATA_FILES])
AC_SUBST(AM_CXXFLAGS, "$AM_CXXFLAGS")
AC_SUBST(AM_LDFLAGS, "$AM_LDFLAGS")
AC_SUBST(PKGDATADIR, "${datadir}/${PACKAGE}")
AC_SUBST(PACKAGE, "${PACKAGE}")

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 data/Makefile
                 src/Makefile])
AC_OUTPUT
