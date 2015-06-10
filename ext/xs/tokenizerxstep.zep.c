
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
#include "kernel/string.h"
#include "kernel/array.h"


ZEPHIR_INIT_CLASS(Xs_TokenizerXstep) {

	ZEPHIR_REGISTER_CLASS(Xs, TokenizerXstep, xs, tokenizerxstep, xs_tokenizerxstep_method_entry, 0);

	zend_declare_property_long(xs_tokenizerxstep_ce, SL("arg"), 2, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(xs_tokenizerxstep_ce TSRMLS_CC, 1, xs_tokenizer_ce);
	return SUCCESS;

}

PHP_METHOD(Xs_TokenizerXstep, __construct) {

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

PHP_METHOD(Xs_TokenizerXstep, getTokens) {

	long c, a, i;
	zval *value_param = NULL, *doc = NULL, *terms, *_0, _1 = zval_used_for_init, _2 = zval_used_for_init, *_3 = NULL;
	zval *value = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &value_param, &doc);

	zephir_get_strval(value, value_param);
	if (!doc) {
		doc = ZEPHIR_GLOBAL(global_null);
	}
	ZEPHIR_INIT_VAR(terms);
	array_init(terms);


	c = zephir_fast_strlen_ev(value);
	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("arg"), PH_NOISY_CC);
	a = zephir_get_intval(_0);
	i = a;
	while (1) {
		ZEPHIR_SINIT_NVAR(_1);
		ZVAL_LONG(&_1, 0);
		ZEPHIR_SINIT_NVAR(_2);
		ZVAL_LONG(&_2, i);
		ZEPHIR_INIT_NVAR(_3);
		zephir_substr(_3, value, 0 , zephir_get_intval(&_2), 0);
		zephir_array_append(&terms, _3, PH_SEPARATE, "xs/tokenizerxstep.zep", 23);
		if (i >= c) {
			break;
		}
		i += a;
	}
	RETURN_CCTOR(terms);

}

