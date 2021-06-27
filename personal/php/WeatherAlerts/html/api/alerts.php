<?php

include_once "util/util.php";


// Input validation
$requestMethod = filter_input(INPUT_SERVER, 'REQUEST_METHOD', FILTER_SANITIZE_STRING);
$uuid = filter_input(INPUT_GET, 'uuid', FILTER_SANITIZE_STRING);

// Return user alerts
if($requestMethod === 'GET')
{
    $data = json_decode('[{"label":"A"}, {"label":"B"}, {"label":"C"}]');

    success_response($data);
    return;
}

// Update user alerts
else if($requestMethod === 'POST')
{
    error_response(400);
    return;
}

error_response(400);