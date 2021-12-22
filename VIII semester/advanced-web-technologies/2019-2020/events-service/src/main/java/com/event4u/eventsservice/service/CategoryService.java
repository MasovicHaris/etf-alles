package com.event4u.eventsservice.service;

import com.event4u.eventsservice.exceptionHandling.AlreadyExistsException;
import com.event4u.eventsservice.exceptionHandling.InvalidParameterException;
import com.event4u.eventsservice.exceptionHandling.NotFoundException;
import com.event4u.eventsservice.model.Category;
import com.event4u.eventsservice.repository.CategoryRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@Service
public class CategoryService {

    @Autowired
    private CategoryRepository categoryRepository;

    public List<Category> findAll() {
        var it = categoryRepository.findAll();
        var categories = new ArrayList<Category>();
        it.forEach(c -> {
            categories.add(c);
        });
        return categories;
    }

    public Category findById(Long id) {
        Optional<Category> c =  categoryRepository.findById(id);
        if (!c.isPresent()) {
            throw new NotFoundException("Category with id " + id.toString());
        }
        return c.get();
    }

    public Long count() {
        return categoryRepository.count();
    }

    public void deleteById(Long categoryId) {
        if (!categoryRepository.existsById(categoryId)) {
            throw new NotFoundException("Category with id " + categoryId.toString());
        }
        categoryRepository.deleteById(categoryId);
    }

    public Category createCategory(String name, String image, String color) {
        if (name.isEmpty()) {
            throw new InvalidParameterException("Category name cannot be null!");
        }
        List<Category> categories = findAll();
        categories.forEach(c-> {
            if (c.getName().equals(name)) {
                throw new AlreadyExistsException("Category with name " + name);
            }
        });
        return categoryRepository.save(new Category(name, image, color));
    }

    public Category updateCategory(Long id, String name) {
        if (name.isEmpty()) {
            throw new InvalidParameterException("Category name cannot be null!");
        }
        if (!categoryRepository.existsById(id)) {
            throw new NotFoundException("Category with id " + id.toString());
        }
        Category c = categoryRepository.findById(id).map(category -> {
            category.setName(name);
            return categoryRepository.save(category);
        }).orElseThrow();
        c.getEvents().forEach(e-> e.setCategory(null));
        return c;
    }
}
