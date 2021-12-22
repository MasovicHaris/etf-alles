/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.event4u.notificationservice.repository;

import com.event4u.notificationservice.model.Events;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

/**
 *
 * @author DT User
 */

@RepositoryRestResource(collectionResourceRel = "events", path = "events")
public interface EventsRepository extends CrudRepository<Events, Long> {

    Events findByEventId(Long id);
}
