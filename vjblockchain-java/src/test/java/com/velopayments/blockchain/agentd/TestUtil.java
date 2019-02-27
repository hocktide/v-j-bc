package com.velopayments.blockchain.agentd;

import com.velopayments.blockchain.cert.Certificate;
import com.velopayments.blockchain.crypt.GenericStreamCipher;
import com.velopayments.blockchain.util.ByteUtil;
import com.velopayments.blockchain.util.UuidUtil;

import java.util.UUID;

public class TestUtil {

    /**
     * The format of the outer envelope response is as follows:
     *   byte 0            message type
     *   bytes 1 - 4       size of payload big endian format
     *   bytes 5 - N+5     encrypted payload
     *   bytes N+6 - N+38  HMAC of envelope (all previous bytes)
     *
     * @param encryptionKey
     * @param apiMethod
     * @param requestId
     * @param status
     * @param payload
     * @return
     */
    public static byte[] createAgentdResponse(byte[] encryptionKey,ApiMethod apiMethod,
                                              long requestId, long status, byte[] payload) {

        // build inner envelope response
        byte inner[] = new byte[12 + payload.length];

        // first four bytes of inner envelope are the api method
        System.arraycopy(ByteUtil.longToBytes(apiMethod.getValue(),4,true),
                0, inner,0,4);

        // next four bytes of inner envelope are the request ID
        System.arraycopy(ByteUtil.longToBytes(requestId, 4,true), 0, inner, 4, 4);

        // next four bytes of inner envelope are the response
        System.arraycopy(ByteUtil.longToBytes(status, 4,true), 0, inner, 8, 4);

        // the remaining bytes of the inner envelope are the payload
        System.arraycopy(payload, 0, inner, 12, payload.length);

        // now to build the outer envelope
        byte[] encryptedPayload = GenericStreamCipher.encrypt(encryptionKey, new byte[8], inner);

        // create a buffer to hold the output
        byte response[] = new byte[1 + 4 + encryptedPayload.length + 32];

        // bytes 1 - 4 are the size of the encrypted payload
        System.arraycopy(ByteUtil.longToBytes(encryptedPayload.length,4, true), 0, response, 1, 4);

        // bytes 5 - N+5 are the encrypted payload
        System.arraycopy(encryptedPayload, 0, response, 5, encryptedPayload.length);

        // TODO: HMAC

        return response;
    }

    public static byte[] createBlockResponsePayload(UUID blockId, byte[] certificateBytes) {

        byte[] response = new byte[72 + (certificateBytes==null ? 0 : certificateBytes.length)];

        // first 16 bytes are blockId
        System.arraycopy(UuidUtil.getBytesFromUUID(blockId), 0, response, 0, 16);

        UUID prevBlockId = UUID.randomUUID();
        System.arraycopy(UuidUtil.getBytesFromUUID(prevBlockId), 0, response, 16, 16);

        UUID nextBlockId = UUID.randomUUID();
        System.arraycopy(UuidUtil.getBytesFromUUID(nextBlockId), 0, response, 32, 16);

        UUID firstTxId = UUID.randomUUID();
        System.arraycopy(UuidUtil.getBytesFromUUID(firstTxId), 0, response, 48, 16);

        long blockHeight = 7L;
        System.arraycopy(ByteUtil.longToBytes(blockHeight, true), 0, response, 64, 8);

        // the remaining bytes are the certificate
        if (certificateBytes != null) {
            System.arraycopy(certificateBytes, 0, response, 72, certificateBytes.length);
        }

        return response;
    }


    public static byte[] createTransactionResponsePayload(UUID transactionId, byte[] certificateBytes) {

        byte[] response = new byte[64 + (certificateBytes==null ? 0 : certificateBytes.length)];

        // first 16 bytes are transactionId
        System.arraycopy(UuidUtil.getBytesFromUUID(transactionId), 0, response, 0, 16);

        UUID prevTransactionId = UUID.randomUUID();
        System.arraycopy(UuidUtil.getBytesFromUUID(prevTransactionId), 0, response, 16, 16);

        UUID nextTransactionId = UUID.randomUUID();
        System.arraycopy(UuidUtil.getBytesFromUUID(nextTransactionId), 0, response, 32, 16);

        UUID artifactId = UUID.randomUUID();
        System.arraycopy(UuidUtil.getBytesFromUUID(artifactId), 0, response, 48, 16);

        // the remaining bytes are the certificate
        if (certificateBytes != null) {
            System.arraycopy(certificateBytes, 0, response, 64, certificateBytes.length);
        }

        return response;
    }

}
