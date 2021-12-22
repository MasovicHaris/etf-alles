package com.event4u.eventsservice.exceptionHandling;

public class TokenException extends RuntimeException {
    public TokenException() {
        super("Token invalid!");
    }
}
