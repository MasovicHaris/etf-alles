package com.event4u.eventsservice.model;

public class SuccessMessage {
    String message;

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public SuccessMessage(String m) {
        this.message = m;
    }
}
