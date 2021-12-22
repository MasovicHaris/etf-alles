package com.event4u.eventsservice.helpers;

import com.event4u.eventsservice.model.*;
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

public class EventIdDeserializer extends StdDeserializer<EventDes> {
    public EventIdDeserializer() {
        this(null);
    }

    public EventIdDeserializer(Class<?> vc) {
        super(vc);
    }

    @Override
    public EventDes deserialize(JsonParser jsonParser, DeserializationContext deserializationContext)  throws IOException, JsonProcessingException  {

        JsonNode node = jsonParser.getCodec().readTree(jsonParser);
        Long id = Long.valueOf((Integer) node.get("id").numberValue());
        String title =  node.get("title").asText();
        String address = node.get("address").asText();
        LocalDate date = LocalDate.parse(node.get("date").asText());
        String description = node.get("description").asText();
        Boolean isActive = node.get("active").asBoolean();
        return new EventDes(id, title, address, date, description, isActive);
    }
}
