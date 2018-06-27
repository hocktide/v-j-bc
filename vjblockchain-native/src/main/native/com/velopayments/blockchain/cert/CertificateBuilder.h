/**
 * \file CertificateBuilder.h
 *
 * Class and method exports for CertificateBuilder.  This header includes a
 * static registration mechanism for creating global references to the
 * CertificateBuilder class, so that CertificateParser instances can be created
 * from C and methods for these instances can be called from C.
 */

#ifndef  PRIVATE_CERTIFICATE_BUILDER_HEADER_GUARD
# define PRIVATE_CERTIFICATE_BUILDER_HEADER_GUARD

#include <jni.h>

/* make this header C++ friendly */
#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/**
 * Register the following CertificateBuilder references and make them global.
 *
 * Note: this method must be called in a synchronized static initialization
 * block in Java to ensure that there isn't a registration race.  This method
 * must be called before any of the following references are used.
 *
 * \param env   JNI environment to use.
 *
 * \returns 0 on success and non-zero on failure.
 */
int CertificateBuilder_register(JNIEnv* env);

/* public class com.velopayments.blockchain.cert.CertificateBuilder {
 */
extern jclass CertificateBuilder;

/* private java.util.LinkedList<
 *      java.util.AbstractMap$SimpleEntry<java.lang.Integer, byte[]>> fields;
 * descriptor: Ljava/util/LinkedList;
 */
extern jfieldID CertificateBuilder_field_fields;

/* public com.velopayments.blockchain.cert.CertificateBuilder
 * addByte(int, byte);
 * descriptor: (IB)Lcom/velopayments/blockchain/cert/CertificaeBuilder;
 */
extern jmethodID CertificateBuilder_addByte;

/* public com.velopayments.blockchain.cert.CertificateBuilder
 * addShort(int, int);
 * descriptor: (II)Lcom/velopayments/blockchain/cert/CertificateBuilder;
 */
extern jmethodID CertificateBuilder_addShort;

/* public com.velopayments.blockchain.cert.CertificateBuilder addInt(int, int);
 * descriptor: (II)Lcom/velopayments/blockchain/cert/CertificateBuilder;
 */
extern jmethodID CertificateBuilder_addInt;

/* public com.velopayments.blockchain.cert.CertificateBuilder
 * addLong(int, long);
 * descriptor: (IJ)Lcom/velopayments/blockchain/cert/CertificateBuilder;
 */
extern jmethodID CertificateBuilder_addLong;

/* public com.velopayments.blockchain.cert.CertificateBuilder
 * addUUID(int, java.util.UUID);
 * descriptor:
 *   (ILjava/util/UUID;)Lcom/velopayments/blockchain/cert/CertificateBuilder;
 */
extern jmethodID CertificateBuilder_addUUID;

/* public com.velopayments.blockchain.cert.CertificateBuilder
 * addString(int, java.lang.String);
 * descriptor:
 *   (ILjava/lang/String;)Lcom/velopayments/blockchain/cert/CertificateBuilder;
 */
extern jmethodID CertificateBuilder_addString;

/* public com.velopayments.blockchain.cert.CertificateBuilder
 * addDate(int, java.util.Date);
 * descriptor:
 *   (ILjava/util/Date;)Lcom/velopayments/blockchain/cert/CertificateBuilder;
 */
extern jmethodID CertificateBuilder_addDate;

/* public byte[]
 * sign(java.util.UUID, com.velopayments.blockchain.crypt.SigningPrivateKey);
 * descriptor:
 * (Ljava/util/UUID;Lcom/velopayments/blockchain/crypt/SigningPrivateKey;)[B
 */
extern jmethodID CertificateBuilder_sign;

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*PRIVATE_CERTIFICATE_BUILDER_HEADER_GUARD*/