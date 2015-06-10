
extern zend_class_entry *xs_tokenizernone_ce;

ZEPHIR_INIT_CLASS(Xs_TokenizerNone);

PHP_METHOD(Xs_TokenizerNone, getTokens);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizernone_gettokens, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_OBJ_INFO(0, doc, Xs\\Document, 1)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xs_tokenizernone_method_entry) {
	PHP_ME(Xs_TokenizerNone, getTokens, arginfo_xs_tokenizernone_gettokens, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
