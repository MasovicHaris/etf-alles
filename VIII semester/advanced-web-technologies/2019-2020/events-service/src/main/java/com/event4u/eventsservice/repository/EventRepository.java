package com.event4u.eventsservice.repository;

import com.event4u.eventsservice.model.Event;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface EventRepository extends CrudRepository<Event, Long>  {
}
