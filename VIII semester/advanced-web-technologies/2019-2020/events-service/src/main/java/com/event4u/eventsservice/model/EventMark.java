package com.event4u.eventsservice.model;

public class EventMark {
    private Event event;
    private Boolean isMarked;
    private Boolean isGoing;

    protected EventMark() {}

    public EventMark(Event event, Boolean isMarked, Boolean isGoing) {
        this.event = event;
        this.isMarked = isMarked;
        this.isGoing = isGoing;
    }

    public Event getEvent() {
        return event;
    }

    public void setEvent(Event event) {
        this.event = event;
    }

    public Boolean getMarked() {
        return isMarked;
    }

    public void setMarked(Boolean marked) {
        isMarked = marked;
    }

    public Boolean getGoing() {
        return isGoing;
    }

    public void setGoing(Boolean going) {
        isGoing = going;
    }
}
