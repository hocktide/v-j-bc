/**
 * \file AgentConnection_getBlockByIdNative.c
 *
 * Get a Block from the database by a UUID.
 *
 * \copyright 2018 Velo Payments, Inc.  All rights reserved.
 */

#include <cbmc/model_assert.h>
#include <com/velopayments/blockchain/client/AgentConnection.h>
#include <com/velopayments/blockchain/client/AgentConnectionPrivate.h>
#include <com/velopayments/blockchain/init/init.h>
#include <java/lang/IllegalStateException.h>
#include <java/util/Optional.h>
#include <string.h>
#include <util/uuid_conv.h>
#include <vpr/parameters.h>

/*
 * Class:     com_velopayments_blockchain_client_AgentConnection
 * Method:    getBlockByIdNative
 * Signature: (Ljava/util/UUID;)Ljava/util/Optional;
 */
JNIEXPORT jobject JNICALL
Java_com_velopayments_blockchain_client_AgentConnection_getBlockByIdNative(
    JNIEnv* env, jobject that, jobject blockId)
{
    jobject retval = NULL;

    /* function contract enforcement. */
    MODEL_ASSERT(MODEL_PROP_VALID_JNI_ENV(env));
    MODEL_ASSERT(NULL != that);
    MODEL_ASSERT(NULL != blockId);

    /* verify that the vjblockchain library has been initialized. */
    if (!vjblockchain_initialized)
    {
        (*env)->ThrowNew(env, IllegalStateException,
                         "vjblockchain not initialized.");
        goto exit_return;
    }

    /* get the handle for our connection details. */
    jlong handle =
        (*env)->GetLongField(env, that, AgentConnection_field_handle);

    /* transform this value into our connection details struct. */
    agent_connection_details_t* details = (agent_connection_details_t*)handle;
    if (NULL == details || NULL == details->env)
    {
        (*env)->ThrowNew(env, IllegalStateException,
                         "AgentConnection handle invariant violated.");
        goto exit_return;
    }

    /* get the bytes for this transaction id. */
    uint8_t block_id_bytes[16];
    uuidToBytes(env, blockId, block_id_bytes);

    /* create a transaction for querying the database. */
    MDB_txn* txn;
    if (0 != mdb_txn_begin(details->env, NULL, 0, &txn))
    {
        (*env)->ThrowNew(env, IllegalStateException,
                         "Could not create transaction "
                         "for querying blockchain.");
        goto exit_return;
    }

    /* query the database. */
    MDB_val key; key.mv_size = 16; key.mv_data = block_id_bytes;
    MDB_val val; memset(&val, 0, sizeof(val));
    int dbstat = mdb_get(txn, details->block_db, &key, &val);
    if (MDB_NOTFOUND == dbstat)
    {
        retval = (*env)->CallStaticObjectMethod(env, Optional, Optional_empty);
        goto cleanup_txn;
    }
    else if (0 != dbstat)
    {
        (*env)->ThrowNew(env, IllegalStateException,
                         "Could not query block database.");
        goto cleanup_txn;
    }

    /* create array for return value. */
    block_record_t* rec = (block_record_t*)val.mv_data;
    jbyteArray arr = (*env)->NewByteArray(env, rec->block_size);
    if (NULL == arr)
    {
        (*env)->ThrowNew(env, IllegalStateException,
                         "Could not allocate byte array.");
        goto cleanup_txn;
    }

    /* get the raw bytes of this array. */
    uint8_t* arr_bytes = (*env)->GetByteArrayElements(env, arr, NULL);

    /* copy the value from the database to the Java raw array. */
    memcpy(arr_bytes, ((uint8_t*)rec) + sizeof(block_record_t),
           rec->block_size);

    /* Release the array. */
    (*env)->ReleaseByteArrayElements(env, arr, arr_bytes, 0);

    /* success. */
    retval = (*env)->CallStaticObjectMethod(env, Optional, Optional_of, arr);

cleanup_txn:
    mdb_txn_abort(txn);

exit_return:
    return retval;
}
