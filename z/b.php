<?php

header('Content-type: text/plain; charset=utf-8');

$xs = new \Xs\Xs(__DIR__ . '/test.ini');

$docs = $xs->search->search();
print_R($docs);
