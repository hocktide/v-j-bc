/**
 * \file uuid_conv.h
 *
 * Convert a byte array to a Java UUID.
 */
#ifndef  PRIVATE_UUID_CONV_HEADER_GUARD
# define PRIVATE_UUID_CONV_HEADER_GUARD

#include <jni.h>

/**
 * Convert a C byte array to a Java UUID.
 *
 * \param env               Java environment.
 * \param uuid_bytes        The 128-bit UUID in serialized byte form.
 *
 * \returns a Java UUID object, or NULL if the UUID could not be converted.
 * Note that if this method returns NULL, it will throw an
 * IllegalArgumentException.
 */
jobject uuidFromBytes(JNIEnv* env, const uint8_t* uuid_bytes);

#endif //PRIVATE_UUID_CONV_HEADER_GUARD