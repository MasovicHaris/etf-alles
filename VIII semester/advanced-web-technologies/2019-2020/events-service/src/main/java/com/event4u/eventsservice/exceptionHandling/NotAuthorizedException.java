package com.event4u.eventsservice.exceptionHandling;

public class NotAuthorizedException extends RuntimeException {
    public NotAuthorizedException() {
        super("Not Authorized!");
    }
}
