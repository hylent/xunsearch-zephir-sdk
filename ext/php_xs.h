
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_XS_H
#define PHP_XS_H 1

#ifdef PHP_WIN32
#define ZEPHIR_RELEASE 1
#endif

#include "kernel/globals.h"

#define PHP_XS_NAME        "xs"
#define PHP_XS_VERSION     "1.4.9"
#define PHP_XS_EXTNAME     "xs"
#define PHP_XS_AUTHOR      "Hylent"
#define PHP_XS_ZEPVERSION  "0.7.0b"
#define PHP_XS_DESCRIPTION "Xunsearch SDK Zephir implementation"



ZEND_BEGIN_MODULE_GLOBALS(xs)

	int initialized;

	/* Memory */
	zephir_memory_entry *start_memory; /**< The first preallocated frame */
	zephir_memory_entry *end_memory; /**< The last preallocate frame */
	zephir_memory_entry *active_memory; /**< The current memory frame */

	/* Virtual Symbol Tables */
	zephir_symbol_table *active_symbol_table;

	/** Function cache */
	HashTable *fcache;

	zephir_fcall_cache_entry *scache[ZEPHIR_MAX_CACHE_SLOTS];

	/* Cache enabled */
	unsigned int cache_enabled;

	/* Max recursion control */
	unsigned int recursive_lock;

	/* Global constants */
	zval *global_true;
	zval *global_false;
	zval *global_null;
	
ZEND_END_MODULE_GLOBALS(xs)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(xs)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) TSRMG(xs_globals_id, zend_xs_globals *, v)
#else
	#define ZEPHIR_GLOBAL(v) (xs_globals.v)
#endif

#ifdef ZTS
	#define ZEPHIR_VGLOBAL ((zend_xs_globals *) (*((void ***) tsrm_ls))[TSRM_UNSHUFFLE_RSRC_ID(xs_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(xs_globals)
#endif

#define ZEPHIR_API ZEND_API

#define zephir_globals_def xs_globals
#define zend_zephir_globals_def zend_xs_globals

extern zend_module_entry xs_module_entry;
#define phpext_xs_ptr &xs_module_entry

#endif
