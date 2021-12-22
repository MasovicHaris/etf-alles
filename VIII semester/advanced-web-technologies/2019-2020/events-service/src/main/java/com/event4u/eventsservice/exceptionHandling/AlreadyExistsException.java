package com.event4u.eventsservice.exceptionHandling;

public class AlreadyExistsException extends RuntimeException {
    public AlreadyExistsException(String m) {
        super(m + " already exists!");
    }
}
