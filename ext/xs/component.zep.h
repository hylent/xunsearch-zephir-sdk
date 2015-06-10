
extern zend_class_entry *xs_component_ce;

ZEPHIR_INIT_CLASS(Xs_Component);

PHP_METHOD(Xs_Component, __get);
PHP_METHOD(Xs_Component, __set);
PHP_METHOD(Xs_Component, __isset);
PHP_METHOD(Xs_Component, __unset);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_component___get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_component___set, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_component___isset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_component___unset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xs_component_method_entry) {
	PHP_ME(Xs_Component, __get, arginfo_xs_component___get, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Component, __set, arginfo_xs_component___set, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Component, __isset, arginfo_xs_component___isset, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Component, __unset, arginfo_xs_component___unset, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
