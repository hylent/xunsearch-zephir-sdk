
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
#include "kernel/concat.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/exception.h"
#include "kernel/operators.h"


ZEPHIR_INIT_CLASS(Xs_Component) {

	ZEPHIR_REGISTER_CLASS(Xs, Component, xs, component, xs_component_method_entry, 0);

	return SUCCESS;

}

PHP_METHOD(Xs_Component, __get) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *_0, *_1 = NULL, *_3, _4, *_5 = NULL;
	zval *name = NULL, *getter = NULL, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(getter);
	ZEPHIR_CONCAT_SV(getter, "get", name);
	if ((zephir_method_exists(this_ptr, getter TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_RETURN_CALL_METHOD_ZVAL(this_ptr, getter, NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(_0);
	object_init_ex(_0, xs_exception_ce);
	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_SV(_2, "set", name);
	if ((zephir_method_exists(this_ptr, _2 TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "Write-only", 1);
	} else {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "Undefined", 1);
	}
	ZEPHIR_INIT_VAR(_3);
	zephir_get_class(_3, this_ptr, 0 TSRMLS_CC);
	ZEPHIR_SINIT_VAR(_4);
	ZVAL_STRING(&_4, "%s property: %s::%s", 0);
	ZEPHIR_CALL_FUNCTION(&_5, "sprintf", NULL, 3, &_4, _1, _3, name);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, 4, _5);
	zephir_check_call_status();
	zephir_throw_exception_debug(_0, "xs/component.zep", 19 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

PHP_METHOD(Xs_Component, __set) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *value, *_0, *_1 = NULL, *_3, _4, *_5 = NULL;
	zval *name = NULL, *setter = NULL, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &value);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(setter);
	ZEPHIR_CONCAT_SV(setter, "set", name);
	if ((zephir_method_exists(this_ptr, setter TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_CALL_METHOD_ZVAL(NULL, this_ptr, setter, NULL, 0, value);
		zephir_check_call_status();
		RETURN_MM_NULL();
	}
	ZEPHIR_INIT_VAR(_0);
	object_init_ex(_0, xs_exception_ce);
	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_SV(_2, "get", name);
	if ((zephir_method_exists(this_ptr, _2 TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "Read-only", 1);
	} else {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "Undefined", 1);
	}
	ZEPHIR_INIT_VAR(_3);
	zephir_get_class(_3, this_ptr, 0 TSRMLS_CC);
	ZEPHIR_SINIT_VAR(_4);
	ZVAL_STRING(&_4, "%s property: %s::%s", 0);
	ZEPHIR_CALL_FUNCTION(&_5, "sprintf", NULL, 3, &_4, _1, _3, name);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, 4, _5);
	zephir_check_call_status();
	zephir_throw_exception_debug(_0, "xs/component.zep", 37 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

PHP_METHOD(Xs_Component, __isset) {

	zval *name_param = NULL;
	zval *name = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_CONCAT_SV(_0, "get", name);
	RETURN_MM_BOOL((zephir_method_exists(this_ptr, _0 TSRMLS_CC)  == SUCCESS));

}

PHP_METHOD(Xs_Component, __unset) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(_0);
	ZVAL_NULL(_0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "__set", NULL, 0, name, _0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

