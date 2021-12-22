package com.event4u.eventsservice.model;

import com.event4u.eventsservice.EventsServiceApplication;

import javax.persistence.*;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.time.LocalDate;
import java.util.List;

@Entity
@Table(name = "Event")
public class Event {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    @NotNull(message = "Event title cannot be null or empty")
    @NotBlank(message = "Event title cannot be null or empty")
    @Column(nullable=false)
    private String title;
    @NotNull(message = "Event address cannot be null or empty")
    @NotBlank(message = "Event address cannot be null or empty")
    @Column(nullable=false)
    private String address;
   // @Past(message = "Event with date in the past cannot be created")
    @NotNull(message = "Event date cannot be null or empty")
    @Column(nullable=false)
    private LocalDate date;
    @Column
    private LocalDate endDate;
    @Column(columnDefinition = "LONGTEXT")
    private String description;
    @Column
    private String imageUrl;
    private Boolean isActive;
    //@NotNull(message = "Event must belong to a category")
    @ManyToOne //vise dogadjaja pripada istoj kategoriji
    private Category category;
    @NotNull(message = "Event must have a creator")
    @ManyToOne
    private User creator;
    //@NotNull(message = "Event must have a location")
    @ManyToOne
    private Location location;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "event")
    private List<EventUser> eu;
    private EventsServiceApplication.Status crateEventStatus;
    private String beginTime;
    private String endTime;
    private Integer numberOfGoing;
    private Integer numberOfInterested;

    protected Event() {}

    public Event(String title, String address, LocalDate date, String description, Boolean isActive, Category category, User creator, Location location, String imageUrl, String beginTime, String endTime, LocalDate endDate) {
        this.title = title;
        this.address = address;
        this.date = date;
        this.description = description;
        this.isActive = isActive;
        this.category = category;
        this.creator = creator;
        this.location = location;
        this.imageUrl = imageUrl;
        this.crateEventStatus = EventsServiceApplication.Status.CREATE_STARTED;
        this.beginTime = beginTime;
        this.endTime = endTime;
        this.numberOfGoing = 0;
        this.numberOfInterested = 0;
        this.endDate = endDate;
    }

    @Override
    public String toString() {
        return String.format(
                "Event[id=%d, title='%s', address='%s', description='%s']",
                id, title, address, description
        );
    }

    public Long getId() {
        return id;
    }

    public String getTitle() {
        return title;
    }

    public String getAddress() {
        return address;
    }

    public String getDescription() {
        return description;
    }

    public LocalDate getDate() {
        return date;
    }

    public Boolean getActive() {
        return isActive;
    }

    public User getCreator() {
        return creator;
    }

    public Category getCategory() {
        return category;
    }

    public void setActive(Boolean active) {
        isActive = active;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setDate(LocalDate date) {
        this.date = date;
    }

    public void setCategory(Category category) {
        this.category = category;
    }

    public Location getLocation() {
        return location;
    }

    public void setLocation(Location location) {
        this.location = location;
    }

    public EventsServiceApplication.Status getCrateEventStatus() {
        return crateEventStatus;
    }

    public void setCrateEventStatus(EventsServiceApplication.Status crateEventStatus) {
        this.crateEventStatus = crateEventStatus;
    }

    public String getBeginTime() {
        return beginTime;
    }

    public void setBeginTime(String beginTime) {
        this.beginTime = beginTime;
    }

    public String getEndTime() {
        return endTime;
    }

    public void setEndTime(String endTime) {
        this.endTime = endTime;
    }

    public String getImageUrl() {
        return imageUrl;
    }

    public void setImageUrl(String imageUrl) {
        this.imageUrl = imageUrl;
    }

    public Integer getNumberOfGoing() {
        return numberOfGoing;
    }

    public void addGoing() {
        this.numberOfGoing++;
    }

    public void removeGoing() {
        this.numberOfGoing--;
    }

    public Integer getNumberOfInterested() {
        return numberOfInterested;
    }

    public void addInterested() {
        this.numberOfInterested++;
    }

    public void removeInterested() {
        this.numberOfInterested--;
    }

    public LocalDate getEndDate() {
        return endDate;
    }

    public void setEndDate(LocalDate endDate) {
        this.endDate = endDate;
    }
}
