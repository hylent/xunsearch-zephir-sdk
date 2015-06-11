
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
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/string.h"
#include "kernel/array.h"
#include "kernel/hash.h"
#include "kernel/concat.h"
#include "kernel/exception.h"
#include "kernel/math.h"


ZEPHIR_INIT_CLASS(Xs_Search) {

	ZEPHIR_REGISTER_CLASS_EX(Xs, Search, xs, search, xs_server_ce, xs_search_method_entry, 0);

	zend_declare_property_long(xs_search_ce, SL("defaultOp"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_search_ce, SL("prefix"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_search_ce, SL("fieldSet"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_bool(xs_search_ce, SL("resetScheme"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_search_ce, SL("query"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_search_ce, SL("terms"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_search_ce, SL("count"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_search_ce, SL("lastCount"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_search_ce, SL("highlight"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_search_ce, SL("curDb"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_search_ce, SL("curDbs"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_search_ce, SL("lastDb"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_search_ce, SL("lastDbs"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(xs_search_ce, SL("facets"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_long(xs_search_ce, SL("limit"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_long(xs_search_ce, SL("offset"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_string(xs_search_ce, SL("charset"), "UTF-8", ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_class_constant_long(xs_search_ce, SL("PAGE_SIZE"), 10 TSRMLS_CC);

	zend_declare_class_constant_string(xs_search_ce, SL("LOG_DB"), "log_db" TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Xs_Search, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *conn_param = NULL, *xs = NULL;
	zval *conn = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &conn_param, &xs);

	if (!conn_param) {
		ZEPHIR_INIT_VAR(conn);
		ZVAL_STRING(conn, "", 1);
	} else {
		zephir_get_strval(conn, conn_param);
	}
	if (!xs) {
		xs = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_CALL_PARENT(NULL, xs_search_ce, this_ptr, "__construct", &_0, 17, conn, xs);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Search, open) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *conn_param = NULL, *_1;
	zval *conn = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &conn_param);

	zephir_get_strval(conn, conn_param);


	ZEPHIR_CALL_PARENT(NULL, xs_search_ce, this_ptr, "open", &_0, 24, conn);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_1);
	array_init(_1);
	zephir_update_property_this(this_ptr, SL("prefix"), _1 TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("fieldSet"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("lastCount"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Search, setCharset) {

	zval *charset_param = NULL, *_0, *_1;
	zval *charset = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &charset_param);

	zephir_get_strval(charset, charset_param);


	ZEPHIR_INIT_VAR(_0);
	zephir_fast_strtoupper(_0, charset);
	zephir_get_strval(charset, _0);
	if (ZEPHIR_IS_STRING(charset, "UTF8")) {
		ZEPHIR_INIT_ZVAL_NREF(_1);
		ZVAL_STRING(_1, "UTF-8", 1);
		zephir_update_property_this(this_ptr, SL("charset"), _1 TSRMLS_CC);
	} else {
		zephir_update_property_this(this_ptr, SL("charset"), charset TSRMLS_CC);
	}
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, setFuzzy) {

	zval *value_param = NULL, *_0 = NULL;
	zend_bool value;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &value_param);

	if (!value_param) {
		value = 1;
	} else {
		value = zephir_get_boolval(value_param);
	}


	ZEPHIR_INIT_VAR(_0);
	if (value) {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, 1);
	} else {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, 0);
	}
	zephir_update_property_this(this_ptr, SL("defaultOp"), _0 TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, setCutOff) {

	zephir_fcall_cache_entry *_4 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *percent_param = NULL, *weight_param = NULL, *cmd, *_0 = NULL, *_1 = NULL, *_2 = NULL, *_3 = NULL, *_5 = NULL, *_6;
	long percent, weight;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &percent_param, &weight_param);

	percent = zephir_get_intval(percent_param);
	if (!weight_param) {
		weight = 0;
	} else {
		weight = zephir_get_intval(weight_param);
	}


	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 100);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, percent);
	ZEPHIR_CALL_FUNCTION(&_2, "min", NULL, 25, _0, _1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 0);
	ZEPHIR_CALL_FUNCTION(&_3, "max", &_4, 26, _0, _2);
	zephir_check_call_status();
	percent = zephir_get_intval(_3);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 0);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_LONG(_1, (((weight * 10)) & 255));
	ZEPHIR_CALL_FUNCTION(&_5, "max", &_4, 26, _0, _1);
	zephir_check_call_status();
	weight = zephir_get_intval(_5);
	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 199);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_LONG(_1, percent);
	ZEPHIR_INIT_VAR(_6);
	ZVAL_LONG(_6, weight);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _0, _1, _6);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd);
	zephir_check_call_status();
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, setRequireMatchedTerm) {

	int ZEPHIR_LAST_CALL_STATUS;
	long arg1, arg2;
	zval *value_param = NULL, *cmd, *_0 = NULL, *_1, *_2, *_3;
	zend_bool value;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &value_param);

	if (!value_param) {
		value = 1;
	} else {
		value = zephir_get_boolval(value_param);
	}


	arg1 = 2;
	ZEPHIR_INIT_VAR(_0);
	if (value) {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, 1);
	} else {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, 0);
	}
	arg2 = zephir_get_numberval(_0);
	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 200);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, arg1);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, arg2);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _1, _2, _3);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd);
	zephir_check_call_status();
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, setAutoSynonyms) {

	int ZEPHIR_LAST_CALL_STATUS;
	long flag;
	zval *value_param = NULL, *cmd, *_0;
	zend_bool value;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &value_param);

	if (!value_param) {
		value = 1;
	} else {
		value = zephir_get_boolval(value_param);
	}


	flag = ((1 | 2) | 4);
	if (value) {
		flag = (flag | 1536);
	}
	ZEPHIR_INIT_VAR(cmd);
	zephir_create_array(cmd, 2, 0 TSRMLS_CC);
	add_assoc_long_ex(cmd, SS("cmd"), 231);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, flag);
	zephir_array_update_string(&cmd, SL("arg"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd);
	zephir_check_call_status();
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, setSynonymScale) {

	int ZEPHIR_LAST_CALL_STATUS;
	long arg1, arg2;
	zval *value_param = NULL, *cmd, *_0 = NULL, *_1 = NULL, *_2 = NULL, *_3;
	double value;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

	value = zephir_get_doubleval(value_param);


	arg1 = 1;
	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 0);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, ((long) ((value * (double) 100)) & 255));
	ZEPHIR_CALL_FUNCTION(&_2, "max", NULL, 26, _0, _1);
	zephir_check_call_status();
	arg2 = zephir_get_intval(_2);
	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 200);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_LONG(_1, arg1);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, arg2);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _0, _1, _3);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd);
	zephir_check_call_status();
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, getAllSynonyms) {

	zephir_fcall_cache_entry *_12 = NULL;
	HashTable *_10;
	HashPosition _9;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *page = NULL, *_4 = NULL;
	zend_bool stemmed;
	zval *limit_param = NULL, *offset_param = NULL, *stemmed_param = NULL, *cmd, *res = NULL, *ret, *line = NULL, *value = NULL, *key = NULL, _0, _1, _2, *_3 = NULL, *_5 = NULL, *_6 = NULL, *_7, *_8, **_11;
	long limit, offset;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 3, &limit_param, &offset_param, &stemmed_param);

	if (!limit_param) {
		limit = 0;
	} else {
		limit = zephir_get_intval(limit_param);
	}
	if (!offset_param) {
		offset = 0;
	} else {
		offset = zephir_get_intval(offset_param);
	}
	if (!stemmed_param) {
		stemmed = 0;
	} else {
		stemmed = zephir_get_boolval(stemmed_param);
	}


	if (limit > 0) {
		ZEPHIR_SINIT_VAR(_0);
		ZVAL_STRING(&_0, "II", 0);
		ZEPHIR_SINIT_VAR(_1);
		ZVAL_LONG(&_1, offset);
		ZEPHIR_SINIT_VAR(_2);
		ZVAL_LONG(&_2, limit);
		ZEPHIR_CALL_FUNCTION(&_3, "pack", NULL, 2, &_0, &_1, &_2);
		zephir_check_call_status();
		zephir_get_strval(_4, _3);
		ZEPHIR_CPY_WRT(page, _4);
	} else {
		ZEPHIR_INIT_NVAR(page);
		ZVAL_EMPTY_STRING(page);
	}
	ZEPHIR_INIT_VAR(cmd);
	zephir_create_array(cmd, 2, 0 TSRMLS_CC);
	add_assoc_long_ex(cmd, SS("cmd"), 72);
	zephir_array_update_string(&cmd, SL("buf1"), &page, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(_5);
	if (stemmed) {
		ZEPHIR_INIT_NVAR(_5);
		ZVAL_LONG(_5, 1);
	} else {
		ZEPHIR_INIT_NVAR(_5);
		ZVAL_LONG(_5, 0);
	}
	zephir_array_update_string(&cmd, SL("arg1"), &_5, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(_6);
	ZVAL_LONG(_6, 280);
	ZEPHIR_CALL_METHOD(&res, this_ptr, "execcommand", NULL, 0, cmd, _6);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(ret);
	array_init(ret);
	ZEPHIR_OBS_VAR(_7);
	zephir_read_property(&_7, res, SL("buf"), PH_NOISY_CC);
	if (!(ZEPHIR_IS_EMPTY(_7))) {
		ZEPHIR_INIT_NVAR(_6);
		ZEPHIR_OBS_VAR(_8);
		zephir_read_property(&_8, res, SL("buf"), PH_NOISY_CC);
		zephir_fast_explode_str(_6, SL("\n"), _8, LONG_MAX TSRMLS_CC);
		zephir_is_iterable(_6, &_10, &_9, 0, 0, "xs/search.zep", 125);
		for (
		  ; zephir_hash_get_current_data_ex(_10, (void**) &_11, &_9) == SUCCESS
		  ; zephir_hash_move_forward_ex(_10, &_9)
		) {
			ZEPHIR_GET_HVALUE(line, _11);
			ZEPHIR_INIT_NVAR(value);
			zephir_fast_explode_str(value, SL("\t"), line, LONG_MAX TSRMLS_CC);
			Z_SET_ISREF_P(value);
			ZEPHIR_CALL_FUNCTION(&key, "array_shift", &_12, 27, value);
			Z_UNSET_ISREF_P(value);
			zephir_check_call_status();
			zephir_array_update_zval(&ret, key, &value, PH_COPY | PH_SEPARATE);
		}
	}
	RETURN_CCTOR(ret);

}

PHP_METHOD(Xs_Search, getSynonyms) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *term_param = NULL, *cmd, *res = NULL, *_0 = NULL, *_1, *_2, *_3;
	zval *term = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &term_param);

	zephir_get_strval(term, term_param);


	if (zephir_fast_strlen_ev(term) < 1) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_VAR(cmd);
	zephir_create_array(cmd, 3, 0 TSRMLS_CC);
	add_assoc_long_ex(cmd, SS("cmd"), 72);
	add_assoc_long_ex(cmd, SS("arg1"), 2);
	zephir_array_update_string(&cmd, SL("buf"), &term, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 280);
	ZEPHIR_CALL_METHOD(&res, this_ptr, "execcommand", NULL, 0, cmd, _1);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_2);
	zephir_read_property(&_2, res, SL("buf"), PH_NOISY_CC);
	if (ZEPHIR_IS_STRING_IDENTICAL(_2, "")) {
		array_init(return_value);
		RETURN_MM();
	}
	ZEPHIR_OBS_VAR(_3);
	zephir_read_property(&_3, res, SL("buf"), PH_NOISY_CC);
	zephir_fast_explode_str(return_value, SL("\n"), _3, LONG_MAX TSRMLS_CC);
	RETURN_MM();

}

