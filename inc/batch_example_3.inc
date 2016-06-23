<?php

/**
 * Multiple operations and context.
 */

/**
 * Form callback.
 */
function batch_example_3() {
   // Batch with params.
  $batch = array(
    'operations' => array(
      array('batch_example_3_get_files', array()),
      array('batch_example_3_animation', array()),
    ),
    'file' => drupal_get_path('module', 'batch_example') . '/inc/batch_example_3.inc'
  );

  // Set and process it.
  batch_set($batch);
  batch_process('batch-example');
}

function batch_example_3_get_files(&$context) {
  $path = drupal_get_path('module', 'batch_example') . '/files/';
  $files = file_scan_directory($path, '/^batch_example_3.*\.png$/');
  $context['results'] = array_values($files);
  $context['finished'] = 1;
}

/**
 * Called for each .
 */
function batch_example_3_animation(&$context) {
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