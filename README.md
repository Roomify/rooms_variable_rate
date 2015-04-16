[![Build Status](https://travis-ci.org/Roomify/rooms_variable_rate.svg?branch=tests)](https://travis-ci.org/Roomify/rooms_variable_rate)

INTRODUCTION
------------

The Rooms Variable Rate module enables you to define pricing rules that are
based on the length of the booking period. These rules can replace the
standard Rooms pricing calendar or they can work in conjunction with it.

Some typical usage scenarios are:

"If a booking is longer than 2 nights and shorter than 5, apply a 10% discount"

"If a booking is longer than 7 nights and shorter than 10, apply a 10$ per night
flat rate"

The flat rate will be determined by either the default flat rate associated
with a bookable entity or by the price that is derived from the standard pricing
calendar.

INSTALLATION
------------

Simply download and enable the module.

Rooms Variable Rate requires:

* rooms 7.x-1.x-dev (>= 1.5 in the future)

CONFIGURATION
-------------

After activating the module there are two ways to activate variable rates.

1. Activate variable rates for a specific unit: Visit the Rooms Unit Type
configuration page for the type of units you want to activate variable rates
for. When enabled, a new tab "Manage Variable Pricing" will appear in units of
that type. Using this tab, unit owners will be able to define Variable Rate
periods.

2. Activate variables rates globally via a Rule: Create a rule with the action
modify rooms rate on the event modify rooms rate. Based on the conditions you
set you can target specific units or avoid units that have variable rates defined
at the entity level.

You can also choose to enable or disable the default Rooms Pricing Calendar. This
will have the "Manage Pricing" tab and pricing calendar and the base price for a
bookable unit will be the starting point for price calculations.

If the Pricing Calendar is not disabled then it will providing the pricing
starting point.


AUTHORS / CREDITS
-----------------

* Author: [plopesc](http://drupal.org/u/plopesc)
* Development sponsored by [Roomify](http://roomify.us).