PHP_METHOD(Xs_Search, getQuery) {

	zend_bool _10;
	zephir_fcall_cache_entry *_8 = NULL, *_16 = NULL;
	zval *_6 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *regex = NULL;
	zval *query = NULL, *cmd, *res = NULL, *_0 = NULL, *_1, *_2 = NULL, *_3 = NULL, *_4, _5, *_7 = NULL, _9, *_11, _12, *_13, *_14 = NULL, *_15, *_17;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &query);

	if (!query) {
		ZEPHIR_CPY_WRT(query, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(query);
	}


	if (Z_TYPE_P(query) == IS_NULL) {
		ZEPHIR_INIT_NVAR(query);
		ZVAL_STRING(query, "", 1);
	} else {
		ZEPHIR_CALL_METHOD(&_0, this_ptr, "prequerystring", NULL, 28, query);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(query, _0);
	}
	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("defaultOp"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, 96);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 0);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _2, _3, _1, query);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_2);
	ZVAL_LONG(_2, 202);
	ZEPHIR_CALL_METHOD(&res, this_ptr, "execcommand", NULL, 0, cmd, _2);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_4);
	zephir_read_property(&_4, res, SL("buf"), PH_NOISY_CC);
	ZEPHIR_SINIT_VAR(_5);
	ZVAL_STRING(&_5, "VALUE_RANGE", 0);
	ZEPHIR_INIT_NVAR(_2);
	zephir_fast_strpos(_2, _4, &_5, 0 );
	if (!ZEPHIR_IS_FALSE_IDENTICAL(_2)) {
		ZEPHIR_INIT_VAR(regex);
		ZVAL_STRING(regex, "/(VALUE_RANGE) (\\d+) (\\S+) (.+?)(?=\\))/", 1);
		ZEPHIR_INIT_VAR(_6);
		zephir_create_array(_6, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(_6, this_ptr);
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "formatValueRange", 1);
		zephir_array_fast_append(_6, _3);
		ZEPHIR_OBS_VAR(_7);
		zephir_read_property(&_7, res, SL("buf"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&_0, "preg_replace_callback", &_8, 29, regex, _6, _7);
		zephir_check_call_status();
		zephir_update_property_zval(res, SL("buf"), _0 TSRMLS_CC);
	}
	ZEPHIR_OBS_NVAR(_7);
	zephir_read_property(&_7, res, SL("buf"), PH_NOISY_CC);
	ZEPHIR_SINIT_VAR(_9);
	ZVAL_STRING(&_9, "VALUE_GE", 0);
	ZEPHIR_INIT_NVAR(_3);
	zephir_fast_strpos(_3, _7, &_9, 0 );
	_10 = !ZEPHIR_IS_FALSE_IDENTICAL(_3);
	if (!(_10)) {
		ZEPHIR_OBS_VAR(_11);
		zephir_read_property(&_11, res, SL("buf"), PH_NOISY_CC);
		ZEPHIR_SINIT_VAR(_12);
		ZVAL_STRING(&_12, "VALUE_LE", 0);
		ZEPHIR_INIT_VAR(_13);
		zephir_fast_strpos(_13, _11, &_12, 0 );
		_10 = !ZEPHIR_IS_FALSE_IDENTICAL(_13);
	}
	if (_10) {
		ZEPHIR_INIT_NVAR(regex);
		ZVAL_STRING(regex, "/(VALUE_[GL]E) (\\d+) (.+?)(?=\\))/", 1);
		ZEPHIR_INIT_NVAR(_6);
		zephir_create_array(_6, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(_6, this_ptr);
		ZEPHIR_INIT_VAR(_14);
		ZVAL_STRING(_14, "formatValueRange", 1);
		zephir_array_fast_append(_6, _14);
		ZEPHIR_OBS_VAR(_15);
		zephir_read_property(&_15, res, SL("buf"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&_0, "preg_replace_callback", &_8, 29, regex, _6, _15);
		zephir_check_call_status();
		zephir_update_property_zval(res, SL("buf"), _0 TSRMLS_CC);
	}
	ZEPHIR_OBS_NVAR(_7);
	zephir_read_property(&_7, res, SL("buf"), PH_NOISY_CC);
	_17 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
	ZEPHIR_INIT_NVAR(_14);
	ZVAL_STRING(_14, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_RETURN_CALL_CE_STATIC(xs_xs_ce, "convert", &_16, 7, _7, _17, _14);
	zephir_check_temp_parameter(_14);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Xs_Search, setQuery) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *query;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &query);



	ZEPHIR_CALL_METHOD(NULL, this_ptr, "clearquery", NULL, 30);
	zephir_check_call_status();
	if (Z_TYPE_P(query) != IS_NULL) {
		zephir_update_property_this(this_ptr, SL("query"), query TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "addquerystring", NULL, 0, query);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, setMultiSort) {

	zephir_fcall_cache_entry *_8 = NULL;
	HashTable *_2;
	HashPosition _1;
	int ZEPHIR_LAST_CALL_STATUS;
	long vno, type;
	zval *buf;
	zend_bool reversed, relevanceFirst, asc;
	zval *fields, *reversed_param = NULL, *relevanceFirst_param = NULL, *key = NULL, *value = NULL, *cmd, *_0 = NULL, **_3, *_4, *_5 = NULL, *_6 = NULL, _7 = zval_used_for_init, *_9 = NULL, *_10 = NULL, *_11 = NULL, *_12, *_13;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &fields, &reversed_param, &relevanceFirst_param);

	if (!reversed_param) {
		reversed = 0;
	} else {
		reversed = zephir_get_boolval(reversed_param);
	}
	if (!relevanceFirst_param) {
		relevanceFirst = 0;
	} else {
		relevanceFirst = zephir_get_boolval(relevanceFirst_param);
	}


	if (Z_TYPE_P(fields) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(_0);
		ZVAL_BOOL(_0, !reversed);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "setsort", NULL, 0, fields, _0, (relevanceFirst ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(buf);
	ZVAL_EMPTY_STRING(buf);
	zephir_is_iterable(fields, &_2, &_1, 0, 0, "xs/search.zep", 201);
	for (
	  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HMKEY(key, _2, _1);
		ZEPHIR_GET_HVALUE(value, _3);
		if (Z_TYPE_P(value) == IS_BOOL) {
			_4 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(_0);
			ZVAL_BOOL(_0, 1);
			ZEPHIR_CALL_METHOD(&_5, _4, "getfield", NULL, 0, key, _0);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(_6);
			zephir_read_property(&_6, _5, SL("vno"), PH_NOISY_CC);
			vno = zephir_get_numberval(_6);
			asc = zephir_is_true(value);
		} else {
			_4 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(_0);
			ZVAL_BOOL(_0, 1);
			ZEPHIR_CALL_METHOD(&_5, _4, "getfield", NULL, 0, value, _0);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(_6);
			zephir_read_property(&_6, _5, SL("vno"), PH_NOISY_CC);
			vno = zephir_get_numberval(_6);
			asc = 0;
		}
		if (vno != 255) {
			ZEPHIR_SINIT_NVAR(_7);
			ZVAL_LONG(&_7, vno);
			ZEPHIR_CALL_FUNCTION(&_5, "chr", &_8, 31, &_7);
			zephir_check_call_status();
			ZEPHIR_INIT_LNVAR(_9);
			if (asc) {
				ZEPHIR_INIT_NVAR(_9);
				ZVAL_LONG(_9, 1);
			} else {
				ZEPHIR_INIT_NVAR(_9);
				ZVAL_LONG(_9, 0);
			}
			ZEPHIR_CALL_FUNCTION(&_10, "chr", &_8, 31, _9);
			zephir_check_call_status();
			ZEPHIR_INIT_LNVAR(_11);
			ZEPHIR_CONCAT_VV(_11, _5, _10);
			zephir_concat_self(&buf, _11 TSRMLS_CC);
		}
	}
	if (!ZEPHIR_IS_STRING_IDENTICAL(buf, "")) {
		type = 3;
		if (relevanceFirst) {
			type = (type | 0x40);
		}
		if (!(reversed)) {
			type = (type | 0x80);
		}
		ZEPHIR_INIT_VAR(cmd);
		object_init_ex(cmd, xs_command_ce);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, 192);
		ZEPHIR_INIT_VAR(_12);
		ZVAL_LONG(_12, type);
		ZEPHIR_INIT_VAR(_13);
		ZVAL_LONG(_13, 0);
		ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _0, _12, _13, buf);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, setSort) {

	zephir_fcall_cache_entry *_2 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	long type, vno;
	zend_bool asc, relevanceFirst;
	zval *field, *asc_param = NULL, *relevanceFirst_param = NULL, *cmd, *_0 = NULL, *_1 = NULL, *_3, *_4 = NULL, *_5, *_6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &field, &asc_param, &relevanceFirst_param);

	if (!asc_param) {
		asc = 0;
	} else {
		asc = zephir_get_boolval(asc_param);
	}
	if (!relevanceFirst_param) {
		relevanceFirst = 0;
	} else {
		relevanceFirst = zephir_get_boolval(relevanceFirst_param);
	}


	if (Z_TYPE_P(field) == IS_ARRAY) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "setmultisort", NULL, 0, field, (asc ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)), (relevanceFirst ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(cmd);
	if (Z_TYPE_P(field) == IS_NULL) {
		object_init_ex(cmd, xs_command_ce);
		ZEPHIR_INIT_VAR(_0);
		ZVAL_LONG(_0, 192);
		ZEPHIR_INIT_VAR(_1);
		ZVAL_LONG(_1, 0);
		ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", &_2, 19, _0, _1);
		zephir_check_call_status();
	} else {
		type = 2;
		if (relevanceFirst) {
			type = (type | 0x40);
		}
		if (asc) {
			type = (type | 0x80);
		}
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_BOOL(_0, 1);
		ZEPHIR_CALL_METHOD(&_4, _3, "getfield", NULL, 0, field, _0);
		zephir_check_call_status();
		ZEPHIR_OBS_VAR(_5);
		zephir_read_property(&_5, _4, SL("vno"), PH_NOISY_CC);
		vno = zephir_get_numberval(_5);
		object_init_ex(cmd, xs_command_ce);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, 192);
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_LONG(_1, type);
		ZEPHIR_INIT_VAR(_6);
		ZVAL_LONG(_6, vno);
		ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", &_2, 19, _0, _1, _6);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd);
	zephir_check_call_status();
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, setDocOrder) {

	int ZEPHIR_LAST_CALL_STATUS;
	long type;
	zval *asc_param = NULL, *cmd, *_0, *_1;
	zend_bool asc;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &asc_param);

	if (!asc_param) {
		asc = 0;
	} else {
		asc = zephir_get_boolval(asc_param);
	}


	if (asc) {
		type = (1 | 0x80);
	} else {
		type = 1;
	}
	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 192);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, type);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _0, _1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd);
	zephir_check_call_status();
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, setCollapse) {

	int ZEPHIR_LAST_CALL_STATUS;
	long num, vno, max;
	zval *field, *num_param = NULL, *cmd, *_0, *_1 = NULL, *_2 = NULL, *_3, *_4 = NULL, *_5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &field, &num_param);

	if (!num_param) {
		num = 1;
	} else {
		num = zephir_get_intval(num_param);
	}


	if (Z_TYPE_P(field) == IS_NULL) {
		vno = 255;
	} else {
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_2);
		ZVAL_BOOL(_2, 1);
		ZEPHIR_CALL_METHOD(&_1, _0, "getfield", NULL, 0, field, _2);
		zephir_check_call_status();
		ZEPHIR_OBS_VAR(_3);
		zephir_read_property(&_3, _1, SL("vno"), PH_NOISY_CC);
		vno = zephir_get_numberval(_3);
	}
	ZEPHIR_INIT_NVAR(_2);
	ZVAL_LONG(_2, 255);
	ZEPHIR_INIT_VAR(_4);
	ZVAL_LONG(_4, num);
	ZEPHIR_CALL_FUNCTION(&_1, "min", NULL, 25, _2, _4);
	zephir_check_call_status();
	max = zephir_get_intval(_1);
	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	ZEPHIR_INIT_NVAR(_2);
	ZVAL_LONG(_2, 195);
	ZEPHIR_INIT_NVAR(_4);
	ZVAL_LONG(_4, max);
	ZEPHIR_INIT_VAR(_5);
	ZVAL_LONG(_5, vno);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _2, _4, _5);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd);
	zephir_check_call_status();
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, addRange) {

	zephir_fcall_cache_entry *_8 = NULL, *_13 = NULL, *_16 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _0, _1, _2, _3;
	long vno;
	zval *field, *from = NULL, *to = NULL, *cmd = NULL, *_4, *_5 = NULL, *_6, *_7 = NULL, *_9, *_10 = NULL, *_11, _12 = zval_used_for_init, *_14 = NULL, *_15 = NULL, *_17 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &field, &from, &to);

	ZEPHIR_SEPARATE_PARAM(from);
	ZEPHIR_SEPARATE_PARAM(to);


	_0 = ZEPHIR_IS_STRING_IDENTICAL(from, "");
	if (!(_0)) {
		_0 = ZEPHIR_IS_FALSE_IDENTICAL(from);
	}
	if (_0) {
		ZEPHIR_INIT_NVAR(from);
		ZVAL_NULL(from);
	}
	_1 = ZEPHIR_IS_STRING_IDENTICAL(to, "");
	if (!(_1)) {
		_1 = ZEPHIR_IS_FALSE_IDENTICAL(to);
	}
	if (_1) {
		ZEPHIR_INIT_NVAR(to);
		ZVAL_NULL(to);
	}
	_2 = Z_TYPE_P(from) != IS_NULL;
	if (!(_2)) {
		_2 = Z_TYPE_P(to) != IS_NULL;
	}
	if (_2) {
		_3 = zephir_fast_strlen_ev(from) > 255;
		if (!(_3)) {
			_3 = zephir_fast_strlen_ev(to) > 255;
		}
		if (_3) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(xs_exception_ce, "Value of range is too long", "xs/search.zep", 284);
			return;
		}
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&_5, _4, "getfield", NULL, 0, field);
		zephir_check_call_status();
		ZEPHIR_OBS_VAR(_6);
		zephir_read_property(&_6, _5, SL("vno"), PH_NOISY_CC);
		vno = zephir_get_numberval(_6);
		_9 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_10);
		ZVAL_STRING(_10, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_7, xs_xs_ce, "convert", &_8, 7, from, _10, _9);
		zephir_check_temp_parameter(_10);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(from, _7);
		_11 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_10);
		ZVAL_STRING(_10, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_7, xs_xs_ce, "convert", &_8, 7, to, _10, _11);
		zephir_check_temp_parameter(_10);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(to, _7);
		if (Z_TYPE_P(from) == IS_NULL) {
			ZEPHIR_INIT_VAR(cmd);
			object_init_ex(cmd, xs_command_ce);
			ZEPHIR_SINIT_VAR(_12);
			ZVAL_LONG(&_12, 0);
			ZEPHIR_CALL_FUNCTION(&_7, "chr", &_13, 31, &_12);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(_10);
			ZVAL_LONG(_10, 229);
			ZEPHIR_INIT_VAR(_14);
			ZVAL_LONG(_14, 5);
			ZEPHIR_INIT_VAR(_15);
			ZVAL_LONG(_15, vno);
			ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", &_16, 19, _10, _14, _15, to, _7);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(cmd);
			if (Z_TYPE_P(to) == IS_NULL) {
				object_init_ex(cmd, xs_command_ce);
				ZEPHIR_SINIT_NVAR(_12);
				ZVAL_LONG(&_12, 1);
				ZEPHIR_CALL_FUNCTION(&_17, "chr", &_13, 31, &_12);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(_10);
				ZVAL_LONG(_10, 229);
				ZEPHIR_INIT_NVAR(_14);
				ZVAL_LONG(_14, 5);
				ZEPHIR_INIT_NVAR(_15);
				ZVAL_LONG(_15, vno);
				ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", &_16, 19, _10, _14, _15, from, _17);
				zephir_check_call_status();
			} else {
				object_init_ex(cmd, xs_command_ce);
				ZEPHIR_INIT_NVAR(_10);
				ZVAL_LONG(_10, 228);
				ZEPHIR_INIT_NVAR(_14);
				ZVAL_LONG(_14, 5);
				ZEPHIR_INIT_NVAR(_15);
				ZVAL_LONG(_15, vno);
				ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", &_16, 19, _10, _14, _15, from, to);
				zephir_check_call_status();
			}
		}
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, addWeight) {

	int ZEPHIR_LAST_CALL_STATUS;
	long weight;
	zval *term = NULL;
	zval *field, *term_param = NULL, *weight_param = NULL, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &field, &term_param, &weight_param);

	zephir_get_strval(term, term_param);
	if (!weight_param) {
		weight = 1;
	} else {
		weight = zephir_get_intval(weight_param);
	}


	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 4);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, weight);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addqueryterm", NULL, 0, field, term, _0, _1);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Xs_Search, setFacets) {

	zephir_fcall_cache_entry *_7 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_1;
	HashPosition _0;
	zval *buf;
	zend_bool exact;
	zval *field = NULL, *exact_param = NULL, *fields = NULL, *ff = NULL, *cmd, **_2, *_3, *_4 = NULL, *_5 = NULL, *_6 = NULL, *_8 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &field, &exact_param);

	ZEPHIR_SEPARATE_PARAM(field);
	if (!exact_param) {
		exact = 0;
	} else {
		exact = zephir_get_boolval(exact_param);
	}
	ZEPHIR_INIT_VAR(buf);
	ZVAL_STRING(buf, "", 1);


	if (Z_TYPE_P(field) == IS_ARRAY) {
		ZEPHIR_CPY_WRT(fields, field);
	} else {
		ZEPHIR_INIT_NVAR(fields);
		zephir_create_array(fields, 1, 0 TSRMLS_CC);
		zephir_array_fast_append(fields, field);
	}
	zephir_is_iterable(fields, &_1, &_0, 0, 0, "xs/search.zep", 327);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(field, _2);
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&ff, _3, "getfield", NULL, 0, field);
		zephir_check_call_status();
		ZEPHIR_OBS_NVAR(_4);
		zephir_read_property(&_4, ff, SL("type"), PH_NOISY_CC);
		if (!ZEPHIR_IS_LONG_IDENTICAL(_4, 0)) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(xs_exception_ce, "Field `name` cannot be used for facets search, can only be string type", "xs/search.zep", 323);
			return;
		}
		ZEPHIR_OBS_NVAR(_5);
		zephir_read_property(&_5, ff, SL("vno"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&_6, "chr", &_7, 31, _5);
		zephir_check_call_status();
		zephir_concat_self(&buf, _6 TSRMLS_CC);
	}
	ZEPHIR_INIT_VAR(cmd);
	zephir_create_array(cmd, 2, 0 TSRMLS_CC);
	add_assoc_long_ex(cmd, SS("cmd"), 197);
	zephir_array_update_string(&cmd, SL("buf"), &buf, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(_8);
	if (exact) {
		ZEPHIR_INIT_NVAR(_8);
		ZVAL_LONG(_8, 1);
	} else {
		ZEPHIR_INIT_NVAR(_8);
		ZVAL_LONG(_8, 0);
	}
	zephir_array_update_string(&cmd, SL("arg1"), &_8, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd);
	zephir_check_call_status();
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, getFacets) {

	zval *field = NULL, *f, *_0;

	zephir_fetch_params(0, 0, 1, &field);

	if (!field) {
		field = ZEPHIR_GLOBAL(global_null);
	}


	if (Z_TYPE_P(field) == IS_NULL) {
		RETURN_MEMBER(this_ptr, "facets");
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("facets"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&f, _0, field, 1 TSRMLS_CC)) {
		RETURN_CTORW(f);
	}
	array_init(return_value);
	return;

}

PHP_METHOD(Xs_Search, setScwsMulti) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _0;
	zval *level_param = NULL, *cmd, *_1;
	long level;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &level_param);

	level = zephir_get_intval(level_param);


	_0 = level >= 0;
	if (_0) {
		_0 = level < 16;
	}
	if (_0) {
		ZEPHIR_INIT_VAR(cmd);
		zephir_create_array(cmd, 3, 0 TSRMLS_CC);
		add_assoc_long_ex(cmd, SS("cmd"), 198);
		add_assoc_long_ex(cmd, SS("arg1"), 51);
		ZEPHIR_INIT_VAR(_1);
		ZVAL_LONG(_1, level);
		zephir_array_update_string(&cmd, SL("arg2"), &_1, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, setLimit) {

	zval *limit_param = NULL, *offset_param = NULL, *_0;
	long limit, offset;

	zephir_fetch_params(0, 1, 1, &limit_param, &offset_param);

	limit = zephir_get_intval(limit_param);
	if (!offset_param) {
		offset = 0;
	} else {
		offset = zephir_get_intval(offset_param);
	}


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, limit);
	zephir_update_property_this(this_ptr, SL("limit"), _0 TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, offset);
	zephir_update_property_this(this_ptr, SL("offset"), _0 TSRMLS_CC);
	RETURN_THISW();

}

