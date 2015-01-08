<?php

/**
 * Implements hook_drush_command().
 */
function reactive_tools_drush_command() {
    $items = array();

    // Omega 4.x framework.
    $items['omega-download-reactive-assets'] = array(
        'aliases' => array('omega-dra'),
        'core' => array('7'),
        'description' => "Drush command. Download Reactive assets: starterkits and layoutkits.",
        'drush dependencies' => array('omega'),
    );

    $items['omega-layout-build'] = array(
        'description' => dt('Creates an Omega layout from layoutkits.'),
        'arguments' => array(
            'name' => dt('The name of your layout.'),
        ),
        'options' => array(
            'machine-name' => dt('The machine-readable name of layout. This will be auto-generated from the human-readable name if omitted.'),
            'theme' => dt('The machine-readable name of your theme the layout is built for.'),
            'layoutkit' => dt('The layoutkit that you want build. Defaults to "default".'),
            'set-default' => dt('Automatically enable layout after creation and make it the default layout.'),
            'no-readme' => dt('Skips readme files when generating the layout.'),
            'with-libraries' => dt("Execute the libraries.make file upon completion."),
            'need-to-config' => dt("Configure layout special settings"),
        ),
        'examples' => array(
            'drush omega-layout-build "My Layout"' => dt('Creates an Omega layout called "My Layout".'),
            'drush omega-layout-build "My Layout" --theme=my_theme' => dt('Creates an Omega layout called "My Layout" for theme with machine-readable name "my_theme".'),
            'drush omega-layout-build "My Layout" --layoutkit=my_custom_layoutkit' => dt('Uses my_custom_layoutkit layoutkit for creating an Omega Layout called "My Layout" in current omega theme.'),
            'drush omega-layout-build "My Layout" --theme=my_theme --layoutkit=my_custom_layoutkit' => dt('Uses the my_custom_layoutkit for creating an Omega layout called "My Layout" in my_theme theme.'),
        ),
        'aliases' => array('olb'),
    );

    $items['omega-layout-wizard'] = array(
        'description' => dt('Guides you through a wizard for generating a layout.'),
        'aliases' => array('olwiz'),
    );

    $items['omega-layout-configure'] = array(
        'description' => dt('Configure an Omega layout with a special setting.'),
        'arguments' => array(
            'machine-name' => dt('The machine-readable name of your layout.'),
        ),
        'options' => array(
            'theme' => dt('The machine-readable name of your theme the layout is configure for.'),
            'reset' => dt('Reset configuration.'),
        ),
        'examples' => array(
            'drush omega-layout-configure "my_layout"' => dt('Configure an Omega layout with machine-readable name "my_layout".'),
            'drush omega-layout-configure "my_layout" --theme=my_theme' => dt('Configure an Omega layout with machine-readable name "my_layout" for "my_theme" theme.'),
            'drush omega-layout-configure "my_layout" --theme=my_theme --reset=y' => dt('Reset configuration for Omega layout with machine-readable name "my_layout" in "my_theme" omega theme.'),
        ),
        'aliases' => array('olc'),
    );




    $items['omega-h'] = array(
        'aliases' => array('omega-helping'),
        'callback' => 'drush_reactive_tools_omega_h',
    );

    return $items;
}



