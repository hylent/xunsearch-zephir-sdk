
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
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/hash.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "kernel/file.h"


ZEPHIR_INIT_CLASS(Xs_Index) {

	ZEPHIR_REGISTER_CLASS_EX(Xs, Index, xs, index, xs_server_ce, xs_index_method_entry, 0);

	zend_declare_property_null(xs_index_ce, SL("adds"), ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_string(xs_index_ce, SL("buf"), "", ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_long(xs_index_ce, SL("bufSize"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_bool(xs_index_ce, SL("rebuild"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Xs_Index, __destruct) {

	zephir_fcall_cache_entry *_7 = NULL;
	HashTable *_5;
	HashPosition _4;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *srv = NULL, *_0, *_1 = NULL, *_2, *_3, **_6;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("rebuild"), PH_NOISY_CC);
	if (zephir_is_true(_0)) {

		/* try_start_1: */

			ZEPHIR_CALL_METHOD(NULL, this_ptr, "endrebuild", NULL, 0);
			zephir_check_call_status_or_jump(try_end_1);

		try_end_1:

		if (EG(exception)) {
			ZEPHIR_INIT_VAR(_1);
			ZEPHIR_CPY_WRT(_1, EG(exception));
			if (zephir_instance_of_ev(_1, xs_exception_ce TSRMLS_CC)) {
				zend_clear_exception(TSRMLS_C);
			}
		}
	}
	ZEPHIR_OBS_VAR(_2);
	zephir_read_static_property_ce(&_2, xs_index_ce, SL("adds") TSRMLS_CC);
	if (Z_TYPE_P(_2) == IS_ARRAY) {
		_3 = zephir_fetch_static_property_ce(xs_index_ce, SL("adds") TSRMLS_CC);
		zephir_is_iterable(_3, &_5, &_4, 0, 0, "xs/index.zep", 25);
		for (
		  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_5, &_4)
		) {
			ZEPHIR_GET_HVALUE(srv, _6);
			ZEPHIR_CALL_METHOD(NULL, srv, "close", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(_1);
	array_init(_1);
	zephir_update_static_property_ce(xs_index_ce, SL("adds"), &_1 TSRMLS_CC);
	ZEPHIR_CALL_PARENT(NULL, xs_index_ce, this_ptr, "__destruct", &_7, 16);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Index, addServer) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *conn_param = NULL, *srv, *_0;
	zval *conn = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &conn_param);

	zephir_get_strval(conn, conn_param);


	ZEPHIR_INIT_VAR(srv);
	object_init_ex(srv, xs_server_ce);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, srv, "__construct", NULL, 17, conn, _0);
	zephir_check_call_status();
	zephir_update_static_property_array_multi_ce(xs_index_ce, SL("adds"), &srv TSRMLS_CC, SL("a"), 1);
	RETURN_CCTOR(srv);

}

PHP_METHOD(Xs_Index, execCommand) {

	HashTable *_6;
	HashPosition _5;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	long resArg, resCmd;
	zval *cmd, *resArg_param = NULL, *resCmd_param = NULL, *res = NULL, *srv = NULL, *_1 = NULL, *_2 = NULL, *_3, *_4, **_7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &cmd, &resArg_param, &resCmd_param);

	if (!resArg_param) {
		resArg = 0;
	} else {
		resArg = zephir_get_intval(resArg_param);
	}
	if (!resCmd_param) {
		resCmd = 128;
	} else {
		resCmd = zephir_get_intval(resCmd_param);
	}


	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, resArg);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, resCmd);
	ZEPHIR_CALL_PARENT(&res, xs_index_ce, this_ptr, "execcommand", &_0, 18, cmd, _1, _2);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_3);
	zephir_read_static_property_ce(&_3, xs_index_ce, SL("adds") TSRMLS_CC);
	if (Z_TYPE_P(_3) == IS_ARRAY) {
		_4 = zephir_fetch_static_property_ce(xs_index_ce, SL("adds") TSRMLS_CC);
		zephir_is_iterable(_4, &_6, &_5, 0, 0, "xs/index.zep", 50);
		for (
		  ; zephir_hash_get_current_data_ex(_6, (void**) &_7, &_5) == SUCCESS
		  ; zephir_hash_move_forward_ex(_6, &_5)
		) {
			ZEPHIR_GET_HVALUE(srv, _7);
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_LONG(_1, resArg);
			ZEPHIR_INIT_NVAR(_2);
			ZVAL_LONG(_2, resCmd);
			ZEPHIR_CALL_METHOD(NULL, srv, "execcommand", NULL, 0, cmd, _1, _2);
			zephir_check_call_status();
		}
	}
	RETURN_CCTOR(res);

}

PHP_METHOD(Xs_Index, clean) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0, *_1;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 37);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 253);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, _0, _1);
	zephir_check_call_status();
	RETURN_THIS();

}

