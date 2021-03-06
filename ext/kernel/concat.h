
#ifndef ZEPHIR_KERNEL_CONCAT_H
#define ZEPHIR_KERNEL_CONCAT_H

#include <php.h>
#include <Zend/zend.h>

#include "kernel/main.h"

#define ZEPHIR_CONCAT_SS(result, op1, op2) \
	 zephir_concat_ss(&result, op1, sizeof(op1)-1, op2, sizeof(op2)-1, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_SS(result, op1, op2) \
	 zephir_concat_ss(&result, op1, sizeof(op1)-1, op2, sizeof(op2)-1, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_SSV(result, op1, op2, op3) \
	 zephir_concat_ssv(&result, op1, sizeof(op1)-1, op2, sizeof(op2)-1, op3, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_SSV(result, op1, op2, op3) \
	 zephir_concat_ssv(&result, op1, sizeof(op1)-1, op2, sizeof(op2)-1, op3, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_SV(result, op1, op2) \
	 zephir_concat_sv(&result, op1, sizeof(op1)-1, op2, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_SV(result, op1, op2) \
	 zephir_concat_sv(&result, op1, sizeof(op1)-1, op2, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_SVS(result, op1, op2, op3) \
	 zephir_concat_svs(&result, op1, sizeof(op1)-1, op2, op3, sizeof(op3)-1, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_SVS(result, op1, op2, op3) \
	 zephir_concat_svs(&result, op1, sizeof(op1)-1, op2, op3, sizeof(op3)-1, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_SVSVS(result, op1, op2, op3, op4, op5) \
	 zephir_concat_svsvs(&result, op1, sizeof(op1)-1, op2, op3, sizeof(op3)-1, op4, op5, sizeof(op5)-1, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_SVSVS(result, op1, op2, op3, op4, op5) \
	 zephir_concat_svsvs(&result, op1, sizeof(op1)-1, op2, op3, sizeof(op3)-1, op4, op5, sizeof(op5)-1, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_SVSVSV(result, op1, op2, op3, op4, op5, op6) \
	 zephir_concat_svsvsv(&result, op1, sizeof(op1)-1, op2, op3, sizeof(op3)-1, op4, op5, sizeof(op5)-1, op6, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_SVSVSV(result, op1, op2, op3, op4, op5, op6) \
	 zephir_concat_svsvsv(&result, op1, sizeof(op1)-1, op2, op3, sizeof(op3)-1, op4, op5, sizeof(op5)-1, op6, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_VS(result, op1, op2) \
	 zephir_concat_vs(&result, op1, op2, sizeof(op2)-1, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_VS(result, op1, op2) \
	 zephir_concat_vs(&result, op1, op2, sizeof(op2)-1, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_VSVS(result, op1, op2, op3, op4) \
	 zephir_concat_vsvs(&result, op1, op2, sizeof(op2)-1, op3, op4, sizeof(op4)-1, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_VSVS(result, op1, op2, op3, op4) \
	 zephir_concat_vsvs(&result, op1, op2, sizeof(op2)-1, op3, op4, sizeof(op4)-1, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_VSVSVS(result, op1, op2, op3, op4, op5, op6) \
	 zephir_concat_vsvsvs(&result, op1, op2, sizeof(op2)-1, op3, op4, sizeof(op4)-1, op5, op6, sizeof(op6)-1, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_VSVSVS(result, op1, op2, op3, op4, op5, op6) \
	 zephir_concat_vsvsvs(&result, op1, op2, sizeof(op2)-1, op3, op4, sizeof(op4)-1, op5, op6, sizeof(op6)-1, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_VSVSVSVS(result, op1, op2, op3, op4, op5, op6, op7, op8) \
	 zephir_concat_vsvsvsvs(&result, op1, op2, sizeof(op2)-1, op3, op4, sizeof(op4)-1, op5, op6, sizeof(op6)-1, op7, op8, sizeof(op8)-1, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_VSVSVSVS(result, op1, op2, op3, op4, op5, op6, op7, op8) \
	 zephir_concat_vsvsvsvs(&result, op1, op2, sizeof(op2)-1, op3, op4, sizeof(op4)-1, op5, op6, sizeof(op6)-1, op7, op8, sizeof(op8)-1, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_VV(result, op1, op2) \
	 zephir_concat_vv(&result, op1, op2, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_VV(result, op1, op2) \
	 zephir_concat_vv(&result, op1, op2, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_VVSVV(result, op1, op2, op3, op4, op5) \
	 zephir_concat_vvsvv(&result, op1, op2, op3, sizeof(op3)-1, op4, op5, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_VVSVV(result, op1, op2, op3, op4, op5) \
	 zephir_concat_vvsvv(&result, op1, op2, op3, sizeof(op3)-1, op4, op5, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_VVV(result, op1, op2, op3) \
	 zephir_concat_vvv(&result, op1, op2, op3, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_VVV(result, op1, op2, op3) \
	 zephir_concat_vvv(&result, op1, op2, op3, 1 TSRMLS_CC);


void zephir_concat_ss(zval **result, const char *op1, zend_uint op1_len, const char *op2, zend_uint op2_len, int self_var TSRMLS_DC);
void zephir_concat_ssv(zval **result, const char *op1, zend_uint op1_len, const char *op2, zend_uint op2_len, zval *op3, int self_var TSRMLS_DC);
void zephir_concat_sv(zval **result, const char *op1, zend_uint op1_len, zval *op2, int self_var TSRMLS_DC);
void zephir_concat_svs(zval **result, const char *op1, zend_uint op1_len, zval *op2, const char *op3, zend_uint op3_len, int self_var TSRMLS_DC);
void zephir_concat_svsvs(zval **result, const char *op1, zend_uint op1_len, zval *op2, const char *op3, zend_uint op3_len, zval *op4, const char *op5, zend_uint op5_len, int self_var TSRMLS_DC);
void zephir_concat_svsvsv(zval **result, const char *op1, zend_uint op1_len, zval *op2, const char *op3, zend_uint op3_len, zval *op4, const char *op5, zend_uint op5_len, zval *op6, int self_var TSRMLS_DC);
void zephir_concat_vs(zval **result, zval *op1, const char *op2, zend_uint op2_len, int self_var TSRMLS_DC);
void zephir_concat_vsvs(zval **result, zval *op1, const char *op2, zend_uint op2_len, zval *op3, const char *op4, zend_uint op4_len, int self_var TSRMLS_DC);
void zephir_concat_vsvsvs(zval **result, zval *op1, const char *op2, zend_uint op2_len, zval *op3, const char *op4, zend_uint op4_len, zval *op5, const char *op6, zend_uint op6_len, int self_var TSRMLS_DC);
void zephir_concat_vsvsvsvs(zval **result, zval *op1, const char *op2, zend_uint op2_len, zval *op3, const char *op4, zend_uint op4_len, zval *op5, const char *op6, zend_uint op6_len, zval *op7, const char *op8, zend_uint op8_len, int self_var TSRMLS_DC);
void zephir_concat_vv(zval **result, zval *op1, zval *op2, int self_var TSRMLS_DC);
void zephir_concat_vvsvv(zval **result, zval *op1, zval *op2, const char *op3, zend_uint op3_len, zval *op4, zval *op5, int self_var TSRMLS_DC);
void zephir_concat_vvv(zval **result, zval *op1, zval *op2, zval *op3, int self_var TSRMLS_DC);
void zephir_concat_function(zval *result, zval *op1, zval *op2 TSRMLS_DC);

#endif /* ZEPHIR_KERNEL_CONCAT_H */

