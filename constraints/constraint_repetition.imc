<?php

/**
 * @file
 * Password policy constraint callbacks.
 */

/****************************************************************************/
/* Constraint API                                                           */
/****************************************************************************/

/**
 * Description of the constraint.
 */
function password_policy_constraint_characterrepetition_description() {
  return array('name' => t('Character Repetition'), 'description' => t('Passwords may not repeat the same character more than this number of times.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_characterrepetition_error($constraint) {
  if ($constraint == 1) {
    return format_string('Passwords may not repeat the same letter more than once.', array('@count' => $constraint));
  }
  else {
    return format_string('Passwords may not repeat the same letter more than @count times.', array('@count' => $constraint));
  }
}

/**
 * Password validation.
 */
function password_policy_constraint_characterrepetition_validate($password, $constraint, $account) {

  $characters_count = array();

  foreach (str_split($password) as $each_character) {
    if (array_key_exists($each_character, $characters_count)) {
      $characters_count[$each_character]++;
    }
    else {
      $characters_count[$each_character] = 1;
    }
  }

  foreach ($characters_count as $each_character_repetition_entry) {
    if ($each_character_repetition_entry > $constraint) {
      return FALSE;
    }
  }

  return TRUE;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_characterrepetition_js($constraint, $account) {

  $data = array(
    'passwordPolicy' => array(
      'repetition_max' => $constraint,
    ),
  );
  drupal_add_js($data, 'setting');

  return <<<JS

    if (!Drupal.settings.passwordPolicy.repetition_max) {
      return;
    }

    // No case sensitivity. aAa is not as bad as aaa.
    // use regex of the form that matches if there's more than the repetition_max
    // e.g. (.){3,) matches on 3 or more.
    var pattern = new RegExp('(.){' + (parseInt(Drupal.settings.passwordPolicy.repetition_max) + 1) + ',}', 'g');

    if (value.match(pattern)) {
      strength = 'low';
      msg.push(translate.constraint_characterrepetition);
    }
JS;
}
