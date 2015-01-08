<?php

/**
 * @file
 * Configuration for {{ LAYOUT NAME }} layout in an Omega theme.
 * Consists  global drupal variable, additional regions and sass variable.
 *
 * !Important: For anabling any changes in these variables
 * must to be called drush command
 * drush-layout-configure {{ LAYOUT }} (drush-lc {{ LAYOUT }}).
 */

/**
 * Add new regions for theme.info and {{ LAYOUT }}.layout.inc.
 * Notice , full name of the region after drush command will be panels1_key.
 * It is used for avoiding name conflict with other layouts.
 * @var array
 */
// $regions_config = array(
//     'region'        => "Region One",
//     'second_region' => "Second Region",
// );

/**
 * Configuration variable, that is available everywhere in drupal environment
 * as global variable {{ LAYOUT }}_config.
 * @var array
 */
// $drupal_config = array(
//     'some' => array(
//         'feature1' => "value",
//         'feature2' => "value",
//     ),
//     'cart' => array(
//         'position' => "left",
//         'fx' => "slide-reveal",
//     ),
// );

/**
 * Configuration for sass variable.
 * After drush command value of the 'value' key  will be translated
 * to sass map variable with 'sass_variable' name in 'file' file.
 * @var array
 */
// $sass_config = array(
//     'file'  => 'sass/layouts/{{ LAYOUT SANITIZED }}/settings/_panels.scss',
//     'sass_variable' => 'panels',
//     'value' => array(
//         'contacts' => array(
//             'position' => "right",
//             'size' => '100%',
//             'fx' => "push-simple",
//         ),
//         'cart' => array(
//             'position' => "left",
//             'size' => '300px',
//             'fx' => "slide-reveal",
//         ),
//     ),
// );

?>
