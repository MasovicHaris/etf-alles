package com.event4u.notificationservice.model;

import com.fasterxml.jackson.annotation.JsonCreator;
import com.fasterxml.jackson.annotation.JsonProperty;


public class UserAll {

    String id;
    String username;
    String name;
    String surname;
    String password;
    String picture;
    String description;
    String dateOfRegistration;
    String createdAt;
    String updatedAt;

    public UserAll() {
        this("","" ,"" ,"" ,"","","","","","");
    }
    @JsonCreator
    public UserAll(@JsonProperty("id") String id, @JsonProperty("username") String username, @JsonProperty("name") String name,
                   @JsonProperty("surname") String surname, @JsonProperty("password")String password,
                   @JsonProperty("picture")String picture, @JsonProperty("description")String description, @JsonProperty("dateOfRegistration") String dateOfRegistration,
                   @JsonProperty("createdAt")String createdAt, @JsonProperty("updatedAt")String updatedAt) {
        this.id=id;
        this.name=name;
        this.surname=surname;
        this.username=username;
        this.password=password;
        this.picture=picture;
        this.description=description;
        this.dateOfRegistration=dateOfRegistration;
        this.createdAt=createdAt;
        this.updatedAt=updatedAt;
    }

    public String getName() {
        return name;
    }

    public String getDateOfRegistration() {
        return dateOfRegistration;
    }

    public void setDateOfRegistration(String dateOfRegistration) {
        this.dateOfRegistration = dateOfRegistration;
    }

    public String getUsername() {
        return username;
    }

    public String getSurname() {
        return surname;
    }

    public String getCreatedAt() {
        return createdAt;
    }

    public String getDescription() {
        return description;
    }

    public String getId() {
        return id;
    }

    public String getPassword() {
        return password;
    }

    public String getPicture() {
        return picture;
    }

    public String getUpdatedAt() {
        return updatedAt;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setCreatedAt(String createdAt) {
        this.createdAt = createdAt;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setId(String id) {
        this.id = id;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setPicture(String picture) {
        this.picture = picture;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public void setUpdatedAt(String updatedAt) {
        this.updatedAt = updatedAt;
    }

    public void setUsername(String username) {
        this.username = username;
    }
}
