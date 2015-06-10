
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
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/hash.h"
#include "kernel/concat.h"
#include "kernel/exception.h"


ZEPHIR_INIT_CLASS(Xs_FieldScheme) {

	ZEPHIR_REGISTER_CLASS(Xs, FieldScheme, xs, fieldscheme, xs_fieldscheme_method_entry, 0);

	zend_declare_property_null(xs_fieldscheme_ce, SL("logger"), ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(xs_fieldscheme_ce, SL("fields"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_fieldscheme_ce, SL("typeMap"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_fieldscheme_ce, SL("vnoMap"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_class_constant_long(xs_fieldscheme_ce, SL("MIXED_VNO"), 255 TSRMLS_CC);

	zend_class_implements(xs_fieldscheme_ce TSRMLS_CC, 1, zend_ce_aggregate);
	return SUCCESS;

}

PHP_METHOD(Xs_FieldScheme, logger) {

	zval *_1, *_3, *_4, *_5, *_6, *_7;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *scheme, *_0, *_2 = NULL, *_8;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_static_property_ce(xs_fieldscheme_ce, SL("logger") TSRMLS_CC);
	if (unlikely(Z_TYPE_P(_0) == IS_NULL)) {
		ZEPHIR_INIT_VAR(scheme);
		object_init_ex(scheme, xs_fieldscheme_ce);
		if (zephir_has_constructor(scheme TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, scheme, "__construct", NULL, 0);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_VAR(_1);
		zephir_create_array(_1, 1, 0 TSRMLS_CC);
		add_assoc_stringl_ex(_1, SS("type"), SL("id"), 1);
		ZEPHIR_INIT_VAR(_2);
		ZVAL_STRING(_2, "id", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, scheme, "addfield", NULL, 13, _2, _1);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "pinyin", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, scheme, "addfield", NULL, 13, _2);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "partial", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, scheme, "addfield", NULL, 13, _2);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_3);
		zephir_create_array(_3, 2, 0 TSRMLS_CC);
		add_assoc_stringl_ex(_3, SS("type"), SL("numeric"), 1);
		add_assoc_stringl_ex(_3, SS("index"), SL("self"), 1);
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "total", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, scheme, "addfield", NULL, 13, _2, _3);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_4);
		zephir_create_array(_4, 2, 0 TSRMLS_CC);
		add_assoc_stringl_ex(_4, SS("type"), SL("numeric"), 1);
		add_assoc_stringl_ex(_4, SS("index"), SL("self"), 1);
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "lastnum", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, scheme, "addfield", NULL, 13, _2, _4);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_5);
		zephir_create_array(_5, 2, 0 TSRMLS_CC);
		add_assoc_stringl_ex(_5, SS("type"), SL("numeric"), 1);
		add_assoc_stringl_ex(_5, SS("index"), SL("self"), 1);
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "currnum", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, scheme, "addfield", NULL, 13, _2, _5);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_6);
		zephir_create_array(_6, 1, 0 TSRMLS_CC);
		add_assoc_stringl_ex(_6, SS("type"), SL("string"), 1);
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "currtag", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, scheme, "addfield", NULL, 13, _2, _6);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_7);
		zephir_create_array(_7, 1, 0 TSRMLS_CC);
		add_assoc_stringl_ex(_7, SS("type"), SL("body"), 1);
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "body", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, scheme, "addfield", NULL, 13, _2, _7);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
		zephir_update_static_property_ce(xs_fieldscheme_ce, SL("logger"), &scheme TSRMLS_CC);
	}
	_8 = zephir_fetch_static_property_ce(xs_fieldscheme_ce, SL("logger") TSRMLS_CC);
	RETURN_CTOR(_8);

}

