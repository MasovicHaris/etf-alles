package com.event4u.notificationservice.model;

import java.time.LocalDate;

public class NotificationBody {

    private Long eventId;
    private String  name;
    private LocalDate date;
    private String token;

    protected NotificationBody() {

    }

    public NotificationBody(Long eventId, String name, LocalDate date) {
        this.name = name;
        this.eventId=eventId;
        this.date=date;
    }

    public NotificationBody(Long eventId, String name, LocalDate date, String token) {
        this.name = name;
        this.eventId=eventId;
        this.date=date;
        this.token=token;
    }

    public Long getEventId() {
        return eventId;
    }

    public String getName() {
        return name;
    }

    public LocalDate getDate() {
        return date;
    }

    public String getToken() {return token;}


}
