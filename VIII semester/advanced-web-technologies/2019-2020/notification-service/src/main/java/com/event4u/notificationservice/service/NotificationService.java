package com.event4u.notificationservice.service;

import com.event4u.notificationservice.ServiceInstanceRestController;
import com.event4u.notificationservice.controller.MyStompSessionHandler;
import com.event4u.notificationservice.exception.NotificationNotFoundException;
import com.event4u.notificationservice.model.*;
import com.event4u.notificationservice.repository.NotificationRepository;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;
import org.apache.tomcat.util.json.JSONParser;
import org.apache.tomcat.util.json.ParseException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpMethod;
import org.springframework.http.ResponseEntity;
import org.springframework.messaging.converter.MappingJackson2MessageConverter;
import org.springframework.messaging.simp.stomp.StompFrameHandler;
import org.springframework.messaging.simp.stomp.StompHeaders;
import org.springframework.messaging.simp.stomp.StompSession;
import org.springframework.messaging.simp.stomp.StompSessionHandler;
import org.springframework.stereotype.Service;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.web.client.RestTemplate;
import org.springframework.web.socket.client.WebSocketClient;
import org.springframework.web.socket.client.standard.StandardWebSocketClient;
import org.springframework.web.socket.messaging.WebSocketStompClient;
import org.springframework.web.socket.sockjs.client.SockJsClient;
import org.springframework.web.socket.sockjs.client.Transport;
import org.springframework.web.socket.sockjs.client.WebSocketTransport;

import javax.xml.bind.DatatypeConverter;
import java.lang.reflect.Type;
import java.math.BigInteger;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Set;
import java.util.concurrent.ExecutionException;

@Service
public class NotificationService {
    @Autowired
    private NotificationRepository notificationRepository;
    @Autowired
    private UserService userService;
    @Autowired
    private EventsService eventsService;
    @Autowired
    private ServiceInstanceRestController serviceInstanceRestController;

    @Autowired
    private Sender sender;


    public void validateToken(String token, String key) {


        String token1=token.replace("Bearer ","");
        String base64Key = DatatypeConverter.printBase64Binary(key.getBytes());
        byte[] secretBytes = DatatypeConverter.parseBase64Binary(base64Key);

        Claims claim = Jwts.parser().setSigningKey(secretBytes).parseClaimsJws(token1).getBody();

    }
    public Long getUserIdFromToken(String token, String key) {


        String token1=token.replace("Bearer ","");
        String base64Key = DatatypeConverter.printBase64Binary(key.getBytes());
        byte[] secretBytes = DatatypeConverter.parseBase64Binary(base64Key);
        Claims claim = Jwts.parser().setSigningKey(secretBytes).parseClaimsJws(token1).getBody();
        ObjectMapper mapper = new ObjectMapper();

        UserBody u = mapper.convertValue(claim, UserBody.class);

        Long id1=u.getId();
        return id1;
    }

    public void sendToSubscribers(String token) throws ExecutionException, InterruptedException {

        WebSocketClient simpleWebSocketClient = new StandardWebSocketClient();
        List<Transport> transports = new ArrayList<>(1);
        transports.add(new WebSocketTransport(simpleWebSocketClient));
        SockJsClient sockJsClient = new SockJsClient(transports);
        WebSocketStompClient stompClient = new WebSocketStompClient(sockJsClient);
        stompClient.setMessageConverter(new MappingJackson2MessageConverter());

        List<String> listOfUrls = serviceInstanceRestController.serviceInstancesByApplicationName("notification-service");

        String url1 = listOfUrls.get(0);
        String url = url1+"/ws";

        StompSessionHandler sessionHandler = new MyStompSessionHandler();
        StompSession session = stompClient.connect(url, sessionHandler).get();

        session.subscribe("topic", new StompFrameHandler() {
            @Override
            public Type getPayloadType(StompHeaders headers) {
                return Notification.class;
            }

            @Override
            public void handleFrame(StompHeaders headers,Object payload) {
                System.err.println(payload.toString());
            }
        });
        session.send("/app/hello", token);
    }
    public Object findAll(String token, String key) throws ExecutionException, InterruptedException {

        Long id = getUserIdFromToken(token, key);
        if (!userService.isThere(id)) userService.createUser(token, key,id);
        User user = userService.getUserById(token ,key,getUserIdFromToken(token, key));
        return notificationRepository.findByUser(user);
    }

    public List<Notification> findByUserId(String token, String key, Long id) {

        //if (!userService.isThere(id)) userService.createUser(token, key,id);

        User user = userService.getUserById(token ,key,id);
        return notificationRepository.findByUser(user);
    }

    public Notification findById(String token, String key, Long id) {
        validateToken(token, key);
        return notificationRepository.findById(id).orElseThrow(() -> new NotificationNotFoundException(id));
    }

