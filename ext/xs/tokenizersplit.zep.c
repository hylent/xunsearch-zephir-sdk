
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
#include "kernel/string.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"


ZEPHIR_INIT_CLASS(Xs_TokenizerSplit) {

	ZEPHIR_REGISTER_CLASS(Xs, TokenizerSplit, xs, tokenizersplit, xs_tokenizersplit_method_entry, 0);

	zend_declare_property_string(xs_tokenizersplit_ce, SL("arg"), " ", ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(xs_tokenizersplit_ce TSRMLS_CC, 1, xs_tokenizer_ce);
	return SUCCESS;

}

PHP_METHOD(Xs_TokenizerSplit, __construct) {

	zval *arg_param = NULL, *_0 = NULL;
	zval *arg = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &arg_param);

	if (!arg_param) {
		ZEPHIR_INIT_VAR(arg);
		ZVAL_STRING(arg, "", 1);
	} else {
		zephir_get_strval(arg, arg_param);
	}


	if (zephir_fast_strlen_ev(arg) > 0) {
		zephir_update_property_this(this_ptr, SL("arg"), arg TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_TokenizerSplit, getTokens) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _1, _6;
	zval *value_param = NULL, *doc = NULL, *_0, *_2, _3, _4, *_5, *_7, _8, _9, *_10, *_11;
	zval *value = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &value_param, &doc);

	zephir_get_strval(value, value_param);
	if (!doc) {
		doc = ZEPHIR_GLOBAL(global_null);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("arg"), PH_NOISY_CC);
	_1 = zephir_fast_strlen_ev(_0) > 2;
	if (_1) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("arg"), PH_NOISY_CC);
		ZEPHIR_SINIT_VAR(_3);
		ZVAL_LONG(&_3, 0);
		ZEPHIR_SINIT_VAR(_4);
		ZVAL_LONG(&_4, 1);
		ZEPHIR_INIT_VAR(_5);
		zephir_substr(_5, _2, 0 , 1 , 0);
		_1 = ZEPHIR_IS_LONG(_5, '/');
	}
	_6 = _1;
	if (_6) {
		_7 = zephir_fetch_nproperty_this(this_ptr, SL("arg"), PH_NOISY_CC);
		ZEPHIR_SINIT_VAR(_8);
		ZVAL_LONG(&_8, -1);
		ZEPHIR_SINIT_VAR(_9);
		ZVAL_LONG(&_9, 1);
		ZEPHIR_INIT_VAR(_10);
		zephir_substr(_10, _7, -1 , 1 , 0);
		_6 = ZEPHIR_IS_LONG(_10, '/');
	}
	if (_6) {
		_11 = zephir_fetch_nproperty_this(this_ptr, SL("arg"), PH_NOISY_CC);
		ZEPHIR_RETURN_CALL_FUNCTION("preg_split", NULL, 45, _11, value);
		zephir_check_call_status();
		RETURN_MM();
	}
	_11 = zephir_fetch_nproperty_this(this_ptr, SL("arg"), PH_NOISY_CC);
	zephir_fast_explode(return_value, _11, value, LONG_MAX TSRMLS_CC);
	RETURN_MM();

}