PHP_METHOD(Xs_Search, setDb) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;
	zval *name_param = NULL, *_1, *_2, *_3;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(_0);
	zephir_create_array(_0, 2, 0 TSRMLS_CC);
	add_assoc_long_ex(_0, SS("cmd"), 32);
	zephir_array_update_string(&_0, SL("buf"), &name, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, _0);
	zephir_check_call_status();
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("curDb"), PH_NOISY_CC);
	zephir_update_property_this(this_ptr, SL("lastDb"), _1 TSRMLS_CC);
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("curDbs"), PH_NOISY_CC);
	zephir_update_property_this(this_ptr, SL("lastDbs"), _2 TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("curDb"), name TSRMLS_CC);
	ZEPHIR_INIT_VAR(_3);
	array_init(_3);
	zephir_update_property_this(this_ptr, SL("curDbs"), _3 TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, addDb) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;
	zval *name_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(_0);
	zephir_create_array(_0, 2, 0 TSRMLS_CC);
	add_assoc_long_ex(_0, SS("cmd"), 68);
	zephir_array_update_string(&_0, SL("buf"), &name, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, _0);
	zephir_check_call_status();
	zephir_update_property_array_append(this_ptr, SL("curDbs"), name TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, markResetScheme) {


	zephir_update_property_this(this_ptr, SL("resetScheme"), (1) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);

}

PHP_METHOD(Xs_Search, terms) {

	zephir_fcall_cache_entry *_12 = NULL;
	HashTable *_8;
	HashPosition _7;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool convert, _1, _10;
	zval *query = NULL, *convert_param = NULL, *ret = NULL, *cmd, *res = NULL, *tmps, *tmp = NULL, *_0 = NULL, *_2, *_3, *_4 = NULL, *_5, *_6, **_9, _11 = zval_used_for_init;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &query, &convert_param);

	if (!query) {
		ZEPHIR_CPY_WRT(query, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(query);
	}
	if (!convert_param) {
		convert = 1;
	} else {
		convert = zephir_get_boolval(convert_param);
	}


	if (Z_TYPE_P(query) == IS_NULL) {
		ZEPHIR_INIT_NVAR(query);
		ZVAL_STRING(query, "", 1);
	} else {
		ZEPHIR_CALL_METHOD(&_0, this_ptr, "prequerystring", NULL, 28, query);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(query, _0);
	}
	_1 = ZEPHIR_IS_STRING_IDENTICAL(query, "");
	if (_1) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("terms"), PH_NOISY_CC);
		_1 = Z_TYPE_P(_2) != IS_NULL;
	}
	if (_1) {
		ZEPHIR_OBS_VAR(ret);
		zephir_read_property_this(&ret, this_ptr, SL("terms"), PH_NOISY_CC);
	} else {
		ZEPHIR_INIT_VAR(cmd);
		object_init_ex(cmd, xs_command_ce);
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("defaultOp"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_4);
		ZVAL_LONG(_4, 97);
		ZEPHIR_INIT_VAR(_5);
		ZVAL_LONG(_5, 0);
		ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _4, _5, _3, query);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_LONG(_4, 204);
		ZEPHIR_CALL_METHOD(&res, this_ptr, "execcommand", NULL, 0, cmd, _4);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(ret);
		array_init(ret);
		ZEPHIR_OBS_VAR(_6);
		zephir_read_property(&_6, res, SL("buf"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(tmps);
		zephir_fast_explode_str(tmps, SL(" "), _6, LONG_MAX TSRMLS_CC);
		zephir_is_iterable(tmps, &_8, &_7, 0, 0, "xs/search.zep", 408);
		for (
		  ; zephir_hash_get_current_data_ex(_8, (void**) &_9, &_7) == SUCCESS
		  ; zephir_hash_move_forward_ex(_8, &_7)
		) {
			ZEPHIR_GET_HVALUE(tmp, _9);
			_10 = ZEPHIR_IS_STRING_IDENTICAL(tmp, "");
			if (!(_10)) {
				ZEPHIR_SINIT_NVAR(_11);
				ZVAL_STRING(&_11, ":", 0);
				ZEPHIR_INIT_NVAR(_4);
				zephir_fast_strpos(_4, tmp, &_11, 0 );
				_10 = !ZEPHIR_IS_FALSE_IDENTICAL(_4);
			}
			if (_10) {
				continue;
			}
			zephir_array_append(&ret, tmp, PH_SEPARATE, "xs/search.zep", 406);
		}
		if (ZEPHIR_IS_STRING_IDENTICAL(query, "")) {
			zephir_update_property_this(this_ptr, SL("terms"), ret TSRMLS_CC);
		}
	}
	if (convert) {
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_STRING(_4, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_CE_STATIC(xs_xs_ce, "convert", &_12, 7, ret, _3, _4);
		zephir_check_temp_parameter(_4);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_CCTOR(ret);

}

PHP_METHOD(Xs_Search, count) {

	zend_bool _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *query = NULL, *cmd, *res = NULL, *ret = NULL, *_0 = NULL, *_2, *_3, *_4 = NULL, *_5, *_6, _7, *_8;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &query);

	if (!query) {
		ZEPHIR_CPY_WRT(query, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(query);
	}


	if (Z_TYPE_P(query) == IS_NULL) {
		ZEPHIR_INIT_NVAR(query);
		ZVAL_STRING(query, "", 1);
	} else {
		ZEPHIR_CALL_METHOD(&_0, this_ptr, "prequerystring", NULL, 28, query);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(query, _0);
	}
	_1 = ZEPHIR_IS_STRING_IDENTICAL(query, "");
	if (_1) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("count"), PH_NOISY_CC);
		_1 = Z_TYPE_P(_2) != IS_NULL;
	}
	if (_1) {
		RETURN_MM_MEMBER(this_ptr, "count");
	}
	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("defaultOp"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_4);
	ZVAL_LONG(_4, 65);
	ZEPHIR_INIT_VAR(_5);
	ZVAL_LONG(_5, 0);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _4, _5, _3, query);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_4);
	ZVAL_LONG(_4, 206);
	ZEPHIR_CALL_METHOD(&res, this_ptr, "execcommand", NULL, 0, cmd, _4);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_6);
	zephir_read_property(&_6, res, SL("buf"), PH_NOISY_CC);
	ZEPHIR_SINIT_VAR(_7);
	ZVAL_STRING(&_7, "Icount", 0);
	ZEPHIR_CALL_FUNCTION(&ret, "unpack", NULL, 5, &_7, _6);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING_IDENTICAL(query, "")) {
		zephir_array_fetch_string(&_8, ret, SL("count"), PH_NOISY | PH_READONLY, "xs/search.zep", 434 TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("count"), _8 TSRMLS_CC);
	}
	zephir_array_fetch_string(&_8, ret, SL("count"), PH_NOISY | PH_READONLY, "xs/search.zep", 436 TSRMLS_CC);
	RETURN_CTOR(_8);

}

PHP_METHOD(Xs_Search, search) {

	zephir_fcall_cache_entry *_12 = NULL, *_16 = NULL, *_27 = NULL, *_28 = NULL, *_29 = NULL, *_35 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	long off;
	zval *page = NULL, *value = NULL, *_7 = NULL;
	zend_bool saveHighlight, endLoop = 0, _1;
	zval *query = NULL, *saveHighlight_param = NULL, *cmd, *res = NULL, *tmp = NULL, *ret, *vnoes = NULL, *name = NULL, *doc = NULL, *_0, *_2 = NULL, *_3, *_4 = NULL, *_5, _6 = zval_used_for_init, *_8, *_9 = NULL, *_10 = NULL, *_11, *_13, *_14, *_15 = NULL, *_17 = NULL, *_18 = NULL, *_19 = NULL, _20 = zval_used_for_init, _21 = zval_used_for_init, *_22, *_23 = NULL, *_24, *_25, *_26, *_30 = NULL, *_31 = NULL, *_32 = NULL, *_33 = NULL, *_34 = NULL, *_36;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &query, &saveHighlight_param);

	if (!query) {
		ZEPHIR_CPY_WRT(query, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(query);
	}
	if (!saveHighlight_param) {
		saveHighlight = 1;
	} else {
		saveHighlight = zephir_get_boolval(saveHighlight_param);
	}
	ZEPHIR_INIT_VAR(doc);
	ZVAL_NULL(doc);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("curDb"), PH_NOISY_CC);
	_1 = !ZEPHIR_IS_STRING_IDENTICAL(_0, "log_db");
	if (_1) {
		_1 = saveHighlight;
	}
	if (_1) {
		zephir_update_property_this(this_ptr, SL("highlight"), query TSRMLS_CC);
	}
	if (Z_TYPE_P(query) == IS_NULL) {
		ZEPHIR_INIT_NVAR(query);
		ZVAL_STRING(query, "", 1);
	} else {
		ZEPHIR_CALL_METHOD(&_2, this_ptr, "prequerystring", NULL, 28, query);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(query, _2);
	}
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("offset"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_4);
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("limit"), PH_NOISY_CC);
	if (ZEPHIR_GT_LONG(_5, 0)) {
		ZEPHIR_OBS_NVAR(_4);
		zephir_read_property_this(&_4, this_ptr, SL("limit"), PH_NOISY_CC);
	} else {
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_LONG(_4, 10);
	}
	ZEPHIR_SINIT_VAR(_6);
	ZVAL_STRING(&_6, "II", 0);
	ZEPHIR_CALL_FUNCTION(&_2, "pack", NULL, 2, &_6, _3, _4);
	zephir_check_call_status();
	zephir_get_strval(_7, _2);
	ZEPHIR_CPY_WRT(page, _7);
	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	_8 = zephir_fetch_nproperty_this(this_ptr, SL("defaultOp"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_9);
	ZVAL_LONG(_9, 66);
	ZEPHIR_INIT_VAR(_10);
	ZVAL_LONG(_10, 0);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _9, _10, _8, query, page);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_9);
	ZVAL_LONG(_9, 206);
	ZEPHIR_CALL_METHOD(&res, this_ptr, "execcommand", NULL, 0, cmd, _9);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_11);
	zephir_read_property(&_11, res, SL("buf"), PH_NOISY_CC);
	ZEPHIR_SINIT_NVAR(_6);
	ZVAL_STRING(&_6, "Icount", 0);
	ZEPHIR_CALL_FUNCTION(&tmp, "unpack", &_12, 5, &_6, _11);
	zephir_check_call_status();
	zephir_array_fetch_string(&_13, tmp, SL("count"), PH_NOISY | PH_READONLY, "xs/search.zep", 458 TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("lastCount"), _13 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(_9);
	array_init(_9);
	zephir_update_property_this(this_ptr, SL("facets"), _9 TSRMLS_CC);
	ZEPHIR_INIT_VAR(ret);
	array_init(ret);
	_14 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_15, _14, "getscheme", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&vnoes, _15, "getvnomap", NULL, 0);
	zephir_check_call_status();
	while (1) {
		ZEPHIR_CALL_METHOD(&res, this_ptr, "getrespond", &_16, 0);
		zephir_check_call_status();
		ZEPHIR_OBS_NVAR(_17);
		zephir_read_property(&_17, res, SL("cmd"), PH_NOISY_CC);
		do {
			if (ZEPHIR_IS_LONG(_17, 142)) {
				off = 0;
				while (1) {
					ZEPHIR_OBS_NVAR(_18);
					zephir_read_property(&_18, res, SL("buf"), PH_NOISY_CC);
					if (!((off + 6) < zephir_fast_strlen_ev(_18))) {
						break;
					}
					ZEPHIR_OBS_NVAR(_19);
					zephir_read_property(&_19, res, SL("buf"), PH_NOISY_CC);
					ZEPHIR_SINIT_NVAR(_6);
					ZVAL_LONG(&_6, off);
					ZEPHIR_SINIT_NVAR(_20);
					ZVAL_LONG(&_20, 6);
					ZEPHIR_INIT_NVAR(_10);
					zephir_substr(_10, _19, zephir_get_intval(&_6), 6 , 0);
					ZEPHIR_SINIT_NVAR(_21);
					ZVAL_STRING(&_21, "Cvno/Cvlen/Inum", 0);
					ZEPHIR_CALL_FUNCTION(&tmp, "unpack", &_12, 5, &_21, _10);
					zephir_check_call_status();
					ZEPHIR_OBS_NVAR(name);
					zephir_array_fetch_string(&_22, tmp, SL("vno"), PH_READONLY, "xs/search.zep", 469 TSRMLS_CC);
					if (zephir_array_isset_fetch(&name, vnoes, _22, 0 TSRMLS_CC)) {
						ZEPHIR_OBS_NVAR(_23);
						zephir_read_property(&_23, res, SL("buf"), PH_NOISY_CC);
						zephir_array_fetch_string(&_24, tmp, SL("vlen"), PH_NOISY | PH_READONLY, "xs/search.zep", 470 TSRMLS_CC);
						ZEPHIR_SINIT_NVAR(_21);
						ZVAL_LONG(&_21, (off + 6));
						ZEPHIR_INIT_NVAR(value);
						zephir_substr(value, _23, zephir_get_intval(&_21), zephir_get_intval(_24), 0);
						zephir_array_fetch_string(&_25, tmp, SL("num"), PH_NOISY | PH_READONLY, "xs/search.zep", 471 TSRMLS_CC);
						zephir_update_property_array_multi(this_ptr, SL("facets"), &_25 TSRMLS_CC, SL("zz"), 2, name, value);
					}
					zephir_array_fetch_string(&_24, tmp, SL("vlen"), PH_NOISY | PH_READONLY, "xs/search.zep", 473 TSRMLS_CC);
					off += (zephir_get_numberval(_24) + 6);
				}
				break;
			}
			if (ZEPHIR_IS_LONG(_17, 140)) {
				ZEPHIR_INIT_NVAR(doc);
				object_init_ex(doc, xs_document_ce);
				ZEPHIR_OBS_NVAR(_18);
				zephir_read_property(&_18, res, SL("buf"), PH_NOISY_CC);
				_26 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
				ZEPHIR_CALL_METHOD(NULL, doc, "__construct", &_27, 32, _18, _26);
				zephir_check_call_status();
				zephir_array_append(&ret, doc, PH_SEPARATE, "xs/search.zep", 478);
				break;
			}
			if (ZEPHIR_IS_LONG(_17, 141)) {
				if (zephir_is_true(doc)) {
					ZEPHIR_CALL_METHOD(&name, res, "getarg", &_28, 0);
					zephir_check_call_status();
					ZEPHIR_OBS_NVAR(tmp);
					if (zephir_array_isset_fetch(&tmp, vnoes, name, 0 TSRMLS_CC)) {
						ZEPHIR_CPY_WRT(name, tmp);
					}
					ZEPHIR_OBS_NVAR(_18);
					zephir_read_property(&_18, res, SL("buf"), PH_NOISY_CC);
					ZEPHIR_CALL_METHOD(NULL, doc, "setfield", &_29, 33, name, _18);
					zephir_check_call_status();
				}
				break;
			}
			if (ZEPHIR_IS_LONG(_17, 143)) {
				if (zephir_is_true(doc)) {
					ZEPHIR_INIT_NVAR(_30);
					ZEPHIR_OBS_NVAR(_18);
					zephir_read_property(&_18, res, SL("buf"), PH_NOISY_CC);
					zephir_fast_explode_str(_30, SL(" "), _18, LONG_MAX TSRMLS_CC);
					ZEPHIR_INIT_NVAR(_31);
					ZVAL_STRING(_31, "matched", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_INIT_NVAR(_32);
					ZVAL_BOOL(_32, 1);
					ZEPHIR_CALL_METHOD(NULL, doc, "setfield", &_29, 33, _31, _30, _32);
					zephir_check_temp_parameter(_31);
					zephir_check_call_status();
				}
				break;
			}
			if (ZEPHIR_IS_LONG(_17, 128)) {
				ZEPHIR_CALL_METHOD(&_33, res, "getarg", &_28, 0);
				zephir_check_call_status();
				if (ZEPHIR_IS_LONG(_33, 207)) {
					endLoop = 1;
					break;
				}
			}
			ZEPHIR_CALL_METHOD(&name, res, "getarg", &_28, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(_30);
			object_init_ex(_30, xs_exception_ce);
			ZEPHIR_OBS_NVAR(_18);
			zephir_read_property(&_18, res, SL("cmd"), PH_NOISY_CC);
			ZEPHIR_INIT_LNVAR(_34);
			ZEPHIR_CONCAT_SVSVS(_34, "Unexpected respond in search {CMD:", _18, ", ARG:", name, "}");
			ZEPHIR_CALL_METHOD(NULL, _30, "__construct", &_35, 4, _34);
			zephir_check_call_status();
			zephir_throw_exception_debug(_30, "xs/search.zep", 501 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		} while(0);

		if (endLoop) {
			break;
		}
	}
	if (ZEPHIR_IS_STRING_IDENTICAL(query, "")) {
		_26 = zephir_fetch_nproperty_this(this_ptr, SL("lastCount"), PH_NOISY_CC);
		zephir_update_property_this(this_ptr, SL("count"), _26 TSRMLS_CC);
		_36 = zephir_fetch_nproperty_this(this_ptr, SL("curDb"), PH_NOISY_CC);
		if (!ZEPHIR_IS_STRING_IDENTICAL(_36, "log_db")) {
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "logquery", NULL, 34);
			zephir_check_call_status();
			if (saveHighlight) {
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "inithighlight", NULL, 35);
				zephir_check_call_status();
			}
		}
	}
	ZEPHIR_INIT_ZVAL_NREF(_26);
	ZVAL_LONG(_26, 0);
	zephir_update_property_this(this_ptr, SL("offset"), _26 TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_26);
	ZVAL_LONG(_26, 0);
	zephir_update_property_this(this_ptr, SL("limit"), _26 TSRMLS_CC);
	RETURN_CCTOR(ret);

}

