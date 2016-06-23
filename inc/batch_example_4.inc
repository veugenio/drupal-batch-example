<?php

/**
 * Multiple operations and context.
 */

/**
 * Form callback.
 */
function batch_example_4() {
  // Batch with params.
  $batch = array(
    'operations' => array(
      array('batch_example_4_init_capture', array()),
      array('batch_example_4_get_files', array()),
      array('batch_example_4_animation', array()),
    ),
    'finished' => 'batch_example_4_finish_capture',
    'file' => drupal_get_path('module', 'batch_example') . '/inc/batch_example_4.inc'
  );

  // Set and process it.
  batch_set($batch);
  batch_process('batch-example');
}

function batch_example_4_init_capture(&$context) {
  shell_exec('tail --lines 0 -f /var/log/apache2/access.log > /tmp/batch_example_4.log &');
}

function batch_example_4_get_files(&$context) {
  $path = drupal_get_path('module', 'batch_example') . '/files/';
  $files = file_scan_directory($path, '/^batch_example_3.*\.png$/');
  
  krsort($files);
  $context['results'] = array_values($files);
  $context['finished'] = 1;
}

/**
 * Called for each .
 */
function batch_example_4_animation(&$context) {
  if (!isset($context['sandbox']['total'])) {
    $context['sandbox']['total'] = sizeof($context['results']) - 1;
    $context['sandbox']['current'] = 0;
  }

  $file = $context['results'][$context['sandbox']['current']];
  $context['message'] = theme_image(array('path' => $file->uri));
  $context['finished'] = $context['sandbox']['current'] / $context['sandbox']['total'];
  $context['sandbox']['current'] ++;

  sleep(1);
}

function batch_example_4_finish_capture($success) {
  dpm($success);
  $log = file_get_contents('/tmp/batch_example_4.log');
  dpm($log);

  shell_exec('pkill tail');
}