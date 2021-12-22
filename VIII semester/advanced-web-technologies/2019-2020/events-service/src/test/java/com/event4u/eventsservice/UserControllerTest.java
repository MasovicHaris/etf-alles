package com.event4u.eventsservice;

import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.mock.web.MockHttpServletRequest;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.MvcResult;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;

import static org.hamcrest.Matchers.hasSize;
import static org.hamcrest.Matchers.is;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.jsonPath;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
@SpringBootTest
@AutoConfigureMockMvc
public class UserControllerTest {
    @Autowired
    private MockMvc mvc;

    @Test
    public void getAllUsers() throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("/events-micro/users")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$", hasSize(3)))
                .andExpect(jsonPath("$[0].id", is(1)))
                .andExpect(jsonPath("$[1].id", is(2)))
                .andExpect(jsonPath("$[2].id", is(3)))
        ;
    }

    @Test
    public void getUserById() throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("/events-micro/users/1")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$.id", is(1)))
        ;
    }

    public Long getNumberOfUsers() throws Exception {
        MvcResult r = mvc.perform(MockMvcRequestBuilders.get("/events-micro/users/count")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andReturn();
        return Long.valueOf(r.getResponse().getContentAsString());
    }

    @Order(1)
    @Test
    public void addUser() throws Exception {
        Long count1 = getNumberOfUsers();
        mvc.perform(MockMvcRequestBuilders.post("/events-micro/users/4")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$.id", is(4)));
        Long count2 = getNumberOfUsers();
        if (count1 != count2-1) {
            throw new Exception("Add new user test: User not added!");
        }
    }

    @Test
    public void addUserBadReq() throws Exception {
        Long count1 = getNumberOfUsers();
        mvc.perform(MockMvcRequestBuilders.post("/events-micro/users/1")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isBadRequest())
                .andExpect(jsonPath("$.message",is("User with id 1 already exists!")));
    }

    @Order(2)
    @Test
    public void deleteNewUser() throws Exception {
        Long count1 = getNumberOfUsers();
        mvc.perform(MockMvcRequestBuilders.delete("/events-micro/users/4")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk());
        Long count2 = getNumberOfUsers();
        if (count1 != count2+1) {
            throw new Exception("Delete new user test: User not deleted!");
        }
    }

    @Test
    public void deleteNewUserBadReq() throws Exception {
        mvc.perform(MockMvcRequestBuilders.delete("/events-micro/users/409"))
                .andExpect(status().isNotFound())
                .andExpect(jsonPath("$.message", is("User with id 409 not found!")));
    }
}
