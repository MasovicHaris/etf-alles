package com.event4u.systemevents;

import com.event4u.systemevents.grpc.Event4U;
import com.event4u.systemevents.grpc.actionGrpc;
import io.grpc.stub.StreamObserver;
import org.lognet.springboot.grpc.GRpcService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.netflix.eureka.EnableEurekaClient;
import org.springframework.context.ConfigurableApplicationContext;

@SpringBootApplication
@EnableEurekaClient
public class SystemEventsApplication {

	@GRpcService
	public class SystemEventsService extends actionGrpc.actionImplBase{
		@Autowired
		private ActionService actionService;

		@Override
		public void logAction(Event4U.Request request, StreamObserver<Event4U.APIResponse> responseObserver) {

			try {
				System.out.println("Service name: " + request.getServiceName() + ", resource name: " + request.getResourceName());
				actionService.createAction(
						request.getServiceName(), request.getUserId(), request.getActionType(), request.getResourceName());
				Event4U.APIResponse.Builder response = Event4U.APIResponse.newBuilder();
				response.setResponseMessage("Action saved");
				response.setResponseType(Event4U.APIResponse.ResponseType.SUCCESS);
				responseObserver.onNext(response.build());
				responseObserver.onCompleted();
			}
			catch(Exception ex) {
				Event4U.APIResponse.Builder response = Event4U.APIResponse.newBuilder();
				response.setResponseMessage("Action NOT saved! Error: " + ex.getMessage());
				response.setResponseType(Event4U.APIResponse.ResponseType.ERROR);
				responseObserver.onNext(response.build());
				responseObserver.onCompleted();
			}
		}
	}

	private static ConfigurableApplicationContext applicationContext;

	public static void main(String[] args) {
		applicationContext = SpringApplication.run(SystemEventsApplication.class, args);
		System.out.println("Starting GRPC Server");
		//checkBeansPresence("actionService", "actionRepository", "action");
	}

	private static void checkBeansPresence(String... beans) {
		for (String beanName : beans) {
			System.out.println("Is " + beanName + " in ApplicationContext: " + applicationContext.containsBean(beanName));
		}
	}
}
