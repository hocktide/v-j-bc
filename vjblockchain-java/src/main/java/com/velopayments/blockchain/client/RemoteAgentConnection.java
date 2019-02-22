package com.velopayments.blockchain.client;

import com.velopayments.blockchain.agentd.*;
import com.velopayments.blockchain.cert.Certificate;

import javax.net.SocketFactory;
import java.io.IOException;
import java.util.Optional;
import java.util.UUID;
import java.util.concurrent.CompletableFuture;

public class RemoteAgentConnection implements VelochainConnection {

    private RemoteAgentConfiguration config;
    private RemoteAgentChannel remoteAgentChannel;
    private ProtocolHandler protocolHandler;

    public RemoteAgentConnection(RemoteAgentConfiguration config,
                                 SocketFactory socketFactory) {
        this.config = config;
        this.remoteAgentChannel = new RemoteAgentChannelImpl(config, socketFactory);
        this.protocolHandler = new ProtocolHandlerImpl(config,remoteAgentChannel);
    }

    @Override
    public void commitTransactions() throws IOException {

    }

    @Override
    public void cancelTransactions() throws IOException {

    }

    public void connect() throws IOException {
        remoteAgentChannel.connect();
        protocolHandler.handshake();
    }

    @Override
    public void close() throws IOException {

        /* commit outstanding transactions. */
        commitTransactions();

        remoteAgentChannel.close();
    }

    @Override
    public CompletableFuture<TransactionStatus> submit(Certificate transaction)
    throws IOException {
        return null;
    }

    @Override
    public UUID getLatestBlockId()
    throws IOException {

        return null;
    }

    @Override
    public Optional<UUID> getNextBlockId(UUID blockId)
    throws IOException {

        return protocolHandler.sendAndReceiveUUID(ApiMethod.GET_NEXT_BLOCK_ID, blockId);
    }

    @Override
    public Optional<UUID> getPrevBlockId(UUID blockId)
    throws IOException {

        return protocolHandler.sendAndReceiveUUID(ApiMethod.GET_PREV_BLOCK_ID, blockId);
    }

    @Override
    public Optional<UUID> getTransactionBlockId(UUID txnId)
    throws IOException {

        return protocolHandler.sendAndReceiveUUID(ApiMethod.GET_TXN_BLOCK_ID, txnId);
    }

    @Override
    public Optional<Certificate> getBlockById(UUID blockId)
    throws IOException {

        return Optional.empty();
    }

    @Override
    public Optional<UUID> getBlockIdByBlockHeight(long height)
    throws IOException {

        return Optional.empty();
    }

    @Override
    public Optional<Certificate> getTransactionById(UUID txnId)
    throws IOException {

        return Optional.empty();
    }

    @Override
    public Optional<UUID> getFirstTransactionIdForArtifactById(UUID artifactId)
    throws IOException {

        return protocolHandler.sendAndReceiveUUID(
                ApiMethod.GET_FIRST_TXN_ID_FOR_ARTIFACT_BY_ID,
                artifactId);
    }

    @Override
    public Optional<UUID> getLastTransactionIdForArtifactById(UUID artifactId)
    throws IOException {

        return protocolHandler.sendAndReceiveUUID(
                ApiMethod.GET_LAST_TXN_ID_FOR_ARTIFACT_BY_ID,
                artifactId);
    }

    @Override
    public Optional<UUID> getLastBlockIdForArtifactById(UUID artifactId)
    throws IOException {

        return protocolHandler.sendAndReceiveUUID(
                ApiMethod.GET_LAST_BLOCK_ID_FOR_ARTIFACT_BY_ID,
                artifactId);
    }

    @Override
    public Optional<UUID> getPreviousTransactionIdForTransactionById(UUID txnId)
    throws IOException {

        return protocolHandler.sendAndReceiveUUID(
                ApiMethod.GET_PREV_TXN_ID_FOR_TXN_BY_ID,
                txnId);
    }

    @Override
    public Optional<UUID> getNextTransactionIdForTransactionById(UUID txnId)
    throws IOException {

        return protocolHandler.sendAndReceiveUUID(
                ApiMethod.GET_NEXT_TXN_ID_FOR_TXN_BY_ID,
                txnId);
    }
}