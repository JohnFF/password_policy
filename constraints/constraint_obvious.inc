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
function password_policy_constraint_obvious_description() {
  return array('name' => t('Obvious'), 'description' => t('Passwords may not be easy to guess, for example, "password".'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_obvious_error($constraint) {
  return t('Passwords may not be easy to guess. Examples include "password".');
}

/**
 * Returns the list of passwords that contain obvious patterns.
 *
 * @return array of strings in lower case.
 */
function password_policy_constraint_obvious_get_obvious_list() {
  return array(
    // Common words/phrases.
    'pass',
    'login',
    'enter',
    'letmein',
    'qwerty',
    'abcdef',
    'abcabc',
    'aabbcc',
    'abc123',
    'computer',
    'laptop',
    'monitor',
  );
}

/**
 * Password validation.
 */
function password_policy_constraint_obvious_validate($password, $constraint, $account) {

  $translated_password = drupal_strtolower($password);

  $leet_translations = array(
    '0' => 'o',
    '1' => 'l',
    '3' => 'e',
    '4' => 'a',
    '5' => 's',
    '7' => 't',
  );

  $translated_password = strtr($translated_password, $leet_translations);

  $obvious_list = password_policy_constraint_obvious_get_obvious_list();

  foreach ($obvious_list as $each_obvious_entry) {
    if (strpos($translated_password, $each_obvious_entry) !== FALSE) {
      return FALSE;
    }
  }

  return TRUE;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_obvious_js($constraint, $account) {
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
//        msg.push(translate.constraint_obvious);
//      }
//    }
//JS;
}
