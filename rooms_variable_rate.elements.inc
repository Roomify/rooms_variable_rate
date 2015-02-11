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
    '#process' => array('rooms_variable_rate_process'),
  );
  return $elements;
}

/**
 * Generates the 'rooms_variable_rate' Form API element.
 */
function rooms_variable_rate_process($element, $form_state = array(), $complete_form = array()) {
  $element['minimum_stay'] = array(
    '#title' => t('Minimum stay'),
    '#title_display' => 'invisible',
    '#type' => 'textfield',
    '#field_prefix' => '<strong>' . t('If booking longer than') . '</strong>',
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

  return $element;
}
