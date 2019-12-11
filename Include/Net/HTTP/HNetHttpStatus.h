#ifndef APP_HNETHTTPSTATUS_H
#define APP_HNETHTTPSTATUS_H

enum EHttpStatus {
    EHS_INVALID_CODE = 0,
    EHS_CONTINUE = 100,
    EHS_SWITCHING_PROTOCOLS = 101,
    EHS_OK = 200,
    EHS_CREATED = 201,
    EHS_ACCEPTED = 202,
    EHS_NON_AUTHORITATIVE_INFO = 203,
    EHS_NO_CONTENT = 204,
    EHS_RESET_CONTENT = 205,
    EHS_PARTIAL_CONTENT = 206,
    EHS_MULTIPLE_CHOICES = 300,
    EHS_MOVED_PERMANENTLY = 301,
    EHS_FOUND = 302,
    EHS_SEE_OTHER = 303,
    EHS_NOT_MODIFIED = 304,
    EHS_USE_PROXY = 305,
    EHS_TEMPORARY_REDIRECT = 307,
    EHS_BAD_REQUEST = 400,
    EHS_UNAUTHORIZED = 401,
    EHS_PAYMENT_REQUIRED = 402,
    EHS_FORBIDDEN = 403,
    EHS_NOT_FOUND = 404,
    EHS_METHOD_NOT_ALLOWED = 405,
    EHS_NOT_ACCEPTABLE = 406,
    EHS_PROXY_AUTHENTICATION_REQUIRED = 407,
    EHS_REQUEST_TIMEOUT = 408,
    EHS_CONFLICT = 409,
    EHS_GONE = 410,
    EHS_LENGTH_REQUIRED = 411,
    EHS_PRECONDITION_FAILED = 412,
    EHS_REQUEST_ENTITY_TOO_LARGE = 413,
    EHS_UNSUPPORTED_MEDIA_TYPE = 415,
    EHS_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
    EHS_EXPECTATION_FAILED = 417,
    EHS_INTERNAL_SERVER_ERROR = 500,
    EHS_NOT_IMPLEMENTED = 501,
    EHS_BAD_GATEWAY = 502,
    EHS_SERVICE_UNAVAILABLE = 503,
    EHS_GATEWAY_TIMEOUT = 504,
    EHS_VERSION_NOT_SUPPORTED = 505,
    EHS_NET_OVERLOAD = 509  //Not a official code
};

#endif //APP_HNETHTTPSTATUS_H