
extern zend_class_entry *xs_xs_ce;

ZEPHIR_INIT_CLASS(Xs_Xs);

PHP_METHOD(Xs_Xs, getLastXs);
PHP_METHOD(Xs_Xs, convert);
PHP_METHOD(Xs_Xs, __construct);
PHP_METHOD(Xs_Xs, __destruct);
PHP_METHOD(Xs_Xs, getScheme);
PHP_METHOD(Xs_Xs, setScheme);
PHP_METHOD(Xs_Xs, restoreScheme);
PHP_METHOD(Xs_Xs, getConfig);
PHP_METHOD(Xs_Xs, getName);
PHP_METHOD(Xs_Xs, setName);
PHP_METHOD(Xs_Xs, getDefaultCharset);
PHP_METHOD(Xs_Xs, setDefaultCharset);
PHP_METHOD(Xs_Xs, getIndex);
PHP_METHOD(Xs_Xs, getSearch);
PHP_METHOD(Xs_Xs, getScwsServer);
PHP_METHOD(Xs_Xs, getFieldId);
PHP_METHOD(Xs_Xs, getFieldTitle);
PHP_METHOD(Xs_Xs, getFieldBody);
PHP_METHOD(Xs_Xs, getField);
PHP_METHOD(Xs_Xs, getAllFields);
PHP_METHOD(Xs_Xs, parseIniData);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_xs_convert, 0, 0, 3)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, to)
	ZEND_ARG_INFO(0, from)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_xs___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_xs_setscheme, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, fs, Xs\\FieldScheme, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_xs_setname, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_xs_setdefaultcharset, 0, 0, 1)
	ZEND_ARG_INFO(0, charset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_xs_getfield, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, throws)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_xs_parseinidata, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xs_xs_method_entry) {
	PHP_ME(Xs_Xs, getLastXs, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Xs_Xs, convert, arginfo_xs_xs_convert, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Xs_Xs, __construct, arginfo_xs_xs___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Xs_Xs, __destruct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
	PHP_ME(Xs_Xs, getScheme, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Xs, setScheme, arginfo_xs_xs_setscheme, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Xs, restoreScheme, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Xs, getConfig, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Xs, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Xs, setName, arginfo_xs_xs_setname, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Xs, getDefaultCharset, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Xs, setDefaultCharset, arginfo_xs_xs_setdefaultcharset, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Xs, getIndex, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Xs, getSearch, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Xs, getScwsServer, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Xs, getFieldId, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Xs, getFieldTitle, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Xs, getFieldBody, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Xs, getField, arginfo_xs_xs_getfield, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Xs, getAllFields, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Xs, parseIniData, arginfo_xs_xs_parseinidata, ZEND_ACC_PRIVATE)
	PHP_FE_END
};
