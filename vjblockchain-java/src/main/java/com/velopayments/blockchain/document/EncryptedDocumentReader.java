package com.velopayments.blockchain.document;


import com.velopayments.blockchain.crypt.EncryptionPrivateKey;
import com.velopayments.blockchain.crypt.EncryptionPublicKey;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Arrays;

public class EncryptedDocumentReader {

    private byte[] secretKey;
    private InputStream encryptedDocStream;

    /**
     * Create an EncryptedDocumentReader from a private key, a public key, a shared secret
     * and an InputStream.
     *
     * @param localPrivateKey     The private key of the entity reading this document.
     * @param peerPublicKey       The public key of the peer that created this document.
     * @param sharedSecret        The shared secret produced for the entity reading this document.
     * @param encryptedDocStream  The document to be decrypted.
     */
    public EncryptedDocumentReader(EncryptionPrivateKey localPrivateKey, EncryptionPublicKey peerPublicKey,
                                   byte[] sharedSecret, InputStream encryptedDocStream) {

        this.secretKey = decryptSecretNative(localPrivateKey, peerPublicKey, sharedSecret);
        this.encryptedDocStream = encryptedDocStream;
    }

    /**
     * Get the encrypted document as an InputStream.  Note the document is
     * returned in decrypted form.
     *
     * @return an InputStream representing the encrypted document
     */
    public InputStream getEncrypted() throws IOException {


        // unpack this in the same way it was packed up
        int r,offset = 0;
        byte[] buffer = new byte[EncryptedDocumentBuilder.BUFFER_SIZE];

        // the first 8 bytes are the IV
        byte[] iv = new byte[8];
        encryptedDocStream.read(iv, 0, iv.length);

        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        while ((r = encryptedDocStream.read(buffer, 0, buffer.length)) != -1) {
            byte[] chunk;
            if (0 == offset) {
                chunk = Arrays.copyOf(iv, iv.length + r);
                System.arraycopy(buffer, 0, chunk, iv.length, r);
            } else {
                chunk = Arrays.copyOf(buffer, r);
            }
            byte[] decrypted = decryptNative(secretKey, chunk, offset);
            ++offset;

            bos.write(decrypted);
        }

        // TODO
        return new ByteArrayInputStream(bos.toByteArray());
    }

    /**
     * Recover the secret key from the given local private key, peer public key,
     * and encrypted key.
     *
     * @param localPrivateKey   The local private key.
     * @param peerPublicKey     The peer public key.
     * @param encryptedKey      The encrypted key to decrypt.
     *
     * @return the decrypted key.
     */
    private static native byte[] decryptSecretNative(
            EncryptionPrivateKey localPrivateKey, EncryptionPublicKey peerPublicKey,
            byte[] encryptedKey);

    /**
     * Decrypt the input value using the provided secret key.
     *
     * @param secretKey     The secret key to use to decrypt this value.
     * @param input         The input value to decrypt.
     * @param offset
     *
     * @return the decrypted value.
     */
    private static native byte[] decryptNative(byte[] secretKey, byte[] input, int offset);

}