PHP_METHOD(Xs_FieldScheme, __toString) {

	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_3;
	HashPosition _2;
	zval *field = NULL, *_0, *_1, **_4, *_5 = NULL, *_6 = NULL;
	zval *str;

	ZEPHIR_MM_GROW();
	ZEPHIR_INIT_VAR(str);
	ZVAL_STRING(str, "", 1);

	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("fields"), PH_NOISY_CC);
	if (Z_TYPE_P(_0) == IS_ARRAY) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("fields"), PH_NOISY_CC);
		zephir_is_iterable(_1, &_3, &_2, 0, 0, "xs/fieldscheme.zep", 44);
		for (
		  ; zephir_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
		  ; zephir_hash_move_forward_ex(_3, &_2)
		) {
			ZEPHIR_GET_HVALUE(field, _4);
			ZEPHIR_CALL_METHOD(&_5, field, "toconfig", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_LNVAR(_6);
			ZEPHIR_CONCAT_VS(_6, _5, "\n");
			zephir_concat_self(&str, _6 TSRMLS_CC);
		}
	}
	RETURN_CTOR(str);

}

PHP_METHOD(Xs_FieldScheme, getFieldId) {

	zval *name, *_0, *_1, *_2;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("typeMap"), PH_NOISY_CC);
	if (zephir_array_isset_long_fetch(&name, _0, 10, 1 TSRMLS_CC)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("fields"), PH_NOISY_CC);
		zephir_array_fetch(&_2, _1, name, PH_NOISY | PH_READONLY, "xs/fieldscheme.zep", 54 TSRMLS_CC);
		RETURN_CTORW(_2);
	}
	RETURN_BOOL(0);

}

PHP_METHOD(Xs_FieldScheme, getFieldTitle) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _8;
	HashTable *_5;
	HashPosition _4;
	zval *name, *field = NULL, *_0, *_1, *_2, *_3, **_6, *_7 = NULL, *_9 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(name);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("typeMap"), PH_NOISY_CC);
	if (zephir_array_isset_long_fetch(&name, _0, 11, 0 TSRMLS_CC)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("fields"), PH_NOISY_CC);
		zephir_array_fetch(&_2, _1, name, PH_NOISY | PH_READONLY, "xs/fieldscheme.zep", 65 TSRMLS_CC);
		RETURN_CTOR(_2);
	}
	ZEPHIR_OBS_VAR(_3);
	zephir_read_property_this(&_3, this_ptr, SL("fields"), PH_NOISY_CC);
	if (Z_TYPE_P(_3) == IS_ARRAY) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("fields"), PH_NOISY_CC);
		zephir_is_iterable(_1, &_5, &_4, 0, 0, "xs/fieldscheme.zep", 74);
		for (
		  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_5, &_4)
		) {
			ZEPHIR_GET_HVALUE(field, _6);
			ZEPHIR_OBS_NVAR(_7);
			zephir_read_property(&_7, field, SL("type"), PH_NOISY_CC);
			_8 = ZEPHIR_IS_LONG_IDENTICAL(_7, 0);
			if (_8) {
				ZEPHIR_CALL_METHOD(&_9, field, "isboolindex", NULL, 0);
				zephir_check_call_status();
				_8 = !zephir_is_true(_9);
			}
			if (_8) {
				RETURN_CCTOR(field);
			}
		}
	}
	RETURN_MM_BOOL(0);

}

PHP_METHOD(Xs_FieldScheme, getFieldBody) {

	zval *name, *_0, *_1, *_2;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("typeMap"), PH_NOISY_CC);
	if (zephir_array_isset_long_fetch(&name, _0, 12, 1 TSRMLS_CC)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("fields"), PH_NOISY_CC);
		zephir_array_fetch(&_2, _1, name, PH_NOISY | PH_READONLY, "xs/fieldscheme.zep", 84 TSRMLS_CC);
		RETURN_CTORW(_2);
	}
	RETURN_BOOL(0);

}

