#include "ksom_error.h"

char * ksom_error_str(KSOM_ERROR e) {

    switch (e) {
        case KSOM_OK:
            return "KSOM: no error";
        case KSOM_INTERNAL:
            return "KSOM: internal error";
        case KSOM_NOMEM:
            return "KSOM: out of memory";
        case KSOM_INVALID_NET_OPT:
            return "KSOM: invalid network option";
        case KSOM_INVALID_NODE_OPT:
            return "KSOM: invalid node option";
        case KSOM_INVALID_FV:
            return "KSOM: invalid feature vector";
    }

    return "KSOM: unknown error code";
}
