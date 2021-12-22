package com.event4u.eventsservice;

import static org.hamcrest.Matchers.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

import com.event4u.eventsservice.helpers.EventIdDeserializer;
import com.event4u.eventsservice.helpers.NewEventSerializer;
import com.event4u.eventsservice.model.EventDes;
import com.event4u.eventsservice.model.NewEvent;
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
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.MvcResult;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.web.client.RestTemplate;

import java.time.LocalDate;

@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
@SpringBootTest
@AutoConfigureMockMvc
public class EventControllerTest {
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


    @Order(1)
    @Test
    public void getNumberOfEvents() throws Exception {
        MvcResult r = mvc.perform(MockMvcRequestBuilders.get("/events-micro/events/count")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(content().string("2"))
                .andReturn()
        ;
    }

    @Order(2)
    @Test
    public void getAllEvents() throws Exception{
        mvc.perform(MockMvcRequestBuilders.get("/events-micro/events")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$", hasSize(2)))
                .andExpect(jsonPath("$[0].id", is(7)))
                .andExpect(jsonPath("$[0].address", is("Zmaja od Bosne bb")))
                .andExpect(jsonPath("$[0].date", is("2020-03-23")))
                .andExpect(jsonPath("$[0].description", is("Laboratorijske vježbe iz predmeta NWT")))
                .andExpect(jsonPath("$[0].category.id", is(1)))
                .andExpect(jsonPath("$[0].creator.id", is(1)))
                .andExpect(jsonPath("$[0].location.id", is(4)))
                .andExpect(jsonPath("$[0].title", is("LV4 NWT")))
                .andExpect(jsonPath("$[0].active", is(true)));

    }

    @Order(3)
    @Test
    public void getEventById() throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("/events-micro/events/7")
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
                .andExpect(jsonPath("$.active", is(true)));

        ;
    }

    public int getEventsCount() throws Exception {
        MvcResult r = mvc.perform(MockMvcRequestBuilders.get("/events-micro/events/count")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andReturn()
                ;
        String num = r.getResponse().getContentAsString();
        return Integer.parseInt(num);
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


    @Order(4)
    @Test
    public void createEvent() throws Exception {
        loginUser();
        NewEvent newEvent = new NewEvent("LV6 NWT", "Zmaja od Bosne bb", LocalDate.of(2020,03,30), "Laboratorijske vježbe iz predmeta NWT", Long.valueOf(1),Long.valueOf(6), Boolean.TRUE, "", "09:00", "10:00", null );
        MvcResult r = mvc.perform(MockMvcRequestBuilders.post("/events-micro/events")
                .contentType(MediaType.APPLICATION_JSON)
                .header(HttpHeaders.AUTHORIZATION,"Bearer " + token)
                .content(convertEventToJson(newEvent)))
                .andExpect(status().isOk())
                .andReturn()
                ;
    }

    public EventDes createEventHelper() throws Exception {
        loginUser();
        NewEvent newEvent = new NewEvent("LV6 NWT", "Zmaja od Bosne bb", LocalDate.of(2020,03,30), "Laboratorijske vježbe iz predmeta NWT", Long.valueOf(1),Long.valueOf(6), Boolean.TRUE,"", "09:00", "10:00", null  );
        MvcResult r = mvc.perform(MockMvcRequestBuilders.post("/events-micro/events")
                .contentType(MediaType.APPLICATION_JSON)
                .header(HttpHeaders.AUTHORIZATION,"Bearer " + token)
                .content(convertEventToJson(newEvent)))
                .andExpect(status().isOk())
                .andReturn()
                ;
        return getEventFromRes(r.getResponse().getContentAsString());
    }

    @Order(5)
    @Test
    public void updateEventById() throws Exception {
        EventDes createdEvent = createEventHelper();
        loginUser();
        NewEvent newEvent = new NewEvent("P NWT", "Zmaja od Bosne bb", LocalDate.of(2020,04,07), "Laboratorijske vježbe iz predmeta NWT", Long.valueOf(1),Long.valueOf(4), Boolean.TRUE,"", "09:00", "10:00", null);
        String url = "/events-micro/events/"+createdEvent.getId().toString();
        MvcResult r = mvc.perform(MockMvcRequestBuilders.put(url)
                .contentType(MediaType.APPLICATION_JSON)
                .header(HttpHeaders.AUTHORIZATION,"Bearer " + token)
                .content(convertEventToJson(newEvent)))
                .andExpect(status().isOk())
                .andReturn()
                ;
        // Provjera je li upisano
        String res = r.getResponse().getContentAsString();
        EventDes e = getEventFromRes(res);
        Assert.assertTrue(e.getId().equals(createdEvent.getId()));
        Assert.assertTrue(e.getTitle().equals(newEvent.getTitle()));
        Assert.assertTrue(e.getDate().equals(newEvent.getDate()));
    }

    @Order(5)
    @Test
    public void updateEventByIdNoBody() throws Exception {
        EventDes event = createEventHelper();
        String url = "/events-micro/events/"+event.getId().toString();
        mvc.perform(MockMvcRequestBuilders.put(url)
                .contentType(MediaType.APPLICATION_JSON))
                .andExpect(status().isBadRequest())
                ;
    }


    @Order(6)
    @Test
    public void deleteEventyById() throws Exception {
        EventDes event = createEventHelper();
        String url = "/events-micro/events/"+event.getId().toString();
        mvc.perform(MockMvcRequestBuilders.delete(url)
                .header(HttpHeaders.AUTHORIZATION,"Bearer " + token))
                .andExpect(status().isOk());
    }

    @Order(7)
    @Test
    public void deleteEventyByIdBadRequest() throws Exception {
        EventDes event = createEventHelper();
        String url = "/events-micro/events/"+event.getId().toString();
        mvc.perform(MockMvcRequestBuilders.delete(url)).andExpect(status().isBadRequest());
    }


}