PHP_METHOD(Xs_Index, add) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *doc, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &doc);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_BOOL(_0, 1);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "update", NULL, 0, doc, _0);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Xs_Index, update) {

	HashTable *_11, *_26, *_33, *_39, *_42;
	HashPosition _10, _25, _32, _38, _41;
	zephir_fcall_cache_entry *_6 = NULL, *_31 = NULL, *_35 = NULL, *_36 = NULL, *_44 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	long varg, wdf, wdf1, wdf2;
	zend_bool add, _2, _22;
	zval *doc, *add_param = NULL, *fid = NULL, *key = NULL, *cmd = NULL, *cmds, *field = NULL, *value = NULL, *terms = NULL, *term = NULL, *wdfVar = NULL, *text = NULL, *lastCmd = NULL, *_0 = NULL, *_1, *_3 = NULL, *_4 = NULL, *_5 = NULL, *_7, *_8 = NULL, *_9 = NULL, **_12, *_13 = NULL, *_14 = NULL, *_15 = NULL, *_16 = NULL, *_17 = NULL, *_18 = NULL, *_19 = NULL, *_20 = NULL, *_21 = NULL, *_23 = NULL, *_24 = NULL, **_27, *_28 = NULL, *_29 = NULL, *_30 = NULL, **_34, *_37 = NULL, **_40, **_43;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &doc, &add_param);

	if (!add_param) {
		add = 0;
	} else {
		add = zephir_get_boolval(add_param);
	}


	ZEPHIR_CALL_METHOD(&_0, doc, "beforesubmit", NULL, 0, this_ptr);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE_IDENTICAL(_0)) {
		RETURN_THIS();
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&fid, _1, "getfieldid", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&key, doc, "f", NULL, 0, fid);
	zephir_check_call_status();
	_2 = Z_TYPE_P(key) == IS_NULL;
	if (!(_2)) {
		_2 = ZEPHIR_IS_STRING_IDENTICAL(key, "");
	}
	if (_2) {
		ZEPHIR_INIT_VAR(_3);
		object_init_ex(_3, xs_exception_ce);
		ZEPHIR_INIT_VAR(_4);
		ZEPHIR_CONCAT_SVS(_4, "Missing value of primary key (FIELD:", fid, ")");
		ZEPHIR_CALL_METHOD(NULL, _3, "__construct", NULL, 4, _4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_3, "xs/index.zep", 79 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	ZEPHIR_INIT_NVAR(_3);
	ZVAL_LONG(_3, 163);
	ZEPHIR_INIT_VAR(_5);
	ZVAL_LONG(_5, 0);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", &_6, 19, _3, _5);
	zephir_check_call_status();
	if (!(add)) {
		ZEPHIR_INIT_ZVAL_NREF(_7);
		ZVAL_LONG(_7, 1);
		zephir_update_property_zval(cmd, SL("arg1"), _7 TSRMLS_CC);
		ZEPHIR_OBS_VAR(_8);
		zephir_read_property(&_8, fid, SL("vno"), PH_NOISY_CC);
		zephir_update_property_zval(cmd, SL("arg2"), _8 TSRMLS_CC);
		zephir_update_property_zval(cmd, SL("buf"), key TSRMLS_CC);
	}
	ZEPHIR_INIT_VAR(cmds);
	array_init(cmds);
	zephir_array_append(&cmds, cmd, PH_SEPARATE, "xs/index.zep", 89);
	_7 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_9, _7, "getallfields", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(_9, &_11, &_10, 0, 0, "xs/index.zep", 194);
	for (
	  ; zephir_hash_get_current_data_ex(_11, (void**) &_12, &_10) == SUCCESS
	  ; zephir_hash_move_forward_ex(_11, &_10)
	) {
		ZEPHIR_GET_HVALUE(field, _12);
		ZEPHIR_CALL_METHOD(&value, doc, "f", NULL, 0, field);
		zephir_check_call_status();
		if (Z_TYPE_P(value) != IS_NULL) {
			ZEPHIR_CALL_METHOD(&_13, field, "isnumeric", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(_13)) {
				varg = 0x80;
			} else {
				varg = 0;
			}
			ZEPHIR_CALL_METHOD(&_14, field, "val", NULL, 0, value);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(value, _14);
			ZEPHIR_CALL_METHOD(&_14, field, "hascustomtokenizer", NULL, 0);
			zephir_check_call_status();
			if (!(zephir_is_true(_14))) {
				ZEPHIR_CALL_METHOD(&_15, field, "withpos", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(_15)) {
					ZEPHIR_OBS_NVAR(_8);
					zephir_read_property(&_8, field, SL("weight"), PH_NOISY_CC);
					wdf = ((int) (zephir_get_numberval(_8)) | 0x40);
				} else {
					ZEPHIR_OBS_NVAR(_16);
					zephir_read_property(&_16, field, SL("weight"), PH_NOISY_CC);
					wdf = zephir_get_intval(_16);
				}
				ZEPHIR_CALL_METHOD(&_17, field, "hasindexmixed", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(_17)) {
					ZEPHIR_INIT_NVAR(_3);
					object_init_ex(_3, xs_command_ce);
					ZEPHIR_INIT_NVAR(_5);
					ZVAL_LONG(_5, 162);
					ZEPHIR_INIT_NVAR(_18);
					ZVAL_LONG(_18, wdf);
					ZEPHIR_INIT_NVAR(_19);
					ZVAL_LONG(_19, 255);
					ZEPHIR_CALL_METHOD(NULL, _3, "__construct", &_6, 19, _5, _18, _19, value);
					zephir_check_call_status();
					zephir_array_append(&cmds, _3, PH_SEPARATE, "xs/index.zep", 108);
				}
				ZEPHIR_CALL_METHOD(&_20, field, "hasindexself", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(_20)) {
					ZEPHIR_CALL_METHOD(&_21, field, "isnumeric", NULL, 0);
					zephir_check_call_status();
					if (!(zephir_is_true(_21))) {
						wdf = (wdf | 0x80);
					}
					ZEPHIR_INIT_NVAR(_5);
					object_init_ex(_5, xs_command_ce);
					ZEPHIR_OBS_NVAR(_16);
					zephir_read_property(&_16, field, SL("vno"), PH_NOISY_CC);
					ZEPHIR_INIT_NVAR(_18);
					ZVAL_LONG(_18, 162);
					ZEPHIR_INIT_NVAR(_19);
					ZVAL_LONG(_19, wdf);
					ZEPHIR_CALL_METHOD(NULL, _5, "__construct", &_6, 19, _18, _19, _16, value);
					zephir_check_call_status();
					zephir_array_append(&cmds, _5, PH_SEPARATE, "xs/index.zep", 114);
				}
				ZEPHIR_CALL_METHOD(&_21, field, "hasindexself", NULL, 0);
				zephir_check_call_status();
				_22 = !zephir_is_true(_21);
				if (!(_22)) {
					ZEPHIR_CALL_METHOD(&_23, field, "isnumeric", NULL, 0);
					zephir_check_call_status();
					_22 = zephir_is_true(_23);
				}
				if (_22) {
					ZEPHIR_INIT_NVAR(_18);
					object_init_ex(_18, xs_command_ce);
					ZEPHIR_OBS_NVAR(_16);
					zephir_read_property(&_16, field, SL("vno"), PH_NOISY_CC);
					ZEPHIR_INIT_NVAR(_19);
					ZVAL_LONG(_19, 161);
					ZEPHIR_INIT_NVAR(_24);
					ZVAL_LONG(_24, varg);
					ZEPHIR_CALL_METHOD(NULL, _18, "__construct", &_6, 19, _19, _24, _16, value);
					zephir_check_call_status();
					zephir_array_append(&cmds, _18, PH_SEPARATE, "xs/index.zep", 117);
				}
			} else {
				ZEPHIR_CALL_METHOD(&_15, field, "hasindex", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(_15)) {
					ZEPHIR_CALL_METHOD(&_17, field, "getcustomtokenizer", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&terms, _17, "gettokens", NULL, 0, value, doc);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_20, field, "hasindexself", NULL, 0);
					zephir_check_call_status();
					if (zephir_is_true(_20)) {
						ZEPHIR_CALL_METHOD(&_21, field, "isboolindex", NULL, 0);
						zephir_check_call_status();
						if (zephir_is_true(_21)) {
							wdf = 1;
						} else {
							ZEPHIR_OBS_NVAR(_16);
							zephir_read_property(&_16, field, SL("weight"), PH_NOISY_CC);
							wdf = ((int) (zephir_get_numberval(_16)) | 0x80);
						}
						zephir_is_iterable(terms, &_26, &_25, 0, 0, "xs/index.zep", 135);
						for (
						  ; zephir_hash_get_current_data_ex(_26, (void**) &_27, &_25) == SUCCESS
						  ; zephir_hash_move_forward_ex(_26, &_25)
						) {
							ZEPHIR_GET_HVALUE(term, _27);
							if (zephir_fast_strlen_ev(term) > 200) {
								continue;
							}
							ZEPHIR_INIT_NVAR(_18);
							zephir_fast_strtolower(_18, term);
							ZEPHIR_CPY_WRT(term, _18);
							ZEPHIR_INIT_NVAR(_18);
							object_init_ex(_18, xs_command_ce);
							ZEPHIR_OBS_NVAR(_28);
							zephir_read_property(&_28, field, SL("vno"), PH_NOISY_CC);
							ZEPHIR_INIT_NVAR(_19);
							ZVAL_LONG(_19, 160);
							ZEPHIR_INIT_NVAR(_24);
							ZVAL_LONG(_24, wdf);
							ZEPHIR_CALL_METHOD(NULL, _18, "__construct", &_6, 19, _19, _24, _28, term);
							zephir_check_call_status();
							zephir_array_append(&cmds, _18, PH_SEPARATE, "xs/index.zep", 133);
						}
					}
					ZEPHIR_CALL_METHOD(&_23, field, "hasindexmixed", NULL, 0);
					zephir_check_call_status();
					if (zephir_is_true(_23)) {
						ZEPHIR_INIT_NVAR(_19);
						object_init_ex(_19, xs_command_ce);
						ZEPHIR_OBS_NVAR(_28);
						zephir_read_property(&_28, field, SL("weight"), PH_NOISY_CC);
						ZEPHIR_INIT_NVAR(_24);
						zephir_fast_join_str(_24, SL(" "), terms TSRMLS_CC);
						ZEPHIR_INIT_NVAR(_29);
						ZVAL_LONG(_29, 162);
						ZEPHIR_INIT_NVAR(_30);
						ZVAL_LONG(_30, 255);
						ZEPHIR_CALL_METHOD(NULL, _19, "__construct", &_6, 19, _29, _28, _30, _24);
						zephir_check_call_status();
						zephir_array_append(&cmds, _19, PH_SEPARATE, "xs/index.zep", 138);
					}
				}
				ZEPHIR_INIT_NVAR(_18);
				object_init_ex(_18, xs_command_ce);
				ZEPHIR_OBS_NVAR(_16);
				zephir_read_property(&_16, field, SL("vno"), PH_NOISY_CC);
				ZEPHIR_INIT_NVAR(_19);
				ZVAL_LONG(_19, 161);
				ZEPHIR_INIT_NVAR(_24);
				ZVAL_LONG(_24, varg);
				ZEPHIR_CALL_METHOD(NULL, _18, "__construct", &_6, 19, _19, _24, _16, value);
				zephir_check_call_status();
				zephir_array_append(&cmds, _18, PH_SEPARATE, "xs/index.zep", 141);
			}
		}
		ZEPHIR_CALL_METHOD(&terms, doc, "getaddterms", &_31, 0, field);
		zephir_check_call_status();
		if (Z_TYPE_P(terms) != IS_NULL) {
			ZEPHIR_CALL_METHOD(&_13, field, "isboolindex", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(_13)) {
				wdf1 = 0;
			} else {
				wdf1 = 0x80;
			}
			zephir_is_iterable(terms, &_33, &_32, 0, 0, "xs/index.zep", 167);
			for (
			  ; zephir_hash_get_current_data_ex(_33, (void**) &_34, &_32) == SUCCESS
			  ; zephir_hash_move_forward_ex(_33, &_32)
			) {
				ZEPHIR_GET_HMKEY(term, _33, _32);
				ZEPHIR_GET_HVALUE(wdfVar, _34);
				ZEPHIR_INIT_NVAR(_19);
				zephir_fast_strtolower(_19, term);
				ZEPHIR_CPY_WRT(term, _19);
				if (zephir_fast_strlen_ev(term) > 200) {
					continue;
				}
				ZEPHIR_CALL_METHOD(&_14, field, "isboolindex", &_35, 0);
				zephir_check_call_status();
				if (zephir_is_true(_14)) {
					wdf2 = 1;
				} else {
					ZEPHIR_OBS_NVAR(_16);
					zephir_read_property(&_16, field, SL("weight"), PH_NOISY_CC);
					ZEPHIR_INIT_LNVAR(_4);
					mul_function(_4, wdfVar, _16 TSRMLS_CC);
					wdf2 = zephir_get_numberval(_4);
				}
				while (1) {
					if (!(wdf2 > 0x3f)) {
						break;
					}
					ZEPHIR_INIT_NVAR(_18);
					object_init_ex(_18, xs_command_ce);
					ZEPHIR_OBS_NVAR(_16);
					zephir_read_property(&_16, field, SL("vno"), PH_NOISY_CC);
					ZEPHIR_INIT_NVAR(_19);
					ZVAL_LONG(_19, 160);
					ZEPHIR_INIT_NVAR(_24);
					ZVAL_LONG(_24, (wdf1 | 0x3f));
					ZEPHIR_CALL_METHOD(NULL, _18, "__construct", &_6, 19, _19, _24, _16, term);
					zephir_check_call_status();
					zephir_array_append(&cmds, _18, PH_SEPARATE, "xs/index.zep", 162);
					wdf2 -= 0x3f;
				}
				ZEPHIR_INIT_NVAR(_18);
				object_init_ex(_18, xs_command_ce);
				ZEPHIR_OBS_NVAR(_16);
				zephir_read_property(&_16, field, SL("vno"), PH_NOISY_CC);
				ZEPHIR_INIT_NVAR(_19);
				ZVAL_LONG(_19, 160);
				ZEPHIR_INIT_NVAR(_24);
				ZVAL_LONG(_24, (wdf1 | wdf2));
				ZEPHIR_CALL_METHOD(NULL, _18, "__construct", &_6, 19, _19, _24, _16, term);
				zephir_check_call_status();
				zephir_array_append(&cmds, _18, PH_SEPARATE, "xs/index.zep", 165);
			}
		}
		ZEPHIR_CALL_METHOD(&text, doc, "getaddindex", &_36, 0, field);
		zephir_check_call_status();
		if (Z_TYPE_P(text) != IS_NULL) {
			ZEPHIR_CALL_METHOD(&_13, field, "hascustomtokenizer", NULL, 0);
			zephir_check_call_status();
			if (!(zephir_is_true(_13))) {
				ZEPHIR_CALL_METHOD(&_14, field, "withpos", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(_14)) {
					ZEPHIR_OBS_NVAR(_37);
					zephir_read_property(&_37, field, SL("weight"), PH_NOISY_CC);
					wdf = ((int) (zephir_get_numberval(_37)) | 0x40);
				} else {
					ZEPHIR_OBS_NVAR(_16);
					zephir_read_property(&_16, field, SL("weight"), PH_NOISY_CC);
					wdf = zephir_get_intval(_16);
				}
				ZEPHIR_INIT_NVAR(_18);
				object_init_ex(_18, xs_command_ce);
				ZEPHIR_OBS_NVAR(_16);
				zephir_read_property(&_16, field, SL("vno"), PH_NOISY_CC);
				ZEPHIR_INIT_NVAR(_19);
				ZVAL_LONG(_19, 162);
				ZEPHIR_INIT_NVAR(_24);
				ZVAL_LONG(_24, wdf);
				ZEPHIR_CALL_METHOD(NULL, _18, "__construct", &_6, 19, _19, _24, _16, text);
				zephir_check_call_status();
				zephir_array_append(&cmds, _18, PH_SEPARATE, "xs/index.zep", 176);
			} else {
				ZEPHIR_CALL_METHOD(&_15, field, "isboolindex", NULL, 0);
				zephir_check_call_status();
				if (zephir_is_true(_15)) {
					wdf = 1;
				} else {
					ZEPHIR_OBS_NVAR(_16);
					zephir_read_property(&_16, field, SL("weight"), PH_NOISY_CC);
					wdf = ((int) (zephir_get_numberval(_16)) | 0x80);
				}
				ZEPHIR_CALL_METHOD(&_17, field, "getcustomtokenizer", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&terms, _17, "gettokens", NULL, 0, text, doc);
				zephir_check_call_status();
				zephir_is_iterable(terms, &_39, &_38, 0, 0, "xs/index.zep", 191);
				for (
				  ; zephir_hash_get_current_data_ex(_39, (void**) &_40, &_38) == SUCCESS
				  ; zephir_hash_move_forward_ex(_39, &_38)
				) {
					ZEPHIR_GET_HVALUE(term, _40);
					if (zephir_fast_strlen_ev(term) > 200) {
						continue;
					}
					ZEPHIR_INIT_NVAR(_18);
					zephir_fast_strtolower(_18, term);
					ZEPHIR_CPY_WRT(term, _18);
					ZEPHIR_INIT_NVAR(_18);
					object_init_ex(_18, xs_command_ce);
					ZEPHIR_OBS_NVAR(_16);
					zephir_read_property(&_16, field, SL("vno"), PH_NOISY_CC);
					ZEPHIR_INIT_NVAR(_19);
					ZVAL_LONG(_19, 160);
					ZEPHIR_INIT_NVAR(_24);
					ZVAL_LONG(_24, wdf);
					ZEPHIR_CALL_METHOD(NULL, _18, "__construct", &_6, 19, _19, _24, _16, term);
					zephir_check_call_status();
					zephir_array_append(&cmds, _18, PH_SEPARATE, "xs/index.zep", 189);
				}
			}
		}
	}
	ZEPHIR_INIT_NVAR(_3);
	object_init_ex(_3, xs_command_ce);
	ZEPHIR_INIT_NVAR(_18);
	ZVAL_LONG(_18, 34);
	ZEPHIR_CALL_METHOD(NULL, _3, "__construct", &_6, 19, _18);
	zephir_check_call_status();
	zephir_array_append(&cmds, _3, PH_SEPARATE, "xs/index.zep", 194);
	_7 = zephir_fetch_nproperty_this(this_ptr, SL("bufSize"), PH_NOISY_CC);
	if (ZEPHIR_GT_LONG(_7, 0)) {
		ZEPHIR_INIT_NVAR(_18);
		zephir_fast_join_str(_18, SL(""), cmds TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendbuffer", NULL, 20, _18);
		zephir_check_call_status();
	} else {
		Z_SET_ISREF_P(cmds);
		ZEPHIR_CALL_FUNCTION(&lastCmd, "array_pop", NULL, 21, cmds);
		Z_UNSET_ISREF_P(cmds);
		zephir_check_call_status();
		zephir_is_iterable(cmds, &_42, &_41, 0, 0, "xs/index.zep", 202);
		for (
		  ; zephir_hash_get_current_data_ex(_42, (void**) &_43, &_41) == SUCCESS
		  ; zephir_hash_move_forward_ex(_42, &_41)
		) {
			ZEPHIR_GET_HVALUE(cmd, _43);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", &_44, 0, cmd);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_LONG(_3, 250);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", &_44, 0, lastCmd, _3);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, doc, "aftersubmit", NULL, 0, this_ptr);
	zephir_check_call_status();
	RETURN_THIS();

}

PHP_METHOD(Xs_Index, del) {

	zval *_15;
	HashTable *_6;
	HashPosition _5;
	zephir_fcall_cache_entry *_2 = NULL, *_12 = NULL, *_14 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *term = NULL, *field = NULL, *cmds, *terms = NULL, *_0, *_1 = NULL, *_3 = NULL, *_4 = NULL, **_7, *_8 = NULL, *_9 = NULL, *_10 = NULL, *_11 = NULL, *_13;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &term, &field);

	ZEPHIR_SEPARATE_PARAM(term);
	if (!field) {
		ZEPHIR_CPY_WRT(field, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(field);
	}
	ZEPHIR_INIT_VAR(cmds);
	array_init(cmds);


	if (Z_TYPE_P(field) == IS_NULL) {
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&field, _0, "getfieldid", NULL, 0);
		zephir_check_call_status();
	} else {
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&_1, _0, "getfield", NULL, 0, field);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(field, _1);
	}
	if (Z_TYPE_P(term) == IS_ARRAY) {
		ZEPHIR_CALL_FUNCTION(&terms, "array_unique", NULL, 22, term);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(terms);
		zephir_create_array(terms, 1, 0 TSRMLS_CC);
		zephir_array_fast_append(terms, term);
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_3, _0, "getdefaultcharset", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_4);
	ZVAL_STRING(_4, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_CE_STATIC(&_1, xs_xs_ce, "convert", &_2, 7, terms, _4, _3);
	zephir_check_temp_parameter(_4);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(terms, _1);
	zephir_is_iterable(terms, &_6, &_5, 0, 0, "xs/index.zep", 226);
	for (
	  ; zephir_hash_get_current_data_ex(_6, (void**) &_7, &_5) == SUCCESS
	  ; zephir_hash_move_forward_ex(_6, &_5)
	) {
		ZEPHIR_GET_HVALUE(term, _7);
		ZEPHIR_INIT_NVAR(_4);
		object_init_ex(_4, xs_command_ce);
		ZEPHIR_OBS_NVAR(_8);
		zephir_read_property(&_8, field, SL("vno"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(_9);
		zephir_fast_strtolower(_9, term);
		ZEPHIR_INIT_NVAR(_10);
		ZVAL_LONG(_10, 35);
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_LONG(_11, 0);
		ZEPHIR_CALL_METHOD(NULL, _4, "__construct", &_12, 19, _10, _11, _8, _9);
		zephir_check_call_status();
		zephir_array_append(&cmds, _4, PH_SEPARATE, "xs/index.zep", 224);
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("bufSize"), PH_NOISY_CC);
	if (ZEPHIR_GT_LONG(_0, 0)) {
		ZEPHIR_INIT_NVAR(_9);
		zephir_fast_join_str(_9, SL(""), cmds TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendbuffer", NULL, 20, _9);
		zephir_check_call_status();
	} else {
		if (zephir_fast_count_int(cmds TSRMLS_CC) == 1) {
			zephir_array_fetch_long(&_13, cmds, 0, PH_NOISY | PH_READONLY, "xs/index.zep", 230 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(_9);
			ZVAL_LONG(_9, 250);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", &_14, 0, _13, _9);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_VAR(_15);
			zephir_create_array(_15, 2, 0 TSRMLS_CC);
			add_assoc_long_ex(_15, SS("cmd"), 36);
			ZEPHIR_INIT_NVAR(_9);
			zephir_fast_join_str(_9, SL(""), cmds TSRMLS_CC);
			zephir_array_update_string(&_15, SL("buf"), &_9, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_NVAR(_9);
			ZVAL_LONG(_9, 250);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", &_14, 0, _15, _9);
			zephir_check_call_status();
		}
	}
	RETURN_THIS();

}

PHP_METHOD(Xs_Index, addExdata) {

	zval *_10;
	int ZEPHIR_LAST_CALL_STATUS;
	long first;
	zend_bool checkFile, _0, _1;
	zval *data_param = NULL, *checkFile_param = NULL, *dataVar, _3, _4, *_5, *_6 = NULL, *_7 = NULL, _8;
	zval *data = NULL, *_2 = NULL, *_9;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &data_param, &checkFile_param);

	zephir_get_strval(data, data_param);
	if (!checkFile_param) {
		checkFile = 1;
	} else {
		checkFile = zephir_get_boolval(checkFile_param);
	}


	_0 = zephir_fast_strlen_ev(data) < 255;
	if (_0) {
		_0 = checkFile;
	}
	_1 = _0;
	if (_1) {
		_1 = (zephir_file_exists(data TSRMLS_CC) == SUCCESS);
	}
	if (_1) {
		ZEPHIR_INIT_VAR(dataVar);
		zephir_file_get_contents(dataVar, data TSRMLS_CC);
		if (unlikely(ZEPHIR_IS_FALSE_IDENTICAL(dataVar))) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(xs_exception_ce, "Failed to read exdata from file", "xs/index.zep", 246);
			return;
		}
		zephir_get_strval(_2, dataVar);
		ZEPHIR_CPY_WRT(data, _2);
	}
	ZEPHIR_SINIT_VAR(_3);
	ZVAL_LONG(&_3, 0);
	ZEPHIR_SINIT_VAR(_4);
	ZVAL_LONG(&_4, 1);
	ZEPHIR_INIT_VAR(_5);
	zephir_substr(_5, data, 0 , 1 , 0);
	ZEPHIR_CALL_FUNCTION(&_6, "ord", NULL, 23, _5);
	zephir_check_call_status();
	first = zephir_get_intval(_6);
	do {
		if (first == 191 || first == 163 || first == 42 || first == 35 || first == 36) {
			break;
		}
		ZEPHIR_INIT_VAR(_7);
		object_init_ex(_7, xs_exception_ce);
		ZEPHIR_SINIT_VAR(_8);
		ZVAL_LONG(&_8, first);
		ZEPHIR_INIT_VAR(_9);
		ZEPHIR_CONCAT_SVS(_9, "Invalid start command of exdata (CMD:", &_8, ")");
		ZEPHIR_CALL_METHOD(NULL, _7, "__construct", NULL, 4, _9);
		zephir_check_call_status();
		zephir_throw_exception_debug(_7, "xs/index.zep", 259 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} while(0);

	ZEPHIR_INIT_VAR(_10);
	zephir_create_array(_10, 2, 0 TSRMLS_CC);
	add_assoc_long_ex(_10, SS("cmd"), 36);
	zephir_array_update_string(&_10, SL("buf"), &data, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(_7);
	ZVAL_LONG(_7, 250);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, _10, _7);
	zephir_check_call_status();
	RETURN_THIS();

}

PHP_METHOD(Xs_Index, addSynonym) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _0;
	zval *raw_param = NULL, *synonym_param = NULL, *cmd, *_1 = NULL, *_2, *_3, *_4;
	zval *raw = NULL, *synonym = NULL, *_5 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &raw_param, &synonym_param);

	zephir_get_strval(raw, raw_param);
	zephir_get_strval(synonym, synonym_param);


	_0 = !ZEPHIR_IS_STRING_IDENTICAL(raw, "");
	if (_0) {
		_0 = !ZEPHIR_IS_STRING_IDENTICAL(synonym, "");
	}
	if (_0) {
		ZEPHIR_INIT_VAR(cmd);
		object_init_ex(cmd, xs_command_ce);
		ZEPHIR_INIT_VAR(_1);
		ZVAL_LONG(_1, 42);
		ZEPHIR_INIT_VAR(_2);
		ZVAL_LONG(_2, 0);
		ZEPHIR_INIT_VAR(_3);
		ZVAL_LONG(_3, 0);
		ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _1, _2, _3, raw, synonym);
		zephir_check_call_status();
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("bufSize"), PH_NOISY_CC);
		if (ZEPHIR_GT_LONG(_4, 0)) {
			zephir_get_strval(_5, cmd);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendbuffer", NULL, 20, _5);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_LONG(_1, 250);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd, _1);
			zephir_check_call_status();
		}
	}
	RETURN_THIS();

}

