package com.event4u.eventsservice.repository;

import com.event4u.eventsservice.model.User;
import org.springframework.data.repository.CrudRepository;

public interface UserRepository extends CrudRepository<User, Long> {
}
