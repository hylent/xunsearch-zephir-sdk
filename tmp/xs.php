<?php
/**
 * Xunsearch PHP-SDK 引导文件
 *
 * 这个文件是由开发工具中的 'build lite' 指令智能合并类定义的源码文件
 * 并删除所有注释而自动生成的。
 *
 * 当您编写搜索项目时，先通过 require 引入该文件即可使用所有的 PHP-SDK
 * 功能。合并的主要目的是便于拷贝，只要复制这个库文件即可，而不用拷贝一
 * 大堆文件。详细文档请阅读 {@link:http://www.xunsearch.com/doc/php/}
 *
 * 切勿手动修改本文件！生成时间：2015/04/02 21:20:56
 *
 * @author hightman
 * @link http://www.xunsearch.com/
 * @copyright Copyright &copy; 2011 HangZhou YunSheng Network Technology Co., Ltd.
 * @license http://www.xunsearch.com/license/
 * @version $Id$
 */

define('XS_LIB_ROOT', dirname(__FILE__));

class XSComponent
{
    public function __get($name)
    {
        $getter = 'get' . $name;
        if (method_exists($this, $getter)) {
            return $this->$getter();
        }
        $msg = method_exists($this, 'set' . $name) ? 'Write-only' : 'Undefined';
        $msg .= ' property: ' . get_class($this) . '::$' . $name;
        throw new XSException($msg);
    }
    public function __set($name, $value)
    {
        $setter = 'set' . $name;
        if (method_exists($this, $setter)) {
            return $this->$setter($value);
        }
        $msg = method_exists($this, 'get' . $name) ? 'Read-only' : 'Undefined';
        $msg .= ' property: ' . get_class($this) . '::$' . $name;
        throw new XSException($msg);
    }
    public function __isset($name)
    {
        return method_exists($this, 'get' . $name);
    }
    public function __unset($name)
    {
        $this->__set($name, null);
    }
}



