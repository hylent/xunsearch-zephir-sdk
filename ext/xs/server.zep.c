
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
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/file.h"
#include "kernel/concat.h"
#include "kernel/array.h"
#include "kernel/exception.h"


ZEPHIR_INIT_CLASS(Xs_Server) {

	ZEPHIR_REGISTER_CLASS_EX(Xs, Server, xs, server, xs_component_ce, xs_server_method_entry, 0);

	zend_declare_property_null(xs_server_ce, SL("xs"), ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(xs_server_ce, SL("sock"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(xs_server_ce, SL("conn"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(xs_server_ce, SL("flag"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(xs_server_ce, SL("project"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(xs_server_ce, SL("sendBuffer"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_class_constant_long(xs_server_ce, SL("FILE"), 0x01 TSRMLS_CC);

	zend_declare_class_constant_long(xs_server_ce, SL("BROKEN"), 0x02 TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Xs_Server, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *conn_param = NULL, *xs = NULL, *_0 = NULL;
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


	zephir_update_property_this(this_ptr, SL("xs"), xs TSRMLS_CC);
	if (zephir_fast_strlen_ev(conn) > 0) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "open", NULL, 0, conn);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Server, __destruct) {

	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	zephir_update_property_this(this_ptr, SL("xs"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "close", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Server, open) {

	zend_bool _3;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *conn_param = NULL, *_0, *_1, *_2, *_4, *_5 = NULL;
	zval *conn = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &conn_param);

	zephir_get_strval(conn, conn_param);


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "close", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("conn"), conn TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, 0x02);
	zephir_update_property_this(this_ptr, SL("flag"), _0 TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_STRING(_0, "", 1);
	zephir_update_property_this(this_ptr, SL("sendBuffer"), _0 TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("project"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "connect", NULL, 0);
	zephir_check_call_status();
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
	ZEPHIR_INIT_ZVAL_NREF(_1);
	ZVAL_LONG(_1, ((int) (zephir_get_numberval(_0)) ^ 0x02));
	zephir_update_property_this(this_ptr, SL("flag"), _1 TSRMLS_CC);
	ZEPHIR_OBS_VAR(_2);
	zephir_read_property_this(&_2, this_ptr, SL("xs"), PH_NOISY_CC);
	_3 = Z_TYPE_P(_2) == IS_OBJECT;
	if (_3) {
		ZEPHIR_OBS_VAR(_4);
		zephir_read_property_this(&_4, this_ptr, SL("xs"), PH_NOISY_CC);
		_3 = zephir_instance_of_ev(_4, xs_xs_ce TSRMLS_CC);
	}
	if (_3) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("xs"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&_5, _1, "getname", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setproject", NULL, 0, _5);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Server, reopen) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *force_param = NULL, *_0, *_2;
	zend_bool force, _1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &force_param);

	if (!force_param) {
		force = 0;
	} else {
		force = zephir_get_boolval(force_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
	_1 = ((((int) (zephir_get_numberval(_0)) & 0x02))) ? 1 : 0;
	if (!(_1)) {
		_1 = force;
	}
	if (_1) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("conn"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "open", NULL, 0, _2);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

PHP_METHOD(Xs_Server, close) {

	zval *_9 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *ioerr_param = NULL, *cmd, *_0, *_2, *_4, *_5, *_6, *_8, *_10;
	zend_bool ioerr, _1, _3, _7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &ioerr_param);

	if (!ioerr_param) {
		ioerr = 0;
	} else {
		ioerr = zephir_get_boolval(ioerr_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("sock"), PH_NOISY_CC);
	_1 = zephir_is_true(_0);
	if (_1) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
		_1 = !((((int) (zephir_get_numberval(_2)) & 0x02)));
	}
	if (_1) {
		_3 = !ioerr;
		if (_3) {
			_4 = zephir_fetch_nproperty_this(this_ptr, SL("sendBuffer"), PH_NOISY_CC);
			_3 = !ZEPHIR_IS_STRING_IDENTICAL(_4, "");
		}
		if (_3) {
			_5 = zephir_fetch_nproperty_this(this_ptr, SL("sendBuffer"), PH_NOISY_CC);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, _5);
			zephir_check_call_status();
			ZEPHIR_INIT_ZVAL_NREF(_6);
			ZVAL_STRING(_6, "", 1);
			zephir_update_property_this(this_ptr, SL("sendBuffer"), _6 TSRMLS_CC);
		}
		_7 = !ioerr;
		if (_7) {
			_5 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
			_7 = !((((int) (zephir_get_numberval(_5)) & 0x01)));
		}
		if (_7) {
			ZEPHIR_INIT_VAR(cmd);
			object_init_ex(cmd, xs_command_ce);
			ZEPHIR_INIT_VAR(_8);
			ZVAL_LONG(_8, 4);
			ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, _8);
			zephir_check_call_status();
			_6 = zephir_fetch_nproperty_this(this_ptr, SL("sock"), PH_NOISY_CC);
			zephir_get_strval(_9, cmd);
			zephir_fwrite(NULL, _6, _9 TSRMLS_CC);
		}
		_5 = zephir_fetch_nproperty_this(this_ptr, SL("sock"), PH_NOISY_CC);
		zephir_fclose(_5 TSRMLS_CC);
		_6 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
		ZEPHIR_INIT_ZVAL_NREF(_10);
		ZVAL_LONG(_10, ((int) (zephir_get_numberval(_6)) | 0x02));
		zephir_update_property_this(this_ptr, SL("flag"), _10 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Server, getConnString) {

	zval *_0, _2, *_3;
	zval *str = NULL, *_1 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("conn"), PH_NOISY_CC);
	zephir_get_strval(_1, _0);
	ZEPHIR_CPY_WRT(str, _1);
	if (zephir_is_numeric(str)) {
		ZEPHIR_CONCAT_SV(return_value, "localhost:", str);
		RETURN_MM();
	}
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_STRING(&_2, ":", 0);
	ZEPHIR_INIT_VAR(_3);
	zephir_fast_strpos(_3, str, &_2, 0 );
	if (ZEPHIR_IS_FALSE_IDENTICAL(_3)) {
		ZEPHIR_CONCAT_SV(return_value, "unix://", str);
		RETURN_MM();
	}
	RETURN_CTOR(str);

}

PHP_METHOD(Xs_Server, getSocket) {


	RETURN_MEMBER(this_ptr, "sock");

}

PHP_METHOD(Xs_Server, getProject) {


	RETURN_MEMBER(this_ptr, "project");

}

PHP_METHOD(Xs_Server, setProject) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_1;
	zval *name_param = NULL, *home_param = NULL, *_0, *_2;
	zval *name = NULL, *home = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name_param, &home_param);

	zephir_get_strval(name, name_param);
	if (!home_param) {
		ZEPHIR_INIT_VAR(home);
		ZVAL_STRING(home, "", 1);
	} else {
		zephir_get_strval(home, home_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("project"), PH_NOISY_CC);
	if (!ZEPHIR_IS_IDENTICAL(name, _0)) {
		ZEPHIR_INIT_VAR(_1);
		zephir_create_array(_1, 3, 0 TSRMLS_CC);
		add_assoc_long_ex(_1, SS("cmd"), 1);
		zephir_array_update_string(&_1, SL("buf"), &name, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_1, SL("buf1"), &home, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(_2);
		ZVAL_LONG(_2, 201);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, _1, _2);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("project"), name TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Server, setTimeout) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0;
	zval *sec_param = NULL, *_1 = NULL;
	long sec;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &sec_param);

	sec = zephir_get_intval(sec_param);


	ZEPHIR_INIT_VAR(_0);
	zephir_create_array(_0, 2, 0 TSRMLS_CC);
	add_assoc_long_ex(_0, SS("cmd"), 3);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, sec);
	zephir_array_update_string(&_0, SL("arg"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_LONG(_1, 208);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "execcommand", NULL, 0, _0, _1);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Server, execCommand) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _0, _9, _13, _14;
	zval *buf = NULL, *_3 = NULL, *_4 = NULL, *_5;
	long resArg, resCmd;
	zval *cmdArg, *resArg_param = NULL, *resCmd_param = NULL, *cmd = NULL, *res = NULL, *_1, *_2 = NULL, *_6, *_7, *_8, *_10 = NULL, *_11 = NULL, *_12 = NULL, *_15 = NULL, *_16;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &cmdArg, &resArg_param, &resCmd_param);

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


	_0 = Z_TYPE_P(cmdArg) == IS_OBJECT;
	if (_0) {
		_0 = (zephir_instance_of_ev(cmdArg, xs_command_ce TSRMLS_CC));
	}
	if (_0) {
		ZEPHIR_CPY_WRT(cmd, cmdArg);
	} else {
		ZEPHIR_INIT_NVAR(cmd);
		object_init_ex(cmd, xs_command_ce);
		ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, cmdArg);
		zephir_check_call_status();
	}
	ZEPHIR_OBS_VAR(_1);
	zephir_read_property(&_1, cmd, SL("cmd"), PH_NOISY_CC);
	if (((int) (zephir_get_numberval(_1)) & 0x80)) {
		ZEPHIR_OBS_VAR(_2);
		zephir_read_property_this(&_2, this_ptr, SL("sendBuffer"), PH_NOISY_CC);
		zephir_get_strval(_3, _2);
		zephir_get_strval(_4, cmd);
		ZEPHIR_INIT_VAR(_5);
		ZEPHIR_CONCAT_VV(_5, _3, _4);
		zephir_update_property_this(this_ptr, SL("sendBuffer"), _5 TSRMLS_CC);
		RETURN_MM_BOOL(1);
	}
	_6 = zephir_fetch_nproperty_this(this_ptr, SL("sendBuffer"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_7);
	ZEPHIR_CONCAT_VV(_7, _6, cmd);
	zephir_get_strval(buf, _7);
	ZEPHIR_INIT_ZVAL_NREF(_8);
	ZVAL_STRING(_8, "", 1);
	zephir_update_property_this(this_ptr, SL("sendBuffer"), _8 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, buf);
	zephir_check_call_status();
	_8 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
	if (((int) (zephir_get_numberval(_8)) & 0x01)) {
		RETURN_MM_BOOL(1);
	}
	ZEPHIR_CALL_METHOD(&res, this_ptr, "getrespond", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_OBS_NVAR(_2);
	zephir_read_property(&_2, res, SL("cmd"), PH_NOISY_CC);
	_9 = ZEPHIR_IS_LONG_IDENTICAL(_2, 129);
	if (_9) {
		_9 = resCmd != 129;
	}
	if (_9) {
		ZEPHIR_INIT_VAR(_10);
		object_init_ex(_10, xs_exception_ce);
		ZEPHIR_OBS_VAR(_11);
		zephir_read_property(&_11, res, SL("buf"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&_12, res, "getarg", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _10, "__construct", NULL, 4, _11, _12);
		zephir_check_call_status();
		zephir_throw_exception_debug(_10, "xs/server.zep", 142 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_OBS_NVAR(_2);
	zephir_read_property(&_2, res, SL("cmd"), PH_NOISY_CC);
	_13 = !ZEPHIR_IS_LONG(_2, resCmd);
	if (!(_13)) {
		_14 = resArg != 0;
		if (_14) {
			ZEPHIR_CALL_METHOD(&_12, res, "getarg", NULL, 0);
			zephir_check_call_status();
			_14 = !ZEPHIR_IS_LONG(_12, resArg);
		}
		_13 = _14;
	}
	if (_13) {
		ZEPHIR_INIT_NVAR(_10);
		object_init_ex(_10, xs_exception_ce);
		ZEPHIR_OBS_NVAR(_11);
		zephir_read_property(&_11, res, SL("cmd"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&_15, res, "getarg", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_16);
		ZEPHIR_CONCAT_SVSVS(_16, "Unexpected respond {CMD:", _11, ", ARG:", _15, "}");
		ZEPHIR_CALL_METHOD(NULL, _10, "__construct", NULL, 4, _16);
		zephir_check_call_status();
		zephir_throw_exception_debug(_10, "xs/server.zep", 146 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CCTOR(res);

}

PHP_METHOD(Xs_Server, sendCommand) {

	zval *_1 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _0;
	zval *cmdArg, *cmd = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &cmdArg);



	_0 = Z_TYPE_P(cmdArg) == IS_OBJECT;
	if (_0) {
		_0 = (zephir_instance_of_ev(cmdArg, xs_command_ce TSRMLS_CC));
	}
	if (_0) {
		ZEPHIR_CPY_WRT(cmd, cmdArg);
	} else {
		ZEPHIR_INIT_NVAR(cmd);
		object_init_ex(cmd, xs_command_ce);
		ZEPHIR_CALL_METHOD(NULL, cmd, "__construct", NULL, 19, cmdArg);
		zephir_check_call_status();
	}
	zephir_get_strval(_1, cmd);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, _1);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Server, getRespond) {

	zephir_fcall_cache_entry *_2 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *hdr = NULL, *res, *_0 = NULL, *_1, _4, *_5 = NULL, *_6, *_7 = NULL, *_8;
	zval *buf = NULL, *_3 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 8);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "read", &_2, 0, _1);
	zephir_check_call_status();
	zephir_get_strval(_3, _0);
	ZEPHIR_CPY_WRT(buf, _3);
	ZEPHIR_SINIT_VAR(_4);
	ZVAL_STRING(&_4, "Ccmd/Carg1/Carg2/Cblen1/Iblen", 0);
	ZEPHIR_CALL_FUNCTION(&hdr, "unpack", NULL, 5, &_4, buf);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(res);
	object_init_ex(res, xs_command_ce);
	ZEPHIR_CALL_METHOD(NULL, res, "__construct", NULL, 19, hdr);
	zephir_check_call_status();
	zephir_array_fetch_string(&_6, hdr, SL("blen"), PH_NOISY | PH_READONLY, "xs/server.zep", 173 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&_5, this_ptr, "read", &_2, 0, _6);
	zephir_check_call_status();
	zephir_update_property_zval(res, SL("buf"), _5 TSRMLS_CC);
	zephir_array_fetch_string(&_8, hdr, SL("blen1"), PH_NOISY | PH_READONLY, "xs/server.zep", 174 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&_7, this_ptr, "read", &_2, 0, _8);
	zephir_check_call_status();
	zephir_update_property_zval(res, SL("buf1"), _7 TSRMLS_CC);
	RETURN_CCTOR(res);

}

PHP_METHOD(Xs_Server, hasRespond) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool _1;
	zval *wfds, *xfds, *rfds, *_0, *_2, *_3, *_4, *_5, *_6 = NULL;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("sock"), PH_NOISY_CC);
	_1 = Z_TYPE_P(_0) == IS_NULL;
	if (!(_1)) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
		_1 = ((((int) (zephir_get_numberval(_2)) & ((0x02 | 0x01))))) ? 1 : 0;
	}
	if (_1) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_VAR(wfds);
	array_init(wfds);
	ZEPHIR_INIT_VAR(xfds);
	array_init(xfds);
	ZEPHIR_INIT_VAR(rfds);
	array_init(rfds);
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("sock"), PH_NOISY_CC);
	zephir_array_append(&rfds, _3, PH_SEPARATE, "xs/server.zep", 190);
	ZEPHIR_INIT_VAR(_4);
	ZVAL_LONG(_4, 0);
	ZEPHIR_INIT_VAR(_5);
	ZVAL_LONG(_5, 0);
	Z_SET_ISREF_P(rfds);
	ZEPHIR_CALL_FUNCTION(&_6, "stream_select", NULL, 50, rfds, wfds, xfds, _4, _5);
	Z_UNSET_ISREF_P(rfds);
	zephir_check_call_status();
	RETURN_MM_BOOL(ZEPHIR_GT_LONG(_6, 0));

}

PHP_METHOD(Xs_Server, write) {

	zend_bool _3, _4;
	zephir_fcall_cache_entry *_2 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	long len, size;
	zval *buf_param = NULL, *len_param = NULL, *bytes = NULL, *meta = NULL, *_0, _1 = zval_used_for_init, *_5 = NULL, *_6, *_7, _8, _9, *_10 = NULL;
	zval *buf = NULL, *msg = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &buf_param, &len_param);

	zephir_get_strval(buf, buf_param);
	if (!len_param) {
		len = 0;
	} else {
		len = zephir_get_intval(len_param);
	}


	if (len == 0) {
		len = zephir_fast_strlen_ev(buf);
		if (len == 0) {
			RETURN_MM_NULL();
		}
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "check", NULL, 0);
	zephir_check_call_status();
	size = len;
	while (1) {
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("sock"), PH_NOISY_CC);
		ZEPHIR_SINIT_NVAR(_1);
		ZVAL_LONG(&_1, len);
		ZEPHIR_CALL_FUNCTION(&bytes, "fwrite", &_2, 51, _0, buf, &_1);
		zephir_check_call_status();
		_3 = ZEPHIR_IS_FALSE_IDENTICAL(bytes);
		if (!(_3)) {
			_3 = ZEPHIR_IS_LONG_IDENTICAL(bytes, 0);
		}
		_4 = _3;
		if (!(_4)) {
			_4 = ZEPHIR_IS_LONG_IDENTICAL(bytes, len);
		}
		if (_4) {
			break;
		}
		len -= zephir_get_numberval(bytes);
		ZEPHIR_INIT_NVAR(_5);
		zephir_substr(_5, buf, zephir_get_intval(bytes), 0, ZEPHIR_SUBSTR_NO_LENGTH);
		zephir_get_strval(buf, _5);
	}
	_3 = ZEPHIR_IS_FALSE_IDENTICAL(bytes);
	if (!(_3)) {
		_3 = ZEPHIR_IS_LONG_IDENTICAL(bytes, 0);
	}
	if (_3) {
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("sock"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(&meta, "stream_get_meta_data", NULL, 52, _0);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_5);
		ZVAL_BOOL(_5, 1);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "close", NULL, 0, _5);
		zephir_check_call_status();
		zephir_array_fetch_string(&_6, meta, SL("timed_out"), PH_NOISY | PH_READONLY, "xs/server.zep", 223 TSRMLS_CC);
		if (zephir_is_true(_6)) {
			ZEPHIR_INIT_VAR(msg);
			ZVAL_STRING(msg, "timeout", 1);
		} else {
			zephir_array_fetch_string(&_7, meta, SL("eof"), PH_NOISY | PH_READONLY, "xs/server.zep", 226 TSRMLS_CC);
			if (zephir_is_true(_7)) {
				ZEPHIR_INIT_NVAR(msg);
				ZVAL_STRING(msg, "closed", 1);
			} else {
				ZEPHIR_INIT_NVAR(msg);
				ZVAL_STRING(msg, "unknown", 1);
			}
		}
		ZEPHIR_INIT_NVAR(_5);
		object_init_ex(_5, xs_exception_ce);
		ZEPHIR_SINIT_NVAR(_1);
		ZVAL_STRING(&_1, "Failed to send data to server completely (SIZE:%d/%d, REASON:%s)", 0);
		ZEPHIR_SINIT_VAR(_8);
		ZVAL_LONG(&_8, (size - len));
		ZEPHIR_SINIT_VAR(_9);
		ZVAL_LONG(&_9, size);
		ZEPHIR_CALL_FUNCTION(&_10, "sprintf", NULL, 3, &_1, &_8, &_9, msg);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _5, "__construct", NULL, 4, _10);
		zephir_check_call_status();
		zephir_throw_exception_debug(_5, "xs/server.zep", 237 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Server, read) {

	zend_bool _3;
	zephir_fcall_cache_entry *_2 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *buf, *msg = NULL;
	zval *len_param = NULL, *bytes = NULL, *meta = NULL, *_0, _1 = zval_used_for_init, *_4 = NULL, *_5, *_6, _7, _8, *_9 = NULL;
	long len, size;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &len_param);

	len = zephir_get_intval(len_param);


	if (len == 0) {
		RETURN_MM_STRING("", 1);
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "check", NULL, 0);
	zephir_check_call_status();
	size = len;
	ZEPHIR_INIT_VAR(buf);
	ZVAL_EMPTY_STRING(buf);
	while (1) {
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("sock"), PH_NOISY_CC);
		ZEPHIR_SINIT_NVAR(_1);
		ZVAL_LONG(&_1, len);
		ZEPHIR_CALL_FUNCTION(&bytes, "fread", &_2, 53, _0, &_1);
		zephir_check_call_status();
		_3 = ZEPHIR_IS_FALSE_IDENTICAL(bytes);
		if (!(_3)) {
			_3 = zephir_fast_strlen_ev(bytes) == 0;
		}
		if (_3) {
			break;
		}
		len -= zephir_fast_strlen_ev(bytes);
		zephir_concat_self(&buf, bytes TSRMLS_CC);
		if (len <= 0) {
			RETURN_CTOR(buf);
		}
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("sock"), PH_NOISY_CC);
	ZEPHIR_CALL_FUNCTION(&meta, "stream_get_meta_data", NULL, 52, _0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_4);
	ZVAL_BOOL(_4, 1);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "close", NULL, 0, _4);
	zephir_check_call_status();
	zephir_array_fetch_string(&_5, meta, SL("timed_out"), PH_NOISY | PH_READONLY, "xs/server.zep", 271 TSRMLS_CC);
	if (zephir_is_true(_5)) {
		ZEPHIR_INIT_VAR(msg);
		ZVAL_STRING(msg, "timeout", 1);
	} else {
		zephir_array_fetch_string(&_6, meta, SL("eof"), PH_NOISY | PH_READONLY, "xs/server.zep", 274 TSRMLS_CC);
		if (zephir_is_true(_6)) {
			ZEPHIR_INIT_NVAR(msg);
			ZVAL_STRING(msg, "closed", 1);
		} else {
			ZEPHIR_INIT_NVAR(msg);
			ZVAL_STRING(msg, "unknown", 1);
		}
	}
	ZEPHIR_INIT_NVAR(_4);
	object_init_ex(_4, xs_exception_ce);
	ZEPHIR_SINIT_NVAR(_1);
	ZVAL_STRING(&_1, "Failed to recv data to server completely (SIZE:%d/%d, REASON:%s)", 0);
	ZEPHIR_SINIT_VAR(_7);
	ZVAL_LONG(&_7, (size - len));
	ZEPHIR_SINIT_VAR(_8);
	ZVAL_LONG(&_8, size);
	ZEPHIR_CALL_FUNCTION(&_9, "sprintf", NULL, 3, &_1, &_7, &_8, msg);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, _4, "__construct", NULL, 4, _9);
	zephir_check_call_status();
	zephir_throw_exception_debug(_4, "xs/server.zep", 285 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

PHP_METHOD(Xs_Server, check) {

	zval *_0, *_1;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("sock"), PH_NOISY_CC);
	if (unlikely(Z_TYPE_P(_0) == IS_NULL)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(xs_exception_ce, "No server connection", "xs/server.zep", 291);
		return;
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
	if (((int) (zephir_get_numberval(_1)) & 0x02)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(xs_exception_ce, "Broken server connection", "xs/server.zep", 295);
		return;
	}

}

PHP_METHOD(Xs_Server, connect) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *pos, *sock = NULL, *errNo = NULL, *err = NULL, *_0, _2 = zval_used_for_init, _3 = zval_used_for_init, *_4 = NULL, *_5 = NULL, *_7 = NULL, *_9, *_10, _11 = zval_used_for_init, _13 = zval_used_for_init, *_14, *_15 = NULL, _16;
	long port, timeout;
	zval *conn = NULL, *host = NULL, *_1 = NULL, *_6 = NULL, *_8, *_12 = NULL;

	ZEPHIR_MM_GROW();
	ZEPHIR_INIT_VAR(errNo);
	ZVAL_NULL(errNo);
	ZEPHIR_INIT_VAR(err);
	ZVAL_NULL(err);

	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("conn"), PH_NOISY_CC);
	zephir_get_strval(_1, _0);
	ZEPHIR_CPY_WRT(conn, _1);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_STRING(&_2, "file://", 0);
	ZEPHIR_SINIT_VAR(_3);
	ZVAL_LONG(&_3, 7);
	ZEPHIR_CALL_FUNCTION(&_4, "strncmp", NULL, 54, conn, &_2, &_3);
	zephir_check_call_status();
	if (!(zephir_is_true(_4))) {
		ZEPHIR_SINIT_NVAR(_2);
		ZVAL_LONG(&_2, 7);
		ZEPHIR_INIT_VAR(_5);
		zephir_substr(_5, conn, 7 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
		zephir_get_strval(_6, _5);
		ZEPHIR_CPY_WRT(conn, _6);
		ZEPHIR_SINIT_NVAR(_3);
		ZVAL_STRING(&_3, "wb", 0);
		ZEPHIR_CALL_FUNCTION(&sock, "fopen", NULL, 55, conn, &_3);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(sock)) {
			ZEPHIR_INIT_VAR(_7);
			object_init_ex(_7, xs_exception_ce);
			ZEPHIR_INIT_VAR(_8);
			ZEPHIR_CONCAT_SV(_8, "Failed to open local file for writing: ", conn);
			ZEPHIR_CALL_METHOD(NULL, _7, "__construct", NULL, 4, _8);
			zephir_check_call_status();
			zephir_throw_exception_debug(_7, "xs/server.zep", 311 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		_9 = zephir_fetch_nproperty_this(this_ptr, SL("flag"), PH_NOISY_CC);
		ZEPHIR_INIT_ZVAL_NREF(_10);
		ZVAL_LONG(_10, ((int) (zephir_get_numberval(_9)) | 0x01));
		zephir_update_property_this(this_ptr, SL("flag"), _10 TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("sock"), sock TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (zephir_is_numeric(conn)) {
		ZEPHIR_INIT_VAR(host);
		ZVAL_STRING(host, "localhost", 1);
		port = zephir_get_intval(conn);
	} else {
		ZEPHIR_SINIT_NVAR(_3);
		ZVAL_STRING(&_3, ":", 0);
		ZEPHIR_INIT_VAR(pos);
		zephir_fast_strpos(pos, conn, &_3, 0 );
		if (!ZEPHIR_IS_FALSE_IDENTICAL(pos)) {
			ZEPHIR_SINIT_VAR(_11);
			ZVAL_LONG(&_11, 0);
			ZEPHIR_INIT_NVAR(_5);
			zephir_substr(_5, conn, 0 , zephir_get_intval(pos), 0);
			zephir_get_strval(_12, _5);
			ZEPHIR_CPY_WRT(host, _12);
			ZEPHIR_SINIT_VAR(_13);
			ZVAL_LONG(&_13, (zephir_get_numberval(pos) + 1));
			ZEPHIR_INIT_NVAR(_7);
			zephir_substr(_7, conn, zephir_get_intval(&_13), 0, ZEPHIR_SUBSTR_NO_LENGTH);
			port = zephir_get_intval(_7);
		} else {
			ZEPHIR_INIT_NVAR(host);
			ZEPHIR_CONCAT_SV(host, "unix://", conn);
			port = -1;
		}
	}
	ZEPHIR_INIT_NVAR(_5);
	ZVAL_LONG(_5, port);
	ZEPHIR_INIT_NVAR(_7);
	ZVAL_LONG(_7, 5);
	Z_SET_ISREF_P(errNo);
	ZEPHIR_CALL_FUNCTION(&sock, "fsockopen", NULL, 56, host, _5, errNo, err, _7);
	Z_UNSET_ISREF_P(errNo);
	zephir_check_call_status();
	if (ZEPHIR_IS_FALSE_IDENTICAL(sock)) {
		ZEPHIR_INIT_NVAR(_5);
		object_init_ex(_5, xs_exception_ce);
		ZEPHIR_SINIT_NVAR(_11);
		ZVAL_LONG(&_11, port);
		ZEPHIR_INIT_VAR(_14);
		ZEPHIR_CONCAT_VSVSVSVS(_14, err, "(C#", errNo, ", ", host, ":", &_11, ")");
		ZEPHIR_CALL_METHOD(NULL, _5, "__construct", NULL, 4, _14);
		zephir_check_call_status();
		zephir_throw_exception_debug(_5, "xs/server.zep", 334 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_SINIT_NVAR(_13);
	ZVAL_STRING(&_13, "max_execution_time", 0);
	ZEPHIR_CALL_FUNCTION(&_15, "ini_get", NULL, 57, &_13);
	zephir_check_call_status();
	timeout = zephir_get_intval(_15);
	if (timeout > 0) {
		timeout--;
	} else {
		timeout = 30;
	}
	ZEPHIR_CALL_FUNCTION(NULL, "stream_set_blocking", NULL, 58, sock, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_SINIT_NVAR(_13);
	ZVAL_LONG(&_13, timeout);
	ZEPHIR_SINIT_VAR(_16);
	ZVAL_LONG(&_16, 0);
	ZEPHIR_CALL_FUNCTION(NULL, "stream_set_timeout", NULL, 59, sock, &_13, &_16);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("sock"), sock TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