PHP_METHOD(Xs_Index, delSynonym) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *raw_param = NULL, *synonym_param = NULL, *cmd, *_0 = NULL, *_1, *_2, *_3;
	zval *raw = NULL, *synonym = NULL, *_4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &raw_param, &synonym_param);

	zephir_get_strval(raw, raw_param);
	if (!synonym_param) {
		ZEPHIR_INIT_VAR(synonym);
		ZVAL_STRING(synonym, "", 1);
	} else {
		zephir_get_strval(synonym, synonym_param);
	}


	if (!ZEPHIR_IS_STRING_IDENTICAL(raw, "")) {
		ZEPHIR_INIT_VAR(cmd);
		object_init_ex(cmd, xs_command_ce);
		ZEPHIR_INIT_VAR(_0);
		ZVAL_LONG(_0, 42);
		ZEPHIR_INIT_VAR(_1);
		ZVAL_LONG(_1, 1);
		ZEPHIR_INIT_VAR(_2);
		ZVAL_LONG(_2, 0);
		ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _0, _1, _2, raw, synonym);
		zephir_check_call_status();
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("bufSize"), PH_NOISY_CC);
		if (ZEPHIR_GT_LONG(_3, 0)) {
			zephir_get_strval(_4, cmd);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendbuffer", NULL, 20, _4);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(_0);
			ZVAL_LONG(_0, 250);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, cmd, _0);
			zephir_check_call_status();
		}
	}
	RETURN_THIS();

}

