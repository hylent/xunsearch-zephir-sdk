
extern zend_class_entry *xs_search_ce;

ZEPHIR_INIT_CLASS(Xs_Search);

PHP_METHOD(Xs_Search, __construct);
PHP_METHOD(Xs_Search, open);
PHP_METHOD(Xs_Search, setCharset);
PHP_METHOD(Xs_Search, setFuzzy);
PHP_METHOD(Xs_Search, setCutOff);
PHP_METHOD(Xs_Search, setRequireMatchedTerm);
PHP_METHOD(Xs_Search, setAutoSynonyms);
PHP_METHOD(Xs_Search, setSynonymScale);
PHP_METHOD(Xs_Search, getAllSynonyms);
PHP_METHOD(Xs_Search, getSynonyms);
PHP_METHOD(Xs_Search, getQuery);
PHP_METHOD(Xs_Search, setQuery);
PHP_METHOD(Xs_Search, setMultiSort);
PHP_METHOD(Xs_Search, setSort);
PHP_METHOD(Xs_Search, setDocOrder);
PHP_METHOD(Xs_Search, setCollapse);
PHP_METHOD(Xs_Search, addRange);
PHP_METHOD(Xs_Search, addWeight);
PHP_METHOD(Xs_Search, setFacets);
PHP_METHOD(Xs_Search, getFacets);
PHP_METHOD(Xs_Search, setScwsMulti);
PHP_METHOD(Xs_Search, setLimit);
PHP_METHOD(Xs_Search, setDb);
PHP_METHOD(Xs_Search, addDb);
PHP_METHOD(Xs_Search, markResetScheme);
PHP_METHOD(Xs_Search, terms);
PHP_METHOD(Xs_Search, count);
PHP_METHOD(Xs_Search, search);
PHP_METHOD(Xs_Search, getLastCount);
PHP_METHOD(Xs_Search, getDbTotal);
PHP_METHOD(Xs_Search, getHotQuery);
PHP_METHOD(Xs_Search, getRelatedQuery);
PHP_METHOD(Xs_Search, getExpandedQuery);
PHP_METHOD(Xs_Search, getCorrectedQuery);
PHP_METHOD(Xs_Search, addSearchLog);
PHP_METHOD(Xs_Search, highlight);
PHP_METHOD(Xs_Search, logQuery);
PHP_METHOD(Xs_Search, clearQuery);
PHP_METHOD(Xs_Search, addQueryString);
PHP_METHOD(Xs_Search, addQueryTerm);
PHP_METHOD(Xs_Search, restoreDb);
PHP_METHOD(Xs_Search, preQueryString);
PHP_METHOD(Xs_Search, regQueryPrefix);
PHP_METHOD(Xs_Search, initSpecialField);
PHP_METHOD(Xs_Search, cleanFieldQuery);
PHP_METHOD(Xs_Search, cleanFieldCallback);
PHP_METHOD(Xs_Search, initHighlight);
PHP_METHOD(Xs_Search, formatValueRange);
PHP_METHOD(Xs_Search, numfromstr);
PHP_METHOD(Xs_Search, xapianUnserialise);
PHP_METHOD(Xs_Search, isRobotAgent);

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, conn)
	ZEND_ARG_OBJ_INFO(0, xs, Xs\\Xs, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_open, 0, 0, 1)
	ZEND_ARG_INFO(0, conn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_setcharset, 0, 0, 1)
	ZEND_ARG_INFO(0, charset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_setfuzzy, 0, 0, 0)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_setcutoff, 0, 0, 1)
	ZEND_ARG_INFO(0, percent)
	ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_setrequirematchedterm, 0, 0, 0)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_setautosynonyms, 0, 0, 0)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_setsynonymscale, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_getallsynonyms, 0, 0, 0)
	ZEND_ARG_INFO(0, limit)
	ZEND_ARG_INFO(0, offset)
	ZEND_ARG_INFO(0, stemmed)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_getsynonyms, 0, 0, 1)
	ZEND_ARG_INFO(0, term)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_getquery, 0, 0, 0)
	ZEND_ARG_INFO(0, query)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_setquery, 0, 0, 1)
	ZEND_ARG_INFO(0, query)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_setmultisort, 0, 0, 1)
	ZEND_ARG_INFO(0, fields)
	ZEND_ARG_INFO(0, reversed)
	ZEND_ARG_INFO(0, relevanceFirst)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_setsort, 0, 0, 1)
	ZEND_ARG_INFO(0, field)
	ZEND_ARG_INFO(0, asc)
	ZEND_ARG_INFO(0, relevanceFirst)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_setdocorder, 0, 0, 0)
	ZEND_ARG_INFO(0, asc)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_setcollapse, 0, 0, 1)
	ZEND_ARG_INFO(0, field)
	ZEND_ARG_INFO(0, num)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_addrange, 0, 0, 3)
	ZEND_ARG_INFO(0, field)
	ZEND_ARG_INFO(0, from)
	ZEND_ARG_INFO(0, to)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_addweight, 0, 0, 2)
	ZEND_ARG_INFO(0, field)
	ZEND_ARG_INFO(0, term)
	ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_setfacets, 0, 0, 1)
	ZEND_ARG_INFO(0, field)
	ZEND_ARG_INFO(0, exact)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_getfacets, 0, 0, 0)
	ZEND_ARG_INFO(0, field)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_setscwsmulti, 0, 0, 1)
	ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_setlimit, 0, 0, 1)
	ZEND_ARG_INFO(0, limit)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_setdb, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_adddb, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_terms, 0, 0, 0)
	ZEND_ARG_INFO(0, query)
	ZEND_ARG_INFO(0, convert)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_count, 0, 0, 0)
	ZEND_ARG_INFO(0, query)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_search, 0, 0, 0)
	ZEND_ARG_INFO(0, query)
	ZEND_ARG_INFO(0, saveHighlight)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_gethotquery, 0, 0, 0)
	ZEND_ARG_INFO(0, limit)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_getrelatedquery, 0, 0, 0)
	ZEND_ARG_INFO(0, query)
	ZEND_ARG_INFO(0, limit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_getexpandedquery, 0, 0, 1)
	ZEND_ARG_INFO(0, query)
	ZEND_ARG_INFO(0, limit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_getcorrectedquery, 0, 0, 0)
	ZEND_ARG_INFO(0, query)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_addsearchlog, 0, 0, 1)
	ZEND_ARG_INFO(0, query)
	ZEND_ARG_INFO(0, wdf)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_highlight, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_INFO(0, strtr)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_logquery, 0, 0, 0)
	ZEND_ARG_INFO(0, query)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_addquerystring, 0, 0, 1)
	ZEND_ARG_INFO(0, query)
	ZEND_ARG_INFO(0, addOp)
	ZEND_ARG_INFO(0, scale)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_addqueryterm, 0, 0, 2)
	ZEND_ARG_INFO(0, field)
	ZEND_ARG_INFO(0, term)
	ZEND_ARG_INFO(0, addOp)
	ZEND_ARG_INFO(0, scale)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_prequerystring, 0, 0, 1)
	ZEND_ARG_INFO(0, query)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_regqueryprefix, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_cleanfieldquery, 0, 0, 1)
	ZEND_ARG_INFO(0, query)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_cleanfieldcallback, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, match, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_formatvaluerange, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, match, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_numfromstr, 0, 0, 2)
	ZEND_ARG_INFO(0, str)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_xs_search_xapianunserialise, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(xs_search_method_entry) {
	PHP_ME(Xs_Search, __construct, arginfo_xs_search___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Xs_Search, open, arginfo_xs_search_open, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, setCharset, arginfo_xs_search_setcharset, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, setFuzzy, arginfo_xs_search_setfuzzy, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, setCutOff, arginfo_xs_search_setcutoff, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, setRequireMatchedTerm, arginfo_xs_search_setrequirematchedterm, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, setAutoSynonyms, arginfo_xs_search_setautosynonyms, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, setSynonymScale, arginfo_xs_search_setsynonymscale, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, getAllSynonyms, arginfo_xs_search_getallsynonyms, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, getSynonyms, arginfo_xs_search_getsynonyms, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, getQuery, arginfo_xs_search_getquery, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, setQuery, arginfo_xs_search_setquery, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, setMultiSort, arginfo_xs_search_setmultisort, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, setSort, arginfo_xs_search_setsort, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, setDocOrder, arginfo_xs_search_setdocorder, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, setCollapse, arginfo_xs_search_setcollapse, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, addRange, arginfo_xs_search_addrange, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, addWeight, arginfo_xs_search_addweight, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, setFacets, arginfo_xs_search_setfacets, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, getFacets, arginfo_xs_search_getfacets, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, setScwsMulti, arginfo_xs_search_setscwsmulti, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, setLimit, arginfo_xs_search_setlimit, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, setDb, arginfo_xs_search_setdb, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, addDb, arginfo_xs_search_adddb, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, markResetScheme, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, terms, arginfo_xs_search_terms, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, count, arginfo_xs_search_count, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, search, arginfo_xs_search_search, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, getLastCount, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, getDbTotal, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, getHotQuery, arginfo_xs_search_gethotquery, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, getRelatedQuery, arginfo_xs_search_getrelatedquery, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, getExpandedQuery, arginfo_xs_search_getexpandedquery, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, getCorrectedQuery, arginfo_xs_search_getcorrectedquery, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, addSearchLog, arginfo_xs_search_addsearchlog, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, highlight, arginfo_xs_search_highlight, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, logQuery, arginfo_xs_search_logquery, ZEND_ACC_PRIVATE)
	PHP_ME(Xs_Search, clearQuery, NULL, ZEND_ACC_PRIVATE)
	PHP_ME(Xs_Search, addQueryString, arginfo_xs_search_addquerystring, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, addQueryTerm, arginfo_xs_search_addqueryterm, ZEND_ACC_PUBLIC)
	PHP_ME(Xs_Search, restoreDb, NULL, ZEND_ACC_PRIVATE)
	PHP_ME(Xs_Search, preQueryString, arginfo_xs_search_prequerystring, ZEND_ACC_PRIVATE)
	PHP_ME(Xs_Search, regQueryPrefix, arginfo_xs_search_regqueryprefix, ZEND_ACC_PRIVATE)
	PHP_ME(Xs_Search, initSpecialField, NULL, ZEND_ACC_PRIVATE)
	PHP_ME(Xs_Search, cleanFieldQuery, arginfo_xs_search_cleanfieldquery, ZEND_ACC_PRIVATE)
	PHP_ME(Xs_Search, cleanFieldCallback, arginfo_xs_search_cleanfieldcallback, ZEND_ACC_PRIVATE)
	PHP_ME(Xs_Search, initHighlight, NULL, ZEND_ACC_PRIVATE)
	PHP_ME(Xs_Search, formatValueRange, arginfo_xs_search_formatvaluerange, ZEND_ACC_PRIVATE)
	PHP_ME(Xs_Search, numfromstr, arginfo_xs_search_numfromstr, ZEND_ACC_PRIVATE)
	PHP_ME(Xs_Search, xapianUnserialise, arginfo_xs_search_xapianunserialise, ZEND_ACC_PRIVATE)
	PHP_ME(Xs_Search, isRobotAgent, NULL, ZEND_ACC_PRIVATE)
	PHP_FE_END
};
