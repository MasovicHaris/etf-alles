package com.event4u.eventsservice.model;

import javax.persistence.*;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.awt.*;
import java.util.List;

@Entity
@Table(name = "Location")
public class Location {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    @NotNull(message = "Coordinates cannot be null or empty")
    @Column(nullable=false)
    private Point coordinates;
    @NotNull(message = "City cannot be null or empty")
    @NotBlank(message = "City cannot be null or empty")
    @Column(nullable=false)
    private String city;
    @NotNull(message = "Country cannot be null or empty")
    @NotBlank(message = "Country cannot be null or empty")
    @Column(nullable=false)
    private String country;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "location")
    private List<Event> events;

    protected Location() {

    }

    public Location(Point coordinates, String city, String country) {
        this.coordinates = new Point(coordinates.x,coordinates.y);
        this.city = city;
        this.country = country;
    }

    @Override
    public String toString() {
        return String.format(
                "Location[id=%d, coordinates=[%d,%d], city='%s', country='%s']",
                id, coordinates.x, coordinates.y, city, country
        );
    }

    public Long getId() {
        return id;
    }

    public String getCity() {
        return city;
    }

    public String getCountry() {
        return country;
    }

    public Point getCoordinates() {
        return coordinates;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public void setCoordinates(Point coordinates) {
        this.coordinates = coordinates;
    }

    public void setCountry(String country) {
        this.country = country;
    }
}