PHP_METHOD(Xs_Index, setScwsMulti) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_1;
	zend_bool _0;
	zval *level_param = NULL, *_2;
	long level;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &level_param);

	level = zephir_get_intval(level_param);


	_0 = level >= 0;
	if (_0) {
		_0 = level < 16;
	}
	if (_0) {
		ZEPHIR_INIT_VAR(_1);
		zephir_create_array(_1, 3, 0 TSRMLS_CC);
		add_assoc_long_ex(_1, SS("cmd"), 198);
		add_assoc_long_ex(_1, SS("arg1"), 51);
		ZEPHIR_INIT_VAR(_2);
		ZVAL_LONG(_2, level);
		zephir_array_update_string(&_1, SL("arg2"), &_2, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, _1);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

PHP_METHOD(Xs_Index, getScwsMulti) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;
	zval *res = NULL, *_1, *_2;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	zephir_create_array(_0, 2, 0 TSRMLS_CC);
	add_assoc_long_ex(_0, SS("cmd"), 73);
	add_assoc_long_ex(_0, SS("arg1"), 5);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 200);
	ZEPHIR_CALL_METHOD(&res, this_ptr, "execcommand", NULL, 0, _0, _1);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_2);
	zephir_read_property(&_2, res, SL("buf"), PH_NOISY_CC);
	RETURN_MM_LONG(zephir_get_intval(_2));

}