    public List<Notification> findByUserIdRead(String token, String key, Long id) {
        validateToken(token, key);
        User user = userService.getUserById(token, key,id);
        Iterable<Notification> all = notificationRepository.findByUser(user);
        ArrayList<Notification> notifications = new ArrayList<Notification>();
        all.forEach(e -> {
            if(e.getIsRead()==true)
                notifications.add(e);
        });
        return notifications;
    }
    public Iterable<Notification> findAllByEvent(String toke, String key,Long id) {
        Events event = eventsService.getEventById(toke, key,id);
        Iterable<Notification> all = notificationRepository.findByEvent(event);

        return all;
    }

    public List<Notification> findByUserIdNotRead(String token, String key,Long id) {

        User user = userService.getUserById(token ,key,id);
        Iterable<Notification> all = notificationRepository.findByUser(user);
        ArrayList<Notification> notifications = new ArrayList<Notification>();
        all.forEach(e -> {
            if(e.getIsRead()==false)
                notifications.add(e);
        });
        return notifications;
    }

    public void deleteById(String token , String key, Long id) {
        validateToken(token, key);
        notificationRepository.deleteById(id);
    }


    public Notification createNotification(String token, String key, Long userId, Long eventId, String message, LocalDate date, boolean isRead, int type) throws ExecutionException, InterruptedException {

        sendToSubscribers(token);

        User user = userService.getUserById(token, key,userId);
        Events event = eventsService.getEventById(token, key, eventId);
        return notificationRepository.save(new Notification(user,event,message,date,isRead, type));
    }

    public Notification createNotificationNew(String token, NotificationBody not, String key, int type) throws ExecutionException, InterruptedException, JsonProcessingException, ParseException {
        //parse token

        sendToSubscribers(token);
        token=token.replace("Bearer ","");
        String base64Key = DatatypeConverter.printBase64Binary(key.getBytes());
        byte[] secretBytes = DatatypeConverter.parseBase64Binary(base64Key);
        Claims claim = Jwts.parser().setSigningKey(secretBytes).parseClaimsJws(token).getBody();

        ObjectMapper mapper = new ObjectMapper();

        //Iz tokena dobijemo info o useru
        UserBody u = mapper.convertValue(claim, UserBody.class);
        //return claim;

        Long userid=u.getId();
        //Kreiranje poruke

        String message = "{\"event\": \""+not.getName() +"\" , \"date\": \""+not.getDate()+"\""+" , \"name\": \""+userid+"\"}";


        if (type==1) {


            RestTemplate restTemplate = new RestTemplate();

            List<String> listOfUrls = serviceInstanceRestController.serviceInstancesByApplicationName("notification-service");

            String url = listOfUrls.get(0);

            MultiValueMap<String, String> headers = new LinkedMultiValueMap<>();
            headers.add("Content-Type", "application/json");
            headers.add("Authorization", token);
            ResponseEntity<String> response = restTemplate.exchange(url+"users/subscribers/"+userid, HttpMethod.GET, new HttpEntity<Object>(headers), String.class);

            String odg = response.getBody();
            JSONParser parser = new JSONParser(odg);
            ArrayList<BigInteger> json =(ArrayList<BigInteger>)  parser.parse();

            System.out.println("Subscriberi su "+odg);
            String finalToken = token;
            json.forEach(e -> {
                try {
                    //Tip 3 je za subscribere
                    createNotification(finalToken, key, e.longValue(), not.getEventId(), message, not.getDate(), false, 3);

                } catch (ExecutionException ex) {
                    ex.printStackTrace();
                } catch (InterruptedException ex) {
                    ex.printStackTrace();
                }
            });

            //Tip 1 notif. je za kreiranje notifikacija za usera koji je kreirao event, o uspjesnom kreiranju
            return createNotification(token, key, userid, not.getEventId(), message, not.getDate(), false, type);
        }
        else //salji samo subscriberima
        {
            //Tip 2 notif. je za kreiranje notifikacija za going to evente
            return createNotification(token, key, userid, not.getEventId(), message, not.getDate(), false, type);
        }
    }

    public List<Notification> findByEventId(String token, String key, Long id) {
        Events event = eventsService.getEventById(token, key,id);
        return notificationRepository.findByEvent(event);
    }

    public void deleteByUser(String token, String key, Long userId) {

        User user = userService.getUserById(token, key, userId);
        List<Notification> lista = notificationRepository.findByUser(user);
        notificationRepository.deleteAll(lista);
    }
    public Notification updateNotification(String token, String key, Long id, NotificationBody tijelo) {
        Events e =eventsService.getEventById(token, key, tijelo.getEventId());
        LocalDate ld = tijelo.getDate();

        String message = "{\"event\": \""+tijelo.getName() +"\" , \"date\": \""+tijelo.getDate()+"\""+" , \"name\": \"\"}";

        Notification n = notificationRepository.findById(id).map(us -> {
            us.setEvent(e);
            us.setMessage(message);
            us.setDate(ld);
            return notificationRepository.save(us);
        }).orElseThrow();
        return n;
    }

    public Object updateNotificationRead(String token, String key, Long id) throws ExecutionException, InterruptedException {

        Notification n = notificationRepository.findById(id).map(us -> {
            us.setIsRead(true);
            return notificationRepository.save(us);
        }).orElseThrow();
        return findAll(token, key);
    }
}
