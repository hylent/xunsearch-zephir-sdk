
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
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "kernel/concat.h"
#include "kernel/hash.h"
#include "kernel/array.h"
#include "kernel/string.h"


ZEPHIR_INIT_CLASS(Xs_TokenizerScws) {

	ZEPHIR_REGISTER_CLASS(Xs, TokenizerScws, xs, tokenizerscws, xs_tokenizerscws_method_entry, 0);

	zend_declare_property_null(xs_tokenizerscws_ce, SL("charset"), ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(xs_tokenizerscws_ce, SL("server"), ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(xs_tokenizerscws_ce, SL("setting"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_class_constant_long(xs_tokenizerscws_ce, SL("MULTI_MASK"), 15 TSRMLS_CC);

	zend_declare_class_constant_long(xs_tokenizerscws_ce, SL("MULTI_NONE"), 0 TSRMLS_CC);

	zend_declare_class_constant_long(xs_tokenizerscws_ce, SL("MULTI_SHORT"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(xs_tokenizerscws_ce, SL("MULTI_DUALITY"), 2 TSRMLS_CC);

	zend_declare_class_constant_long(xs_tokenizerscws_ce, SL("MULTI_ZMAIN"), 4 TSRMLS_CC);

	zend_declare_class_constant_long(xs_tokenizerscws_ce, SL("MULTI_ZALL"), 8 TSRMLS_CC);

	zend_declare_class_constant_long(xs_tokenizerscws_ce, SL("XDICT_XDB"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(xs_tokenizerscws_ce, SL("XDICT_MEM"), 2 TSRMLS_CC);

	zend_declare_class_constant_long(xs_tokenizerscws_ce, SL("XDICT_TXT"), 4 TSRMLS_CC);

	zend_class_implements(xs_tokenizerscws_ce TSRMLS_CC, 1, xs_tokenizer_ce);
	return SUCCESS;

}

PHP_METHOD(Xs_TokenizerScws, __construct) {

	zend_bool _6;
	zval *_3;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	zval *arg = NULL, *xs = NULL, *_0, *_2 = NULL, *_4 = NULL, *_5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &arg);

	if (!arg) {
		arg = ZEPHIR_GLOBAL(global_null);
	}


	_0 = zephir_fetch_static_property_ce(xs_tokenizerscws_ce, SL("server") TSRMLS_CC);
	if (Z_TYPE_P(_0) == IS_NULL) {
		ZEPHIR_CALL_CE_STATIC(&xs, xs_xs_ce, "getlastxs", &_1, 61);
		zephir_check_call_status();
		if (Z_TYPE_P(xs) == IS_NULL) {
			ZEPHIR_INIT_VAR(_2);
			object_init_ex(_2, xs_exception_ce);
			ZEPHIR_INIT_VAR(_3);
			ZEPHIR_CONCAT_SS(_3, "An Xs instance should be created before using ", "Xs\\TokenizerScws");
			ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL, 4, _3);
			zephir_check_call_status();
			zephir_throw_exception_debug(_2, "xs/tokenizerscws.zep", 28 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&_4, xs, "getscwsserver", NULL, 0);
		zephir_check_call_status();
		zephir_update_static_property_ce(xs_tokenizerscws_ce, SL("server"), &_4 TSRMLS_CC);
		_5 = zephir_fetch_static_property_ce(xs_tokenizerscws_ce, SL("server") TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_LONG(_2, 0);
		ZEPHIR_CALL_METHOD(NULL, _5, "settimeout", NULL, 0, _2);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4, xs, "getdefaultcharset", NULL, 0);
		zephir_check_call_status();
		zephir_update_static_property_ce(xs_tokenizerscws_ce, SL("charset"), &_4 TSRMLS_CC);
	}
	_6 = Z_TYPE_P(arg) != IS_NULL;
	if (_6) {
		_6 = !ZEPHIR_IS_STRING_IDENTICAL(arg, "");
	}
	if (_6) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setmulti", NULL, 0, arg);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_TokenizerScws, getTokens) {

	HashTable *_4;
	HashPosition _3;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *value_param = NULL, *doc = NULL, *tokens, *words = NULL, *word = NULL, *_0, *_1, *_2, **_5, *_6;
	zval *value = NULL, *charset = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &value_param, &doc);

	zephir_get_strval(value, value_param);
	if (!doc) {
		doc = ZEPHIR_GLOBAL(global_null);
	}
	ZEPHIR_INIT_VAR(tokens);
	array_init(tokens);


	ZEPHIR_INIT_VAR(_0);
	ZVAL_BOOL(_0, 1);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setignore", NULL, 0, _0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_1);
	zephir_read_static_property_ce(&_1, xs_tokenizerscws_ce, SL("charset") TSRMLS_CC);
	zephir_get_strval(charset, _1);
	ZEPHIR_INIT_ZVAL_NREF(_2);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "UTF-8", 1);
	zephir_update_static_property_ce(xs_tokenizerscws_ce, SL("charset"), &_2 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&words, this_ptr, "getresult", NULL, 0, value);
	zephir_check_call_status();
	zephir_is_iterable(words, &_4, &_3, 0, 0, "xs/tokenizerscws.zep", 51);
	for (
	  ; zephir_hash_get_current_data_ex(_4, (void**) &_5, &_3) == SUCCESS
	  ; zephir_hash_move_forward_ex(_4, &_3)
	) {
		ZEPHIR_GET_HVALUE(word, _5);
		zephir_array_fetch_string(&_6, word, SL("word"), PH_NOISY | PH_READONLY, "xs/tokenizerscws.zep", 49 TSRMLS_CC);
		zephir_array_append(&tokens, _6, PH_SEPARATE, "xs/tokenizerscws.zep", 49);
	}
	zephir_update_static_property_ce(xs_tokenizerscws_ce, SL("charset"), &charset TSRMLS_CC);
	RETURN_CCTOR(tokens);

}

PHP_METHOD(Xs_TokenizerScws, setCharset) {

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
		ZEPHIR_INIT_VAR(_1);
		ZVAL_STRING(_1, "UTF-8", 1);
		zephir_update_static_property_ce(xs_tokenizerscws_ce, SL("charset"), &_1 TSRMLS_CC);
	} else {
		zephir_update_static_property_ce(xs_tokenizerscws_ce, SL("charset"), &charset TSRMLS_CC);
	}
	RETURN_THIS();

}

PHP_METHOD(Xs_TokenizerScws, setIgnore) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *yes_param = NULL, *_0, *_1 = NULL, *_2 = NULL, *_3;
	zend_bool yes;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &yes_param);

	if (!yes_param) {
		yes = 1;
	} else {
		yes = zephir_get_boolval(yes_param);
	}


	ZEPHIR_INIT_VAR(_0);
	object_init_ex(_0, xs_command_ce);
	ZEPHIR_INIT_VAR(_1);
	if (yes) {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_LONG(_1, 1);
	} else {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_LONG(_1, 0);
	}
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, 198);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 50);
	ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, 19, _2, _3, _1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_2);
	ZVAL_STRING(_2, "ignore", 1);
	zephir_update_property_array(this_ptr, SL("setting"), _2, _0 TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(Xs_TokenizerScws, setMulti) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *mode_param = NULL, *_0, *_1 = NULL, *_2, *_3;
	long mode;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &mode_param);

	if (!mode_param) {
		mode = 3;
	} else {
		mode = zephir_get_intval(mode_param);
	}


	mode = (mode & 15);
	ZEPHIR_INIT_VAR(_0);
	object_init_ex(_0, xs_command_ce);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 198);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, 51);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, mode);
	ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, 19, _1, _2, _3);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "multi", 1);
	zephir_update_property_array(this_ptr, SL("setting"), _1, _0 TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(Xs_TokenizerScws, setDict) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *fpath_param = NULL, *mode = NULL, _0, *_1 = NULL, *_2, *_3 = NULL, *_4, *_5;
	zval *fpath = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &fpath_param, &mode);

	zephir_get_strval(fpath, fpath_param);
	if (!mode) {
		ZEPHIR_CPY_WRT(mode, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(mode);
	}


	if (Z_TYPE_P(mode) != IS_LONG) {
		ZEPHIR_SINIT_VAR(_0);
		ZVAL_STRING(&_0, ".txt", 0);
		ZEPHIR_CALL_FUNCTION(&_1, "stripos", NULL, 62, fpath, &_0);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(mode);
		if (ZEPHIR_IS_FALSE_IDENTICAL(_1)) {
			ZVAL_LONG(mode, 1);
		} else {
			ZVAL_LONG(mode, 4);
		}
	}
	ZEPHIR_INIT_VAR(_2);
	object_init_ex(_2, xs_command_ce);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 198);
	ZEPHIR_INIT_VAR(_4);
	ZVAL_LONG(_4, 53);
	ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL, 19, _3, _4, mode, fpath);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_3);
	ZVAL_STRING(_3, "set_dict", 1);
	zephir_update_property_array(this_ptr, SL("setting"), _3, _2 TSRMLS_CC);
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("setting"), PH_NOISY_CC);
	zephir_array_unset_string(&_5, SS("add_dict"), PH_SEPARATE);
	RETURN_THIS();

}

