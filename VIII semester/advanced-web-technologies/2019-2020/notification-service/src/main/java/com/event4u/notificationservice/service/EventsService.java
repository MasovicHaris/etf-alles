package com.event4u.notificationservice.service;

import com.event4u.notificationservice.exception.EventNotFoundException;
import com.event4u.notificationservice.grpc.Event4U;
import com.event4u.notificationservice.grpc.gRPCClient;
import com.event4u.notificationservice.model.Events;
import com.event4u.notificationservice.model.UserBody;
import com.event4u.notificationservice.repository.EventsRepository;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.xml.bind.DatatypeConverter;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@Service
public class EventsService {
    @Autowired
    private EventsRepository eventsRepository;
    @Autowired
    private gRPCClient ns;
    @Autowired
    private Sender sender;

    public List<Events> findAll() {
        Iterable<Events> allEvents = eventsRepository.findAll();
        ArrayList<Events> events = new ArrayList<Events>();
        allEvents.forEach(e -> events.add(e));
        return events;
    }

    public Optional<Events> findById(Long id) {
        return eventsRepository.findById(id);
    }

    public Long getUserIdFromToken(String token, String key) {


        String token1=token.replace("Bearer ","");
        String base64Key = DatatypeConverter.printBase64Binary(key.getBytes());
        byte[] secretBytes = DatatypeConverter.parseBase64Binary(base64Key);
        Claims claim = Jwts.parser().setSigningKey(secretBytes).parseClaimsJws(token1).getBody();
        ObjectMapper mapper = new ObjectMapper();

        UserBody u = mapper.convertValue(claim, UserBody.class);

        Long id1=u.getId();
        return id1;
    }
    public Events getEventById(String token, String key, Long id) {
        ns.createLog("Notification service", getUserIdFromToken(token,key), Event4U.Request.ActionType.GET, "Event");
        return eventsRepository.findById(id).orElseThrow(() -> new EventNotFoundException(id));
    }

    public Events createEvent(String token, String key, Long eventId){

        //sender.sendMessage(new NotificationBody(eventId, "name", LocalDate.now()));

        ns.createLog("Notification service", getUserIdFromToken(token,key), Event4U.Request.ActionType.CREATE, "Event");
        return eventsRepository.save(new Events(eventId));
    }

    public Events createEventNew(Long eventId, String name, LocalDate date) throws JsonProcessingException {
        //Iz tokena i key dobijamo usera kako bismo ga upisali u log


       // sender.sendMessage(new NotificationBody(eventId, "name", LocalDate.now()));
        Events e =new Events(eventId);
        e.setName(name);
        e.setDate(date);

        //GRPC poziv system-events
        //Long id1=getUserIdFromToken(token, key);
       // ns.createLog("Notification service", id1, Request.ActionType.CREATE, "Event");

        return eventsRepository.save(e);
    }
    public void deleteById(String token, String key, Long id) {

        //GRPC poziv system-events

        ns.createLog("Notification service", getUserIdFromToken(token,key), Event4U.Request.ActionType.DELETE, "Event");

        eventsRepository.deleteById(id);
    }
    public Events updateEvent(String token, String key, Long id, String name, LocalDate date) {
        Events e = eventsRepository.findById(id).map(event -> {
            event.setEventId(id);
            event.setName(name);
            event.setDate(date);
            //event.setDate(date);
            //
            ns.createLog("Notification service", getUserIdFromToken(token,key), Event4U.Request.ActionType.UPDATE, "Event");
            return eventsRepository.save(event);
        }).orElseThrow();
        return e;
    }
}
