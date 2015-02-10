<?php

/**
 * @file
 * Field API related hooks and functions for Rooms Variable Rate module.
 */

/*****************************************************
 ************** FIELD TYPE FUNCTIONS *****************
 ****************************************************/
/**
 * Implements hook_field_info().
 */
function rooms_variable_rate_field_info() {
  return array(
    'rooms_variable_rate' => array(
      'label' => t('Rooms Variable Rate'),
      'description' => t('Add variable rates based on booking time.'),
      'settings' => array(),
      'default_widget' => 'rooms_variable_rate',
      'default_formatter' => 'rooms_variable_rate',
      'property_type' => 'rooms_variable_rate',
      'property_callbacks' => array('rooms_variable_rate_property_info_callback'),
    ),
  );
}

/**
 * Property callback for the Entity Metadata framework.
 */
function rooms_variable_rate_property_info_callback(&$info, $entity_type, $field, $instance, $field_type) {
  // Apply the default.
  entity_metadata_field_default_property_callback($info, $entity_type, $field, $instance, $field_type);

  // Finally add in instance specific property info.
  $name = $field['field_name'];
  $property = &$info[$entity_type]['bundles'][$instance['bundle']]['properties'][$name];
  $property['type'] = ($field['cardinality'] != 1) ? 'list<rooms_variable_rate>' : 'rooms_variable_rate';
  $property['property info'] = rooms_variable_rate_data_property_info('Rooms Variable Rate');
  $property['getter callback'] = 'entity_metadata_field_verbatim_get';
  $property['setter callback'] = 'entity_metadata_field_verbatim_set';
}

/**
 * Defines info for the properties of the Rooms Variable Rate structure.
 */
function rooms_variable_rate_data_property_info($name = NULL) {
  // Build an array of properties for an Availability Constraints Range.
  $properties = array(
    'rate_type' => array(
      'label' => 'Rate type',
      'type' => 'text',
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
    ),
    'value' => array(
      'label' => 'Value',
      'type' => 'integer',
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
    ),
    'minumum_stay' => array(
      'label' => 'Minimum stay',
      'type' => 'integer',
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
    ),
    'maximum_stay' => array(
      'label' => 'Maximum stay',
      'type' => 'integer',
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
    ),
  );

  // Add the default values for each property.
  foreach ($properties as &$value) {
    $value += array(
      'description' => !empty($name) ? t('!label of field %name', array('!label' => $value['label'], '%name' => $name)) : '',
    );
  }

  return $properties;
}

/**
 * Implements hook_field_validate().
 */
function rooms_variable_rate_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  foreach ($items as $delta => $item) {
    if ((is_numeric($item['value']) && $item['value'] <= 0) || (is_numeric($item['minimum_stay']) && $item['minimum_stay'] <= 0) || (is_numeric($item['maximum_stay']) && $item['maximum_stay'] <= 0)) {
      $errors[$field['field_name']][$langcode][$delta][] = array(
        'error' => 'rooms_variable_rate_negative',
        'message' => t('%name: Values must be integer positive.', array('%name' => $instance['label'])),
      );
    }
  }
}

/**
 * Implements hook_field_is_empty().
 */
function rooms_variable_rate_field_is_empty($item, $field) {
  if ((empty($item['value']) && (string) $item['value'] !== '0') || (empty($item['minimum_stay']) && (string) $item['minimum_stay'] !== '0') || (empty($item['maximum_stay']) && (string) $item['maximum_stay'] !== '0')) {
    return TRUE;
  }
  return FALSE;
}

/*****************************************************
 **************** WIDGET FUNCTIONS *******************
 ****************************************************/
/**
 * Implements hook_field_widget_info().
 */
function rooms_variable_rate_field_widget_info() {
  return array(
    'rooms_variable_rate' => array(
      'label' => t('Rooms Variable Rate'),
      'description' => t('Rooms Variable Rate'),
      'field types' => array('rooms_variable_rate'),
      'settings' => array(),
    ),
  );
}

/**
 * Implements hook_field_widget_form().
 */
function rooms_variable_rate_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  if ($instance['widget']['type'] == 'rooms_variable_rate') {
    $element += array(
      '#title' => $instance['label'],
      '#type' => 'rooms_variable_rate',
      '#default_value' => isset($items[$delta]) ? $items[$delta] : '',
    );
  }
  
  return $element;
}