function drush_reactive_tools_omega_h() {
    // $layoutkits = omega_discovery('layoutkit', 'omega');
    // $path = $layoutkits['panels1']['path'];
    // $theme = omega_discovery('layoutkit', 'omega');
    // $theme = omega_discovery('layout', 'omega_alfaretail');
    // $theme = $GLOBALS['theme_key'];
    // $theme = drupal_parse_info_file(drupal_get_path('theme', $theme) . "/$theme.info");
    // $theme = omega_extensions($GLOBALS['theme_key']);
    $themes = list_themes();
    // $theme = drupal_get_path('theme', $GLOBALS['theme_key']);
    $theme = $themes[$GLOBALS['theme_key']];
    $theme = $GLOBALS['theme_key'];
    // $theme = omega_theme_get_setting('omega_layout', 'simple');
    // variable_del('theme_' . $theme . '_settings');
    // $theme = variable_get('theme_' . $theme . '_settings');
    $theme = variable_get('theme_alfaretail_test_settings', array());
    // variable_del('theme_alfaretail_test_settings');
    // $theme = drush_scan_directory($path, '//', array('process'), 0, FALSE, 'filename', 'is_dir', FALSE);
    // $theme = array_keys($theme);
    // $theme = array_filter($theme, 'is_dir');
    // $layout = 'panels1';
    // $theme = $theme['panels1']['path'].'/config/panels1.config.inc';
    // include_once $theme;
    // drush_op('layout_config_'.$layout, $theme);

    // $form_state = array();
    // $path = drupal_get_path('module', 'system');
    // require $path.'/system.admin.inc';

    // $form_state['build_info']['args'] = array('alfaretail_test');

    // drush_op('drupal_form_submit', 'system_theme_settings', $form_state);
    // $theme = variable_get('theme_alfaretail_test_settings');

    // variable_del('theme_alfaretail_test_settings');

    print_r($theme);
}




/**
 * Checking versions of current omega theme framework
 * and Reactive omega sterterkits.
 *
 * TODO doesn't work.
 *
 * @return [type] [description]
 */
function drush_reactive_tools_omega_download_reactive_assets_validate() {
    $omega_info = system_get_info('theme', 'omega');
    $path = drupal_get_path('module', 'reactive_tools').'/omega reactive assets/omega_reactive_assets.info';
    $omega_reactive_assets_info = drupal_parse_info_file($path);

    if ($omega_info['version'] !== $omega_reactive_assets_info['version']) {
        return drush_set_error(
            'REACTIVE_ASSETS_NEED_TO_UPDATE',
            dt('Please update version of Omega Reactive Assets (reactive_tools/omega reactive assets) to @v', array('@v' => $omega_info['version']), 'error')
        );
    }
}

/**
 * Implements drush_hook_COMMAND()
 */
function drush_reactive_tools_omega_download_reactive_assets() {
    $preffix_path = getcwd();
    $path_omega_reactive = $preffix_path.'/'.drupal_get_path('module', 'reactive_tools').'/omega reactive assets';
    $path_omega = $preffix_path.'/'.drupal_get_path('theme', 'omega');

    $starterkits = php_get_dirs($path_omega_reactive.'/starterkits');
    $layoutkits = php_get_dirs($path_omega_reactive.'/layoutkits');

    drush_print(dt('Importing Omega Reactive starterkits:'));
    foreach ($starterkits as $key => $dir) {
        drush_copy_dir($path_omega_reactive.'/starterkits/'.$dir, $path_omega.'/starterkits/'.$dir, FILE_EXISTS_OVERWRITE);
        drush_log(dt('starterkit @dir imported', array('@dir' => $dir)), 'success');
    }

    drush_print(dt('Importing Omega Reactive layoutkits:'));
    if (!file_exists($path_omega.'/layoutkits')) {
        mkdir($path_omega.'/layoutkits', 0755);
    }
    foreach ($layoutkits as $key => $dir) {
        drush_copy_dir($path_omega_reactive.'/layoutkits/'.$dir, $path_omega.'/layoutkits/'.$dir, FILE_EXISTS_OVERWRITE);
        drush_log(dt('layoutkit @dir imported', array('@dir' => $dir)), 'success');
    }

    drush_print(dt('Done. Now you can use custom starterkits and layoutkits with omega-wizard and omega-layout-wizard commands.'));
}



/**
 * Implements drush_hook_COMMAND_validate().
 */
