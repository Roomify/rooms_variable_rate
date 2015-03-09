<?php

/**
 * @file
 * Rules integration for Rooms Variable Rate.
 *
 * @addtogroup rules
 * @{
 */

/**
 * Implements hook_rules_event_info().
 */
function rooms_variable_rate_rules_event_info() {
  $events = array();

  $events['rooms_variable_rate_modify_rate'] = array(
    'label' => t('Modify Rate'),
    'group' => t('Rooms Variable Rate'),
    'variables' => array(
      'rooms_unit' => array(
        'type' => 'rooms_unit',
        'label' => t('Rooms Unit'),
      ),
      'start_date' => array(
        'type' => 'date',
        'label' => t('Start Date'),
      ),
      'end_date' => array(
        'type' => 'date',
        'label' => t('End Date'),
      ),
      'price' => array(
        'type' => 'decimal',
        'label' => t('Price'),
      ),
    ),
  );

  return $events;
}

/**
 * Implements hook_rules_action_info().
 */
function rooms_variable_rate_rules_action_info() {
  return array(
    'rooms_variable_rate_modify_rate' => array(
      'label' => t('Modify Rooms Rate'),
      'parameter' => array(
        'rooms_variable_rate' => array(
          'type' => 'rooms_variable_rate',
          'restriction' => 'input',
          'label' => t('Rooms Variable Rate'),
          'minimum_stay' => '',
          'maximum_stay' => '',
          'rate_type' => ROOMS_VARIABLE_RATE_DISCOUNT,
          'value' => 10
        ),
        'disable_pricing' => array(
          'type' => 'boolean',
          'label' => t('Disable pricing'),
          'description' => t("If disabled rooms_pricing module behavior will be disabled."),
          'default value' => TRUE,
          'optional' => TRUE,
          'restriction' => 'input',
        ),
      ),
      'group' => t('Rooms Variable Rate'),
    ),
  );
}

function rooms_variable_rate_modify_rate_execute($rooms_variable_rate, $disable_pricing, $action_settings, $rule_state, $action, $callback_type) {
  global $rooms_variable_rate_unit_price;
  $unit = $rule_state->get('rooms_unit')->value();
  $start_date = new DateTime(date('Y-m-d', $rule_state->get('start_date')));
  $end_date = new DateTime(date('Y-m-d', $rule_state->get('end_date')));
  $price = $rule_state->get('price');
  $rates = array($rooms_variable_rate);
  $rooms_variable_rate_unit_price[$unit->unit_id] = rooms_variable_rate_calculate_pricing($price, $unit, $start_date, $end_date, $disable_pricing, $rates);
}

/**
 * Implements hook_rules_data_info().
 */
function rooms_variable_rate_rules_data_info() {
  $data['rooms_variable_rate'] = array(
    'label' => t('Rooms Variable Rate'),
    'ui class' => 'RoomsVariableRateSettings',
  );
  return $data;
}

/**
 * Adds a Rooms Variable Rate form to the enabling action.
 */
class RoomsVariableRateSettings extends RulesDataUI implements RulesDataDirectInputFormInterface {
  public static function getDefaultMode() {
    return 'input';
  }

  public static function inputForm($name, $info, $settings, RulesPlugin $element) {
    $form['rooms_variable_rate'] = array(
      '#type' => 'rooms_variable_rate',
      '#default_value' => $settings[$name],
    );

    return $form;
  }

  public static function render($value) {
    return array();
  }

}

/**
 * @}
 */