PHP_METHOD(Xs_TokenizerScws, addDict) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *fpath_param = NULL, *mode = NULL, _0, *_1 = NULL, *_2, *_3, *_4;
	zval *fpath = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &fpath_param, &mode);

	zephir_get_strval(fpath, fpath_param);
	if (!mode) {
		ZEPHIR_CPY_WRT(mode, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(mode);
	}


	if (Z_TYPE_P(mode) != IS_LONG) {
		ZEPHIR_SINIT_VAR(_0);
		ZVAL_STRING(&_0, ".txt", 0);
		ZEPHIR_CALL_FUNCTION(&_1, "stripos", NULL, 62, fpath, &_0);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(mode);
		if (ZEPHIR_IS_FALSE_IDENTICAL(_1)) {
			ZVAL_LONG(mode, 1);
		} else {
			ZVAL_LONG(mode, 4);
		}
	}
	ZEPHIR_INIT_VAR(_2);
	object_init_ex(_2, xs_command_ce);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 198);
	ZEPHIR_INIT_VAR(_4);
	ZVAL_LONG(_4, 54);
	ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL, 19, _3, _4, mode, fpath);
	zephir_check_call_status();
	zephir_update_property_array_multi(this_ptr, SL("setting"), &_2 TSRMLS_CC, SL("sa"), 2, SL("add_dict"));
	RETURN_THIS();

}

