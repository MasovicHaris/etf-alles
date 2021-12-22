package com.event4u.eventsservice.service;

import com.event4u.eventsservice.grpc.Event4U;
import com.event4u.eventsservice.grpc.actionGrpc;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;
import io.grpc.StatusRuntimeException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.logging.Level;
import java.util.logging.Logger;

@Service
public class LogActionService {
    @Autowired
    DiscoveryService discoveryService;
    private static final Logger logger = Logger.getLogger(LogActionService.class.getName());

    public void logAction(Long userId, Event4U.Request.ActionType actionType, String resName) {
        try {
            String url = discoveryService.getSystemEventsInstance();
            String p = "dns:///";
            //if (System.getProperty("os.name").toLowerCase().contains("windows")) p += "/";
            if ((url != null) && (url.length() > 0)) {
                url = p  + url.substring(7, url.indexOf(":",7)) + ":6565";
            }

            ManagedChannel channel = ManagedChannelBuilder.forTarget(url)
                    .usePlaintext()
                    .build();

            actionGrpc.actionBlockingStub stub
                    = actionGrpc.newBlockingStub(channel);
            Event4U.APIResponse response = stub.logAction(Event4U.Request.newBuilder()
                    .setServiceName("Events-service")
                    .setUserId(userId)
                    .setActionType(actionType)
                    .setResourceName(resName)
                    .build());
            channel.shutdown();
        }
        catch (StatusRuntimeException e) {
            logger.log(Level.WARNING, "RPC failed: {0}", e.getStatus());
            return;
        }
        catch(Exception e) {
            logger.log(Level.WARNING, "RPC failed: {0}", e.getMessage());
            return;
        }


    }
}
