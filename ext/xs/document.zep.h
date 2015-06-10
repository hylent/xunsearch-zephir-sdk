
extern zend_class_entry *xs_document_ce;

ZEPHIR_INIT_CLASS(Xs_Document);

PHP_METHOD(Xs_Document, __construct);
PHP_METHOD(Xs_Document, __get);
PHP_METHOD(Xs_Document, __set);
PHP_METHOD(Xs_Document, __call);
PHP_METHOD(Xs_Document, getCharset);
PHP_METHOD(Xs_Document, setCharset);
PHP_METHOD(Xs_Document, getFields);
PHP_METHOD(Xs_Document, setFields);
PHP_METHOD(Xs_Document, setField);
PHP_METHOD(Xs_Document, f);
PHP_METHOD(Xs_Document, getAddTerms);
PHP_METHOD(Xs_Document, getAddIndex);
PHP_METHOD(Xs_Document, addTerm);
PHP_METHOD(Xs_Document, addIndex);
PHP_METHOD(Xs_Document, getIterator);
PHP_METHOD(Xs_Document, offsetExists);
PHP_METHOD(Xs_Document, offsetGet);
PHP_METHOD(Xs_Document, offsetSet);
PHP_METHOD(Xs_Document, offsetUnset);
PHP_METHOD(Xs_Document, beforeSubmit);
PHP_METHOD(Xs_Document, afterSubmit);
PHP_METHOD(Xs_Document, autoConvert);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, p)
	ZEND_ARG_INFO(0, d)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document___get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document___set, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document___call, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_ARRAY_INFO(0, args, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document_setcharset, 0, 0, 1)
	ZEND_ARG_INFO(0, charset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document_setfields, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, data, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document_setfield, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_INFO(0, isMeta)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document_f, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document_getaddterms, 0, 0, 1)
	ZEND_ARG_INFO(0, field)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document_getaddindex, 0, 0, 1)
	ZEND_ARG_INFO(0, field)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document_addterm, 0, 0, 2)
	ZEND_ARG_INFO(0, field)
	ZEND_ARG_INFO(0, term)
	ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document_addindex, 0, 0, 2)
	ZEND_ARG_INFO(0, field)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document_offsetexists, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document_offsetget, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document_offsetset, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document_offsetunset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document_beforesubmit, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, index, Xs\\Index, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document_aftersubmit, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, index, Xs\\Index, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_document_autoconvert, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xs_document_method_entry) {
	PHP_ME(Xs_Document, __construct, arginfo_xs_document___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Xs_Document, __get, arginfo_xs_document___get, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, __set, arginfo_xs_document___set, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, __call, arginfo_xs_document___call, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, getCharset, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, setCharset, arginfo_xs_document_setcharset, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, getFields, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, setFields, arginfo_xs_document_setfields, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, setField, arginfo_xs_document_setfield, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, f, arginfo_xs_document_f, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, getAddTerms, arginfo_xs_document_getaddterms, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, getAddIndex, arginfo_xs_document_getaddindex, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, addTerm, arginfo_xs_document_addterm, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, addIndex, arginfo_xs_document_addindex, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, getIterator, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, offsetExists, arginfo_xs_document_offsetexists, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, offsetGet, arginfo_xs_document_offsetget, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, offsetSet, arginfo_xs_document_offsetset, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, offsetUnset, arginfo_xs_document_offsetunset, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, beforeSubmit, arginfo_xs_document_beforesubmit, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, afterSubmit, arginfo_xs_document_aftersubmit, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Document, autoConvert, arginfo_xs_document_autoconvert, ZEND_ACC_PRIVATE)
	PHP_FE_END
};