PHP_METHOD(Xs_TokenizerScws, setDuality) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *yes_param = NULL, *_0, *_1 = NULL, *_2 = NULL, *_3;
	zend_bool yes;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &yes_param);

	if (!yes_param) {
		yes = 1;
	} else {
		yes = zephir_get_boolval(yes_param);
	}


	ZEPHIR_INIT_VAR(_0);
	object_init_ex(_0, xs_command_ce);
	ZEPHIR_INIT_VAR(_1);
	if (yes) {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_LONG(_1, 1);
	} else {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_LONG(_1, 0);
	}
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, 198);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 52);
	ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, 19, _2, _3, _1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_2);
	ZVAL_STRING(_2, "duality", 1);
	zephir_update_property_array(this_ptr, SL("setting"), _2, _0 TSRMLS_CC);
	RETURN_THIS();

}

PHP_METHOD(Xs_TokenizerScws, getVersion) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *cmd, *res = NULL, *_0 = NULL, *_1, *_2, *_3;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 73);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 1);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _0, _1);
	zephir_check_call_status();
	_2 = zephir_fetch_static_property_ce(xs_tokenizerscws_ce, SL("server") TSRMLS_CC);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 200);
	ZEPHIR_CALL_METHOD(&res, _2, "execcommand", NULL, 0, cmd, _0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_3);
	zephir_read_property(&_3, res, SL("buf"), PH_NOISY_CC);
	RETURN_CCTOR(_3);

}

