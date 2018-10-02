/**
 * \file SigningPrivateKey.h
 *
 * Class and method exports for SigningPrivateKey.  This header includes a
 * static registration mechanism for creating global references to the
 * SigningPrivateKey class, so that SigningPrivateKey instances can be created
 * from C and methods for these instances can be called from C.
 */

#ifndef  PRIVATE_SIGNING_PRIVATE_KEY_HEADER_GUARD
# define PRIVATE_SIGNING_PRIVATE_KEY_HEADER_GUARD

#include <jni.h>

/* make this header C++ friendly */
#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/**
 * Register the following SigningPrivateKey references and make them global.
 *
 * Note: this method must be called in a synchronized static initialization
 * block in Java to ensure that there isn't a registration race.  This method
 * must be called before any of the following references are used.
 *
 * \param env   JNI environment to use.
 *
 * \returns 0 on success and non-zero on failure.
 */
int SigningPrivateKey_register(JNIEnv* env);

/* public class com.velopayments.blockchain.crypt.SigningPrivateKey {
 */
extern jclass SigningPrivateKey;

/* public com.velopayments.blockchain.crypt.SigningPrivateKey(byte[]);
 * descriptor: ([B)V
 */
extern jmethodID SigningPrivateKey_init;

/* public byte[] getRawBytes();
 * descriptor: ()[B
 */
extern jmethodID SigningPrivateKey_getRawBytes;

/* make this header C++ friendly */
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*PRIVATE_SIGNING_PRIVATE_KEY_HEADER_GUARD*/