PHP_METHOD(Xs_FieldScheme, getField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool throws, _3;
	zval *name = NULL, *throws_param = NULL, *v = NULL, *_0, *_1 = NULL, *_2 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name, &throws_param);

	ZEPHIR_SEPARATE_PARAM(name);
	if (!throws_param) {
		throws = 1;
	} else {
		throws = zephir_get_boolval(throws_param);
	}


	if (Z_TYPE_P(name) == IS_LONG) {
		ZEPHIR_OBS_VAR(v);
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("vnoMap"), PH_NOISY_CC);
		if (!(zephir_array_isset_fetch(&v, _0, name, 0 TSRMLS_CC))) {
			if (throws) {
				ZEPHIR_INIT_VAR(_1);
				object_init_ex(_1, xs_exception_ce);
				ZEPHIR_INIT_VAR(_2);
				ZEPHIR_CONCAT_SV(_2, "Not exists field with vno: ", name);
				ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 4, _2);
				zephir_check_call_status();
				zephir_throw_exception_debug(_1, "xs/fieldscheme.zep", 97 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			RETURN_MM_BOOL(0);
		}
		ZEPHIR_CPY_WRT(name, v);
	}
	ZEPHIR_OBS_NVAR(v);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("fields"), PH_NOISY_CC);
	_3 = !(zephir_array_isset_fetch(&v, _0, name, 0 TSRMLS_CC));
	if (!(_3)) {
		_3 = Z_TYPE_P(v) == IS_NULL;
	}
	if (_3) {
		if (throws) {
			ZEPHIR_INIT_NVAR(_1);
			object_init_ex(_1, xs_exception_ce);
			ZEPHIR_INIT_LNVAR(_2);
			ZEPHIR_CONCAT_SV(_2, "Not exists field with name: ", name);
			ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 4, _2);
			zephir_check_call_status();
			zephir_throw_exception_debug(_1, "xs/fieldscheme.zep", 106 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM_BOOL(0);
	}
	RETURN_CCTOR(v);

}

PHP_METHOD(Xs_FieldScheme, getAllFields) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("fields"), PH_NOISY_CC);
	if (Z_TYPE_P(_0) == IS_ARRAY) {
		RETURN_MM_MEMBER(this_ptr, "fields");
	}
	array_init(return_value);
	RETURN_MM();

}

PHP_METHOD(Xs_FieldScheme, getVnoMap) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("vnoMap"), PH_NOISY_CC);
	if (Z_TYPE_P(_0) == IS_ARRAY) {
		RETURN_MM_MEMBER(this_ptr, "vnoMap");
	}
	array_init(return_value);
	RETURN_MM();

}

