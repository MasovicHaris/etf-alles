package com.event4u.eventsservice.service;

import com.event4u.eventsservice.Sender;
import com.event4u.eventsservice.model.Event;
import com.event4u.eventsservice.model.EventNotification;
import com.fasterxml.jackson.core.JsonProcessingException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.*;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

import java.util.Collections;


@Service
public class NotificationHelperService {
    @Autowired
    private DiscoveryService discoveryService;
    @Autowired
    private TokenHelperService tokenHelperService;
    @Autowired
    private Sender sender;

    private HttpHeaders getHeaders(String token) {
        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.APPLICATION_JSON);
        headers.setAccept(Collections.singletonList(MediaType.APPLICATION_JSON));
        headers.setBearerAuth(token.replace("Bearer ", ""));
        return headers;
    }

    public void deleteEventNotifications (Long eventId, String token) {
        RestTemplate restTemplate = new RestTemplate();
        String deleteEventUrl = discoveryService.getNotificationInstance() + "/events/" + eventId.toString();
        ResponseEntity<String> res = restTemplate.exchange(deleteEventUrl, HttpMethod.DELETE , new HttpEntity<>(getHeaders(token)), String.class);
    }

    public void createEventNotifications(Event e, String token) {
        try {
            sender.sendMessageNotifications(new EventNotification(e.getId(), e.getTitle(), e.getDate(), token));
        }
        catch (JsonProcessingException ex) {
            //TODO: throw error
        }
    }

    public void updateEventNotifications(Event e, String token) {
        RestTemplate restTemplate = new RestTemplate();
        String UpdateEventUrl = discoveryService.getNotificationInstance() + "/events/" + e.getId();
        HttpEntity<EventNotification> req = new HttpEntity<EventNotification>(new EventNotification(e.getId(), e.getTitle(), e.getDate(), token), getHeaders(token));
        ResponseEntity<String> res = restTemplate.exchange(UpdateEventUrl, HttpMethod.PUT , req, String.class); //TODO: fix this
    }

    public void createGoingToNotificaion(Long idEvent, String token) {
        RestTemplate restTemplate = new RestTemplate();
        String createNotificationUrl = discoveryService.getNotificationInstance() + "/notifications/createGoingTo/" + idEvent;
        ResponseEntity<String> res = restTemplate.exchange(createNotificationUrl, HttpMethod.POST , new HttpEntity<>(getHeaders(token)), String.class);
    }
}
