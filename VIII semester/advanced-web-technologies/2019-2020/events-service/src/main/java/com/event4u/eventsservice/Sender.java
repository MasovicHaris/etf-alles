package com.event4u.eventsservice;

import com.event4u.eventsservice.model.Event;
import com.event4u.eventsservice.model.EventNotification;
import com.event4u.eventsservice.model.MessageAMQPRes;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import com.fasterxml.jackson.datatype.jsr310.JavaTimeModule;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.time.format.DateTimeFormatter;
import java.util.Locale;

@Component
public class Sender {
    @Autowired
    private RabbitTemplate rabbitTemplate;

    public void sendMessageNotifications(EventNotification res) throws JsonProcessingException {
        ObjectMapper om = new ObjectMapper();
        om.registerModule(new JavaTimeModule());
        om.disable(SerializationFeature.WRITE_DATES_AS_TIMESTAMPS);
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("EEEE, MMM d, yyyy hh:mm:ss a", Locale.US);
        String jsonString=om.writeValueAsString(res);
        rabbitTemplate.convertAndSend("events-notifications", jsonString);
    }
}
