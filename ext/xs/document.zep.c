
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
#include "kernel/memory.h"
#include "kernel/string.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/hash.h"


ZEPHIR_INIT_CLASS(Xs_Document) {

	ZEPHIR_REGISTER_CLASS(Xs, Document, xs, document, xs_document_method_entry, 0);

	zend_declare_property_long(xs_document_ce, SL("resSize"), 20, ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_string(xs_document_ce, SL("resFormat"), "Idocid/Irank/Iccount/ipercent/fweight", ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(xs_document_ce, SL("data"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_document_ce, SL("terms"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_document_ce, SL("texts"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_document_ce, SL("charset"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_document_ce, SL("meta"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(xs_document_ce TSRMLS_CC, 1, zend_ce_arrayaccess);
	zend_class_implements(xs_document_ce TSRMLS_CC, 1, zend_ce_aggregate);
	return SUCCESS;

}

PHP_METHOD(Xs_Document, __construct) {

	zephir_fcall_cache_entry *_2 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *d = NULL;
	zval *p = NULL, *d_param = NULL, *_0, *_1, *_3, *_4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &p, &d_param);

	if (!p) {
		p = ZEPHIR_GLOBAL(global_null);
	}
	if (!d_param) {
		ZEPHIR_INIT_VAR(d);
		ZVAL_STRING(d, "", 1);
	} else {
		zephir_get_strval(d, d_param);
	}


	if (Z_TYPE_P(p) == IS_ARRAY) {
		zephir_update_property_this(this_ptr, SL("data"), p TSRMLS_CC);
	} else {
		ZEPHIR_INIT_VAR(_0);
		array_init(_0);
		zephir_update_property_this(this_ptr, SL("data"), _0 TSRMLS_CC);
		if (Z_TYPE_P(p) == IS_STRING) {
			_1 = zephir_fetch_static_property_ce(xs_document_ce, SL("resSize") TSRMLS_CC);
			if (!ZEPHIR_IS_LONG_IDENTICAL(_1, zephir_fast_strlen_ev(p))) {
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "setcharset", &_2, 0, p);
				zephir_check_call_status();
				RETURN_MM_NULL();
			}
			_3 = zephir_fetch_static_property_ce(xs_document_ce, SL("resFormat") TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(&_4, "unpack", NULL, 5, _3, p);
			zephir_check_call_status();
			zephir_update_property_this(this_ptr, SL("meta"), _4 TSRMLS_CC);
		}
	}
	if (zephir_fast_strlen_ev(d) > 0) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setcharset", &_2, 0, d);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Document, __get) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _1;
	zval *name_param = NULL, *v, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_OBS_VAR(v);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
	_1 = zephir_array_isset_fetch(&v, _0, name, 0 TSRMLS_CC);
	if (_1) {
		_1 = Z_TYPE_P(v) != IS_NULL;
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "autoconvert", NULL, 6, v);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Document, __set) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *value, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &value);

	zephir_get_strval(name, name_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("meta"), PH_NOISY_CC);
	if (unlikely(Z_TYPE_P(_0) != IS_NULL)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(xs_exception_ce, "Magick property of result document is read-only", "xs/document.zep", 48);
		return;
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setfield", NULL, 0, name, value);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Document, __call) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _3;
	zval *args = NULL;
	zval *name_param = NULL, *args_param = NULL, *v, *_0, *_1 = NULL, *_2, *_4, *_5;
	zval *name = NULL, *nameLower = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &args_param);

	zephir_get_strval(name, name_param);
	zephir_get_arrval(args, args_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("meta"), PH_NOISY_CC);
	if (Z_TYPE_P(_0) != IS_NULL) {
		ZEPHIR_INIT_VAR(_1);
		zephir_fast_strtolower(_1, name);
		zephir_get_strval(nameLower, _1);
		ZEPHIR_OBS_VAR(v);
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("meta"), PH_NOISY_CC);
		_3 = zephir_array_isset_fetch(&v, _2, nameLower, 0 TSRMLS_CC);
		if (_3) {
			_3 = Z_TYPE_P(v) != IS_NULL;
		}
		if (_3) {
			RETURN_CCTOR(v);
		}
	}
	ZEPHIR_INIT_NVAR(_1);
	object_init_ex(_1, xs_exception_ce);
	ZEPHIR_INIT_VAR(_4);
	zephir_get_class(_4, this_ptr, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_5);
	ZEPHIR_CONCAT_SVSVS(_5, "Call to undefined method ", _4, "::", name, "()");
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 4, _5);
	zephir_check_call_status();
	zephir_throw_exception_debug(_1, "xs/document.zep", 67 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

PHP_METHOD(Xs_Document, getCharset) {


	RETURN_MEMBER(this_ptr, "charset");

}

PHP_METHOD(Xs_Document, setCharset) {

	zval *charset_param = NULL, *_0, *_1;
	zval *charset = NULL, *charsetUpper = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &charset_param);

	zephir_get_strval(charset, charset_param);


	ZEPHIR_INIT_VAR(_0);
	zephir_fast_strtoupper(_0, charset);
	zephir_get_strval(charsetUpper, _0);
	if (ZEPHIR_IS_STRING(charsetUpper, "UTF8")) {
		ZEPHIR_INIT_ZVAL_NREF(_1);
		ZVAL_STRING(_1, "UTF-8", 1);
		zephir_update_property_this(this_ptr, SL("charset"), _1 TSRMLS_CC);
	} else {
		zephir_update_property_this(this_ptr, SL("charset"), charsetUpper TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Document, getFields) {


	RETURN_MEMBER(this_ptr, "data");

}

PHP_METHOD(Xs_Document, setFields) {

	zval *data_param = NULL, *_0 = NULL, *_1;
	zval *data = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &data_param);

	if (!data_param) {
	ZEPHIR_INIT_VAR(data);
	array_init(data);
	} else {
		zephir_get_arrval(data, data_param);
	}


	if (ZEPHIR_IS_STRING_IDENTICAL(data, "")) {
		ZEPHIR_INIT_VAR(_0);
		array_init(_0);
		zephir_update_property_this(this_ptr, SL("data"), _0 TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("meta"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("terms"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("texts"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(_0);
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
		zephir_fast_array_merge(_0, &(_1), &(data) TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("data"), _0 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Document, setField) {

	zend_bool isMeta;
	zval *name_param = NULL, *value, *isMeta_param = NULL, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &name_param, &value, &isMeta_param);

	zephir_get_strval(name, name_param);
	if (!isMeta_param) {
		isMeta = 0;
	} else {
		isMeta = zephir_get_boolval(isMeta_param);
	}


	if (Z_TYPE_P(value) == IS_NULL) {
		if (isMeta) {
			_0 = zephir_fetch_nproperty_this(this_ptr, SL("meta"), PH_NOISY_CC);
			zephir_array_unset(&_0, name, PH_SEPARATE);
		} else {
			_0 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
			zephir_array_unset(&_0, name, PH_SEPARATE);
		}
	} else {
		if (isMeta) {
			zephir_update_property_array(this_ptr, SL("meta"), name, value TSRMLS_CC);
		} else {
			zephir_update_property_array(this_ptr, SL("data"), name, value TSRMLS_CC);
		}
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Document, f) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "__get", NULL, 0, name);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Xs_Document, getAddTerms) {

	zephir_fcall_cache_entry *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_2;
	HashPosition _1;
	zval *field_param = NULL, *ts, *t = NULL, *weight = NULL, *terms, *_0, **_3, *_4 = NULL;
	zval *field = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &field_param);

	zephir_get_strval(field, field_param);


	ZEPHIR_OBS_VAR(ts);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("terms"), PH_NOISY_CC);
	if (!(zephir_array_isset_fetch(&ts, _0, field, 0 TSRMLS_CC))) {
		RETURN_MM_NULL();
	}
	if (Z_TYPE_P(ts) != IS_ARRAY) {
		RETURN_MM_NULL();
	}
	ZEPHIR_INIT_VAR(terms);
	array_init(terms);
	zephir_is_iterable(ts, &_2, &_1, 0, 0, "xs/document.zep", 145);
	for (
	  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HMKEY(t, _2, _1);
		ZEPHIR_GET_HVALUE(weight, _3);
		ZEPHIR_CALL_METHOD(&_4, this_ptr, "autoconvert", &_5, 6, t);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(t, _4);
		zephir_array_update_zval(&terms, t, &weight, PH_COPY | PH_SEPARATE);
	}
	RETURN_CCTOR(terms);

}

PHP_METHOD(Xs_Document, getAddIndex) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _1;
	zval *field_param = NULL, *v, *_0;
	zval *field = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &field_param);

	zephir_get_strval(field, field_param);


	ZEPHIR_OBS_VAR(v);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("texts"), PH_NOISY_CC);
	_1 = !(zephir_array_isset_fetch(&v, _0, field, 0 TSRMLS_CC));
	if (!(_1)) {
		_1 = Z_TYPE_P(v) == IS_NULL;
	}
	if (_1) {
		RETURN_MM_NULL();
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "autoconvert", NULL, 6, v);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Xs_Document, addTerm) {

	long weight, _2;
	zval *field_param = NULL, *term_param = NULL, *weight_param = NULL, *v = NULL, *_0, *_1;
	zval *field = NULL, *term = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &field_param, &term_param, &weight_param);

	zephir_get_strval(field, field_param);
	zephir_get_strval(term, term_param);
	if (!weight_param) {
		weight = 1;
	} else {
		weight = zephir_get_intval(weight_param);
	}


	ZEPHIR_OBS_VAR(v);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("terms"), PH_NOISY_CC);
	zephir_array_fetch(&_1, _0, field, PH_READONLY, "xs/document.zep", 163 TSRMLS_CC);
	if (zephir_array_isset_fetch(&v, _1, term, 0 TSRMLS_CC)) {
		ZEPHIR_INIT_NVAR(v);
		_2 = zephir_get_numberval(v);
		ZVAL_LONG(v, _2 + weight);
	} else {
		ZEPHIR_INIT_NVAR(v);
		ZVAL_LONG(v, weight);
	}
	zephir_update_property_array_multi(this_ptr, SL("terms"), &v TSRMLS_CC, SL("zz"), 2, field, term);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Document, addIndex) {

	zval *field_param = NULL, *text_param = NULL, *v = NULL, *_0;
	zval *field = NULL, *text = NULL, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &field_param, &text_param);

	zephir_get_strval(field, field_param);
	zephir_get_strval(text, text_param);


	ZEPHIR_OBS_VAR(v);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("texts"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&v, _0, field, 0 TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_CONCAT_SV(_1, "\n", text);
		zephir_concat_self(&v, _1 TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(v, text);
	}
	zephir_update_property_array(this_ptr, SL("texts"), field, v TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Document, getIterator) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_7 = NULL;
	zend_bool _1;
	zval *from = NULL, *to = NULL, *_5 = NULL, *_6 = NULL;
	zval *data = NULL, *_0, *_2, *_3, *_4 = NULL, *_8;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
	_1 = zephir_is_true(_0);
	if (_1) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
		_1 = !ZEPHIR_IS_STRING_IDENTICAL(_2, "UTF-8");
	}
	if (_1) {
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("meta"), PH_NOISY_CC);
		if (Z_TYPE_P(_3) == IS_NULL) {
			ZEPHIR_OBS_VAR(_4);
			zephir_read_property_this(&_4, this_ptr, SL("charset"), PH_NOISY_CC);
			zephir_get_strval(_5, _4);
			ZEPHIR_CPY_WRT(from, _5);
			ZEPHIR_INIT_VAR(to);
			ZVAL_STRING(to, "UTF-8", 1);
		} else {
			ZEPHIR_INIT_NVAR(from);
			ZVAL_STRING(from, "UTF-8", 1);
			ZEPHIR_OBS_NVAR(_4);
			zephir_read_property_this(&_4, this_ptr, SL("charset"), PH_NOISY_CC);
			zephir_get_strval(_6, _4);
			ZEPHIR_CPY_WRT(to, _6);
		}
		_8 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
		ZEPHIR_CALL_CE_STATIC(&data, xs_xs_ce, "convert", &_7, 7, _8, to, from);
		zephir_check_call_status();
	} else {
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
		ZEPHIR_CPY_WRT(data, _3);
	}
	object_init_ex(return_value, zephir_get_internal_ce(SS("arrayiterator") TSRMLS_CC));
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 8, data);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Xs_Document, offsetExists) {

	zval *name_param = NULL, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
	RETURN_MM_BOOL(zephir_array_isset(_0, name));

}