class XSIndex extends XSServer
{
    private $_buf = '';
    private $_bufSize = 0;
    private $_rebuild = false;
    private static $_adds = array();
    public function addServer($conn)
    {
        $srv = new XSServer($conn, $this->xs);
        self::$_adds[] = $srv;
        return $srv;
    }
    public function execCommand($cmd, $res_arg = XS_CMD_NONE, $res_cmd = XS_CMD_OK)
    {
        $res = parent::execCommand($cmd, $res_arg, $res_cmd);
        foreach (self::$_adds as $srv) {
            $srv->execCommand($cmd, $res_arg, $res_cmd);
        }
        return $res;
    }
    public function clean()
    {
        $this->execCommand(XS_CMD_INDEX_CLEAN_DB, XS_CMD_OK_DB_CLEAN);
        return $this;
    }
    public function add(XSDocument $doc)
    {
        return $this->update($doc, true);
    }
    public function update(XSDocument $doc, $add = false)
    {
        if ($doc->beforeSubmit($this) === false) {
            return $this;
        }
        $fid = $this->xs->getFieldId();
        $key = $doc->f($fid);
        if ($key === null || $key === '') {
            throw new XSException('Missing value of primary key (FIELD:' . $fid . ')');
        }
        $cmd = new XSCommand(XS_CMD_INDEX_REQUEST, XS_CMD_INDEX_REQUEST_ADD);
        if ($add !== true) {
            $cmd->arg1 = XS_CMD_INDEX_REQUEST_UPDATE;
            $cmd->arg2 = $fid->vno;
            $cmd->buf = $key;
        }
        $cmds = array($cmd);
        foreach ($this->xs->getAllFields() as $field) /* @var $field XSFieldMeta */ {
            if (($value = $doc->f($field)) !== null) {
                $varg = $field->isNumeric() ? XS_CMD_VALUE_FLAG_NUMERIC : 0;
                $value = $field->val($value);
                if (!$field->hasCustomTokenizer()) {
                    $wdf = $field->weight | ($field->withPos() ? XS_CMD_INDEX_FLAG_WITHPOS : 0);
                    if ($field->hasIndexMixed()) {
                        $cmds[] = new XSCommand(XS_CMD_DOC_INDEX, $wdf, XSFieldScheme::MIXED_VNO, $value);
                    }
                    if ($field->hasIndexSelf()) {
                        $wdf |= $field->isNumeric() ? 0 : XS_CMD_INDEX_FLAG_SAVEVALUE;
                        $cmds[] = new XSCommand(XS_CMD_DOC_INDEX, $wdf, $field->vno, $value);
                    }
                    if (!$field->hasIndexSelf() || $field->isNumeric()) {
                        $cmds[] = new XSCommand(XS_CMD_DOC_VALUE, $varg, $field->vno, $value);
                    }
                } else {
                    if ($field->hasIndex()) {
                        $terms = $field->getCustomTokenizer()->getTokens($value, $doc);
                        if ($field->hasIndexSelf()) {
                            $wdf = $field->isBoolIndex() ? 1 : ($field->weight | XS_CMD_INDEX_FLAG_CHECKSTEM);
                            foreach ($terms as $term) {
                                if (strlen($term) > 200) {
                                    continue;
                                }
                                $term = strtolower($term);
                                $cmds[] = new XSCommand(XS_CMD_DOC_TERM, $wdf, $field->vno, $term);
                            }
                        }
                        if ($field->hasIndexMixed()) {
                            $mtext = implode(' ', $terms);
                            $cmds[] = new XSCommand(XS_CMD_DOC_INDEX, $field->weight, XSFieldScheme::MIXED_VNO, $mtext);
                        }
                    }
                    $cmds[] = new XSCommand(XS_CMD_DOC_VALUE, $varg, $field->vno, $value);
                }
            }
            if (($terms = $doc->getAddTerms($field)) !== null) {
                $wdf1 = $field->isBoolIndex() ? 0 : XS_CMD_INDEX_FLAG_CHECKSTEM;
                foreach ($terms as $term => $wdf) {
                    $term = strtolower($term);
                    if (strlen($term) > 200) {
                        continue;
                    }
                    $wdf2 = $field->isBoolIndex() ? 1 : $wdf * $field->weight;
                    while ($wdf2 > XSFieldMeta::MAX_WDF) {
                        $cmds[] = new XSCommand(XS_CMD_DOC_TERM, $wdf1 | XSFieldMeta::MAX_WDF, $field->vno, $term);
                        $wdf2 -= XSFieldMeta::MAX_WDF;
                    }
                    $cmds[] = new XSCommand(XS_CMD_DOC_TERM, $wdf1 | $wdf2, $field->vno, $term);
                }
            }
            if (($text = $doc->getAddIndex($field)) !== null) {
                if (!$field->hasCustomTokenizer()) {
                    $wdf = $field->weight | ($field->withPos() ? XS_CMD_INDEX_FLAG_WITHPOS : 0);
                    $cmds[] = new XSCommand(XS_CMD_DOC_INDEX, $wdf, $field->vno, $text);
                } else {
                    $wdf = $field->isBoolIndex() ? 1 : ($field->weight | XS_CMD_INDEX_FLAG_CHECKSTEM);
                    $terms = $field->getCustomTokenizer()->getTokens($text, $doc);
                    foreach ($terms as $term) {
                        if (strlen($term) > 200) {
                            continue;
                        }
                        $term = strtolower($term);
                        $cmds[] = new XSCommand(XS_CMD_DOC_TERM, $wdf, $field->vno, $term);
                    }
                }
            }
        }
        $cmds[] = new XSCommand(XS_CMD_INDEX_SUBMIT);
        if ($this->_bufSize > 0) {
            $this->appendBuffer(implode('', $cmds));
        } else {
            for ($i = 0; $i < count($cmds) - 1; $i++) {
                $this->execCommand($cmds[$i]);
            }
            $this->execCommand($cmds[$i], XS_CMD_OK_RQST_FINISHED);
        }
        $doc->afterSubmit($this);
        return $this;
    }
    public function del($term, $field = null)
    {
        $field = $field === null ? $this->xs->getFieldId() : $this->xs->getField($field);
        $cmds = array();
        $terms = is_array($term) ? array_unique($term) : array($term);
        $terms = XS::convert($terms, 'UTF-8', $this->xs->getDefaultCharset());
        foreach ($terms as $term) {
            $cmds[] = new XSCommand(XS_CMD_INDEX_REMOVE, 0, $field->vno, strtolower($term));
        }
        if ($this->_bufSize > 0) {
            $this->appendBuffer(implode('', $cmds));
        } elseif (count($cmds) == 1) {
            $this->execCommand($cmds[0], XS_CMD_OK_RQST_FINISHED);
        } else {
            $cmd = array('cmd' => XS_CMD_INDEX_EXDATA, 'buf' => implode('', $cmds));
            $this->execCommand($cmd, XS_CMD_OK_RQST_FINISHED);
        }
        return $this;
    }
    public function addExdata($data, $check_file = true)
    {
        if (strlen($data) < 255 && $check_file
                && file_exists($data) && ($data = file_get_contents($data)) === false) {
            throw new XSException('Failed to read exdata from file');
        }
        $first = ord(substr($data, 0, 1));
        if ($first != XS_CMD_IMPORT_HEADER
                && $first != XS_CMD_INDEX_REQUEST && $first != XS_CMD_INDEX_SYNONYMS
                && $first != XS_CMD_INDEX_REMOVE && $first != XS_CMD_INDEX_EXDATA) {
            throw new XSException('Invalid start command of exdata (CMD:' . $first . ')');
        }
        $cmd = array('cmd' => XS_CMD_INDEX_EXDATA, 'buf' => $data);
        $this->execCommand($cmd, XS_CMD_OK_RQST_FINISHED);
        return $this;
    }
    public function addSynonym($raw, $synonym)
    {
        $raw = strval($raw);
        $synonym = strval($synonym);
        if ($raw !== '' && $synonym !== '') {
            $cmd = new XSCommand(XS_CMD_INDEX_SYNONYMS, XS_CMD_INDEX_SYNONYMS_ADD, 0, $raw, $synonym);
            if ($this->_bufSize > 0) {
                $this->appendBuffer(strval($cmd));
            } else {
                $this->execCommand($cmd, XS_CMD_OK_RQST_FINISHED);
            }
        }
        return $this;
    }
    public function delSynonym($raw, $synonym = null)
    {
        $raw = strval($raw);
        $synonym = $synonym === null ? '' : strval($synonym);
        if ($raw !== '') {
            $cmd = new XSCommand(XS_CMD_INDEX_SYNONYMS, XS_CMD_INDEX_SYNONYMS_DEL, 0, $raw, $synonym);
            if ($this->_bufSize > 0) {
                $this->appendBuffer(strval($cmd));
            } else {
                $this->execCommand($cmd, XS_CMD_OK_RQST_FINISHED);
            }
        }
        return $this;
    }
    public function setScwsMulti($level)
    {
        $level = intval($level);
        if ($level >= 0 && $level < 16) {
            $cmd = array('cmd' => XS_CMD_SEARCH_SCWS_SET, 'arg1' => XS_CMD_SCWS_SET_MULTI, 'arg2' => $level);
            $this->execCommand($cmd);
        }
        return $this;
    }
    public function getScwsMulti()
    {
        $cmd = array('cmd' => XS_CMD_SEARCH_SCWS_GET, 'arg1' => XS_CMD_SCWS_GET_MULTI);
        $res = $this->execCommand($cmd, XS_CMD_OK_INFO);
        return intval($res->buf);
    }
    public function openBuffer($size = 4)
    {
        if ($this->_buf !== '') {
            $this->addExdata($this->_buf, false);
        }
        $this->_bufSize = intval($size) << 20;
        $this->_buf = '';
        return $this;
    }
    public function closeBuffer()
    {
        return $this->openBuffer(0);
    }
    public function beginRebuild()
    {
        $this->execCommand(array('cmd' => XS_CMD_INDEX_REBUILD, 'arg1' => 0), XS_CMD_OK_DB_REBUILD);
        $this->_rebuild = true;
        return $this;
    }
    public function endRebuild()
    {
        if ($this->_rebuild === true) {
            $this->_rebuild = false;
            $this->execCommand(array('cmd' => XS_CMD_INDEX_REBUILD, 'arg1' => 1), XS_CMD_OK_DB_REBUILD);
        }
        return $this;
    }
    public function stopRebuild()
    {
        try {
            $this->execCommand(array('cmd' => XS_CMD_INDEX_REBUILD, 'arg1' => 2), XS_CMD_OK_DB_REBUILD);
            $this->_rebuild = false;
        } catch (XSException $e) {
            if ($e->getCode() !== XS_CMD_ERR_WRONGPLACE) {
                throw $e;
            }
        }
        return $this;
    }
    public function setDb($name)
    {
        $this->execCommand(array('cmd' => XS_CMD_INDEX_SET_DB, 'buf' => $name), XS_CMD_OK_DB_CHANGED);
        return $this;
    }
    public function flushLogging()
    {
        try {
            $this->execCommand(XS_CMD_FLUSH_LOGGING, XS_CMD_OK_LOG_FLUSHED);
        } catch (XSException $e) {
            if ($e->getCode() === XS_CMD_ERR_BUSY) {
                return false;
            }
            throw $e;
        }
        return true;
    }
    public function flushIndex()
    {
        try {
            $this->execCommand(XS_CMD_INDEX_COMMIT, XS_CMD_OK_DB_COMMITED);
        } catch (XSException $e) {
            if ($e->getCode() === XS_CMD_ERR_BUSY || $e->getCode() === XS_CMD_ERR_RUNNING) {
                return false;
            }
            throw $e;
        }
        return true;
    }
    public function getCustomDict()
    {
        $res = $this->execCommand(XS_CMD_INDEX_USER_DICT, XS_CMD_OK_INFO);
        return $res->buf;
    }
    public function setCustomDict($content)
    {
        $cmd = array('cmd' => XS_CMD_INDEX_USER_DICT, 'arg1' => 1, 'buf' => $content);
        $this->execCommand($cmd, XS_CMD_OK_DICT_SAVED);
    }
    public function close($ioerr = false)
    {
        $this->closeBuffer();
        parent::close($ioerr);
    }
    private function appendBuffer($buf)
    {
        $this->_buf .= $buf;
        if (strlen($this->_buf) >= $this->_bufSize) {
            $this->addExdata($this->_buf, false);
            $this->_buf = '';
        }
    }
    public function __destruct()
    {
        if ($this->_rebuild === true) {
            try {
                $this->endRebuild();
            } catch (Exception $e) {
            }
        }
        foreach (self::$_adds as $srv) {
            $srv->close();
        }
        self::$_adds = array();
        parent::__destruct();
    }
}
class XSSearch extends XSServer
{
    const PAGE_SIZE = 10;
    const LOG_DB = 'log_db';
    private $_defaultOp = XS_CMD_QUERY_OP_AND;
    private $_prefix, $_fieldSet, $_resetScheme = false;
    private $_query, $_terms, $_count;
    private $_lastCount, $_highlight;
    private $_curDb, $_curDbs = array();
    private $_lastDb, $_lastDbs = array();
    private $_facets = array();
    private $_limit = 0, $_offset = 0;
    private $_charset = 'UTF-8';
    public function open($conn)
    {
        parent::open($conn);
        $this->_prefix = array();
        $this->_fieldSet = false;
        $this->_lastCount = false;
    }
    public function setCharset($charset)
    {
        $this->_charset = strtoupper($charset);
        if ($this->_charset == 'UTF8') {
            $this->_charset = 'UTF-8';
        }
        return $this;
    }
    public function setFuzzy($value = true)
    {
        $this->_defaultOp = $value === true ? XS_CMD_QUERY_OP_OR : XS_CMD_QUERY_OP_AND;
        return $this;
    }
    public function setCutOff($percent, $weight = 0)
    {
        $percent = max(0, min(100, intval($percent)));
        $weight = max(0, (intval($weight * 10) & 255));
        $cmd = new XSCommand(XS_CMD_SEARCH_SET_CUTOFF, $percent, $weight);
        $this->execCommand($cmd);
        return $this;
    }
    public function setRequireMatchedTerm($value = true)
    {
        $arg1 = XS_CMD_SEARCH_MISC_MATCHED_TERM;
        $arg2 = $value === true ? 1 : 0;
        $cmd = new XSCommand(XS_CMD_SEARCH_SET_MISC, $arg1, $arg2);
        $this->execCommand($cmd);
        return $this;
    }
    public function setAutoSynonyms($value = true)
    {
        $flag = XS_CMD_PARSE_FLAG_BOOLEAN | XS_CMD_PARSE_FLAG_PHRASE | XS_CMD_PARSE_FLAG_LOVEHATE;
        if ($value === true) {
            $flag |= XS_CMD_PARSE_FLAG_AUTO_MULTIWORD_SYNONYMS;
        }
        $cmd = array('cmd' => XS_CMD_QUERY_PARSEFLAG, 'arg' => $flag);
        $this->execCommand($cmd);
        return $this;
    }
    public function setSynonymScale($value)
    {
        $arg1 = XS_CMD_SEARCH_MISC_SYN_SCALE;
        $arg2 = max(0, (intval($value * 100) & 255));
        $cmd = new XSCommand(XS_CMD_SEARCH_SET_MISC, $arg1, $arg2);
        $this->execCommand($cmd);
        return $this;
    }
    public function getAllSynonyms($limit = 0, $offset = 0, $stemmed = false)
    {
        $page = $limit > 0 ? pack('II', intval($offset), intval($limit)) : '';
        $cmd = array('cmd' => XS_CMD_SEARCH_GET_SYNONYMS, 'buf1' => $page);
        $cmd['arg1'] = $stemmed == true ? 1 : 0;
        $res = $this->execCommand($cmd, XS_CMD_OK_RESULT_SYNONYMS);
        $ret = array();
        if (!empty($res->buf)) {
            foreach (explode("\n", $res->buf) as $line) {
                $value = explode("\t", $line);
                $key = array_shift($value);
                $ret[$key] = $value;
            }
        }
        return $ret;
    }
    public function getSynonyms($term)
    {
        $term = strval($term);
        if (strlen($term) === 0) {
            return false;
        }
        $cmd = array('cmd' => XS_CMD_SEARCH_GET_SYNONYMS, 'arg1' => 2, 'buf' => $term);
        $res = $this->execCommand($cmd, XS_CMD_OK_RESULT_SYNONYMS);
        $ret = $res->buf === '' ? array() : explode("\n", $res->buf);
        return $ret;
    }
    public function getQuery($query = null)
    {
        $query = $query === null ? '' : $this->preQueryString($query);
        $cmd = new XSCommand(XS_CMD_QUERY_GET_STRING, 0, $this->_defaultOp, $query);
        $res = $this->execCommand($cmd, XS_CMD_OK_QUERY_STRING);
        if (strpos($res->buf, 'VALUE_RANGE') !== false) {
            $regex = '/(VALUE_RANGE) (\d+) (\S+) (.+?)(?=\))/';
            $res->buf = preg_replace_callback($regex, array($this, 'formatValueRange'), $res->buf);
        }
        if (strpos($res->buf, 'VALUE_GE') !== false || strpos($res->buf, 'VALUE_LE') !== false) {
            $regex = '/(VALUE_[GL]E) (\d+) (.+?)(?=\))/';
            $res->buf = preg_replace_callback($regex, array($this, 'formatValueRange'), $res->buf);
        }
        return XS::convert($res->buf, $this->_charset, 'UTF-8');
    }
    public function setQuery($query)
    {
        $this->clearQuery();
        if ($query !== null) {
            $this->_query = $query;
            $this->addQueryString($query);
        }
        return $this;
    }
    public function setMultiSort($fields, $reverse = false, $relevance_first = false)
    {
        if (!is_array($fields)) {
            return $this->setSort($fields, !$reverse, $relevance_first);
        }
        $buf = '';
        foreach ($fields as $key => $value) {
            if (is_bool($value)) {
                $vno = $this->xs->getField($key, true)->vno;
                $asc = $value;
            } else {
                $vno = $this->xs->getField($value, true)->vno;
                $asc = false;
            }
            if ($vno != XSFieldScheme::MIXED_VNO) {
                $buf .= chr($vno) . chr($asc ? 1 : 0);
            }
        }
        if ($buf !== '') {
            $type = XS_CMD_SORT_TYPE_MULTI;
            if ($relevance_first) {
                $type |= XS_CMD_SORT_FLAG_RELEVANCE;
            }
            if (!$reverse) {
                $type |= XS_CMD_SORT_FLAG_ASCENDING;
            }
            $cmd = new XSCommand(XS_CMD_SEARCH_SET_SORT, $type, 0, $buf);
            $this->execCommand($cmd);
        }
        return $this;
    }
    public function setSort($field, $asc = false, $relevance_first = false)
    {
        if (is_array($field)) {
            return $this->setMultiSort($field, $asc, $relevance_first);
        }
        if ($field === null) {
            $cmd = new XSCommand(XS_CMD_SEARCH_SET_SORT, XS_CMD_SORT_TYPE_RELEVANCE);
        } else {
            $type = XS_CMD_SORT_TYPE_VALUE;
            if ($relevance_first) {
                $type |= XS_CMD_SORT_FLAG_RELEVANCE;
            }
            if ($asc) {
                $type |= XS_CMD_SORT_FLAG_ASCENDING;
            }
            $vno = $this->xs->getField($field, true)->vno;
            $cmd = new XSCommand(XS_CMD_SEARCH_SET_SORT, $type, $vno);
        }
        $this->execCommand($cmd);
        return $this;
    }
    public function setDocOrder($asc = false)
    {
        $type = XS_CMD_SORT_TYPE_DOCID | ($asc ? XS_CMD_SORT_FLAG_ASCENDING : 0);
        $cmd = new XSCommand(XS_CMD_SEARCH_SET_SORT, $type);
        $this->execCommand($cmd);
        return $this;
    }
    public function setCollapse($field, $num = 1)
    {
        $vno = $field === null ? XSFieldScheme::MIXED_VNO : $this->xs->getField($field, true)->vno;
        $max = min(255, intval($num));
        $cmd = new XSCommand(XS_CMD_SEARCH_SET_COLLAPSE, $max, $vno);
        $this->execCommand($cmd);
        return $this;
    }
    public function addRange($field, $from, $to)
    {
        if ($from === '' || $from === false) {
            $from = null;
        }
        if ($to === '' || $to === false) {
            $to = null;
        }
        if ($from !== null || $to !== null) {
            if (strlen($from) > 255 || strlen($to) > 255) {
                throw new XSException('Value of range is too long');
            }
            $vno = $this->xs->getField($field)->vno;
            $from = XS::convert($from, 'UTF-8', $this->_charset);
            $to = XS::convert($to, 'UTF-8', $this->_charset);
            if ($from === null) {
                $cmd = new XSCommand(XS_CMD_QUERY_VALCMP, XS_CMD_QUERY_OP_FILTER, $vno, $to, chr(XS_CMD_VALCMP_LE));
            } elseif ($to === null) {
                $cmd = new XSCommand(XS_CMD_QUERY_VALCMP, XS_CMD_QUERY_OP_FILTER, $vno, $from, chr(XS_CMD_VALCMP_GE));
            } else {
                $cmd = new XSCommand(XS_CMD_QUERY_RANGE, XS_CMD_QUERY_OP_FILTER, $vno, $from, $to);
            }
            $this->execCommand($cmd);
        }
        return $this;
    }
    public function addWeight($field, $term, $weight = 1)
    {
        return $this->addQueryTerm($field, $term, XS_CMD_QUERY_OP_AND_MAYBE, $weight);
    }
    public function setFacets($field, $exact = false)
    {
        $buf = '';
        if (!is_array($field)) {
            $field = array($field);
        }
        foreach ($field as $name) {
            $ff = $this->xs->getField($name);
            if ($ff->type !== XSFieldMeta::TYPE_STRING) {
                throw new XSException("Field `$name' cann't be used for facets search, can only be string type");
            }
            $buf .= chr($ff->vno);
        }
        $cmd = array('cmd' => XS_CMD_SEARCH_SET_FACETS, 'buf' => $buf);
        $cmd['arg1'] = $exact === true ? 1 : 0;
        $this->execCommand($cmd);
        return $this;
    }
    public function getFacets($field = null)
    {
        if ($field === null) {
            return $this->_facets;
        }
        return isset($this->_facets[$field]) ? $this->_facets[$field] : array();
    }
    public function setScwsMulti($level)
    {
        $level = intval($level);
        if ($level >= 0 && $level < 16) {
            $cmd = array('cmd' => XS_CMD_SEARCH_SCWS_SET, 'arg1' => XS_CMD_SCWS_SET_MULTI, 'arg2' => $level);
            $this->execCommand($cmd);
        }
        return $this;
    }
    public function setLimit($limit, $offset = 0)
    {
        $this->_limit = intval($limit);
        $this->_offset = intval($offset);
        return $this;
    }
    public function setDb($name)
    {
        $name = strval($name);
        $this->execCommand(array('cmd' => XS_CMD_SEARCH_SET_DB, 'buf' => strval($name)));
        $this->_lastDb = $this->_curDb;
        $this->_lastDbs = $this->_curDbs;
        $this->_curDb = $name;
        $this->_curDbs = array();
        return $this;
    }
    public function addDb($name)
    {
        $name = strval($name);
        $this->execCommand(array('cmd' => XS_CMD_SEARCH_ADD_DB, 'buf' => $name));
        $this->_curDbs[] = $name;
        return $this;
    }
    public function markResetScheme()
    {
        $this->_resetScheme = true;
    }
    public function terms($query = null, $convert = true)
    {
        $query = $query === null ? '' : $this->preQueryString($query);
        if ($query === '' && $this->_terms !== null) {
            $ret = $this->_terms;
        } else {
            $cmd = new XSCommand(XS_CMD_QUERY_GET_TERMS, 0, $this->_defaultOp, $query);
            $res = $this->execCommand($cmd, XS_CMD_OK_QUERY_TERMS);
            $ret = array();
            $tmps = explode(' ', $res->buf);
            for ($i = 0; $i < count($tmps); $i++) {
                if ($tmps[$i] === '' || strpos($tmps[$i], ':') !== false) {
                    continue;
                }
                $ret[] = $tmps[$i];
            }
            if ($query === '') {
                $this->_terms = $ret;
            }
        }
        return $convert ? XS::convert($ret, $this->_charset, 'UTF-8') : $ret;
    }
    public function count($query = null)
    {
        $query = $query === null ? '' : $this->preQueryString($query);
        if ($query === '' && $this->_count !== null) {
            return $this->_count;
        }
        $cmd = new XSCommand(XS_CMD_SEARCH_GET_TOTAL, 0, $this->_defaultOp, $query);
        $res = $this->execCommand($cmd, XS_CMD_OK_SEARCH_TOTAL);
        $ret = unpack('Icount', $res->buf);
        if ($query === '') {
            $this->_count = $ret['count'];
        }
        return $ret['count'];
    }
    public function search($query = null, $saveHighlight = true)
    {
        if ($this->_curDb !== self::LOG_DB && $saveHighlight) {
            $this->_highlight = $query;
        }
        $query = $query === null ? '' : $this->preQueryString($query);
        $page = pack('II', $this->_offset, $this->_limit > 0 ? $this->_limit : self::PAGE_SIZE);
        $cmd = new XSCommand(XS_CMD_SEARCH_GET_RESULT, 0, $this->_defaultOp, $query, $page);
        $res = $this->execCommand($cmd, XS_CMD_OK_RESULT_BEGIN);
        $tmp = unpack('Icount', $res->buf);
        $this->_lastCount = $tmp['count'];
        $ret = $this->_facets = array();
        $vnoes = $this->xs->getScheme()->getVnoMap();
        while (true) {
            $res = $this->getRespond();
            if ($res->cmd == XS_CMD_SEARCH_RESULT_FACETS) {
                $off = 0;
                while (($off + 6) < strlen($res->buf)) {
                    $tmp = unpack('Cvno/Cvlen/Inum', substr($res->buf, $off, 6));
                    if (isset($vnoes[$tmp['vno']])) {
                        $name = $vnoes[$tmp['vno']];
                        $value = substr($res->buf, $off + 6, $tmp['vlen']);
                        if (!isset($this->_facets[$name])) {
                            $this->_facets[$name] = array();
                        }
                        $this->_facets[$name][$value] = $tmp['num'];
                    }
                    $off += $tmp['vlen'] + 6;
                }
            } elseif ($res->cmd == XS_CMD_SEARCH_RESULT_DOC) {
                $doc = new XSDocument($res->buf, $this->_charset);
                $ret[] = $doc;
            } elseif ($res->cmd == XS_CMD_SEARCH_RESULT_FIELD) {
                if (isset($doc)) {
                    $name = isset($vnoes[$res->arg]) ? $vnoes[$res->arg] : $res->arg;
                    $doc->setField($name, $res->buf);
                }
            } elseif ($res->cmd == XS_CMD_SEARCH_RESULT_MATCHED) {
                if (isset($doc)) {
                    $doc->setField('matched', explode(' ', $res->buf), true);
                }
            } elseif ($res->cmd == XS_CMD_OK && $res->arg == XS_CMD_OK_RESULT_END) {
                break;
            } else {
                $msg = 'Unexpected respond in search {CMD:' . $res->cmd . ', ARG:' . $res->arg . '}';
                throw new XSException($msg);
            }
        }
        if ($query === '') {
            $this->_count = $this->_lastCount;
            if ($this->_curDb !== self::LOG_DB) {
                $this->logQuery();
                if ($saveHighlight) {
                    $this->initHighlight();
                }
            }
        }
        $this->_limit = $this->_offset = 0;
        return $ret;
    }
    public function getLastCount()
    {
        return $this->_lastCount;
    }
    public function getDbTotal()
    {
        $cmd = new XSCommand(XS_CMD_SEARCH_DB_TOTAL);
        $res = $this->execCommand($cmd, XS_CMD_OK_DB_TOTAL);
        $tmp = unpack('Itotal', $res->buf);
        return $tmp['total'];
    }
    public function getHotQuery($limit = 6, $type = 'total')
    {
        $ret = array();
        $limit = max(1, min(50, intval($limit)));
        $this->xs->setScheme(XSFieldScheme::logger());
        try {
            $this->setDb(self::LOG_DB)->setLimit($limit);
            if ($type !== 'lastnum' && $type !== 'currnum') {
                $type = 'total';
            }
            $result = $this->search($type . ':1');
            foreach ($result as $doc) /* @var $doc XSDocument */ {
                $body = $doc->body;
                $ret[$body] = $doc->f($type);
            }
            $this->restoreDb();
        } catch (XSException $e) {
            if ($e->getCode() != XS_CMD_ERR_XAPIAN) {
                throw $e;
            }
        }
        $this->xs->restoreScheme();
        return $ret;
    }
    public function getRelatedQuery($query = null, $limit = 6)
    {
        $ret = array();
        $limit = max(1, min(20, intval($limit)));
        if ($query === null) {
            $query = $this->cleanFieldQuery($this->_query);
        }
        if (empty($query) || strpos($query, ':') !== false) {
            return $ret;
        }
        $op = $this->_defaultOp;
        $this->xs->setScheme(XSFieldScheme::logger());
        try {
            $result = $this->setDb(self::LOG_DB)->setFuzzy()->setLimit($limit + 1)->search($query);
            foreach ($result as $doc) /* @var $doc XSDocument */ {
                $doc->setCharset($this->_charset);
                $body = $doc->body;
                if (!strcasecmp($body, $query)) {
                    continue;
                }
                $ret[] = $body;
                if (count($ret) == $limit) {
                    break;
                }
            }
        } catch (XSException $e) {
            if ($e->getCode() != XS_CMD_ERR_XAPIAN) {
                throw $e;
            }
        }
        $this->restoreDb();
        $this->xs->restoreScheme();
        $this->_defaultOp = $op;
        return $ret;
    }
    public function getExpandedQuery($query, $limit = 10)
    {
        $ret = array();
        $limit = max(1, min(20, intval($limit)));
        try {
            $buf = XS::convert($query, 'UTF-8', $this->_charset);
            $cmd = array('cmd' => XS_CMD_QUERY_GET_EXPANDED, 'arg1' => $limit, 'buf' => $buf);
            $res = $this->execCommand($cmd, XS_CMD_OK_RESULT_BEGIN);
            while (true) {
                $res = $this->getRespond();
                if ($res->cmd == XS_CMD_SEARCH_RESULT_FIELD) {
                    $ret[] = XS::convert($res->buf, $this->_charset, 'UTF-8');
                } elseif ($res->cmd == XS_CMD_OK && $res->arg == XS_CMD_OK_RESULT_END) {
                    break;
                } else {
                    $msg = 'Unexpected respond in search {CMD:' . $res->cmd . ', ARG:' . $res->arg . '}';
                    throw new XSException($msg);
                }
            }
        } catch (XSException $e) {
            if ($e->getCode() != XS_CMD_ERR_XAPIAN) {
                throw $e;
            }
        }
        return $ret;
    }
    public function getCorrectedQuery($query = null)
    {
        $ret = array();
        try {
            if ($query === null) {
                if ($this->_count > 0 && $this->_count > ceil($this->getDbTotal() * 0.001)) {
                    return $ret;
                }
                $query = $this->cleanFieldQuery($this->_query);
            }
            if (empty($query) || strpos($query, ':') !== false) {
                return $ret;
            }
            $buf = XS::convert($query, 'UTF-8', $this->_charset);
            $cmd = array('cmd' => XS_CMD_QUERY_GET_CORRECTED, 'buf' => $buf);
            $res = $this->execCommand($cmd, XS_CMD_OK_QUERY_CORRECTED);
            if ($res->buf !== '') {
                $ret = explode("\n", XS::convert($res->buf, $this->_charset, 'UTF-8'));
            }
        } catch (XSException $e) {
            if ($e->getCode() != XS_CMD_ERR_XAPIAN) {
                throw $e;
            }
        }
        return $ret;
    }
    public function addSearchLog($query, $wdf = 1)
    {
        $cmd = array('cmd' => XS_CMD_SEARCH_ADD_LOG, 'buf' => $query);
        if ($wdf > 1) {
            $cmd['buf1'] = pack('i', $wdf);
        }
        $this->execCommand($cmd, XS_CMD_OK_LOGGED);
    }
    public function highlight($value, $strtr = false)
    {
        if (empty($value)) {
            return $value;
        }
        if (!is_array($this->_highlight)) {
            $this->initHighlight();
        }
        if (isset($this->_highlight['pattern'])) {
            $value = preg_replace($this->_highlight['pattern'], $this->_highlight['replace'], $value);
        }
        if (isset($this->_highlight['pairs'])) {
            $value = $strtr ?
                strtr($value, $this->_highlight['pairs']) :
                str_replace(array_keys($this->_highlight['pairs']), array_values($this->_highlight['pairs']), $value);
        }
        return $value;
    }
    private function logQuery($query = null)
    {
        if ($this->isRobotAgent()) {
            return;
        }
        if ($query !== '' && $query !== null) {
            $terms = $this->terms($query, false);
        } else {
            $query = $this->_query;
            if (!$this->_lastCount || ($this->_defaultOp == XS_CMD_QUERY_OP_OR && strpos($query, ' '))
                || strpos($query, ' OR ') || strpos($query, ' NOT ') || strpos($query, ' XOR ')) {
                return;
            }
            $terms = $this->terms(null, false);
        }
        $log = '';
        $pos = $max = 0;
        foreach ($terms as $term) {
            $pos1 = ($pos > 3 && strlen($term) === 6) ? $pos - 3 : $pos;
            if (($pos2 = strpos($query, $term, $pos1)) === false) {
                continue;
            }
            if ($pos2 === $pos) {
                $log .= $term;
            } elseif ($pos2 < $pos) {
                $log .= substr($term, 3);
            } else {
                if (++$max > 3 || strlen($log) > 42) {
                    break;
                }
                $log .= ' ' . $term;
            }
            $pos = $pos2 + strlen($term);
        }
        $log = trim($log);
        if (strlen($log) < 2 || (strlen($log) == 3 && ord($log[0]) > 0x80)) {
            return;
        }
        $this->addSearchLog($log);
    }
    private function clearQuery()
    {
        $cmd = new XSCommand(XS_CMD_QUERY_INIT);
        if ($this->_resetScheme === true) {
            $cmd->arg1 = 1;
            $this->_prefix = array();
            $this->_fieldSet = false;
            $this->_resetScheme = false;
        }
        $this->execCommand($cmd);
        $this->_query = $this->_count = $this->_terms = null;
    }
    public function addQueryString($query, $addOp = XS_CMD_QUERY_OP_AND, $scale = 1)
    {
        $query = $this->preQueryString($query);
        $bscale = ($scale > 0 && $scale != 1) ? pack('n', intval($scale * 100)) : '';
        $cmd = new XSCommand(XS_CMD_QUERY_PARSE, $addOp, $this->_defaultOp, $query, $bscale);
        $this->execCommand($cmd);
        return $query;
    }
    public function addQueryTerm($field, $term, $addOp = XS_CMD_QUERY_OP_AND, $scale = 1)
    {
        $term = strtolower($term);
        $term = XS::convert($term, 'UTF-8', $this->_charset);
        $bscale = ($scale > 0 && $scale != 1) ? pack('n', intval($scale * 100)) : '';
        $vno = $field === null ? XSFieldScheme::MIXED_VNO : $this->xs->getField($field, true)->vno;
        $cmd = new XSCommand(XS_CMD_QUERY_TERM, $addOp, $vno, $term, $bscale);
        $this->execCommand($cmd);
        return $this;
    }
    private function restoreDb()
    {
        $db = $this->_lastDb;
        $dbs = $this->_lastDbs;
        $this->setDb($db);
        foreach ($dbs as $name) {
            $this->addDb($name);
        }
    }
    private function preQueryString($query)
    {
        $query = trim($query);
        if ($this->_resetScheme === true) {
            $this->clearQuery();
        }
        $this->initSpecialField();
        $newQuery = '';
        $parts = preg_split('/[ \t\r\n]+/', $query);
        foreach ($parts as $part) {
            if ($part === '') {
                continue;
            }
            if ($newQuery != '') {
                $newQuery .= ' ';
            }
            if (($pos = strpos($part, ':', 1)) !== false) {
                for ($i = 0; $i < $pos; $i++) {
                    if (strpos('+-~(', $part[$i]) === false) {
                        break;
                    }
                }
                $name = substr($part, $i, $pos - $i);
                if (($field = $this->xs->getField($name, false)) !== false
                    && $field->vno != XSFieldScheme::MIXED_VNO) {
                    $this->regQueryPrefix($name);
                    if ($field->hasCustomTokenizer()) {
                        $prefix = $i > 0 ? substr($part, 0, $i) : '';
                        $suffix = '';
                        $value = substr($part, $pos + 1);
                        if (substr($value, -1, 1) === ')') {
                            $suffix = ')';
                            $value = substr($value, 0, -1);
                        }
                        $terms = array();
                        $tokens = $field->getCustomTokenizer()->getTokens($value);
                        foreach ($tokens as $term) {
                            $terms[] = strtolower($term);
                        }
                        $terms = array_unique($terms);
                        $newQuery .= $prefix . $name . ':' . implode(' ' . $name . ':', $terms) . $suffix;
                    } elseif (substr($part, $pos + 1, 1) != '(' && preg_match('/[\x81-\xfe]/', $part)) {
                        $newQuery .= substr($part, 0, $pos + 1) . '(' . substr($part, $pos + 1) . ')';
                    } else {
                        $newQuery .= $part;
                    }
                    continue;
                }
            }
            if (strlen($part) > 1 && ($part[0] == '+' || $part[0] == '-') && $part[1] != '('
                && preg_match('/[\x81-\xfe]/', $part)) {
                $newQuery .= substr($part, 0, 1) . '(' . substr($part, 1) . ')';
                continue;
            }
            $newQuery .= $part;
        }
        return XS::convert($newQuery, 'UTF-8', $this->_charset);
    }
    private function regQueryPrefix($name)
    {
        if (!isset($this->_prefix[$name])
            && ($field = $this->xs->getField($name, false))
            && ($field->vno != XSFieldScheme::MIXED_VNO)) {
            $type = $field->isBoolIndex() ? XS_CMD_PREFIX_BOOLEAN : XS_CMD_PREFIX_NORMAL;
            $cmd = new XSCommand(XS_CMD_QUERY_PREFIX, $type, $field->vno, $name);
            $this->execCommand($cmd);
            $this->_prefix[$name] = true;
        }
    }
    private function initSpecialField()
    {
        if ($this->_fieldSet === true) {
            return;
        }
        foreach ($this->xs->getAllFields() as $field) /* @var $field XSFieldMeta */ {
            if ($field->cutlen != 0) {
                $len = min(127, ceil($field->cutlen / 10));
                $cmd = new XSCommand(XS_CMD_SEARCH_SET_CUT, $len, $field->vno);
                $this->execCommand($cmd);
            }
            if ($field->isNumeric()) {
                $cmd = new XSCommand(XS_CMD_SEARCH_SET_NUMERIC, 0, $field->vno);
                $this->execCommand($cmd);
            }
        }
        $this->_fieldSet = true;
    }
    private function cleanFieldQuery($query)
    {
        $query = strtr($query, array(' AND ' => ' ', ' OR ' => ' '));
        if (strpos($query, ':') !== false) {
            $regex = '/(^|\s)([0-9A-Za-z_\.-]+):([^\s]+)/';
            return preg_replace_callback($regex, array($this, 'cleanFieldCallback'), $query);
        }
        return $query;
    }
    private function cleanFieldCallback($match)
    {
        if (($field = $this->xs->getField($match[2], false)) === false) {
            return $match[0];
        }
        if ($field->isBoolIndex()) {
            return '';
        }
        if (substr($match[3], 0, 1) == '(' && substr($match[3], -1, 1) == ')') {
            $match[3] = substr($match[3], 1, -1);
        }
        return $match[1] . $match[3];
    }
    private function initHighlight()
    {
        $terms = array();
        $tmps = $this->terms($this->_highlight, false);
        for ($i = 0; $i < count($tmps); $i++) {
            if (strlen($tmps[$i]) !== 6 || ord(substr($tmps[$i], 0, 1)) < 0xc0) {
                $terms[] = XS::convert($tmps[$i], $this->_charset, 'UTF-8');
                continue;
            }
            for ($j = $i + 1; $j < count($tmps); $j++) {
                if (strlen($tmps[$j]) !== 6 || substr($tmps[$j], 0, 3) !== substr($tmps[$j - 1], 3, 3)) {
                    break;
                }
            }
            if (($k = ($j - $i)) === 1) {
                $terms[] = XS::convert($tmps[$i], $this->_charset, 'UTF-8');
            } else {
                $i = $j - 1;
                while ($k--) {
                    $j--;
                    if ($k & 1) {
                        $terms[] = XS::convert(substr($tmps[$j - 1], 0, 3) . $tmps[$j], $this->_charset, 'UTF-8');
                    }
                    $terms[] = XS::convert($tmps[$j], $this->_charset, 'UTF-8');
                }
            }
        }
        $pattern = $replace = $pairs = array();
        foreach ($terms as $term) {
            if (!preg_match('/[a-zA-Z]/', $term)) {
                $pairs[$term] = '<em>' . $term . '</em>';
            } else {
                $pattern[] = '/' . strtr($term, array('+' => '\\+', '/' => '\\/')) . '/i';
                $replace[] = '<em>$0</em>';
            }
        }
        $this->_highlight = array();
        if (count($pairs) > 0) {
            $this->_highlight['pairs'] = $pairs;
        }
        if (count($pattern) > 0) {
            $this->_highlight['pattern'] = $pattern;
            $this->_highlight['replace'] = $replace;
        }
    }
    private function formatValueRange($match)
    {
        $field = $this->xs->getField(intval($match[2]), false);
        if ($field === false) {
            return $match[0];
        }
        $val1 = $val2 = '~';
        if (isset($match[4])) {
            $val2 = $field->isNumeric() ? $this->xapianUnserialise($match[4]) : $match[4];
        }
        if ($match[1] === 'VALUE_LE') {
            $val2 = $field->isNumeric() ? $this->xapianUnserialise($match[3]) : $match[3];
        } else {
            $val1 = $field->isNumeric() ? $this->xapianUnserialise($match[3]) : $match[3];
        }
        return $field->name . ':[' . $val1 . ',' . $val2 . ']';
    }
    private function numfromstr($str, $index)
    {
        return $index < strlen($str) ? ord($str[$index]) : 0;
    }
    private function xapianUnserialise($value)
    {
        if ($value === "\x80") {
            return 0.0;
        }
        if ($value === str_repeat("\xff", 9)) {
            return INF;
        }
        if ($value === '') {
            return -INF;
        }
        $i = 0;
        $c = ord($value[0]);
        $c ^= ($c & 0xc0) >> 1;
        $negative = !($c & 0x80) ? 1 : 0;
        $exponent_negative = ($c & 0x40) ? 1 : 0;
        $explen = !($c & 0x20) ? 1 : 0;
        $exponent = $c & 0x1f;
        if (!$explen) {
            $exponent >>= 2;
            if ($negative ^ $exponent_negative) {
                $exponent ^= 0x07;
            }
        } else {
            $c = $this->numfromstr($value, ++$i);
            $exponent <<= 6;
            $exponent |= ($c >> 2);
            if ($negative ^ $exponent_negative) {
                $exponent &= 0x07ff;
            }
        }
        $word1 = ($c & 0x03) << 24;
        $word1 |= $this->numfromstr($value, ++$i) << 16;
        $word1 |= $this->numfromstr($value, ++$i) << 8;
        $word1 |= $this->numfromstr($value, ++$i);
        $word2 = 0;
        if ($i < strlen($value)) {
            $word2 = $this->numfromstr($value, ++$i) << 24;
            $word2 |= $this->numfromstr($value, ++$i) << 16;
            $word2 |= $this->numfromstr($value, ++$i) << 8;
            $word2 |= $this->numfromstr($value, ++$i);
        }
        if (!$negative) {
            $word1 |= 1 << 26;
        } else {
            $word1 = 0 - $word1;
            if ($word2 != 0) {
                ++$word1;
            }
            $word2 = 0 - $word2;
            $word1 &= 0x03ffffff;
        }
        $mantissa = 0;
        if ($word2) {
            $mantissa = $word2 / 4294967296.0; // 1<<32
        }
        $mantissa += $word1;
        $mantissa /= 1 << ($negative === 1 ? 26 : 27);
        if ($exponent_negative) {
            $exponent = 0 - $exponent;
        }
        $exponent += 8;
        if ($negative) {
            $mantissa = 0 - $mantissa;
        }
        return round($mantissa * pow(2, $exponent), 2);
    }
    private function isRobotAgent()
    {
        if (isset($_SERVER['HTTP_USER_AGENT'])) {
            $agent = strtolower($_SERVER['HTTP_USER_AGENT']);
            $keys = array('bot', 'slurp', 'spider', 'crawl', 'curl');
            foreach ($keys as $key) {
                if (strpos($agent, $key) !== false) {
                    return true;
                }
            }
        }
        return false;
    }
}


