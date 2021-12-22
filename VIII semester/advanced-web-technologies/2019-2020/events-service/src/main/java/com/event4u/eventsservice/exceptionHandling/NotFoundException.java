package com.event4u.eventsservice.exceptionHandling;

public class NotFoundException extends RuntimeException {
    public NotFoundException(String m) {
        super(m + " not found!");
    }
}
