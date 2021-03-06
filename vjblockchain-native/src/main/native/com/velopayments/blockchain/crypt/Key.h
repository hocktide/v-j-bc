/**
 * \file Key.h
 *
 * Class and method exports for Key.  This header includes a static registration
 * mechanism for creating global references to the Key class, so that Key
 * instances can be created from C and methods for these instances can be called
 * from C.
 *
 * \copyright 2019 Velo Payments, Inc.  All rights reserved.
 */

#ifndef  PRIVATE_KEY_HEADER_GUARD
# define PRIVATE_KEY_HEADER_GUARD

#include <jni.h>

#include "../init/init_fwd.h"

/* make this header C++ friendly */
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/* forward decls. */
typedef struct Key_JavaVars
Key_JavaVars;

/**
 * Register the following Key references and make them global.
 *
 * Note: this method must be called in a synchronized static initialization
 * block in Java to ensure that there isn't a registration race.  This method
 * must be called before any of the following references are used.
 *
 * \param env   JNI environment to use.
 * \param inst  native instance to initialize.
 *
 * \returns 0 on success and non-zero on failure.
 */
int
Key_register(
    JNIEnv* env,
    vjblockchain_native_instance* inst);

/**
 * \brief Java variables for Key.
 */
struct Key_JavaVars
{
    /* public class com.velopayments.blockchain.crypt.Key {
     */
    jclass classid;

    /* public com.velopayments.blockchain.crypt.Key(byte[]);
     * descriptor: ([B)V
     */
    jmethodID init;

    /* public byte[] getRawBytes();
     * descriptor: ()[B
     */
    jmethodID getRawBytes;

    /*
     * private byte[] key;
     * descriptor: [B
     */
    jfieldID key;
};

/* helper macro. */
#define KEY_JAVA_VARS() \
    Key_JavaVars Key

/* make this header C++ friendly */
#ifdef __cplusplus
}
#endif //__cplusplus

#endif //PRIVATE_KEY_HEADER_GUARD
