<?php

// Strings
function duration_from_seconds($total_seconds)
{
    $duration = date('i:s', $total_seconds);
    if($total_seconds < 60 * 10)
    {
        $duration = substr($duration, 1);
    }
    else if($total_seconds > 60 * 60)
    {
        $duration = (integer) ($total_seconds / 60 / 60) . ":" . $duration;
    }
    return $duration;
}

function date_from_components($year, $month = null, $day = null)
{
    if($month != null)
    {
        if($day != null)
        {
            return sprintf("%02d/%02d/%02d", $month, $day, $year);
        }

        return sprintf("%02d/%02d", $month, $year);
    }

    return $year;
}

function random_string($length = 32)
{
    return bin2hex(random_bytes($length));
}

// API response
function http_response_code_description($response_code)
{
    switch($response_code)
    {
        case 100: return 'Continue';
        case 101: return 'Switching Protocols';
        case 200: return 'OK';
        case 201: return 'Created';
        case 202: return 'Accepted';
        case 203: return 'Non-Authoritative Information';
        case 204: return 'No Content';
        case 205: return 'Reset Content';
        case 206: return 'Partial Content';
        case 300: return 'Multiple Choices';
        case 301: return 'Moved Permanently';
        case 302: return 'Moved Temporarily';
        case 303: return 'See Other';
        case 304: return 'Not Modified';
        case 305: return 'Use Proxy';
        case 400: return 'Bad Request';
        case 401: return 'Unauthorized';
        case 402: return 'Payment Required';
        case 403: return 'Forbidden';
        case 404: return 'Not Found';
        case 405: return 'Method Not Allowed';
        case 406: return 'Not Acceptable';
        case 407: return 'Proxy Authentication Required';
        case 408: return 'Request Time-out';
        case 409: return 'Conflict';
        case 410: return 'Gone';
        case 411: return 'Length Required';
        case 412: return 'Precondition Failed';
        case 413: return 'Request Entity Too Large';
        case 414: return 'Request-URI Too Large';
        case 415: return 'Unsupported Media Type';
        case 500: return 'Internal Server Error';
        case 501: return 'Not Implemented';
        case 502: return 'Bad Gateway';
        case 503: return 'Service Unavailable';
        case 504: return 'Gateway Time-out';
        case 505: return 'HTTP Version not supported';
    }
}

function response($response_code, $message)
{
    http_response_code($response_code);

    $response = array();
    if($response_code >= 200 && $response_code < 300)
    {
        $response['data'] = $message;
    }
    else
    {
        $response['error'] = $message;
    }

    echo json_encode($response);
    exit();
}

function success_response($data)
{
    response(200, $data);
}

function error_response($response_code, $message = null)
{
    if(!isset($message))
    {
        $message = http_response_code_description($response_code);
    }

    response($response_code, $message);
}
