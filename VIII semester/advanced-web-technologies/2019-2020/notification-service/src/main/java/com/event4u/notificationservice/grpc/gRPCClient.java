package com.event4u.notificationservice.grpc;

import com.event4u.notificationservice.ServiceInstanceRestController;
import io.grpc.Channel;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;
import io.grpc.StatusRuntimeException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

import java.util.List;
import org.springframework.stereotype.Service;

import java.util.logging.Level;
import java.util.logging.Logger;

@Service
public class gRPCClient {
    private static final Logger logger = Logger.getLogger(gRPCClient.class.getName());

    @Autowired
    private ServiceInstanceRestController serviceInstanceRestController;




    public void createLog(String ServiceName, Long userId, Event4U.Request.ActionType actionType, String resourceName) {



        RestTemplate restTemplate = new RestTemplate();
        List<String> listOfUrls = serviceInstanceRestController.serviceInstancesByApplicationName("system-events-service");

        String url = listOfUrls.get(0);
        String fooResourceUrl = url;

        String p = "dns:///";
        //if (System.getProperty("os.name").toLowerCase().contains("windows")) p += "/";
        if ((url != null) && (url.length() > 0)) {
            url = p  + url.substring(7, url.indexOf(":",7)) + ":6565";
        }
        ManagedChannel channel = ManagedChannelBuilder.forTarget(url)

                .usePlaintext()
                .build();


        try {

            actionGrpc.actionBlockingStub stub
                    = actionGrpc.newBlockingStub(channel);
            Event4U.APIResponse response = stub.logAction(Event4U.Request.newBuilder()
                    .setServiceName(ServiceName)
                    .setUserId(userId)
                    .setActionType(actionType)
                    .setResourceName(resourceName)
                    .build());
            channel.shutdown();

        } catch (StatusRuntimeException e) {
            logger.log(Level.WARNING, "RPC failed: {0}", e.getStatus());
            return;
        }
    }


}
