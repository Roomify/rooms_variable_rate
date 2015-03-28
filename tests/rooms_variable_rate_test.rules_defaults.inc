<?php
/**
 * @file
 * equipment_rental_equipment.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function rooms_variable_rate_test_default_rules_configuration() {
  $items = array();
  $items['rooms_variable_rate_test'] = entity_import('rules_config', '{ "rooms_variable_rate_test" : {
      "LABEL" : "Rooms Variable Rate test",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Rooms Variable Rate" ],
      "REQUIRES" : [ "rules", "rooms_variable_rate" ],
      "ON" : { "rooms_variable_rate_modify_rate" : [] },
      "IF" : [
        { "NOT entity_has_field" : { "entity" : [ "rooms-unit" ], "field" : "rooms_variable_rate" } }
      ],
      "DO" : [
        { "rooms_variable_rate_modify_rate" : { "rooms_variable_rate" : { "value" : {
                "minimum_stay" : "1",
                "maximum_stay" : "5",
                "rate_type" : "discount",
                "value" : "10"
              }
            },
            "disable_pricing": 1
          }
        }
      ]
    }
  }');
  return $items;
}
