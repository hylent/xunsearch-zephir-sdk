
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#if PHP_VERSION_ID < 50500
#include <locale.h>
#endif

#include "php_ext.h"
#include "xs.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *xs_tokenizer_ce;
zend_class_entry *xs_component_ce;
zend_class_entry *xs_server_ce;
zend_class_entry *xs_command_ce;
zend_class_entry *xs_document_ce;
zend_class_entry *xs_exception_ce;
zend_class_entry *xs_fieldmeta_ce;
zend_class_entry *xs_fieldscheme_ce;
zend_class_entry *xs_index_ce;
zend_class_entry *xs_search_ce;
zend_class_entry *xs_tokenizerfull_ce;
zend_class_entry *xs_tokenizernone_ce;
zend_class_entry *xs_tokenizerscws_ce;
zend_class_entry *xs_tokenizersplit_ce;
zend_class_entry *xs_tokenizerxlen_ce;
zend_class_entry *xs_tokenizerxstep_ce;
zend_class_entry *xs_xs_ce;

ZEND_DECLARE_MODULE_GLOBALS(xs)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(xs)
{
#if PHP_VERSION_ID < 50500
	char* old_lc_all = setlocale(LC_ALL, NULL);
	if (old_lc_all) {
		size_t len = strlen(old_lc_all);
		char *tmp  = calloc(len+1, 1);
		if (UNEXPECTED(!tmp)) {
			return FAILURE;
		}

		memcpy(tmp, old_lc_all, len);
		old_lc_all = tmp;
	}

	setlocale(LC_ALL, "C");
#endif
	REGISTER_INI_ENTRIES();
	ZEPHIR_INIT(Xs_Tokenizer);
	ZEPHIR_INIT(Xs_Component);
	ZEPHIR_INIT(Xs_Server);
	ZEPHIR_INIT(Xs_Command);
	ZEPHIR_INIT(Xs_Document);
	ZEPHIR_INIT(Xs_Exception);
	ZEPHIR_INIT(Xs_FieldMeta);
	ZEPHIR_INIT(Xs_FieldScheme);
	ZEPHIR_INIT(Xs_Index);
	ZEPHIR_INIT(Xs_Search);
	ZEPHIR_INIT(Xs_TokenizerFull);
	ZEPHIR_INIT(Xs_TokenizerNone);
	ZEPHIR_INIT(Xs_TokenizerScws);
	ZEPHIR_INIT(Xs_TokenizerSplit);
	ZEPHIR_INIT(Xs_TokenizerXlen);
	ZEPHIR_INIT(Xs_TokenizerXstep);
	ZEPHIR_INIT(Xs_Xs);

#if PHP_VERSION_ID < 50500
	setlocale(LC_ALL, old_lc_all);
	free(old_lc_all);
#endif
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(xs)
{

	zephir_deinitialize_memory(TSRMLS_C);
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_xs_globals *xs_globals TSRMLS_DC)
{
	xs_globals->initialized = 0;

	/* Memory options */
	xs_globals->active_memory = NULL;

	/* Virtual Symbol Tables */
	xs_globals->active_symbol_table = NULL;

	/* Cache Enabled */
	xs_globals->cache_enabled = 1;

	/* Recursive Lock */
	xs_globals->recursive_lock = 0;

	/* Static cache */
	memset(xs_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);


}

static PHP_RINIT_FUNCTION(xs)
{

	zend_xs_globals *xs_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(xs_globals_ptr TSRMLS_CC);
	//zephir_init_interned_strings(TSRMLS_C);

	zephir_initialize_memory(xs_globals_ptr TSRMLS_CC);


	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(xs)
{

	

	zephir_deinitialize_memory(TSRMLS_C);
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(xs)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_XS_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_XS_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_XS_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_XS_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_XS_ZEPVERSION);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(xs)
{
	php_zephir_init_globals(xs_globals TSRMLS_CC);
}

static PHP_GSHUTDOWN_FUNCTION(xs)
{

}


zend_function_entry php_xs_functions[] = {
ZEND_FE_END

};

zend_module_entry xs_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	PHP_XS_EXTNAME,
	php_xs_functions,
	PHP_MINIT(xs),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(xs),
#else
	NULL,
#endif
	PHP_RINIT(xs),
	PHP_RSHUTDOWN(xs),
	PHP_MINFO(xs),
	PHP_XS_VERSION,
	ZEND_MODULE_GLOBALS(xs),
	PHP_GINIT(xs),
	PHP_GSHUTDOWN(xs),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_XS
ZEND_GET_MODULE(xs)
#endif
