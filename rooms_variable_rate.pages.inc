<?php

/**
 * @file
 * Page callbacks for Rooms Variable Rate module.
 */

/**
 * Form callback for Manage Variable Pricing page.
 */
function rooms_variable_rate_pricing_form($form, &$form_state, $unit) {
  $form['base_price'] = array(
    '#type' => 'textfield',
    '#title' => t('Base price'),
    '#default_value' => isset($unit->base_price) ? $unit->base_price : '',
    '#size' => '5',
    '#field_suffix' => t('Per unit per night'),
    '#maxlength' => 10,
    '#required' => TRUE,
    '#weight' => -98,
  );

  $instances = field_info_instances('rooms_unit', $unit->type);
  // Add the field related form elements.
  $form_state['rooms_unit'] = $unit;
  field_attach_form('rooms_unit', $unit, $form, $form_state);

  // Hide undesired fields.
  foreach ($instances as $name => $instance) {
    if ($name != ROOMS_VARIABLE_RATE_FIELD_NAME) {
      $form[$name]['#access'] = FALSE;
    }
  }

  $form['actions'] = array(
    '#type' => 'actions',
    '#tree' => FALSE,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Prices'),
    '#submit' => $submit + array('rooms_variable_rate_pricing_form_submit'),
  );

  return $form;
}

/**
 * Rooms Variable Rate form validate callback.
 */
function rooms_variable_rate_pricing_form_validate(&$form, &$form_state) {
  $unit = $form_state['rooms_unit'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('rooms_unit', $unit, $form, $form_state);

  // Validate price field.
  if (!empty($form_state['values']['base_price']) && !is_numeric($form_state['values']['base_price'])) {
    form_set_error('base_price', t('%name: you must enter a numeric value for the price.', array('%name' => t('Base price'))));
  }
}

/**
 * Rooms Variable Rate form submit callback.
 */
function rooms_variable_rate_pricing_form_submit($form, &$form_state) {
  $unit = entity_ui_controller('rooms_unit')->entityFormSubmitBuildEntity($form, $form_state);
  $unit->changed = time();

  $unit->save();
  drupal_set_message(t('Bookable unit @name saved', array('@name' => $unit->name)));
  $form_state['redirect'] = 'admin/rooms/units/unit/' . $unit->unit_id;
}

/**
 * Overrides page callback for Bulk Pricing Management.
 *
 * Disables unit types that overrides default pricing logic.
 *
 * @param string $year
 *   Year to perform the operations.
 * @param string $month
 *   Month to perform the operations.
 * @param string $type
 *   Bookable unit type to perform the operation.
 *
 * @return array
 *   Bulk pricing management page render array.
 */
function rooms_variable_rate_bulk_pricing_management($year = '', $month = '', $type = 'all') {
  // Load FullCalendar and relevant js/css.
  rooms_fullcalendar_loaded();

  // If year is not set then give it the current date.
  $year = ($year == '') ? date('Y', time()) : $year;
  $month = ($month == '') ? date('n', time()) : $month;
  $type = ($type == '') ? 'all' : $type;

  // It's not a valid unit type.
  if (rooms_unit_get_types($type) == FALSE) {
    $type = 'all';
  }

  // It's not a valid month or not valid year.
  $year_options = range(date('Y', time()) - 2, date('Y', time()) + 5);
  if ($month < 1 || $month > 12 || !in_array($year, $year_options)) {
    $year = date('Y', time());
    $month = date('n', time());
  }

  $allowed_types = array();
  foreach (rooms_unit_get_types() as $unit_type_name => $unit_type) {
    if (!variable_get('rooms_variable_rate_disable_pricing_' . $unit_type->type, 0)) {
      $allowed_types[$unit_type_name] = $unit_type;
    }
  }

  $rooms_id = $units = array();
  if ($type == 'all' || in_array($type, $allowed_types)) {
    $efq = new EntityFieldQuery();
    $efq->entityCondition('entity_type', 'rooms_unit')
      ->addTag('rooms_pricing_access')
      ->pager(20);
    if ($type != 'all') {
      $efq->entityCondition('bundle', $type, '=');
    }
    else {
      $efq->entityCondition('bundle', array_keys($allowed_types), 'IN');
    }
    $rooms_units = $efq->execute();

    if ($rooms_units) {
      $units = array_values(entity_load('rooms_unit', array_keys($rooms_units['rooms_unit'])));

      foreach ($units as $value) {
        $rooms_id[] = $value->unit_id;
      }
    }
  }

  // Return the full render array.
  return array(
    drupal_get_form('rooms_filter_month_form', $month, $year, $allowed_types),
    drupal_get_form('rooms_pricing_update_form', $month, $year, $type, $units),
    array(
      '#theme' => 'pager',
    ),
    '#attached' => array(
      'css' => array(drupal_get_path('module', 'rooms_pricing') . '/css/rooms_pricing.css'),
      'js' => array(
        drupal_get_path('module', 'rooms_pricing') . '/js/rooms_pricing_management.js',
        array(
          'data' => array(
            'roomsUnitManagement' => array(
              'roomsNumber' => count($rooms_id),
              'currentMonth' => $month,
              'currentYear' => $year,
              'roomsId' => $rooms_id,
            ),
          ),
          'type' => 'setting',
        ),
      ),
    ),
  );
}