function drush_reactive_tools_omega_layout_configure_validate($machine_name) {
    // Rebuild the theme data so that we can safely check for the existence of
    // themes by using the information provided by list_themes().

    // Validate the machine-readable name of the layout.
    if (!isset($machine_name) ) {
        return drush_set_error('OMEGA_MISSING_ARGUMENT', dt("You didn't specify a machine-name for the layout configuration."));
    }

    // Validate existing of the theme.
    $theme = drush_get_option('theme', $_GLOBALS['theme_key']);
    $themes = list_themes();
    if (!isset($themes[$theme])) {
        return drush_set_error('OMEGA_THEME_DOES_NOT_EXIST', dt('A theme with the machine-readable name @theme does not exists.', array(
                '@theme' => $theme,
            )));
    }

    $layouts = omega_discovery('layout', $theme);
    if (!isset($layouts[$machine_name])) {
        return drush_set_error('OMEGA_LAYOUT_DOES_NOT_EXISTS', dt('The layout with machine-readable name @name does not exists in @theme theme.', array(
                '@name' => $machine_name,
                '@theme' => $theme,
            )));
    }
}

/**
 * Implements drush_hook_COMMAND().
 */
function drush_reactive_tools_omega_layout_configure($layout) {
    $config  = str_replace('_', '-', $layout).'.config.inc';
    $reset   = drush_get_option('reset', NULL);
    $theme   = drush_get_option('theme', $_GLOBALS['theme_key']);
    $themes  = list_themes();
    $layouts = omega_discovery('layout', $theme);
    $regions_config = array();
    $drupal_config  = array();
    $sass_config    = array();


    if (!file_exists($layouts[$layout]['path'].'/config/'.$config)) {
        // There is nothing to configure.
        drush_log(dt('There is no config file and nothing to configure for @name layout.', array('@name' => $layout)));
        return TRUE;
    }

    if (!$reset) {
        // Include layout  regions, drupal and sass _config variables.
        include_once $layouts[$layout]['path'].'/config/'.$config;
    }

    // Update drupal variable.
    variable_set($layout.'_config', $drupal_config);

    if ($sass_config['sass_variable']) {
        // Rewrite SASS file.
        $text .= "/** \n";
        $text .= " * DO NOT CHANGE this file directly.\n";
        $text .= " * Change configuration in $layout.config.inc\n";
        $text .= " * Use only drush command drush-omega-layout-configure\n";
        $text .= " */ \n";
        $text .= php_array_to_sass($sass_config['value'], $sass_config['sass_variable']);
        if (!file_put_contents($layouts[$layout]['path'].'/../../'.$sass_config['file'], $text)) {
            return drush_set_error('OMEGA_LAYOUT_CONFIGURE', dt('Failed to configure layout.'));
        }
    }


    // Repalce regions in theme.info and layout.inc with new ones
    // e.i. delete and add regions with $layout_ prefix.
    drush_omega_layout_regions($themes[$theme]->filename, $layout, $regions_config);
    drush_omega_layout_regions($layouts[$layout]['file'], $layout, $regions_config);
}

/**
 * Implements drush_hook_COMMAND_validate().
 */
