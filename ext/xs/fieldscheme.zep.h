
extern zend_class_entry *xs_fieldscheme_ce;

ZEPHIR_INIT_CLASS(Xs_FieldScheme);

PHP_METHOD(Xs_FieldScheme, logger);
PHP_METHOD(Xs_FieldScheme, __toString);
PHP_METHOD(Xs_FieldScheme, getFieldId);
PHP_METHOD(Xs_FieldScheme, getFieldTitle);
PHP_METHOD(Xs_FieldScheme, getFieldBody);
PHP_METHOD(Xs_FieldScheme, getField);
PHP_METHOD(Xs_FieldScheme, getAllFields);
PHP_METHOD(Xs_FieldScheme, getVnoMap);
PHP_METHOD(Xs_FieldScheme, addField);
PHP_METHOD(Xs_FieldScheme, checkValid);
PHP_METHOD(Xs_FieldScheme, getIterator);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_fieldscheme_getfield, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, throws)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_fieldscheme_addfield, 0, 0, 1)
	ZEND_ARG_INFO(0, fieldArg)
	ZEND_ARG_ARRAY_INFO(0, config, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_fieldscheme_checkvalid, 0, 0, 0)
	ZEND_ARG_INFO(0, throws)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xs_fieldscheme_method_entry) {
	PHP_ME(Xs_FieldScheme, logger, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Xs_FieldScheme, __toString, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldScheme, getFieldId, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldScheme, getFieldTitle, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldScheme, getFieldBody, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldScheme, getField, arginfo_xs_fieldscheme_getfield, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldScheme, getAllFields, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldScheme, getVnoMap, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldScheme, addField, arginfo_xs_fieldscheme_addfield, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldScheme, checkValid, arginfo_xs_fieldscheme_checkvalid, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldScheme, getIterator, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
