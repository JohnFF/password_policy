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
function password_policy_constraint_character_repetition_description() {
  return array('name' => t('Character Repetition'), 'description' => t('Passwords may not repeat the same number of characters too many times.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_character_repetition_error($constraint) {
  return format_string('Passwords may not repeat the same letter more than @count times.', array('@count' => $constraint));
}

/**
 * Password validation.
 */
function password_policy_constraint_character_repetition_validate($password, $constraint, $account) {

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
    if ($each_character_repetition_entry >= $constraint) {
      return FALSE;
    }
  }

  return TRUE;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_character_repetition_js($constraint, $account) {
  // Add username as JavaScript setting.
//  $username = isset($account->name) ? $account->name : '';
//  $data = array(
//    'passwordPolicy' => array(
//      'username' => $username,
//    ),
//  );
//  drupal_add_js($data, 'setting');
//
//  return <<<JS
//
//    var username = '';
//    var usernameInput = jQuery('input.username');
//    if (usernameInput.length) {
//      username = usernameInput.val();
//    }
//    else {
//      username = Drupal.settings.passwordPolicy.username;
//    }
//    if (username) {
//      var username_lowercase = username.toLowerCase();
//      var password_lowercase = value.toLowerCase();
//      if (password_lowercase.indexOf(username_lowercase) != -1) {
//        strength = 'low';
//        msg.push(translate.constraint_character_repetition);
//      }
//    }
//JS;
}
