package com.event4u.notificationservice.exception;

import org.springframework.http.HttpStatus;

import java.util.Arrays;
import java.util.List;

public class ApiError {
    private HttpStatus status;
    private String message;
    private List<String> errors;

    public ApiError() {
        super();
    }

    public ApiError(HttpStatus status, String message, List<String> errors) {
        super();
        this.status = status;
        this.message = message;
        this.errors = errors;
    }

    public ApiError(HttpStatus status, String message, String error) {
        super();
        this.status = status;
        this.message = message;
        errors = Arrays.asList(error);
    }

    public HttpStatus getStatus() {
        return status;
    }

    public List<String> getErrors() {
        return errors;
    }

    public String getMessage() {
        return message;
    }
    public void setStatus(final HttpStatus status) {
        this.status = status;
    }
    public void setMessage(final String message) {
        this.message = message;
    }
    public void setErrors(final List<String> errors) {
        this.errors = errors;
    }

    public void setError(final String error) {
        errors = Arrays.asList(error);
    }
}