function drush_reactive_tools_omega_layout_build_validate($name = NULL) {
    // Rebuild the theme data so that we can safely check for the existence of
    // themes by using the information provided by list_themes().
    system_rebuild_theme_data();

    // Validate the -name of the layout.
    if (!isset($name)) {
        return drush_set_error('OMEGA_MISSING_ARGUMENT', dt("You didn't specify a name for the layout."));
    }

    // Validate layoutkit for existing in layoutkits.
    if ($layoutkit = drush_get_option('layoutkit')) {
        $layoutkits = omega_discovery('layoutkit', 'omega');
        if (!isset($layoutkits[$layoutkit])) {
            return drush_set_error('OMEGA_LAYOUTKIT_DOES_NOT_EXISTS', dt('A layoutkit with the machine-readable name @layoutkit does not exists.', array(
                    '@layoutkit' => $layoutkit,
                )));
        }
    }

    // Validate existing of the theme.
    $theme = drush_get_option('theme', $_GLOBALS['theme_key']);
    $themes = list_themes();
    if (!isset($themes[$theme])) {
        return drush_set_error('OMEGA_THEME_DOES_NOT_EXIST', dt('A theme with the machine-readable name @theme does not exists.', array(
                '@theme' => $theme,
            )));
    }

    // Validate the machine-readable name of the layout.
    if ($machine_name = drush_get_option('machine-name')) {
        if (!is_string($machine_name)) {
            return drush_set_error('OMEGA_LAYOUT_NAME_INVALID', dt('The --machine-name option expects a string value.'));
        }

        if (!preg_match('/^[a-z][a-z0-9_]*$/', $machine_name)) {
            return drush_set_error('OMEGA_LAYOUT_NAME_INVALID', dt('The machine name (@name) is invalid. It may only contain lowercase numbers, letters and underscores and must start with a letter.', array(
                    '@name' => $machine_name,
                )));
        }

        $layouts = omega_discovery('layout', $theme);
        // Validate that the machine-readable name of the theme is unique.
        if (isset($layouts[$machine_name])) {
            return drush_set_error('OMEGA_LAYOUT_ALREADY_EXISTS', dt('A layout with the machine-readable name @name already exists. The machine-readable name must be unique.', array(
                    '@name' => $machine_name,
            )));
        }
    }
}

/**
 * Implements drush_hook_COMMAND().
 */
