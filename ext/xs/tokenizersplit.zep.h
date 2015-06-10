
extern zend_class_entry *xs_tokenizersplit_ce;

ZEPHIR_INIT_CLASS(Xs_TokenizerSplit);

PHP_METHOD(Xs_TokenizerSplit, __construct);
PHP_METHOD(Xs_TokenizerSplit, getTokens);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizersplit___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, arg)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizersplit_gettokens, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_OBJ_INFO(0, doc, Xs\\Document, 1)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xs_tokenizersplit_method_entry) {
	PHP_ME(Xs_TokenizerSplit, __construct, arginfo_xs_tokenizersplit___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Xs_TokenizerSplit, getTokens, arginfo_xs_tokenizersplit_gettokens, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
