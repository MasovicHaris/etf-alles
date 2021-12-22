package com.event4u.eventsservice;

import com.event4u.eventsservice.helpers.EventIdDeserializer;
import com.event4u.eventsservice.model.Event;
import com.event4u.eventsservice.model.EventDes;
import com.event4u.eventsservice.model.EventNotification;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.module.SimpleModule;
import net.minidev.json.JSONObject;
import org.junit.Assert;
import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.web.client.TestRestTemplate;
import org.springframework.http.*;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.MvcResult;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.web.client.HttpClientErrorException;
import org.springframework.web.client.RestTemplate;

import java.util.Collections;

import static org.hamcrest.Matchers.is;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.jsonPath;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
@SpringBootTest
@AutoConfigureMockMvc
public class NotificationServiceTest {
    @Autowired
    private MockMvc mvc;
    private static String token;
    private static Long userId;


    private String getUserServiceUrl() throws Exception {
        // Get user service url
        String urlDiscoverUserService = "/services/user-management-service";
        MvcResult r = mvc.perform(MockMvcRequestBuilders.get(urlDiscoverUserService)).andReturn();
        return r.getResponse().getContentAsString();
    }

    public void loginUser() throws Exception {
        String baseUrl = getUserServiceUrl();
        login(baseUrl + "/api/auth/login");
    }

    private static void login(String loginUrl) {
        RestTemplate restTemplate = new RestTemplate();
        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.APPLICATION_JSON);
        JSONObject newUserJsonObject = new JSONObject();
        JSONObject userJsonObject = new JSONObject();
        userJsonObject.put("username", "dzenana"); //User inace u bazi user managment servisa
        userJsonObject.put("password", "password");
        HttpEntity<String> requestLogin = new HttpEntity<String>(userJsonObject.toString(), headers);
        String res = restTemplate.postForObject(loginUrl, requestLogin, String.class);
        ObjectMapper objectMapper = new ObjectMapper();
        JsonNode root;
        try {
            root = objectMapper.readTree(res);
            token = root.get("token").toString();
            token = token.replace("\"", "");
            userId = Long.valueOf(root.get("user").get("id").toString());
        } catch (JsonProcessingException e) {
            e.printStackTrace();
        }
    }

    private String getNotificatonServiceUrl() throws Exception {
        // Get user service url
        String urlDiscoverUserService = "/services/notification-service";
        MvcResult r = mvc.perform(MockMvcRequestBuilders.get(urlDiscoverUserService)).andReturn();
        return r.getResponse().getContentAsString();
    }

    private HttpHeaders getHeaders(String token) {
        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.APPLICATION_JSON);
        headers.setAccept(Collections.singletonList(MediaType.APPLICATION_JSON));
        headers.setBearerAuth(token.replace("Bearer ", ""));
        return headers;
    }

    public EventDes getEventFromRes(String res) {
        ObjectMapper m = new ObjectMapper();
        SimpleModule module = new SimpleModule();
        module.addDeserializer(EventDes.class, new EventIdDeserializer());
        m.registerModule(module);
        try {
            return m.readValue(res, EventDes.class);
        }
        catch (JsonProcessingException e) {
            e.printStackTrace();
        }
        return null;
    }

    private EventDes getEvent() throws Exception {
        MvcResult res = mvc.perform(MockMvcRequestBuilders.get("/events-micro/events/7")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$.id", is(7)))
                .andExpect(jsonPath("$.address", is("Zmaja od Bosne bb")))
                .andExpect(jsonPath("$.date", is("2020-03-23")))
                .andExpect(jsonPath("$.description", is("Laboratorijske vježbe iz predmeta NWT")))
                .andExpect(jsonPath("$.category.id", is(1)))
                .andExpect(jsonPath("$.creator.id", is(1)))
                .andExpect(jsonPath("$.location.id", is(4)))
                .andExpect(jsonPath("$.title", is("LV4 NWT")))
                .andExpect(jsonPath("$.active", is(true)))
                .andReturn();
        ;

        return getEventFromRes(res.getResponse().getContentAsString());
    }

    @Test
    public void getUrl() throws Exception {
        String urlDiscoverUserService = "/services/notification-service";
        MvcResult r = mvc.perform(MockMvcRequestBuilders.get(urlDiscoverUserService))
                .andExpect(status().isOk())
                .andReturn();
    }

    @Order(1)
    @Test
    public void createEventNotifications() throws Exception {
        loginUser();
        EventDes e = getEvent();
        RestTemplate restTemplate = new RestTemplate();
        String createEventUrl = getNotificatonServiceUrl() + "/events/createEvent";
        try {
            HttpEntity<EventNotification> req = new HttpEntity<EventNotification>(new EventNotification(e.getId(), e.getTitle(), e.getDate(), token), getHeaders(token));
            ResponseEntity<String> res = restTemplate.exchange(createEventUrl, HttpMethod.POST, req, String.class);
            Assert.assertTrue(res.getStatusCode().value() == 200);
        }
        catch (HttpClientErrorException ex) {
            Assert.assertEquals(200, ex.getRawStatusCode());
        }
    }

    @Order(2)
    @Test
    public void updateEventNotifications() throws Exception {
        loginUser();
        EventDes e = getEvent();
        RestTemplate restTemplate = new RestTemplate();
        String updateEventUrl = getNotificatonServiceUrl() + "/events/7";
        HttpEntity<EventNotification> req = new HttpEntity<EventNotification>(new EventNotification(e.getId(), e.getTitle() +"Izmjena", e.getDate(), token), getHeaders(token));
        try {
            ResponseEntity<String> res = restTemplate.exchange(updateEventUrl, HttpMethod.PUT , req, String.class);
            Assert.assertTrue(res.getStatusCode().value() == 200);
        }
        catch (HttpClientErrorException ex) {
            Assert.assertEquals(200, ex.getRawStatusCode());
        }
    }

    @Order(3)
    @Test
    public void createGoingToNotificaion() throws Exception {
        loginUser();
        RestTemplate restTemplate = new RestTemplate();
        String createNotificationUrl = getNotificatonServiceUrl() + "/notifications/createGoingTo/7";
        try {
            ResponseEntity<String> res = restTemplate.exchange(createNotificationUrl, HttpMethod.POST , new HttpEntity<>(getHeaders(token)), String.class);
            Assert.assertTrue(res.getStatusCode().value() == 200);
        }
        catch (HttpClientErrorException ex) {
            Assert.assertEquals(200, ex.getRawStatusCode());
        }

    }

    @Order(4)
    @Test
    public void deleteEventNotifications () throws Exception {
        loginUser();
        RestTemplate restTemplate = new RestTemplate();
        String deleteEventUrl = getNotificatonServiceUrl() + "/events/7";
        try {
            ResponseEntity<String> res = restTemplate.exchange(deleteEventUrl, HttpMethod.DELETE , new HttpEntity<>(getHeaders(token)), String.class);
            Assert.assertTrue(res.getStatusCode().value() == 200);
        }
        catch (HttpClientErrorException ex) {
            Assert.assertEquals(200, ex.getRawStatusCode());
        }
    }


}
