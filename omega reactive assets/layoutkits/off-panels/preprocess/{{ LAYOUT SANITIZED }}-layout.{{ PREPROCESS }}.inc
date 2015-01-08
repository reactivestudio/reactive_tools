<?php

/**
 * Implements hook_preprocess_page().
 */
function {{ THEME }}_preprocess_{{ LAYOUT }}_layout(&$variables) {
    // You can use preprocess hooks to modify the variables before they are passed
    // to the theme function or template file.
    $variables['{{ LAYOUT }}_config'] = variable_get('{{ LAYOUT }}_config', array());
}
