
extern zend_class_entry *xs_tokenizerfull_ce;

ZEPHIR_INIT_CLASS(Xs_TokenizerFull);

PHP_METHOD(Xs_TokenizerFull, getTokens);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerfull_gettokens, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_OBJ_INFO(0, doc, Xs\\Document, 1)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xs_tokenizerfull_method_entry) {
	PHP_ME(Xs_TokenizerFull, getTokens, arginfo_xs_tokenizerfull_gettokens, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
