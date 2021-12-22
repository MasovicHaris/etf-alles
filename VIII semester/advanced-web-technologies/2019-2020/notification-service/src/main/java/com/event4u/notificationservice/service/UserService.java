package com.event4u.notificationservice.service;

import com.event4u.notificationservice.NotificationServiceApplication;
import com.event4u.notificationservice.ServiceInstanceRestController;
import com.event4u.notificationservice.exception.UserNotFoundException;
import com.event4u.notificationservice.model.User;
import com.event4u.notificationservice.model.UserAll;
import com.event4u.notificationservice.model.UserBody;
import com.event4u.notificationservice.repository.EventsRepository;
import com.event4u.notificationservice.repository.UserRepository;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;
import net.minidev.json.JSONObject;
import org.apache.tomcat.util.json.JSONParser;
import org.apache.tomcat.util.json.ParseException;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpMethod;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.web.client.RestTemplate;

import javax.xml.bind.DatatypeConverter;
import java.util.*;
import java.util.concurrent.atomic.AtomicBoolean;

@Service
public class UserService {


    private static final Logger log =
            LoggerFactory.getLogger(NotificationServiceApplication.class);

    @Autowired
    private UserRepository userRepository;

    @Autowired
    private ServiceInstanceRestController serviceInstanceRestController;

    @Autowired
    private NotificationService notificationService;

    public Optional<User> findById(Long id) {
        return userRepository.findById(id);
    }

    public List<User> findAll(String token, String key) {
        notificationService.validateToken(token, key);
        Iterable<User> allUsers = userRepository.findAll();
        ArrayList<User> u = new ArrayList<User>();
        allUsers.forEach(e -> u.add(e));
        return u;
    }

    public boolean isThere(Long id) {
        Iterable<User> allUsers = userRepository.findAll();
        AtomicBoolean tu= new AtomicBoolean(false);
        ArrayList<User> u = new ArrayList<User>();
        allUsers.forEach(e -> {
            if (e.getUserId()==id) {
                tu.set(true);
            }
        });
        return tu.get();
    }

    public User getUserById(String token, String key,Long id) {

        notificationService.validateToken(token, key);
        return userRepository.findById(id).orElseThrow(() -> new UserNotFoundException(id));
    }

    public User createUser(String token, String key, Long userId){

        notificationService.validateToken(token, key);
        return userRepository.save(new User(userId));
    }

    public void addSubscriber(String token, String key, Long id1, Long id2) {


        //if (!isThere(id1)) createUser(token, key,id1);
        //if (!isThere(id2)) createUser(token, key,id2);

        User koSeSubscriba = userRepository.findById(id1).orElseThrow(() -> new UserNotFoundException(id1));
        User naKogaSeSubscriba = userRepository.findById(id2).orElseThrow(() -> new UserNotFoundException(id2));


        log.info("Subscribe se na: "+ naKogaSeSubscriba.getUserId().toString());
        log.info("Ko se subscribe: "+ koSeSubscriba.getUserId().toString());

        koSeSubscriba.getSubsribedTo().add(naKogaSeSubscriba);
        naKogaSeSubscriba.getSubscriber().add(koSeSubscriba);

        userRepository.save(koSeSubscriba);
        userRepository.save(naKogaSeSubscriba);
    }

    public Set<Long> getSubscribers(String token, String key, Long id1) {

        //if (!isThere(id1)) createUser(token, key,id1);

        User user1 = userRepository.findById(id1).orElseThrow(() -> new UserNotFoundException(id1));

        Set<Long> odg = new HashSet<>();
        try {
            Set<User> lista = user1.getSubscriber();

            lista.forEach(e -> {
                odg.add(e.getUserId());
            });
        }
        catch(Exception e) {

        }
        finally {

            return  odg;
        }
    }

    public void deleteById(String token, String key, Long id) {

        notificationService.validateToken(token, key);
        userRepository.deleteById(id);
    }

