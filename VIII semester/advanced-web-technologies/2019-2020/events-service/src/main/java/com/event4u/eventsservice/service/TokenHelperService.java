package com.event4u.eventsservice.service;

import com.event4u.eventsservice.model.Token;
import com.fasterxml.jackson.databind.ObjectMapper;
import io.jsonwebtoken.Claims;
import io.jsonwebtoken.ExpiredJwtException;
import io.jsonwebtoken.Jwts;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

import javax.xml.bind.DatatypeConverter;
import com.event4u.eventsservice.exceptionHandling.TokenException;

@Service
public class TokenHelperService {
    @Value("${jwt.secret}")
    private String key;

    public Token getTokenFromString(String token) {
        try {
            token=token.replace("Bearer ","");
            String base64Key = DatatypeConverter.printBase64Binary(key.getBytes());
            byte[] secretBytes = DatatypeConverter.parseBase64Binary(base64Key);
            Claims claim = Jwts.parser().setSigningKey(secretBytes).parseClaimsJws(token).getBody();
            ObjectMapper mapper = new ObjectMapper();
            return mapper.convertValue(claim, Token.class);
        }
        catch(Exception e) {
            throw new TokenException();
        }

    }

    public Long getUserIdFromToken(String token) {
        return getTokenFromString(token).getId();
    }
}
