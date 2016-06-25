<?php

/**
 * Batch selecting a range of nodes to process.
 */

/**
 * Menu callback.
 */
function batch_example_1() {
  $batch = array(
    'operations' => array(
      array('batch_example_1_operation_1', array()),
      array('batch_example_1_operation_2', array()),
      array('batch_example_1_operation_3', array())
    ),
    'file' => drupal_get_path('module', 'batch_example') . '/inc/batch_example_1_5.inc',
    'title' => t('Node processor'),
    'init_message' => t('Processing nodes.'),
    'progress_message' => t('Processed @current out of @total.'),
  );
  batch_set($batch);
  batch_process('batch-example');
}

/**
 * This operation will run until $context['finished'] reaches 1.
 */
function batch_example_1_operation_1(&$context) {

  if (empty($context['sandbox']['offset'])) {
    $context['message'] = t('Initialized');
    $context['sandbox']['offset'] = 0;
    $context['sandbox']['limit'] = 10;
  }

  $nodes = db_select('node', 'n')
      ->fields('n', array('title'))
      ->range(
          $context['sandbox']['offset'],
          $context['sandbox']['limit'])
      ->execute()->fetchAllKeyed();

  if (sizeof($nodes) < 1) {
    $context['message'] = t('Finished');
    $context['finished'] = 1;
    return;
  }

  $context['finished'] = 0;
  $context['results'] += $nodes;
  $context['sandbox']['offset'] += $context['sandbox']['limit'];
}

function batch_example_1_operation_2(&$context) {
  dpm($context);
  sleep(1);
}

function batch_example_1_operation_3(&$context) {
  dpm($context);
  sleep(1);
}