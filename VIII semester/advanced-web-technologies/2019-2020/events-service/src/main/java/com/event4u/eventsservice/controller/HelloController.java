package com.event4u.eventsservice.controller;

import com.event4u.eventsservice.service.EventUserService;
import com.event4u.eventsservice.service.LogActionService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.*;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;


@RestController
public class HelloController {

    @RequestMapping(path ="/", produces = {MediaType.APPLICATION_JSON_VALUE})
    public String index() {
        return "Greetings from Events microservice!";
    }


}