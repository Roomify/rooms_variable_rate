[![Build Status](https://travis-ci.org/Roomify/rooms_variable_rate.svg?branch=tests)](https://travis-ci.org/Roomify/rooms_variable_rate)

INTRODUCTION
------------

Rooms Variable Rate module allows to override the default pricing behavior
provided by Rooms Pricing module.

This module adds variable rate configuration based on booking periods. Site
admins can define discount over the official price or flat rates based on the
booking duration.

Some typical usage scenario are:

"If a booking is longer than 2 nights and shorter than 5, apply a 10% discount"

"If a booking is longer than 7 nights and shorter than 10, apply a 10$ per night
flat rate"

INSTALLATION
------------

Simply download and enable the module.

Rooms Variable Rate requires:

* rooms 7.x-1.x-dev (>= 1.5 in the future)

CONFIGURATION
-------------

After activating the module visit the rooms unit type configuration page for
the type of units you want to activate variable rates.

You can activate variable rate for all units of a certain type. When enabled, a
new tab "Manage Variable Pricing" will appear in units of that type. Using this
tab, unit owners will be able to define Variable Rate periods.

Tou also can enable and disable the default Rooms "Manage Pricing" tab, in order
to use as base price to apply the rate variations the basic price per night or
the configured in "Manage Pricing" tab.

AUTHORS / CREDITS
---------------

* Author: [plopesc](http://drupal.org/u/plopesc)
* Development sponsored by [Roomify](http://roomify.us).
