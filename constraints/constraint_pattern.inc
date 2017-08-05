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
function password_policy_constraint_pattern_description() {
  return array('name' => t('Keyboard Patterns'), 'description' => t('Passwords may not contain digit or keyboard patterns such as "abc", "123", "qwer", etc.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_pattern_error($constraint) {
  return t('Passwords may not contain patterns such as "abc" "123" "qwerty" etc.');
}

/**
 * Returns the list of passwords that contain pattern patterns.
 *
 * @return array of strings in lower case.
 */
function password_policy_constraint_pattern_get_pattern_list() {
  return array(
    // Digit patterns.
    '123', 
    '321',
    'abc',
    'cba',

    // Keyboard patterns.
    'qwer',
    'qazw',
    'zxcv',
    'zaqx',
    'asdf',
    '1q2w3',
    'q1w2e3',
    '!"£$',
    '?><M',
  );
}

/**
 * Password validation.
 */
function password_policy_constraint_pattern_validate($password, $constraint, $account) {

  $translated_password = drupal_strtolower($password);

  $leet_translations = array(
    '4' => 'a',
    '3' => 'e',
    '0' => 'o',
    '1' => 'l',
    '7' => 't',
  );

  $translated_password = strtr($translated_password, $leet_translations);

  $pattern_list = password_policy_constraint_pattern_get_pattern_list();

  foreach ($pattern_list as $each_pattern_entry) {
    if (strpos($translated_password, $each_pattern_entry) !== FALSE) {
      return FALSE;
    }
  }

  return TRUE;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_pattern_js($constraint, $account) {
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
//        msg.push(translate.constraint_pattern);
//      }
//    }
//JS;
}
