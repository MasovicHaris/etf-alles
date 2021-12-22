package com.event4u.eventsservice.model;

import java.io.Serializable;

public class MessageAMQPReq implements Serializable {
    String action;
    Long id;

    protected MessageAMQPReq() {

    }

    public MessageAMQPReq(String action, Long id) {
        this.action = action;
        this.id = id;
    }


    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getAction() {
        return action;
    }

    public void setAction(String action) {
        this.action = action;
    }
}
