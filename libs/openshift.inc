<?php

// Loop through all provided variables and generate secure versions
// If not running on OpenShift, returns defaults and logs an error message
//
// This function calls secure_function and passes an array of:
//  { 
//    'hash'     => generated sha hash,
//    'variable' => name of variable,
//    'original' => original value
//  }
function openshift_secure($default_keys,$secure_function = null) {
  // Attempts to get secret token

  // $my_token = getenv('CAKEPHP_SECRET_KEY');
  $my_token = 'TEST0439fdsdh7gfw87fnw4rawef4';

  // Only generate random values if on OpenShift
  $array = $default_keys;

  // Loop over each default_key and set the new value
  foreach ($default_keys as $key => $value) {
    // Create hash out of token and this key's name
    $sha = hash('sha256',"$my_token-$key");
    // Pass an array so we can add stuff without breaking existing calls
    $vals = array(
      'hash' => $sha,
      'variable'  => $key,
      'original'  => $value
    );
    // Call user specified function or just return hash
    $array[$key] = ($secure_function ? call_user_func($secure_function,$vals) : $sha);
  }
  return $array;
}

?>
