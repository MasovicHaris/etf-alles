package com.event4u.eventsservice.service;

import com.event4u.eventsservice.EventsServiceApplication;
import com.event4u.eventsservice.exceptionHandling.NotAuthorizedException;
import com.event4u.eventsservice.exceptionHandling.NotFoundException;
import com.event4u.eventsservice.model.*;
import com.event4u.eventsservice.repository.EventRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;


@Service
public class EventService {
    @Autowired
    private EventRepository eventRepository;
    @Autowired
    private CategoryService categoryService;
    @Autowired
    private LocationService locationService;
    @Autowired
    private UserService userService;
    @Autowired
    private NotificationHelperService notificationHelperService;
    @Autowired
    private DiscoveryService discoveryService;
    @Autowired
    private TokenHelperService tokenHelperService;
    @Autowired
    private EventUserService eventUserService;

    public List<Event> findAll() {
        var it = eventRepository.findAll();
        var events = new ArrayList<Event>();
        it.forEach(e -> events.add(e));
        return events;
    }

    public Boolean existsById(Long id) {
        return eventRepository.existsById(id);
    }

    public Event findById(Long id) {
        Optional<Event> e = eventRepository.findById(id);
        if (!e.isPresent()) {
            throw new NotFoundException("Event with id " + id.toString());
        }
        return e.get();
    }

    public EventMark findById(Long id, String token) {
        Event e = findById(id);
        Long idUser = tokenHelperService.getUserIdFromToken(token);
        EventUser eu = null;

        eu= eventUserService.getEventUser(idUser, e.getId());
        if (eu==null) {
            return new EventMark(e,false,false);
        }
        else {
            return new EventMark(e,true,eu.getGoing());
        }
    }

    public Long count() {
        return eventRepository.count();
    }

    public List<Event> deleteById(Long eventId, String token) {
        Optional<Event> e = eventRepository.findById(eventId);
        if (!e.isPresent()) {
            throw new NotFoundException("Event with id " + eventId.toString());
        }
        eventRepository.deleteById(eventId);
        notificationHelperService.deleteEventNotifications(eventId, token);
        return findByCreator(token);
    }

    public void deleteById(Long eventId) {
        eventRepository.deleteById(eventId);
    }

    public Event createEvent(String title, String address, LocalDate date, String description, Long idCategory, Long idLocation, String token, String imageUrl, String timeFrom, String timeTo, LocalDate endDate){
        Long idUser = tokenHelperService.getUserIdFromToken(token);
        Category category = categoryService.findById(idCategory);
        User crator = userService.getUserById(idUser);
        //Location location = locationService.findById(idLocation);
        Event e = new Event(title,address,date,description,Boolean.TRUE, category, crator, null, imageUrl, timeFrom, timeTo, endDate);
        eventRepository.save(e);
        notificationHelperService.createEventNotifications(e, token);
        return e;
    }

    public Event updateEvent(Long id, String title, String address, LocalDate date, String description, Boolean isActive, Long idCategory, Long idLocation, String token, String imageUrl, String timeFrom, String timeTo) {
        Long idUser = tokenHelperService.getUserIdFromToken(token);
        Optional<Event> e = eventRepository.findById(id).map(event -> {
            if (!idUser.equals(event.getCreator().getId())) {
                throw new NotAuthorizedException();
            }
            event.setActive(isActive);
            event.setAddress(address);
            event.setTitle(title);
            event.setDate(date);
            event.setDescription(description);
            event.setBeginTime(timeFrom);
            event.setEndTime(timeTo);
            if (event.getCategory().getId() != idCategory) {
                Category c = categoryService.findById(idCategory);
                event.setCategory(c);
            }
            event.setImageUrl(imageUrl);
           /* if (event.getLocation().getId() != idLocation) {
                Location l = locationService.findById(idLocation);
                event.setLocation(l);
            }*/
            return eventRepository.save(event);
        });
        Event event = e.get();
    //    notificationHelperService.updateEventNotifications(event, token);
        return event;
    }
    public List<Event> findByCategoryId(Long id) {
        List<Event> events = findAll();
        events.removeIf(e -> (e.getCategory().getId() != id || e.getDate().isBefore(LocalDate.now())));
        return events;
    }

    public List<EventMark> findByCategoryId(Long idCategory, String token) {
        Long idUser = tokenHelperService.getUserIdFromToken(token);
        List<Event> events = findAll();
        events.removeIf(e-> (e.getCategory().getId()!=idCategory));
        List<EventMark> eventsMarks = new ArrayList<>();
        EventUser eu = null;
        for (Event e: events) {
            eu= eventUserService.getEventUser(idUser, e.getId());
            if (eu==null) {
                eventsMarks.add(new EventMark(e,false,false));
            }
            else {
                eventsMarks.add(new EventMark(e,true,eu.getGoing()));
            }

        }
        return eventsMarks;
    }

    public void changeStatus(Long id, EventsServiceApplication.Status s) {
        Event e = findById(id);
        e.setCrateEventStatus(s);
        eventRepository.save(e);
    }

    public EventsServiceApplication.Status getStatus(Long id) {
        Event e = findById(id);
        return e.getCrateEventStatus();
    }

    public List<Event> findByCreator(String token) {
        Long idUser = tokenHelperService.getUserIdFromToken(token);
        List<Event> events = findAll();
        events.removeIf(e-> (!e.getCreator().getId().equals(idUser)));
        return events;
    }

    public List<Event> findByAnyCreator(Long id) {
        List<Event> events = findAll();
        events.removeIf(e-> (!e.getCreator().getId().equals(id)));
        return events;
    }

    public Event addTime(Long id, String token, EventTime time) {
        Long idUser = tokenHelperService.getUserIdFromToken(token);
        Event e = findById(id);
        if (e.getCreator().getId()!=idUser) throw new NotAuthorizedException();
        e.setBeginTime(time.getBeginTime().toString());
        e.setEndTime(time.getEndTime().toString());
        return eventRepository.save(e);
    }


}
