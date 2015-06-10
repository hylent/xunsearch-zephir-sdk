
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
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/operators.h"


ZEPHIR_INIT_CLASS(Xs_TokenizerXlen) {

	ZEPHIR_REGISTER_CLASS(Xs, TokenizerXlen, xs, tokenizerxlen, xs_tokenizerxlen_method_entry, 0);

	zend_declare_property_long(xs_tokenizerxlen_ce, SL("arg"), 2, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(xs_tokenizerxlen_ce TSRMLS_CC, 1, xs_tokenizer_ce);
	return SUCCESS;

}

PHP_METHOD(Xs_TokenizerXlen, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *arg_param = NULL, *_0 = NULL, *_1, *_2 = NULL, *_3 = NULL;
	long arg;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &arg_param);

	if (!arg_param) {
		arg = 0;
	} else {
		arg = zephir_get_intval(arg_param);
	}


	if (arg > 0) {
		ZEPHIR_INIT_VAR(_0);
		ZVAL_LONG(_0, 255);
		ZEPHIR_INIT_VAR(_1);
		ZVAL_LONG(_1, arg);
		ZEPHIR_CALL_FUNCTION(&_2, "min", NULL, 26, _0, _1);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, 1);
		ZEPHIR_CALL_FUNCTION(&_3, "max", NULL, 27, _0, _2);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("arg"), _3 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_TokenizerXlen, getTokens) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *value_param = NULL, *doc = NULL, *_0;
	zval *value = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &value_param, &doc);

	zephir_get_strval(value, value_param);
	if (!doc) {
		doc = ZEPHIR_GLOBAL(global_null);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("arg"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_FUNCTION("str_split", NULL, 64, value, _0);
	zephir_check_call_status();
	RETURN_MM();

}

