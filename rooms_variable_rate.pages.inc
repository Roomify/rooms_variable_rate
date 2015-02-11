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
    if ($name != 'rooms_variable_rate') {
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
 * Rooms Variable Rate form submit callback.
 */
function rooms_variable_rate_pricing_form_submit($form, &$form_state) {
  $unit = entity_ui_controller('rooms_unit')->entityFormSubmitBuildEntity($form, $form_state);
  $unit->changed = time();

  $unit->save();
  $form_state['redirect'] = 'admin/rooms/units/unit/' . $unit->unit_id;
}
