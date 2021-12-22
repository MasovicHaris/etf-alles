package com.event4u.eventsservice.model;

import javax.persistence.*;
import javax.validation.constraints.NotNull;

@Entity
@Table(name = "EventUser")
public class EventUser {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    @NotNull(message = "User cannot be null or empty")
    @ManyToOne
    private User user;
    @NotNull(message = "Event cannot be null or empty")
    @ManyToOne
    private Event event;
    @NotNull(message = "isGoing must have a value")
    @Column(nullable=false)
    private Boolean isGoing;

    protected EventUser() {};

    public EventUser(User user, Event event, Boolean isGoing) {
        this.user = user;
        this.event = event;
        this.isGoing = isGoing;
    }

    public Long getId() {
        return id;
    }

    public User getUser() {
        return user;
    }

    public Event getEvent() {
        return event;
    }

    public Boolean getGoing() {
        return isGoing;
    }

    public void setGoing(Boolean going) {
        isGoing = going;
    }

    @Override
    public String toString() {
        return String.format(
                "User with id=%d is going to event with id=%d",
                user.getId(), event.getId()
        );
    }
}
