PHP_ARG_ENABLE(xs, whether to enable xs, [ --enable-xs   Enable Xs])

if test "$PHP_XS" = "yes"; then

	

	if ! test "x" = "x"; then
		PHP_EVAL_LIBLINE(, XS_SHARED_LIBADD)
	fi

	AC_DEFINE(HAVE_XS, 1, [Whether you have Xs])
	xs_sources="xs.c kernel/main.c kernel/memory.c kernel/exception.c kernel/hash.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/extended/array.c kernel/string.c kernel/fcall.c kernel/extended/fcall.c kernel/require.c kernel/file.c kernel/operators.c kernel/math.c kernel/concat.c kernel/variables.c kernel/filter.c kernel/iterator.c kernel/time.c kernel/exit.c xs/command.zep.c
	xs/component.zep.c
	xs/document.zep.c
	xs/exception.zep.c
	xs/fieldmeta.zep.c
	xs/fieldscheme.zep.c
	xs/index.zep.c
	xs/search.zep.c
	xs/server.zep.c
	xs/tokenizer.zep.c
	xs/tokenizerfull.zep.c
	xs/tokenizernone.zep.c
	xs/tokenizerscws.zep.c
	xs/tokenizersplit.zep.c
	xs/tokenizerxlen.zep.c
	xs/tokenizerxstep.zep.c
	xs/xs.zep.c "
	PHP_NEW_EXTENSION(xs, $xs_sources, $ext_shared,, )
	PHP_SUBST(XS_SHARED_LIBADD)

	old_CPPFLAGS=$CPPFLAGS
	CPPFLAGS="$CPPFLAGS $INCLUDES"

	AC_CHECK_DECL(
		[HAVE_BUNDLED_PCRE],
		[
			AC_CHECK_HEADERS(
				[ext/pcre/php_pcre.h],
				[
					PHP_ADD_EXTENSION_DEP([xs], [pcre])
					AC_DEFINE([ZEPHIR_USE_PHP_PCRE], [1], [Whether PHP pcre extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	AC_CHECK_DECL(
		[HAVE_JSON],
		[
			AC_CHECK_HEADERS(
				[ext/json/php_json.h],
				[
					PHP_ADD_EXTENSION_DEP([xs], [json])
					AC_DEFINE([ZEPHIR_USE_PHP_JSON], [1], [Whether PHP json extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	CPPFLAGS=$old_CPPFLAGS

	PHP_INSTALL_HEADERS([ext/xs], [php_XS.h])

fi
