/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.event4u.notificationservice.repository;
import java.util.List;

import com.event4u.notificationservice.model.Notification;
import com.event4u.notificationservice.model.User;
import com.event4u.notificationservice.model.Events;
import org.springframework.data.repository.CrudRepository;
/**
 *
 * @author DT User
 */
public interface NotificationRepository extends 
        CrudRepository<Notification, Long> {

    List<Notification> findByUser(User user);
    List<Notification> findByEvent(Events event);
    Notification findByNotificationId(Long id);
    List<Notification> deleteByUser(User user);
    void deleteAllByUser(User user);
    void deleteById(Long id);
}
