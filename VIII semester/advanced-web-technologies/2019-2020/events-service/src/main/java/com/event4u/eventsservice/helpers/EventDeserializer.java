/*
package com.event4u.eventsservice.helpers;

import com.event4u.eventsservice.model.Category;
import com.event4u.eventsservice.model.Event;
import com.event4u.eventsservice.model.Location;
import com.event4u.eventsservice.model.User;
import com.fasterxml.jackson.annotation.JsonAutoDetect;
import com.fasterxml.jackson.annotation.PropertyAccessor;
import com.fasterxml.jackson.core.JsonParser;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.*;
import com.fasterxml.jackson.databind.deser.std.DelegatingDeserializer;
import com.fasterxml.jackson.databind.deser.std.StdDeserializer;
import org.springframework.context.annotation.Bean;

import java.io.DataInput;
import java.io.IOException;
import java.time.LocalDate;

public class EventDeserializer extends StdDeserializer<Event> {
    public EventDeserializer() {
        this(null);
    }

    public EventDeserializer(Class<?> vc) {
        super(vc);
    }
    @Bean
    public ObjectMapper objectMapper() {
        ObjectMapper mapper = new ObjectMapper();
        mapper.configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
        mapper.configure(MapperFeature.DEFAULT_VIEW_INCLUSION, true);
        mapper.configure(SerializationFeature.FAIL_ON_EMPTY_BEANS, false);
        mapper.setVisibility(PropertyAccessor.ALL, JsonAutoDetect.Visibility.NONE);
        mapper.setVisibility(PropertyAccessor.FIELD, JsonAutoDetect.Visibility.ANY);
        return mapper;
    }

    @Override
    public Event deserialize(JsonParser jsonParser, DeserializationContext deserializationContext)  throws IOException, JsonProcessingException  {
        */
/*JsonNode node = jsonParser.getCodec().readTree(jsonParser);
        Long id = Long.valueOf((Integer) node.get("id").numberValue());
        String title =  node.get("title").asText();
        String address = node.get("address").asText();
        LocalDate date = LocalDate.parse(node.get("date").asText());
        String description = node.get("description").asText();
        Boolean isActive = node.get("active").asBoolean();
        Category c = objectMapper().readValue(node.get("category").asText(), Category.class); //(Category) node.get("category").traverse(jsonParser.getCodec()).readValuesAs(Category.class);
        User user = (User) node.get("creator").traverse(jsonParser.getCodec()).readValuesAs(User.class);
        Location location = (Location) node.get("location").traverse(jsonParser.getCodec()).readValuesAs(Location.class);
        *//*

        Event e = (Event) super.deserialize(jsonParser, deserializationContext);
        return new Event(id, title, address, date, description, c, user, location, isActive);
    }
}
*/