function drush_reactive_tools_omega_layout_build($name) {
    // Try to generate a machine-readable name.
    // If that fails, prompt for one.
    if (!$machine_name = drush_get_option('machine-name', drush_omega_generate_layout_name($name))) {
            drush_print(dt("Sorry, I couldn't generate a machine-readable name for @name. Please use the '--machine-name' option to specify it manually.", array(
                    '@name' => $name,
            )));
    }


    $theme_name = drush_get_option('theme', $_GLOBALS['theme_key']);
    $layoutkit  = drush_get_option('layoutkit', 'default');
    $themes     = list_themes();
    $layoutkits = omega_discovery('layoutkit', 'omega');
    $theme      = $themes[$theme_name];
    $layoutkit  = $layoutkits[$layoutkit];

    // Create a temporary directory so we don't leave any stale files if an
    // operation fails.
    $temporary = drush_tempdir() . '/' . $name;

    // Try to copy the layoutkit to the temporary path.
    if (!drush_copy_dir($layoutkit['path'], $temporary)) {
        return drush_set_error('OMEGA_GENERATE_LAYOUT', dt('Failed to generate layout. Directory copy error.'));
    }


    // Delete the .layoutkit.inc file.
    drush_delete_dir($temporary . '/' . basename($layoutkit['file']));

    // Put the name for the new layout in place.
    $info = array(
        'name' => $name,
    ) + $layoutkit['info'];

    // If the layoutkit does not provide any regions, use those defined in the
    // theme (if any).
    if (empty($info['regions'])) {
        // We explicitly avoid reading from the generated theme info array
        // for this and get the raw, unprocessed .info file data
        // of the base theme instead to prevent any system-
        // or module-provided regions to leak into our theme's .info file
        // (e.g. via hook_system_info_alter() as used by the dashboard
        // module).
        $theme_info = drupal_parse_info_file(drupal_get_path('theme', $theme) . "/$theme.info");
        if (!empty($basetheme_info['regions'])) {
            $info['regions'] = $theme_info['regions'];
        }
    }


    // Write to the new .info file in .layout.inc
    $file = $temporary . '/' . $machine_name . '.layout.inc';
    if (!file_put_contents($file, drush_omega_compose_info_file($info))) {
        return drush_set_error('OMEGA_GENERATE_LAYOUT', dt('Failed to generate layout.'));
    }

    // Optionally remove README.txt files.
    if (drush_get_option('no-readme')) {
        foreach (file_scan_directory($temporary, '/^README/') as $file) {
            drush_delete_dir($file->uri);
        }
    }


    // Recursively rewrite the file names and contents of all the files
    // that are now in the layout's directory to represent the human- and
    // machine-readable names of the layout.
    $camel = strtr(ucwords(strtr($machine_name, array('_' => ' ', '.' => '_ '))), array(' ' => ''));
    $search = array(
        '/{{ THEME }}/'  => $theme_name,
        '/{{ LAYOUT }}/' => $machine_name,
        '/{{ LAYOUT NAME }}/' => $name,
        '/{{ LAYOUT SANITIZED }}/' => str_replace('_', '-', $machine_name),
        '/{{ LAYOUT CAMELCASE }}/' => $camel,
        '/{{ LAYOUT CAMELCASE LOWER }}/' => lcfirst($camel),
        '/{{ PREPROCESS }}/' => 'preprocess',
        '/{{ PROCESS }}/' => 'process',
    );

    if (!drush_omega_rewrite_recursive($temporary, array_keys($search), array_values($search))) {
        return drush_set_error('OMEGA_GENERATE_LAYOUT', dt('Failed to generate layout.'));
    }



    // Move the new layout's dirs (sass, preprocess, process, images ...)
    // to theme's dir.
    $destination = dirname($theme->filename);
    $files = drush_scan_directory($temporary, '//', array('config'), 0, FALSE, 'filename', 0, FALSE);
    $dirs = array_filter(array_keys($files), 'is_dir');
    foreach ($dirs as $dir) {
        if (!drush_op('drush_copy_dir', $dir, $destination.'/'.basename($dir), FILE_EXISTS_MERGE)) {
            return drush_set_error('OMEGA_GENERATE_LAYOUT', dt('Failed to generate layout.'));
        }
        if (!drush_op('drush_delete_dir', $dir, TRUE)) {
            return drush_set_error('OMEGA_GENERATE_LAYOUT', dt('Failed to generate layout.'));
        }
    }


    // Move the new layout to its destination.
    $layout_dir = $destination.'/layouts/'.str_replace('_', '-', $machine_name);

    if (!file_exists($destination.'/layouts')) {
        mkdir($destination.'/layouts', 0775);
    }
    if (!drush_op('drush_move_dir', $temporary, $layout_dir)) {
        return drush_set_error('OMEGA_GENERATE_LAYOUT', dt('Failed to generate layout.'));
    }


    // Rebuild the theme caches so that  we can do some final tasks.
    drupal_theme_rebuild();
    system_rebuild_theme_data();


    // Make the newly created layout the default one.
    if ($default = drush_get_option('set-default')) {
        if (!$settings = drush_op('variable_get', 'theme_'.$theme->name.'_settings')) {
            $form_state['build_info']['args'] = array($theme->name);
            // Include system_theme_settings
            // from modules/system/system.admin.inc
            $path_system = drupal_get_path('module', 'system');
            drush_include($path_system, 'system.admin');
            drush_op('drupal_form_submit', 'system_theme_settings', $form_state);
            $settings = drush_op('variable_get', 'theme_'.$theme->name.'_settings');
        }

        $settings['omega_toggle_extension_layouts'] = 1;
        $settings['omega_layout'] = $machine_name;

        drush_op('variable_set', 'theme_'.$theme->name.'_settings', $settings);
    }


    // Execute the theme's libraries.make file unless disabled.
    if (drush_get_option('with-libraries') && is_file($layout_dir.'/libraries.make')) {
        $makefile = $layout_dir.'/libraries.make';
        drush_invoke_process('@self', 'make', array($makefile),
            array(
                'no-core' => TRUE,
                'contrib-destination' => './'.$destination,
                'yes' => TRUE,
            )
        );
    }

    // Execute configuring for the newly created layout if it exists.
    if ($need_to_config = drush_get_option('need-to-config')) {
        drush_invoke_process('@self', 'omega-layout-configure', array($machine_name), array('theme' => $theme_name));
    }

    // Clear cache all.
    drush_invoke('cc', 'all');

    drush_log(dt('You have successfully created the layout @name (@machine-name) in @path.', array(
        '@name' => $name,
        '@machine-name' => $machine_name,
        '@path' => dirname($layout_dir),
    )), 'success');
}