PHP_METHOD(Xs_Document, offsetGet) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "__get", NULL, 0, name);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Xs_Document, offsetSet) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *value, *_0 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &value);

	zephir_get_strval(name, name_param);


	if (zephir_fast_strlen_ev(name) > 0) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "__set", NULL, 0, name, value);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Document, offsetUnset) {

	zval *name_param = NULL, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
	zephir_array_unset(&_0, name, PH_SEPARATE);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Document, beforeSubmit) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *index, *_0, *_1, *_2 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &index);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
	if (Z_TYPE_P(_0) == IS_NULL) {
		ZEPHIR_OBS_VAR(_1);
		zephir_read_property(&_1, index, SL("xs"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&_2, _1, "getdefaultcharset", NULL, 0);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("charset"), _2 TSRMLS_CC);
	}
	RETURN_MM_BOOL(1);

}

PHP_METHOD(Xs_Document, afterSubmit) {

	zval *index;

	zephir_fetch_params(0, 1, 0, &index);



	RETURN_BOOL(1);

}

PHP_METHOD(Xs_Document, autoConvert) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_9 = NULL;
	zend_bool _2, _3, _4;
	zval *charset = NULL, *from = NULL, *to = NULL, *_1 = NULL;
	zval *value, *_0, *_5, *_6, _7, *_8;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value);



	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("charset"), PH_NOISY_CC);
	zephir_get_strval(_1, _0);
	ZEPHIR_CPY_WRT(charset, _1);
	_2 = ZEPHIR_IS_STRING(charset, "");
	if (!(_2)) {
		_2 = ZEPHIR_IS_STRING(charset, "UTF-8");
	}
	_3 = _2;
	if (!(_3)) {
		_3 = Z_TYPE_P(value) != IS_STRING;
	}
	_4 = _3;
	if (!(_4)) {
		ZEPHIR_INIT_VAR(_5);
		ZEPHIR_INIT_VAR(_6);
		ZEPHIR_SINIT_VAR(_7);
		ZVAL_STRING(&_7, "/[\\x81-\\xfe]/", 0);
		zephir_preg_match(_6, &_7, value, _5, 0, 0 , 0  TSRMLS_CC);
		_4 = !zephir_is_true(_6);
	}
	if (_4) {
		RETVAL_ZVAL(value, 1, 0);
		RETURN_MM();
	}
	_8 = zephir_fetch_nproperty_this(this_ptr, SL("meta"), PH_NOISY_CC);
	if (Z_TYPE_P(_8) == IS_NULL) {
		ZEPHIR_CPY_WRT(from, charset);
		ZEPHIR_INIT_VAR(to);
		ZVAL_STRING(to, "UTF-8", 1);
	} else {
		ZEPHIR_INIT_NVAR(from);
		ZVAL_STRING(from, "UTF-8", 1);
		ZEPHIR_CPY_WRT(to, charset);
	}
	ZEPHIR_RETURN_CALL_CE_STATIC(xs_xs_ce, "convert", &_9, 7, value, to, from);
	zephir_check_call_status();
	RETURN_MM();

}

