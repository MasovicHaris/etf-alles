package com.event4u.eventsservice.model;

import com.fasterxml.jackson.annotation.JsonCreator;

import java.io.Serializable;
import java.time.LocalDate;

public class EventNotification implements Serializable {
    private Long eventId;
    private String  name;
    private LocalDate date;
    private String token;

    public EventNotification() {

    }

    @JsonCreator
    public EventNotification(Long eventId, String name, LocalDate date, String token) {
        this.name = name;
        this.eventId=eventId;
        this.date=date;
        this.token = token;
    }

    public Long getEventId() {
        return eventId;
    }

    public void setEventId(Long eventId) {
        this.eventId = eventId;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public LocalDate getDate() {
        return date;
    }

    public void setDate(LocalDate date) {
        this.date = date;
    }

    public String getToken() {
        return token;
    }

    public void setToken(String token) {
        this.token = token;
    }
}
