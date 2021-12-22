package com.event4u.eventsservice.model;

import java.time.LocalDate;

public class EventDes {
    private Long id;
    private String title;
    private String address;
    private LocalDate date;
    private String description;
    private Boolean isActive;

    public EventDes(Long id, String title, String address, LocalDate date, String description, Boolean isActive) {
        this.id = id;
        this.title = title;
        this.address = address;
        this.date = date;
        this.description = description;
        this.isActive = isActive;
    }


    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public LocalDate getDate() {
        return date;
    }

    public void setDate(LocalDate date) {
        this.date = date;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public Boolean getActive() {
        return isActive;
    }

    public void setActive(Boolean active) {
        isActive = active;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }
}
