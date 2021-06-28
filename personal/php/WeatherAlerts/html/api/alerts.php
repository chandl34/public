<?php

include_once "util/util.php";


// Input validation
$requestMethod = filter_input(INPUT_SERVER, 'REQUEST_METHOD', FILTER_SANITIZE_STRING);
$uuid = filter_input(INPUT_GET, 'uuid', FILTER_SANITIZE_STRING);
$debug = filter_input(INPUT_GET, 'debug', FILTER_VALIDATE_BOOLEAN); 

// Return user alerts
if($requestMethod === 'GET')
{
    if(!$debug)
    {
        error_response(400);
        return;
    }
    
    $data = json_decode('[' . 
            '{"postcode":"12345", "alerts":[{"type":"freezing", "datetime":"02/10/2021 08:00am EST"}, {"type":"lightning", "datetime":"02/10/2021 10:00am EST"}, {"type":"tornado", "datetime":"02/10/2021 06:00pm EST"}]}, ' . 
            '{"postcode":"67890", "alerts":[{"type":"hurricane", "datetime":"02/10/2021 09:00am EST"}]}, ' . 
            '{"postcode":"11111", "alerts":[]}' .
            ']');

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