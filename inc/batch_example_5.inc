<?php

/**
 * Batch non-progressive.
 */

/**
 * Form callback.
 */
function batch_example_5() {
  // Batch with params.
  $batch = array(
    'operations' => array(
      array('batch_example_5_get_files', array()),
      array('batch_example_5_animation', array()),
    ),
    'file' => drupal_get_path('module', 'batch_example') . '/inc/batch_example_5.inc'
  );

  // Set and process it.
  batch_set($batch);

  // Set progressive option.
  $batch1 = &batch_get();
  $batch1['progressive'] = FALSE;

  batch_process('batch-example');
}

function batch_example_5_get_files(&$context) {
  $path = drupal_get_path('module', 'batch_example') . '/files/';
  $files = file_scan_directory($path, '/^batch_example_3.*\.png$/');
  
  krsort($files);
  $context['results'] = array_values($files);
  $context['finished'] = 1;
}

/**
 * Called for each .
 */
function batch_example_5_animation(&$context) {
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