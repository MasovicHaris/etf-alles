package com.event4u.eventsservice.model;

import java.sql.Time;

public class EventTime {
    private Long beginTime;
    private Long endTime;

    protected EventTime() {};

    public EventTime(Long beginTime, Long endTime) {
        this.beginTime = beginTime;
        this.endTime = endTime;
    }

    public Long getBeginTime() {
        return beginTime;
    }

    public Long getEndTime() {
        return endTime;
    }

    public void setBeginTime(Long beginTime) {
        this.beginTime = beginTime;
    }

    public void setEndTime(Long endTime) {
        this.endTime = endTime;
    }
}
