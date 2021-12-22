package com.event4u.eventsservice;

import com.event4u.eventsservice.model.Category;

import static org.hamcrest.Matchers.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;

import org.junit.jupiter.api.TestMethodOrder;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.MvcResult;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;

@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
@SpringBootTest
@AutoConfigureMockMvc
public class CategoryControllerTest {

    @Autowired
    private MockMvc mvc;

    @Order(1)
    @Test
    public void getAllCategories() throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("/events-micro/categories")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$", hasSize(3)))
                .andExpect(jsonPath("$[0].id", is(1)))
                .andExpect(jsonPath("$[0].name", is("Outdoors&Adventure")))
                .andExpect(jsonPath("$[1].id", is(2)))
                .andExpect(jsonPath("$[1].name", is("Tech")))
                .andExpect(jsonPath("$[2].id", is(3)))
                .andExpect(jsonPath("$[2].name", is("Learning")))
                ;
    }

    @Test
    public void getCategoryById() throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("/events-micro/categories/1")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$.id", is(1)))
                .andExpect(jsonPath("$.name", is("Outdoors&Adventure")))
        ;
    }

    @Test
    public void getCategoryByIdBadParameter() throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("/events-micro/categories/-11")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isNotFound())
                .andExpect(jsonPath("$.message", is("Category with id -11 not found!")))
        ;
    }

    @Test
    public void getCategoryByIdBadParameterType() throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("/events-micro/categories/fkdsj")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isBadRequest())
        ;
    }

    @Order(2)
    @Test
    public void getNumberOfCategories() throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("/events-micro/categories/count")
                .accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(content().string("3"))
        ;
    }

    public Category convertResToCategory(String res) {
        ObjectMapper m = new ObjectMapper();
        try {
            Category newCategory = m.readValue(res, Category.class);
            return newCategory;
        } catch (JsonProcessingException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Order(3)
    @Test
    public void createCategory() throws Exception {
        MvcResult r = mvc.perform(MockMvcRequestBuilders.post("/events-micro/categories")
                .content("Fitness"))
                .andExpect(status().isOk())
                .andReturn()
                ;
        convertResToCategory(r.getResponse().getContentAsString());

    }

    @Order(4)
    @Test
    public void createCategoryAlreadyExists() throws Exception {
        mvc.perform(MockMvcRequestBuilders.post("/events-micro/categories")
                .content("Fitness"))
                .andExpect(status().isBadRequest())
                .andExpect(jsonPath("$.message",is("Category with name Fitness already exists!")))
                ;
    }

    @Test
    public void createCategoryNoBody() throws Exception {
        mvc.perform(MockMvcRequestBuilders.post("/events-micro/categories"))
                .andExpect(status().isBadRequest())
            ;
    }

    public Category createCategoryHelper(String content) throws Exception {
        MvcResult r = mvc.perform(MockMvcRequestBuilders.post("/events-micro/categories")
                .content(content))
                .andExpect(status().isOk())
                .andReturn()
                ;
        return convertResToCategory(r.getResponse().getContentAsString());
    }

    @Order(5)
    @Test
    public void updateCategoryById() throws Exception {
        Category newCategory = createCategoryHelper("Sports");
        String id = newCategory.getId().toString();
        String url = "/events-micro/categories/"+ id;
        MvcResult r = mvc.perform(MockMvcRequestBuilders.put(url)
                .content("NWT"))
                .andExpect(status().isOk())
                .andReturn()
                ;
        Category updatedCategory = convertResToCategory(r.getResponse().getContentAsString());
        if (!updatedCategory.getName().equals("NWT")) {
            throw new Exception("Not updated");
        }
    }

    @Test
    public void updateCategoryByIdBadRequest() throws Exception {
        createCategoryHelper("Cooking");
        String url = "/events-micro/categories/lkdsfjsldjf";
        mvc.perform(MockMvcRequestBuilders.put(url)
                .content("NWT"))
                .andExpect(status().isBadRequest())
                ;
    }

    @Test
    public void updateCategoryByIdNotFound() throws Exception {
        createCategoryHelper("Books");
        String url = "/events-micro/categories/-11";
        mvc.perform(MockMvcRequestBuilders.delete(url))
                .andExpect(status().isNotFound())
                .andExpect(jsonPath("$.message", is("Category with id -11 not found!")));
    }

    @Test
    public void deleteCategoryById() throws Exception {
        Category newCategory = createCategoryHelper("Cooking");
        String url = "/events-micro/categories/"+newCategory.getId().toString();
        mvc.perform(MockMvcRequestBuilders.delete(url)).andExpect(status().isOk());
    }

    @Test
    public void deleteCategoryByIdBadRequest() throws Exception {
        createCategoryHelper("Running");
        String url = "/events-micro/categories/sdf";
        mvc.perform(MockMvcRequestBuilders.delete(url)).andExpect(status().is5xxServerError());
    }

    @Test
    public void deleteCategoryByIdNotFound() throws Exception {
        createCategoryHelper("Music");
        String url = "/events-micro/categories/-11";
        mvc.perform(MockMvcRequestBuilders.delete(url))
                .andExpect(status().isNotFound())
                .andExpect(jsonPath("$.message", is("Category with id -11 not found!")));
    }
}
