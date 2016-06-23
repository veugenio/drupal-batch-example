<?php

/**
 * More options and custom queue.
 */

/**
 * Callback.
 */
function batch_example_6() {

  $batch = array(
    'operations' => array(
      array('batch_example_6_get_files', array()),
      array('batch_example_6_animation', array()),
      ),
    'queue' => array(
      'name' => 'batch_example_queue',
      'class' => 'BatchExampleQueue',
    ),
    'finished' => 'batch_example_finished',
    'title' => t('Processing Example Batch'),
    'init_message' => t('Example Batch is starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Example Batch has encountered an error.'),
    'file' => drupal_get_path('module', 'batch_example') . '/inc/batch_example_6.inc',
  );

  batch_set($batch);
  batch_process('batch-example');
}

/**
 * Get all files.
 */
function batch_example_6_get_files(&$context) {
  $path = drupal_get_path('module', 'batch_example') . '/files/';
  $files = file_scan_directory($path, '/^batch_example_3.*\.png$/');
  
  krsort($files);
  $context['results'] = array_values($files);
  $context['finished'] = 1;
}

/**
 * Called for each image.
 */
function batch_example_6_animation(&$context) {
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

/**
 * Finished.
 */
function batch_example_6_finished($success, $result) {
  dpm($success);
  dpm($result);
}

