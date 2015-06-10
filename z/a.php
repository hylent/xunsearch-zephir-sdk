<?php

$xs = new \Xs\Xs(__DIR__ . '/test.ini');

$doc = new \Xs\Document();
$doc->pk = 1;
$doc->id = 1;
$doc->title = 'hello world';
$doc->cityid = 1;
$doc->areaid = '2_3';
$doc->mallid = '4_5_6';

$xs->index->update($doc, 1);
