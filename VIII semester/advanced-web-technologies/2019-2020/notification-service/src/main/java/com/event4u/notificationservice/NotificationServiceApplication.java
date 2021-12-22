package com.event4u.notificationservice;

import java.time.LocalDate;

import com.event4u.notificationservice.grpc.gRPCClient;
import com.event4u.notificationservice.model.Events;
import com.event4u.notificationservice.model.Notification;
import com.event4u.notificationservice.model.NotificationBody;
import com.event4u.notificationservice.model.User;
import com.event4u.notificationservice.repository.EventsRepository;
import com.event4u.notificationservice.repository.NotificationRepository;
import com.event4u.notificationservice.repository.UserRepository;
import com.event4u.notificationservice.service.Receiver;
import com.event4u.notificationservice.service.Sender;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.amqp.core.Binding;
import org.springframework.amqp.core.BindingBuilder;
import org.springframework.amqp.core.Queue;
import org.springframework.amqp.core.TopicExchange;
import org.springframework.amqp.rabbit.connection.ConnectionFactory;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.amqp.rabbit.listener.SimpleMessageListenerContainer;
import org.springframework.amqp.rabbit.listener.adapter.MessageListenerAdapter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.ApplicationRunner;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.loadbalancer.LoadBalanced;
import org.springframework.cloud.netflix.eureka.EnableEurekaClient;
import org.springframework.context.annotation.Bean;
import org.springframework.web.client.RestTemplate;

@EnableEurekaClient
@SpringBootApplication
public class NotificationServiceApplication {


    private static final Logger log = 
            LoggerFactory.getLogger(NotificationServiceApplication.class);

    public static void main(String[] args) throws InterruptedException {

        SpringApplication.run(NotificationServiceApplication.class, args);

    }

    @Bean
    Queue queue() {
        return new Queue("notifications-events", false);
    }
    @Bean
    Queue queue2() {
        return new Queue("events-notifications", false);
    }
    @Bean
    Queue queue3() {
        return new Queue("notifications-frontend", false);
    }

    @Bean
    TopicExchange exchange()
    {
        return new TopicExchange("message_queue_exchange");
    }

    @Bean
    Binding binding(Queue queue, TopicExchange exchange)
    {
        return BindingBuilder.bind(queue).to(exchange).with("events-notifications");
    }

    @Bean
    SimpleMessageListenerContainer container(ConnectionFactory connectionFactory,
                                             MessageListenerAdapter listenerAdapter) {
        SimpleMessageListenerContainer container = new SimpleMessageListenerContainer();
        container.setConnectionFactory(connectionFactory);
        container.setQueueNames("events-notifications");
        container.setMessageListener(listenerAdapter);
        return container;
    }


    @Bean
    MessageListenerAdapter listenerAdapter(Receiver receiver) {
        return new MessageListenerAdapter(receiver, "listen");
    }

    @Bean
    @LoadBalanced
    public RestTemplate getRestTemplate() {
        return new RestTemplate();
    }


    @Bean
    public CommandLineRunner demo(NotificationRepository repository, EventsRepository repository2, UserRepository repository3) {
        return (args) -> {



            // save a few customers
            repository.save(new Notification(repository3.save(new User(Long.valueOf(1))), repository2.save(new Events(Long.valueOf(1))), "{\"event\":\"Studentski pohodi - Bobovac\",\"date\":\"2020-03-01\",\"name\":\"ajla\"}", LocalDate.of(Integer.parseInt("2022"),Integer.parseInt("2"),Integer.parseInt("2")), false,2));
            repository.save(new Notification(repository3.save(new User(Long.valueOf(2))), repository2.save(new Events(Long.valueOf(1))),"{\"event\":\"Studentski pohodi - Bobovac\",\"date\":\"2020-03-01\",\"name\":\"ajla\"}",LocalDate.of(Integer.parseInt("2022"),Integer.parseInt("2"),Integer.parseInt("2")), false,2));
            repository.save(new Notification(repository3.save(new User(Long.valueOf(3))),repository2.save(new Events(Long.valueOf(1))),"{\"event\":\"Studentski pohodi - Bobovac\",\"date\":\"2010-03-01\",\"name\":\"ajla\"}", LocalDate.of(Integer.parseInt("2022"),Integer.parseInt("2"),Integer.parseInt("2")), false,2));

            log.info("Notifications found with findAll():");
            log.info("-------------------------------");

            for (Notification notification : repository.findAll()) {
                log.info(notification.toString());
            }
            log.info("");

            repository2.save(new Events(Long.valueOf(1)));
            repository2.save(new Events(Long.valueOf(2)));
            repository2.save(new Events(Long.valueOf(3)));
            repository2.save(new Events(Long.valueOf(7), "Studentski pohodi - Bobovac", LocalDate.of(2020, 9, 23)));
            repository2.save(new Events(Long.valueOf(8), "Studentski pohodi - Trebevic", LocalDate.of(2020, 9, 23)));

            log.info("Events found with findAll():");
            log.info("-------------------------------");

            for (Events event : repository2.findAll()) {
                log.info(event.toString());
            }
            log.info("");

            repository3.save(new User(Long.valueOf(12)));
            repository3.save(new User(Long.valueOf(23)));
            repository3.save(new User(Long.valueOf(123)));

            Events e1 = new Events(Long.valueOf(4));
            Events e2 = new Events(Long.valueOf(5));

            User u1 = new User(Long.valueOf(1));

            User u2 = new User(Long.valueOf(2));

            User u3 = new User(Long.valueOf(3));

            repository3.save(u1);
            repository3.save(u2);
            repository3.save(u3);


            log.info("Events found with findAll():");
            log.info("-------------------------------");

            for (User user : repository3.findAll()) {
                log.info(user.toString());
            }
            log.info("");
        };
    }


}