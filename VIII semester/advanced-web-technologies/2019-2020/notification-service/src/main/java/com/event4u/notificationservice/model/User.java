/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.event4u.notificationservice.model;


import com.fasterxml.jackson.annotation.JsonBackReference;
import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.JsonManagedReference;

import javax.persistence.*;
import javax.validation.constraints.NotNull;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 *
 * @author DT User
 */
@Entity

@JsonIgnoreProperties({"events","subscribedTo", "subscriber"})
public class User {

    @Id
    @Column(name = "user_id")
    @NotNull(message = "Id cannot be null")
    private Long userId;

    @ManyToMany(cascade = CascadeType.ALL)
    private Set<User> subscriber = new HashSet<>();


    @JsonBackReference
    @ManyToMany(cascade = CascadeType.ALL,mappedBy = "subscriber")
    private Set<User> subscribedTo = new HashSet<>();

    @OneToMany (mappedBy = "user")
    private List<Notification> notifications;

    @ManyToMany(cascade = CascadeType.ALL)
    private Set<Events> events = new HashSet<>();

    protected User() {
    }

    public User(Long id) {
        this.userId=id;
    }

    @Override
    public String toString() {
        return String.format(
                "User[id=%d]",
                userId);
    }

    public Long getUserId() {
        return userId;
    }
    public void setUserId(Long userId) {
        this.userId=userId;
    }


    public Set<Events> getEvents() {
        return events;
    }

    public void setEvents(Set<Events> events) {
        this.events=events;
    }
    public Set<User> getSubscriber() {
        return subscriber;
    }
    public Set<User> getSubsribedTo() {
        return subscribedTo;
    }
}
