package com.event4u.notificationservice;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cloud.client.discovery.DiscoveryClient;
import org.springframework.stereotype.Service;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import java.util.ArrayList;
import java.util.List;

@Service
@RestController
public
class ServiceInstanceRestController {

    @Autowired
    private DiscoveryClient discoveryClient;

    @RequestMapping("/service/{applicationName}")
    public List<String> serviceInstancesByApplicationName(
            @PathVariable String applicationName) {

        List<String> services = new ArrayList<String>();
        discoveryClient.getInstances(applicationName).forEach(instance ->
        {
            services.add(String.format("%s", instance.getUri()));
        });
        return services;
    }

    @RequestMapping(value = "/services", method = RequestMethod.GET)
    public List<String> getRegisteredServices()
    {
        List<String> services = new ArrayList<String>();
        discoveryClient.getServices().forEach(serviceName ->
        {
            discoveryClient.getInstances(serviceName).forEach(instance ->
            {
                services.add(String.format("%s:%s", serviceName, instance.getUri()));
            });
        });
        return services;
    }
}