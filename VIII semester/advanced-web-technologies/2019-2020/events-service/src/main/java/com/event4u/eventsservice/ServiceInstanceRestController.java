package com.event4u.eventsservice;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cloud.client.ServiceInstance;
import org.springframework.cloud.client.discovery.DiscoveryClient;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;


@RestController
public class ServiceInstanceRestController {

	@Autowired
	private DiscoveryClient discoveryClient;

	@RequestMapping(value = "/services/{name}", method = RequestMethod.GET)
	public String getRegisteredServicesByName(@PathVariable String name)
	{
		for (ServiceInstance instance : discoveryClient.getInstances(name)) {
			return String.format("%s", instance.getUri());
		}
		return "";
	}
}