class XSTokenizerNone implements XSTokenizer
{
    public function getTokens($value, XSDocument $doc = null)
    {
        return array();
    }
}
class XSTokenizerFull implements XSTokenizer
{
    public function getTokens($value, XSDocument $doc = null)
    {
        return array($value);
    }
}
class XSTokenizerSplit implements XSTokenizer
{
    private $arg = ' ';
    public function __construct($arg = null)
    {
        if ($arg !== null && $arg !== '') {
            $this->arg = $arg;
        }
    }
    public function getTokens($value, XSDocument $doc = null)
    {
        if (strlen($this->arg) > 2 && substr($this->arg, 0, 1) == '/' && substr($this->arg, -1, 1) == '/') {
            return preg_split($this->arg, $value);
        }
        return explode($this->arg, $value);
    }
}
class XSTokenizerXlen implements XSTokenizer
{
    private $arg = 2;
    public function __construct($arg = null)
    {
        if ($arg !== null && $arg !== '') {
            $this->arg = intval($arg);
            if ($this->arg < 1 || $this->arg > 255) {
                throw new XSException('Invalid argument for ' . __CLASS__ . ': ' . $arg);
            }
        }
    }
    public function getTokens($value, XSDocument $doc = null)
    {
        $terms = array();
        for ($i = 0; $i < strlen($value); $i += $this->arg) {
            $terms[] = substr($value, $i, $this->arg);
        }
        return $terms;
    }
}
class XSTokenizerXstep implements XSTokenizer
{
    private $arg = 2;
    public function __construct($arg = null)
    {
        if ($arg !== null && $arg !== '') {
            $this->arg = intval($arg);
            if ($this->arg < 1 || $this->arg > 255) {
                throw new XSException('Invalid argument for ' . __CLASS__ . ': ' . $arg);
            }
        }
    }
    public function getTokens($value, XSDocument $doc = null)
    {
        $terms = array();
        $i = $this->arg;
        while (true) {
            $terms[] = substr($value, 0, $i);
            if ($i >= strlen($value)) {
                break;
            }
            $i += $this->arg;
        }
        return $terms;
    }
}
class XSTokenizerScws implements XSTokenizer
{
    const MULTI_MASK = 15;
    private static $_charset;
    private $_setting = array();
    private static $_server;
    public function __construct($arg = null)
    {
        if (self::$_server === null) {
            $xs = XS::getLastXS();
            if ($xs === null) {
                throw new XSException('An XS instance should be created before using ' . __CLASS__);
            }
            self::$_server = $xs->getScwsServer();
            self::$_server->setTimeout(0);
            self::$_charset = $xs->getDefaultCharset();
            if (!defined('SCWS_MULTI_NONE')) {
                define('SCWS_MULTI_NONE', 0);
                define('SCWS_MULTI_SHORT', 1);
                define('SCWS_MULTI_DUALITY', 2);
                define('SCWS_MULTI_ZMAIN', 4);
                define('SCWS_MULTI_ZALL', 8);
            }
            if (!defined('SCWS_XDICT_XDB')) {
                define('SCWS_XDICT_XDB', 1);
                define('SCWS_XDICT_MEM', 2);
                define('SCWS_XDICT_TXT', 4);
            }
        }
        if ($arg !== null && $arg !== '') {
            $this->setMulti($arg);
        }
    }
    public function getTokens($value, XSDocument $doc = null)
    {
        $tokens = array();
        $this->setIgnore(true);
        $_charset = self::$_charset;
        self::$_charset = 'UTF-8';
        $words = $this->getResult($value);
        foreach ($words as $word) {
            $tokens[] = $word['word'];
        }
        self::$_charset = $_charset;
        return $tokens;
    }
    public function setCharset($charset)
    {
        self::$_charset = strtoupper($charset);
        if (self::$_charset == 'UTF8') {
            self::$_charset = 'UTF-8';
        }
        return $this;
    }
    public function setIgnore($yes = true)
    {
        $this->_setting['ignore'] = new XSCommand(XS_CMD_SEARCH_SCWS_SET, XS_CMD_SCWS_SET_IGNORE, $yes === false
                            ? 0 : 1);
        return $this;
    }
    public function setMulti($mode = 3)
    {
        $mode = intval($mode) & self::MULTI_MASK;
        $this->_setting['multi'] = new XSCommand(XS_CMD_SEARCH_SCWS_SET, XS_CMD_SCWS_SET_MULTI, $mode);
        return $this;
    }
    public function setDict($fpath, $mode = null)
    {
        if (!is_int($mode)) {
            $mode = stripos($fpath, '.txt') !== false ? SCWS_XDICT_TXT : SCWS_XDICT_XDB;
        }
        $this->_setting['set_dict'] = new XSCommand(XS_CMD_SEARCH_SCWS_SET, XS_CMD_SCWS_SET_DICT, $mode, $fpath);
        unset($this->_setting['add_dict']);
        return $this;
    }
    public function addDict($fpath, $mode = null)
    {
        if (!is_int($mode)) {
            $mode = stripos($fpath, '.txt') !== false ? SCWS_XDICT_TXT : SCWS_XDICT_XDB;
        }
        if (!isset($this->_setting['add_dict'])) {
            $this->_setting['add_dict'] = array();
        }
        $this->_setting['add_dict'][] = new XSCommand(XS_CMD_SEARCH_SCWS_SET, XS_CMD_SCWS_ADD_DICT, $mode, $fpath);
        return $this;
    }
    public function setDuality($yes = true)
    {
        $this->_setting['duality'] = new XSCommand(XS_CMD_SEARCH_SCWS_SET, XS_CMD_SCWS_SET_DUALITY, $yes === false
                            ? 0 : 1);
        return $this;
    }
    public function getVersion()
    {
        $cmd = new XSCommand(XS_CMD_SEARCH_SCWS_GET, XS_CMD_SCWS_GET_VERSION);
        $res = self::$_server->execCommand($cmd, XS_CMD_OK_INFO);
        return $res->buf;
    }
    public function getResult($text)
    {
        $words = array();
        $text = $this->applySetting($text);
        $cmd = new XSCommand(XS_CMD_SEARCH_SCWS_GET, XS_CMD_SCWS_GET_RESULT, 0, $text);
        $res = self::$_server->execCommand($cmd, XS_CMD_OK_SCWS_RESULT);
        while ($res->buf !== '') {
            $tmp = unpack('Ioff/a4attr/a*word', $res->buf);
            $tmp['word'] = XS::convert($tmp['word'], self::$_charset, 'UTF-8');
            $words[] = $tmp;
            $res = self::$_server->getRespond();
        }
        return $words;
    }
    public function getTops($text, $limit = 10, $xattr = '')
    {
        $words = array();
        $text = $this->applySetting($text);
        $cmd = new XSCommand(XS_CMD_SEARCH_SCWS_GET, XS_CMD_SCWS_GET_TOPS, $limit, $text, $xattr);
        $res = self::$_server->execCommand($cmd, XS_CMD_OK_SCWS_TOPS);
        while ($res->buf !== '') {
            $tmp = unpack('Itimes/a4attr/a*word', $res->buf);
            $tmp['word'] = XS::convert($tmp['word'], self::$_charset, 'UTF-8');
            $words[] = $tmp;
            $res = self::$_server->getRespond();
        }
        return $words;
    }
    public function hasWord($text, $xattr)
    {
        $text = $this->applySetting($text);
        $cmd = new XSCommand(XS_CMD_SEARCH_SCWS_GET, XS_CMD_SCWS_HAS_WORD, 0, $text, $xattr);
        $res = self::$_server->execCommand($cmd, XS_CMD_OK_INFO);
        return $res->buf === 'OK';
    }
    private function applySetting($text)
    {
        self::$_server->reopen();
        foreach ($this->_setting as $key => $cmd) {
            if (is_array($cmd)) {
                foreach ($cmd as $_cmd) {
                    self::$_server->execCommand($_cmd);
                }
            } else {
                self::$_server->execCommand($cmd);
            }
        }
        return XS::convert($text, 'UTF-8', self::$_charset);
    }
}
