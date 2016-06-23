<?php

/**
 * Simplest batch implementation.
 */

/**
 * Menu callback.
 */
function batch_example_1() {
  $value = 'test';
  $batch = array(
    'operations' => array(
      array('batch_example_1_operation_1', array($value)),
      array('batch_example_1_operation_2', array()),
      array('batch_example_1_operation_3', array())
    ),
    'file' => drupal_get_path('module', 'batch_example') . '/inc/batch_example_1_4.inc'
  );
  batch_set($batch);
  batch_process('batch-example');
}

/**
 * This operation will run until $context['finished'] reaches 1.
 */
function batch_example_1_operation_1($value, $context) {
  
  if (empty($context['sandbox']['test'])) {
    dpm('First time');
    $context['finished'] = 0;
  }
  
  dpm($value);
  dpm($context);
  sleep(1);
  
  $context['qualquer_palavra']['test'] = 'Sandbox text';
  $context['sandbox']['test'] = 'Sandbox text';
  $context['results']['test'] = 'Sandbox text';

  $context['message'] = t('Message example');
  $context['finished'] += 0.5;
}

function batch_example_1_operation_2($context) {
  dpm($context);
  sleep(3);
}

function batch_example_1_operation_3($context) {
  dpm($context);
  sleep(1);
}