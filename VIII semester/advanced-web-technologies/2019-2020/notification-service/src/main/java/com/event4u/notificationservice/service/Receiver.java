package com.event4u.notificationservice.service;

        import com.event4u.notificationservice.NotificationServiceApplication;
        import com.event4u.notificationservice.model.MessageAMQPResponse;
        import com.event4u.notificationservice.model.Notification;
        import com.event4u.notificationservice.model.NotificationBody;
        import com.event4u.notificationservice.service.UserService;
        import com.fasterxml.jackson.core.JsonProcessingException;
        import com.fasterxml.jackson.databind.ObjectMapper;
        import com.google.gson.Gson;
        import org.apache.tomcat.util.json.JSONParser;
        import org.json.JSONObject;
        import org.springframework.amqp.rabbit.annotation.RabbitListener;
        import org.springframework.amqp.rabbit.core.RabbitTemplate;
        import org.springframework.beans.factory.annotation.Autowired;
        import org.springframework.beans.factory.annotation.Value;
        import org.springframework.stereotype.Component;

        import java.time.LocalDate;

@Component
public class Receiver {

    @Autowired
    UserService userService;

    @Autowired
    private Sender sender;
    @Autowired
    EventsService eventsService;
    @Autowired
    NotificationService notificationService;

    @Value("${jwt.secret}")
    private String key;

    private Long eventID = null;

    //Receiver za upis eventa
    @RabbitListener(queues = "events-notifications")
    public void listen(String in) throws JsonProcessingException {
        try {
            JSONObject jsonObj = new JSONObject(in);
            String date=jsonObj.getString("date");
            String name=jsonObj.getString("name");
            eventID= jsonObj.getLong("eventId");
            LocalDate localDate1 = LocalDate.parse(date);
            String token =jsonObj.getString("token");

            eventsService.createEventNew(eventID, name, localDate1);
            Notification n = notificationService.createNotificationNew(token, new NotificationBody(eventID, name, localDate1), key, 1);
            MessageAMQPResponse mes=new MessageAMQPResponse(eventID, "OK", "EVENTS-SERVICE");
            String jsonString=new ObjectMapper().writeValueAsString(mes);

            sender.sendMessage(jsonString);
        }
        catch (Exception ex) {

            System.out.println(ex);
            MessageAMQPResponse mes=new MessageAMQPResponse(eventID, "ERROR", "EVENTS-SERVICE");
            String jsonString=new ObjectMapper().writeValueAsString(mes);
            sender.sendMessage(jsonString);
        }
    }
}
