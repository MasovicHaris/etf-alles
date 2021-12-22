package com.event4u.notificationservice.controller;

import com.event4u.notificationservice.model.Events;
import com.event4u.notificationservice.model.Notification;
import com.event4u.notificationservice.model.NotificationBody;
import com.event4u.notificationservice.service.EventsService;
import com.event4u.notificationservice.service.NotificationService;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.netflix.discovery.DiscoveryClient;
import net.minidev.json.JSONObject;
import org.apache.tomcat.util.json.ParseException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.concurrent.ExecutionException;

@RequestMapping(path="events",produces = {MediaType.APPLICATION_JSON_VALUE})
@RestController
public class EventController {

    @Autowired
    private EventsService eventService;
    @Autowired
    private NotificationService notificationService;
    @Value("${jwt.secret}")
    private String key;
    //Vraca event po id-u
    @GetMapping(path="/getById/{id}",produces = {MediaType.APPLICATION_JSON_VALUE})
    public Events getEventById(@RequestHeader("Authorization") String token, @PathVariable Long id){
        Events e = eventService.getEventById(token, key, id);
        return eventService.getEventById(token, key,id);
    }

    @GetMapping(path="",produces = {MediaType.APPLICATION_JSON_VALUE})
    public Object allEvents() {
        return eventService.findAll();
    }

    //Dodavanje event-a
    @PostMapping(path="",produces = {MediaType.APPLICATION_JSON_VALUE})
    public Events newEvent(@RequestHeader("Authorization") String token,@RequestBody String eventId) {
        return eventService.createEvent(token, key, Long.parseLong(eventId));
    }
    //Brisanje evnta

    @DeleteMapping("/{id}")
    public ResponseEntity<JSONObject> deleteEvents(@RequestHeader("Authorization") String token, @PathVariable Long id) {
        try {
            eventService.deleteById(token, key, id);
            JSONObject Entity = new JSONObject();
            Entity.put("message","Successful deletion of the event with id: "+id );
            return  new ResponseEntity<JSONObject>(
                    Entity,
                    HttpStatus.OK);
        }
        catch(Exception e) {
            JSONObject Entity2 = new JSONObject();
            Entity2.put("message","Error deleting event with id: "+id );

            return  new ResponseEntity<JSONObject>(
                    Entity2,
                    HttpStatus.BAD_REQUEST);
        }

    }
    //Dodavanje event-a
    @PostMapping(path="createEvent",produces = {MediaType.APPLICATION_JSON_VALUE})
    public NotificationBody newEventCreate (@RequestHeader("Authorization") String token, @RequestBody NotificationBody event) throws JsonProcessingException, ExecutionException, InterruptedException, ParseException {
        Events e = eventService.createEventNew(event.getEventId(), event.getName(), event.getDate());
        //Kreiraj notifikaciju odmah
        Notification n = notificationService.createNotificationNew(token, event, key, 2);
        return event;
    }

    @PutMapping(path ="/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public Events updateEvent(@RequestHeader("Authorization") String token, @RequestBody NotificationBody tijelo, @PathVariable Long id) {
        //update notifikacija sa tim eventom
        Iterable<Notification> all=notificationService.findAllByEvent(token, key, id);
        ArrayList<Notification> notifications = new ArrayList<Notification>();
        all.forEach(e -> {
            notificationService.updateNotification(token, key, e.getNotificationId(), tijelo);
        });
        return eventService.updateEvent(token, key,id, tijelo.getName(), tijelo.getDate());
    }
}
