
extern zend_class_entry *xs_server_ce;

ZEPHIR_INIT_CLASS(Xs_Server);

PHP_METHOD(Xs_Server, __construct);
PHP_METHOD(Xs_Server, __destruct);
PHP_METHOD(Xs_Server, open);
PHP_METHOD(Xs_Server, reopen);
PHP_METHOD(Xs_Server, close);
PHP_METHOD(Xs_Server, getConnString);
PHP_METHOD(Xs_Server, getSocket);
PHP_METHOD(Xs_Server, getProject);
PHP_METHOD(Xs_Server, setProject);
PHP_METHOD(Xs_Server, setTimeout);
PHP_METHOD(Xs_Server, execCommand);
PHP_METHOD(Xs_Server, sendCommand);
PHP_METHOD(Xs_Server, getRespond);
PHP_METHOD(Xs_Server, hasRespond);
PHP_METHOD(Xs_Server, write);
PHP_METHOD(Xs_Server, read);
PHP_METHOD(Xs_Server, check);
PHP_METHOD(Xs_Server, connect);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_server___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, conn)
	ZEND_ARG_OBJ_INFO(0, xs, Xs\\Xs, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_server_open, 0, 0, 1)
	ZEND_ARG_INFO(0, conn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_server_reopen, 0, 0, 0)
	ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_server_close, 0, 0, 0)
	ZEND_ARG_INFO(0, ioerr)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_server_setproject, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, home)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_server_settimeout, 0, 0, 1)
	ZEND_ARG_INFO(0, sec)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_server_execcommand, 0, 0, 1)
	ZEND_ARG_INFO(0, cmdArg)
	ZEND_ARG_INFO(0, resArg)
	ZEND_ARG_INFO(0, resCmd)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_server_sendcommand, 0, 0, 1)
	ZEND_ARG_INFO(0, cmdArg)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_server_write, 0, 0, 1)
	ZEND_ARG_INFO(0, buf)
	ZEND_ARG_INFO(0, len)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_server_read, 0, 0, 1)
	ZEND_ARG_INFO(0, len)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xs_server_method_entry) {
	PHP_ME(Xs_Server, __construct, arginfo_xs_server___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Xs_Server, __destruct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
	PHP_ME(Xs_Server, open, arginfo_xs_server_open, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Server, reopen, arginfo_xs_server_reopen, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Server, close, arginfo_xs_server_close, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Server, getConnString, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Server, getSocket, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Server, getProject, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Server, setProject, arginfo_xs_server_setproject, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Server, setTimeout, arginfo_xs_server_settimeout, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Server, execCommand, arginfo_xs_server_execcommand, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Server, sendCommand, arginfo_xs_server_sendcommand, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Server, getRespond, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Server, hasRespond, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Server, write, arginfo_xs_server_write, ZEND_ACC_PROTECTED)
	PHP_ME(Xs_Server, read, arginfo_xs_server_read, ZEND_ACC_PROTECTED)
	PHP_ME(Xs_Server, check, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Xs_Server, connect, NULL, ZEND_ACC_PROTECTED)
	PHP_FE_END
};
