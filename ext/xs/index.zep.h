
extern zend_class_entry *xs_index_ce;

ZEPHIR_INIT_CLASS(Xs_Index);

PHP_METHOD(Xs_Index, __destruct);
PHP_METHOD(Xs_Index, addServer);
PHP_METHOD(Xs_Index, execCommand);
PHP_METHOD(Xs_Index, clean);
PHP_METHOD(Xs_Index, add);
PHP_METHOD(Xs_Index, update);
PHP_METHOD(Xs_Index, del);
PHP_METHOD(Xs_Index, addExdata);
PHP_METHOD(Xs_Index, addSynonym);
PHP_METHOD(Xs_Index, delSynonym);
PHP_METHOD(Xs_Index, setScwsMulti);
PHP_METHOD(Xs_Index, getScwsMulti);
PHP_METHOD(Xs_Index, openBuffer);
PHP_METHOD(Xs_Index, closeBuffer);
PHP_METHOD(Xs_Index, beginRebuild);
PHP_METHOD(Xs_Index, endRebuild);
PHP_METHOD(Xs_Index, stopRebuild);
PHP_METHOD(Xs_Index, setDb);
PHP_METHOD(Xs_Index, flushLogging);
PHP_METHOD(Xs_Index, flushIndex);
PHP_METHOD(Xs_Index, getCustomDict);
PHP_METHOD(Xs_Index, setCustomDict);
PHP_METHOD(Xs_Index, close);
PHP_METHOD(Xs_Index, appendBuffer);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_index_addserver, 0, 0, 1)
	ZEND_ARG_INFO(0, conn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_index_execcommand, 0, 0, 1)
	ZEND_ARG_INFO(0, cmd)
	ZEND_ARG_INFO(0, resArg)
	ZEND_ARG_INFO(0, resCmd)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_index_add, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, doc, Xs\\Document, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_index_update, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, doc, Xs\\Document, 0)
	ZEND_ARG_INFO(0, add)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_index_del, 0, 0, 1)
	ZEND_ARG_INFO(0, term)
	ZEND_ARG_INFO(0, field)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_index_addexdata, 0, 0, 1)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, checkFile)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_index_addsynonym, 0, 0, 2)
	ZEND_ARG_INFO(0, raw)
	ZEND_ARG_INFO(0, synonym)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_index_delsynonym, 0, 0, 1)
	ZEND_ARG_INFO(0, raw)
	ZEND_ARG_INFO(0, synonym)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_index_setscwsmulti, 0, 0, 1)
	ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_index_openbuffer, 0, 0, 0)
	ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_index_setdb, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_index_setcustomdict, 0, 0, 1)
	ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_index_close, 0, 0, 0)
	ZEND_ARG_INFO(0, ioerr)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_index_appendbuffer, 0, 0, 1)
	ZEND_ARG_INFO(0, buf)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xs_index_method_entry) {
	PHP_ME(Xs_Index, __destruct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
	PHP_ME(Xs_Index, addServer, arginfo_xs_index_addserver, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, execCommand, arginfo_xs_index_execcommand, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, clean, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, add, arginfo_xs_index_add, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, update, arginfo_xs_index_update, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, del, arginfo_xs_index_del, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, addExdata, arginfo_xs_index_addexdata, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, addSynonym, arginfo_xs_index_addsynonym, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, delSynonym, arginfo_xs_index_delsynonym, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, setScwsMulti, arginfo_xs_index_setscwsmulti, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, getScwsMulti, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, openBuffer, arginfo_xs_index_openbuffer, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, closeBuffer, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, beginRebuild, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, endRebuild, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, stopRebuild, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, setDb, arginfo_xs_index_setdb, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, flushLogging, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, flushIndex, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, getCustomDict, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, setCustomDict, arginfo_xs_index_setcustomdict, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, close, arginfo_xs_index_close, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Index, appendBuffer, arginfo_xs_index_appendbuffer, ZEND_ACC_PRIVATE)
	PHP_FE_END
};
