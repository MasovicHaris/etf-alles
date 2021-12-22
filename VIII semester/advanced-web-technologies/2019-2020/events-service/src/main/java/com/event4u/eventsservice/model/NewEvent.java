package com.event4u.eventsservice.model;

import java.time.LocalDate;

public class NewEvent {
    private String title;
    private String address;
    private LocalDate date;
    private String description;
    private Long idCategory;
    private Long idLocation;
    private Boolean isActive;
    private String imageUrl;
    private String timeFrom;
    private String timeTo;
    private LocalDate endDate;

    public NewEvent(String title, String address, LocalDate date, String description, Long idCategory, Long idLocation, Boolean isActive, String imageUrl, String timeFrom, String timeTo, LocalDate endDate) {
        this.title = title;
        this.address = address;
        this.date = date;
        this.description = description;
        this.idCategory = idCategory;
        this.idLocation = idLocation;
        this.isActive = isActive;
        this.imageUrl = imageUrl;
        this.timeFrom = timeFrom;
        this.timeTo = timeTo;
        this.endDate = endDate;
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

    public Long getIdCategory() {
        return idCategory;
    }

    public void setIdCategory(Long idCategory) {
        this.idCategory = idCategory;
    }

    public Long getIdLocation() {
        return idLocation;
    }

    public void setIdLocation(Long idLocation) {
        this.idLocation = idLocation;
    }

    public Boolean getActive() {
        return isActive;
    }

    public void setActive(Boolean active) {
        isActive = active;
    }

    public String getImageUrl() {
        return imageUrl;
    }

    public void setImageUrl(String imageUrl) {
        this.imageUrl = imageUrl;
    }

    public String getTimeFrom() {
        return timeFrom;
    }

    public void setTimeFrom(String timeFrom) {
        this.timeFrom = timeFrom;
    }

    public String getTimeTo() {
        return timeTo;
    }

    public void setTimeTo(String timeTo) {
        this.timeTo = timeTo;
    }

    public LocalDate getEndDate() {
        return endDate;
    }

    public void setEndDate(LocalDate endDate) {
        this.endDate = endDate;
    }
}
