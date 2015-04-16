<?php

/**
 * @file
 * Form element definitions for Rooms Variable Rate module.
 */

/**
 * Implements hook_element_info().
 */
function rooms_variable_rate_element_info() {
  $elements = array();
  $elements['rooms_variable_rate'] = array(
    '#input' => TRUE,
    '#process' => array('rooms_variable_rate_element_process'),
  );
  $elements['rooms_variable_rate_discount'] = array(
    '#input' => TRUE,
    '#process' => array('rooms_variable_rate_discount_element_process'),
  );
  $elements['rooms_variable_rate_length'] = array(
    '#input' => TRUE,
    '#process' => array('rooms_variable_rate_length_element_process'),
  );
  return $elements;
}

/**
 * Generates the 'rooms_variable_rate_length' Form API element.
 */
function rooms_variable_rate_length_element_process($element, $form_state, $complete_form) {
  $element['minimum_stay'] = array(
    '#title' => t('Minimum stay'),
    '#title_display' => 'invisible',
    '#type' => 'textfield',
    '#field_prefix' => '<strong>' . t('If booking is equal or longer than') . '</strong>',
    '#field_suffix' => t('days'),
    '#size' => 2,
    '#default_value' => isset($element['#value']['minimum_stay']) ? $element['#value']['minimum_stay'] : '',
    '#element_validate' => array('element_validate_integer_positive'),
    '#weight' => 0,
  );

  $element['maximum_stay'] = array(
    '#title' => t('Maximum stay'),
    '#title_display' => 'invisible',
    '#type' => 'textfield',
    '#field_prefix' => '<strong>' . t('and booking shorter than') . '</strong>',
    '#field_suffix' => t('days'),
    '#size' => 2,
    '#default_value' => isset($element['#value']['maximum_stay']) ? $element['#value']['maximum_stay'] : '',
    '#element_validate' => array('element_validate_integer_positive'),
    '#weight' => 1,
  );

  return $element;
}


/**
 * Generates the 'rooms_variable_rate_discount' Form API element.
 */
function rooms_variable_rate_discount_element_process($element, $form_state, $complete_form) {

  $element['rate_type'] = array(
    '#type' => 'select',
    '#options' => array(
      ROOMS_VARIABLE_RATE_DISCOUNT => t('Discount (%)'),
      ROOMS_VARIABLE_RATE_FLAT_RATE => t('Flat rate'),
    ),
    '#default_value' => isset($element['#value']['rate_type']) ? $element['#value']['rate_type'] : '',
    '#field_prefix' => '<strong>' . t('provide') . '</strong>',
    '#weight' => 2,
    '#prefix' => '<div class="container-inline">',
  );

  $element['value'] = array(
    '#title' => t('Value'),
    '#title_display' => 'invisible',
    '#type' => 'textfield',
    '#size' => 2,
    '#default_value' => isset($element['#value']['value']) ? $element['#value']['value'] : '',
    '#element_validate' => array('element_validate_integer_positive'),
    '#weight' => 3,
    '#suffix' => '</div>',
  );

  $element['#element_validate'] = array('rooms_variable_rate_element_validate');

  return $element;
}


/**
 * Generates the 'rooms_variable_rate' Form API element.
 */
function rooms_variable_rate_element_process($element, $form_state, $complete_form) {
  $element['minimum_stay'] = array(
    '#title' => t('Minimum stay'),
    '#title_display' => 'invisible',
    '#type' => 'textfield',
    '#field_prefix' => '<strong>' . t('If booking is equal or longer than') . '</strong>',
    '#field_suffix' => t('days'),
    '#size' => 2,
    '#default_value' => isset($element['#value']['minimum_stay']) ? $element['#value']['minimum_stay'] : '',
    '#element_validate' => array('element_validate_integer_positive'),
    '#weight' => 0,
  );

  $element['maximum_stay'] = array(
    '#title' => t('Maximum stay'),
    '#title_display' => 'invisible',
    '#type' => 'textfield',
    '#field_prefix' => '<strong>' . t('and booking shorter than') . '</strong>',
    '#field_suffix' => t('days'),
    '#size' => 2,
    '#default_value' => isset($element['#value']['maximum_stay']) ? $element['#value']['maximum_stay'] : '',
    '#element_validate' => array('element_validate_integer_positive'),
    '#weight' => 1,
  );

  $element['rate_type'] = array(
    '#type' => 'select',
    '#options' => array(
      ROOMS_VARIABLE_RATE_DISCOUNT => t('Discount (%)'),
      ROOMS_VARIABLE_RATE_FLAT_RATE => t('Flat rate'),
    ),
    '#default_value' => isset($element['#value']['rate_type']) ? $element['#value']['rate_type'] : '',
    '#field_prefix' => '<strong>' . t('provide') . '</strong>',
    '#weight' => 2,
    '#prefix' => '<div class="container-inline">',
  );

  $element['value'] = array(
    '#title' => t('Value'),
    '#title_display' => 'invisible',
    '#type' => 'textfield',
    '#size' => 2,
    '#default_value' => isset($element['#value']['value']) ? $element['#value']['value'] : '',
    '#element_validate' => array('element_validate_integer_positive'),
    '#weight' => 3,
    '#suffix' => '</div>',
  );

  $element['#element_validate'] = array('rooms_variable_rate_element_validate');

  return $element;
}

/**
 * Validate handler for 'rooms_variable_rate' form element.
 */
function rooms_variable_rate_element_validate($element, &$form_state) {
  $value = $element['#value'];
  if (is_array($value)) {
    $name = empty($element['#title']) ? t('Variable Rate') : $element['#title'];
    if (is_array($value)) {
      if ($value['minimum_stay'] > $value['maximum_stay']) {
        form_error($element, t("%name: Minimum booking period can't be greater than maximum.", array('%name' => $name)));
      }
    }

    if ($value['rate_type'] == ROOMS_VARIABLE_RATE_DISCOUNT && $value['value'] > 100) {
      form_error($element, t("%name: Percentage can't be greater than 100.", array('%name' => $name)));
    }
  }
}
