package com.event4u.eventsservice.service;

import com.event4u.eventsservice.exceptionHandling.AlreadyExistsException;
import com.event4u.eventsservice.exceptionHandling.NotFoundException;
import com.event4u.eventsservice.model.Event;
import com.event4u.eventsservice.model.User;
import com.event4u.eventsservice.repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.Optional;

@Service
public class UserService {
    @Autowired
    private UserRepository userRepository;

    public User getUserById(Long id) {
        Optional<User> u = userRepository.findById(id);
        if (!u.isPresent()) {
            throw new NotFoundException("User with id " + id.toString());
        }
        return u.get();
    }

    public ArrayList<User> getAllUsers() {
        var it = userRepository.findAll();
        var users = new ArrayList<User>();
        it.forEach(e -> users.add(e));
        return users;
    }

    public User createUser(Long id) {
        if (userRepository.existsById(id)) {
            throw new AlreadyExistsException("User with id " + id.toString());
        }
        return userRepository.save(new User(id));
    }

    public void deleteUser(Long id) {
        if(!userRepository.existsById(id)) {
            throw new NotFoundException("User with id " + id.toString());
        }
        userRepository.deleteById(id);
    }

    public Long count() {
        return userRepository.count();
    }

    public Boolean existsById(Long id) {
        return userRepository.existsById(id);
    }
}
