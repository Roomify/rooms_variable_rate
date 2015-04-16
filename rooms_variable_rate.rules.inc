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
    'label' => t('Modify Rooms Rate'),
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
    ),
  );

  return $events;
}

/**
 * Implements hook_rules_condition_info().
 */
function rooms_variable_rate_rules_condition_info() {
  $conditions['variable_rate_booking_length'] = array(
    'label' => t('Booking period length comparison'),
    'group' => t('Rooms Variable Rate'),
    'base' => 'variable_rate_booking_length',
    'parameter' => array(
      'rooms_variable_rate_length' => array(
        'type' => 'rooms_variable_rate_length',
        'label' => t('Rooms Variable Rate Length'),
        'minimum_stay' => '',
        'maximum_stay' => ''
      ),
    ),
  );

return $conditions;
}

/**
 * Implements hook_rules_action_info().
 */
function rooms_variable_rate_rules_action_info() {
  return array(
    'rooms_variable_rate_modify_rate' => array(
      'label' => t('Modify Rooms Rate'),
      'parameter' => array(
        'rooms_variable_rate_discount' => array(
          'type' => 'rooms_variable_rate_discount',
          'restriction' => 'input',
          'label' => t('Rooms Variable Rate'),
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

function variable_rate_booking_length($start_date, $end_date, $rule_state) {

  $start = $rule_state->variables['start_date'];
  $end = $rule_state->variables['end_date'];

  $period = $start->diff($end)->days;


  if ($rule_state->currentArguments['rooms_variable_rate_length']['minimum_stay'] <= $period && $rule_state->currentArguments['rooms_variable_rate_length']['maximum_stay'] > $period) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

function rooms_variable_rate_modify_rate_execute($rooms_variable_rate, $disable_pricing, $action_settings, $rule_state, $action, $callback_type) {
  global $_rooms_variable_rate_unit_price_modifiers;

  $start = $rule_state->variables['start_date'];
  $end = $rule_state->variables['end_date'];

  $period = $start->diff($end)->days;

  if ($rule_state->currentArguments['settings']['rooms_variable_rate_discount']['rate_type'] == 'flat_rate') {
    $op_type = 'replace';
    $value = $rule_state->currentArguments['settings']['rooms_variable_rate_discount']['value'];
    $amount = $value * $period;
  }
  else {
    $op_type = ROOMS_DECREASE;
    $amount = $rule_state->currentArguments['settings']['rooms_variable_rate_discount']['value'];
  }

  $_rooms_variable_rate_unit_price_modifiers = array (
     '#op_type' => $op_type,
     '#amount' => $amount,
  );
}


/**
 * Implements hook_rules_data_info().
 */
function rooms_variable_rate_rules_data_info() {
  $data['rooms_variable_rate_discount'] = array(
    'label' => t('Rooms Variable Rate Discount'),
    'ui class' => 'RoomsVariableRateDiscountSettings',
  );
  $data['rooms_variable_rate_length'] = array(
    'label' => t('Rooms Variable Rate Length'),
    'ui class' => 'RoomsVariableRateLengthSettings',
  );
  return $data;
}

/**
 * Adds a Rooms Variable Rate form to the enabling action.
 */
class RoomsVariableRateLengthSettings extends RulesDataUI implements RulesDataDirectInputFormInterface {
  public static function getDefaultMode() {
    return 'input';
  }

  public static function inputForm($name, $info, $settings, RulesPlugin $element) {
    $form['rooms_variable_rate_length'] = array(
      '#type' => 'rooms_variable_rate_length',
      '#default_value' => $settings[$name],
    );

    return $form;
  }

  public static function render($value) {
    return array();
  }

}

/**
 * Adds a Rooms Variable Rate form to the enabling action.
 */
class RoomsVariableRateDiscountSettings extends RulesDataUI implements RulesDataDirectInputFormInterface {
  public static function getDefaultMode() {
    return 'input';
  }

  public static function inputForm($name, $info, $settings, RulesPlugin $element) {
    $form['rooms_variable_rate_discount'] = array(
      '#type' => 'rooms_variable_rate_discount',
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
