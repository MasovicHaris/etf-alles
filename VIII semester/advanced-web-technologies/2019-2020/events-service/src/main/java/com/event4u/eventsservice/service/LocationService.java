package com.event4u.eventsservice.service;

import com.event4u.eventsservice.exceptionHandling.AlreadyExistsException;
import com.event4u.eventsservice.exceptionHandling.NotFoundException;
import com.event4u.eventsservice.model.Category;
import com.event4u.eventsservice.model.Location;
import com.event4u.eventsservice.repository.LocationRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.awt.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@Service
public class LocationService {
    @Autowired
    private LocationRepository locationRepository;

    public List<Location> findAll() {
        var it = locationRepository.findAll();
        var locations = new ArrayList<Location>();
        it.forEach(e -> locations.add(e));
        return locations;
    }

    public Location findById(Long id) {
        Optional<Location> l = locationRepository.findById(id);
        if (!l.isPresent()) {
            throw new NotFoundException("Location with id " + id.toString());
        }
        return l.get();
    }

    public Long count() {
        return locationRepository.count();
    }

    public void deleteById(Long locationId) {
        if (!locationRepository.existsById(locationId)) {
            throw new NotFoundException("Location with id " + locationId.toString());
        }
        locationRepository.deleteById(locationId);
    }

    public Location addNewLocation(Point coordinates, String city, String country) {
        List<Location> locations = findAll();
        locations.forEach(l-> {
            if (l.getCity().equals(city) && l.getCountry().equals(country)) {
                throw new AlreadyExistsException("Location " + city + " " + country);
            }
        });
        return locationRepository.save(new Location(coordinates, city, country));
    }

    public Location updateLocation(Long id, Point coordinates, String city, String country) {
        if (!locationRepository.existsById(id)) {
            throw new NotFoundException("Location with id " + id.toString());
        }
        List<Location> locations = findAll();
        locations.forEach(l-> {
            if (l.getCity().equals(city) && l.getCountry().equals(country)) {
                throw new AlreadyExistsException("Location " + city + " " + country);
            }
        });
        return locationRepository.findById(id).map(location-> {
            location.setCoordinates(coordinates);
            location.setCity(city);
            location.setCountry(country);
            return locationRepository.save(location);
        }).orElseThrow();
    }
}
