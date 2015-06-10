
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


ZEPHIR_INIT_CLASS(Xs_Tokenizer) {

	ZEPHIR_REGISTER_INTERFACE(Xs, Tokenizer, xs, tokenizer, xs_tokenizer_method_entry);

	zend_declare_class_constant_long(xs_tokenizer_ce, SL("DFL"), 0 TSRMLS_CC);

	return SUCCESS;

}

ZEPHIR_DOC_METHOD(Xs_Tokenizer, getTokens);

