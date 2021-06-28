<?php

include_once "util/util.php";

// Input validation
$requestMethod = filter_input(INPUT_SERVER, 'REQUEST_METHOD', FILTER_SANITIZE_STRING);
$uuid = filter_input(INPUT_GET, 'uuid', FILTER_SANITIZE_STRING);
$debug = filter_input(INPUT_GET, 'debug', FILTER_VALIDATE_BOOLEAN);

// Return user alerts
if ($requestMethod === 'GET') {
    if ($debug) {
        $dateFormat = "Y-m-d\TH:i:s\Z";
        $currTime = time();
                
        $data = array(
            array("postcode" => "12345",
                "alerts" => array(
                    array("type" => "freezing", "datetime" => gmdate($dateFormat, $currTime + (2 * 60 * 60))),
                    array("type" => "lightning", "datetime" => gmdate($dateFormat, $currTime + (4.5 * 60 * 60))),
                    array("type" => "tornado", "datetime" => gmdate($dateFormat, $currTime + (8.75 * 60 * 60))))),
            array("postcode" => "67890",
                "alerts" => array(
                    array("type" => "hurricane", "datetime" => gmdate($dateFormat, $currTime + (3.25 * 60 * 60))))),
            array("postcode" => "11111"));

        success_response($data);
        return;
    }

    error_response(400);
    return;
}

// Update user alerts
else if ($requestMethod === 'POST') {
    error_response(400);
    return;
}

error_response(400);
