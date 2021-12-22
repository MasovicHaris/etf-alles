package com.event4u.eventsservice.controller;

import com.event4u.eventsservice.model.Event;
import com.event4u.eventsservice.model.EventMark;
import com.event4u.eventsservice.model.SuccessMessage;
import com.event4u.eventsservice.model.User;
import com.event4u.eventsservice.service.EventUserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RequestMapping("events-micro")
@RestController
public class EventUserController {
    @Autowired
    private EventUserService eventUserService;

    @GetMapping(path = "/going/{idEvent}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public List<User> getUsersGoing(@PathVariable Long idEvent) {
        return eventUserService.getUsersGoing(idEvent);
    }

    @GetMapping(path = "/interested/{idEvent}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public List<User> getUsersInterested(@PathVariable Long idEvent) {
        return eventUserService.getUsersInterested(idEvent);
    }

    @GetMapping(path = "/my-events/going", produces = {MediaType.APPLICATION_JSON_VALUE})
    public List<Event> getEventsGoing(@RequestHeader("Authorization") String token) {
        return eventUserService.getEventsGoing(token);
    }

    @GetMapping(path = "/my-events/interested", produces = {MediaType.APPLICATION_JSON_VALUE})
    public List<Event> getEventsInterested(@RequestHeader("Authorization") String token) {
        return eventUserService.getEventsInterested(token);
    }

    @GetMapping(path = "/goingNum/{idEvent}", produces = {MediaType.APPLICATION_JSON_VALUE})
    int getNumberOfUsersGoing(@PathVariable Long idEvent) {
        return eventUserService.getNumberOfUsersGoing(idEvent);
    }

    @GetMapping(path = "/interestedNum/{idEvent}", produces = {MediaType.APPLICATION_JSON_VALUE})
    int getNumberOfUsersInterested(@PathVariable Long idEvent) {
        return eventUserService.getNumberOfUsersInterested(idEvent);
    }

    @PostMapping(path = "/interested/{idEvent}", produces = {MediaType.APPLICATION_JSON_VALUE})
    EventMark markEventInterested(@RequestHeader("Authorization") String token, @PathVariable Long idEvent) {
        return eventUserService.markAsInterested(idEvent, token);
    }

    @PostMapping(path = "/going/{idEvent}", produces = {MediaType.APPLICATION_JSON_VALUE})
    EventMark markEventGoing(@RequestHeader("Authorization") String token, @PathVariable Long idEvent) {
        return eventUserService.markAsGoing(idEvent, token);
    }

    @DeleteMapping(path = "/removeMark/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    EventMark deleteMark(@RequestHeader("Authorization") String token, @PathVariable Long id) {
        return eventUserService.removeMark(id, token);
    }
}
