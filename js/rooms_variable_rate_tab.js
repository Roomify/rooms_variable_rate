(function ($) {

  Drupal.behaviors.roomsVariableRate = {
    attach: function (context) {
      $('fieldset.unit-type-form-variable-rate', context).drupalSetSummary(function (context) {
        var vals = [];

        if ($('.form-item-rooms-variable-rate-per-unit input', context).is(':checked')) {
          vals.push(Drupal.t('Variable rate pricing enabled'));
        }
        else {
          vals.push(Drupal.t('Variable rate pricing disabled'));
        }

        if ($('.form-item-rooms-variable-rate-disable-core-pricing input', context).is(':checked')) {
          vals.push(Drupal.t('Default pricing and price calendar enabled'));
        }
        else {
          vals.push(Drupal.t('Default pricing and price calendar disabled'));
        }

        return vals.join('<br />');
      });

    }
  };

})(jQuery);