PHP_METHOD(Xs_TokenizerScws, getResult) {

	zephir_fcall_cache_entry *_8 = NULL, *_10 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *text_param = NULL, *words, *cmd, *res = NULL, *tmp = NULL, *_0 = NULL, *_1 = NULL, *_2, *_3, *_4, *_5 = NULL, *_6 = NULL, _7 = zval_used_for_init, *_9 = NULL, *_11, *_12, *_13;
	zval *text = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &text_param);

	zephir_get_strval(text, text_param);
	ZEPHIR_INIT_VAR(words);
	array_init(words);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "applysetting", NULL, 63, text);
	zephir_check_call_status();
	zephir_get_strval(text, _0);
	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 73);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, 2);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 0);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _1, _2, _3, text);
	zephir_check_call_status();
	_4 = zephir_fetch_static_property_ce(xs_tokenizerscws_ce, SL("server") TSRMLS_CC);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_LONG(_1, 290);
	ZEPHIR_CALL_METHOD(&res, _4, "execcommand", NULL, 0, cmd, _1);
	zephir_check_call_status();
	while (1) {
		ZEPHIR_OBS_NVAR(_5);
		zephir_read_property(&_5, res, SL("buf"), PH_NOISY_CC);
		if (!(!ZEPHIR_IS_STRING_IDENTICAL(_5, ""))) {
			break;
		}
		ZEPHIR_OBS_NVAR(_6);
		zephir_read_property(&_6, res, SL("buf"), PH_NOISY_CC);
		ZEPHIR_SINIT_NVAR(_7);
		ZVAL_STRING(&_7, "Ioff/a4attr/a*word", 0);
		ZEPHIR_CALL_FUNCTION(&tmp, "unpack", &_8, 5, &_7, _6);
		zephir_check_call_status();
		zephir_array_fetch_string(&_11, tmp, SL("word"), PH_NOISY | PH_READONLY, "xs/tokenizerscws.zep", 130 TSRMLS_CC);
		_12 = zephir_fetch_static_property_ce(xs_tokenizerscws_ce, SL("charset") TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_9, xs_xs_ce, "convert", &_10, 0, _11, _12, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
		zephir_array_update_string(&tmp, SL("word"), &_9, PH_COPY | PH_SEPARATE);
		zephir_array_append(&words, tmp, PH_SEPARATE, "xs/tokenizerscws.zep", 131);
		_13 = zephir_fetch_static_property_ce(xs_tokenizerscws_ce, SL("server") TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&res, _13, "getrespond", NULL, 0);
		zephir_check_call_status();
	}
	RETURN_CCTOR(words);

}

PHP_METHOD(Xs_TokenizerScws, getTops) {

	zephir_fcall_cache_entry *_8 = NULL, *_10 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	long limit;
	zval *text_param = NULL, *limit_param = NULL, *xattr_param = NULL, *words, *cmd, *res = NULL, *tmp = NULL, *_0 = NULL, *_1 = NULL, *_2, *_3, *_4, *_5 = NULL, *_6 = NULL, _7 = zval_used_for_init, *_9 = NULL, *_11, *_12, *_13;
	zval *text = NULL, *xattr = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &text_param, &limit_param, &xattr_param);

	zephir_get_strval(text, text_param);
	if (!limit_param) {
		limit = 10;
	} else {
		limit = zephir_get_intval(limit_param);
	}
	if (!xattr_param) {
		ZEPHIR_INIT_VAR(xattr);
		ZVAL_STRING(xattr, "", 1);
	} else {
		zephir_get_strval(xattr, xattr_param);
	}
	ZEPHIR_INIT_VAR(words);
	array_init(words);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "applysetting", NULL, 63, text);
	zephir_check_call_status();
	zephir_get_strval(text, _0);
	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 73);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, 3);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, limit);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _1, _2, _3, text, xattr);
	zephir_check_call_status();
	_4 = zephir_fetch_static_property_ce(xs_tokenizerscws_ce, SL("server") TSRMLS_CC);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_LONG(_1, 291);
	ZEPHIR_CALL_METHOD(&res, _4, "execcommand", NULL, 0, cmd, _1);
	zephir_check_call_status();
	while (1) {
		ZEPHIR_OBS_NVAR(_5);
		zephir_read_property(&_5, res, SL("buf"), PH_NOISY_CC);
		if (!(!ZEPHIR_IS_STRING_IDENTICAL(_5, ""))) {
			break;
		}
		ZEPHIR_OBS_NVAR(_6);
		zephir_read_property(&_6, res, SL("buf"), PH_NOISY_CC);
		ZEPHIR_SINIT_NVAR(_7);
		ZVAL_STRING(&_7, "Itimes/a4attr/a*word", 0);
		ZEPHIR_CALL_FUNCTION(&tmp, "unpack", &_8, 5, &_7, _6);
		zephir_check_call_status();
		zephir_array_fetch_string(&_11, tmp, SL("word"), PH_NOISY | PH_READONLY, "xs/tokenizerscws.zep", 146 TSRMLS_CC);
		_12 = zephir_fetch_static_property_ce(xs_tokenizerscws_ce, SL("charset") TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_CE_STATIC(&_9, xs_xs_ce, "convert", &_10, 0, _11, _12, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
		zephir_array_update_string(&tmp, SL("word"), &_9, PH_COPY | PH_SEPARATE);
		zephir_array_append(&words, tmp, PH_SEPARATE, "xs/tokenizerscws.zep", 147);
		_13 = zephir_fetch_static_property_ce(xs_tokenizerscws_ce, SL("server") TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&res, _13, "getrespond", NULL, 0);
		zephir_check_call_status();
	}
	RETURN_CCTOR(words);

}

PHP_METHOD(Xs_TokenizerScws, hasWord) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *text_param = NULL, *xattr_param = NULL, *cmd, *res = NULL, *_0 = NULL, *_1 = NULL, *_2, *_3, *_4, *_5;
	zval *text = NULL, *xattr = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &text_param, &xattr_param);

	zephir_get_strval(text, text_param);
	zephir_get_strval(xattr, xattr_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "applysetting", NULL, 63, text);
	zephir_check_call_status();
	zephir_get_strval(text, _0);
	ZEPHIR_INIT_VAR(cmd);
	object_init_ex(cmd, xs_command_ce);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 73);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, 4);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 0);
	ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _1, _2, _3, text, xattr);
	zephir_check_call_status();
	_4 = zephir_fetch_static_property_ce(xs_tokenizerscws_ce, SL("server") TSRMLS_CC);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_LONG(_1, 200);
	ZEPHIR_CALL_METHOD(&res, _4, "execcommand", NULL, 0, cmd, _1);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_5);
	zephir_read_property(&_5, res, SL("buf"), PH_NOISY_CC);
	RETURN_MM_BOOL(ZEPHIR_IS_STRING_IDENTICAL(_5, "OK"));

}