    public void deleteSubscriber(Long id1, Long id2) {
        User user1 = userRepository.findById(id1).orElseThrow(() -> new UserNotFoundException(id1));
        User user2 = userRepository.findById(id2).orElseThrow(() -> new UserNotFoundException(id2));

        System.out.println(user1.getSubscriber());
        user1.getSubscriber().remove(user2);
        System.out.println(user1.getSubscriber());
        userRepository.save(user1);

    }
    public User updateUser(Long id) {
        User e = userRepository.findById(id).map(us -> {
            us.setUserId(id);
            return userRepository.save(us);
        }).orElseThrow();
        return e;
    }

    public Object getAllSubscribers(String token, String key) throws JsonProcessingException, ParseException {

        String token1=token.replace("Bearer ","");
        String base64Key = DatatypeConverter.printBase64Binary(key.getBytes());
        byte[] secretBytes = DatatypeConverter.parseBase64Binary(base64Key);
        Claims claim = Jwts.parser().setSigningKey(secretBytes).parseClaimsJws(token1).getBody();
        ObjectMapper mapper = new ObjectMapper();

        UserBody u = mapper.convertValue(claim, UserBody.class);

        Long id1=u.getId();

        Set<Long> users=getSubscribers(token, key, id1);
        //Nadji adresu user managment servisa

        RestTemplate restTemplate = new RestTemplate();
        List<String> listOfUrls = serviceInstanceRestController.serviceInstancesByApplicationName("gateway-service");

        String url = listOfUrls.get(0);
        String fooResourceUrl = url;

        MultiValueMap<String, String> headers = new LinkedMultiValueMap<>();
        headers.add("Content-Type", "application/json");
        headers.add("Authorization", token);
        ResponseEntity<String> response = restTemplate.exchange(fooResourceUrl + "aggregator/api/users", HttpMethod.GET, new HttpEntity<Object>(headers), String.class);

        String odg = response.getBody();
        JSONParser parser = new JSONParser(odg);
        ArrayList<UserAll> json =(ArrayList<UserAll>)  parser.parse();


        ArrayList<UserAll> sviSubscriberi = new ArrayList<UserAll>();

        ObjectMapper MAPPER = new ObjectMapper();
        List<UserAll> ts = MAPPER.readValue(odg, MAPPER.getTypeFactory().constructCollectionType(ArrayList.class, UserAll.class));
        //UserAll ua = mapper.convertValue(json.get(0), UserAll.class);

        for (int i=0; i<json.size(); i++) {
            int finalI = i;

            users.forEach(e -> {
                if (e==Long.parseLong(ts.get(finalI).getId())) {
                    sviSubscriberi.add(ts.get(finalI));
                }
            });
        }

        return sviSubscriberi;
    }
    public String getValidToken() {
        RestTemplate restTemplate = new RestTemplate();
        List<String> listOfUrls = serviceInstanceRestController.serviceInstancesByApplicationName("user-management-service");
        String url = listOfUrls.get(0);
        String fooResourceUrl = url;

        MultiValueMap<String, String> headers = new LinkedMultiValueMap<>();
        headers.add("Content-Type", "application/json");
        try {
            JSONObject Entity1 = new JSONObject();
            Entity1.put("username", "testAjla");
            Entity1.put("name", "Ajla");
            Entity1.put("surname", "Panjeta");
            Entity1.put("password", "passwordnovi");
            ResponseEntity<String> response1 = restTemplate.exchange(fooResourceUrl + "/api/auth/signup", HttpMethod.POST, new HttpEntity<Object>(Entity1, headers), String.class);

        }
        catch (Exception e) {

        }
        finally {

        JSONObject Entity2 = new JSONObject();
        Entity2.put("username","testAjla");
        Entity2.put("password","passwordnovi");
        ResponseEntity<String> response = restTemplate.exchange(fooResourceUrl + "/api/auth/login", HttpMethod.POST, new HttpEntity<Object>(Entity2, headers), String.class);

        String odg = response.getBody();
        return odg;

        }
    }

}
