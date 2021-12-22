package com.event4u.eventsservice.model;

public class Token {
    private Long id;
    private String name;
    private String surname;
    private String username;
    private Long iat;
    private Long exp;


    protected Token() {

    }

    public Token(Long id, String name, String surname, String username, Long iat, Long exp) {
        this.name = name;
        this.id=id;
        this.surname=surname;
        this.username=username;
        this.iat=iat;
        this.exp=exp;
    }

    public Long getExp() {
        return exp;
    }

    public Long getIat() {
        return iat;
    }

    public Long getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getSurname() {
        return surname;
    }

    public String getUsername() {
        return username;
    }

}
