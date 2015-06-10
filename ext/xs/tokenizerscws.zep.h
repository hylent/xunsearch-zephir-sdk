
extern zend_class_entry *xs_tokenizerscws_ce;

ZEPHIR_INIT_CLASS(Xs_TokenizerScws);

PHP_METHOD(Xs_TokenizerScws, __construct);
PHP_METHOD(Xs_TokenizerScws, getTokens);
PHP_METHOD(Xs_TokenizerScws, setCharset);
PHP_METHOD(Xs_TokenizerScws, setIgnore);
PHP_METHOD(Xs_TokenizerScws, setMulti);
PHP_METHOD(Xs_TokenizerScws, setDict);
PHP_METHOD(Xs_TokenizerScws, addDict);
PHP_METHOD(Xs_TokenizerScws, setDuality);
PHP_METHOD(Xs_TokenizerScws, getVersion);
PHP_METHOD(Xs_TokenizerScws, getResult);
PHP_METHOD(Xs_TokenizerScws, getTops);
PHP_METHOD(Xs_TokenizerScws, hasWord);
PHP_METHOD(Xs_TokenizerScws, applySetting);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerscws___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, arg)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerscws_gettokens, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_OBJ_INFO(0, doc, Xs\\Document, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerscws_setcharset, 0, 0, 1)
	ZEND_ARG_INFO(0, charset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerscws_setignore, 0, 0, 0)
	ZEND_ARG_INFO(0, yes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerscws_setmulti, 0, 0, 0)
	ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerscws_setdict, 0, 0, 1)
	ZEND_ARG_INFO(0, fpath)
	ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerscws_adddict, 0, 0, 1)
	ZEND_ARG_INFO(0, fpath)
	ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerscws_setduality, 0, 0, 0)
	ZEND_ARG_INFO(0, yes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerscws_getresult, 0, 0, 1)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerscws_gettops, 0, 0, 1)
	ZEND_ARG_INFO(0, text)
	ZEND_ARG_INFO(0, limit)
	ZEND_ARG_INFO(0, xattr)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerscws_hasword, 0, 0, 2)
	ZEND_ARG_INFO(0, text)
	ZEND_ARG_INFO(0, xattr)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_tokenizerscws_applysetting, 0, 0, 1)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xs_tokenizerscws_method_entry) {
	PHP_ME(Xs_TokenizerScws, __construct, arginfo_xs_tokenizerscws___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Xs_TokenizerScws, getTokens, arginfo_xs_tokenizerscws_gettokens, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_TokenizerScws, setCharset, arginfo_xs_tokenizerscws_setcharset, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_TokenizerScws, setIgnore, arginfo_xs_tokenizerscws_setignore, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_TokenizerScws, setMulti, arginfo_xs_tokenizerscws_setmulti, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_TokenizerScws, setDict, arginfo_xs_tokenizerscws_setdict, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_TokenizerScws, addDict, arginfo_xs_tokenizerscws_adddict, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_TokenizerScws, setDuality, arginfo_xs_tokenizerscws_setduality, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_TokenizerScws, getVersion, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_TokenizerScws, getResult, arginfo_xs_tokenizerscws_getresult, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_TokenizerScws, getTops, arginfo_xs_tokenizerscws_gettops, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_TokenizerScws, hasWord, arginfo_xs_tokenizerscws_hasword, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_TokenizerScws, applySetting, arginfo_xs_tokenizerscws_applysetting, ZEND_ACC_PRIVATE)
	PHP_FE_END
};
