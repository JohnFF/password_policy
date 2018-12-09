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

  $password = drupal_strtolower($password);

  $pattern_list = password_policy_constraint_pattern_get_pattern_list();

  foreach ($pattern_list as $each_pattern_entry) {
    if (strpos($password, $each_pattern_entry) !== FALSE) {
      return FALSE;
    }
  }

  $leet_translations = array(
    '4' => 'a',
    '3' => 'e',
    '0' => 'o',
    '1' => 'l',
    '7' => 't',
  );

  $translated_password = strtr($password, $leet_translations);

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
  $data = array(
    'passwordPolicy' => array(
      'passwords_patterns' => password_policy_constraint_pattern_get_pattern_list(),
    ),
  );
  drupal_add_js($data, 'setting');

  return <<<JS

    if (!Drupal.settings.passwordPolicy.passwords_patterns) {
      return;
    }
    var password_lowercase = value.toLowerCase();

    var arrayLength = Drupal.settings.passwordPolicy.passwords_patterns.length;
    for (var i = 0; i < arrayLength; i++) {
      if (password_lowercase.includes(Drupal.settings.passwordPolicy.passwords_patterns[i])) {
        strength = 'low';
        msg.push(translate.constraint_pattern);
      }
    }
JS;
}
