package com.event4u.eventsservice.exceptionHandling;

public class InvalidParameterException extends RuntimeException {
    public InvalidParameterException(String m) {
        super(m);
    }
}
