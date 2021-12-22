package com.event4u.eventsservice.controller;

import com.event4u.eventsservice.grpc.Event4U;
import com.event4u.eventsservice.model.Category;
import com.event4u.eventsservice.model.SuccessMessage;
import com.event4u.eventsservice.service.CategoryService;
import com.event4u.eventsservice.service.LogActionService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RequestMapping("events-micro/categories")
@RestController
public class CategoryController {
    @Autowired
    private CategoryService categoryService;
    @Autowired
    private LogActionService logActionService;

    @GetMapping(path ="", produces = {MediaType.APPLICATION_JSON_VALUE})
    public List<Category> allCategories() {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.GET,"Category");
        return categoryService.findAll();
    }

    @GetMapping(path = "/count", produces = {MediaType.APPLICATION_JSON_VALUE})
    public Long count() {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.GET,"Category");
        return categoryService.count();
    }

    @GetMapping(path = "/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public Category getCategoryById(@PathVariable Long id) {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.GET,"Category");
        return categoryService.findById(id);
    }

    @PostMapping(path = "", produces = {MediaType.APPLICATION_JSON_VALUE})
    public Category newCategory(@RequestBody String name, @RequestBody String image, @RequestBody String color) {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.CREATE,"Category");
        return categoryService.createCategory(name, image, color);
    }

    @DeleteMapping(path = "/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public SuccessMessage deleteCategory(@PathVariable String id) {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.DELETE,"Category");
        Long categoryId = Long.parseLong(id);
        categoryService.deleteById(categoryId);
        return new SuccessMessage("Category with id " +  id + " successfully deleted");
    }

    @PutMapping(path ="/{id}", produces = {MediaType.APPLICATION_JSON_VALUE})
    public Category updateCategory(@RequestBody String name, @PathVariable Long id) {
        logActionService.logAction(Long.valueOf("0"), Event4U.Request.ActionType.UPDATE,"Category");
        return categoryService.updateCategory(id, name);
    }

}
