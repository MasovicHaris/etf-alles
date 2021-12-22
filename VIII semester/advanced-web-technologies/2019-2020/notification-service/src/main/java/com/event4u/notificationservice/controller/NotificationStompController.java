package com.event4u.notificationservice.controller;

import com.event4u.notificationservice.model.Notification;
import com.event4u.notificationservice.model.User;
import com.event4u.notificationservice.repository.NotificationRepository;
import com.event4u.notificationservice.service.NotificationService;
import com.event4u.notificationservice.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.stereotype.Controller;

import java.util.ArrayList;

@Controller
public class NotificationStompController {

    @Value("${jwt.secret}")
    private String key;

    @Autowired
    private NotificationService notificationService;
    @Autowired
    private NotificationRepository notificationRepository;
    @Autowired
    private UserService userService;

    @MessageMapping("/hello")
    @SendTo("/topic/notification")
    public ArrayList<Notification> send(String token) throws Exception {
        User user = userService.getUserById(token ,key,notificationService.getUserIdFromToken(token, key));
        return (ArrayList<Notification>) notificationRepository.findByUser(user);
    }
}