/**
 * Implements drush_hook_COMMAND().
 */
function drush_reactive_tools_omega_layout_wizard() {
    // Rebuild the theme data so that we can safely check
    // for the existence of themes by using the information
    // provided by list_themes().
    system_rebuild_theme_data();

    // Prompt for a theme, where the new layout would be placed in.
    if (!$theme = drush_omega_theme_choice(dt('Please choose a theme for your new layout'))) {
        $theme = $GLOBALS['theme_key'];
    }
    drush_set_option('theme', $theme);

    // Let the user choose a layoutkit.
    $layoutkits = omega_discovery('layoutkit', 'omega');
    if (!$layoutkit = drush_omega_layoutkit_choice($layoutkits, dt('Please choose a layoutkit for your new layout'))) {
        $layoutkit = 'default';
    }
    drush_set_option('layoutkit', $layoutkit);

    // Prompt for a layout name.
    $name = drush_prompt(dt('Please enter the name of the new layout'), $layoutkits[$layoutkit]['info']['name']);

    // Try to generate a machine-readable name.
    // If that fails, prompt for one.
    if (!$machine_name = drush_omega_generate_layout_name($name)) {
        drush_print(dt("Sorry, I couldn't generate a machine-readable name for @name", array('@name' => $name,)));
    }

    // Prompt for a layout name using the automatically generated default if any.
    drush_set_option('machine-name', drush_omega_require_valid_layout_name(
        $theme, dt('Please enter a machine-readable name for your new theme'), $machine_name
    ));

    // Let the user choose to directly make layout the default.
    drush_set_option('set-default', drush_confirm(dt('Do you want to make your new layout the default?')));

    // Optionally skip readme files when generating the layout.
    drush_set_option('no-readme', !drush_confirm(dt("Do you want to keep the layoutkit's readme files?")));

    // Let the user decide whether he/she wants to download the libraries directly.
    if (is_file("{$layoutkits[$layoutkit]['path']}/libraries.make")) {
        drush_set_option('with-libraries', drush_confirm(dt('Do you want to download the libraries defined in libraries.make now?')));
    }

    // Finally, let the user choose to configure layout with special settings.
    drush_set_option('need-to-config', drush_confirm(dt('Do you want to configure your new layout after creating?')));

    drush_invoke('omega-layout-build', $name);
}
















/**
 * Helping functions.
 */

/**
 * Get array of subdirectories
 *
 * @param  string $path path of directory
 * @return array
 */
function php_get_dirs($path) {
    $dirs = array();
    if (!is_dir($path)) {
        // return FALSE;
    }

    $dir = opendir($path);
    while($file = readdir($dir)) {
        if (is_dir($path.'/'.$file) && $file != '.' && $file != '..') {
            $dirs[] = $file;
        }
    }

    return $dirs;
}

function php_array_to_sass($variable, $name, $tab = "\t") {
    $text = ($tab === "\t")? '$'.$name.": (\n" : "";

    foreach ($variable as $key => $value) {
        if (is_array($value)) {
            $prefix = "(\n";
            $suffix = $tab."),\n";
            $value  = php_array_to_sass($value, $name, $tab."\t");
        } else {
            $prefix = '';
            $suffix = ",\n";
            $value  = preg_match('/%|px\s*$/', $value)? $value : '"'.$value.'"';
        }
        $text .= $tab.$key.': '.$prefix.$value.$suffix;
    }

    if ($tab === "\t") { $text .= ');' ;}

    return $text;
}

/**
 * Helper function for printing a list of available layoutkits.
 *
 * @param array $layoutkits
 *   An array of layouts.
 * @param string $message
 *   The message that should be displayed.
 *
 * @return bool|string
 *   The machine-readable name of the chosen layout or FALSE if the
 *   operation was cancelled.
 */
