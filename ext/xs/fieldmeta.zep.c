
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
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/string.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/exception.h"


ZEPHIR_INIT_CLASS(Xs_FieldMeta) {

	ZEPHIR_REGISTER_CLASS(Xs, FieldMeta, xs, fieldmeta, xs_fieldmeta_method_entry, 0);

	zend_declare_property_null(xs_fieldmeta_ce, SL("tokenizers"), ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(xs_fieldmeta_ce, SL("name"), ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_long(xs_fieldmeta_ce, SL("cutlen"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_long(xs_fieldmeta_ce, SL("weight"), 1, ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_long(xs_fieldmeta_ce, SL("type"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_long(xs_fieldmeta_ce, SL("vno"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_long(xs_fieldmeta_ce, SL("tokenizer"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_long(xs_fieldmeta_ce, SL("flag"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_class_constant_long(xs_fieldmeta_ce, SL("MAX_WDF"), 0x3f TSRMLS_CC);

	zend_declare_class_constant_long(xs_fieldmeta_ce, SL("TYPE_STRING"), 0 TSRMLS_CC);

	zend_declare_class_constant_long(xs_fieldmeta_ce, SL("TYPE_NUMERIC"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(xs_fieldmeta_ce, SL("TYPE_DATE"), 2 TSRMLS_CC);

	zend_declare_class_constant_long(xs_fieldmeta_ce, SL("TYPE_ID"), 10 TSRMLS_CC);

	zend_declare_class_constant_long(xs_fieldmeta_ce, SL("TYPE_TITLE"), 11 TSRMLS_CC);

	zend_declare_class_constant_long(xs_fieldmeta_ce, SL("TYPE_BODY"), 12 TSRMLS_CC);

	zend_declare_class_constant_long(xs_fieldmeta_ce, SL("FLAG_INDEX_SELF"), 0x01 TSRMLS_CC);

	zend_declare_class_constant_long(xs_fieldmeta_ce, SL("FLAG_INDEX_MIXED"), 0x02 TSRMLS_CC);

	zend_declare_class_constant_long(xs_fieldmeta_ce, SL("FLAG_INDEX_BOTH"), 0x03 TSRMLS_CC);

	zend_declare_class_constant_long(xs_fieldmeta_ce, SL("FLAG_WITH_POSITION"), 0x10 TSRMLS_CC);

	zend_declare_class_constant_long(xs_fieldmeta_ce, SL("FLAG_NON_BOOL"), 0x80 TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Xs_FieldMeta, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *config = NULL;
	zval *name_param = NULL, *config_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name_param, &config_param);

	zephir_get_strval(name, name_param);
	if (!config_param) {
	ZEPHIR_INIT_VAR(config);
	array_init(config);
	} else {
		zephir_get_arrval(config, config_param);
	}


	zephir_update_property_this(this_ptr, SL("name"), name TSRMLS_CC);
	if (1 == 1) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "fromconfig", NULL, 0, config);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_FieldMeta, __toString) {

	zval *_1 = NULL;
	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("name"), PH_NOISY_CC);
	zephir_get_strval(_1, _0);
	RETURN_CTOR(_1);

}

PHP_METHOD(Xs_FieldMeta, val) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _1;
	zval *value = NULL, *_0, *_2 = NULL, _3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value);

	ZEPHIR_SEPARATE_PARAM(value);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
	if (ZEPHIR_IS_LONG(_0, 2)) {
		_1 = !(zephir_is_numeric(value));
		if (!(_1)) {
			_1 = zephir_fast_strlen_ev(value) != 8;
		}
		if (_1) {
			ZEPHIR_INIT_VAR(_2);
			if (zephir_is_numeric(value)) {
				ZEPHIR_CPY_WRT(_2, value);
			} else {
				ZEPHIR_CALL_FUNCTION(&_2, "strtotime", NULL, 9, value);
				zephir_check_call_status();
			}
			ZEPHIR_SINIT_VAR(_3);
			ZVAL_STRING(&_3, "Ymd", 0);
			ZEPHIR_CALL_FUNCTION(&value, "date", NULL, 10, &_3, _2);
			zephir_check_call_status();
		}
	}
	RETVAL_ZVAL(value, 1, 0);
	RETURN_MM();

}

PHP_METHOD(Xs_FieldMeta, withPos) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
	if (((int) (zephir_get_numberval(_0)) & 0x10)) {
		RETURN_BOOL(1);
	}
	RETURN_BOOL(0);

}

PHP_METHOD(Xs_FieldMeta, isBoolIndex) {

	zend_bool _2;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0, *_1 = NULL, *_3;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
	if (((int) (zephir_get_numberval(_0)) & 0x80)) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "hasindex", NULL, 0);
	zephir_check_call_status();
	_2 = !zephir_is_true(_1);
	if (!(_2)) {
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("tokenizer"), PH_NOISY_CC);
		_2 = !ZEPHIR_IS_LONG_IDENTICAL(_3, 0);
	}
	RETURN_MM_BOOL(_2);

}

PHP_METHOD(Xs_FieldMeta, isNumeric) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
	RETURN_BOOL(ZEPHIR_IS_LONG(_0, 1));

}

PHP_METHOD(Xs_FieldMeta, isSpeical) {

	zend_bool _1, _3;
	zval *_0, *_2, *_4;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
	_1 = ZEPHIR_IS_LONG(_0, 10);
	if (!(_1)) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
		_1 = ZEPHIR_IS_LONG(_2, 11);
	}
	_3 = _1;
	if (!(_3)) {
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
		_3 = ZEPHIR_IS_LONG(_4, 12);
	}
	RETURN_BOOL(_3);

}

PHP_METHOD(Xs_FieldMeta, hasIndex) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
	if (((int) (zephir_get_numberval(_0)) & 0x03)) {
		RETURN_BOOL(1);
	}
	RETURN_BOOL(0);

}

PHP_METHOD(Xs_FieldMeta, hasIndexMixed) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
	if (((int) (zephir_get_numberval(_0)) & 0x02)) {
		RETURN_BOOL(1);
	}
	RETURN_BOOL(0);

}

PHP_METHOD(Xs_FieldMeta, hasIndexSelf) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
	if (((int) (zephir_get_numberval(_0)) & 0x01)) {
		RETURN_BOOL(1);
	}
	RETURN_BOOL(0);

}

PHP_METHOD(Xs_FieldMeta, hasCustomTokenizer) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("tokenizer"), PH_NOISY_CC);
	RETURN_BOOL(!ZEPHIR_IS_LONG_IDENTICAL(_0, 0));

}

PHP_METHOD(Xs_FieldMeta, getCustomTokenizer) {

	zend_class_entry *_15, *_17;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name = NULL, *arg = NULL, *_7 = NULL, *_9 = NULL, *_11 = NULL;
	zval *tokenizer = NULL, *m = NULL, *_0, *_1, *_2, *_3, _4, *_5 = NULL, *_6, *_8 = NULL, *_10, *_12 = NULL, *_13 = NULL, *_14 = NULL, *_16 = NULL;

	ZEPHIR_MM_GROW();
	ZEPHIR_INIT_VAR(m);
	ZVAL_NULL(m);

	ZEPHIR_OBS_VAR(tokenizer);
	_0 = zephir_fetch_static_property_ce(xs_fieldmeta_ce, SL("tokenizers") TSRMLS_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("tokenizer"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&tokenizer, _0, _1, 0 TSRMLS_CC)) {
		RETURN_CCTOR(tokenizer);
	}
	ZEPHIR_INIT_VAR(_2);
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("tokenizer"), PH_NOISY_CC);
	ZEPHIR_SINIT_VAR(_4);
	ZVAL_STRING(&_4, "/^([^\\(]+)\\((.*)\\)$/", 0);
	zephir_preg_match(_2, &_4, _3, m, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(_2)) {
		ZEPHIR_INIT_VAR(_5);
		zephir_array_fetch_long(&_6, m, 1, PH_NOISY | PH_READONLY, "xs/fieldmeta.zep", 125 TSRMLS_CC);
		zephir_ucfirst(_5, _6);
		zephir_get_strval(_7, _5);
		ZEPHIR_INIT_VAR(name);
		ZEPHIR_CONCAT_SSV(name, "Xs", "\\Tokenizer", _7);
		ZEPHIR_OBS_VAR(_8);
		zephir_array_fetch_long(&_8, m, 2, PH_NOISY, "xs/fieldmeta.zep", 126 TSRMLS_CC);
		zephir_get_strval(_9, _8);
		ZEPHIR_CPY_WRT(arg, _9);
	} else {
		ZEPHIR_INIT_NVAR(_5);
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("tokenizer"), PH_NOISY_CC);
		zephir_ucfirst(_5, _10);
		zephir_get_strval(_11, _5);
		ZEPHIR_INIT_NVAR(name);
		ZEPHIR_CONCAT_SSV(name, "Xs", "\\Tokenizer", _11);
		ZEPHIR_INIT_NVAR(arg);
		ZVAL_EMPTY_STRING(arg);
	}
	if (unlikely(!(zephir_class_exists(name, zephir_is_true(ZEPHIR_GLOBAL(global_true))  TSRMLS_CC)))) {
		ZEPHIR_INIT_NVAR(_5);
		object_init_ex(_5, xs_exception_ce);
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("name"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_12);
		ZEPHIR_CONCAT_SVSVS(_12, "Undefined custom tokenizer ", name, " for field `", _10, "`");
		ZEPHIR_CALL_METHOD(NULL, _5, "__construct", NULL, 4, _12);
		zephir_check_call_status();
		zephir_throw_exception_debug(_5, "xs/fieldmeta.zep", 133 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_NVAR(tokenizer);
	if (zephir_fast_strlen_ev(arg) > 0) {
		zephir_fetch_safe_class(_14, name);
		_15 = zend_fetch_class(Z_STRVAL_P(_14), Z_STRLEN_P(_14), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
		object_init_ex(tokenizer, _15);
		if (zephir_has_constructor(tokenizer TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, tokenizer, "__construct", NULL, 0, arg);
			zephir_check_call_status();
		}
	} else {
		zephir_fetch_safe_class(_16, name);
		_17 = zend_fetch_class(Z_STRVAL_P(_16), Z_STRLEN_P(_16), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
		object_init_ex(tokenizer, _17);
		if (zephir_has_constructor(tokenizer TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, tokenizer, "__construct", NULL, 0);
			zephir_check_call_status();
		}
	}
	if (unlikely(!((zephir_instance_of_ev(tokenizer, xs_tokenizer_ce TSRMLS_CC))))) {
		ZEPHIR_INIT_NVAR(_5);
		object_init_ex(_5, xs_exception_ce);
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("name"), PH_NOISY_CC);
		ZEPHIR_INIT_LNVAR(_12);
		ZEPHIR_CONCAT_VSVS(_12, name, " for field `", _10, "` does not implement Tokenizer interface");
		ZEPHIR_CALL_METHOD(NULL, _5, "__construct", NULL, 4, _12);
		zephir_check_call_status();
		zephir_throw_exception_debug(_5, "xs/fieldmeta.zep", 143 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_OBS_NVAR(_8);
	zephir_read_property_this(&_8, this_ptr, SL("tokenizer"), PH_NOISY_CC);
	zephir_update_static_property_array_multi_ce(xs_fieldmeta_ce, SL("tokenizers"), &tokenizer TSRMLS_CC, SL("z"), 1, _8);
	RETURN_CCTOR(tokenizer);

}

PHP_METHOD(Xs_FieldMeta, toConfig) {

	zend_bool _6, _9, _10, _13, _14, _16;
	zval *s;
	zval index, *_0, *_1, *_2, *_3, *_4, *_5, *_7, *_8 = NULL, *_11, *_12, *_15;

	ZEPHIR_MM_GROW();
	ZEPHIR_INIT_VAR(s);
	ZVAL_STRING(s, "", 1);

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("name"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_CONCAT_SVS(_1, "[", _0, "]\n");
	zephir_concat_self(&s, _1 TSRMLS_CC);
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
	do {
		if (ZEPHIR_IS_LONG(_2, 1)) {
			zephir_concat_self_str(&s, "type = numeric\n", sizeof("type = numeric\n")-1 TSRMLS_CC);
			break;
		}
		if (ZEPHIR_IS_LONG(_2, 10)) {
			zephir_concat_self_str(&s, "type = id\n", sizeof("type = id\n")-1 TSRMLS_CC);
			break;
		}
		if (ZEPHIR_IS_LONG(_2, 11)) {
			zephir_concat_self_str(&s, "type = title\n", sizeof("type = title\n")-1 TSRMLS_CC);
			break;
		}
		if (ZEPHIR_IS_LONG(_2, 12)) {
			zephir_concat_self_str(&s, "type = body\n", sizeof("type = body\n")-1 TSRMLS_CC);
			break;
		}
	} while(0);

	_3 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
	if (!ZEPHIR_IS_LONG_IDENTICAL(_3, 12)) {
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
		ZEPHIR_SINIT_VAR(index);
		ZVAL_LONG(&index, ((int) (zephir_get_numberval(_4)) & 0x03));
		if (zephir_is_true(&index)) {
			do {
				if (ZEPHIR_IS_LONG(&index, 0x03)) {
					_5 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
					if (!ZEPHIR_IS_LONG_IDENTICAL(_5, 11)) {
						zephir_concat_self_str(&s, "index = both\n", sizeof("index = both\n")-1 TSRMLS_CC);
					}
					break;
				}
				if (ZEPHIR_IS_LONG(&index, 0x02)) {
					zephir_concat_self_str(&s, "index = mixed\n", sizeof("index = mixed\n")-1 TSRMLS_CC);
					break;
				}
				_5 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
				if (!ZEPHIR_IS_LONG_IDENTICAL(_5, 10)) {
					zephir_concat_self_str(&s, "index = self\n", sizeof("index = self\n")-1 TSRMLS_CC);
				}
				break;
			} while(0);

		}
	}
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
	_6 = !ZEPHIR_IS_LONG_IDENTICAL(_4, 10);
	if (_6) {
		_5 = zephir_fetch_nproperty_this(this_ptr, SL("tokenizer"), PH_NOISY_CC);
		_6 = !ZEPHIR_IS_LONG_IDENTICAL(_5, 0);
	}
	if (_6) {
		_7 = zephir_fetch_nproperty_this(this_ptr, SL("tokenizer"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_8);
		ZEPHIR_CONCAT_SVS(_8, "tokenizer = ", _7, "\n");
		zephir_concat_self(&s, _8 TSRMLS_CC);
	}
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("cutlen"), PH_NOISY_CC);
	_9 = ZEPHIR_GT_LONG(_4, 0);
	if (_9) {
		_7 = zephir_fetch_nproperty_this(this_ptr, SL("cutlen"), PH_NOISY_CC);
		_10 = ZEPHIR_IS_LONG_IDENTICAL(_7, 300);
		if (_10) {
			_11 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
			_10 = ZEPHIR_IS_LONG_IDENTICAL(_11, 12);
		}
		_9 = !(_10);
	}
	if (_9) {
		_12 = zephir_fetch_nproperty_this(this_ptr, SL("cutlen"), PH_NOISY_CC);
		ZEPHIR_INIT_LNVAR(_8);
		ZEPHIR_CONCAT_SVS(_8, "cutlen = ", _12, "\n");
		zephir_concat_self(&s, _8 TSRMLS_CC);
	}
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("weight"), PH_NOISY_CC);
	_13 = !ZEPHIR_IS_LONG_IDENTICAL(_4, 1);
	if (_13) {
		_7 = zephir_fetch_nproperty_this(this_ptr, SL("weight"), PH_NOISY_CC);
		_14 = ZEPHIR_IS_LONG_IDENTICAL(_7, 5);
		if (_14) {
			_12 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
			_14 = ZEPHIR_IS_LONG_IDENTICAL(_12, 11);
		}
		_13 = !(_14);
	}
	if (_13) {
		_15 = zephir_fetch_nproperty_this(this_ptr, SL("weight"), PH_NOISY_CC);
		ZEPHIR_INIT_LNVAR(_8);
		ZEPHIR_CONCAT_SVS(_8, "weight = ", _15, "\n");
		zephir_concat_self(&s, _8 TSRMLS_CC);
	}
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
	if (((int) (zephir_get_numberval(_4)) & 0x10)) {
		_7 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
		_16 = !ZEPHIR_IS_LONG_IDENTICAL(_7, 12);
		if (_16) {
			_12 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
			_16 = !ZEPHIR_IS_LONG_IDENTICAL(_12, 11);
		}
		if (_16) {
			zephir_concat_self_str(&s, "phrase = yes\n", sizeof("phrase = yes\n")-1 TSRMLS_CC);
		}
	} else {
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
		_16 = ZEPHIR_IS_LONG_IDENTICAL(_4, 12);
		if (!(_16)) {
			_7 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
			_16 = ZEPHIR_IS_LONG_IDENTICAL(_7, 11);
		}
		if (_16) {
			zephir_concat_self_str(&s, "phrase = no\n", sizeof("phrase = no\n")-1 TSRMLS_CC);
		}
	}
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
	if (((int) (zephir_get_numberval(_4)) & 0x80)) {
		zephir_concat_self_str(&s, "non_bool = yes\n", sizeof("non_bool = yes\n")-1 TSRMLS_CC);
	}
	RETURN_CTOR(s);

}

PHP_METHOD(Xs_FieldMeta, fromConfig) {

	zend_bool _8, _11, _12, _13;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_3 = NULL, *_5 = NULL;
	zval *predef = NULL;
	zval *config_param = NULL, *c = NULL, *_0 = NULL, *_1 = NULL, *_2 = NULL, *_4 = NULL, *_6, *_7, *_9, *_10;
	zval *config = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &config_param);

	zephir_get_arrval(config, config_param);


	ZEPHIR_OBS_VAR(c);
	if (zephir_array_isset_string_fetch(&c, config, SS("type"), 0 TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(_0);
		zephir_fast_strtoupper(_0, c);
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_CONCAT_SSV(_1, "Xs\\FieldMeta", "::TYPE_", _0);
		zephir_get_strval(predef, _1);
		ZEPHIR_CALL_FUNCTION(&_2, "defined", &_3, 11, predef);
		zephir_check_call_status();
		if (zephir_is_true(_2)) {
			ZEPHIR_CALL_FUNCTION(&_4, "constant", &_5, 12, predef);
			zephir_check_call_status();
			zephir_update_property_this(this_ptr, SL("type"), _4 TSRMLS_CC);
			_6 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
			do {
				if (ZEPHIR_IS_LONG(_6, 10)) {
					ZEPHIR_INIT_ZVAL_NREF(_7);
					ZVAL_LONG(_7, 0x01);
					zephir_update_property_this(this_ptr, SL("flag"), _7 TSRMLS_CC);
					ZEPHIR_INIT_ZVAL_NREF(_7);
					ZVAL_STRING(_7, "full", 1);
					zephir_update_property_this(this_ptr, SL("tokenizer"), _7 TSRMLS_CC);
					break;
				}
				if (ZEPHIR_IS_LONG(_6, 11)) {
					ZEPHIR_INIT_ZVAL_NREF(_7);
					ZVAL_LONG(_7, (0x03 | 0x10));
					zephir_update_property_this(this_ptr, SL("flag"), _7 TSRMLS_CC);
					ZEPHIR_INIT_ZVAL_NREF(_7);
					ZVAL_LONG(_7, 5);
					zephir_update_property_this(this_ptr, SL("weight"), _7 TSRMLS_CC);
					break;
				}
				if (ZEPHIR_IS_LONG(_6, 12)) {
					ZEPHIR_INIT_ZVAL_NREF(_7);
					ZVAL_LONG(_7, 255);
					zephir_update_property_this(this_ptr, SL("vno"), _7 TSRMLS_CC);
					ZEPHIR_INIT_ZVAL_NREF(_7);
					ZVAL_LONG(_7, (0x01 | 0x10));
					zephir_update_property_this(this_ptr, SL("flag"), _7 TSRMLS_CC);
					ZEPHIR_INIT_ZVAL_NREF(_7);
					ZVAL_LONG(_7, 300);
					zephir_update_property_this(this_ptr, SL("cutlen"), _7 TSRMLS_CC);
					break;
				}
			} while(0);

		}
	}
	ZEPHIR_OBS_NVAR(c);
	_8 = zephir_array_isset_string_fetch(&c, config, SS("index"), 0 TSRMLS_CC);
	if (_8) {
		_6 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
		_8 = !ZEPHIR_IS_LONG(_6, 12);
	}
	if (_8) {
		ZEPHIR_INIT_NVAR(_0);
		zephir_fast_strtoupper(_0, c);
		ZEPHIR_INIT_LNVAR(_1);
		ZEPHIR_CONCAT_SSV(_1, "Xs\\FieldMeta", "::FLAG_INDEX_", _0);
		zephir_get_strval(predef, _1);
		ZEPHIR_CALL_FUNCTION(&_2, "defined", &_3, 11, predef);
		zephir_check_call_status();
		if (zephir_is_true(_2)) {
			_7 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
			ZEPHIR_CALL_FUNCTION(&_4, "constant", &_5, 12, predef);
			zephir_check_call_status();
			ZEPHIR_INIT_ZVAL_NREF(_9);
			ZVAL_LONG(_9, ((((int) (zephir_get_numberval(_7)) & ~(0x03))) | zephir_get_intval(_4)));
			zephir_update_property_this(this_ptr, SL("flag"), _9 TSRMLS_CC);
		}
		_6 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
		if (ZEPHIR_IS_LONG(_6, 10)) {
			_9 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
			ZEPHIR_INIT_ZVAL_NREF(_10);
			ZVAL_LONG(_10, ((int) (zephir_get_numberval(_9)) | 0x01));
			zephir_update_property_this(this_ptr, SL("flag"), _10 TSRMLS_CC);
		}
	}
	ZEPHIR_OBS_NVAR(c);
	if (zephir_array_isset_string_fetch(&c, config, SS("cutlen"), 0 TSRMLS_CC)) {
		ZEPHIR_INIT_ZVAL_NREF(_6);
		ZVAL_LONG(_6, zephir_get_intval(c));
		zephir_update_property_this(this_ptr, SL("cutlen"), _6 TSRMLS_CC);
	}
	ZEPHIR_OBS_NVAR(c);
	_11 = zephir_array_isset_string_fetch(&c, config, SS("weight"), 0 TSRMLS_CC);
	if (_11) {
		_6 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
		_11 = !ZEPHIR_IS_LONG(_6, 12);
	}
	if (_11) {
		ZEPHIR_INIT_ZVAL_NREF(_9);
		ZVAL_LONG(_9, (zephir_get_intval(c) & 0x3f));
		zephir_update_property_this(this_ptr, SL("weight"), _9 TSRMLS_CC);
	}
	ZEPHIR_OBS_NVAR(c);
	if (zephir_array_isset_string_fetch(&c, config, SS("phrase"), 0 TSRMLS_CC)) {
		ZEPHIR_INIT_NVAR(_0);
		zephir_fast_strtolower(_0, c);
		do {
			if (ZEPHIR_IS_STRING(_0, "yes")) {
				_9 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
				ZEPHIR_INIT_ZVAL_NREF(_10);
				ZVAL_LONG(_10, ((int) (zephir_get_numberval(_9)) | 0x10));
				zephir_update_property_this(this_ptr, SL("flag"), _10 TSRMLS_CC);
				break;
			}
			if (ZEPHIR_IS_STRING(_0, "no")) {
				_6 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
				ZEPHIR_INIT_ZVAL_NREF(_9);
				ZVAL_LONG(_9, ((int) (zephir_get_numberval(_6)) & ~(0x10)));
				zephir_update_property_this(this_ptr, SL("flag"), _9 TSRMLS_CC);
				break;
			}
		} while(0);

	}
	ZEPHIR_OBS_NVAR(c);
	if (zephir_array_isset_string_fetch(&c, config, SS("non_bool"), 0 TSRMLS_CC)) {
		ZEPHIR_INIT_NVAR(_0);
		zephir_fast_strtolower(_0, c);
		do {
			if (ZEPHIR_IS_STRING(_0, "yes")) {
				_6 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
				ZEPHIR_INIT_ZVAL_NREF(_9);
				ZVAL_LONG(_9, ((int) (zephir_get_numberval(_6)) | 0x80));
				zephir_update_property_this(this_ptr, SL("flag"), _9 TSRMLS_CC);
				break;
			}
			if (ZEPHIR_IS_STRING(_0, "no")) {
				_6 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
				ZEPHIR_INIT_ZVAL_NREF(_9);
				ZVAL_LONG(_9, ((int) (zephir_get_numberval(_6)) & ~(0x80)));
				zephir_update_property_this(this_ptr, SL("flag"), _9 TSRMLS_CC);
				break;
			}
		} while(0);

	}
	ZEPHIR_OBS_NVAR(c);
	_12 = zephir_array_isset_string_fetch(&c, config, SS("tokenizer"), 0 TSRMLS_CC);
	if (_12) {
		_6 = zephir_fetch_nproperty_this(this_ptr, SL("type"), PH_NOISY_CC);
		_12 = !ZEPHIR_IS_LONG(_6, 10);
	}
	_13 = _12;
	if (_13) {
		_13 = !ZEPHIR_IS_STRING(c, "default");
	}
	if (_13) {
		zephir_update_property_this(this_ptr, SL("tokenizer"), c TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

