
extern zend_class_entry *xs_tokenizerxlen_ce;

ZEPHIR_INIT_CLASS(Xs_TokenizerXlen);

PHP_METHOD(Xs_TokenizerXlen, __construct);
PHP_METHOD(Xs_TokenizerXlen, getTokens);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerxlen___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, arg)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerxlen_gettokens, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_OBJ_INFO(0, doc, Xs\\Document, 1)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xs_tokenizerxlen_method_entry) {
	PHP_ME(Xs_TokenizerXlen, __construct, arginfo_xs_tokenizerxlen___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Xs_TokenizerXlen, getTokens, arginfo_xs_tokenizerxlen_gettokens, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
