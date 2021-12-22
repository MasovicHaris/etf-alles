package com.event4u.eventsservice;

import static org.hamcrest.Matchers.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

import com.event4u.eventsservice.helpers.EventIdDeserializer;
import com.event4u.eventsservice.helpers.NewEventSerializer;
import com.event4u.eventsservice.model.*;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.module.SimpleModule;
import net.minidev.json.JSONObject;
import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;

import org.junit.jupiter.api.TestMethodOrder;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.*;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.MvcResult;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.web.client.RestTemplate;

import java.time.LocalDate;

@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
@SpringBootTest
@AutoConfigureMockMvc
public class EventUserControllerTest {


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

    private static void signup(String signupUrl) {
        RestTemplate restTemplate = new RestTemplate();
        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.APPLICATION_JSON);
        JSONObject newUserJsonObject = new JSONObject();
        newUserJsonObject.put("name", "test");
        newUserJsonObject.put("surname", "test");
        newUserJsonObject.put("username", "test");
        newUserJsonObject.put("password", "test");
        HttpEntity<String> request = new HttpEntity<String>(newUserJsonObject.toString(), headers);
        String resultAsJsonStr = restTemplate.postForObject(signupUrl, request, String.class); //TODO: why error??
    }

    public void getGoingForEventById(Integer id, Integer idUser) throws Exception {
        MvcResult res = mvc.perform(MockMvcRequestBuilders.get("/events-micro/going/" + id.toString())
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$", hasSize(1)))
                .andExpect(jsonPath("$[0].id", is(idUser)))
                .andReturn()
        ;
    }

    private void getInterestedForEventById(Integer id, Integer idUser) throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("/events-micro/interested/" + id.toString())
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$", hasSize(1)))
                .andExpect(jsonPath("$[0].id", is(idUser)))
                .andReturn()
        ;
    }

    private void getNumberOfGoingForEventById(Integer id, Integer idUser) throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("/events-micro/goingNum/" + id.toString())
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(content().string("0"))
        ;
    }

    @Test
    public void getGoingForEvent() throws Exception {
        getGoingForEventById(7,2);
    }


    @Test
    public void getGoingForEventBadRequest() throws Exception {
        String url = "/events-micro/going/-11";
        mvc.perform(MockMvcRequestBuilders.get(url))
                .andExpect(status().isNotFound())
                .andExpect(jsonPath("$.message", is("Event with id -11 not found!")));
    }

    @Order(0)
    @Test
    public void getInterestedForEvent() throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("/events-micro/interested/7")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$", hasSize(0)))
        ;
    }

    @Order(0)
    @Test
    public void getInterestedForEventBadRequest() throws Exception {
        String url = "/events-micro/interested/-11";
        mvc.perform(MockMvcRequestBuilders.get(url))
                .andExpect(status().isNotFound())
                .andExpect(jsonPath("$.message", is("Event with id -11 not found!")));
    }

    @Order(0)
    @Test
    public void getNumberOfGoingForEvent() throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("/events-micro/goingNum/7")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(content().string("1"))
        ;
    }

    @Order(0)
    @Test
    public void getNumberOfGoingForEventBadRequest() throws Exception {
        String url = "/events-micro/goingNum/-11";
        mvc.perform(MockMvcRequestBuilders.get(url))
                .andExpect(status().isNotFound())
                .andExpect(jsonPath("$.message", is("Event with id -11 not found!")));
    }

    @Order(0)
    @Test
    public void getNumberOfInterestedForEvent() throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("/events-micro/interestedNum/7")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(content().string("0"))
        ;
    }

    @Test
    public void getNumberOfInterestedForEventBadRequest() throws Exception {
        String url = "/events-micro/interestedNum/-11";
        mvc.perform(MockMvcRequestBuilders.get(url))
                .andExpect(status().isNotFound())
                .andExpect(jsonPath("$.message", is("Event with id -11 not found!")));
    }

    public String convertEventToJson(NewEvent event) {
        ObjectMapper m = new ObjectMapper();
        SimpleModule module = new SimpleModule();
        module.addSerializer(NewEvent.class, new NewEventSerializer(NewEvent.class));
        m.registerModule(module);
        try {
            String s =  m.writeValueAsString(event);
            return s;
        } catch (JsonProcessingException e) {
            e.printStackTrace();
        }
        return "";
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

    public EventDes createEventHelper() throws Exception {
        loginUser();
        NewEvent newEvent = new NewEvent("LV6 NWT", "Zmaja od Bosne bb", LocalDate.of(2020,03,30), "Laboratorijske vježbe iz predmeta NWT", Long.valueOf(1),Long.valueOf(6), Boolean.TRUE, "", "08:00", "", null );
        MvcResult r = mvc.perform(MockMvcRequestBuilders.post("/events-micro/events")
                .contentType(MediaType.APPLICATION_JSON)
                .header(HttpHeaders.AUTHORIZATION,"Bearer " + token)
                .content(convertEventToJson(newEvent)))
                .andExpect(status().isOk())
                .andReturn()
                ;
        return getEventFromRes(r.getResponse().getContentAsString());
    }

    @Order(1)
    @Test
    public void MarkEventAsInterested() throws Exception{
        Integer idEvent = 7;
        String url = "/events-micro/interested/"+idEvent.toString();
        loginUser();
        mvc.perform(MockMvcRequestBuilders.post(url)
                .contentType(MediaType.APPLICATION_JSON)
                .header(HttpHeaders.AUTHORIZATION,"Bearer " + token))
                .andExpect(status().isOk())
                .andExpect(content().json("{" +
                        "\"message\": \"Event successfully marked as interested\"" +
                        "}"))
                .andReturn()
        ;
        getInterestedForEventById(7,2);
    }

    @Order(1)
    @Test
    public void MarkEventAsGoing() throws Exception{
        EventDes event = createEventHelper();
        loginUser();
        String url = "/events-micro/going/"+event.getId().toString();
        mvc.perform(MockMvcRequestBuilders.post(url)
                .contentType(MediaType.APPLICATION_JSON)
                .header(HttpHeaders.AUTHORIZATION,"Bearer " + token))
                .andExpect(status().isOk())
                .andExpect(content().json("{" +
                        "\"message\": \"Event successfully marked as going\"" +
                        "}"))
                .andReturn()
        ;
        getGoingForEventById(event.getId().intValue(), 2);
    }

    @Order(3)
    @Test
    public void DeleteMark() throws Exception{
        Integer idEvent = 8;
        loginUser();
        String url = "/events-micro/removeMark/"+idEvent.toString();
        mvc.perform(MockMvcRequestBuilders.delete(url)
                .contentType(MediaType.APPLICATION_JSON)
                .header(HttpHeaders.AUTHORIZATION,"Bearer " + token))
                .andExpect(status().isOk())
                .andExpect(content().json("{" +
                        "\"message\": \"Mark successfully removed\"" +
                        "}"))
                .andReturn()
        ;
    }

    @Order(3)
    @Test
    public void checkIfRemovedFromDB() throws Exception {
        getNumberOfGoingForEventById(8,1);
    }


    @Test
    public void MarkEventAsInterestedBadReq() throws Exception{
        Integer idEvent = 70;
        String url = "/events-micro/interested/"+idEvent.toString();
        loginUser();
        mvc.perform(MockMvcRequestBuilders.post(url)
                .contentType(MediaType.APPLICATION_JSON)
                .header(HttpHeaders.AUTHORIZATION,"Bearer " + token))
                .andExpect(status().isNotFound())
                .andExpect(jsonPath("$.message", is("Event with id 70 not found!")))
                .andReturn()
        ;
    }

    @Test
    public void MarkEventAsGoingBadReq() throws Exception{
        Integer idEvent = 80;
        loginUser();
        String url = "/events-micro/going/"+idEvent.toString();
        mvc.perform(MockMvcRequestBuilders.post(url)
                .contentType(MediaType.APPLICATION_JSON)
                .header(HttpHeaders.AUTHORIZATION,"Bearer " + token))
                .andExpect(status().isNotFound())
                .andExpect(jsonPath("$.message", is("Event with id 80 not found!")))
                .andReturn()
        ;
    }

    @Test
    public void DeleteMarkReq() throws Exception{
        Integer idEvent = 80;
        loginUser();
        String url = "/events-micro/removeMark/"+idEvent.toString();
        mvc.perform(MockMvcRequestBuilders.delete(url)
                .contentType(MediaType.APPLICATION_JSON)
                .header(HttpHeaders.AUTHORIZATION,"Bearer " + token))
                .andExpect(status().isNotFound())
                .andExpect(jsonPath("$.message", is("Event with id 80 not found!")))
                .andReturn()
        ;
    }

}