function drush_omega_layoutkit_choice($layoutkits, $message) {
    $options = array();
    foreach ($layoutkits as $key => $info) {
        $options[$key] = dt('@name: !description', array(
                '@name' => $info['info']['name'],
                '!description' => isset($info['info']['description']) ? $info['info']['description'] : dt('No description'),
        ));
    }

    return drush_choice($options, $message);
}

/**
 * Generates a valid machine-readable name for a layout from any string.
 *
 * @param string $string
 *   The string to generate the machine-readable name from.
 *
 * @return string
 *   The generated machine-readable name.
 */
function drush_omega_generate_layout_name($string) {
    // Machine-readable names have to start with a lowercase letter.
    $string = preg_replace('/^[^a-z]+/', '', strtolower($string));
    // Machine-readable names may only contain alphanumeric characters
    // and underscores.
    $string = preg_replace('/[^a-z0-9_]+/', '_', $string);
    // Trim all trailing and leading underscores.
    $string = trim($string, '_');

    $layouts = omega_discovery('layout');
    if (isset($layouts[$string])) {
        $plain = $string;
        $counter = 0;

        while (isset($layouts[$string])) {
            // Make sure that the machine-readable name of the theme is unique.
            $string = $plain . '_' . $counter++;
        }
    }

    return $string;
}

/**
 * Helper function that continuously prompts for a valid machine-readable name.
 *
 * @param string $message
 *   The message that should be displayed.
 * @param string $default
 *   (Optional) The default layout name. Defaults to NULL.
 *
 * @return string
 *   A valid, unique machine-readable name.
 */
function drush_omega_require_valid_layout_name($theme, $message, $default = NULL) {
    while (TRUE) {
        // Keep prompting for a machine-name until we get an acceptable value.
        $prompt = drush_prompt($message, $default);

        if (!preg_match('/^[a-z][a-z0-9_]*$/', $prompt)) {
            drush_print('The machine-readable name is invalid. It may only contain lowercase numbers, letters and underscores and must start with a letter.');
        } else {
            $layouts = omega_discovery('layout', $theme);
            // Validate that the machine-readable name of the layout is unique.
            if (isset($layouts[$prompt])) {
                drush_print(dt('A layout with the name @name already exists for the theme @theme. The machine-readable name must be unique.', array(
                        '@name' => $prompt,
                        '@theme' => $theme,
                    ))
                );
            } else {
                // The given machine-readable name is valid. Let's proceed.
                return $prompt;
            }
        }
    }
}

/**
 * Rebuild theme's or layout's .info file and add/remove layout regions.
 *
 * @param  [type] $info_file [description]
 * @param  [type] $layout    [description]
 * @param  array  $regions   [description]
 * @return [type]            [description]
 */
function drush_omega_layout_regions($info_file, $layout, $regions = array()) {
    // Get info array.
    $info = drupal_parse_info_file($info_file);

    // First, delete all layout_ regions from previous configuration.
    $temp_regions = $info['regions'];
    $temp_regions = array_intersect_key(
        $temp_regions,
        array_flip(
            array_filter(
                array_keys($temp_regions),
                create_function('$k', 'return !preg_match("/'.$layout.'/", $k);')
            )
        )
    );
    $info['regions'] = $temp_regions;

    // Next, add the new ones.
    // Add $layout prefix to $regions keys.
    foreach ($regions as $key => $value) {
        $regions[$layout.'_'.$key] = $value;
        unset($regions[$key]);
    }

    $info['regions'] += $regions;

    // Save new info to file.
    if (!file_put_contents($info_file, drush_omega_compose_info_file($info))) {
        return drush_set_error('OMEGA_LAYOUT_CONFIGURE', dt('Failed to configure layout.'));
    }
}









