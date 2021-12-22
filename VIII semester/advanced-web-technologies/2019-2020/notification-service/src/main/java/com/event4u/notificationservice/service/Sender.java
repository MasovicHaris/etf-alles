package com.event4u.notificationservice.service;

import com.event4u.notificationservice.model.MessageAMQPResponse;
import com.event4u.notificationservice.model.NotificationBody;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import org.springframework.stereotype.Service;

@Component
public class Sender {
    @Autowired
    private RabbitTemplate rabbitTemplate;

    public void sendMessage(String res) throws JsonProcessingException {
        rabbitTemplate.convertAndSend("notifications-events", res);
    }

    public void sendMessageFrontend(String res) throws JsonProcessingException {
        rabbitTemplate.convertAndSend("notifications-frontend", res);
    }


}

