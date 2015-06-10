
extern zend_class_entry *xs_command_ce;

ZEPHIR_INIT_CLASS(Xs_Command);

PHP_METHOD(Xs_Command, __construct);
PHP_METHOD(Xs_Command, __toString);
PHP_METHOD(Xs_Command, getArg);
PHP_METHOD(Xs_Command, setArg);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_command___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, cmd)
	ZEND_ARG_INFO(0, arg1)
	ZEND_ARG_INFO(0, arg2)
	ZEND_ARG_INFO(0, buf)
	ZEND_ARG_INFO(0, buf1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_command_setarg, 0, 0, 1)
	ZEND_ARG_INFO(0, arg)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xs_command_method_entry) {
	PHP_ME(Xs_Command, __construct, arginfo_xs_command___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Xs_Command, __toString, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Command, getArg, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Command, setArg, arginfo_xs_command_setarg, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
