package com.event4u.eventsservice.controller;

import com.event4u.eventsservice.grpc.Event4U;
import com.event4u.eventsservice.model.SuccessMessage;
import com.event4u.eventsservice.model.User;
import com.event4u.eventsservice.repository.UserRepository;
import com.event4u.eventsservice.service.LogActionService;
import com.event4u.eventsservice.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDate;
import java.util.ArrayList;

@RequestMapping("events-micro/users")
@RestController
public class UserController {
    @Autowired
    private UserService userService;
    @Autowired
    private LogActionService logActionService;

    @GetMapping(path ="", produces = {MediaType.APPLICATION_JSON_VALUE})
    public ArrayList<User> getAllUsers() {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.GET,"User");
        return userService.getAllUsers();
    }

    @GetMapping(path = "/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public User getUserById(@PathVariable Long id){
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.GET,"User");
        return userService.getUserById(id);
    }

    @GetMapping(path = "/count", produces = {MediaType.APPLICATION_JSON_VALUE})
    public Long count() {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.GET,"User");
        return userService.count();
    }

    @PostMapping(path ="/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public User newUser(@PathVariable Long id) {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.CREATE,"User");
        return userService.createUser(id);
    }

    @DeleteMapping(path ="/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public SuccessMessage deleteUser(@PathVariable Long id) {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.DELETE,"User");
        userService.deleteUser(id);
        return new SuccessMessage("User with id " + id + " successfully deleted");
    }
}
