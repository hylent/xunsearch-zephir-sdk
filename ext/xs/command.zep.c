
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/hash.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/string.h"
#include "kernel/concat.h"


ZEPHIR_INIT_CLASS(Xs_Command) {

	ZEPHIR_REGISTER_CLASS_EX(Xs, Command, xs, command, xs_component_ce, xs_command_method_entry, 0);

	zend_declare_property_long(xs_command_ce, SL("cmd"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_long(xs_command_ce, SL("arg1"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_long(xs_command_ce, SL("arg2"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_string(xs_command_ce, SL("buf"), "", ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_string(xs_command_ce, SL("buf1"), "", ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_NONE"), 0 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_DEFAULT"), 0 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_PROTOCOL"), 20110707 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_USE"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_HELLO"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_DEBUG"), 2 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_TIMEOUT"), 3 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUIT"), 4 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_SET_DB"), 32 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_GET_DB"), 33 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_SUBMIT"), 34 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_REMOVE"), 35 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_EXDATA"), 36 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_CLEAN_DB"), 37 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_DELETE_PROJECT"), 38 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_COMMIT"), 39 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_REBUILD"), 40 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_FLUSH_LOGGING"), 41 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_SYNONYMS"), 42 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_USER_DICT"), 43 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_DB_TOTAL"), 64 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_GET_TOTAL"), 65 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_GET_RESULT"), 66 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_SET_DB"), 32 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_GET_DB"), 33 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_ADD_DB"), 68 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_FINISH"), 69 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_DRAW_TPOOL"), 70 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_ADD_LOG"), 71 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_GET_SYNONYMS"), 72 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_SCWS_GET"), 73 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_GET_STRING"), 96 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_GET_TERMS"), 97 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_GET_CORRECTED"), 98 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_GET_EXPANDED"), 99 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK"), 128 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR"), 129 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_RESULT_DOC"), 140 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_RESULT_FIELD"), 141 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_RESULT_FACETS"), 142 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_RESULT_MATCHED"), 143 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_DOC_TERM"), 160 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_DOC_VALUE"), 161 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_DOC_INDEX"), 162 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_REQUEST"), 163 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_IMPORT_HEADER"), 191 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_SET_SORT"), 192 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_SET_CUT"), 193 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_SET_NUMERIC"), 194 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_SET_COLLAPSE"), 195 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_KEEPALIVE"), 196 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_SET_FACETS"), 197 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_SCWS_SET"), 198 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_SET_CUTOFF"), 199 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_SET_MISC"), 200 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_INIT"), 224 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_PARSE"), 225 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_TERM"), 226 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_RANGEPROC"), 227 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_RANGE"), 228 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_VALCMP"), 229 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_PREFIX"), 230 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_PARSEFLAG"), 231 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SORT_TYPE_RELEVANCE"), 0 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SORT_TYPE_DOCID"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SORT_TYPE_VALUE"), 2 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SORT_TYPE_MULTI"), 3 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SORT_TYPE_MASK"), 0x3f TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SORT_FLAG_RELEVANCE"), 0x40 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SORT_FLAG_ASCENDING"), 0x80 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_OP_AND"), 0 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_OP_OR"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_OP_AND_NOT"), 2 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_OP_XOR"), 3 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_OP_AND_MAYBE"), 4 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_QUERY_OP_FILTER"), 5 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_RANGE_PROC_STRING"), 0 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_RANGE_PROC_DATE"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_RANGE_PROC_NUMBER"), 2 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_VALCMP_LE"), 0 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_VALCMP_GE"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_PARSE_FLAG_BOOLEAN"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_PARSE_FLAG_PHRASE"), 2 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_PARSE_FLAG_LOVEHATE"), 4 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_PARSE_FLAG_BOOLEAN_ANY_CASE"), 8 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_PARSE_FLAG_WILDCARD"), 16 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_PARSE_FLAG_PURE_NOT"), 32 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_PARSE_FLAG_PARTIAL"), 64 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_PARSE_FLAG_SPELLING_CORRECTION"), 128 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_PARSE_FLAG_SYNONYM"), 256 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_PARSE_FLAG_AUTO_SYNONYMS"), 512 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_PARSE_FLAG_AUTO_MULTIWORD_SYNONYMS"), 1536 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_PREFIX_NORMAL"), 0 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_PREFIX_BOOLEAN"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_WEIGHT_MASK"), 0x3f TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_FLAG_WITHPOS"), 0x40 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_FLAG_SAVEVALUE"), 0x80 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_FLAG_CHECKSTEM"), 0x80 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_VALUE_FLAG_NUMERIC"), 0x80 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_REQUEST_ADD"), 0 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_REQUEST_UPDATE"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_SYNONYMS_ADD"), 0 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_INDEX_SYNONYMS_DEL"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_MISC_SYN_SCALE"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SEARCH_MISC_MATCHED_TERM"), 2 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SCWS_GET_VERSION"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SCWS_GET_RESULT"), 2 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SCWS_GET_TOPS"), 3 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SCWS_HAS_WORD"), 4 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SCWS_GET_MULTI"), 5 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SCWS_SET_IGNORE"), 50 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SCWS_SET_MULTI"), 51 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SCWS_SET_DUALITY"), 52 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SCWS_SET_DICT"), 53 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_SCWS_ADD_DICT"), 54 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_UNKNOWN"), 600 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_NOPROJECT"), 401 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_TOOLONG"), 402 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_INVALIDCHAR"), 403 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_EMPTY"), 404 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_NOACTION"), 405 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_RUNNING"), 406 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_REBUILDING"), 407 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_WRONGPLACE"), 450 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_WRONGFORMAT"), 451 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_EMPTYQUERY"), 452 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_TIMEOUT"), 501 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_IOERR"), 502 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_NOMEM"), 503 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_BUSY"), 504 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_UNIMP"), 505 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_NODB"), 506 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_DBLOCKED"), 507 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_CREATE_HOME"), 508 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_INVALID_HOME"), 509 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_REMOVE_HOME"), 510 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_REMOVE_DB"), 511 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_STAT"), 512 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_OPEN_FILE"), 513 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_TASK_CANCELED"), 514 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_ERR_XAPIAN"), 515 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_INFO"), 200 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_PROJECT"), 201 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_QUERY_STRING"), 202 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_DB_TOTAL"), 203 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_QUERY_TERMS"), 204 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_QUERY_CORRECTED"), 205 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_SEARCH_TOTAL"), 206 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_RESULT_BEGIN"), 206 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_RESULT_END"), 207 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_TIMEOUT_SET"), 208 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_FINISHED"), 209 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_LOGGED"), 210 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_RQST_FINISHED"), 250 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_DB_CHANGED"), 251 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_DB_INFO"), 252 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_DB_CLEAN"), 253 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_PROJECT_ADD"), 254 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_PROJECT_DEL"), 255 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_DB_COMMITED"), 256 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_DB_REBUILD"), 257 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_LOG_FLUSHED"), 258 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_DICT_SAVED"), 259 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_RESULT_SYNONYMS"), 280 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_SCWS_RESULT"), 290 TSRMLS_CC);

	zend_declare_class_constant_long(xs_command_ce, SL("CMD_OK_SCWS_TOPS"), 291 TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Xs_Command, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_bool _3;
	HashTable *_1;
	HashPosition _0;
	zval *buf = NULL, *buf1 = NULL;
	long arg1, arg2;
	zval *cmd, *arg1_param = NULL, *arg2_param = NULL, *buf_param = NULL, *buf1_param = NULL, *k = NULL, *v = NULL, **_2, *_4 = NULL, *_6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 4, &cmd, &arg1_param, &arg2_param, &buf_param, &buf1_param);

	if (!arg1_param) {
		arg1 = 0;
	} else {
		arg1 = zephir_get_intval(arg1_param);
	}
	if (!arg2_param) {
		arg2 = 0;
	} else {
		arg2 = zephir_get_intval(arg2_param);
	}
	if (!buf_param) {
		ZEPHIR_INIT_VAR(buf);
		ZVAL_STRING(buf, "", 1);
	} else {
		zephir_get_strval(buf, buf_param);
	}
	if (!buf1_param) {
		ZEPHIR_INIT_VAR(buf1);
		ZVAL_STRING(buf1, "", 1);
	} else {
		zephir_get_strval(buf1, buf1_param);
	}


	if (Z_TYPE_P(cmd) == IS_ARRAY) {
		zephir_is_iterable(cmd, &_1, &_0, 0, 0, "xs/command.zep", 188);
		for (
		  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		  ; zephir_hash_move_forward_ex(_1, &_0)
		) {
			ZEPHIR_GET_HMKEY(k, _1, _0);
			ZEPHIR_GET_HVALUE(v, _2);
			_3 = ZEPHIR_IS_STRING_IDENTICAL(k, "arg");
			if (!(_3)) {
				ZEPHIR_CALL_FUNCTION(&_4, "property_exists", &_5, 1, this_ptr, k);
				zephir_check_call_status();
				_3 = zephir_is_true(_4);
			}
			if (_3) {
				zephir_update_property_zval_zval(this_ptr, k, v TSRMLS_CC);
			}
		}
	} else {
		zephir_update_property_this(this_ptr, SL("cmd"), cmd TSRMLS_CC);
		ZEPHIR_INIT_ZVAL_NREF(_6);
		ZVAL_LONG(_6, arg1);
		zephir_update_property_this(this_ptr, SL("arg1"), _6 TSRMLS_CC);
		ZEPHIR_INIT_ZVAL_NREF(_6);
		ZVAL_LONG(_6, arg2);
		zephir_update_property_this(this_ptr, SL("arg2"), _6 TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("buf"), buf TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("buf1"), buf1 TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Xs_Command, __toString) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0, *_1, _2 = zval_used_for_init, _3 = zval_used_for_init, *_4, *_5, *_6, *_7, *_8, _9, *_10 = NULL, *_11, *_12;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("buf1"), PH_NOISY_CC);
	if (zephir_fast_strlen_ev(_0) > 0xff) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("buf1"), PH_NOISY_CC);
		ZEPHIR_SINIT_VAR(_2);
		ZVAL_LONG(&_2, 0);
		ZEPHIR_SINIT_VAR(_3);
		ZVAL_LONG(&_3, 0xff);
		ZEPHIR_INIT_VAR(_4);
		zephir_substr(_4, _1, 0 , 0xff , 0);
		zephir_update_property_this(this_ptr, SL("buf1"), _4 TSRMLS_CC);
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("cmd"), PH_NOISY_CC);
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("arg1"), PH_NOISY_CC);
	_6 = zephir_fetch_nproperty_this(this_ptr, SL("arg2"), PH_NOISY_CC);
	_7 = zephir_fetch_nproperty_this(this_ptr, SL("buf1"), PH_NOISY_CC);
	_8 = zephir_fetch_nproperty_this(this_ptr, SL("buf"), PH_NOISY_CC);
	ZEPHIR_SINIT_NVAR(_2);
	ZVAL_STRING(&_2, "CCCCI", 0);
	ZEPHIR_SINIT_NVAR(_3);
	ZVAL_LONG(&_3, zephir_fast_strlen_ev(_7));
	ZEPHIR_SINIT_VAR(_9);
	ZVAL_LONG(&_9, zephir_fast_strlen_ev(_8));
	ZEPHIR_CALL_FUNCTION(&_10, "pack", NULL, 2, &_2, _1, _5, _6, &_3, &_9);
	zephir_check_call_status();
	_11 = zephir_fetch_nproperty_this(this_ptr, SL("buf"), PH_NOISY_CC);
	_12 = zephir_fetch_nproperty_this(this_ptr, SL("buf1"), PH_NOISY_CC);
	ZEPHIR_CONCAT_VVV(return_value, _10, _11, _12);
	RETURN_MM();

}

PHP_METHOD(Xs_Command, getArg) {

	zval *_0, *_1;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("arg2"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("arg1"), PH_NOISY_CC);
	RETURN_LONG(((int) (zephir_get_numberval(_0)) | (((int) (zephir_get_numberval(_1)) << 8))));

}

PHP_METHOD(Xs_Command, setArg) {

	zval *arg_param = NULL, *_0;
	long arg;

	zephir_fetch_params(0, 1, 0, &arg_param);

	arg = zephir_get_intval(arg_param);


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, (((arg >> 8)) & 0xff));
	zephir_update_property_this(this_ptr, SL("arg1"), _0 TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, (arg & 0xff));
	zephir_update_property_this(this_ptr, SL("arg2"), _0 TSRMLS_CC);

}