PHP_METHOD(Xs_FieldScheme, addField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _0, _12;
	zval *config = NULL;
	zval *fieldArg, *config_param = NULL, *field = NULL, *prev, *_1, *_2, *_3 = NULL, *_4 = NULL, *_5 = NULL, *_6 = NULL, *_7, *_8, *_9 = NULL, *_10 = NULL, *_11, *_13;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &fieldArg, &config_param);

	if (!config_param) {
	ZEPHIR_INIT_VAR(config);
	array_init(config);
	} else {
		zephir_get_arrval(config, config_param);
	}


	_0 = Z_TYPE_P(fieldArg) == IS_OBJECT;
	if (_0) {
		_0 = (zephir_instance_of_ev(fieldArg, xs_fieldmeta_ce TSRMLS_CC));
	}
	if (_0) {
		ZEPHIR_CPY_WRT(field, fieldArg);
	} else {
		ZEPHIR_INIT_NVAR(field);
		object_init_ex(field, xs_fieldmeta_ce);
		ZEPHIR_CALL_METHOD(NULL, field, "__construct", NULL, 14, fieldArg, config);
		zephir_check_call_status();
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("fields"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(_2);
	zephir_read_property(&_2, field, SL("name"), PH_NOISY_CC);
	if (unlikely(zephir_array_isset(_1, _2))) {
		ZEPHIR_INIT_VAR(_3);
		object_init_ex(_3, xs_exception_ce);
		ZEPHIR_OBS_VAR(_4);
		zephir_read_property(&_4, field, SL("name"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_5);
		ZEPHIR_CONCAT_SV(_5, "Duplicated field name: ", _4);
		ZEPHIR_CALL_METHOD(NULL, _3, "__construct", NULL, 4, _5);
		zephir_check_call_status();
		zephir_throw_exception_debug(_3, "xs/fieldscheme.zep", 143 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_6, field, "isspeical", NULL, 15);
	zephir_check_call_status();
	if (zephir_is_true(_6)) {
		ZEPHIR_OBS_VAR(prev);
		_7 = zephir_fetch_nproperty_this(this_ptr, SL("typeMap"), PH_NOISY_CC);
		ZEPHIR_OBS_NVAR(_4);
		zephir_read_property(&_4, field, SL("type"), PH_NOISY_CC);
		if (zephir_array_isset_fetch(&prev, _7, _4, 0 TSRMLS_CC)) {
			ZEPHIR_INIT_NVAR(_3);
			object_init_ex(_3, xs_exception_ce);
			zephir_array_fetch_string(&_8, config, SL("type"), PH_NOISY | PH_READONLY, "xs/fieldscheme.zep", 148 TSRMLS_CC);
			ZEPHIR_OBS_VAR(_9);
			zephir_read_property(&_9, field, SL("name"), PH_NOISY_CC);
			ZEPHIR_INIT_LNVAR(_5);
			ZEPHIR_CONCAT_SVSVSV(_5, "Duplicated ", _8, " field: ", _9, " and ", prev);
			ZEPHIR_CALL_METHOD(NULL, _3, "__construct", NULL, 4, _5);
			zephir_check_call_status();
			zephir_throw_exception_debug(_3, "xs/fieldscheme.zep", 148 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_OBS_NVAR(_9);
		zephir_read_property(&_9, field, SL("name"), PH_NOISY_CC);
		ZEPHIR_OBS_VAR(_10);
		zephir_read_property(&_10, field, SL("type"), PH_NOISY_CC);
		zephir_update_property_array(this_ptr, SL("typeMap"), _10, _9 TSRMLS_CC);
	}
	ZEPHIR_OBS_NVAR(_4);
	zephir_read_property(&_4, field, SL("type"), PH_NOISY_CC);
	if (ZEPHIR_IS_LONG(_4, 12)) {
		ZEPHIR_INIT_ZVAL_NREF(_7);
		ZVAL_LONG(_7, 255);
		zephir_update_property_zval(field, SL("vno"), _7 TSRMLS_CC);
	} else {
		_7 = zephir_fetch_nproperty_this(this_ptr, SL("vnoMap"), PH_NOISY_CC);
		ZEPHIR_INIT_ZVAL_NREF(_11);
		ZVAL_LONG(_11, zephir_fast_count_int(_7 TSRMLS_CC));
		zephir_update_property_zval(field, SL("vno"), _11 TSRMLS_CC);
	}
	ZEPHIR_OBS_NVAR(_4);
	zephir_read_property(&_4, field, SL("name"), PH_NOISY_CC);
	ZEPHIR_OBS_NVAR(_9);
	zephir_read_property(&_9, field, SL("vno"), PH_NOISY_CC);
	zephir_update_property_array(this_ptr, SL("vnoMap"), _9, _4 TSRMLS_CC);
	ZEPHIR_OBS_NVAR(_4);
	zephir_read_property(&_4, field, SL("type"), PH_NOISY_CC);
	_12 = !ZEPHIR_IS_LONG(_4, 10);
	if (!(_12)) {
		_7 = zephir_fetch_nproperty_this(this_ptr, SL("fields"), PH_NOISY_CC);
		ZEPHIR_OBS_NVAR(_10);
		zephir_read_property(&_10, field, SL("name"), PH_NOISY_CC);
		_12 = !(zephir_array_isset(_7, _10));
	}
	if (_12) {
		ZEPHIR_OBS_VAR(_13);
		zephir_read_property(&_13, field, SL("name"), PH_NOISY_CC);
		zephir_update_property_array(this_ptr, SL("fields"), _13, field TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_FieldScheme, checkValid) {

	zval *throws_param = NULL, *_0;
	zend_bool throws;

	zephir_fetch_params(0, 0, 1, &throws_param);

	if (!throws_param) {
		throws = 0;
	} else {
		throws = zephir_get_boolval(throws_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("typeMap"), PH_NOISY_CC);
	if (!(zephir_array_isset_long(_0, 10))) {
		if (throws) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(xs_exception_ce, "Missing field of type ID", "xs/fieldscheme.zep", 171);
			return;
		}
		RETURN_BOOL(0);
	}
	RETURN_BOOL(1);

}

PHP_METHOD(Xs_FieldScheme, getIterator) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;

	ZEPHIR_MM_GROW();

	object_init_ex(return_value, zephir_get_internal_ce(SS("arrayiterator") TSRMLS_CC));
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("fields"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 8, _0);
	zephir_check_call_status();
	RETURN_MM();

}

