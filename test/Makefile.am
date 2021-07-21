# =============================== System Test =============================== #

EXTRA_PROGRAMS = test_system
test_system_SOURCES = system.c

installcheck-local:
	$(MAKE) $(AM_MAKEFLAGS) test_system$(EXEEXT) \
		CFLAGS="-I$(DESTDIR)$(includedir) -Wall -Wextra -Werror" \
		LDADD="$(DESTDIR)$(libdir)/libvector.la" \
		DEPENDENCIES="$(DESTDIR)$(libdir)/libvector.la"
	./test_system$(EXEEXT)

# ================================ Unit Test ================================ #

check_LTLIBRARIES = libstub.la libvector_test.la
check_PROGRAMS =
TESTS = $(check_PROGRAMS)

libstub_la_SOURCES = stub.c
libstub_la_LDFLAGS = -rpath $(abs_builddir)

libvector_test_la_SOURCES = $(top_srcdir)/source/vector/common.c \
			    $(top_srcdir)/source/vector/access.c \
			    $(top_srcdir)/source/vector/comparison.c \
			    $(top_srcdir)/source/vector/create.c \
			    $(top_srcdir)/source/vector/debug.c \
			    $(top_srcdir)/source/vector/delete.c \
			    $(top_srcdir)/source/vector/insert.c \
			    $(top_srcdir)/source/vector/move.c \
			    $(top_srcdir)/source/vector/remove.c \
			    $(top_srcdir)/source/vector/resize.c \
			    $(top_srcdir)/source/vector/search.c \
			    $(top_srcdir)/source/vector/shift.c \
			    $(top_srcdir)/source/vector/sort.c

# Define malloc, realloc, and free to stub_malloc, stub_realloc, and stub_free
libvector_test_la_CFLAGS = -I$(top_srcdir)/header \
			   -Wall -Wextra -Werror \
			   -Dmalloc=stub_malloc -Drealloc=stub_realloc -Dfree=stub_free \
			   -D__vector_inline__=

libvector_test_la_LIBADD = libstub.la
libvector_test_la_LDFLAGS = -rpath $(abs_builddir) @test_vector_la_ldflags@

# The _GNU_SOURCE feature test macro must be defined in order to obtain the
# definitions of RTLD_DEFAULT and RTLD_NEXT from <dlfcn.h>
TEST_CFLAGS = -I$(top_srcdir)/header \
	      -Wall -Wextra -Werror \
	      -D_GNU_SOURCE -D__vector_inline__=
TEST_LDADD = libvector_test.la -ldl

check_PROGRAMS += test_vector_common
test_vector_common_SOURCES = test.h vector_common.c
test_vector_common_CFLAGS = $(TEST_CFLAGS)
test_vector_common_LDADD = $(TEST_LDADD)
test_vector_common_LDFLAGS = $(TEST_LDFLAGS)

check_PROGRAMS += test_vector_access
test_vector_access_SOURCES = test.h vector_access.c
test_vector_access_CFLAGS = $(TEST_CFLAGS)
test_vector_access_LDADD = $(TEST_LDADD)
test_vector_access_LDFLAGS = $(TEST_LDFLAGS)

check_PROGRAMS += test_vector_comparison
test_vector_comparison_SOURCES = test.h vector_comparison.c
test_vector_comparison_CFLAGS = $(TEST_CFLAGS)
test_vector_comparison_LDADD = $(TEST_LDADD)
test_vector_comparison_LDFLAGS = $(TEST_LDFLAGS)

check_PROGRAMS += test_vector_create
test_vector_create_SOURCES = test.h vector_create.c
test_vector_create_CFLAGS = $(TEST_CFLAGS)
test_vector_create_LDADD = $(TEST_LDADD)
test_vector_create_LDFLAGS = $(TEST_LDFLAGS)

check_PROGRAMS += test_vector_debug
test_vector_debug_SOURCES = test.h vector_debug.c
test_vector_debug_CFLAGS = $(TEST_CFLAGS)
test_vector_debug_LDADD = $(TEST_LDADD)
test_vector_debug_LDFLAGS = $(TEST_LDFLAGS)

check_PROGRAMS += test_vector_delete
test_vector_delete_SOURCES = test.h vector_delete.c
test_vector_delete_CFLAGS = $(TEST_CFLAGS)
test_vector_delete_LDADD = $(TEST_LDADD)
test_vector_delete_LDFLAGS = $(TEST_LDFLAGS)

check_PROGRAMS += test_vector_insert
test_vector_insert_SOURCES = test.h vector_insert.c
test_vector_insert_CFLAGS = $(TEST_CFLAGS)
test_vector_insert_LDADD = $(TEST_LDADD)
test_vector_insert_LDFLAGS = $(TEST_LDFLAGS)

check_PROGRAMS += test_vector_move
test_vector_move_SOURCES = test.h vector_move.c
test_vector_move_CFLAGS = $(TEST_CFLAGS)
test_vector_move_LDADD = $(TEST_LDADD)
test_vector_move_LDFLAGS = $(TEST_LDFLAGS)

check_PROGRAMS += test_vector_remove
test_vector_remove_SOURCES = test.h vector_remove.c
test_vector_remove_CFLAGS = $(TEST_CFLAGS)
test_vector_remove_LDADD = $(TEST_LDADD)
test_vector_remove_LDFLAGS = $(TEST_LDFLAGS)

check_PROGRAMS += test_vector_resize
test_vector_resize_SOURCES = test.h vector_resize.c
test_vector_resize_CFLAGS = $(TEST_CFLAGS)
test_vector_resize_LDADD = $(TEST_LDADD)
test_vector_resize_LDFLAGS = $(TEST_LDFLAGS)

check_PROGRAMS += test_vector_search
test_vector_search_SOURCES = test.h vector_search.c
test_vector_search_CFLAGS = $(TEST_CFLAGS)
test_vector_search_LDADD = $(TEST_LDADD)
test_vector_search_LDFLAGS = $(TEST_LDFLAGS)

check_PROGRAMS += test_vector_shift
test_vector_shift_SOURCES = test.h vector_shift.c
test_vector_shift_CFLAGS = $(TEST_CFLAGS)
test_vector_shift_LDADD = $(TEST_LDADD)
test_vector_shift_LDFLAGS = $(TEST_LDFLAGS)

check_PROGRAMS += test_vector_sort
test_vector_sort_SOURCES = test.h vector_sort.c
test_vector_sort_CFLAGS = $(TEST_CFLAGS)
test_vector_sort_LDADD = $(TEST_LDADD)
test_vector_sort_LDFLAGS = $(TEST_LDFLAGS)
