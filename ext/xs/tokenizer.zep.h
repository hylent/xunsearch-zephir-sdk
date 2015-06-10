
extern zend_class_entry *xs_tokenizer_ce;

ZEPHIR_INIT_CLASS(Xs_Tokenizer);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizer_gettokens, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_OBJ_INFO(0, doc, Xs\\Document, 1)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xs_tokenizer_method_entry) {
	PHP_ABSTRACT_ME(Xs_Tokenizer, getTokens, arginfo_xs_tokenizer_gettokens)
	PHP_FE_END
};