PHP_METHOD(Xs_Search, getLastCount) {


	RETURN_MEMBER(this_ptr, "lastCount");

}

PHP_METHOD(Xs_Search, getDbTotal) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *cmd, *res = NULL, *tmp = NULL, *_0 = NULL, *_1, _2, *_3;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 64);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 203);
	ZEPHIR_CALL_METHOD(&res, this_ptr, "execcommand", NULL, 0, cmd, _0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_1);
	zephir_read_property(&_1, res, SL("buf"), PH_NOISY_CC);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_STRING(&_2, "Itotal", 0);
	ZEPHIR_CALL_FUNCTION(&tmp, "unpack", NULL, 5, &_2, _1);
	zephir_check_call_status();
	zephir_array_fetch_string(&_3, tmp, SL("total"), PH_NOISY | PH_READONLY, "xs/search.zep", 533 TSRMLS_CC);
	RETURN_CTOR(_3);

}

PHP_METHOD(Xs_Search, getHotQuery) {

	HashTable *_11;
	HashPosition _10;
	zend_bool _8;
	zephir_fcall_cache_entry *_6 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *type = NULL, *_9;
	zval *limit_param = NULL, *type_param = NULL, *ret, *result = NULL, *doc = NULL, *body = NULL, *ex = NULL, *_0 = NULL, *_1, *_2 = NULL, *_3 = NULL, *_4, *_5 = NULL, *_7 = NULL, **_12, *_13 = NULL, *_14 = NULL, *_15;
	long limit;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &limit_param, &type_param);

	if (!limit_param) {
		limit = 6;
	} else {
		limit = zephir_get_intval(limit_param);
	}
	if (!type_param) {
		ZEPHIR_INIT_VAR(type);
		ZVAL_STRING(type, "total", 1);
	} else {
		zephir_get_strval(type, type_param);
	}
	ZEPHIR_INIT_VAR(ret);
	array_init(ret);


	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 50);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, limit);
	ZEPHIR_CALL_FUNCTION(&_2, "min", NULL, 25, _0, _1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 1);
	ZEPHIR_CALL_FUNCTION(&_3, "max", NULL, 26, _0, _2);
	zephir_check_call_status();
	limit = zephir_get_intval(_3);
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
	ZEPHIR_CALL_CE_STATIC(&_5, xs_fieldscheme_ce, "logger", &_6, 36);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, _4, "setscheme", NULL, 0, _5);
	zephir_check_call_status();

	/* try_start_1: */

		ZEPHIR_INIT_NVAR(_0);
		ZVAL_STRING(_0, "log_db", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&_7, this_ptr, "setdb", NULL, 0, _0);
		zephir_check_temp_parameter(_0);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, limit);
		ZEPHIR_CALL_METHOD(NULL, _7, "setlimit", NULL, 0, _0);
		zephir_check_call_status_or_jump(try_end_1);
		_8 = !ZEPHIR_IS_STRING_IDENTICAL(type, "lastnum");
		if (_8) {
			_8 = !ZEPHIR_IS_STRING_IDENTICAL(type, "currnum");
		}
		if (_8) {
			ZEPHIR_INIT_NVAR(type);
			ZVAL_STRING(type, "total", 1);
		}
		ZEPHIR_INIT_VAR(_9);
		ZEPHIR_CONCAT_VS(_9, type, ":1");
		ZEPHIR_CALL_METHOD(&result, this_ptr, "search", NULL, 0, _9);
		zephir_check_call_status_or_jump(try_end_1);
		zephir_is_iterable(result, &_11, &_10, 0, 0, "xs/search.zep", 553);
		for (
		  ; zephir_hash_get_current_data_ex(_11, (void**) &_12, &_10) == SUCCESS
		  ; zephir_hash_move_forward_ex(_11, &_10)
		) {
			ZEPHIR_GET_HVALUE(doc, _12);
			ZEPHIR_OBS_NVAR(_13);
			zephir_read_property(&_13, doc, SL("body"), PH_NOISY_CC);
			ZEPHIR_CPY_WRT(body, _13);
			ZEPHIR_CALL_METHOD(&_14, doc, "f", NULL, 0, type);
			zephir_check_call_status_or_jump(try_end_1);
			zephir_array_update_zval(&ret, body, &_14, PH_COPY | PH_SEPARATE);
		}
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "restoredb", NULL, 37);
		zephir_check_call_status_or_jump(try_end_1);

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(ex, EG(exception));
		if (zephir_instance_of_ev(ex, xs_exception_ce TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CALL_METHOD(&_7, ex, "getcode", NULL, 0);
			zephir_check_call_status();
			if (!ZEPHIR_IS_LONG(_7, 515)) {
				zephir_throw_exception_debug(ex, "xs/search.zep", 556 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	_15 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _15, "restorescheme", NULL, 0);
	zephir_check_call_status();
	RETURN_CCTOR(ret);

}

PHP_METHOD(Xs_Search, getRelatedQuery) {

	HashTable *_14;
	HashPosition _13;
	zephir_fcall_cache_entry *_9 = NULL, *_19 = NULL;
	zend_bool _5;
	int ZEPHIR_LAST_CALL_STATUS;
	long limit, op;
	zval *query = NULL, *limit_param = NULL, *ret, *result = NULL, *doc = NULL, *body = NULL, *ex = NULL, *_0 = NULL, *_1 = NULL, *_2 = NULL, *_3 = NULL, *_4, _6, *_7, *_8 = NULL, *_10 = NULL, *_11 = NULL, *_12 = NULL, **_15, *_16, *_17 = NULL, *_18 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &query, &limit_param);

	if (!query) {
		ZEPHIR_CPY_WRT(query, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(query);
	}
	if (!limit_param) {
		limit = 6;
	} else {
		limit = zephir_get_intval(limit_param);
	}
	ZEPHIR_INIT_VAR(ret);
	array_init(ret);


	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 20);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, limit);
	ZEPHIR_CALL_FUNCTION(&_2, "min", NULL, 25, _0, _1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 1);
	ZEPHIR_CALL_FUNCTION(&_3, "max", NULL, 26, _0, _2);
	zephir_check_call_status();
	limit = zephir_get_intval(_3);
	if (Z_TYPE_P(query) == IS_NULL) {
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("query"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&query, this_ptr, "cleanfieldquery", NULL, 38, _4);
		zephir_check_call_status();
	}
	_5 = ZEPHIR_IS_EMPTY(query);
	if (!(_5)) {
		ZEPHIR_SINIT_VAR(_6);
		ZVAL_STRING(&_6, ":", 0);
		ZEPHIR_INIT_NVAR(_0);
		zephir_fast_strpos(_0, query, &_6, 0 );
		_5 = !ZEPHIR_IS_FALSE_IDENTICAL(_0);
	}
	if (_5) {
		RETURN_CCTOR(ret);
	}
	ZEPHIR_OBS_VAR(_7);
	zephir_read_property_this(&_7, this_ptr, SL("defaultOp"), PH_NOISY_CC);
	op = zephir_get_intval(_7);
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
	ZEPHIR_CALL_CE_STATIC(&_8, xs_fieldscheme_ce, "logger", &_9, 36);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, _4, "setscheme", NULL, 0, _8);
	zephir_check_call_status();

	/* try_start_1: */

		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "log_db", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&_10, this_ptr, "setdb", NULL, 0, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CALL_METHOD(&_11, _10, "setfuzzy", NULL, 0);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_LONG(_1, (limit + 1));
		ZEPHIR_CALL_METHOD(&_12, _11, "setlimit", NULL, 0, _1);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CALL_METHOD(&result, _12, "search", NULL, 0, query);
		zephir_check_call_status_or_jump(try_end_1);
		zephir_is_iterable(result, &_14, &_13, 0, 0, "xs/search.zep", 591);
		for (
		  ; zephir_hash_get_current_data_ex(_14, (void**) &_15, &_13) == SUCCESS
		  ; zephir_hash_move_forward_ex(_14, &_13)
		) {
			ZEPHIR_GET_HVALUE(doc, _15);
			_16 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
			ZEPHIR_CALL_METHOD(NULL, doc, "setcharset", NULL, 0, _16);
			zephir_check_call_status_or_jump(try_end_1);
			ZEPHIR_OBS_NVAR(_17);
			zephir_read_property(&_17, doc, SL("body"), PH_NOISY_CC);
			ZEPHIR_CPY_WRT(body, _17);
			ZEPHIR_CALL_FUNCTION(&_18, "strcasecmp", &_19, 39, body, query);
			zephir_check_call_status_or_jump(try_end_1);
			if (!(zephir_is_true(_18))) {
				continue;
			}
			zephir_array_append(&ret, body, PH_SEPARATE, "xs/search.zep", 586);
			if (zephir_fast_count_int(ret TSRMLS_CC) == limit) {
				break;
			}
		}

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(ex, EG(exception));
		if (zephir_instance_of_ev(ex, xs_exception_ce TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CALL_METHOD(&_10, ex, "getcode", NULL, 0);
			zephir_check_call_status();
			if (!ZEPHIR_IS_LONG(_10, 515)) {
				zephir_throw_exception_debug(ex, "xs/search.zep", 593 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "restoredb", NULL, 37);
	zephir_check_call_status();
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _4, "restorescheme", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_ZVAL_NREF(_16);
	ZVAL_LONG(_16, op);
	zephir_update_property_this(this_ptr, SL("defaultOp"), _16 TSRMLS_CC);
	RETURN_CCTOR(ret);

}

PHP_METHOD(Xs_Search, getExpandedQuery) {

	zend_bool _13;
	zephir_fcall_cache_entry *_5 = NULL, *_8 = NULL, *_14 = NULL, *_16 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	long limit;
	zval *query_param = NULL, *limit_param = NULL, *ret, *cmd, *res = NULL, *ex = NULL, *_0 = NULL, *_1, *_2 = NULL, *_3 = NULL, *_4 = NULL, *_6, *_9 = NULL, *_10 = NULL, *_11 = NULL, *_12, *_15 = NULL;
	zval *query = NULL, *buf = NULL, *_7 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &query_param, &limit_param);

	zephir_get_strval(query, query_param);
	if (!limit_param) {
		limit = 10;
	} else {
		limit = zephir_get_intval(limit_param);
	}
	ZEPHIR_INIT_VAR(ret);
	array_init(ret);


	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 20);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, limit);
	ZEPHIR_CALL_FUNCTION(&_2, "min", NULL, 25, _0, _1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 1);
	ZEPHIR_CALL_FUNCTION(&_3, "max", NULL, 26, _0, _2);
	zephir_check_call_status();
	limit = zephir_get_intval(_3);

	/* try_start_1: */

		_6 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_STRING(_0, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_4, xs_xs_ce, "convert", &_5, 7, query, _0, _6);
		zephir_check_temp_parameter(_0);
		zephir_check_call_status_or_jump(try_end_1);
		zephir_get_strval(_7, _4);
		ZEPHIR_CPY_WRT(buf, _7);
		ZEPHIR_INIT_VAR(cmd);
		zephir_create_array(cmd, 3, 0 TSRMLS_CC);
		add_assoc_long_ex(cmd, SS("cmd"), 99);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, limit);
		zephir_array_update_string(&cmd, SL("arg1"), &_0, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&cmd, SL("buf"), &buf, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, 206);
		ZEPHIR_CALL_METHOD(&res, this_ptr, "execcommand", NULL, 0, cmd, _0);
		zephir_check_call_status_or_jump(try_end_1);
		while (1) {
			ZEPHIR_CALL_METHOD(&res, this_ptr, "getrespond", &_8, 0);
			zephir_check_call_status_or_jump(try_end_1);
			ZEPHIR_OBS_NVAR(_9);
			zephir_read_property(&_9, res, SL("cmd"), PH_NOISY_CC);
			if (ZEPHIR_IS_LONG(_9, 141)) {
				ZEPHIR_OBS_NVAR(_11);
				zephir_read_property(&_11, res, SL("buf"), PH_NOISY_CC);
				_12 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
				ZEPHIR_INIT_NVAR(_0);
				ZVAL_STRING(_0, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
				ZEPHIR_CALL_CE_STATIC(&_10, xs_xs_ce, "convert", &_5, 7, _11, _12, _0);
				zephir_check_temp_parameter(_0);
				zephir_check_call_status_or_jump(try_end_1);
				zephir_array_append(&ret, _10, PH_SEPARATE, "xs/search.zep", 616);
				continue;
			}
			ZEPHIR_OBS_NVAR(_11);
			zephir_read_property(&_11, res, SL("cmd"), PH_NOISY_CC);
			_13 = ZEPHIR_IS_LONG(_11, 128);
			if (_13) {
				ZEPHIR_CALL_METHOD(&_10, res, "getarg", &_14, 0);
				zephir_check_call_status_or_jump(try_end_1);
				_13 = ZEPHIR_IS_LONG(_10, 207);
			}
			if (_13) {
				break;
			}
			ZEPHIR_INIT_NVAR(_0);
			object_init_ex(_0, xs_exception_ce);
			ZEPHIR_OBS_NVAR(_11);
			zephir_read_property(&_11, res, SL("cmd"), PH_NOISY_CC);
			ZEPHIR_CALL_METHOD(&_10, res, "getarg", &_14, 0);
			zephir_check_call_status_or_jump(try_end_1);
			ZEPHIR_INIT_LNVAR(_15);
			ZEPHIR_CONCAT_SVSVS(_15, "Unexpected respond in search {CMD:", _11, ", ARG:", _10, "}");
			ZEPHIR_CALL_METHOD(NULL, _0, "__construct", &_16, 4, _15);
			zephir_check_call_status_or_jump(try_end_1);
			zephir_throw_exception_debug(_0, "xs/search.zep", 622 TSRMLS_CC);
			goto try_end_1;

		}

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(ex, EG(exception));
		if (zephir_instance_of_ev(ex, xs_exception_ce TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CALL_METHOD(&_4, ex, "getcode", NULL, 0);
			zephir_check_call_status();
			if (!ZEPHIR_IS_LONG(_4, 515)) {
				zephir_throw_exception_debug(ex, "xs/search.zep", 626 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	RETURN_CCTOR(ret);

}

PHP_METHOD(Xs_Search, getCorrectedQuery) {

	zephir_fcall_cache_entry *_7 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _1;
	zval *buf = NULL, *_9 = NULL;
	zval *query = NULL, *ret = NULL, *cmd, *res = NULL, *ex = NULL, *_0, *_2, *_3 = NULL, _4 = zval_used_for_init, *_5, *_6, *_8 = NULL, *_10, *_11 = NULL, *_12;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &query);

	if (!query) {
		ZEPHIR_CPY_WRT(query, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(query);
	}
	ZEPHIR_INIT_VAR(ret);
	array_init(ret);



	/* try_start_1: */

		if (Z_TYPE_P(query) == IS_NULL) {
			_0 = zephir_fetch_nproperty_this(this_ptr, SL("count"), PH_NOISY_CC);
			_1 = ZEPHIR_GT_LONG(_0, 0);
			if (_1) {
				_2 = zephir_fetch_nproperty_this(this_ptr, SL("count"), PH_NOISY_CC);
				ZEPHIR_CALL_METHOD(&_3, this_ptr, "getdbtotal", NULL, 0);
				zephir_check_call_status_or_jump(try_end_1);
				ZEPHIR_SINIT_VAR(_4);
				ZVAL_DOUBLE(&_4, (zephir_get_numberval(_3) * 0.001));
				_1 = ZEPHIR_GT_LONG(_2, zephir_ceil(&_4 TSRMLS_CC));
			}
			if (_1) {
				RETURN_CCTOR(ret);
			}
			_5 = zephir_fetch_nproperty_this(this_ptr, SL("query"), PH_NOISY_CC);
			ZEPHIR_CALL_METHOD(&query, this_ptr, "cleanfieldquery", NULL, 38, _5);
			zephir_check_call_status_or_jump(try_end_1);
		}
		_1 = ZEPHIR_IS_EMPTY(query);
		if (!(_1)) {
			ZEPHIR_SINIT_NVAR(_4);
			ZVAL_STRING(&_4, ":", 0);
			ZEPHIR_INIT_VAR(_6);
			zephir_fast_strpos(_6, query, &_4, 0 );
			_1 = !ZEPHIR_IS_FALSE_IDENTICAL(_6);
		}
		if (_1) {
			RETURN_CCTOR(ret);
		}
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_8);
		ZVAL_STRING(_8, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_3, xs_xs_ce, "convert", &_7, 7, query, _8, _0);
		zephir_check_temp_parameter(_8);
		zephir_check_call_status_or_jump(try_end_1);
		zephir_get_strval(_9, _3);
		ZEPHIR_CPY_WRT(buf, _9);
		ZEPHIR_INIT_VAR(cmd);
		zephir_create_array(cmd, 2, 0 TSRMLS_CC);
		add_assoc_long_ex(cmd, SS("cmd"), 98);
		zephir_array_update_string(&cmd, SL("buf"), &buf, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(_8);
		ZVAL_LONG(_8, 205);
		ZEPHIR_CALL_METHOD(&res, this_ptr, "execcommand", NULL, 0, cmd, _8);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_OBS_VAR(_10);
		zephir_read_property(&_10, res, SL("buf"), PH_NOISY_CC);
		if (!ZEPHIR_IS_STRING_IDENTICAL(_10, "")) {
			ZEPHIR_OBS_VAR(_12);
			zephir_read_property(&_12, res, SL("buf"), PH_NOISY_CC);
			_2 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(_8);
			ZVAL_STRING(_8, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_CE_STATIC(&_11, xs_xs_ce, "convert", &_7, 7, _12, _2, _8);
			zephir_check_temp_parameter(_8);
			zephir_check_call_status_or_jump(try_end_1);
			ZEPHIR_INIT_NVAR(ret);
			zephir_fast_explode_str(ret, SL("\n"), _11, LONG_MAX TSRMLS_CC);
		}

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(ex, EG(exception));
		if (zephir_instance_of_ev(ex, xs_exception_ce TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CALL_METHOD(&_3, ex, "getcode", NULL, 0);
			zephir_check_call_status();
			if (!ZEPHIR_IS_LONG(_3, 515)) {
				zephir_throw_exception_debug(ex, "xs/search.zep", 656 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	RETURN_CCTOR(ret);

}

PHP_METHOD(Xs_Search, addSearchLog) {

	int ZEPHIR_LAST_CALL_STATUS;
	long wdf;
	zval *query_param = NULL, *wdf_param = NULL, *cmd, _0, _1, *_2 = NULL, *_3;
	zval *query = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &query_param, &wdf_param);

	zephir_get_strval(query, query_param);
	if (!wdf_param) {
		wdf = 1;
	} else {
		wdf = zephir_get_intval(wdf_param);
	}


	ZEPHIR_INIT_VAR(cmd);
	zephir_create_array(cmd, 2, 0 TSRMLS_CC);
	add_assoc_long_ex(cmd, SS("cmd"), 71);
	zephir_array_update_string(&cmd, SL("buf"), &query, PH_COPY | PH_SEPARATE);
	if (wdf > 1) {
		ZEPHIR_SINIT_VAR(_0);
		ZVAL_STRING(&_0, "i", 0);
		ZEPHIR_SINIT_VAR(_1);
		ZVAL_LONG(&_1, wdf);
		ZEPHIR_CALL_FUNCTION(&_2, "pack", NULL, 2, &_0, &_1);
		zephir_check_call_status();
		zephir_array_update_string(&cmd, SL("buf1"), &_2, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 210);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd, _3);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Search, highlight) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool strtr;
	zval *value_param = NULL, *strtr_param = NULL, *p = NULL, *_0, *_1, *_2, *_3, *_4 = NULL, *_5, *_6, *_7, *_8 = NULL;
	zval *value = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &value_param, &strtr_param);

	zephir_get_strval(value, value_param);
	if (!strtr_param) {
		strtr = 0;
	} else {
		strtr = zephir_get_boolval(strtr_param);
	}


	if (ZEPHIR_IS_EMPTY(value)) {
		RETURN_CTOR(value);
	}
	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("highlight"), PH_NOISY_CC);
	if (Z_TYPE_P(_0) != IS_ARRAY) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "inithighlight", NULL, 35);
		zephir_check_call_status();
	}
	ZEPHIR_OBS_VAR(p);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("highlight"), PH_NOISY_CC);
	if (zephir_array_isset_string_fetch(&p, _1, SS("pattern"), 0 TSRMLS_CC)) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("highlight"), PH_NOISY_CC);
		zephir_array_fetch_string(&_3, _2, SL("replace"), PH_NOISY | PH_READONLY, "xs/search.zep", 684 TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&_4, "preg_replace", NULL, 40, p, _3, value);
		zephir_check_call_status();
		zephir_get_strval(value, _4);
	}
	ZEPHIR_OBS_NVAR(p);
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("highlight"), PH_NOISY_CC);
	if (zephir_array_isset_string_fetch(&p, _2, SS("pairs"), 0 TSRMLS_CC)) {
		if (strtr) {
			_5 = zephir_fetch_nproperty_this(this_ptr, SL("highlight"), PH_NOISY_CC);
			zephir_array_fetch_string(&_3, _5, SL("pairs"), PH_NOISY | PH_READONLY, "xs/search.zep", 688 TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(&_4, "strtr", NULL, 41, value, _3);
			zephir_check_call_status();
			zephir_get_strval(value, _4);
		} else {
			ZEPHIR_INIT_VAR(_6);
			ZEPHIR_INIT_VAR(_7);
			zephir_array_keys(_7, p TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(&_8, "array_values", NULL, 42, p);
			zephir_check_call_status();
			zephir_fast_str_replace(&_6, _7, _8, value TSRMLS_CC);
			zephir_get_strval(value, _6);
		}
	}
	RETURN_CTOR(value);

}

PHP_METHOD(Xs_Search, logQuery) {

	unsigned char _27;
	HashTable *_23;
	HashPosition _22;
	zend_bool _7, _9, _11, _14, _17;
	zephir_fcall_cache_entry *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	long max, pos, pos1;
	zval *query_param = NULL, *terms = NULL, *term = NULL, *pos2 = NULL, *_0 = NULL, *_1 = NULL, *_2 = NULL, *_4, *_6, *_8, _10 = zval_used_for_init, _12 = zval_used_for_init, *_13, _15, *_16, _18, *_19, *_20, *_21, **_24, *_25 = NULL, *_28 = NULL;
	zval *query = NULL, *log = NULL, *_5 = NULL, *_26 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &query_param);

	if (!query_param) {
		ZEPHIR_INIT_VAR(query);
		ZVAL_STRING(query, "", 1);
	} else {
		zephir_get_strval(query, query_param);
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "isrobotagent", NULL, 43);
	zephir_check_call_status();
	if (zephir_is_true(_0)) {
		RETURN_MM_NULL();
	}
	if (zephir_fast_strlen_ev(query) > 0) {
		ZEPHIR_INIT_VAR(_2);
		ZVAL_BOOL(_2, 0);
		ZEPHIR_CALL_METHOD(&terms, this_ptr, "terms", &_3, 0, query, _2);
		zephir_check_call_status();
	} else {
		ZEPHIR_OBS_VAR(_4);
		zephir_read_property_this(&_4, this_ptr, SL("query"), PH_NOISY_CC);
		zephir_get_strval(_5, _4);
		ZEPHIR_CPY_WRT(query, _5);
		_6 = zephir_fetch_nproperty_this(this_ptr, SL("lastCount"), PH_NOISY_CC);
		_7 = !zephir_is_true(_6);
		if (!(_7)) {
			_8 = zephir_fetch_nproperty_this(this_ptr, SL("defaultOp"), PH_NOISY_CC);
			_9 = ZEPHIR_IS_LONG(_8, 1);
			if (_9) {
				ZEPHIR_SINIT_VAR(_10);
				ZVAL_STRING(&_10, " ", 0);
				ZEPHIR_INIT_NVAR(_2);
				zephir_fast_strpos(_2, query, &_10, 0 );
				_9 = zephir_is_true(_2);
			}
			_7 = _9;
		}
		_11 = _7;
		if (!(_11)) {
			ZEPHIR_SINIT_VAR(_12);
			ZVAL_STRING(&_12, " OR ", 0);
			ZEPHIR_INIT_VAR(_13);
			zephir_fast_strpos(_13, query, &_12, 0 );
			_11 = zephir_is_true(_13);
		}
		_14 = _11;
		if (!(_14)) {
			ZEPHIR_SINIT_VAR(_15);
			ZVAL_STRING(&_15, " NOT ", 0);
			ZEPHIR_INIT_VAR(_16);
			zephir_fast_strpos(_16, query, &_15, 0 );
			_14 = zephir_is_true(_16);
		}
		_17 = _14;
		if (!(_17)) {
			ZEPHIR_SINIT_VAR(_18);
			ZVAL_STRING(&_18, " XOR ", 0);
			ZEPHIR_INIT_VAR(_19);
			zephir_fast_strpos(_19, query, &_18, 0 );
			_17 = zephir_is_true(_19);
		}
		if (_17) {
			RETURN_MM_NULL();
		}
		ZEPHIR_INIT_VAR(_20);
		ZVAL_NULL(_20);
		ZEPHIR_INIT_VAR(_21);
		ZVAL_BOOL(_21, 0);
		ZEPHIR_CALL_METHOD(&terms, this_ptr, "terms", &_3, 0, _20, _21);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(log);
	ZVAL_EMPTY_STRING(log);
	max = 0;
	pos = 0;
	zephir_is_iterable(terms, &_23, &_22, 0, 0, "xs/search.zep", 746);
	for (
	  ; zephir_hash_get_current_data_ex(_23, (void**) &_24, &_22) == SUCCESS
	  ; zephir_hash_move_forward_ex(_23, &_22)
	) {
		ZEPHIR_GET_HVALUE(term, _24);
		_7 = pos > 3;
		if (_7) {
			_7 = zephir_fast_strlen_ev(term) == 6;
		}
		if (_7) {
			pos1 = (pos - 3);
		} else {
			pos1 = pos;
		}
		ZEPHIR_SINIT_NVAR(_10);
		ZVAL_LONG(&_10, pos1);
		ZEPHIR_INIT_NVAR(pos2);
		zephir_fast_strpos(pos2, query, term, zephir_get_intval(&_10) );
		if (ZEPHIR_IS_FALSE_IDENTICAL(pos2)) {
			continue;
		}
		if (ZEPHIR_IS_LONG_IDENTICAL(pos2, pos)) {
			zephir_concat_self(&log, term TSRMLS_CC);
		} else {
			if (ZEPHIR_LT_LONG(pos2, pos)) {
				ZEPHIR_SINIT_NVAR(_12);
				ZVAL_LONG(&_12, 3);
				ZEPHIR_INIT_NVAR(_2);
				zephir_substr(_2, term, 3 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
				zephir_concat_self(&log, _2 TSRMLS_CC);
			} else {
				max++;
				_9 = max > 3;
				if (!(_9)) {
					_9 = zephir_fast_strlen_ev(log) > 42;
				}
				if (_9) {
					break;
				}
				ZEPHIR_INIT_LNVAR(_25);
				ZEPHIR_CONCAT_SV(_25, " ", term);
				zephir_concat_self(&log, _25 TSRMLS_CC);
			}
		}
		pos = (zephir_get_numberval(pos2) + zephir_fast_strlen_ev(term));
	}
	ZEPHIR_INIT_NVAR(_2);
	zephir_fast_trim(_2, log, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
	zephir_get_strval(_26, _2);
	ZEPHIR_CPY_WRT(log, _26);
	_7 = zephir_fast_strlen_ev(log) < 2;
	if (!(_7)) {
		_9 = zephir_fast_strlen_ev(log) == 3;
		if (_9) {
			_27 = ZEPHIR_STRING_OFFSET(log, 0);
			ZEPHIR_SINIT_NVAR(_10);
			ZVAL_LONG(&_10, _27);
			ZEPHIR_CALL_FUNCTION(&_28, "ord", NULL, 22, &_10);
			zephir_check_call_status();
			_9 = ZEPHIR_GT_LONG(_28, 0x80);
		}
		_7 = _9;
	}
	if (_7) {
		RETURN_MM_NULL();
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "addsearchlog", NULL, 0, log);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Search, clearQuery) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *cmd, *_0 = NULL, *_1, *_2;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 224);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _0);
	zephir_check_call_status();
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("resetScheme"), PH_NOISY_CC);
	if (ZEPHIR_IS_TRUE_IDENTICAL(_1)) {
		ZEPHIR_INIT_ZVAL_NREF(_2);
		ZVAL_LONG(_2, 1);
		zephir_update_property_zval(cmd, SL("arg1"), _2 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_0);
		array_init(_0);
		zephir_update_property_this(this_ptr, SL("prefix"), _0 TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("fieldSet"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("resetScheme"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("terms"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("count"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("query"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Search, addQueryString) {

	zend_bool _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *bscale = NULL, *_4 = NULL;
	long addOp, scale;
	zval *query = NULL, *addOp_param = NULL, *scale_param = NULL, *cmd, *_0 = NULL, _2, _3, *_5, *_6, *_7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &query, &addOp_param, &scale_param);

	ZEPHIR_SEPARATE_PARAM(query);
	if (!addOp_param) {
		addOp = 0;
	} else {
		addOp = zephir_get_intval(addOp_param);
	}
	if (!scale_param) {
		scale = 1;
	} else {
		scale = zephir_get_intval(scale_param);
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "prequerystring", NULL, 28, query);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(query, _0);
	_1 = scale > 0;
	if (_1) {
		_1 = scale != 1;
	}
	if (_1) {
		ZEPHIR_SINIT_VAR(_2);
		ZVAL_STRING(&_2, "n", 0);
		ZEPHIR_SINIT_VAR(_3);
		ZVAL_LONG(&_3, ((scale * 100)));
		ZEPHIR_CALL_FUNCTION(&_0, "pack", NULL, 2, &_2, &_3);
		zephir_check_call_status();
		zephir_get_strval(_4, _0);
		ZEPHIR_CPY_WRT(bscale, _4);
	} else {
		ZEPHIR_INIT_NVAR(bscale);
		ZVAL_EMPTY_STRING(bscale);
	}
	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("defaultOp"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_6);
	ZVAL_LONG(_6, 225);
	ZEPHIR_INIT_VAR(_7);
	ZVAL_LONG(_7, addOp);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _6, _7, _5, query, bscale);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd);
	zephir_check_call_status();
	RETVAL_ZVAL(query, 1, 0);
	RETURN_MM();

}

PHP_METHOD(Xs_Search, addQueryTerm) {

	zend_bool _7;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	long addOp, scale, vno;
	zval *term = NULL, *bscale = NULL, *_6 = NULL, *_11 = NULL;
	zval *field, *term_param = NULL, *addOp_param = NULL, *scale_param = NULL, *cmd, *_0 = NULL, *_2 = NULL, *_3, *_4, *_5 = NULL, _8, _9, *_10 = NULL, *_12, *_13, *_14, *_15;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 2, &field, &term_param, &addOp_param, &scale_param);

	zephir_get_strval(term, term_param);
	if (!addOp_param) {
		addOp = 0;
	} else {
		addOp = zephir_get_intval(addOp_param);
	}
	if (!scale_param) {
		scale = 1;
	} else {
		scale = zephir_get_intval(scale_param);
	}


	ZEPHIR_INIT_VAR(_3);
	zephir_fast_strtolower(_3, term);
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_5);
	ZVAL_STRING(_5, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&_0, xs_xs_ce, "convert", &_1, 7, _3, _5, _4);
	zephir_check_temp_parameter(_5);
	zephir_check_call_status();
	zephir_get_strval(_6, _0);
	ZEPHIR_CPY_WRT(term, _6);
	_7 = scale > 0;
	if (_7) {
		_7 = scale != 1;
	}
	if (_7) {
		ZEPHIR_SINIT_VAR(_8);
		ZVAL_STRING(&_8, "n", 0);
		ZEPHIR_SINIT_VAR(_9);
		ZVAL_LONG(&_9, ((scale * 100)));
		ZEPHIR_CALL_FUNCTION(&_10, "pack", NULL, 2, &_8, &_9);
		zephir_check_call_status();
		zephir_get_strval(_11, _10);
		ZEPHIR_CPY_WRT(bscale, _11);
	} else {
		ZEPHIR_INIT_NVAR(bscale);
		ZVAL_EMPTY_STRING(bscale);
	}
	if (Z_TYPE_P(field) == IS_NULL) {
		vno = 255;
	} else {
		_12 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_5);
		ZVAL_BOOL(_5, 1);
		ZEPHIR_CALL_METHOD(&_10, _12, "getfield", NULL, 0, field, _5);
		zephir_check_call_status();
		ZEPHIR_OBS_VAR(_13);
		zephir_read_property(&_13, _10, SL("vno"), PH_NOISY_CC);
		vno = zephir_get_numberval(_13);
	}
	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	ZEPHIR_INIT_NVAR(_5);
	ZVAL_LONG(_5, 226);
	ZEPHIR_INIT_VAR(_14);
	ZVAL_LONG(_14, addOp);
	ZEPHIR_INIT_VAR(_15);
	ZVAL_LONG(_15, vno);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _5, _14, _15, term, bscale);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd);
	zephir_check_call_status();
	RETURN_THIS();

}

