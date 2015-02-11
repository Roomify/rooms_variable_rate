(function ($) {

  Drupal.behaviors.roomsVariableRate = {
    attach: function (context) {
      $('fieldset.unit-type-form-variable-rate', context).drupalSetSummary(function (context) {
        var vals = [];

        if ($('.form-item-rooms-variable-rate-per-unit input', context).is(':checked')) {
          vals.push(Drupal.t('Unit constraints enabled'));
        }
        else {
          vals.push(Drupal.t('Unit constraints disabled'));
        }

        if ($('.form-item-rooms-variable-rate-disable-core-pricing input', context).is(':checked')) {
          vals.push(Drupal.t('Default core pricing enabled'));
        }
        else {
          vals.push(Drupal.t('Default core pricing disabled'));
        }

        return vals.join('<br />');
      });

    }
  };

})(jQuery);
