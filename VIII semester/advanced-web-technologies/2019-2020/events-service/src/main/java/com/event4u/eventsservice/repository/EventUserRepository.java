package com.event4u.eventsservice.repository;

import com.event4u.eventsservice.model.EventUser;
import org.springframework.data.jpa.repository.JpaRepository;

public interface EventUserRepository extends JpaRepository<EventUser, Long> {
}