PHP_METHOD(Xs_Search, restoreDb) {

	zephir_fcall_cache_entry *_3 = NULL;
	HashTable *_1;
	HashPosition _0;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *db, *dbs, *name = NULL, **_2;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(db);
	zephir_read_property_this(&db, this_ptr, SL("lastDb"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(dbs);
	zephir_read_property_this(&dbs, this_ptr, SL("lastDbs"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setdb", NULL, 0, db);
	zephir_check_call_status();
	zephir_is_iterable(dbs, &_1, &_0, 0, 0, "xs/search.zep", 818);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(name, _2);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "adddb", &_3, 0, name);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Search, preQueryString) {

	zephir_fcall_cache_entry *_15 = NULL, *_30 = NULL, *_41 = NULL;
	zend_bool _13, _34, _39;
	HashTable *_5, *_26;
	HashPosition _4, _25;
	int ZEPHIR_LAST_CALL_STATUS;
	long i;
	zval *query_param = NULL, *parts = NULL, *part = NULL, *pos = NULL, *field = NULL, *terms = NULL, *tokens = NULL, *term = NULL, *_0, *_2, _3 = zval_used_for_init, **_6, _7 = zval_used_for_init, _8 = zval_used_for_init, *_9 = NULL, _10 = zval_used_for_init, *_11 = NULL, *_12, *_14 = NULL, *_16 = NULL, *_17 = NULL, _18 = zval_used_for_init, _19 = zval_used_for_init, _20 = zval_used_for_init, _21 = zval_used_for_init, _22 = zval_used_for_init, _23 = zval_used_for_init, *_24 = NULL, **_27, *_28 = NULL, *_29 = NULL, *_32 = NULL, *_33 = NULL, *_35 = NULL, *_36 = NULL, *_37 = NULL, *_38 = NULL, *_40 = NULL;
	zval *query = NULL, *newQuery, *name = NULL, *prefix = NULL, *suffix = NULL, *value = NULL, *_1 = NULL, *_31 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &query_param);

	zephir_get_strval(query, query_param);


	ZEPHIR_INIT_VAR(_0);
	zephir_fast_trim(_0, query, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
	zephir_get_strval(_1, _0);
	ZEPHIR_CPY_WRT(query, _1);
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("resetScheme"), PH_NOISY_CC);
	if (ZEPHIR_IS_TRUE_IDENTICAL(_2)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "clearquery", NULL, 30);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "initspecialfield", NULL, 44);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(newQuery);
	ZVAL_EMPTY_STRING(newQuery);
	ZEPHIR_SINIT_VAR(_3);
	ZVAL_STRING(&_3, "/[ \t\r\n]+/", 0);
	ZEPHIR_CALL_FUNCTION(&parts, "preg_split", NULL, 45, &_3, query);
	zephir_check_call_status();
	zephir_is_iterable(parts, &_5, &_4, 0, 0, "xs/search.zep", 887);
	for (
	  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
	  ; zephir_hash_move_forward_ex(_5, &_4)
	) {
		ZEPHIR_GET_HVALUE(part, _6);
		if (ZEPHIR_IS_STRING_IDENTICAL(part, "")) {
			continue;
		}
		if (!ZEPHIR_IS_STRING(newQuery, "")) {
			zephir_concat_self_str(&newQuery, " ", sizeof(" ")-1 TSRMLS_CC);
		}
		ZEPHIR_SINIT_NVAR(_3);
		ZVAL_STRING(&_3, ":", 0);
		ZEPHIR_INIT_NVAR(pos);
		zephir_fast_strpos(pos, part, &_3, 1 );
		if (!ZEPHIR_IS_FALSE_IDENTICAL(pos)) {
			i = 0;
			while (1) {
				if (!(ZEPHIR_GT_LONG(pos, i))) {
					break;
				}
				ZEPHIR_SINIT_NVAR(_7);
				ZVAL_LONG(&_7, i);
				ZEPHIR_SINIT_NVAR(_8);
				ZVAL_LONG(&_8, 1);
				ZEPHIR_INIT_NVAR(_9);
				zephir_substr(_9, part, zephir_get_intval(&_7), 1 , 0);
				ZEPHIR_SINIT_NVAR(_10);
				ZVAL_STRING(&_10, "+-~(", 0);
				ZEPHIR_INIT_NVAR(_11);
				zephir_fast_strpos(_11, &_10, _9, 0 );
				if (ZEPHIR_IS_FALSE_IDENTICAL(_11)) {
					break;
				}
				i++;
			}
			ZEPHIR_SINIT_NVAR(_7);
			ZVAL_LONG(&_7, i);
			ZEPHIR_SINIT_NVAR(_8);
			ZVAL_LONG(&_8, (zephir_get_numberval(pos) - i));
			ZEPHIR_INIT_NVAR(name);
			zephir_substr(name, part, zephir_get_intval(&_7), zephir_get_intval(&_8), 0);
			_12 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(_9);
			ZVAL_BOOL(_9, 0);
			ZEPHIR_CALL_METHOD(&field, _12, "getfield", NULL, 0, name, _9);
			zephir_check_call_status();
			_13 = !ZEPHIR_IS_FALSE_IDENTICAL(field);
			if (_13) {
				ZEPHIR_OBS_NVAR(_14);
				zephir_read_property(&_14, field, SL("vno"), PH_NOISY_CC);
				_13 = !ZEPHIR_IS_LONG(_14, 255);
			}
			if (_13) {
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "regqueryprefix", &_15, 46, name);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_16, field, "hascustomtokenizer", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(_16)) {
					ZEPHIR_INIT_LNVAR(_17);
					if (i > 0) {
						ZEPHIR_SINIT_NVAR(_10);
						ZVAL_LONG(&_10, 0);
						ZEPHIR_SINIT_NVAR(_18);
						ZVAL_LONG(&_18, i);
						ZEPHIR_INIT_NVAR(_17);
						zephir_substr(_17, part, 0 , zephir_get_intval(&_18), 0);
					} else {
						ZEPHIR_INIT_NVAR(_17);
						ZVAL_STRING(_17, "", 1);
					}
					zephir_get_strval(prefix, _17);
					ZEPHIR_INIT_NVAR(suffix);
					ZVAL_EMPTY_STRING(suffix);
					ZEPHIR_SINIT_NVAR(_19);
					ZVAL_LONG(&_19, (zephir_get_numberval(pos) + 1));
					ZEPHIR_INIT_NVAR(value);
					zephir_substr(value, part, zephir_get_intval(&_19), 0, ZEPHIR_SUBSTR_NO_LENGTH);
					ZEPHIR_SINIT_NVAR(_20);
					ZVAL_LONG(&_20, -1);
					ZEPHIR_SINIT_NVAR(_21);
					ZVAL_LONG(&_21, 1);
					ZEPHIR_INIT_NVAR(_9);
					zephir_substr(_9, value, -1 , 1 , 0);
					if (ZEPHIR_IS_STRING_IDENTICAL(_9, ")")) {
						ZEPHIR_INIT_NVAR(suffix);
						ZVAL_STRING(suffix, ")", 1);
						ZEPHIR_SINIT_NVAR(_22);
						ZVAL_LONG(&_22, 0);
						ZEPHIR_SINIT_NVAR(_23);
						ZVAL_LONG(&_23, -1);
						ZEPHIR_INIT_NVAR(_11);
						zephir_substr(_11, value, 0 , -1 , 0);
						zephir_get_strval(value, _11);
					}
					ZEPHIR_INIT_NVAR(terms);
					array_init(terms);
					ZEPHIR_CALL_METHOD(&_24, field, "getcustomtokenizer", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&tokens, _24, "gettokens", NULL, 0, value);
					zephir_check_call_status();
					zephir_is_iterable(tokens, &_26, &_25, 0, 0, "xs/search.zep", 866);
					for (
					  ; zephir_hash_get_current_data_ex(_26, (void**) &_27, &_25) == SUCCESS
					  ; zephir_hash_move_forward_ex(_26, &_25)
					) {
						ZEPHIR_GET_HVALUE(term, _27);
						ZEPHIR_INIT_NVAR(_28);
						zephir_fast_strtolower(_28, term);
						zephir_array_append(&terms, _28, PH_SEPARATE, "xs/search.zep", 864);
					}
					ZEPHIR_CALL_FUNCTION(&_29, "array_unique", &_30, 21, terms);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(terms, _29);
					ZEPHIR_INIT_NVAR(_28);
					ZEPHIR_INIT_LNVAR(_31);
					ZEPHIR_CONCAT_SVS(_31, " ", name, ":");
					zephir_fast_join(_28, _31, terms TSRMLS_CC);
					ZEPHIR_INIT_LNVAR(_32);
					ZEPHIR_CONCAT_VVSVV(_32, prefix, name, ":", _28, suffix);
					zephir_concat_self(&newQuery, _32 TSRMLS_CC);
				} else {
					ZEPHIR_SINIT_NVAR(_18);
					ZVAL_LONG(&_18, (zephir_get_numberval(pos) + 1));
					ZEPHIR_SINIT_NVAR(_19);
					ZVAL_LONG(&_19, 1);
					ZEPHIR_INIT_NVAR(_33);
					zephir_substr(_33, part, zephir_get_intval(&_18), 1 , 0);
					_34 = !ZEPHIR_IS_STRING(_33, "(");
					if (_34) {
						ZEPHIR_INIT_NVAR(_35);
						ZEPHIR_INIT_NVAR(_36);
						ZEPHIR_SINIT_NVAR(_20);
						ZVAL_STRING(&_20, "/[\\x81-\\xfe]/", 0);
						zephir_preg_match(_36, &_20, part, _35, 0, 0 , 0  TSRMLS_CC);
						_34 = zephir_is_true(_36);
					}
					if (_34) {
						ZEPHIR_SINIT_NVAR(_21);
						ZVAL_LONG(&_21, 0);
						ZEPHIR_SINIT_NVAR(_22);
						ZVAL_LONG(&_22, (zephir_get_numberval(pos) + 1));
						ZEPHIR_INIT_NVAR(_37);
						zephir_substr(_37, part, 0 , zephir_get_intval(&_22), 0);
						ZEPHIR_SINIT_NVAR(_23);
						ZVAL_LONG(&_23, (zephir_get_numberval(pos) + 1));
						ZEPHIR_INIT_NVAR(_38);
						zephir_substr(_38, part, zephir_get_intval(&_23), 0, ZEPHIR_SUBSTR_NO_LENGTH);
						ZEPHIR_INIT_LNVAR(_17);
						ZEPHIR_CONCAT_VSVS(_17, _37, "(", _38, ")");
						zephir_concat_self(&newQuery, _17 TSRMLS_CC);
					} else {
						zephir_concat_self(&newQuery, part TSRMLS_CC);
					}
				}
				continue;
			}
		}
		_13 = zephir_fast_strlen_ev(part) > 1;
		if (_13) {
			ZEPHIR_SINIT_NVAR(_7);
			ZVAL_LONG(&_7, 0);
			ZEPHIR_SINIT_NVAR(_8);
			ZVAL_LONG(&_8, 1);
			ZEPHIR_INIT_NVAR(_9);
			zephir_substr(_9, part, 0 , 1 , 0);
			ZEPHIR_SINIT_NVAR(_10);
			ZVAL_STRING(&_10, "+-", 0);
			ZEPHIR_INIT_NVAR(_11);
			zephir_fast_strpos(_11, &_10, _9, 0 );
			_13 = !ZEPHIR_IS_FALSE_IDENTICAL(_11);
		}
		_34 = _13;
		if (_34) {
			ZEPHIR_SINIT_NVAR(_18);
			ZVAL_LONG(&_18, 1);
			ZEPHIR_SINIT_NVAR(_19);
			ZVAL_LONG(&_19, 1);
			ZEPHIR_INIT_NVAR(_28);
			zephir_substr(_28, part, 1 , 1 , 0);
			_34 = !ZEPHIR_IS_STRING_IDENTICAL(_28, "(");
		}
		_39 = _34;
		if (_39) {
			ZEPHIR_INIT_NVAR(_40);
			ZEPHIR_INIT_NVAR(_33);
			ZEPHIR_SINIT_NVAR(_20);
			ZVAL_STRING(&_20, "/[\\x81-\\xfe]/", 0);
			zephir_preg_match(_33, &_20, part, _40, 0, 0 , 0  TSRMLS_CC);
			_39 = zephir_is_true(_33);
		}
		if (_39) {
			ZEPHIR_SINIT_NVAR(_21);
			ZVAL_LONG(&_21, 0);
			ZEPHIR_SINIT_NVAR(_22);
			ZVAL_LONG(&_22, 1);
			ZEPHIR_INIT_NVAR(_36);
			zephir_substr(_36, part, 0 , 1 , 0);
			ZEPHIR_SINIT_NVAR(_23);
			ZVAL_LONG(&_23, 1);
			ZEPHIR_INIT_NVAR(_37);
			zephir_substr(_37, part, 1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
			ZEPHIR_INIT_LNVAR(_17);
			ZEPHIR_CONCAT_VSVS(_17, _36, "(", _37, ")");
			zephir_concat_self(&newQuery, _17 TSRMLS_CC);
			continue;
		}
		zephir_concat_self(&newQuery, part TSRMLS_CC);
	}
	_12 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
	ZEPHIR_INIT_NVAR(_38);
	ZVAL_STRING(_38, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_RETURN_CALL_CE_STATIC(xs_xs_ce, "convert", &_41, 7, newQuery, _38, _12);
	zephir_check_temp_parameter(_38);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Xs_Search, regQueryPrefix) {

	int ZEPHIR_LAST_CALL_STATUS;
	long type;
	zval *name_param = NULL, *field = NULL, *cmd, *_0, *_1, *_2 = NULL, *_3, *_4 = NULL, *_5 = NULL, *_6, *_7;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("prefix"), PH_NOISY_CC);
	if (!(zephir_array_isset(_0, name))) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_2);
		ZVAL_BOOL(_2, 0);
		ZEPHIR_CALL_METHOD(&field, _1, "getfield", NULL, 0, name, _2);
		zephir_check_call_status();
		ZEPHIR_OBS_VAR(_3);
		zephir_read_property(&_3, field, SL("vno"), PH_NOISY_CC);
		if (!ZEPHIR_IS_LONG(_3, 255)) {
			ZEPHIR_INIT_VAR(_4);
			ZEPHIR_CALL_METHOD(&_5, field, "isboolindex", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(_5)) {
				ZEPHIR_INIT_NVAR(_4);
				ZVAL_LONG(_4, 1);
			} else {
				ZEPHIR_INIT_NVAR(_4);
				ZVAL_LONG(_4, 0);
			}
			type = zephir_get_numberval(_4);
			ZEPHIR_INIT_VAR(cmd);
			object_init_ex(cmd, xs_command_ce);
			ZEPHIR_OBS_VAR(_6);
			zephir_read_property(&_6, field, SL("vno"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(_2);
			ZVAL_LONG(_2, 230);
			ZEPHIR_INIT_VAR(_7);
			ZVAL_LONG(_7, type);
			ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _2, _7, _6, name);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd);
			zephir_check_call_status();
			zephir_update_property_array(this_ptr, SL("prefix"), name, ZEPHIR_GLOBAL(global_true) TSRMLS_CC);
		}
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Search, initSpecialField) {

	zephir_fcall_cache_entry *_12 = NULL, *_14 = NULL, *_15 = NULL;
	HashTable *_4;
	HashPosition _3;
	int ZEPHIR_LAST_CALL_STATUS;
	long len;
	zval *field = NULL, *cmd = NULL, *_0, *_1, *_2 = NULL, **_5, *_6 = NULL, *_7 = NULL, _8 = zval_used_for_init, *_9 = NULL, *_10 = NULL, *_11 = NULL, *_13 = NULL;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("fieldSet"), PH_NOISY_CC);
	if (ZEPHIR_IS_TRUE_IDENTICAL(_0)) {
		RETURN_MM_NULL();
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_2, _1, "getallfields", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(_2, &_4, &_3, 0, 0, "xs/search.zep", 926);
	for (
	  ; zephir_hash_get_current_data_ex(_4, (void**) &_5, &_3) == SUCCESS
	  ; zephir_hash_move_forward_ex(_4, &_3)
	) {
		ZEPHIR_GET_HVALUE(field, _5);
		ZEPHIR_OBS_NVAR(_6);
		zephir_read_property(&_6, field, SL("cutlen"), PH_NOISY_CC);
		if (!ZEPHIR_IS_LONG(_6, 0)) {
			ZEPHIR_OBS_NVAR(_7);
			zephir_read_property(&_7, field, SL("cutlen"), PH_NOISY_CC);
			ZEPHIR_SINIT_NVAR(_8);
			ZVAL_DOUBLE(&_8, zephir_safe_div_zval_long(_7, 10 TSRMLS_CC));
			ZEPHIR_INIT_NVAR(_9);
			ZVAL_LONG(_9, 127);
			ZEPHIR_INIT_NVAR(_10);
			ZVAL_DOUBLE(_10, zephir_ceil(&_8 TSRMLS_CC));
			ZEPHIR_CALL_FUNCTION(&_11, "min", &_12, 25, _9, _10);
			zephir_check_call_status();
			len = zephir_get_intval(_11);
			ZEPHIR_INIT_NVAR(cmd);
			object_init_ex(cmd, xs_command_ce);
			ZEPHIR_OBS_NVAR(_13);
			zephir_read_property(&_13, field, SL("vno"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(_9);
			ZVAL_LONG(_9, 193);
			ZEPHIR_INIT_NVAR(_10);
			ZVAL_LONG(_10, len);
			ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", &_14, 19, _9, _10, _13);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", &_15, 0, cmd);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_METHOD(&_11, field, "isnumeric", NULL, 0);
		zephir_check_call_status();
		if (zephir_is_true(_11)) {
			ZEPHIR_INIT_NVAR(cmd);
			object_init_ex(cmd, xs_command_ce);
			ZEPHIR_OBS_NVAR(_7);
			zephir_read_property(&_7, field, SL("vno"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(_9);
			ZVAL_LONG(_9, 194);
			ZEPHIR_INIT_NVAR(_10);
			ZVAL_LONG(_10, 0);
			ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", &_14, 19, _9, _10, _7);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", &_15, 18, cmd);
			zephir_check_call_status();
		}
	}
	zephir_update_property_this(this_ptr, SL("fieldSet"), (1) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Search, cleanFieldQuery) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0, *_4;
	zval *query_param = NULL, *_1 = NULL, _2, *_3, *_5 = NULL;
	zval *query = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &query_param);

	zephir_get_strval(query, query_param);


	ZEPHIR_INIT_VAR(_0);
	zephir_create_array(_0, 2, 0 TSRMLS_CC);
	add_assoc_stringl_ex(_0, SS(" AND "), SL(" "), 1);
	add_assoc_stringl_ex(_0, SS(" OR "), SL(" "), 1);
	ZEPHIR_CALL_FUNCTION(&_1, "strtr", NULL, 41, query, _0);
	zephir_check_call_status();
	zephir_get_strval(query, _1);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_STRING(&_2, ":", 0);
	ZEPHIR_INIT_VAR(_3);
	zephir_fast_strpos(_3, query, &_2, 0 );
	if (!ZEPHIR_IS_FALSE_IDENTICAL(_3)) {
		ZEPHIR_INIT_VAR(_4);
		zephir_create_array(_4, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(_4, this_ptr);
		ZEPHIR_INIT_VAR(_5);
		ZVAL_STRING(_5, "cleanFieldCallback", 1);
		zephir_array_fast_append(_4, _5);
		ZEPHIR_INIT_NVAR(_5);
		ZVAL_STRING(_5, "/(^|\\s)([0-9A-Za-z_\\.-]+):([^\\s]+)/", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_FUNCTION("preg_replace_callback", NULL, 29, _5, _4, query);
		zephir_check_temp_parameter(_5);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_CTOR(query);

}

PHP_METHOD(Xs_Search, cleanFieldCallback) {

	zend_bool _7;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *match_param = NULL, *field = NULL, *_0, *_1, *_2 = NULL, *_3, *_4 = NULL, _5, _6, *_8, _9, _10, *_11, *_12, _13, _14, *_15;
	zval *match = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &match_param);

	zephir_get_arrval(match, match_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
	zephir_array_fetch_long(&_1, match, 2, PH_NOISY | PH_READONLY, "xs/search.zep", 942 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_BOOL(_2, 0);
	ZEPHIR_CALL_METHOD(&field, _0, "getfield", NULL, 0, _1, _2);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE_IDENTICAL(field)) {
		zephir_array_fetch_long(&_3, match, 0, PH_NOISY | PH_READONLY, "xs/search.zep", 944 TSRMLS_CC);
		RETURN_CTOR(_3);
	}
	ZEPHIR_CALL_METHOD(&_4, field, "isboolindex", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(_4)) {
		RETURN_MM_STRING("", 1);
	}
	zephir_array_fetch_long(&_3, match, 3, PH_NOISY | PH_READONLY, "xs/search.zep", 949 TSRMLS_CC);
	ZEPHIR_SINIT_VAR(_5);
	ZVAL_LONG(&_5, 0);
	ZEPHIR_SINIT_VAR(_6);
	ZVAL_LONG(&_6, 1);
	ZEPHIR_INIT_NVAR(_2);
	zephir_substr(_2, _3, 0 , 1 , 0);
	_7 = ZEPHIR_IS_STRING(_2, "(");
	if (_7) {
		zephir_array_fetch_long(&_8, match, 3, PH_NOISY | PH_READONLY, "xs/search.zep", 949 TSRMLS_CC);
		ZEPHIR_SINIT_VAR(_9);
		ZVAL_LONG(&_9, -1);
		ZEPHIR_SINIT_VAR(_10);
		ZVAL_LONG(&_10, 1);
		ZEPHIR_INIT_VAR(_11);
		zephir_substr(_11, _8, -1 , 1 , 0);
		_7 = ZEPHIR_IS_STRING(_11, ")");
	}
	if (_7) {
		zephir_array_fetch_long(&_12, match, 3, PH_NOISY | PH_READONLY, "xs/search.zep", 950 TSRMLS_CC);
		ZEPHIR_SINIT_VAR(_13);
		ZVAL_LONG(&_13, 1);
		ZEPHIR_SINIT_VAR(_14);
		ZVAL_LONG(&_14, -1);
		ZEPHIR_INIT_VAR(_15);
		zephir_substr(_15, _12, 1 , -1 , 0);
		zephir_array_update_long(&match, 3, &_15, PH_COPY | PH_SEPARATE, "xs/search.zep", 950);
	}
	zephir_array_fetch_long(&_3, match, 1, PH_NOISY | PH_READONLY, "xs/search.zep", 952 TSRMLS_CC);
	zephir_array_fetch_long(&_12, match, 3, PH_NOISY | PH_READONLY, "xs/search.zep", 952 TSRMLS_CC);
	ZEPHIR_CONCAT_VV(return_value, _3, _12);
	RETURN_MM();

}

PHP_METHOD(Xs_Search, initHighlight) {

	zval *_29 = NULL;
	HashTable *_26;
	HashPosition _25;
	zephir_fcall_cache_entry *_8 = NULL, *_10 = NULL, *_30 = NULL;
	zend_bool _3, _14;
	int ZEPHIR_LAST_CALL_STATUS;
	long i, j, k;
	zval *terms, *tmps = NULL, *pairs, *replace, *pattern, *term = NULL, *_0, *_1 = NULL, *_2, *_4, _5 = zval_used_for_init, _6 = zval_used_for_init, *_7 = NULL, *_9 = NULL, *_11, *_12, *_13 = NULL, *_15, _16 = zval_used_for_init, _17 = zval_used_for_init, *_18, _19 = zval_used_for_init, _20 = zval_used_for_init, *_21 = NULL, *_22 = NULL, *_23 = NULL, *_24, **_27, *_28 = NULL, *_31 = NULL, *_32, *_33;

	ZEPHIR_MM_GROW();
	ZEPHIR_INIT_VAR(terms);
	array_init(terms);

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("highlight"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_BOOL(_1, 0);
	ZEPHIR_CALL_METHOD(&tmps, this_ptr, "terms", NULL, 0, _0, _1);
	zephir_check_call_status();
	i = 0;
	while (1) {
		if (!(i < zephir_fast_count_int(tmps TSRMLS_CC))) {
			break;
		}
		zephir_array_fetch_long(&_2, tmps, i, PH_NOISY | PH_READONLY, "xs/search.zep", 963 TSRMLS_CC);
		_3 = zephir_fast_strlen_ev(_2) != 6;
		if (!(_3)) {
			zephir_array_fetch_long(&_4, tmps, i, PH_NOISY | PH_READONLY, "xs/search.zep", 963 TSRMLS_CC);
			ZEPHIR_SINIT_NVAR(_5);
			ZVAL_LONG(&_5, 0);
			ZEPHIR_SINIT_NVAR(_6);
			ZVAL_LONG(&_6, 1);
			ZEPHIR_INIT_NVAR(_1);
			zephir_substr(_1, _4, 0 , 1 , 0);
			ZEPHIR_CALL_FUNCTION(&_7, "ord", &_8, 22, _1);
			zephir_check_call_status();
			_3 = ZEPHIR_LT_LONG(_7, 0xc0);
		}
		if (_3) {
			zephir_array_fetch_long(&_11, tmps, i, PH_NOISY | PH_READONLY, "xs/search.zep", 964 TSRMLS_CC);
			_12 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(_13);
			ZVAL_STRING(_13, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_CE_STATIC(&_9, xs_xs_ce, "convert", &_10, 0, _11, _12, _13);
			zephir_check_temp_parameter(_13);
			zephir_check_call_status();
			zephir_array_append(&terms, _9, PH_SEPARATE, "xs/search.zep", 964);
			i++;
			continue;
		}
		j = (i + 1);
		while (1) {
			if (!(j < zephir_fast_count_int(tmps TSRMLS_CC))) {
				break;
			}
			zephir_array_fetch_long(&_11, tmps, j, PH_NOISY | PH_READONLY, "xs/search.zep", 970 TSRMLS_CC);
			_14 = zephir_fast_strlen_ev(_11) != 6;
			if (!(_14)) {
				zephir_array_fetch_long(&_15, tmps, j, PH_NOISY | PH_READONLY, "xs/search.zep", 970 TSRMLS_CC);
				ZEPHIR_SINIT_NVAR(_16);
				ZVAL_LONG(&_16, 0);
				ZEPHIR_SINIT_NVAR(_17);
				ZVAL_LONG(&_17, 3);
				ZEPHIR_INIT_NVAR(_13);
				zephir_substr(_13, _15, 0 , 3 , 0);
				zephir_array_fetch_long(&_18, tmps, (j - 1), PH_NOISY | PH_READONLY, "xs/search.zep", 970 TSRMLS_CC);
				ZEPHIR_SINIT_NVAR(_19);
				ZVAL_LONG(&_19, 3);
				ZEPHIR_SINIT_NVAR(_20);
				ZVAL_LONG(&_20, 3);
				ZEPHIR_INIT_NVAR(_21);
				zephir_substr(_21, _18, 3 , 3 , 0);
				_14 = !ZEPHIR_IS_IDENTICAL(_13, _21);
			}
			if (_14) {
				break;
			}
			j++;
		}
		k = (j - i);
		if (k == 1) {
			zephir_array_fetch_long(&_11, tmps, i, PH_NOISY | PH_READONLY, "xs/search.zep", 977 TSRMLS_CC);
			_12 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
			ZEPHIR_INIT_NVAR(_13);
			ZVAL_STRING(_13, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_CE_STATIC(&_9, xs_xs_ce, "convert", &_10, 7, _11, _12, _13);
			zephir_check_temp_parameter(_13);
			zephir_check_call_status();
			zephir_array_append(&terms, _9, PH_SEPARATE, "xs/search.zep", 977);
		} else {
			i = (j - 1);
			while (1) {
				if (!(k)) {
					break;
				}
				j--;
				if ((k & 1)) {
					zephir_array_fetch_long(&_11, tmps, (j - 1), PH_NOISY | PH_READONLY, "xs/search.zep", 983 TSRMLS_CC);
					ZEPHIR_SINIT_NVAR(_16);
					ZVAL_LONG(&_16, 0);
					ZEPHIR_SINIT_NVAR(_17);
					ZVAL_LONG(&_17, 3);
					ZEPHIR_INIT_NVAR(_13);
					zephir_substr(_13, _11, 0 , 3 , 0);
					zephir_array_fetch_long(&_15, tmps, j, PH_NOISY | PH_READONLY, "xs/search.zep", 983 TSRMLS_CC);
					ZEPHIR_INIT_LNVAR(_22);
					ZEPHIR_CONCAT_VV(_22, _13, _15);
					_12 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
					ZEPHIR_INIT_NVAR(_21);
					ZVAL_STRING(_21, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_CE_STATIC(&_9, xs_xs_ce, "convert", &_10, 7, _22, _12, _21);
					zephir_check_temp_parameter(_21);
					zephir_check_call_status();
					zephir_array_append(&terms, _9, PH_SEPARATE, "xs/search.zep", 983);
				}
				zephir_array_fetch_long(&_18, tmps, j, PH_NOISY | PH_READONLY, "xs/search.zep", 985 TSRMLS_CC);
				_24 = zephir_fetch_nproperty_this(this_ptr, SL("charset"), PH_NOISY_CC);
				ZEPHIR_INIT_NVAR(_21);
				ZVAL_STRING(_21, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
				ZEPHIR_CALL_CE_STATIC(&_23, xs_xs_ce, "convert", &_10, 7, _18, _24, _21);
				zephir_check_temp_parameter(_21);
				zephir_check_call_status();
				zephir_array_append(&terms, _23, PH_SEPARATE, "xs/search.zep", 985);
				k--;
			}
		}
		i++;
	}
	ZEPHIR_INIT_VAR(pairs);
	array_init(pairs);
	ZEPHIR_INIT_VAR(replace);
	array_init(replace);
	ZEPHIR_INIT_VAR(pattern);
	array_init(pattern);
	zephir_is_iterable(terms, &_26, &_25, 0, 0, "xs/search.zep", 1002);
	for (
	  ; zephir_hash_get_current_data_ex(_26, (void**) &_27, &_25) == SUCCESS
	  ; zephir_hash_move_forward_ex(_26, &_25)
	) {
		ZEPHIR_GET_HVALUE(term, _27);
		ZEPHIR_INIT_NVAR(_28);
		ZEPHIR_INIT_NVAR(_13);
		ZEPHIR_SINIT_NVAR(_5);
		ZVAL_STRING(&_5, "/[a-zA-Z]/", 0);
		zephir_preg_match(_13, &_5, term, _28, 0, 0 , 0  TSRMLS_CC);
		if (!(zephir_is_true(_13))) {
			ZEPHIR_INIT_LNVAR(_22);
			ZEPHIR_CONCAT_SVS(_22, "<em>", term, "</em>");
			zephir_array_update_zval(&pairs, term, &_22, PH_COPY | PH_SEPARATE);
		} else {
			ZEPHIR_INIT_NVAR(_29);
			zephir_create_array(_29, 2, 0 TSRMLS_CC);
			add_assoc_stringl_ex(_29, SS("+"), SL("\\+"), 1);
			add_assoc_stringl_ex(_29, SS("/"), SL("\\/"), 1);
			ZEPHIR_CALL_FUNCTION(&_7, "strtr", &_30, 41, term, _29);
			zephir_check_call_status();
			ZEPHIR_INIT_LNVAR(_31);
			ZEPHIR_CONCAT_SVS(_31, "/", _7, "/i");
			zephir_array_append(&pattern, _31, PH_SEPARATE, "xs/search.zep", 998);
			ZEPHIR_INIT_NVAR(_13);
			ZVAL_STRING(_13, "<em>0</em>", 1);
			zephir_array_append(&replace, _13, PH_SEPARATE, "xs/search.zep", 999);
		}
	}
	ZEPHIR_INIT_NVAR(_13);
	array_init(_13);
	zephir_update_property_this(this_ptr, SL("highlight"), _13 TSRMLS_CC);
	if (zephir_fast_count_int(pairs TSRMLS_CC) > 0) {
		ZEPHIR_INIT_NVAR(_21);
		ZVAL_STRING(_21, "pairs", 1);
		zephir_update_property_array(this_ptr, SL("highlight"), _21, pairs TSRMLS_CC);
	}
	if (zephir_fast_count_int(pattern TSRMLS_CC) > 0) {
		ZEPHIR_INIT_VAR(_32);
		ZVAL_STRING(_32, "pattern", 1);
		zephir_update_property_array(this_ptr, SL("highlight"), _32, pattern TSRMLS_CC);
		ZEPHIR_INIT_VAR(_33);
		ZVAL_STRING(_33, "replace", 1);
		zephir_update_property_array(this_ptr, SL("highlight"), _33, replace TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Search, formatValueRange) {

	zephir_fcall_cache_entry *_7 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *val1 = NULL, *val2 = NULL;
	zval *match_param = NULL, *field = NULL, *_0, *_1, *_2, *_3, *_4, *_5 = NULL, *_6 = NULL, *_8, *_9;
	zval *match = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &match_param);

	zephir_get_arrval(match, match_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(_1);
	zephir_array_fetch_long(&_1, match, 2, PH_NOISY, "xs/search.zep", 1017 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, zephir_get_intval(_1));
	ZEPHIR_INIT_VAR(_3);
	ZVAL_BOOL(_3, 0);
	ZEPHIR_CALL_METHOD(&field, _0, "getfield", NULL, 0, _2, _3);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE_IDENTICAL(field)) {
		zephir_array_fetch_long(&_4, match, 0, PH_NOISY | PH_READONLY, "xs/search.zep", 1019 TSRMLS_CC);
		RETURN_CTOR(_4);
	}
	ZEPHIR_INIT_VAR(val1);
	ZVAL_STRING(val1, "~", 1);
	ZEPHIR_INIT_VAR(val2);
	ZVAL_STRING(val2, "~", 1);
	if (zephir_array_isset_long(match, 4)) {
		ZEPHIR_INIT_VAR(_5);
		ZEPHIR_CALL_METHOD(&_6, field, "isnumeric", NULL, 0);
		zephir_check_call_status();
		if (zephir_is_true(_6)) {
			zephir_array_fetch_long(&_4, match, 4, PH_NOISY | PH_READONLY, "xs/search.zep", 1024 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&_5, this_ptr, "xapianunserialise", &_7, 47, _4);
			zephir_check_call_status();
		} else {
			ZEPHIR_OBS_NVAR(_5);
			zephir_array_fetch_long(&_5, match, 4, PH_NOISY, "xs/search.zep", 1024 TSRMLS_CC);
		}
		zephir_get_strval(val2, _5);
	}
	zephir_array_fetch_long(&_4, match, 1, PH_NOISY | PH_READONLY, "xs/search.zep", 1026 TSRMLS_CC);
	if (ZEPHIR_IS_STRING_IDENTICAL(_4, "VALUE_LE")) {
		ZEPHIR_INIT_LNVAR(_5);
		ZEPHIR_CALL_METHOD(&_6, field, "isnumeric", NULL, 0);
		zephir_check_call_status();
		if (zephir_is_true(_6)) {
			zephir_array_fetch_long(&_8, match, 3, PH_NOISY | PH_READONLY, "xs/search.zep", 1027 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&_5, this_ptr, "xapianunserialise", &_7, 47, _8);
			zephir_check_call_status();
		} else {
			ZEPHIR_OBS_NVAR(_5);
			zephir_array_fetch_long(&_5, match, 3, PH_NOISY, "xs/search.zep", 1027 TSRMLS_CC);
		}
		zephir_get_strval(val2, _5);
	} else {
		ZEPHIR_INIT_LNVAR(_5);
		ZEPHIR_CALL_METHOD(&_6, field, "isnumeric", NULL, 0);
		zephir_check_call_status();
		if (zephir_is_true(_6)) {
			zephir_array_fetch_long(&_4, match, 3, PH_NOISY | PH_READONLY, "xs/search.zep", 1029 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&_5, this_ptr, "xapianunserialise", &_7, 47, _4);
			zephir_check_call_status();
		} else {
			ZEPHIR_OBS_NVAR(_5);
			zephir_array_fetch_long(&_5, match, 3, PH_NOISY, "xs/search.zep", 1029 TSRMLS_CC);
		}
		zephir_get_strval(val1, _5);
	}
	ZEPHIR_OBS_VAR(_9);
	zephir_read_property(&_9, field, SL("name"), PH_NOISY_CC);
	ZEPHIR_CONCAT_VSVSVS(return_value, _9, ":[", val1, ",", val2, "]");
	RETURN_MM();

}

PHP_METHOD(Xs_Search, numfromstr) {

	int ZEPHIR_LAST_CALL_STATUS;
	unsigned char _1;
	long index;
	zval *str_param = NULL, *index_param = NULL, *_0 = NULL, _2;
	zval *str = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &str_param, &index_param);

	zephir_get_strval(str, str_param);
	index = zephir_get_intval(index_param);


	ZEPHIR_INIT_VAR(_0);
	if (index < zephir_fast_strlen_ev(str)) {
		_1 = ZEPHIR_STRING_OFFSET(str, index);
		ZEPHIR_SINIT_VAR(_2);
		ZVAL_LONG(&_2, _1);
		ZEPHIR_CALL_FUNCTION(&_0, "ord", NULL, 22, &_2);
		zephir_check_call_status();
	} else {
		ZVAL_LONG(_0, 0);
	}
	RETURN_CCTOR(_0);

}

PHP_METHOD(Xs_Search, xapianUnserialise) {

	unsigned char _5;
	zephir_fcall_cache_entry *_3 = NULL, *_6 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	double mantissa;
	long i, c, negative, exponentNegative, explen, exponent, word1, word2;
	zval *value_param = NULL, _0 = zval_used_for_init, _1 = zval_used_for_init, *_2 = NULL, *_4 = NULL, *_7 = NULL, *_8 = NULL, *_9 = NULL, *_10 = NULL, *_11 = NULL, *_12 = NULL, *_13, _14, _15;
	zval *value = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

	zephir_get_strval(value, value_param);


	if (ZEPHIR_IS_STRING_IDENTICAL(value, "\x80")) {
		RETURN_MM_DOUBLE(0.0);
	}
	ZEPHIR_SINIT_VAR(_0);
	ZVAL_STRING(&_0, "\\xff", 0);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_LONG(&_1, 9);
	ZEPHIR_CALL_FUNCTION(&_2, "str_repeat", NULL, 48, &_0, &_1);
	zephir_check_call_status();
	if (ZEPHIR_IS_IDENTICAL(value, _2)) {
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_STRING(&_0, "INF", 0);
		ZEPHIR_RETURN_CALL_FUNCTION("constant", &_3, 12, &_0);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (ZEPHIR_IS_STRING_IDENTICAL(value, "")) {
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_STRING(&_0, "INF", 0);
		ZEPHIR_CALL_FUNCTION(&_4, "constant", &_3, 12, &_0);
		zephir_check_call_status();
		RETURN_MM_DOUBLE((0.0 - zephir_get_numberval(_4)));
	}
	i = 0;
	_5 = ZEPHIR_STRING_OFFSET(value, 0);
	ZEPHIR_SINIT_NVAR(_0);
	ZVAL_LONG(&_0, _5);
	ZEPHIR_CALL_FUNCTION(&_4, "ord", NULL, 22, &_0);
	zephir_check_call_status();
	c = zephir_get_intval(_4);
	c = (c ^ ((((c & 0xc0)) >> 1)));
	if ((c & 0x80)) {
		negative = 0;
	} else {
		negative = 1;
	}
	if ((c & 0x40)) {
		exponentNegative = 1;
	} else {
		exponentNegative = 0;
	}
	if ((c & 0x20)) {
		explen = 0;
	} else {
		explen = 1;
	}
	exponent = (c & 0x1f);
	if (explen) {
		i++;
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_LONG(&_0, i);
		ZEPHIR_CALL_METHOD(&_4, this_ptr, "numfromstr", &_6, 49, value, &_0);
		zephir_check_call_status();
		c = zephir_get_intval(_4);
		exponent = (((exponent << 6)) | ((c >> 2)));
		if ((negative ^ exponentNegative)) {
			exponent = (exponent & 0x07ff);
		}
	} else {
		exponent = (exponent >> 2);
		if ((negative ^ exponentNegative)) {
			exponent = (exponent ^ 0x07);
		}
	}
	word1 = (((c & 0x03)) << 24);
	i++;
	ZEPHIR_SINIT_NVAR(_0);
	ZVAL_LONG(&_0, i);
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "numfromstr", &_6, 49, value, &_0);
	zephir_check_call_status();
	word1 = ((word1 | (int) (zephir_get_numberval(_4))) << 16);
	i++;
	ZEPHIR_SINIT_NVAR(_0);
	ZVAL_LONG(&_0, i);
	ZEPHIR_CALL_METHOD(&_7, this_ptr, "numfromstr", &_6, 49, value, &_0);
	zephir_check_call_status();
	word1 = ((word1 | (int) (zephir_get_numberval(_7))) << 8);
	i++;
	ZEPHIR_SINIT_NVAR(_0);
	ZVAL_LONG(&_0, i);
	ZEPHIR_CALL_METHOD(&_8, this_ptr, "numfromstr", &_6, 49, value, &_0);
	zephir_check_call_status();
	word1 = (word1 | (int) (zephir_get_numberval(_8)));
	word2 = 0;
	if (i < zephir_fast_strlen_ev(value)) {
		i++;
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_LONG(&_0, i);
		ZEPHIR_CALL_METHOD(&_9, this_ptr, "numfromstr", &_6, 49, value, &_0);
		zephir_check_call_status();
		word2 = ((int) (zephir_get_numberval(_9)) << 24);
		i++;
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_LONG(&_0, i);
		ZEPHIR_CALL_METHOD(&_10, this_ptr, "numfromstr", &_6, 49, value, &_0);
		zephir_check_call_status();
		word2 = ((word2 | (int) (zephir_get_numberval(_10))) << 16);
		i++;
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_LONG(&_0, i);
		ZEPHIR_CALL_METHOD(&_11, this_ptr, "numfromstr", &_6, 49, value, &_0);
		zephir_check_call_status();
		word2 = ((word2 | (int) (zephir_get_numberval(_11))) << 8);
		i++;
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_LONG(&_0, i);
		ZEPHIR_CALL_METHOD(&_12, this_ptr, "numfromstr", &_6, 49, value, &_0);
		zephir_check_call_status();
		word2 = (word2 | (int) (zephir_get_numberval(_12)));
	}
	if (negative) {
		word1 = (0 - word1);
		if (word2 != 0) {
			word1++;
		}
		word2 = (0 - word2);
		word1 = (word1 & 0x03ffffff);
	} else {
		word1 = (word1 | 67108864);
	}
	mantissa = (double) (0);
	if (word2) {
		mantissa = zephir_safe_div_long_double(word2, 4294967296.0 TSRMLS_CC);
	}
	mantissa += (double) word1;
	if (negative == 1) {
		mantissa = zephir_safe_div_double_long(mantissa, 67108864 TSRMLS_CC);
	} else {
		mantissa = zephir_safe_div_double_long(mantissa, 134217728 TSRMLS_CC);
	}
	if (exponentNegative) {
		exponent = (0 - exponent);
	}
	exponent += 8;
	if (negative) {
		mantissa = (double) (0 - mantissa);
	}
	ZEPHIR_INIT_VAR(_13);
	ZEPHIR_SINIT_NVAR(_0);
	ZVAL_LONG(&_0, 2);
	ZEPHIR_SINIT_NVAR(_1);
	ZVAL_LONG(&_1, exponent);
	zephir_pow_function(_13, &_0, &_1);
	ZEPHIR_SINIT_VAR(_14);
	ZVAL_LONG(&_14, (mantissa * zephir_get_numberval(_13)));
	ZEPHIR_SINIT_VAR(_15);
	ZVAL_LONG(&_15, 2);
	zephir_round(return_value, &_14, &_15, NULL TSRMLS_CC);
	RETURN_MM();

}

PHP_METHOD(Xs_Search, isRobotAgent) {

	HashTable *_3;
	HashPosition _2;
	zval *_0;
	zval *agent = NULL;
	zval *agentVar, *key = NULL, *_SERVER, *_1 = NULL, **_4;

	ZEPHIR_MM_GROW();
	zephir_get_global(&_SERVER, SS("_SERVER") TSRMLS_CC);

	ZEPHIR_OBS_VAR(agentVar);
	if (zephir_array_isset_string_fetch(&agentVar, _SERVER, SS("HTTP_USER_AGENT"), 0 TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(agent);
		zephir_fast_strtolower(agent, agentVar);
		ZEPHIR_INIT_VAR(_0);
		zephir_create_array(_0, 5, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(_1);
		ZVAL_STRING(_1, "bot", 1);
		zephir_array_fast_append(_0, _1);
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "slurp", 1);
		zephir_array_fast_append(_0, _1);
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "spider", 1);
		zephir_array_fast_append(_0, _1);
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "crawl", 1);
		zephir_array_fast_append(_0, _1);
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "curl", 1);
		zephir_array_fast_append(_0, _1);
		zephir_is_iterable(_0, &_3, &_2, 0, 0, "xs/search.zep", 1145);
		for (
		  ; zephir_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
		  ; zephir_hash_move_forward_ex(_3, &_2)
		) {
			ZEPHIR_GET_HVALUE(key, _4);
			ZEPHIR_INIT_NVAR(_1);
			zephir_fast_strpos(_1, agent, key, 0 );
			if (!ZEPHIR_IS_FALSE_IDENTICAL(_1)) {
				RETURN_MM_BOOL(1);
			}
		}
	}
	RETURN_MM_BOOL(0);

}

