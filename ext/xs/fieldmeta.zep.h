
extern zend_class_entry *xs_fieldmeta_ce;

ZEPHIR_INIT_CLASS(Xs_FieldMeta);

PHP_METHOD(Xs_FieldMeta, __construct);
PHP_METHOD(Xs_FieldMeta, __toString);
PHP_METHOD(Xs_FieldMeta, val);
PHP_METHOD(Xs_FieldMeta, withPos);
PHP_METHOD(Xs_FieldMeta, isBoolIndex);
PHP_METHOD(Xs_FieldMeta, isNumeric);
PHP_METHOD(Xs_FieldMeta, isSpeical);
PHP_METHOD(Xs_FieldMeta, hasIndex);
PHP_METHOD(Xs_FieldMeta, hasIndexMixed);
PHP_METHOD(Xs_FieldMeta, hasIndexSelf);
PHP_METHOD(Xs_FieldMeta, hasCustomTokenizer);
PHP_METHOD(Xs_FieldMeta, getCustomTokenizer);
PHP_METHOD(Xs_FieldMeta, toConfig);
PHP_METHOD(Xs_FieldMeta, fromConfig);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_fieldmeta___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_ARRAY_INFO(0, config, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_fieldmeta_val, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_fieldmeta_fromconfig, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, config, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xs_fieldmeta_method_entry) {
	PHP_ME(Xs_FieldMeta, __construct, arginfo_xs_fieldmeta___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Xs_FieldMeta, __toString, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldMeta, val, arginfo_xs_fieldmeta_val, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldMeta, withPos, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldMeta, isBoolIndex, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldMeta, isNumeric, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldMeta, isSpeical, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldMeta, hasIndex, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldMeta, hasIndexMixed, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldMeta, hasIndexSelf, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldMeta, hasCustomTokenizer, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldMeta, getCustomTokenizer, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldMeta, toConfig, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_FieldMeta, fromConfig, arginfo_xs_fieldmeta_fromconfig, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
