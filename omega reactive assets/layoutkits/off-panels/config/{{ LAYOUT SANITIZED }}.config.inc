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
$regions_config = array(
    'contacts' => "Panels Contacts",
    'cart'     => "Panels Cart",
);

/**
 * Configuration variable, that is available everywhere in drupal environment
 * as global variable {{ LAYOUT }}_config.
 * @var array
 */
$drupal_config = array(
    'contacts' => array(
        'position' => "right",
        'seze' => '300px',
        'fx' => "push",
    ),
    'cart' => array(
        'position' => "left",
        'size' => 'auto',
        'fx' => "reveal",
    ),
);
?>