PHP_METHOD(Xs_Index, openBuffer) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *size_param = NULL, *_0, *_1, *_2;
	long size;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &size_param);

	if (!size_param) {
		size = 4;
	} else {
		size = zephir_get_intval(size_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("buf"), PH_NOISY_CC);
	if (!ZEPHIR_IS_STRING_IDENTICAL(_0, "")) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("buf"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_2);
		ZVAL_BOOL(_2, 0);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "addexdata", NULL, 0, _1, _2);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_ZVAL_NREF(_1);
	ZVAL_LONG(_1, (size << 20));
	zephir_update_property_this(this_ptr, SL("bufSize"), _1 TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_1);
	ZVAL_STRING(_1, "", 1);
	zephir_update_property_this(this_ptr, SL("buf"), _1 TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(Xs_Index, closeBuffer) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 0);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "openbuffer", NULL, 0, _0);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Xs_Index, beginRebuild) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_1;
	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	zephir_create_array(_0, 2, 0 TSRMLS_CC);
	add_assoc_long_ex(_0, SS("cmd"), 40);
	add_assoc_long_ex(_0, SS("arg1"), 0);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 257);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, _0, _1);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("rebuild"), (1) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(Xs_Index, endRebuild) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_1;
	zval *_0, *_2;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("rebuild"), PH_NOISY_CC);
	if (zephir_is_true(_0)) {
		zephir_update_property_this(this_ptr, SL("rebuild"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
		ZEPHIR_INIT_VAR(_1);
		zephir_create_array(_1, 2, 0 TSRMLS_CC);
		add_assoc_long_ex(_1, SS("cmd"), 40);
		add_assoc_long_ex(_1, SS("arg1"), 1);
		ZEPHIR_INIT_VAR(_2);
		ZVAL_LONG(_2, 257);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, _1, _2);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

PHP_METHOD(Xs_Index, stopRebuild) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;
	zval *ex = NULL, *_1, *_2 = NULL;

	ZEPHIR_MM_GROW();


	/* try_start_1: */

		ZEPHIR_INIT_VAR(_0);
		zephir_create_array(_0, 2, 0 TSRMLS_CC);
		add_assoc_long_ex(_0, SS("cmd"), 40);
		add_assoc_long_ex(_0, SS("arg1"), 2);
		ZEPHIR_INIT_VAR(_1);
		ZVAL_LONG(_1, 257);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, _0, _1);
		zephir_check_call_status_or_jump(try_end_1);
		zephir_update_property_this(this_ptr, SL("rebuild"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(ex, EG(exception));
		if (zephir_instance_of_ev(ex, xs_exception_ce TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CALL_METHOD(&_2, ex, "getcode", NULL, 0);
			zephir_check_call_status();
			if (!ZEPHIR_IS_LONG_IDENTICAL(_2, 450)) {
				zephir_throw_exception_debug(ex, "xs/index.zep", 351 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	RETURN_THIS();

}

PHP_METHOD(Xs_Index, setDb) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;
	zval *name_param = NULL, *_1;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(_0);
	zephir_create_array(_0, 2, 0 TSRMLS_CC);
	add_assoc_long_ex(_0, SS("cmd"), 32);
	zephir_array_update_string(&_0, SL("buf"), &name, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 251);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, _0, _1);
	zephir_check_call_status();
	RETURN_THIS();

}

PHP_METHOD(Xs_Index, flushLogging) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *ex = NULL, *_0, *_1, *_2 = NULL;

	ZEPHIR_MM_GROW();


	/* try_start_1: */

		ZEPHIR_INIT_VAR(_0);
		ZVAL_LONG(_0, 41);
		ZEPHIR_INIT_VAR(_1);
		ZVAL_LONG(_1, 258);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, _0, _1);
		zephir_check_call_status_or_jump(try_end_1);

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(ex, EG(exception));
		if (zephir_instance_of_ev(ex, xs_exception_ce TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CALL_METHOD(&_2, ex, "getcode", NULL, 0);
			zephir_check_call_status();
			if (ZEPHIR_IS_LONG_IDENTICAL(_2, 504)) {
				RETURN_MM_BOOL(0);
			}
			zephir_throw_exception_debug(ex, "xs/index.zep", 373 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	RETURN_MM_BOOL(1);

}

PHP_METHOD(Xs_Index, flushIndex) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *ex = NULL, *_0, *_1, *_2 = NULL;

	ZEPHIR_MM_GROW();


	/* try_start_1: */

		ZEPHIR_INIT_VAR(_0);
		ZVAL_LONG(_0, 39);
		ZEPHIR_INIT_VAR(_1);
		ZVAL_LONG(_1, 256);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, _0, _1);
		zephir_check_call_status_or_jump(try_end_1);

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(ex, EG(exception));
		if (zephir_instance_of_ev(ex, xs_exception_ce TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CALL_METHOD(&_2, ex, "getcode", NULL, 0);
			zephir_check_call_status();
			do {
				if (ZEPHIR_IS_LONG(_2, 504) || ZEPHIR_IS_LONG(_2, 406)) {
					RETURN_MM_BOOL(0);
				}
			} while(0);

			zephir_throw_exception_debug(ex, "xs/index.zep", 390 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	RETURN_MM_BOOL(1);

}

PHP_METHOD(Xs_Index, getCustomDict) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *res = NULL, *_0, *_1, *_2;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 43);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 200);
	ZEPHIR_CALL_METHOD(&res, this_ptr, "execcommand", NULL, 0, _0, _1);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_2);
	zephir_read_property(&_2, res, SL("buf"), PH_NOISY_CC);
	RETURN_CCTOR(_2);

}

PHP_METHOD(Xs_Index, setCustomDict) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;
	zval *content_param = NULL, *_1;
	zval *content = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &content_param);

	zephir_get_strval(content, content_param);


	ZEPHIR_INIT_VAR(_0);
	zephir_create_array(_0, 3, 0 TSRMLS_CC);
	add_assoc_long_ex(_0, SS("cmd"), 43);
	add_assoc_long_ex(_0, SS("arg1"), 1);
	zephir_array_update_string(&_0, SL("buf"), &content, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 259);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, _0, _1);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Index, close) {

	zephir_fcall_cache_entry *_0 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *ioerr = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &ioerr);

	if (!ioerr) {
		ioerr = ZEPHIR_GLOBAL(global_false);
	}


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "closebuffer", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_PARENT(NULL, xs_index_ce, this_ptr, "close", &_0, 24, ioerr);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Index, appendBuffer) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *buf_param = NULL, *_0, *_1, *_2, *_3, *_4;
	zval *buf = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &buf_param);

	zephir_get_strval(buf, buf_param);


	zephir_update_property_this(this_ptr, SL("buf"), buf TSRMLS_CC);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("buf"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("bufSize"), PH_NOISY_CC);
	if (ZEPHIR_LE_LONG(_1, zephir_fast_strlen_ev(_0))) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("buf"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_3);
		ZVAL_BOOL(_3, 0);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "addexdata", NULL, 0, _2, _3);
		zephir_check_call_status();
		ZEPHIR_INIT_ZVAL_NREF(_4);
		ZVAL_STRING(_4, "", 1);
		zephir_update_property_this(this_ptr, SL("buf"), _4 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

