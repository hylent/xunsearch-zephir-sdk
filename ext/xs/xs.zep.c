
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
#include "kernel/hash.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "kernel/file.h"
#include "kernel/exception.h"
#include "kernel/concat.h"


ZEPHIR_INIT_CLASS(Xs_Xs) {

	ZEPHIR_REGISTER_CLASS_EX(Xs, Xs, xs, xs, xs_component_ce, xs_xs_method_entry, 0);

	zend_declare_property_null(xs_xs_ce, SL("lastXs"), ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(xs_xs_ce, SL("index"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_xs_ce, SL("search"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_xs_ce, SL("scws"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_xs_ce, SL("scheme"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_xs_ce, SL("bindScheme"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_xs_ce, SL("config"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_class_constant_string(xs_xs_ce, SL("PACKAGE_BUGREPORT"), "http://www.xunsearch.com/bugs" TSRMLS_CC);

	zend_declare_class_constant_string(xs_xs_ce, SL("PACKAGE_NAME"), "xunsearch" TSRMLS_CC);

	zend_declare_class_constant_string(xs_xs_ce, SL("PACKAGE_TARNAME"), "xunsearch" TSRMLS_CC);

	zend_declare_class_constant_string(xs_xs_ce, SL("PACKAGE_URL"), "" TSRMLS_CC);

	zend_declare_class_constant_string(xs_xs_ce, SL("PACKAGE_VERSION"), "1.4.9" TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Xs_Xs, getLastXs) {

	zval *_0;


	_0 = zephir_fetch_static_property_ce(xs_xs_ce, SL("lastXs") TSRMLS_CC);
	RETURN_CTORW(_0);

}

PHP_METHOD(Xs_Xs, convert) {

	zend_bool _5;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_4 = NULL;
	HashTable *_1;
	HashPosition _0;
	zval *to = NULL, *from = NULL;
	zval *data, *to_param = NULL, *from_param = NULL, *k = NULL, *v = NULL, **_2, *_3 = NULL, *_6, *_7, _8;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &data, &to_param, &from_param);

	ZEPHIR_SEPARATE_PARAM(data);
	zephir_get_strval(to, to_param);
	zephir_get_strval(from, from_param);


	if (ZEPHIR_IS_EQUAL(to, from)) {
		RETVAL_ZVAL(data, 1, 0);
		RETURN_MM();
	}
	if (Z_TYPE_P(data) == IS_ARRAY) {
		zephir_is_iterable(data, &_1, &_0, 1, 0, "xs/xs.zep", 38);
		for (
		  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		  ; zephir_hash_move_forward_ex(_1, &_0)
		) {
			ZEPHIR_GET_HMKEY(k, _1, _0);
			ZEPHIR_GET_HVALUE(v, _2);
			ZEPHIR_CALL_SELF(&_3, "convert", &_4, 0, v, to, from);
			zephir_check_call_status();
			zephir_array_update_zval(&data, k, &_3, PH_COPY | PH_SEPARATE);
		}
		RETVAL_ZVAL(data, 1, 0);
		RETURN_MM();
	}
	_5 = Z_TYPE_P(data) == IS_STRING;
	if (_5) {
		ZEPHIR_INIT_VAR(_6);
		ZEPHIR_INIT_VAR(_7);
		ZEPHIR_SINIT_VAR(_8);
		ZVAL_STRING(&_8, "/[\\x81-\\xfe]/", 0);
		zephir_preg_match(_7, &_8, data, _6, 0, 0 , 0  TSRMLS_CC);
		_5 = zephir_is_true(_7);
	}
	if (_5) {
		ZEPHIR_RETURN_CALL_FUNCTION("mb_convert_encoding", NULL, 65, data, to, from);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETVAL_ZVAL(data, 1, 0);
	RETURN_MM();

}

PHP_METHOD(Xs_Xs, __construct) {

	zephir_fcall_cache_entry *_6 = NULL;
	HashTable *_4;
	HashPosition _3;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *file_param = NULL, *config = NULL, *scheme, *k = NULL, *v = NULL, *_0 = NULL, **_5, _7, *_8 = NULL;
	zval *file = NULL, *data = NULL, *_1, *_2 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &file_param);

	zephir_get_strval(file, file_param);


	if (unlikely(!((zephir_file_exists(file TSRMLS_CC) == SUCCESS)))) {
		ZEPHIR_INIT_VAR(_0);
		object_init_ex(_0, xs_exception_ce);
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_CONCAT_SV(_1, "Cannot find project config file: ", file);
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, 4, _1);
		zephir_check_call_status();
		zephir_throw_exception_debug(_0, "xs/xs.zep", 54 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_NVAR(_0);
	zephir_file_get_contents(_0, file TSRMLS_CC);
	zephir_get_strval(_2, _0);
	ZEPHIR_CPY_WRT(data, _2);
	ZEPHIR_CALL_METHOD(&config, this_ptr, "parseinidata", NULL, 66, data);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(scheme);
	object_init_ex(scheme, xs_fieldscheme_ce);
	if (zephir_has_constructor(scheme TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, scheme, "__construct", NULL, 0);
		zephir_check_call_status();
	}
	zephir_is_iterable(config, &_4, &_3, 0, 0, "xs/xs.zep", 67);
	for (
	  ; zephir_hash_get_current_data_ex(_4, (void**) &_5, &_3) == SUCCESS
	  ; zephir_hash_move_forward_ex(_4, &_3)
	) {
		ZEPHIR_GET_HMKEY(k, _4, _3);
		ZEPHIR_GET_HVALUE(v, _5);
		if (Z_TYPE_P(v) == IS_ARRAY) {
			ZEPHIR_CALL_METHOD(NULL, scheme, "addfield", &_6, 13, k, v);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_BOOL(_0, 1);
	ZEPHIR_CALL_METHOD(NULL, scheme, "checkvalid", NULL, 67, _0);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("scheme"), scheme TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("bindScheme"), scheme TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("config"), config TSRMLS_CC);
	if (!(zephir_array_isset_string(config, SS("project.name")))) {
		ZEPHIR_SINIT_VAR(_7);
		ZVAL_STRING(&_7, ".ini", 0);
		ZEPHIR_CALL_FUNCTION(&_8, "basename", NULL, 68, file, &_7);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_STRING(_0, "project.name", 1);
		zephir_update_property_array(this_ptr, SL("config"), _0, _8 TSRMLS_CC);
	}
	zephir_update_static_property_ce(xs_xs_ce, SL("lastXs"), &this_ptr TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Xs, __destruct) {


	zephir_update_property_this(this_ptr, SL("index"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("search"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);

}

PHP_METHOD(Xs_Xs, getScheme) {


	RETURN_MEMBER(this_ptr, "scheme");

}

PHP_METHOD(Xs_Xs, setScheme) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *fs, *_0, *_1, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &fs);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_BOOL(_0, 1);
	ZEPHIR_CALL_METHOD(NULL, fs, "checkvalid", NULL, 0, _0);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("scheme"), fs TSRMLS_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("search"), PH_NOISY_CC);
	if (Z_TYPE_P(_1) != IS_NULL) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("search"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, _2, "markresetscheme", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Xs, restoreScheme) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0, *_1, *_2, *_3, *_4, *_5;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("scheme"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("bindScheme"), PH_NOISY_CC);
	if (!ZEPHIR_IS_IDENTICAL(_0, _1)) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("bindScheme"), PH_NOISY_CC);
		zephir_update_property_this(this_ptr, SL("scheme"), _2 TSRMLS_CC);
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("search"), PH_NOISY_CC);
		if (Z_TYPE_P(_3) != IS_NULL) {
			_4 = zephir_fetch_nproperty_this(this_ptr, SL("search"), PH_NOISY_CC);
			ZEPHIR_INIT_VAR(_5);
			ZVAL_BOOL(_5, 1);
			ZEPHIR_CALL_METHOD(NULL, _4, "markresetscheme", NULL, 0, _5);
			zephir_check_call_status();
		}
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Xs, getConfig) {


	RETURN_MEMBER(this_ptr, "config");

}

PHP_METHOD(Xs_Xs, getName) {

	zval *_0, *_1;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("config"), PH_NOISY_CC);
	zephir_array_fetch_string(&_1, _0, SL("project.name"), PH_NOISY | PH_READONLY, "xs/xs.zep", 117 TSRMLS_CC);
	RETURN_CTORW(_1);

}

PHP_METHOD(Xs_Xs, setName) {

	zval *name_param = NULL, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "project.name", 1);
	zephir_update_property_array(this_ptr, SL("config"), _0, name TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Xs, getDefaultCharset) {

	zval *dc, *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(dc);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("config"), PH_NOISY_CC);
	if (zephir_array_isset_string_fetch(&dc, _0, SS("project.default_charset"), 0 TSRMLS_CC)) {
		zephir_fast_strtoupper(return_value, dc);
		RETURN_MM();
	}
	RETURN_MM_STRING("UTF-8", 1);

}

PHP_METHOD(Xs_Xs, setDefaultCharset) {

	zval *charset_param = NULL, *_0, *_1;
	zval *charset = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &charset_param);

	zephir_get_strval(charset, charset_param);


	ZEPHIR_INIT_VAR(_0);
	zephir_fast_strtoupper(_0, charset);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "project.default_charset", 1);
	zephir_update_property_array(this_ptr, SL("config"), _1, _0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Xs, getIndex) {

	zephir_fcall_cache_entry *_14 = NULL;
	HashTable *_9;
	HashPosition _8;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *conn = NULL, *_2 = NULL, *_7 = NULL, *_11 = NULL;
	zval *index = NULL, *conf = NULL, *adds = NULL, *add = NULL, *pos, *_0, _1, _3, *_4 = NULL, _5, *_6 = NULL, **_10, *_12 = NULL, *_13 = NULL;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("index"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(index, _0);
	if (Z_TYPE_P(index) != IS_NULL) {
		RETURN_CCTOR(index);
	}
	ZEPHIR_OBS_VAR(conf);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("config"), PH_NOISY_CC);
	if (!(zephir_array_isset_string_fetch(&conf, _0, SS("server.index"), 0 TSRMLS_CC))) {
		ZEPHIR_INIT_NVAR(conf);
		ZVAL_LONG(conf, 8383);
	}
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, ";", 0);
	ZEPHIR_INIT_VAR(pos);
	zephir_fast_strpos(pos, conf, &_1, 0 );
	if (ZEPHIR_IS_FALSE_IDENTICAL(pos)) {
		ZEPHIR_INIT_VAR(adds);
		array_init(adds);
		zephir_get_strval(_2, conf);
		ZEPHIR_CPY_WRT(conn, _2);
	} else {
		ZEPHIR_SINIT_VAR(_3);
		ZVAL_LONG(&_3, (zephir_get_numberval(pos) + 1));
		ZEPHIR_INIT_VAR(_4);
		zephir_substr(_4, conf, zephir_get_intval(&_3), 0, ZEPHIR_SUBSTR_NO_LENGTH);
		ZEPHIR_INIT_NVAR(adds);
		zephir_fast_explode_str(adds, SL(";"), _4, LONG_MAX TSRMLS_CC);
		ZEPHIR_SINIT_VAR(_5);
		ZVAL_LONG(&_5, 0);
		ZEPHIR_INIT_VAR(_6);
		zephir_substr(_6, conf, 0 , zephir_get_intval(pos), 0);
		zephir_get_strval(_7, _6);
		ZEPHIR_CPY_WRT(conn, _7);
	}
	ZEPHIR_INIT_NVAR(index);
	object_init_ex(index, xs_index_ce);
	ZEPHIR_CALL_METHOD(NULL, index, "__construct", NULL, 17, conn, this_ptr);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_4);
	ZVAL_LONG(_4, 0);
	ZEPHIR_CALL_METHOD(NULL, index, "settimeout", NULL, 69, _4);
	zephir_check_call_status();
	zephir_is_iterable(adds, &_9, &_8, 0, 0, "xs/xs.zep", 176);
	for (
	  ; zephir_hash_get_current_data_ex(_9, (void**) &_10, &_8) == SUCCESS
	  ; zephir_hash_move_forward_ex(_9, &_8)
	) {
		ZEPHIR_GET_HVALUE(add, _10);
		ZEPHIR_INIT_NVAR(_4);
		zephir_fast_trim(_4, add, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
		zephir_get_strval(_11, _4);
		ZEPHIR_CPY_WRT(conn, _11);
		if (zephir_fast_strlen_ev(conn) > 0) {
			ZEPHIR_CALL_METHOD(&_13, index, "addserver", &_14, 70, conn);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(_6);
			ZVAL_LONG(_6, 0);
			ZEPHIR_CALL_METHOD(NULL, _13, "settimeout", NULL, 69, _6);
			zephir_check_call_status();
		}
	}
	zephir_update_property_this(this_ptr, SL("index"), index TSRMLS_CC);
	RETURN_CCTOR(index);

}

PHP_METHOD(Xs_Xs, getSearch) {

	zephir_fcall_cache_entry *_8 = NULL, *_9 = NULL, *_10 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_2;
	HashPosition _1;
	long i, c;
	zval *item = NULL, *_5 = NULL;
	zval *search = NULL, *conns, *serverSearch, *serverSearchParts, *serverSearchPart = NULL, *ex = NULL, *_0, **_3, *_4 = NULL, *_6 = NULL, *_7;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("search"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(search, _0);
	if (Z_TYPE_P(search) != IS_NULL) {
		RETURN_CCTOR(search);
	}
	ZEPHIR_INIT_VAR(conns);
	array_init(conns);
	ZEPHIR_OBS_VAR(serverSearch);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("config"), PH_NOISY_CC);
	if (zephir_array_isset_string_fetch(&serverSearch, _0, SS("server.search"), 0 TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(serverSearchParts);
		zephir_fast_explode_str(serverSearchParts, SL(";"), serverSearch, LONG_MAX TSRMLS_CC);
		zephir_is_iterable(serverSearchParts, &_2, &_1, 0, 0, "xs/xs.zep", 202);
		for (
		  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
		  ; zephir_hash_move_forward_ex(_2, &_1)
		) {
			ZEPHIR_GET_HVALUE(serverSearchPart, _3);
			ZEPHIR_INIT_NVAR(_4);
			zephir_fast_trim(_4, serverSearchPart, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
			zephir_get_strval(_5, _4);
			ZEPHIR_CPY_WRT(item, _5);
			if (zephir_fast_strlen_ev(item) > 0) {
				zephir_array_append(&conns, item, PH_SEPARATE, "xs/xs.zep", 199);
			}
		}
	} else {
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_LONG(_4, 8384);
		zephir_array_append(&conns, _4, PH_SEPARATE, "xs/xs.zep", 203);
	}
	c = zephir_fast_count_int(conns TSRMLS_CC);
	if (c > 1) {
		Z_SET_ISREF_P(conns);
		ZEPHIR_CALL_FUNCTION(NULL, "shuffle", NULL, 71, conns);
		Z_UNSET_ISREF_P(conns);
		zephir_check_call_status();
	}
	i = 0;
	while (1) {
		if (!(i < c)) {
			break;
		}

		/* try_start_1: */

			ZEPHIR_INIT_NVAR(search);
			object_init_ex(search, xs_search_ce);
			zephir_array_fetch_long(&_7, conns, i, PH_NOISY | PH_READONLY, "xs/xs.zep", 214 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(NULL, search, "__construct", &_8, 72, _7, this_ptr);
			zephir_check_call_status_or_jump(try_end_1);
			ZEPHIR_CALL_METHOD(&_6, this_ptr, "getdefaultcharset", &_9, 0);
			zephir_check_call_status_or_jump(try_end_1);
			ZEPHIR_CALL_METHOD(NULL, search, "setcharset", &_10, 73, _6);
			zephir_check_call_status_or_jump(try_end_1);
			zephir_update_property_this(this_ptr, SL("search"), search TSRMLS_CC);
			RETURN_CCTOR(search);

		try_end_1:

		if (EG(exception)) {
			ZEPHIR_CPY_WRT(ex, EG(exception));
			if (zephir_instance_of_ev(ex, xs_exception_ce TSRMLS_CC)) {
				zend_clear_exception(TSRMLS_C);
				if ((i + 1) >= c) {
					zephir_throw_exception_debug(ex, "xs/xs.zep", 221 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		}
		i++;
	}
	ZEPHIR_THROW_EXCEPTION_DEBUG_STR(xs_exception_ce, "Unreachable!", "xs/xs.zep", 228);
	return;

}

PHP_METHOD(Xs_Xs, getScwsServer) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *scws = NULL, *conn = NULL, *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("scws"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(scws, _0);
	if (Z_TYPE_P(scws) != IS_NULL) {
		RETURN_CCTOR(scws);
	}
	ZEPHIR_OBS_VAR(conn);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("config"), PH_NOISY_CC);
	if (!(zephir_array_isset_string_fetch(&conn, _0, SS("server.search"), 0 TSRMLS_CC))) {
		ZEPHIR_INIT_NVAR(conn);
		ZVAL_LONG(conn, 8384);
	}
	ZEPHIR_INIT_NVAR(scws);
	object_init_ex(scws, xs_server_ce);
	ZEPHIR_CALL_METHOD(NULL, scws, "__construct", NULL, 17, conn, this_ptr);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("scws"), scws TSRMLS_CC);
	RETURN_CCTOR(scws);

}

PHP_METHOD(Xs_Xs, getFieldId) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("scheme"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(_0, "getfieldid", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Xs_Xs, getFieldTitle) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("scheme"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(_0, "getfieldtitle", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Xs_Xs, getFieldBody) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("scheme"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(_0, "getfieldbody", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Xs_Xs, getField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool throws;
	zval *name_param = NULL, *throws_param = NULL, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name_param, &throws_param);

	zephir_get_strval(name, name_param);
	if (!throws_param) {
		throws = 1;
	} else {
		throws = zephir_get_boolval(throws_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("scheme"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(_0, "getfield", NULL, 0, name, (throws ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Xs_Xs, getAllFields) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("scheme"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(_0, "getallfields", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Xs_Xs, parseIniData) {

	zend_bool _5, _6;
	HashTable *_1;
	HashPosition _0;
	char c;
	zval *data_param = NULL, *r, *lines, *line = NULL, *pos = NULL, **_2, *_3 = NULL, _7 = zval_used_for_init, _8 = zval_used_for_init, *_9 = NULL, _10 = zval_used_for_init, _11 = zval_used_for_init, *_12 = NULL, *_14 = NULL, *_16 = NULL, *_17 = NULL, _18 = zval_used_for_init, *_20 = NULL;
	zval *data = NULL, *l = NULL, *sec = NULL, *k = NULL, *v = NULL, *_4 = NULL, *_13 = NULL, *_15 = NULL, *_19 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &data_param);

	zephir_get_strval(data, data_param);
	ZEPHIR_INIT_VAR(r);
	array_init(r);
	ZEPHIR_INIT_VAR(sec);
	ZVAL_STRING(sec, "", 1);


	ZEPHIR_INIT_VAR(lines);
	zephir_fast_explode_str(lines, SL("\n"), data, LONG_MAX TSRMLS_CC);
	zephir_is_iterable(lines, &_1, &_0, 0, 0, "xs/xs.zep", 315);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(line, _2);
		ZEPHIR_INIT_NVAR(_3);
		zephir_fast_trim(_3, line, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
		zephir_get_strval(_4, _3);
		ZEPHIR_CPY_WRT(l, _4);
		if (ZEPHIR_IS_STRING_IDENTICAL(l, "")) {
			continue;
		}
		c = ZEPHIR_STRING_OFFSET(l, 0);
		c = c;
		_5 = c == ';';
		if (!(_5)) {
			_5 = c == '#';
		}
		if (_5) {
			continue;
		}
		_6 = c == '[';
		if (_6) {
			ZEPHIR_SINIT_NVAR(_7);
			ZVAL_LONG(&_7, -1);
			ZEPHIR_SINIT_NVAR(_8);
			ZVAL_LONG(&_8, 1);
			ZEPHIR_INIT_NVAR(_9);
			zephir_substr(_9, l, -1 , 1 , 0);
			_6 = ZEPHIR_IS_STRING_IDENTICAL(_9, "]");
		}
		if (_6) {
			ZEPHIR_SINIT_NVAR(_10);
			ZVAL_LONG(&_10, 1);
			ZEPHIR_SINIT_NVAR(_11);
			ZVAL_LONG(&_11, -1);
			ZEPHIR_INIT_NVAR(_12);
			zephir_substr(_12, l, 1 , -1 , 0);
			zephir_get_strval(_13, _12);
			ZEPHIR_CPY_WRT(sec, _13);
			ZEPHIR_INIT_NVAR(_14);
			array_init(_14);
			zephir_array_update_zval(&r, sec, &_14, PH_COPY | PH_SEPARATE);
			continue;
		}
		ZEPHIR_SINIT_NVAR(_10);
		ZVAL_STRING(&_10, "=", 0);
		ZEPHIR_INIT_NVAR(pos);
		zephir_fast_strpos(pos, line, &_10, 0 );
		if (ZEPHIR_IS_FALSE_IDENTICAL(pos)) {
			continue;
		}
		ZEPHIR_INIT_NVAR(_12);
		ZEPHIR_SINIT_NVAR(_10);
		ZVAL_LONG(&_10, 0);
		ZEPHIR_INIT_NVAR(_14);
		zephir_substr(_14, l, 0 , zephir_get_intval(pos), 0);
		zephir_fast_trim(_12, _14, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
		zephir_get_strval(_15, _12);
		ZEPHIR_CPY_WRT(k, _15);
		ZEPHIR_INIT_NVAR(_16);
		ZEPHIR_SINIT_NVAR(_11);
		ZVAL_LONG(&_11, (zephir_get_numberval(pos) + 1));
		ZEPHIR_INIT_NVAR(_17);
		zephir_substr(_17, l, zephir_get_intval(&_11), 0, ZEPHIR_SUBSTR_NO_LENGTH);
		ZEPHIR_SINIT_NVAR(_18);
		ZVAL_STRING(&_18, " '\"\t", 0);
		zephir_fast_trim(_16, _17, &_18, ZEPHIR_TRIM_BOTH TSRMLS_CC);
		zephir_get_strval(_19, _16);
		ZEPHIR_CPY_WRT(v, _19);
		if (zephir_fast_strlen_ev(sec) > 0) {
			zephir_array_update_multi(&r, &v TSRMLS_CC, SL("zz"), 2, sec, k);
		} else {
			zephir_array_update_zval(&r, k, &v, PH_COPY | PH_SEPARATE);
		}
	}
	RETURN_CCTOR(r);

}

