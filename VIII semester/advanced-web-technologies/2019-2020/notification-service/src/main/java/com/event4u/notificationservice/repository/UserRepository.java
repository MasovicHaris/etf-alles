/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.event4u.notificationservice.repository;

import com.event4u.notificationservice.model.User;
import org.springframework.data.repository.CrudRepository;
/**
 *
 * @author DT User
 */
public interface UserRepository extends
        CrudRepository<User, Long> {

    User findByUserId(Long id);
}
