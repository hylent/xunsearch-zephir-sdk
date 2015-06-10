
extern zend_class_entry *xs_tokenizerxstep_ce;

ZEPHIR_INIT_CLASS(Xs_TokenizerXstep);

PHP_METHOD(Xs_TokenizerXstep, __construct);
PHP_METHOD(Xs_TokenizerXstep, getTokens);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerxstep___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, arg)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerxstep_gettokens, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_OBJ_INFO(0, doc, Xs\\Document, 1)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xs_tokenizerxstep_method_entry) {
	PHP_ME(Xs_TokenizerXstep, __construct, arginfo_xs_tokenizerxstep___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Xs_TokenizerXstep, getTokens, arginfo_xs_tokenizerxstep_gettokens, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
