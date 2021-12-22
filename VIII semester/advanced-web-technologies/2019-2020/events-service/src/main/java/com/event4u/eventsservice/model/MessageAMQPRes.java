package com.event4u.eventsservice.model;

import java.io.Serializable;

public class MessageAMQPRes implements Serializable {
    Long id;
    String ackMessage;
    String destination;

    protected MessageAMQPRes() {

    }

    public MessageAMQPRes(Long id, String ackMessage, String destination) {
        this.ackMessage = ackMessage;
        this.destination = destination;
        this.id = id;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getAckMessage() {
        return ackMessage;
    }

    public void setAckMessage(String ackMessage) {
        this.ackMessage = ackMessage;
    }

    public String getDestination() {
        return destination;
    }

    public void setDestination(String destination) {
        this.destination = destination;
    }
}