PHP_METHOD(Xs_TokenizerScws, applySetting) {

	zephir_fcall_cache_entry *_10 = NULL;
	HashTable *_4, *_7;
	HashPosition _3, _6;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *text_param = NULL, *cmd = NULL, *c = NULL, *_0, *_1, *_2, **_5, **_8, *_9, *_11;
	zval *text = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &text_param);

	zephir_get_strval(text, text_param);


	_0 = zephir_fetch_static_property_ce(xs_tokenizerscws_ce, SL("server") TSRMLS_CC);
	ZEPHIR_CALL_METHOD(NULL, _0, "reopen", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_1);
	zephir_read_property_this(&_1, this_ptr, SL("setting"), PH_NOISY_CC);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("setting"), PH_NOISY_CC);
		zephir_is_iterable(_2, &_4, &_3, 0, 0, "xs/tokenizerscws.zep", 178);
		for (
		  ; zephir_hash_get_current_data_ex(_4, (void**) &_5, &_3) == SUCCESS
		  ; zephir_hash_move_forward_ex(_4, &_3)
		) {
			ZEPHIR_GET_HVALUE(cmd, _5);
			if (Z_TYPE_P(cmd) == IS_ARRAY) {
				zephir_is_iterable(cmd, &_7, &_6, 0, 0, "xs/tokenizerscws.zep", 174);
				for (
				  ; zephir_hash_get_current_data_ex(_7, (void**) &_8, &_6) == SUCCESS
				  ; zephir_hash_move_forward_ex(_7, &_6)
				) {
					ZEPHIR_GET_HVALUE(c, _8);
					_9 = zephir_fetch_static_property_ce(xs_tokenizerscws_ce, SL("server") TSRMLS_CC);
					ZEPHIR_CALL_METHOD(NULL, _9, "execcommand", NULL, 0, c);
					zephir_check_call_status();
				}
			} else {
				_9 = zephir_fetch_static_property_ce(xs_tokenizerscws_ce, SL("server") TSRMLS_CC);
				ZEPHIR_CALL_METHOD(NULL, _9, "execcommand", NULL, 0, cmd);
				zephir_check_call_status();
			}
		}
	}
	_2 = zephir_fetch_static_property_ce(xs_tokenizerscws_ce, SL("charset") TSRMLS_CC);
	ZEPHIR_INIT_VAR(_11);
	ZVAL_STRING(_11, "UTF-8", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_RETURN_CALL_CE_STATIC(xs_xs_ce, "convert", &_10, 7, text, _11, _2);
	zephir_check_temp_parameter(_11);
	zephir_check_call_status();
	RETURN_MM();

}

