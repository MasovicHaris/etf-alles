package com.event4u.notificationservice;

import static org.hamcrest.Matchers.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

import com.event4u.notificationservice.service.UserService;
import org.junit.Before;
import org.junit.jupiter.api.Test;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.MvcResult;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;

@SpringBootTest
@AutoConfigureMockMvc
public class EventControllerTest {

    @Autowired
    private MockMvc mvc;

    @Autowired
    private UserService userService;

    @Test
    public void getAllEventsTest() throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("/events")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(content().contentType("application/json"))
                .andExpect(jsonPath("$[0].eventId", is(1)))
                .andExpect(jsonPath("$[1].eventId", is(2)));

    }
    public String token="";
    public String idUsera;
    @Before
    public void setup() {
        String odg =  userService.getValidToken();
        int intIndex = odg.indexOf("token") +8;

        int intIndexId = odg.indexOf("id") + 4;

        //Da dobijemo id usera čiji je token
        idUsera=odg.substring(intIndexId, odg.indexOf(","));


        token=odg.substring(intIndex);
        token=token.substring(0, token.length() - 2);
    }

   /// public String token="";
   // @Before
   // public void setup() {
   ///     String odg =  userService.getValidToken();
    //    int intIndex = odg.indexOf("token") +8;
     //   token=odg.substring(intIndex,350);
    //}
    @Test
    public void getEventByIdTest() throws Exception {

        setup();
        HttpHeaders httph = new HttpHeaders();
        httph.add("Content-Type","application/json");
        httph.add("Authorization", "Bearer "+token);
        mvc.perform(MockMvcRequestBuilders.get("/events/getById/2").headers(httph)
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$.eventId", is(2)));
    }

    @Test
    public void getEventByIdErrorTest() throws Exception {
        setup();
        HttpHeaders httph = new HttpHeaders();
        httph.add("Content-Type","application/json");
        httph.add("Authorization", "Bearer "+token);
        mvc.perform(MockMvcRequestBuilders.get("/events/getById/88").headers(httph) //ne postoji
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isNotFound())
                .andExpect(jsonPath("$.message", is("Element not found")));
    }
    @Test
    public void postEventByIdTest() throws Exception {
        setup();
        HttpHeaders httph = new HttpHeaders();
        httph.add("Content-Type","application/json");
        httph.add("Authorization", "Bearer "+token);
        MvcResult rez = mvc.perform(MockMvcRequestBuilders.post("/events").headers(httph)
                .content("66"))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$.eventId", is(66))) //ako je uspjeno upisan ispise ga
                .andReturn();
    }
    @Test
    public void postEventByIdErrorTest() throws Exception {
        MvcResult rez = mvc.perform(MockMvcRequestBuilders.post("/events")
                .content(""))
                .andExpect(status().is4xxClientError())
                .andReturn();
    }

    @Test
    public void updateEventTest() throws Exception {
        setup();
        HttpHeaders httph = new HttpHeaders();
        httph.add("Content-Type","application/json");
        httph.add("Authorization", "Bearer "+token);
        MvcResult rez = mvc.perform(MockMvcRequestBuilders.put("/events/2").headers(httph)
                .content("{\"eventId\": 2,\"name\": \"promjena\",\"date\": \"2020-09-07\" }"))

                .andExpect(status().isOk())
                .andExpect(jsonPath("$.eventId", is(2))) //ako je uspjeno upisan ispise ga
                .andReturn();
    }

    @Test
    public void postEventByIdTest2() throws Exception {
        setup();
        HttpHeaders httph = new HttpHeaders();
        httph.add("Content-Type","application/json");
        httph.add("Authorization", "Bearer "+token);
        MvcResult rez = mvc.perform(MockMvcRequestBuilders.post("/events").headers(httph)
                .content("666"))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$.eventId", is(666))) //ako je uspjeno upisan ispise ga
                .andReturn();
    }
    @Test
    public void deleteEventTest() throws Exception {
        setup();
        HttpHeaders httph = new HttpHeaders();
        httph.add("Content-Type","application/json");
        httph.add("Authorization", "Bearer "+token);
        mvc.perform(MockMvcRequestBuilders.delete("/events/666").headers(httph))
                .andExpect(jsonPath("$.message", is("Successful deletion of the event with id: 666")))
                .andExpect(status().isOk());
    }
    @Test
    public void deleteEventTestError() throws Exception {
        setup();
        HttpHeaders httph = new HttpHeaders();
        httph.add("Content-Type","application/json");
        httph.add("Authorization", "Bearer "+token);
        mvc.perform(MockMvcRequestBuilders.delete("/events/6666").headers(httph))
                .andExpect(status().is4xxClientError())
                .andExpect(jsonPath("$.message", is("Error deleting event with id: 6666")));
    }

@Test
    public void postEvent2Test() throws Exception {
        setup();
        HttpHeaders httph = new HttpHeaders();
        httph.add("Content-Type","application/json");
        httph.add("Authorization", "Bearer "+token);
        MvcResult rez = mvc.perform(MockMvcRequestBuilders.post("/events/createEvent")
                .content("{\n" +
                        "\t\"eventId\": 19,\n" +
                        "\t\"name\": \"Ime eventa\",\n" +
                        "\t\"date\": \"2020-07-07\"\n" +
                        "}").headers(httph))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$.name", is("Ime eventa")))
                .andExpect(jsonPath("$.eventId", is(19)))
                .andReturn();
    }

    public void postEvent2TestChcekCreatedNotification() throws Exception {
        setup();
        HttpHeaders httph = new HttpHeaders();
        httph.add("Content-Type","application/json");
        httph.add("Authorization", "Bearer "+token);
            mvc.perform(MockMvcRequestBuilders.get("/notifications/getByEventId/19").headers(httph)
                    .accept(MediaType.APPLICATION_JSON))
                    .andExpect(status().isOk())
                    .andExpect(jsonPath("$", hasSize(1)))
                    .andExpect(jsonPath("$[0].notificationId", is(4)))
                    .andExpect(jsonPath("$[0].eventId", is(19)))
            ;
        }
}
