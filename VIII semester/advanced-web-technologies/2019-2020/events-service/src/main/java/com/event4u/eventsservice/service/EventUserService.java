package com.event4u.eventsservice.service;

import com.event4u.eventsservice.exceptionHandling.NotFoundException;
import com.event4u.eventsservice.model.Event;
import com.event4u.eventsservice.model.EventMark;
import com.event4u.eventsservice.model.EventUser;
import com.event4u.eventsservice.model.User;
import com.event4u.eventsservice.repository.EventRepository;
import com.event4u.eventsservice.repository.EventUserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class EventUserService {
    @Autowired
    private EventUserRepository eventUserRepository;
    @Autowired
    private EventService eventService;
    @Autowired
    private UserService userService;
    @Autowired
    private TokenHelperService tokenHelperService;
    @Autowired
    private  NotificationHelperService notificationHelperService;
    @Autowired
    private EventRepository eventRepository;

    private List<EventUser> getAllUsers(Long idEvent){
        var it = eventUserRepository.findAll();
        var users = new ArrayList<EventUser>();
        it.forEach(eventUser -> {
            if (eventUser.getEvent().getId().equals(idEvent)) {
                users.add(eventUser);
            }
        });
        return users;
    }

    public List<User> getUsersGoing(Long idEvent) {
        if (!eventService.existsById(idEvent)) {
            throw new NotFoundException("Event with id " + idEvent.toString());
        }
        List<EventUser> allEventUsers = getAllUsers(idEvent);
        allEventUsers.removeIf(user -> user.getGoing()!=Boolean.TRUE);
        ArrayList<User> users = new ArrayList<>();
        allEventUsers.forEach(eventUser -> users.add(eventUser.getUser()));
        return users;
    }

    public List<User> getUsersInterested(Long idEvent) {
        if (!eventService.existsById(idEvent)) {
            throw new NotFoundException("Event with id " + idEvent.toString());
        }
        List<EventUser> allEventUsers = getAllUsers(idEvent);
        allEventUsers.removeIf(eu -> eu.getGoing()==Boolean.TRUE);
        ArrayList<User> users = new ArrayList<>();
        allEventUsers.forEach(eventUser -> users.add(eventUser.getUser()));
        return users;
    }

    public List<Event> getEventsGoing(String token) {
        Long idUser = tokenHelperService.getUserIdFromToken(token);
        if (!userService.existsById(idUser)) {
            throw new NotFoundException("User with id " + idUser.toString());
        }
        List<EventUser> allEventUsers = findAllEvents(idUser);
        allEventUsers.removeIf(eu -> eu.getGoing()==Boolean.FALSE);
        ArrayList<Event> events = new ArrayList<>();
        allEventUsers.forEach(eventUser -> events.add(eventUser.getEvent()));
        return events;
    }

    public List<Event> getEventsInterested(String token) {
        Long idUser = tokenHelperService.getUserIdFromToken(token);
        if (!userService.existsById(idUser)) {
            throw new NotFoundException("User with id " + idUser.toString());
        }
        List<EventUser> allEventUsers = findAllEvents(idUser);
        allEventUsers.removeIf(eu -> eu.getGoing()==Boolean.TRUE);
        ArrayList<Event> events = new ArrayList<>();
        allEventUsers.forEach(eventUser -> events.add(eventUser.getEvent()));
        return events;
    }

    private List<EventUser> findAllEvents(Long idUser) {
        var it = eventUserRepository.findAll();
        var events = new ArrayList<EventUser>();
        it.forEach(eventUser -> {
            if (eventUser.getUser().getId().equals(idUser)) {
                events.add(eventUser);
            }
        });
        return events;
    }

    public int getNumberOfUsersGoing(Long idEvent) {
        if (!eventService.existsById(idEvent)) {
            throw new NotFoundException("Event with id " + idEvent.toString());
        }
        return getUsersGoing(idEvent).size();
    }

    public int getNumberOfUsersInterested(Long idEvent) {
        if (!eventService.existsById(idEvent)) {
            throw new NotFoundException("Event with id " + idEvent.toString());
        }
        return getUsersInterested(idEvent).size();
    }

    private void markNew(User user, Event event, Boolean isGoing) {
        eventUserRepository.save(new EventUser(user, event, isGoing));
    }

    public EventMark markAsGoing(Long idEvent, String token) {
        if (!eventService.existsById(idEvent)) {
            throw new NotFoundException("Event with id " + idEvent.toString());
        }
        Long idUser = tokenHelperService.getUserIdFromToken(token);
        EventUser eu = getEventUser(idUser, idEvent);
        Event event = eventService.findById(idEvent);
        User user = userService.getUserById(idUser);
        if (eu != null) {
            if (!eu.getGoing()) {
                event.removeInterested();
                event.addGoing();
            }
           eu.setGoing(Boolean.TRUE);
           eventUserRepository.save(eu);
        }
        else {
            markNew(user, event, Boolean.TRUE);
            event.addGoing();
        }
        eventRepository.save(event);
       // notificationHelperService.createGoingToNotificaion(idEvent, token);
        return new EventMark(event, true, true);
    }

    public EventMark markAsInterested(Long idEvent, String token) {
        if (!eventService.existsById(idEvent)) {
            throw new NotFoundException("Event with id " + idEvent.toString());
        }
        Long idUser = tokenHelperService.getUserIdFromToken(token);
        EventUser eu = getEventUser(idUser, idEvent);
        Event event = eventService.findById(idEvent);
        User user = userService.getUserById(idUser);
        if (eu != null) {
            if (eu.getGoing()) {
                event.removeGoing();
                event.addInterested();
            }
            eu.setGoing(Boolean.FALSE);
            eventUserRepository.save(eu);
        }
        else {
            markNew(user, event, Boolean.FALSE);
            event.addInterested();
        };
        eventRepository.save(event);
        return new EventMark(event, true, false);
    }

    public EventMark removeMark(Long idEvent, String token) {
        if (!eventService.existsById(idEvent)) {
            throw new NotFoundException("Event with id " + idEvent.toString());
        }
        Long idUser = tokenHelperService.getUserIdFromToken(token);
        List<EventUser> allEventUsers = getAllUsers(idEvent);
        Event event = eventService.findById(idEvent);
        for (EventUser eventUser : allEventUsers) {
            if (eventUser.getUser().getId().equals(idUser)) {
                if(eventUser.getGoing()) {
                    event.removeGoing();
                }
                else event.removeInterested();
                eventRepository.save(event);
                eventUserRepository.deleteById(eventUser.getId());
                break;
            }
        }
        return new EventMark(event, false, false);
    }

    public EventUser getEventUser(Long idUser, Long idEvent) {
        List<EventUser> allEventUsers = getAllUsers(idEvent);
        allEventUsers.removeIf(eventUser -> eventUser.getUser().getId()!=idUser);
        if (allEventUsers == null || allEventUsers.size()==0) {
            return null;
        }
        return allEventUsers.get(0);
    }

}
