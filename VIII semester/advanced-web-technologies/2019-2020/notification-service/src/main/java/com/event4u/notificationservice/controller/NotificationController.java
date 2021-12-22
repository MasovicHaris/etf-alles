package com.event4u.notificationservice.controller;

import com.event4u.notificationservice.NotificationServiceApplication;
import com.event4u.notificationservice.ServiceInstanceRestController;
import com.event4u.notificationservice.model.*;
import com.event4u.notificationservice.service.EventsService;
import com.event4u.notificationservice.service.NotificationService;
import com.event4u.notificationservice.service.UserService;
import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import io.jsonwebtoken.*;
import net.minidev.json.JSONObject;
import org.apache.tomcat.util.http.parser.Authorization;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.messaging.converter.MappingJackson2MessageConverter;
import org.springframework.messaging.simp.stomp.StompSession;
import org.springframework.messaging.simp.stomp.StompSessionHandler;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.client.RestTemplate;
import org.springframework.web.socket.client.WebSocketClient;
import org.springframework.web.socket.client.standard.StandardWebSocketClient;
import org.springframework.web.socket.messaging.WebSocketStompClient;

import javax.xml.bind.DatatypeConverter;
import java.security.Key;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.concurrent.ExecutionException;

@RequestMapping(path="/notifications",produces = {MediaType.APPLICATION_JSON_VALUE})
@RestController
public class NotificationController {

    private static final Logger log =
            LoggerFactory.getLogger(NotificationServiceApplication.class);

    @Autowired
    private NotificationService notificationService;

    @Autowired
    private UserService userService;

    @Autowired
    private EventsService eventService;
    @Autowired
    private ServiceInstanceRestController serviceInstanceRestController;


    @Value("${jwt.secret}")
    private String key;

    @GetMapping("")
    public Object allNotifications(@RequestHeader("Authorization") String token) throws ExecutionException, InterruptedException {
        return notificationService.findAll(token,key);
    }
    //Vraca sve notifikacije za jednog korisnika
    @GetMapping("/getByUserId/{id}")
    public List<Notification> getNotificationsByUserId(@RequestHeader("Authorization") String token,@PathVariable Long id) {
        return notificationService.findByUserId(token, key,id);
    }

    //Vraca sve notifikacije za jednog korisnika koje su procitane
    @GetMapping("/getByUserIdRead/{id}")
    public List<Notification> getNotificationsByUserIdRead(@RequestHeader("Authorization") String token,@PathVariable Long id) {
        return notificationService.findByUserIdRead(token, key,id);
    }

    //Vraca sve notifikacije za jednog korisnika koje nisu procitane
    @GetMapping("/getByUserIdNotRead/{id}")
    public List<Notification> getNotificationsByUserIdNotRead(@RequestHeader("Authorization") String token,@PathVariable Long id) {
        return notificationService.findByUserIdNotRead(token, key,id);
    }

    //Vraca notifikaciju po id-u
    @GetMapping("/getById/{id}")
    public Notification getNotificationsById(@RequestHeader("Authorization") String token, @PathVariable Long id) {
        return notificationService.findById(token, key, id);
    }

    //Vraca sve notifikacije za jednog korisnika
    @GetMapping("/getByEventId/{id}")
    public List<Notification> getNotificationsByEventId(@RequestHeader("Authorization") String token,@PathVariable Long id) {
        return notificationService.findByEventId(token, key,id);
    }

    //Brisanje notifikacije po id-u
    @DeleteMapping("/{id}")
    public ResponseEntity<JSONObject> deleteNotification(@RequestHeader("Authorization") String token, @PathVariable Long id) {
        try {
            notificationService.deleteById(token, key, id);
            JSONObject Entity = new JSONObject();
            Entity.put("message","Successful deletion of the notification with id: "+id );
            return  new ResponseEntity<JSONObject>(
                    Entity,
                    HttpStatus.OK);
        }
        catch(Exception e) {
            JSONObject Entity2 = new JSONObject();
            Entity2.put("message",e.toString() );

            return  new ResponseEntity<JSONObject>(
                    Entity2,
                    HttpStatus.BAD_REQUEST);
        }

    }

    //Kreiranje nove notifikacije
    @PostMapping("")
    public Object newNotification(@RequestHeader("Authorization") String token, @RequestParam Long userId, @RequestParam Long eventId, @RequestParam String message, @RequestParam String date, @RequestParam boolean isRead) throws ParseException, ExecutionException, InterruptedException {

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("d/MM/yyyy");
        //convert String to LocalDate
        LocalDate dateL = LocalDate.parse(date, formatter);
        return notificationService.createNotification(token, key,userId, eventId, message, dateL, isRead,1);
    }

    //Kreiranje nove notifikacije sa body
    @PostMapping(path="/postNotification", produces = {MediaType.APPLICATION_JSON_VALUE})
    public Object postNewNotification(@RequestHeader("Authorization") String token, @RequestBody NotificationBody not) throws ExecutionException, InterruptedException, JsonProcessingException, org.apache.tomcat.util.json.ParseException {
       return notificationService.createNotificationNew(token, not, key,2);
    }


      //Brisanje svih notifikacija jednog korisnika
    @DeleteMapping("/deleteByUserId/{id}")
    public ResponseEntity<JSONObject> deleteNotificationByUser(@RequestHeader("Authorization") String token,@PathVariable Long id) {
        try {
            notificationService.deleteByUser(token, key, id);
            JSONObject Entity = new JSONObject();
            Entity.put("message","Successful deletion of the notification with user id: "+id );
            return  new ResponseEntity<JSONObject>(
                    Entity,
                    HttpStatus.OK);
        }
        catch(Exception e) {
            JSONObject Entity2 = new JSONObject();
            Entity2.put("message",e.toString() );

            return  new ResponseEntity<JSONObject>(
                    Entity2,
                    HttpStatus.BAD_REQUEST);
        }
    }

    //Update notification
    @PutMapping(path ="/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public Notification updateNotification(@RequestHeader("Authorization") String token, @RequestBody NotificationBody tijelo, @PathVariable Long id) {
        return notificationService.updateNotification(token, key,id,tijelo);
    }

    @PutMapping(path ="/setAsRead/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public Object updateNotificationRead(@RequestHeader("Authorization") String token, @PathVariable Long id) throws ExecutionException, InterruptedException {

        return notificationService.updateNotificationRead(token, key,id);
    }

    @PostMapping(path ="/createGoingTo/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public NotificationBody createGoingNotification(@RequestHeader("Authorization") String token, @PathVariable Long id) throws ExecutionException, InterruptedException, JsonProcessingException, org.apache.tomcat.util.json.ParseException {
        Events e = eventService.getEventById(token, key, id);
        NotificationBody not= new NotificationBody(id, e.getName(), e.getDate());
        Notification n = notificationService.createNotificationNew(token, not, key, 2);
        return not;
    }

}
