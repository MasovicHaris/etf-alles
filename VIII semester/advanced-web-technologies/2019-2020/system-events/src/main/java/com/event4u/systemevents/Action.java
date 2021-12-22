package com.event4u.systemevents;

import com.event4u.systemevents.grpc.Event4U;
import org.springframework.stereotype.Component;

import javax.persistence.*;
import javax.validation.constraints.NotNull;

@Component
@Entity
@Table(name = "Action")
public class Action {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    @NotNull(message = "Timestamp cannot be null or empty")
    @Column(nullable=false)
    private String timestamp;
    @NotNull(message = "Service name cannot be null or empty")
    @Column(nullable=false)
    private String serviceName;
    @NotNull(message = "User id cannot be null or empty")
    @Column(nullable=false)
    private Long userId;
    @NotNull(message = "Action type cannot be null or empty")
    @Column(nullable=false)
    private Event4U.Request.ActionType actionType;
    @NotNull(message = "Resource name cannot be null or empty")
    @Column(nullable=false)
    private String resourceName;

    protected Action(){

    }

    public Action(String timestamp, String serviceName, Long userId, Event4U.Request.ActionType actionType, String resourceName) {
        this.timestamp = timestamp;
        this.serviceName = serviceName;
        this.userId = userId;
        this.actionType = actionType;
        this.resourceName = resourceName;
    }

    public Long getId() {
        return id;
    }

    public String getTimestamp() {
        return timestamp;
    }

    public void setTimestamp(String timestamp) {
        this.timestamp = timestamp;
    }

    public String getServiceName() {
        return serviceName;
    }

    public void setServiceName(String serviceName) {
        this.serviceName = serviceName;
    }

    public Long getUserId() {
        return userId;
    }

    public void setUserId(Long userId) {
        this.userId = userId;
    }

    public Event4U.Request.ActionType getActionType() {
        return actionType;
    }

    public void setActionType(Event4U.Request.ActionType actionType) {
        this.actionType = actionType;
    }

    public String getResourceName() {
        return resourceName;
    }

    public void setResourceName(String resourceName) {
        this.resourceName = resourceName;
    }
}
