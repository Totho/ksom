/* 
 * File:   ksom_error.h
 * Author: John
 *
 * Created on October 24, 2009, 10:35 AM
 */

#ifndef _KSOM_ERROR_H
#define	_KSOM_ERROR_H

#ifdef	__cplusplus
extern "C" {
#endif

    #define NULL 0
    #define KSOM_FAIL(x) x != KSOM_OK ? 1 : 0
    
    typedef enum _KSOM_ERROR {
        KSOM_OK,
        KSOM_INTERNAL, /* internal logic error */
        KSOM_NOMEM, /* out of memory */
        KSOM_INVALID_NET_OPT,
        KSOM_INVALID_NODE_OPT,
        KSOM_INVALID_FV
    } KSOM_ERROR;

    char * ksom_error_str(KSOM_ERROR e);

#ifdef	__cplusplus
}
#endif

#endif	/* _KSOM_ERROR_H */

