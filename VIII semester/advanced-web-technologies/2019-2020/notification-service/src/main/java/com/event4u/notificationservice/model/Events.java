package com.event4u.notificationservice.model;

import javax.validation.constraints.*;
import javax.persistence.*;

import javax.persistence.ManyToMany;
import java.time.LocalDate;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

@Entity
public class Events {

    @Id
    @NotNull(message = "Event id cannot be null")
    private Long eventId;

    @OneToMany(cascade = CascadeType.ALL, mappedBy = "event")
    private List<Notification> notifications;


    @ManyToMany(cascade = CascadeType.ALL, mappedBy = "events")
    private Set<User> users = new HashSet<>();

    private String name;
    private LocalDate date;

    protected Events() {
    }
    public Events(Long id) {
        this.eventId=id;
    }
    public Events(Long id, String name, LocalDate date) {
        this.eventId=id;
        this.name=name;
        this.date=date;
    }

    @Override
    public String toString() {
        return String.format(
                "Event[id=%d]",
                eventId);
    }

    public Long getEventId() {
        return eventId;
    }
    public void setEventId(Long eventId) {
        this.eventId=eventId;
    }

    public Set<User> getUsers() {
        return users;
    }

    public void setUsers(Set<User> users) {
        this.users = users;
    }

    public String getName() {
        return name;
    }

    public LocalDate getDate() {
        return date;
    }

    public void setDate(LocalDate date) {
        this.date = date;
    }

    public void setName(String name) {
        this.name = name;
    }

    public List<Notification> getNotifications() {
        return notifications;
    }

    public void setNotifications(List<Notification> notifications) {
        this.notifications = notifications;
    }
}
