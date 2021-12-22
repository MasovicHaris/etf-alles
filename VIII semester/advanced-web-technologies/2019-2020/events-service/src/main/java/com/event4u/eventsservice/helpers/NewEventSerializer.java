package com.event4u.eventsservice.helpers;

import com.event4u.eventsservice.model.NewEvent;
import com.fasterxml.jackson.core.JsonGenerator;
import com.fasterxml.jackson.databind.SerializerProvider;
import com.fasterxml.jackson.databind.ser.std.StdSerializer;

import java.io.IOException;

public class NewEventSerializer extends StdSerializer<NewEvent>  {
    public NewEventSerializer(Class<NewEvent> newEventClass) {
        super(newEventClass);
    }

    @Override
    public void serialize(NewEvent event, JsonGenerator jsonGenerator, SerializerProvider serializerProvider) throws IOException {
        jsonGenerator.writeStartObject();
        jsonGenerator.writeStringField("title", event.getTitle());
        jsonGenerator.writeStringField("address", event.getAddress());
        jsonGenerator.writeStringField("date", event.getDate().toString());
        jsonGenerator.writeStringField("description", event.getDescription());
        jsonGenerator.writeNumberField("idCategory", event.getIdCategory());
        jsonGenerator.writeNumberField("idLocation", event.getIdLocation());
        jsonGenerator.writeBooleanField("isActive", event.getActive());
    }

}