/**
 * Implements hook_drush_help().
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function reactive_tools_drush_help($section) {
  switch ($section) {
    case 'drush:reactive-tools':
      return dt("Brief help for Drush command reactive-tools.");
    // The 'title' meta item is used to name a group of
    // commands in `drush help`.  If a title is not defined,
    // the default is "All commands in ___", with the
    // specific name of the commandfile (e.g. reactive_tools).
    // Command files with less than four commands will
    // be placed in the "Other commands" section, _unless_
    // they define a title.  It is therefore preferable
    // to not define a title unless the file defines a lot
    // of commands.
    case 'meta:reactive_tools:title':
      return dt("reactive_tools commands");
    // The 'summary' meta item is displayed in `drush help --filter`,
    // and is used to give a general idea what the commands in this
    // command file do, and what they have in common.
    case 'meta:reactive_tools:summary':
      return dt("Summary of all commands in this command group.");
  }
}

/**
 * Implementation of drush_hook_COMMAND_pre_validate().
 */
function drush_reactive_tools_pre_validate() {

    return TRUE;
}

/**
 * Implementation of drush_hook_COMMAND_validate().
 */
function drush_reactive_tools_validate() {
  $validated = TRUE; // replace with command validation logic
  if (!$validated) {
    return drush_set_error('DRUSH_reactive_tools_ERROR', dt('Command validation failed.'));
  }
  return TRUE;
}


/**
 * Implementation of drush_hook_pm_enable_pre_validate().
 */
function drush_reactive_tools_pm_enable_pre_validate() {
  // If module has any required libraries, and it needs them
  // prior to enabling in order to pass validation, then we can
  // attempt to download them here.  We must look at the command
  // arguments, because PM_ENABLE_MODULES is not available
  // in pre-validate.  See drush_reactive_tools_post_pm_enable
  $extensions = func_get_args();
  // Deal with comma delimited extension list.
  if (strpos($extensions[0], ',') !== FALSE) {
    $extensions = explode(',', $extensions[0]);
  }
}

/**
 * Implementation of drush_hook_post_pm_enable().
 */
function drush_reactive_tools_post_pm_enable() {
  // If module has any required libraries, this is
  // the best place to enable them.
  /*
  $extensions = drush_get_context('PM_ENABLE_MODULES');
  if (in_array('reactive_tools', $extensions) && !drush_get_option('skip')) {
    drush_reactive_tools_download();
  }
  */
  return TRUE;
}

// Customize to download any necessary external libraries.
// Okay to delete if not needed.
function drush_reactive_tools_download($path = NULL) {
  if (!isset($path)) {
    if (module_exists('libraries')) {
      // Libraries 1.x will return a path even if it doesn't exist
      // while 2.x will return FALSE.
      $path = libraries_get_path('LIBRARYNAME');
      if (!$path) {
        $path = 'sites/all/libraries/LIBRARYNAME';
      }
    }
    else {
      $path = '/' . drupal_get_path('module', 'reactive_tools') . '/LIBRARYNAME';
    }
  }
  if (is_dir($path)) {
    drush_log('LIBRARYNAME already present. No download required.', 'ok');
  }
  else {
    $library_url = 'http://server.net/library-1.0.0.zip';
    $library_zip = drush_download_file($library_url);
    if (!$library_zip) {
      drush_log(dt('LIBRARYNAME could not be downloaded from @url', array('@url' => $library_url)), 'warning');
    }
    else {
      // Note that drush_tarball_extract will process zip files too.
      $file_list = drush_tarball_extract($library_zip, FALSE, TRUE);
      if (is_array($file_list)) {
        drush_move_dir(dirname($library_zip) . '/' . $file_list[0], $path);
        drush_log(dt('LIBRARYNAME has been extracted to @path.', array('@path' => $path)), 'success');
        return TRUE;
      }
      else {
        drush_log('LIBRARYNAME could not be extracted.', 'warning');
      }
    }
  }
  return FALSE;
}

