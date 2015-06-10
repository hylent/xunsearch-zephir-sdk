
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/memory.h"


ZEPHIR_INIT_CLASS(Xs_TokenizerFull) {

	ZEPHIR_REGISTER_CLASS(Xs, TokenizerFull, xs, tokenizerfull, xs_tokenizerfull_method_entry, 0);

	zend_class_implements(xs_tokenizerfull_ce TSRMLS_CC, 1, xs_tokenizer_ce);
	return SUCCESS;

}

PHP_METHOD(Xs_TokenizerFull, getTokens) {

	zval *value_param = NULL, *doc = NULL;
	zval *value = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &value_param, &doc);

	zephir_get_strval(value, value_param);
	if (!doc) {
		doc = ZEPHIR_GLOBAL(global_null);
	}


	zephir_create_array(return_value, 1, 0 TSRMLS_CC);
	zephir_array_fast_append(return_value, value);
	RETURN_MM();

}

