package com.event4u.eventsservice.controller;

import com.event4u.eventsservice.grpc.Event4U;
import com.event4u.eventsservice.model.*;
import com.event4u.eventsservice.service.EventService;
import com.event4u.eventsservice.service.LogActionService;
import com.event4u.eventsservice.service.TokenHelperService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;

import java.util.List;


@RequestMapping("events-micro/events")
@RestController
public class EventController {
    @Autowired
    private EventService eventService;
    @Autowired
    private LogActionService logActionService;
    @Autowired
    private TokenHelperService tokenHelperService;

    @GetMapping(path ="", produces = {MediaType.APPLICATION_JSON_VALUE})
    public List<Event> allEvents() {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.GET,"Event");
        return eventService.findAll();
    }

    @GetMapping(path ="/category/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public List<Event> getEventsFromCategory(@PathVariable Long id) {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.GET,"Event");
        return eventService.findByCategoryId(id);
    }

    @GetMapping(path ="/my-events", produces = {MediaType.APPLICATION_JSON_VALUE})
    public List<Event> getEventsByCreator(@RequestHeader("Authorization") String token) {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.GET,"Event");
        return eventService.findByCreator(token);
    }

    @GetMapping(path ="/category-user/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public List<EventMark> getEventsFromCategoryForUser(@RequestHeader("Authorization") String token, @PathVariable Long id) {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.GET,"Event");
        return eventService.findByCategoryId(id,token);
    }

    @GetMapping(path = "/count", produces = {MediaType.APPLICATION_JSON_VALUE})
    public Long count() {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.GET,"Event");
        return eventService.count();
    }

    @GetMapping(path ="/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public Event getEventById(@PathVariable Long id) {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.GET,"Event");
        return eventService.findById(id);
    }

    @GetMapping(path ="/user/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public EventMark getEventForUser(@RequestHeader("Authorization") String token, @PathVariable Long id) {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.GET,"Event");
        return eventService.findById(id,token);
    }

    @GetMapping(path ="/creator/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public List<Event> getEventsByAnyCreator(@PathVariable Long id) {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.GET,"Event");
        return eventService.findByAnyCreator(id);
    }

    @PostMapping(path = "", produces = {MediaType.APPLICATION_JSON_VALUE})
    public Event newEvent(@RequestHeader("Authorization") String token, @RequestBody NewEvent event) {
        logActionService.logAction(tokenHelperService.getUserIdFromToken(token), Event4U.Request.ActionType.CREATE,"Event");
        return eventService.createEvent(event.getTitle(), event.getAddress(), event.getDate() ,event.getDescription() ,event.getIdCategory(), event.getIdLocation(), token, event.getImageUrl(), event.getTimeFrom(), event.getTimeTo(), event.getEndDate());
    }

    @PostMapping(path="/setTime/{id}",produces = {MediaType.APPLICATION_JSON_VALUE})
    public Event setTime(@PathVariable Long id, @RequestHeader("Authorization") String token, @RequestBody EventTime time) {
        return eventService.addTime(id, token, time);
    }

    @DeleteMapping(path = "/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public List<Event> deleteEvent(@RequestHeader("Authorization") String token, @PathVariable String id) {
        logActionService.logAction(tokenHelperService.getUserIdFromToken(token), Event4U.Request.ActionType.DELETE,"Event");
        Long eventId = Long.parseLong(id);
        return eventService.deleteById(eventId, token);
    }

    @PutMapping(path = "/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public Event updateEvent(@RequestHeader("Authorization") String token, @RequestBody NewEvent event, @PathVariable Long id) {
        logActionService.logAction(tokenHelperService.getUserIdFromToken(token), Event4U.Request.ActionType.UPDATE,"Event");
        return eventService.updateEvent(id, event.getTitle(),event.getAddress(), event.getDate(), event.getDescription(), event.getActive(), event.getIdCategory(), event.getIdLocation(), token, event.getImageUrl(), event.getTimeFrom(), event.getTimeTo());
    }


}
